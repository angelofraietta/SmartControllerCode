//StdMidiIn function defs
#include "stdafx.h"

#include "iodata.h"
#include "control.h"
#include "stdmidiin.h"
#include "typenames.h"
#include "ostypes.h"

#define NUM_INLETS 0
#define NUM_OUTLETS 4

#define CHANNEL_OUTLET 1
#define STATUS_OUTLET 0
#define DATA2_OUTLET 3
#define DATA1_OUTLET 2
//static variables

StdMidiIn** StdMidiIn::ObjectsList = NULL;
unsigned StdMidiIn::ListSize = 0;

const unsigned StdMidiIn::NumAccess = StdMidiIn::eMaxAttribute;
const unsigned StdMidiIn::NumResetAccess = StdMidiIn::eMaxResetAttribute;


// create the default
static StdMidiIn *reference = new StdMidiIn (NULL);

const BaseShell* StdMidiIn::GetReference() const
{
	return reference;
}


void StdMidiIn::AddObject(StdMidiIn* NewObject)
{
  StdMidiIn** NewList = new StdMidiIn* [ListSize + 1];
  //copy list over
  for(unsigned i = 0; i < ListSize; i++)
    NewList[i] = ObjectsList[i];
  //add new one
  NewList[ListSize] = NewObject;
  ListSize++;
  delete[] ObjectsList;
  ObjectsList = NewList;
}

const char*const StdMidiIn::szType = STDMIDIIN_TYPE;

const char*const StdMidiIn::szaOutletDetails[NUM_OUTLETS] = {
  "Status",
  "Channel",
  "Data Byte 1",
  "Data Byte 2"
  
};

const char* StdMidiIn::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}



StdMidiIn::StdMidiIn(Patch* Parent, const char* Name ,
		     const char* Comment, UINT8 Status,
                     UINT8 Channel,UINT8 DeviceId,
                     bool Filtered, INT16 Data1Filter,
                     INT16 Data2Filter, bool NoteOnZeroFilter)
  :BaseShell (Parent, NUM_INLETS,
	      NUM_OUTLETS, Name, Comment),
  wResetDevice(DeviceId), 
  IsFiltered(Filtered),
  fNoteOnZeroFiltered(NoteOnZeroFilter),   
  cStatus(Status),
  cMidiChannel(Channel),
  
  iData1(Data1Filter),
  iData2(Data2Filter)
{
  AddObject(this);
  Reset();
}

StdMidiIn::~StdMidiIn()
{
  StdMidiIn** NewList = NULL;
  if(ListSize >1)
    NewList = new StdMidiIn*[ListSize -1];
  bool Found = false;
  unsigned i;
  for (i = 0; i < ListSize && !Found; i++)
    if(ObjectsList[i] == this)
      Found = true;
    else
      {   //copy element back
	NewList[i] = ObjectsList[i];
      }
  ListSize--;
  //now copy remaining elements
  for(unsigned j = i-1; j < ListSize; j++)
    NewList[j] = ObjectsList[j+1];

  delete[] ObjectsList;
  ObjectsList = NewList;


}




BaseShell* StdMidiIn::Create(Patch* Parent)
{
  return new StdMidiIn(Parent);
}


void StdMidiIn::ProcessMidi(unsigned wDeviceNum, MidiData *lpEvent)
{
  for (unsigned i = 0; i < ListSize; i++)
    if(ObjectsList[i]->wDevice == wDeviceNum)
      ObjectsList[i]->OutputMidi(lpEvent);

}

int StdMidiIn::GetStatus()const
{
  return cStatus;
}

int StdMidiIn::GetChannel()const
{
  return cMidiChannel;
}


void StdMidiIn::SetStatus(int NewStatus)
{
  if (NewStatus < 8 || NewStatus >15)
    {
      Error (eInvalidStatus, this, NewStatus);
      return;
    }
  SetModified(true);
  cStatus = (UINT8)NewStatus;
}

void StdMidiIn::SetChannel(int chan)
{
  if (chan < 0 || chan > 16)
    {
      Error (eInvalidChannel, this, chan);
      return ;
    }

  SetModified(true);
  cMidiChannel = (UINT8)chan;
}


void StdMidiIn::SetData1(int Data)
{
  if (Data > 127)
   {
     Error (eInvalidDataValue, this, Data);
     return;
   }

  SetModified(true);
  iData1 = (INT16) Data;
}


void StdMidiIn::SetData2(int Data)
{
  if (Data > 127)
    {
      Error (eInvalidDataValue, this, Data);
      return;
    }
  SetModified(true);
  iData2 = (INT16) Data;

}


void StdMidiIn::OutputMidi(MidiData *lpEvent)
{
  int iStatus = lpEvent->status / 0x10;
  int iChannel = lpEvent->status % 0x10;
  int iData1 = lpEvent->data1;
  int iData2 = lpEvent->data2;

  //check for filters first
  if(IsFiltered)
    {
      if (iStatus != (int)cStatus
	  ||((int)cMidiChannel != 0 && iChannel != (int)cMidiChannel - 1)
	  ||(StdMidiIn::iData1 >=0 && StdMidiIn::iData1 != iData1)
	  ||(StdMidiIn::iData2 >=0 && StdMidiIn::iData2 != iData2)
	  || (fNoteOnZeroFiltered && iStatus == NoteOn && !iData2))
      	return; //did not match filter
    }


  //produce the outputs
  tpOutlet[STATUS_OUTLET]->ProduceOutput(iStatus);
  tpOutlet[CHANNEL_OUTLET]->ProduceOutput(iChannel +1 );


  switch(iStatus)
    {
    case NoteOn:
    case NoteOff:
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
    }
}


const StdMidiIn::str_access StdMidiIn::aAccess[NumAccess] =
{
  {"Device", &StdMidiIn::Device, &StdMidiIn::Device},

};


const char* StdMidiIn::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool StdMidiIn::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool StdMidiIn::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}


const StdMidiIn::str_access StdMidiIn::aResetAccess[NumResetAccess] =
{
  {"Filtered", &StdMidiIn::Filtered, &StdMidiIn::Filtered},
  {"FilterNoteOnVelocityZero", &StdMidiIn::FilterNoteOnVelocityZero, &StdMidiIn::FilterNoteOnVelocityZero},
	{"ResetDevice", &StdMidiIn::ResetDevice, &StdMidiIn::ResetDevice},
  {"Status", &StdMidiIn::Status, &StdMidiIn::Status},
  {"Channel", &StdMidiIn::Channel, &StdMidiIn::Channel},
  {"Data1", &StdMidiIn::Data1, &StdMidiIn::Data1},
  {"Data2", &StdMidiIn::Data2, &StdMidiIn::Data2},
};


const char* StdMidiIn::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool StdMidiIn::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool StdMidiIn::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}

bool StdMidiIn::Status (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetStatus(), ret, ret_size);
}

bool StdMidiIn::Channel (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetChannel(), ret, ret_size);
}
bool StdMidiIn::Data1 (char* ret, unsigned ret_size) const

{
	return SMUtility::IntToStr (GetData1(), ret, ret_size);
}
bool StdMidiIn::Data2 (char* ret, unsigned ret_size) const

{
	return SMUtility::IntToStr (GetData2(), ret, ret_size);
}

bool StdMidiIn::Device (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetDevice(), ret, ret_size);
}

bool StdMidiIn::Filtered (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetFiltered(), ret, ret_size);
}

bool StdMidiIn::FilterNoteOnVelocityZero (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetNoteOnZeroFilter(), ret, ret_size);
}

bool StdMidiIn::ResetDevice  (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetDevice(), ret, ret_size);
}

bool StdMidiIn::Status (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetStatus(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiIn::Channel (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetChannel(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiIn::Data1 (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetData1(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiIn::Data2 (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetData2(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiIn::Device (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetDevice(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiIn::Filtered (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetFiltered(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiIn::FilterNoteOnVelocityZero (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetNoteOnZeroFilter(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool StdMidiIn::ResetDevice (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetDevice(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}
