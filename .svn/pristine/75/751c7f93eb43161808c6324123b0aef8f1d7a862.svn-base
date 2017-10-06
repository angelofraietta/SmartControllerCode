
#ifndef MIDICONTROLLER_LIBRARY
#define MIDICONTROLLER_LIBRARY

#include "configmsg.h"


void  InitialisePatchEditor ();
void   DeInitialisePatchEditor();



bool   ConfigChanged();
void   SetReferenceData();
bool   LoadConfig (const char* filename);
bool   SaveConfig (const char* filename);

bool   WriteConfigChannelData (const STR_CONFIG &config_msg);
bool   SendFactoryDefault();
bool   SendMidiData(const MidiData& data);
bool   GetMidiData(MidiData* data);
unsigned GetBytesWritten();
bool   SendReadConfig();
bool   CancelWrite();
void   SendConfig();
bool   SetOutputDevice(unsigned dev_num);
bool   SetIntputDevice(unsigned dev_num);
unsigned GetNumMidiInDevices();
unsigned GetNumMidiOutDevices();
bool GetMidiInputName (unsigned device_index, char* ret_buf, unsigned buf_len);
bool GetMidiOutputName (unsigned device_index, char* ret_buf, unsigned buf_len);


#endif
