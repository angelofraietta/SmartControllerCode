//## begin module%3ACAA73401AD.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ACAA73401AD.cm

//## begin module%3ACAA73401AD.cp preserve=no
//	Angelo Fraietta
//## end module%3ACAA73401AD.cp

//## Module: SimulatorInterface%3ACAA73401AD; Package specification
//## Subsystem: hal_include%3A80CC250114
//## Source file: c:\develop\SmartController\controller\source\hal_include\simulatorinterface.h

#ifndef simulatorinterface_h
#define simulatorinterface_h 1

//## begin module%3ACAA73401AD.additionalIncludes preserve=no
//## end module%3ACAA73401AD.additionalIncludes

//## begin module%3ACAA73401AD.includes preserve=yes
//## end module%3ACAA73401AD.includes

//## begin module%3ACAA73401AD.declarations preserve=no
//## end module%3ACAA73401AD.declarations

//## begin module%3ACAA73401AD.additionalDeclarations preserve=yes

#ifdef __cplusplus
extern "C" {            // Assume C declarations for C++
#endif

	bool SimulatorGetAnswer (const unsigned char* question, unsigned char* ret_answer);
	void DeleteAllPatches();
	bool OpenMidiOutputDevice (unsigned device_num, unsigned device_index);
	void CloseMidiOutputDevices ();
	void SetDefaultDirectory (const char* dir_name);
  bool GetDefaultDirectory (char* buf, unsigned buf_size);
	bool SimulatorInitialise();
	bool SimulatorDeinitialise();
	bool OpenMidiInputDevice (unsigned device_num, unsigned device_index);
	void CloseMidiInputDevices ();

  unsigned long OpenSysexSendFile (const char* sysex_filename);
  bool TransmitSysexData (unsigned long file_key, unsigned device_index, unsigned num_bytes);
  bool CloseSysexData (unsigned long file_key);

  unsigned GetNumMidiInDevices();
  unsigned GetNumMidiOutDevices();
  bool GetMidiInputName (unsigned device_index, char* ret_buf, unsigned buf_len);
  bool GetMidiOutputName (unsigned device_index, char* ret_buf, unsigned buf_len);  
  unsigned long GetSchedulerTime();

  void  AddAnalogueValue (unsigned channel, unsigned value);
  void  AddDigitalValue(unsigned channel, unsigned value);
  unsigned GetAnalogueValue (unsigned channel);
  bool GetDigitalValue(unsigned channel);
#ifdef __cplusplus
} // endextern "C" {            // Assume C declarations for C++
#endif
//## end module%3ACAA73401AD.additionalDeclarations


//## begin module%3ACAA73401AD.epilog preserve=yes
//## end module%3ACAA73401AD.epilog


#endif
