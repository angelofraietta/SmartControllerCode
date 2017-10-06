#ifndef STDMIDIOUT_H
#define STDMIDIOUT_H

#ifdef _ROSE_ANALYSE
#include "midi.h"
#endif


class StdMidiOut: public BaseShell
{
  friend class TypeList;
 public:
  enum{NoteOff = 8, NoteOn,PolyphonicPressure,
	 ControlChange,ProgramChange,ChannelPressure,PitchBend};
  
  enum {eStatus, eChannel, eData1, eData2, eDevice, eMaxAttribute};
	enum {	eResetStatus, eResetChannel, eResetData1, eResetData2, eResetDevice, eMono, eNoteInletTrigger, eNoteOffOut, eMaxResetAttribute};

  StdMidiOut(Patch* = NULL, const char* Name = "",
	     const char* Comment = "",
	     int Status = NoteOn, int Channel = 1,
	     int Data1 = 60, int Data2 = 60, UINT8 device = 0,
	     bool Mono = false, bool VelocityTrigger = false, bool NoteOffOut = false); //
  ~StdMidiOut();
  
  static BaseShell* Create(Patch*);

  void IntInlet(unsigned , int);
  void VoidInlet(unsigned);
  const char* GetType()const {return szType;}
  const char* GetInletName(unsigned)const;
  void Reset();
	void DoDefaultAction(){Send();}
  
  int GetStatus()const;
  int GetResetStatus()const;
  int GetChannel()const;
  int GetResetChannel()const;
  int GetData1()const;
  int GetResetData1()const;
  int GetData2()const;
  int GetResetData2()const;
  
  void SetStatus(int);
  void SetResetStatus(int);
  void SetChannel(int);
  void SetResetChannel(int);
  void SetData1(int);
  void SetResetData1(int);
  void SetData2(int);
  void SetResetData2(int);
  void SetDevice(int i) {wDevice = (UINT8)i;}
  int GetDevice()const {return wDevice;}
  void SetResetDevice(int i) {wResetDevice = (UINT8)i;}
  int GetResetDevice()const {return wResetDevice;}
  int GetMono()const {return fMono?1:0;}
  void SetMono(int f){fMono = f;}
  void SetData1Trigger(int f);
  int GetData1Trigger()const{return fNoteInletTrigger?1:0;}
  int GetNoteOff()const {return fNoteOff?1:0;}
  void SetNoteOff(int f){fNoteOff = (f);}
  void Send();
  void KillNote();
  void ResetDevice();

  static unsigned NumDevices();

	const BaseShell* GetReference() const;
 private:

  bool fMono :1, fNoteOff:1; //allows the previous Note to Be killed
  bool fNoteInletTrigger:1; //allows a note to trigger from Data2 input
  UINT8 wDevice:4, wResetDevice:4; //the device number in setup
  static const char*const szType;
  MidiData PreviousNote;

  BYTE cStatus:4, cMidiChannel:4, cData1, cData2; // performance values
  BYTE rcStatus:4, rcMidiChannel:4, rcData1, rcData2; // reset values

  void StatusInlet(int);
  void ChannelInlet(int);
  void Data1Inlet(int);
  void Data2Inlet(int);

  //Inlet function table
  typedef void(StdMidiOut::*pVoidFunc)();
  static const pVoidFunc tpVoidFunc[];

  typedef void(StdMidiOut::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];
  // arrays to get names of inlets and outlets
  static const char*const szaInletDetails[];
  
  // access functions
	static const unsigned NumAccess;
	typedef bool (StdMidiOut::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (StdMidiOut::*pSetFunc)(const char* new_value);
	typedef struct
	{
		const char* access_name;
		pGetFunc get_func;
		pSetFunc set_func;
	} str_access;

  static const str_access aAccess[];

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

  bool Status (char* ret, unsigned ret_size) const;
  bool Channel (char* ret, unsigned ret_size) const;
  bool Data1 (char* ret, unsigned ret_size) const;
  bool Data2 (char* ret, unsigned ret_size) const;
  bool Device (char* ret, unsigned ret_size) const;
  bool NoteInletTrigger (char* ret, unsigned ret_size) const;
  bool Mono (char* ret, unsigned ret_size) const;
  bool NoteOffOut (char* ret, unsigned ret_size) const;
  bool ResetStatus (char* ret, unsigned ret_size) const;
  bool ResetChannel (char* ret, unsigned ret_size) const;
  bool ResetData1 (char* ret, unsigned ret_size) const;
  bool ResetData2 (char* ret, unsigned ret_size) const;
  bool ResetDevice  (char* ret, unsigned ret_size) const;


  bool Status (const char* new_val);
  bool Channel (const char* new_val);
  bool Data1 (const char* new_val);
  bool Data2 (const char* new_val);
  bool Device (const char* new_val);
  bool NoteInletTrigger (const char* new_val);
  bool Mono (const char* new_val);
  bool NoteOffOut (const char* new_val);
  bool ResetStatus (const char* new_val);
  bool ResetChannel (const char* new_val);
  bool ResetData1 (const char* new_val);
  bool ResetData2 (const char* new_val);
  bool ResetDevice (const char* new_val);

};



#endif

