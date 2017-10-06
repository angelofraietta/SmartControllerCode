#ifndef SEQUENCER_H
#define SEQUENCER_H

//Sequencer class
#include "timer.h"
#include "estring.h"


class TSmf; //forward dec
class SMFEvent;

class Sequencer: public BaseShell, TickCallback
{
  friend class TypeList;
 public:
  enum{NoteOff = 8, NoteOn,PolyphonicPressure,
	 ControlChange,ProgramChange,ChannelPressure,PitchBend};

  enum {ePlay, eFilename, eTempo, eFlush, eMaxAttribute};
	enum {eResetFilename, eResetTempo, eMaxResetAttribute};
 
  Sequencer(Patch* = NULL, const char* Name = "",
	    const char* Comment = "", const char* sFileName = "", float Tempo = 120,
	    bool Flush = true);

  ~Sequencer();

  void IntInlet(unsigned, int);
  void DoubleInlet (unsigned, double);
  void StringInlet(unsigned, const char*);
  
  static BaseShell* Create(Patch*);

  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  
  void Reset ();
  void SetTempo(int i);
  void SetTempo(double d);
  void SetResetTempo(double d);
  double GetTempo()const{return flTempo;}
  double GetResetTempo()const{return flResetTempo;}
  
  const char* GetType()const {return szType;}
  
  void GetFileName(char* buf, unsigned buf_len)const;
  void GetResetFileName(char* buf, unsigned buf_len)const;
  void SetFileName(const char*);
  void SetResetFileName(const char*);
  
  
  void Play(int StartPlaying);
	int GetPlaying ()const {return (fIsPlaying)?1:0;}
  void Send();
  bool Open();
  bool IsOpen();
  void Close();
  void Start() {dwCurrentTime = 0; SetPosition (0);}
  void End() {dwCurrentTime = dwMaxTime;}
  void Rewind(DWORD dwTime);
  void FastForward(DWORD dwTime);
  unsigned GetNumTracks()const;
  unsigned GetResolution()const {return wResolution;}
  void PurgeItem(DWORD){};
  bool IsPlaying()const {return fIsPlaying;}
  DWORD GetMaxTime()const {return dwMaxTime;}
  DWORD GetCurrentPos()const {return dwCurrentTime;}
  
  void SetPosition(DWORD NewPosition);
  void SetFlush(int f){fFlushNotes = (f);}
  int GetFlush()const {return fFlushNotes? 1:0;}
 	const BaseShell* GetReference() const;

 private:
  bool StopPlaying, fIsWaiting, fIsPlaying;
  bool fFlushNotes;//flush all notes after stopping
  bool ArrayNoteOn[16][128]; //flag for each note on
  float flTempo, flResetTempo;
  DWORD dwTickDuration; //in micor second per beat
  DWORD dwLastEventTime;
  TSmf* SequenceDevice;
  
  string sMidiFileName, sResetMidiFileName, sOpenFileName;
  DWORD dwMaxTime, dwCurrentTime;//the current sequence number
  
  //details for coming event
  SMFEvent* pCurrentEvent;
  DWORD dwDeltaTime; //Time from previous event
  unsigned wTrack;   //which track it belongs to
  void ResetNoteOnArray();
  void FlushNoteOn();
  void OutputMidi();
  void OutputMeta();
  void OutputTempo();
  void ContinuePlaying();
  void OutputTick();
  
  static const char*const szType;
  
  typedef void(Sequencer::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];
  
  typedef void(Sequencer::*pDoubleFunc)(double);
  static const pDoubleFunc tpDoubleFunc[];
  
  typedef void(Sequencer::*pStringFunc)(const char*);
  static const pStringFunc tpStringFunc[];
  
  // arrays to get names of inlets and outlets
  static  const char*const szaInletDetails[];
  static  const char*const szaOutletDetails[];
  
  void MessageControl(const char*);

  
  // access functions
	static const unsigned NumAccess;
	typedef bool (Sequencer::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (Sequencer::*pSetFunc)(const char* new_value);
	typedef struct
	{
		const char* access_name;
		pGetFunc get_func;
		pSetFunc set_func;
	} str_access;

  static const str_access aAccess[eMaxAttribute];

  unsigned GetNumAccess ()const {return NumAccess;}
  const char* GetAccessName (unsigned index)const;
  
  bool SetAttribute (unsigned index, const char* value);
  bool GetAttribute (unsigned index, char* ret_value, unsigned buf_size)const;

	static const unsigned NumResetAccess;
  static const str_access aResetAccess[];
  unsigned GetNumResetAccess ()const {return NumResetAccess;}
  const char* GetResetAccessName (unsigned index)const;

  bool SetResetAttribute (unsigned index, const char* value);
  bool GetResetAttribute (unsigned index, char* ret_value, unsigned buf_size) const;

  bool Play (char* ret, unsigned ret_size) const;
  bool Filename (char* ret, unsigned ret_size) const;
  bool Tempo (char* ret, unsigned ret_size) const;
  bool Flush (char* ret, unsigned ret_size) const;
  bool ResetFilename (char* ret, unsigned ret_size) const;
  bool ResetTempo (char* ret, unsigned ret_size) const;

  bool Play (const char* new_val);
  bool Filename (const char* new_val);
  bool Tempo (const char* new_val);
  bool Flush (const char* new_val);
  bool ResetFilename (const char* new_val);
  bool ResetTempo (const char* new_val);


};

#endif
