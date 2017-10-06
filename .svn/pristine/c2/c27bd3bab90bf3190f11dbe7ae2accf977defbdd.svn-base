#include "stdafx.h"

#include "control.h"
#include "sequencer.h"

#include "estring.h"
#include "typenames.h"
#include "funcdec.h"

#include "smfstl.h"

#define NUM_INLETS  3
#define NUM_OUTLETS  8
#define MAX_TEMPO 500

#define TRACK_OUTPUT 0
#define STATUS_OUTLET 1
#define CHANNEL_OUTLET 2
#define DATA1_OUTLET 3
#define DATA2_OUTLET  4
#define META_TYPE_OUTLET 5
#define META_VALUE 6
#define TEMPO_OUTLET 7


#define DEFAULT_RESOLUTION 240
//#define DEBUG_SEQUENCER

const char*const Sequencer::szType = SEQUENCER_TYPE;
const unsigned Sequencer::NumAccess = Sequencer::eMaxAttribute;
const unsigned Sequencer::NumResetAccess = Sequencer::eMaxResetAttribute;


// create the default
static Sequencer *reference = new Sequencer (NULL);

const BaseShell* Sequencer::GetReference() const
{
	return reference;
}


const Sequencer::pIntFunc  Sequencer::tpIntFunc [NUM_INLETS] = {
  &Sequencer::Play,
  NULL,
  &Sequencer::SetTempo
};

const Sequencer::pDoubleFunc  Sequencer::tpDoubleFunc [NUM_INLETS] = {
  NULL,
  NULL,
  &Sequencer::SetTempo
};

const Sequencer::pStringFunc  Sequencer::tpStringFunc [NUM_INLETS] = {
  &Sequencer::MessageControl,
  &Sequencer::SetFileName,
  NULL,
};


const char*const Sequencer::szaInletDetails[NUM_INLETS] = {
  "Message Control",
  "FileName",
  "Tempo"
};

const char*const Sequencer::szaOutletDetails[NUM_OUTLETS] = {
  "Track",
  "Status",
  "Channel",
  "Data1",
  "Data2",
  "Meta Type",
  "Meta Value",
  "Tempo"
};

const char* Sequencer::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}

const char* Sequencer::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}

Sequencer::Sequencer(Patch* Parent, const char* Name,
										 const char* Comment, const char* FileName, float Tempo,
										 bool Flush)
  :BaseShell(Parent, NUM_INLETS, NUM_OUTLETS,
						 Name, Comment),
  fIsWaiting(false),
  fIsPlaying(false),
  fFlushNotes(Flush),
  flResetTempo(Tempo),
  sResetMidiFileName(FileName),
  dwMaxTime(0),
  dwCurrentTime(0),   
  pCurrentEvent(NULL) 
{
  SequenceDevice = new TSmf;
  ResetNoteOnArray();
  Reset();
}

Sequencer::~Sequencer()
{
  StopPlaying = true;
  if(fFlushNotes)
    FlushNoteOn();
  
  Purge();
  Close();
  delete SequenceDevice;
}

void Sequencer::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    {
      (this->*tpIntFunc[InletNumber])(i);
    }
  
}

void Sequencer::DoubleInlet (unsigned InletNumber, double d)
{
  if ((InletNumber < GetNumInlets())&& (tpDoubleFunc[InletNumber]))
    {
      (this->*tpDoubleFunc[InletNumber])(d);
    }
  
  else
    {
      IntInlet (InletNumber,DoubleToInt(d));
    }
}

inline void Sequencer::StringInlet(unsigned InletNumber, const char* s)
{
  if ((InletNumber < GetNumInlets())&&(tpStringFunc[InletNumber]))
    (this->*tpStringFunc[InletNumber])(s);
}

void Sequencer::MessageControl(const char* s)
{
  if(!strcmp(s, "reset"))
    {
      Reset();
      return;
    }
  if(!strcmp(s, "open"))
    {
      Open();
      return;
    }
  if(!strcmp(s, "close"))
    {
      Close();
      return;
    }
  
  if(!strcmp(s, "start"))
    {
      Start();
      return;
    }
  if(!strcmp(s, "end"))
    {
      End();
      return;
    }
  
  if(!strcmp(s, "play"))
    {
      Play(true);
      return;
    }
  if(!strcmp(s, "stop"))
    {
      Play(false);
      return;
    }
  
}

BaseShell* Sequencer::Create(Patch* Parent)
{
  return new Sequencer(Parent);
}



void Sequencer::OutputTick()
{
  fIsWaiting = false; //there are no items waiting to return
  if(!StopPlaying)
    {
      Send();
      ContinuePlaying();
    }
}



void Sequencer::SetResetTempo(double d)
{
  if((!d) || d > MAX_TEMPO)
    {
      Error(eInvalidTempo, this, d);
      return;
    }
  if(d == (float)flResetTempo)
    return;
  flResetTempo = (float)d;
  SetModified(true);
}

bool Sequencer::Open()
{
  if(SequenceDevice->IsOpen())
    {
      StopPlaying = true;
      if(fFlushNotes)
				FlushNoteOn();
      
      Purge();
      SequenceDevice->Close();
    }
  
#ifdef DEBUG_SEQUENCER
	printf ("Read %s\r\n", sMidiFileName.c_str());
#endif
  if(SequenceDevice->Read(sMidiFileName.c_str()))
    {
      
      //         StartEvent = SequenceDevice->GetStartMerge();

#ifdef DEBUG_SEQUENCER
			printf ("GetMaxTime\r\n");
#endif

      pCurrentEvent = 0;

      dwMaxTime = SequenceDevice->MaxTime();
#ifdef DEBUG_SEQUENCER
			printf ("GetResolution\r\n");
#endif

      wResolution = SequenceDevice->GetResolution();
#ifdef DEBUG_SEQUENCER
			printf ("SetTempo\r\n");
#endif

      SetTempo(flTempo);
      fIsWaiting = false;
#ifdef DEBUG_SEQUENCER
			printf ("Save Openfilename %s\r\n", sMidiFileName.c_str());
#endif
      
      sOpenFileName =  sMidiFileName;
#ifdef DEBUG_SEQUENCER
			printf ("Success\r\n");
#endif

      return true;
    }
  else
    {
			printf ("Unable to Open %s", sMidiFileName.c_str());

      Error(eUnableToOpenSequence, this, sMidiFileName.c_str());
      return false;
    }
}

void Sequencer::SetFileName(const char* FileName)
{
  sMidiFileName = FileName;
}

void Sequencer::SetResetFileName(const char* FileName)
{
  sResetMidiFileName = FileName;
}

unsigned Sequencer::GetNumTracks()const
{
  return SequenceDevice->NumTracks();
}

bool Sequencer::IsOpen()
{
  return SequenceDevice->IsOpen();
}

void Sequencer::Reset()
{
  sMidiFileName = sResetMidiFileName;
  Close();
  SetTempo(flResetTempo);
}

void Sequencer::SetTempo(int NewTempo)
{
  SetTempo((double)NewTempo);
}

void Sequencer::SetTempo(double NewTempo)
{
  if ((!NewTempo) || NewTempo > MAX_TEMPO)
    Error(eInvalidTempo, this, NewTempo);
  else
    {
      flTempo = (float)NewTempo;
      dwTickDuration = (DWORD) (60000UL / NewTempo / wResolution);
      SetTickTempo((float)NewTempo); //add here
    }
}

void Sequencer::Play (int StartPlaying)
{
  dwCurrentTime = SequenceDevice->GetTime();
  if(!StartPlaying
     || !SequenceDevice->IsOpen()
     || dwCurrentTime > dwMaxTime)
    {
      StopPlaying = true;
      fIsPlaying = false;
      if(fFlushNotes)
				FlushNoteOn();
    }
  
  else
    {
      StopPlaying = false;
      if(!fIsPlaying)
				StartTiming();
      fIsPlaying = true;
    }
  //clean up
  ContinuePlaying();
}

void Sequencer::ContinuePlaying()
{
  if(fIsWaiting)
    return; //already waiting for an event
  
  //see if any more events left
  //get the time and track
  bool EndOfSequence = !(SequenceDevice->GetEvent(&pCurrentEvent, &dwDeltaTime, &wTrack));
  if(EndOfSequence)
    {
      StopPlaying = true;
      fIsPlaying = false;
      tpOutlet[TEMPO_OUTLET]->ProduceOutput();      
      return;
    }
  
  fIsWaiting = true;
  
  if(SequenceDevice->GetTime() == 0) //at start of track
    {
      dwLastEventTime = GetTime();
      StartTiming();
    }
  
  
  
  while(!EndOfSequence && dwDeltaTime == 0)
    {
      Send();
      EndOfSequence = !SequenceDevice->GetEvent(&pCurrentEvent, &dwDeltaTime, &wTrack );
    }
  
  if(!EndOfSequence)
    {
      //         wInterval = dwDeltaTime * dwTickDuration;
      //         dwLastEventTime += wInterval;
      GoTickOneshot(dwDeltaTime);
    }
  else
    {
      fIsWaiting = false;
      StopPlaying = true;
      fIsPlaying = false;
      tpOutlet[TEMPO_OUTLET]->ProduceOutput(); 
    }
  
  
  
}

void Sequencer::Send()
{
  if(!pCurrentEvent)
    return;
  
  //send the track
  tpOutlet[TRACK_OUTPUT]->ProduceOutput((int)wTrack);
  //read the type of message and act accordingly
  unsigned wEventType = pCurrentEvent->GetType();
  if( wEventType == (unsigned)SMFEvent::etMidiEvent)
    OutputMidi();
  else
    OutputMeta();
}

void Sequencer::Close()
{
  StopPlaying = true;
  pCurrentEvent = NULL;
  if(fFlushNotes)
    FlushNoteOn();
  
  Purge();
  SequenceDevice->Close();
  sOpenFileName = "";
}

void Sequencer::SetPosition(DWORD NewTime)
{
  if(NewTime < dwMaxTime)
    {
      dwCurrentTime = NewTime;
      SequenceDevice->SetTime(NewTime);
    }
  else
    End();
}

void Sequencer::GetFileName(char* buf, unsigned buf_len)const
{
  strncpy (buf, sMidiFileName.c_str(), buf_len - 1);
	buf[buf_len -1] = '\0';
}

void Sequencer::GetResetFileName(char* buf, unsigned buf_len)const
{
  strncpy (buf, sResetMidiFileName.c_str(), buf_len -1);
	buf[buf_len -1] = '\0';
}


void Sequencer::ResetNoteOnArray()
{
  for(unsigned i = 0; i < 16; i++)
    for(unsigned j = 0; j < 128; j++)
      ArrayNoteOn[i][j] = false;
}

void Sequencer::FlushNoteOn()
{
  for(unsigned wChan = 0; wChan < 16; wChan++)
    {
      for(unsigned wNote = 0; wNote < 128; wNote++)
				{
					if(ArrayNoteOn[wChan][wNote]) //the flag is set
						{
							tpOutlet[STATUS_OUTLET]->ProduceOutput(0x08);
							tpOutlet[CHANNEL_OUTLET]->ProduceOutput((int)wChan+1);
							tpOutlet[DATA1_OUTLET]->ProduceOutput((int)wNote);
							tpOutlet[DATA2_OUTLET]->ProduceOutput(0);
							ArrayNoteOn[wChan][wNote] = false; //reset flag
						}
				}
    }
}

void Sequencer::OutputMidi()
{
  unsigned NumBytes = pCurrentEvent->Length();
  BYTE iStatus  = (BYTE) (pCurrentEvent->GetData()[0] / 0x10);
  BYTE iChannel = (BYTE) (pCurrentEvent->GetData()[0] % 0x10);
  BYTE iData1 = pCurrentEvent->GetData()[1];
  BYTE iData2 = 0;
  if (NumBytes == 3)
    iData2 = pCurrentEvent->GetData()[2];
  
  tpOutlet[STATUS_OUTLET]->ProduceOutput(iStatus);
  tpOutlet[CHANNEL_OUTLET]->ProduceOutput(iChannel +1);
  
  switch(iStatus)
    {
    case NoteOn:
      ArrayNoteOn[iChannel][iData1] = (iData2); //set the flag with velocity
      tpOutlet[DATA1_OUTLET]->ProduceOutput(iData1);
      tpOutlet[DATA2_OUTLET]->ProduceOutput(iData2);
      break;
      
    case NoteOff:
      ArrayNoteOn[iChannel][iData1] = false; //clear the flag
      tpOutlet[DATA1_OUTLET]->ProduceOutput(iData1);
      tpOutlet[DATA2_OUTLET]->ProduceOutput(iData2);
      break;
      
    case ControlChange:
    case PolyphonicPressure:
    case PitchBend:
      tpOutlet[DATA1_OUTLET]->ProduceOutput(iData1);
      tpOutlet[DATA2_OUTLET]->ProduceOutput(iData2);
      break;
      
    case ProgramChange:
    case ChannelPressure:
      tpOutlet[DATA1_OUTLET]->ProduceOutput(iData1);
      break;
    default:
      break;
    };
  
}


void Sequencer::OutputMeta()
{
  //output the meta type
  unsigned EventType = pCurrentEvent->GetType();
  tpOutlet[META_TYPE_OUTLET ]->ProduceOutput((int)EventType);
  switch (EventType){
  case SMFEvent::etText:
  case SMFEvent::etCopyright:
  case SMFEvent::etTrackName:
  case SMFEvent::etInstrument:
  case SMFEvent::etLyric:
  case SMFEvent::etMarker:
  case SMFEvent::etCuePoint:
    tpOutlet[META_VALUE]->ProduceOutput((const char*)(pCurrentEvent->GetData()));
    break;
    
    
  case  SMFEvent::etEndOfTrack:
    tpOutlet[META_VALUE]->ProduceOutput();
    break;
  case SMFEvent::etTempo:
    OutputTempo();
    break;
  default:
    break;
    //, etProprietry, etKeySig,etSequenceNumber,
    //      etSysex, etSMPTE, etTimeSig, etUnknownMeta
    
  };
  
  
}

void Sequencer::OutputTempo()
{
  //convert dword usec per beat to bpm
  DWORD UsecPerBeat  = pCurrentEvent->GetData()[0] * 0x10000;
  UsecPerBeat  += pCurrentEvent->GetData()[1] * 0x100;
  UsecPerBeat  += pCurrentEvent->GetData()[2];
  
  double Tempo = 60000000L / UsecPerBeat;
  tpOutlet[TEMPO_OUTLET]->ProduceOutput(Tempo);
  
}

const Sequencer::str_access Sequencer::aAccess[NumAccess] =
{
  {"Play", &Sequencer::Play, &Sequencer::Play},
  {"Filename", &Sequencer::Filename, &Sequencer::Filename},
  {"Tempo", &Sequencer::Tempo, &Sequencer::Tempo},
  {"Flush", &Sequencer::Flush, &Sequencer::Flush},
};


const char* Sequencer::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool Sequencer::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool Sequencer::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}


const Sequencer::str_access Sequencer::aResetAccess[NumResetAccess] =
{
  {"ResetFilename", &Sequencer::ResetFilename, &Sequencer::ResetFilename},
  {"ResetTempo", &Sequencer::ResetTempo, &Sequencer::ResetTempo}
};


const char* Sequencer::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool Sequencer::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool Sequencer::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}

bool Sequencer::Play (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (IsPlaying()? 1: 0, ret, ret_size);
}

bool Sequencer::Filename (char* ret, unsigned ret_size) const
{
 return SMUtility::StrToStr (sMidiFileName.c_str(), ret, ret_size);
}

bool Sequencer::Tempo (char* ret, unsigned ret_size) const
{
 return SMUtility::FltToStr (flTempo, ret, ret_size);
}

bool Sequencer::Flush (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetFlush (), ret, ret_size);
}

bool Sequencer::ResetFilename (char* ret, unsigned ret_size) const
{
 return SMUtility::StrToStr (sResetMidiFileName.c_str(), ret, ret_size);
}

bool Sequencer::ResetTempo (char* ret, unsigned ret_size) const
{
 return SMUtility::FltToStr (flResetTempo, ret, ret_size);
}



bool Sequencer::Play (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			Play(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Sequencer::Filename (const char* new_val)
{
	SetFileName (new_val);
	return true;
}

bool Sequencer::Tempo (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			SetTempo(SMUtility::StrToFlt(new_val));
			ret = true;
		}
	return ret;
}

bool Sequencer::Flush (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetFlush (SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Sequencer::ResetFilename (const char* new_val)
{
	SetResetFileName (new_val);
	return true;
}

bool Sequencer::ResetTempo (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			SetResetTempo(SMUtility::StrToFlt(new_val));
			ret = true;
		}
	return ret;
}



