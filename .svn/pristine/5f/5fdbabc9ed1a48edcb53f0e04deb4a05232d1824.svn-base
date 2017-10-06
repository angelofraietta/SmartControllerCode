/************************************************************
random generator class definition
*************************************************************/
#include "stdafx.h"
#include <stdlib.h>
#include "control.h"
#include "digitalout.h"
#include "typenames.h"
#include "midioutputdriver.h"

#define NUM_INLETS  2
#define NUM_OUTLETS  0

const char*const DigitalOut::szType = DIGITAL_OUT_TYPE;
const unsigned DigitalOut::NumAccess = DigitalOut::eMaxAttribute;
const unsigned DigitalOut::NumResetAccess = DigitalOut::eMaxResetAttribute;


// create the default
static DigitalOut *reference = new DigitalOut (NULL);

const BaseShell* DigitalOut::GetReference() const
{
	return reference;
}


DigitalOut::DigitalOut ( Patch* Parent,
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

DigitalOut::~DigitalOut()
{
}


const DigitalOut::pIntFunc  DigitalOut::tpIntFunc [NUM_INLETS] = {
  &DigitalOut::SetValue,
  &DigitalOut::SetChannel
};


const char*const DigitalOut::szaInletDetails[NUM_INLETS] = {
  "Value",
  "Channel"
};


const char* DigitalOut::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}


void DigitalOut::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}



void DigitalOut::Reset()
  /* Resets the DigitalOut by loading the reset conditions into the current
     conditions.  This is because a DigitalOut may change during a performance*/
{
  iValue = iResetValue;
  iChannel = iResetChannel;

  if (fGenerateOnReset)
  {
  	Send();
  }
}



void	DigitalOut::SetResetValue(int value)
{
  iResetValue = value;
  SetModified(true);
}

void	DigitalOut::SetResetChannel(int value)
{
  iResetChannel = value;
  SetModified(true);
}

void	DigitalOut::SetGenerateOnReset(int value)
{
  fGenerateOnReset = (value);
  SetModified(true);
}



BaseShell* DigitalOut::Create(Patch* Parent)
{
  return new DigitalOut(Parent);
}






void DigitalOut::Send()
{
	BYTE send_value = 0;
  if (iValue) send_value = 0xFF;
	if (iChannel)
		{
			MidiOutputDriver::TransmitDigitalVoltage((BYTE)send_value, iChannel - 1);
		}
}



const DigitalOut::str_access DigitalOut::aAccess[NumAccess] =
{

  {"Channel", &DigitalOut::Channel, &DigitalOut::Channel},
  {"Value", &DigitalOut::Value, &DigitalOut::Value}
  
};

const char* DigitalOut::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool DigitalOut::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool DigitalOut::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}

const DigitalOut::str_access DigitalOut::aResetAccess[NumResetAccess] =
{
  {"ResetChannel", &DigitalOut::ResetChannel, &DigitalOut::ResetChannel},
  {"ResetValue", &DigitalOut::ResetValue, &DigitalOut::ResetValue},
  {"GenerateOnReset", &DigitalOut::GenerateOnReset, &DigitalOut::GenerateOnReset}
  
};


const char* DigitalOut::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool DigitalOut::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool DigitalOut::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool DigitalOut:: Value (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetValue (), ret, ret_size);
}

bool DigitalOut:: ResetValue (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetValue (), ret, ret_size);
}

bool DigitalOut:: Channel (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetChannel (), ret, ret_size);
}

bool DigitalOut:: ResetChannel (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetChannel (), ret, ret_size);
}

bool DigitalOut:: GenerateOnReset (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetGenerateOnReset (), ret, ret_size);
}


bool DigitalOut:: Value (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetValue(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool DigitalOut::ResetValue (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetValue(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool DigitalOut:: Channel (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetChannel(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool DigitalOut::ResetChannel (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetChannel(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool DigitalOut::GenerateOnReset (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetGenerateOnReset(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}




