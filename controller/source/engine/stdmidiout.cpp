//StdMidiOut function defs
#include "stdafx.h"

#include "iodata.h"
#include "control.h"
#include "ostypes.h"
#include "midi.h"
#include "stdmidiout.h"
#include "typenames.h"
#include "midioutputdriver.h"

//#include "midioutput.h"

#define NUM_INLETS 5
#define NUM_OUTLETS 0

//using hal_include::MidiOutput;


unsigned StdMidiOut::NumDevices ()
{
  return  MidiOutputDriver::NumDevices();
}

  
const char*const StdMidiOut::szType = STDMIDIOUT_TYPE;
const unsigned StdMidiOut::NumAccess = StdMidiOut::eMaxAttribute;
const unsigned StdMidiOut::NumResetAccess = StdMidiOut::eMaxResetAttribute;


// create the default
static StdMidiOut *reference = new StdMidiOut(NULL);

const BaseShell* StdMidiOut::GetReference() const
{
	return reference;
}


const StdMidiOut::pIntFunc  StdMidiOut::tpIntFunc [NUM_INLETS] = {
  &StdMidiOut::StatusInlet,
  &StdMidiOut::ChannelInlet,
  &StdMidiOut::Data1Inlet,
  &StdMidiOut::Data2Inlet,
  &StdMidiOut::SetDevice
  
};

const StdMidiOut::pVoidFunc  StdMidiOut::tpVoidFunc [NUM_INLETS] = {
  &StdMidiOut::Send,
  NULL,
  NULL,
  NULL,
  NULL
  
};

const char*const StdMidiOut::szaInletDetails[NUM_INLETS] = {
  "Status",
  "MIDI Channel",
  "Data Byte 1",
  "Data Byte 2",
  "Midi Device"
};

const char* StdMidiOut::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}



StdMidiOut::StdMidiOut(Patch* Parent, const char* Name ,
											 const char* Comment, int Status, int Channel,
											 int Data1, int Data2, UINT8 DeviceId, bool Mono,
											 bool vTrigger, bool NoteOffOut)
  :BaseShell (Parent, NUM_INLETS,
							NUM_OUTLETS, Name, Comment),
  fMono(Mono),  
  fNoteOff(NoteOffOut),
  fNoteInletTrigger(vTrigger),
  wResetDevice(DeviceId),   
  rcStatus((UINT8)Status),
  rcMidiChannel((UINT8)Channel),
  rcData1((UINT8)Data1), 
  rcData2((UINT8)Data2)  
{
  PreviousNote.status = 0x80;
  PreviousNote.data1 = 0;
  PreviousNote.data2 = 127;
  Reset();
}

StdMidiOut::~StdMidiOut()
{
}

void StdMidiOut::VoidInlet(unsigned InletNumber)
{
  if ((InletNumber < GetNumInlets()) && (tpVoidFunc[InletNumber]))
    (this->*tpVoidFunc[InletNumber])();
}

void StdMidiOut::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}

void StdMidiOut::Reset()
{
  cStatus = rcStatus;
  cMidiChannel = rcMidiChannel;
  cData1 = rcData1;
  cData2= rcData2;
  wDevice = wResetDevice;
}

void StdMidiOut::Send()
{
  if (wDevice >= NumDevices ())
    {
      Error(eInvalidDevice, this, wDevice);
      return;
    }
  
  if(!cMidiChannel)
    {
      Error(eInvalidChannel, this, (int)cMidiChannel);
      return;
    }
  
  if (fMono && cStatus == NoteOn)
    {
      KillNote();//kill the previous
      //set previous channel
      PreviousNote.status = (BYTE)(cMidiChannel - 1);
      PreviousNote.data1 = cData1;
      if(fNoteOff) //SEND A NOTE OFF MESSAGE
				{
					PreviousNote.status = (BYTE) (0x80 + PreviousNote.status);
					PreviousNote.data2 = cData2;
				}
      else // send a note off velocity 0
				{
					PreviousNote.status = (BYTE) (0x90 + PreviousNote.status);
					PreviousNote.data2 = 0;
				}
    }
  
  MidiData Evt;
  Evt.status = (BYTE)(cStatus * 0x10 + ((UINT8)cMidiChannel - 1));
  Evt.data1 = cData1;
  Evt.data2 = cData2;
  //send data

  MidiOutputDriver::TransmitMidiDataMessage(Evt, wDevice);
}


BaseShell* StdMidiOut::Create(Patch* Parent)
{
  return new StdMidiOut(Parent);
}



int StdMidiOut::GetStatus()const
{
  return cStatus;
}

int StdMidiOut::GetResetStatus()const
{
  return rcStatus;
}
int StdMidiOut::GetChannel()const
{
  return cMidiChannel;
}

int StdMidiOut::GetResetChannel()const
{
  return rcMidiChannel;
}

int StdMidiOut::GetData1()const
{
  return cData1;
}

int StdMidiOut::GetResetData1()const
{
  return rcData1;
}

int StdMidiOut::GetData2()const
{
  return cData2;
}

int StdMidiOut::GetResetData2()const
{
  return rcData2;
}

void StdMidiOut::SetStatus(int NewStatus)
{
  if (NewStatus < 8 || NewStatus >15)
    {
      Error (eInvalidStatus, this, NewStatus);
      return;
    }
  cStatus = (UINT8)NewStatus;
}

void StdMidiOut::SetResetStatus(int NewStatus)
{
  if (NewStatus < 8 || NewStatus >15)
    {
      Error (eInvalidStatus, this, NewStatus);
      return;
    }
  
  if(rcStatus == (UINT8)NewStatus)
    return; //don't change it
  
  rcStatus = (UINT8)NewStatus;
  //set modified flag
  SetModified(true);
  
}
void StdMidiOut::SetChannel(int chan)
{
  if (chan < 0 || chan > 16)
    {
      Error (eInvalidChannel, this, chan);
      return ;
    }
  
  cMidiChannel = (UINT8)chan;
}

void StdMidiOut::SetResetChannel(int chan)
{
  if (chan < 0 || chan > 16)
		{
      Error (eInvalidChannel, this, chan);
      return;
		}
  
  if(rcMidiChannel == (UINT8)chan)
    return;
  
  rcMidiChannel = (UINT8)chan;
  //set modified flag
  SetModified(true);
}

void StdMidiOut::SetData1(int Data)
{
  if (Data > 127)
		{
			Error (eInvalidDataValue, this, Data);
			return;
		}
  
  cData1 = (UINT8) Data;
}

void StdMidiOut::SetResetData1(int Data)
{
  if (Data > 127)
		{
			Error (eInvalidDataValue, this, Data);
			return;
		}
  
  
  if(rcData1 == (UINT8) Data)
    return;
  
  rcData1 = (UINT8) Data;
  //set modified flag
  SetModified(true);
}

void StdMidiOut::SetData2(int Data)
{
  if (Data > 127)
    {
      Error (eInvalidDataValue, this, Data);
      return;
    }
  
  cData2 =  (UINT8)Data;
  
}

void StdMidiOut::SetResetData2(int Data)
{
  if (Data > 127)
		{
			Error (eInvalidDataValue, this, Data);    
			return;
		}
	
  if(rcData2 == (UINT8)Data)
    return;
  
  rcData2 = (UINT8)Data;
  //set modified flag
  SetModified(true);
  
}

void StdMidiOut::ResetDevice()
{
  //MidiOutput::resetDevice(wDevice);
}


void StdMidiOut::StatusInlet(int i)
{
  if (i >= NoteOff && i <= PitchBend)
    {
      SetStatus(i);
    }
	else
		{
			Error (eInvalidStatus, this, i);
		}
}

void StdMidiOut::ChannelInlet(int i)
{
  if ((UINT8)i <= 16)
    {
      SetChannel(i);
    }
  else
    {
      Error (eInvalidChannel, this, i);
    }
}

void StdMidiOut::Data1Inlet(int i)
{
  if((UINT8)i <= 127)
    {
      SetData1(i);
      switch(cStatus)
				{
				case ProgramChange:
				case ChannelPressure:
					Send();
					break;
				case NoteOn:
				case NoteOff:
					if(fNoteInletTrigger)
						Send();
					break;
				default:
					break;
				};
    }
  else
		{
			Error (eInvalidDataValue, this, i);
		}
}

void StdMidiOut::Data2Inlet(int i)
{
  if((UINT8)i <= 127)
    {
      SetData2(i);
      switch(cStatus)
				{
				case ControlChange:
				case PolyphonicPressure:
				case PitchBend:
					Send();
					break;
					
				case NoteOn:
				case NoteOff:
					if(!fNoteInletTrigger)
						Send();
					break;
				default:
					break;
				}; //end swithc
    }
  else
		{
			Error (eInvalidDataValue, this, i);
		}
}

void StdMidiOut::KillNote()
{
  if(wDevice >= NumDevices ())
    {
      Error(eInvalidDevice, this, wDevice);
      return;
    }

	MidiOutputDriver::TransmitMidiDataMessage(PreviousNote,wDevice);
}

void StdMidiOut::SetData1Trigger(int f)
{
  if (fNoteInletTrigger != f)
    {
      SetModified(true);
      fNoteInletTrigger = f;
    }
}

const StdMidiOut::str_access StdMidiOut::aAccess[NumAccess] =
{
  {"Status", &StdMidiOut::Status, &StdMidiOut::Status},
  {"Channel", &StdMidiOut::Channel, &StdMidiOut::Channel},
  {"Data1", &StdMidiOut::Data1, &StdMidiOut::Data1},
  {"Data2", &StdMidiOut::Data2, &StdMidiOut::Data2},
  {"Device", &StdMidiOut::Device, &StdMidiOut::Device}

};



const char* StdMidiOut::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool StdMidiOut::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool StdMidiOut::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}


const StdMidiOut::str_access StdMidiOut::aResetAccess[NumResetAccess] =
{
  {"ResetStatus", &StdMidiOut::ResetStatus, &StdMidiOut::ResetStatus},
  {"ResetChannel", &StdMidiOut::ResetChannel, &StdMidiOut::ResetChannel},
  {"ResetData1", &StdMidiOut::ResetData1, &StdMidiOut::ResetData1},
  {"ResetData2", &StdMidiOut::ResetData2, &StdMidiOut::ResetData2},
  {"ResetDevice", &StdMidiOut::ResetDevice, &StdMidiOut::ResetDevice},
  {"Mono", &StdMidiOut::Mono, &StdMidiOut::Mono},
  {"NoteInletTrigger", &StdMidiOut::NoteInletTrigger, &StdMidiOut::NoteInletTrigger},
  {"NoteOffOut", &StdMidiOut::NoteOffOut, &StdMidiOut::NoteOffOut}
  

};


const char* StdMidiOut::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool StdMidiOut::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool StdMidiOut::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool StdMidiOut::Status (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetStatus (), ret, ret_size);
}

bool StdMidiOut::Channel (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetChannel (), ret, ret_size);
}

bool StdMidiOut::Data1 (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetData1 (), ret, ret_size);
}

bool StdMidiOut::Data2 (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetData2 (), ret, ret_size);
}

bool StdMidiOut::Device (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetDevice (), ret, ret_size);
}

bool StdMidiOut::NoteInletTrigger (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetData1Trigger (), ret, ret_size);
}

bool StdMidiOut::Mono (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetMono (), ret, ret_size);
}

bool StdMidiOut::NoteOffOut (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetNoteOff (), ret, ret_size);
}

bool StdMidiOut::ResetStatus (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetStatus (), ret, ret_size);
}

bool StdMidiOut::ResetChannel (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetChannel (), ret, ret_size);
}

bool StdMidiOut::ResetData1 (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetData1 (), ret, ret_size);
}

bool StdMidiOut::ResetData2 (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetData2 (), ret, ret_size);
}

bool StdMidiOut::ResetDevice  (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetDevice (), ret, ret_size);
}


bool StdMidiOut::Status (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetStatus(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiOut::Channel (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetChannel(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiOut::Data1 (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetData1(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiOut::Data2 (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetData2(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiOut::Device (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetDevice(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiOut::NoteInletTrigger (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetData1Trigger(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiOut::Mono (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetMono(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiOut::NoteOffOut (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetNoteOff(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiOut::ResetStatus (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetStatus(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiOut::ResetChannel (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetChannel(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiOut::ResetData1 (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetData1(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiOut::ResetData2 (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetData2(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiOut::ResetDevice (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetDevice(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}
