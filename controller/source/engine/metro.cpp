// Metro defs
#include "stdafx.h"
#include "control.h"
#include "metro.h"
#include <string.h>
#include "typenames.h"

#define NUM_INLETS  2
#define NUM_OUTLETS  1
#define MIN_RATE 10

const char*const Metro::szType = METRO_TYPE;
const unsigned Metro::NumAccess = Metro::eMaxAttribute;
const unsigned Metro::NumResetAccess = Metro::eMaxResetAttribute;


// create the default
static Metro *reference = new Metro(NULL);

const BaseShell* Metro::GetReference() const
{
	return reference;
}


const Metro::pIntFunc  Metro::tpIntFunc [NUM_INLETS] = {
  &Metro::Activate,
  &Metro::SetIntInterval
};

const Metro::pStringFunc  Metro::tpStringFunc [NUM_INLETS] = {
  &Metro::DecodeStringInlet0,
  NULL
};

const char*const Metro::szaInletDetails[NUM_INLETS] = {
  "On / Off",
  "Interval"
};

const char*const Metro::szaOutletDetails[NUM_OUTLETS] = {
  "Metro Output Tick"
};

const char* Metro::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}

const char* Metro::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}

Metro::Metro(Patch* Parent, const char* Name,
	     const char* Comment, unsigned Interval)
  :BaseShell(Parent, NUM_INLETS, NUM_OUTLETS,
	     Name, Comment),
  FreeRunning(Interval), wResetInterval(Interval) 
{
  Reset();
}

Metro::~Metro()
{
  Stop();
}
void Metro::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}

inline void Metro::StringInlet(unsigned InletNumber, const char* s)
{
  if ((InletNumber < GetNumInlets())&&(tpStringFunc[InletNumber]))
    (this->*tpStringFunc[InletNumber])(s);
}

void Metro::Activate(int i)
{
  if (i)
    Start();
  else
    Stop();
}

void Metro::DecodeStringInlet0(const char* s)
{
  if (!strcmp(s, "reset"))
    {Reset(); return;}
  if (!strcmp(s, "start"))
    {Start(); return;}
  if (!strcmp(s, "stop"))
    {Stop(); return;}
}
BaseShell* Metro::Create(Patch* Parent)
{
  return new Metro(Parent);
}


void Metro::SetResetInterval(int i)
{
  if(wResetInterval == (unsigned)i || i < MIN_RATE)
    return;
  wResetInterval = (unsigned)i;
  SetModified(true);
}

void Metro::SetInterval(int i)
{
  if((unsigned)i >= MIN_RATE)
    SetClockInterval(i);
}

const Metro::str_access Metro::aAccess[NumAccess] =
{
  {"Interval", &Metro::Interval, &Metro::Interval},
  {"Metro Is On", &Metro::IsOn, &Metro::IsOn}
};


const char* Metro::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool Metro::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool Metro::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}

const Metro::str_access Metro::aResetAccess[NumResetAccess] =
{
  {"ResetInterval", &Metro::ResetInterval, &Metro::ResetInterval}
  
};

const char* Metro::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool Metro::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool Metro::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}

bool Metro:: Interval (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetInterval (), ret, ret_size);
}

bool Metro:: IsOn (char* ret, unsigned ret_size) const
{
	unsigned running = 0;

  if (IsRunning())
  {
  	running = 1;
  }

	return SMUtility::IntToStr (running, ret, ret_size);
}

bool Metro:: ResetInterval (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetInterval(), ret, ret_size);
}


bool Metro:: Interval (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetInterval(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Metro:: IsOn (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
    	if (SMUtility::StrToInt(new_val))
      {
      	Start();
      }

      else
      {
        Stop();
      }
			ret = true;
		}
	return ret;
}

void Metro:: DoDefaultAction()
{
	if (IsRunning())
		{
			Stop();
		}
	
	else
		{
			Start();
		}
	
}

bool Metro:: ResetInterval (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetInterval(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}
