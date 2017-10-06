/************************************************************
random generator class definition
*************************************************************/
#include "stdafx.h"
#include <stdlib.h>
#include "control.h"
#include "analogout.h"
#include "typenames.h"
#include "midioutputdriver.h"

#define NUM_INLETS  2
#define NUM_OUTLETS  0

const char*const AnalogOut::szType = ANALOGUE_OUT_TYPE;
const unsigned AnalogOut::NumAccess = AnalogOut::eMaxAttribute;
const unsigned AnalogOut::NumResetAccess = AnalogOut::eMaxResetAttribute;


// create the default
static AnalogOut *reference = new AnalogOut (NULL);

const BaseShell* AnalogOut::GetReference() const
{
	return reference;
}


AnalogOut::AnalogOut ( Patch* Parent,
		       const char* Name,
		       const char* Comment,
		       int channel, int value) // default constructor)
  :	BaseShell(Parent, NUM_INLETS, //NumInlets
		  NUM_OUTLETS, // NumOutlets
		  Name,	Comment),
  iResetChannel(channel), iResetValue(value) , fGenerateOnReset(false)
{

  Reset(); // load into current state
};

AnalogOut::~AnalogOut()
{
}


const AnalogOut::pIntFunc  AnalogOut::tpIntFunc [NUM_INLETS] = {
  &AnalogOut::SetValue,
  &AnalogOut::SetChannel
};


const char*const AnalogOut::szaInletDetails[NUM_INLETS] = {
  "Value",
  "Channel"
};


const char* AnalogOut::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}


void AnalogOut::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}



void AnalogOut::Reset()
  /* Resets the AnalogOut by loading the reset conditions into the current
     conditions.  This is because a AnalogOut may change during a performance*/
{
  iValue = iResetValue;
  iChannel = iResetChannel;

  if (fGenerateOnReset)
  {
  	Send();
  }
}



void	AnalogOut::SetResetValue(int value)
{
  iResetValue = value;
  SetModified(true);
}

void	AnalogOut::SetResetChannel(int value)
{
  iResetChannel = value;
  SetModified(true);
}

void	AnalogOut::SetGenerateOnReset(int value)
{
  fGenerateOnReset = (value);
  SetModified(true);
}



BaseShell* AnalogOut::Create(Patch* Parent)
{
  return new AnalogOut(Parent);
}





void AnalogOut::Send()
{
	if (iChannel)
		{
			MidiOutputDriver::TransmitControlVoltage((BYTE)iValue, iChannel - 1);
		}
}



const AnalogOut::str_access AnalogOut::aAccess[NumAccess] =
{

  {"Channel", &AnalogOut::Channel, &AnalogOut::Channel},
  {"Value", &AnalogOut::Value, &AnalogOut::Value}
  
};

const char* AnalogOut::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool AnalogOut::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool AnalogOut::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}

const AnalogOut::str_access AnalogOut::aResetAccess[NumResetAccess] =
{
  {"ResetChannel", &AnalogOut::ResetChannel, &AnalogOut::ResetChannel},
  {"ResetValue", &AnalogOut::ResetValue, &AnalogOut::ResetValue},
  {"GenerateOnReset", &AnalogOut::GenerateOnReset, &AnalogOut::GenerateOnReset}
  
};


const char* AnalogOut::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool AnalogOut::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool AnalogOut::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool AnalogOut:: Value (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetValue (), ret, ret_size);
}

bool AnalogOut:: ResetValue (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetValue (), ret, ret_size);
}

bool AnalogOut:: Channel (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetChannel (), ret, ret_size);
}

bool AnalogOut:: ResetChannel (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetChannel (), ret, ret_size);
}

bool AnalogOut:: GenerateOnReset (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetGenerateOnReset (), ret, ret_size);
}


bool AnalogOut:: Value (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetValue(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool AnalogOut::ResetValue (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetValue(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool AnalogOut:: Channel (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetChannel(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool AnalogOut::ResetChannel (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetChannel(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool AnalogOut::GenerateOnReset (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetGenerateOnReset(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}




