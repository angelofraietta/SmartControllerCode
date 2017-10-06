#ifndef STDMIDIIN_H
#define STDMIDIIN_H

class StdMidiIn;


class StdMidiIn :public BaseShell
{
  friend class TypeList;
 public:
  enum{NoteOff = 8, NoteOn,PolyphonicPressure,
	 ControlChange,ProgramChange,ChannelPressure,PitchBend};
  
  enum {eDevice, eMaxAttribute};
	enum {eFilter, eNoteOnZeroFilter, eResetDevice, eStatus, eChannel, eData1, eData2, eMaxResetAttribute};

  StdMidiIn(Patch* = NULL, const char* Name = "",
	    const char* Comment = "", UINT8 Status = NoteOn,
	    UINT8 Channel = 0, UINT8 device = 0, bool Filtered = false,
	    INT16 Data1Filter = -1, INT16 Data2Filter = -1, bool NoteOnZeroFilter = false); //
  ~StdMidiIn();
  
  static void ProcessMidi(unsigned wDevice, MidiData *lpEvent);
  void OutputMidi(MidiData *lpEvent);
  static BaseShell* Create(Patch*);

  
  const char* GetType()const {return szType;}
  const char* GetOutletName(unsigned)const;
  
  
  void Reset(){wDevice = wResetDevice;}
  
  //these are filters
  int GetStatus()const;
  int GetChannel()const;
  int GetData1()const {return iData1;}
  int GetData2()const {return iData2;}
  int GetNoteOnZeroFilter()const {return fNoteOnZeroFiltered?1:0;}
  void SetStatus(int);
  void SetChannel(int);
  void SetData1(int);
  void SetData2(int);
  void SetNoteOnZeroFilter(int f) {fNoteOnZeroFiltered = (f); SetModified(true);}
  void SetDevice(int i) {wDevice = (UINT8)i;}
  int GetDevice()const {return wDevice;}
  void SetResetDevice(int i) {wDevice = (UINT8)i;}
  int GetResetDevice()const {return wDevice;}
  int GetFiltered()const {return IsFiltered?1:0;}
  void SetFiltered(int ApplyFilter) {IsFiltered = (ApplyFilter);}
	const BaseShell* GetReference() const;

 private:
  UINT8 wDevice, wResetDevice; //the device number in setup
  bool IsFiltered:1;
  bool fNoteOnZeroFiltered:1;  
  static const char*const szType;
  
  //define the filters
  UINT8 cStatus, cMidiChannel;
  INT16 iData1, iData2;
  
  static const char*const szaOutletDetails[];
  
  //list of all MidiIn objects
  static StdMidiIn** ObjectsList;
  static unsigned ListSize;
  static void AddObject(StdMidiIn*);

  
  // access functions
	static const unsigned NumAccess;
	typedef bool (StdMidiIn::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (StdMidiIn::*pSetFunc)(const char* new_value);
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
  bool Filtered (char* ret, unsigned ret_size) const;
  bool FilterNoteOnVelocityZero (char* ret, unsigned ret_size) const;
  bool ResetDevice  (char* ret, unsigned ret_size) const;
   
  bool Status (const char* new_val);
  bool Channel (const char* new_val);
  bool Data1 (const char* new_val);
  bool Data2 (const char* new_val);
  bool Device (const char* new_val);
  bool Filtered (const char* new_val);
  bool FilterNoteOnVelocityZero (const char* new_val);
  bool ResetDevice (const char* new_val);
   
};


#endif





