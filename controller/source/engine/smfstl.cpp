#include "stdafx.h"

#include "smfstl.h"
#include "deltatime.h"
#include "fileanswer.h"
//class implimentation
#include <fcntl.h>

#ifdef _HAL_WINDOWS
#include <sys\stat.h>
#endif

//#define DEBUG_SMSTL

#define GetMsgLength(b)  (b < 0xF0 ? CMsgLen[(b >> 4) - 8] : SMsgLen[b & 0x0F]);


int CMsgLen[] = { 2, 2, 2, 2, 1, 1, 2 };
int SMsgLen[] = { 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

TSmf::TSmf():
  fInSysex(false), 
  wTickInterval(480),
  wCurrentTrack(0),   
  dwNumEvents(0), 
  dwMaxTime(0)
{
}

TSmf::~TSmf()
{
  //delete the buffers
  Close();
}

bool TSmf::Read(const char* FileName)
{
  FILE* InFile;
	const DWORD FileBuffLen = 255;
	char FullFileName [FileBuffLen];


#ifdef DEBUG_SMSTL
	printf ("%s - %s\r\n", "TSmf::Read", FileName);
#endif

	const char* default_dir = FileAnswer::GetDefaultDirName();

  if (default_dir)
  {
	  strcpy (FullFileName, default_dir);
  }
  else
  {
    FullFileName [0] = 0;
  }

	strcat (FullFileName, FileName);

	
  if(fIsOpen)
		{

#ifdef DEBUG_SMSTL	
			printf ("SMSTLClose\r\n");
#endif

    Close();
		}

  InFile = fopen (FullFileName, "r+b");


#ifdef DEBUG_SMSTL	
	struct stat statbuf;
	fstat(fileno(InFile), &statbuf);
	
	printf ("FileSize %u\r\n", statbuf.st_size);

	printf ("%s - %s\r\n", "TSmf::Open", FullFileName);
#endif
  
  if(!InFile)
		{
#ifdef DEBUG_SMSTL
		printf ("%s - %s\r\n", "Unable to open ", FullFileName);
#endif
    return false;
		}

  //read the events in  file
  unsigned NumBytesRead;
  
  
  bool ValidFile = ReadSMFHeader(InFile, &NumBytesRead, &wFormat, &wNumTracks, &wTickInterval);
  if(ValidFile)
    {
#ifdef DEBUG_SMSTL	
			printf ("Valid File\r\n");
#endif
      dwMaxTime = 0;
      dwNumEvents = 0;
      for(unsigned i = 0; i < wNumTracks; i++)
        {
          TTrackStruct* NewTrack = new TTrackStruct;
          aTracks.push_back(NewTrack);
          aTracks[i]->LoadTrack(InFile);
          dwNumEvents += aTracks[i]->NumEvents();
          if(aTracks[i]->MaxTime() > dwMaxTime)
            dwMaxTime = aTracks[i]->MaxTime();
        }
    }
  
  fclose (InFile);
  dwCurrentTime = 0;
  fIsOpen = ValidFile;
#ifdef DEBUG_SMSTL	
	if (ValidFile)
		{
			printf ("Success\r\n");
		}
	else
		{
			printf ("Fail\r\n");
		}
#endif
  return ValidFile;
  
}

void TSmf::Close()
{
  //delete the buffers
  for(unsigned i = 0; i < aTracks.size(); i++)
    {
      TTrackStruct* pTrack = aTracks[i];
      delete pTrack;
    }
  aTracks.erase(aTracks.begin(), aTracks.end());
  fIsOpen = false;
}
void TSmf::SetTime(DWORD NewTime)
{
  //set time for each track
  for(unsigned i = 0; i < aTracks.size(); i++)
    aTracks[i]->SetTime(NewTime);
  
  dwCurrentTime = NewTime;
  
}

bool TSmf::GetEvent(SMFEvent** ppEvent, DWORD* pdwDeltaTime, unsigned* pTrack)//with time from last event
{
  SMFEvent* pNextEvent;
  bool ValidTrack = false;
  if(fInSysex)
    {
      *pdwDeltaTime = 0;
      bool ValidEvent = aTracks[wCurrentTrack]->GetEvent(&pNextEvent);
      if(ValidEvent)
        {
          BYTE LastByte = pNextEvent->GetData()[pNextEvent->dwLength-1];
          fInSysex = (LastByte == 0xF7);
          *pTrack = wCurrentTrack;
          return ValidEvent;
        }
      else
        fInSysex = false;
    }
  //iterate through the tracks and find the lowest value
  DWORD dwLowestTime;
  wCurrentTrack = 0;
  unsigned wLowestTrack = 0;
  //find first valid event
  while(!ValidTrack && wCurrentTrack < aTracks.size())
    {
      dwLowestTime = aTracks[wCurrentTrack]->GetTime();
      bool EndOfTrack = aTracks[wCurrentTrack]->EndOfTrack();
      bool Mute = aTracks[wCurrentTrack]->Mute();
      ValidTrack = !Mute && ! EndOfTrack;
      //ValidTrack = aTracks[wCurrentTrack]->GetEvent(&pNextEvent);
      wLowestTrack = wCurrentTrack++;
    }
  for(unsigned i = wCurrentTrack; ValidTrack && i < aTracks.size(); i++)
    {
      if(aTracks[i]->GetTime() < dwLowestTime)
        {
          bool EndOfTrack = aTracks[i]->EndOfTrack();
          bool Mute = aTracks[i]->Mute();
          bool ValidEvent = !EndOfTrack && !Mute;
          if(ValidEvent)
            {
              wCurrentTrack = i;
              dwLowestTime = aTracks[i]->GetTime();
              wLowestTrack = i;
            }
        }
    }
  if(!ValidTrack)
    {
      *ppEvent = NULL;
      return false;
    }

  bool ValidEvent = aTracks[wLowestTrack]->GetEvent(&pNextEvent);

  *pTrack = wLowestTrack;
  *pdwDeltaTime = dwLowestTime - dwCurrentTime;
  dwCurrentTime = dwLowestTime;
  *ppEvent = pNextEvent;
  return ValidEvent;
}


void Load_hsmf_Chunk(FILE* hFile, byte_vec* Buff, unsigned* pNumBytesRead)
{
  BYTE c;
  unsigned fPtr = 0;
  unsigned long ChunkLength; //read from chunk header
	bool failed = false;

  for(unsigned i = 0; i < CHUNK_ID_SIZE && !failed; i++ )
    {
			unsigned bytes_read = fread (&c, 1, 1, hFile);
			failed = failed || (bytes_read != 1);

      Buff->push_back(c); //and put it in the buffer
			if (failed)
				{
					printf ("Load_hsmf_Chunk Fail ReadingChunk byte %u of %u\r\n", i, CHUNK_ID_SIZE);
				}
#ifdef DEBUG_SMSTL	
			printf ("Chunk ID Byte %u -%c \r\n", i, c);
#endif
      fPtr++;
    }

#ifdef DEBUG_SMSTL	
			printf ("Read Chunk Length %u\r\n", CHUNK_LENGTH_SIZE);
#endif

  //read chunk length
  for(unsigned i = 0; i < CHUNK_LENGTH_SIZE && !failed; i++)
    {
			unsigned bytes_read = fread (&c, 1, 1, hFile);
			failed = failed || (bytes_read != 1);

      Buff->push_back(c); //and put it in the buffer

			if (failed)
				{
					printf ("Load_hsmf_Chunk Fail ReadingChunk Length %u of %u\r\n", i, CHUNK_LENGTH_SIZE);
				}

    }

  unsigned char C0, C1, C2, C3;
  C0 =  (*Buff)[fPtr];
  C1 =  (*Buff)[fPtr + 1];
  C2 =  (*Buff)[fPtr + 2];
  C3 =  (*Buff)[fPtr + 3];
  ChunkLength = C0 * 0x01000000L + C1* 0x010000L + C2 * 0x0100 + C3;

#ifdef DEBUG_SMSTL	
			printf ("Chunk Length read %u\r\n", ChunkLength);
#endif
  
  fPtr +=  CHUNK_LENGTH_SIZE;//now increment pointer
  
  //now read the number of bytes into the buffer
  for(unsigned long i = 0; i < ChunkLength && !failed; i++)
    {
			unsigned bytes_read = fread (&c, 1, 1, hFile); 
			failed = failed || (bytes_read != 1);

      Buff->push_back(c); //and put it in the buffer

			if (failed)
				{
					printf ("Load_hsmf_Chunk Fail ReadingChunk Data %u of %u\r\n", i, ChunkLength);
				}

      fPtr++;
    }
  
  *pNumBytesRead = fPtr;

#ifdef DEBUG_SMSTL	
			printf ("TotalBytes read %u\r\n", *pNumBytesRead);
#endif

}

bool ReadSMFHeader(FILE* hFile,  unsigned* pNumBytesRead, unsigned * wFormat, unsigned* wNumTracks, unsigned* wTime)
{
  byte_vec HeaderData;
  Load_hsmf_Chunk(hFile, &HeaderData, pNumBytesRead);
  
  //see if valid
  if(!HeaderData[0] == 'M' || !HeaderData[1] == 'T' || !HeaderData[2] == 'h' || !HeaderData[3] == 'd')
    return false; //this is not a midi file
  
  *wFormat = (unsigned ) (HeaderData[8] * 0x0100 + HeaderData[9]);
  //read how many tracks there are
  *wNumTracks =  (HeaderData[10] * 0x0100 + HeaderData[11]);
  *wTime = (unsigned)((HeaderData[12] <<8) + HeaderData[13]);
  return true;
}


TTrackStruct::~TTrackStruct()
{
  for(unsigned i = 0; i < pEvents.size(); i++)
    {
      SMFEvent* pEvent = pEvents[i];
      delete pEvent;
    }
}


bool TTrackStruct::LoadTrack(FILE* Infile)
{
  unsigned NumBytesRead;
  
  Load_hsmf_Chunk(Infile, &cData, &NumBytesRead);
  LoadEvents();
  if(pEvents.size())
    dwCurrentTime = pEvents[0]->Time();
  wSize = pEvents.size(); //this will make comparisons faster
  return true;
}


void TTrackStruct::LoadEvents()
{
  //convert the data in the cData Buffer to SMFEvents
  unsigned wCursor = CHUNK_ID_SIZE + CHUNK_LENGTH_SIZE;//this is after the track header data
  BYTE RunningStatus = 0;
  unsigned wSize = cData.size();
  while(wCursor < wSize)
    {
      //read the delta time
      unsigned BytesRead; //we will return this from reading variable length
      SMFEvent* pEvent = new SMFEvent(&cData[wCursor], &BytesRead, &RunningStatus);
      pEvents.push_back(pEvent);
      dwMaxTime += pEvent->Time();
      wCursor+= BytesRead; //increment cursor
    }
}

bool TTrackStruct::GetEvent(SMFEvent** ppEvent)
{
  //make sure not muted or cursor above the number of events
  if(fMute || (dwEventCursor >= NumEvents()))
    return false;
  
  //get the event
  *ppEvent = pEvents[dwEventCursor];
  //adjust the cursor
  dwEventCursor++;
  //adjust the time
  if(!EndOfTrack())
    dwCurrentTime += pEvents[dwEventCursor]->Time();
  return true;
}

void TTrackStruct::SetTime(DWORD dwNewTime)
{
  if(!pEvents.size())
    return;
  //start from beginning
  dwCurrentTime = pEvents[0]->Time();
  dwEventCursor = 0;
  
  if(dwNewTime > dwCurrentTime) //go up
    {
      bool end = NumEvents() <= dwEventCursor;
      while (!end && dwNewTime > dwCurrentTime)
        {
          SMFEvent* NextEvent = pEvents[dwEventCursor];
          dwEventCursor++;
          dwCurrentTime += NextEvent->Time();
          end = NumEvents() <= dwEventCursor;
        }
    }
}
//--------------------------------------------------------------------------
SMFEvent::SMFEvent(BYTE* pEventStart, unsigned* pNumBytesRead, BYTE *pRunningStatus):pData(NULL)
{
  unsigned wCursor = 0;
  //read events from start event and return number of bytes
  dwDeltaTime = ReadVarLen(pEventStart, &wCursor);
  //get the type of data structure it is
  BYTE MessageType = pEventStart[wCursor];
  if(!(MessageType & 0x80)) //must be running status
    MessageType = *pRunningStatus;
  else
    {
      *pRunningStatus = MessageType; //return the running status
      wCursor++;                     //increment cursor
    }
  
  
  switch (MessageType) {
    //sysex
  case 0xF0: ProcessSysex(&pEventStart[wCursor], pNumBytesRead);
    break;
    //sysex continuation
  case 0xF7: ProcessSysex(&pEventStart[wCursor], pNumBytesRead, true);
    break;
    //meta
  case 0xFF: ProcessMeta(&pEventStart[wCursor], pNumBytesRead);
    break;
    //must be midi
  default:       ProcessMidi(MessageType, &pEventStart[wCursor], pNumBytesRead);
    break;
  };
  
  *pNumBytesRead += wCursor;
}

SMFEvent::~SMFEvent()
{  if(pData)
  delete[] pData;
}

void SMFEvent::ProcessSysex(BYTE* pEventStart, unsigned* pNumBytesRead, bool Continue)
{
  unsigned wCursor = 0;
  //get the length of the message
  DWORD dwSysexLen = ReadVarLen(pEventStart, &wCursor);
  
  //create a buffer for the message
  pData = new BYTE[dwSysexLen +1]; //we need extra for status
  
  //store status
  if(Continue)
    pData[0] = 0xF7;
  else
    pData[0] = 0xF0;
  
  //store data
  for(DWORD i = 0; i < dwSysexLen; i++)
    {
      pData[i+1] = pEventStart[wCursor];
      wCursor++;
    }
  *pNumBytesRead = wCursor;
  evType = etSysex;
  
}

void SMFEvent::ProcessMeta(BYTE* pEventStart, unsigned* pNumBytesRead)
{
  unsigned wCursor = 0;
  unsigned MetaType = pEventStart[wCursor];
  wCursor++;
  
  switch(MetaType) 
    {
      //sequence Number //just read the valuse for now
    case 0x00: //see how many more bytes
      {
        BYTE NumChar = pEventStart[wCursor];
        wCursor++;
        if(NumChar == 0x02) //read the next two
          {
            pData = new BYTE[NumChar];
            pData[0] = 0x02;
            pData[1] = pEventStart[wCursor];
            wCursor++;
            pData[2] = pEventStart[wCursor];
            wCursor++;
            dwLength = 3;
          }
        else
          {
            pData = new BYTE[1];
            pData[0] = 0;
            dwLength = 1;
          }
      }
      evType = etSequenceNumber;
      break;
      
      //text
    case 0x01:
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x06:
    case 0x07:
    case 0x7F:
      
      {
        unsigned NumBytesRead;
        DWORD TextLen = ReadVarLen(&pEventStart[wCursor], &NumBytesRead);
        wCursor += NumBytesRead;
        
        //create buffer for text
        pData = new BYTE[TextLen + 1];
        for(DWORD i = 0; i < TextLen; i++)
          {
            pData[i] = pEventStart[wCursor];
            wCursor++;
          }
        pData[TextLen] = 0; //this will make reading the text easy
        dwLength = TextLen;
        //stor the type
        if(MetaType == 0x7F)
          evType = etProprietry;
        else
          evType = (EventType)MetaType;
      }
      break;
      //midi channel
    case 0x20:
      pData = new BYTE[2];
      pData[0] = pEventStart[wCursor];
      wCursor++;
      pData[1] = pEventStart[wCursor];
      wCursor++;
      evType = etMidiChannel;
      break;
      //midi port
    case 0x21:
      {
        BYTE NumBytes = pEventStart[wCursor];
        wCursor++;
        pData = new BYTE[NumBytes];
        pData[0] = pEventStart[wCursor];
        wCursor++;
        dwLength = NumBytes;
        evType = etMidiPort;
      }
      break;
      //end of track
    case 0x2F:
      {
        BYTE NumBytes = pEventStart[wCursor];
        wCursor++;
        pData = new BYTE[NumBytes];
        pData[0] = 0x2F;
        dwLength = NumBytes;
        evType = etEndOfTrack;
      }
      break;
      //tempo
    case 0x51:
      {
        BYTE NumBytes = pEventStart[wCursor];
        wCursor++;
        pData = new BYTE[NumBytes];
        for(BYTE i = 0; i < NumBytes; i++)
          {
            pData[i] = pEventStart[wCursor];
            wCursor++;
          }
        dwLength = NumBytes;
        evType = etTempo;
      }
      break;
    case 0x59:
      {
        BYTE NumBytes = pEventStart[wCursor];
        wCursor++;
        pData = new BYTE[NumBytes];
        for(BYTE i = 0; i < NumBytes; i++)
          {
            pData[i] = pEventStart[wCursor];
            wCursor++;
          }
        dwLength = NumBytes;
        evType = etKeySig;
      }
      break;
      
      //smpte offsett
    case 0x54:
    case 0x58:
      {
        BYTE NumBytes = pEventStart[wCursor];
        wCursor++;
        pData = new BYTE[NumBytes];
        for(BYTE i = 0; i < NumBytes; i++)
          {
            pData[i] = pEventStart[wCursor];
            wCursor++;
          }
        dwLength = NumBytes;
        if(MetaType == 0x54)
          evType = etSMPTE;
        else
          evType = etTimeSig;
      }
      break;
    default:
      {
        BYTE NumBytes = pEventStart[wCursor];
        wCursor++;
        pData = new BYTE[NumBytes];
        for(BYTE i = 0; i < NumBytes; i++)
          {
            pData[i] = pEventStart[wCursor];
            wCursor++;
          }
        dwLength = NumBytes;
        evType = etUnknownMeta;
      }
      
      
    };    //end case
  *pNumBytesRead = wCursor;
}

void SMFEvent::ProcessMidi(BYTE Status, BYTE* pEventData, unsigned* pNumBytesRead)
{
  unsigned wCursor = 0;
  BYTE NumBytesToRead = (BYTE)GetMsgLength(Status);
  pData = new BYTE [NumBytesToRead + 1];
  pData[0] = Status;
  for(BYTE i = 0; i < NumBytesToRead; i++)
    {
      pData[i+1] = pEventData[wCursor];
      wCursor++;
    }
  
  dwLength = NumBytesToRead +1;
  evType = etMidiEvent;
  *pNumBytesRead = wCursor;
}



