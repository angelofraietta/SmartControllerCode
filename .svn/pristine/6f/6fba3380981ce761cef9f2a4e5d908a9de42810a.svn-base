#ifndef STL_SMF_H
#define STL_SMF_H
//------------------------------------------------------------------------
// Standard Midi File Module
//
// Copyright (c) Angelo Fraietta
//
//
//
// Provides functions to open, close, read and write Standard Midi Files
// of Format 0, 1, and 2.
//------------------------------------------------------------------------
#define _SMF_16
#include "estring.h"

#ifndef _ROSE_ANALYSE
#include <stdio.h>
#endif

#ifdef _E_STL
typedef sm_str::vector<BYTE> byte_vec;
#else
typedef std::vector<BYTE> byte_vec;

#endif


#define IN_SYSEX 0x0001			// true if currently reading a sysex

#define SEQUENCE_NUMBER_EVENT 0x0002
#define MIDI_CHANNEL_EVENT 0x2001
#define MIDI_PORT_EVENT 0x2101
#define END_OF_TRACK_EVENT 0x2F00
#define TEMPO_EVENT 0x5103
#define CHUNK_ID_SIZE 4
#define CHUNK_LENGTH_SIZE 4
class TSmf;
class TTrackStruct;


#ifndef _ROSE_ANALYSE
//using std::vector;
#endif

class SMFEvent{
  friend class TSmf;
  friend class TTrackStruct;
  
 public:
  enum EventType {etMidiEvent, etText, etCopyright, etTrackName, etInstrument,
		  etLyric, etMarker, etCuePoint, etMidiChannel, etMidiPort,
		  etEndOfTrack, etTempo, etProprietry, etKeySig,etSequenceNumber,
		  etSysex, etSMPTE, etTimeSig, etUnknownMeta};
  
  SMFEvent(BYTE* pEventStart, unsigned* pNumBytesRead, BYTE* pRunningStatus);//this is from the start of the delta time
  ~SMFEvent();
  
  const BYTE* GetData() {return pData;}//this is the data portion of the event
  DWORD Length()const {return dwLength;}
  unsigned GetType()const {return evType;}

 private:
  DWORD Time()const {return dwDeltaTime;}
  DWORD dwDeltaTime;   //of the event compared to last event in this track
  BYTE* pData;         //data of the event
  DWORD dwLength;      //length of data
  void ProcessSysex(BYTE* pEventStart, unsigned* pNumBytesRead, bool Continue = false);
  void ProcessMeta(BYTE* pEventStart, unsigned* pNumBytesRead);
  void ProcessMidi(BYTE Status, BYTE* pEventData, unsigned* pNumBytesRead);
  EventType evType;
};

//----------------------------------------------------------------------------
class TTrackStruct{
 public:
  TTrackStruct():fMute(false), dwEventCursor(0),dwMaxTime(0){}
  ~TTrackStruct();

  bool LoadTrack(FILE* Infile);
  bool WriteTrack(FILE* Outfile);

  //access to track data
  bool GetEvent(SMFEvent** ppEvent);
  unsigned NumEvents()const{return wSize;}
  DWORD GetTime()const {return dwCurrentTime;}
  DWORD MaxTime()const {return dwMaxTime;}; //return the time of last event in track
  void SetTime(DWORD CurrentTime); //set the pointer to this time or later

  //mute
  bool Mute()const {return fMute;}
  void Mute(bool f) {fMute = f;}
  bool EndOfTrack()const {return  !(dwEventCursor < NumEvents());}
 private:
  bool fMute;
  unsigned dwEventCursor; //current event
  unsigned wSize;//the number of events
  DWORD dwCurrentTime;   //absolute time of event at dwCursor;
  DWORD dwMaxTime;
  byte_vec cData;   //midi events
  sm_ptr::vector<SMFEvent*> pEvents;
  void LoadEvents();
};


//----------------------------------------------------------------------------
class TSmf {
 public:
  TSmf();
  ~TSmf();
  TSmf(const char* FileName); //reading
  bool Read(const char* FileName);
  void Close();
  bool Write(const char* FileName);
  bool IsOpen()const {return fIsOpen;}
  unsigned   NumTracks()const {return wNumTracks;}
  unsigned Format()const {return wFormat;}
  unsigned GetResolution()const {return wTickInterval;}
  DWORD GetTime()const {return dwCurrentTime;}
  void SetTime(DWORD NewTime);
  bool GetEvent(SMFEvent** ppEvent, DWORD* dwDeltaTime, unsigned* Track );//with time from last event
  DWORD NumEvents()const {return dwNumEvents;}
  DWORD MaxTime()const {return dwMaxTime;}; //return the maxt time of tracks
 private:
  bool fIsOpen;
  bool fInSysex;
  unsigned wNumTracks; //as read in the header
  unsigned wFormat;    //ditto
  unsigned wTickInterval;
  unsigned wCurrentTrack; //the track we are currently reading
  DWORD dwCurrentTime;    //the current time in ticks
  DWORD dwNumEvents;      //total number of events
  DWORD dwMaxTime;        //maximum time of all tracks
  sm_ptr::vector<TTrackStruct*> aTracks;  //array of tracks

};

bool ReadSMFHeader(FILE* hFile,  unsigned* pNumBytesRead, unsigned * wFormat, unsigned* wNumTracks, unsigned* wTime);
void Load_hsmf_Chunk(FILE* hFile, byte_vec* Buff, unsigned* pNumBytesRead);
void Load_hsmf_Chunk(FILE* hFile, byte_vec* Buff, unsigned* pNumBytesRead);


#endif



