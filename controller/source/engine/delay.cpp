#include "stdafx.h"
#include "control.h"
#include "delay.h"

#include "estring.h"
#include "typenames.h"


#define NUM_INLETS  2
#define NUM_OUTLETS  1


const char*const Delay::szType = DELAY_TYPE;
const unsigned Delay::NumAccess = Delay::eMaxAttribute;
const unsigned Delay::NumResetAccess = Delay::eMaxResetAttribute;


// create the default
static Delay *reference =  new Delay (NULL);

const BaseShell* Delay::GetReference() const
{
	return reference;
}


const Delay::pIntFunc  Delay::tpIntFunc [NUM_INLETS] = {
  &Delay::DelayInt,
  &Delay::SetInterval
};

const Delay::pStringFunc  Delay::tpStringFunc [NUM_INLETS] = {
  &Delay::DelayString,
  &Delay::StringInlet1
};

const Delay::pDoubleFunc  Delay::tpDoubleFunc [NUM_INLETS] = {
  &Delay::DelayDouble,
  NULL
};

const Delay::pVoidFunc  Delay::tpVoidFunc [NUM_INLETS] = {
  &Delay::DelayVoid,
  NULL
};

const char*const Delay::szaInletDetails[NUM_INLETS] = {
  "Message",
  "Interval"
};

const char*const Delay::szaOutletDetails[NUM_OUTLETS] = {
  "Delayed Message"
};

const char* Delay::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}

const char* Delay::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}

Delay::Delay(Patch* Parent, const char* Name,
						 const char* Comment, unsigned Interval)
  :BaseShell(Parent, NUM_INLETS, NUM_OUTLETS,
						 Name, Comment),
  wResetInterval(Interval), fStopProcess (false)
{Reset();}

Delay::~Delay()
{
  fStopProcess = true;
  Purge();
}

void Delay::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}

void Delay::VoidInlet(unsigned InletNumber)
{
  if ((InletNumber < GetNumInlets())&& (tpVoidFunc[InletNumber]))
    (this->*tpVoidFunc[InletNumber])();
}

void Delay::DoubleInlet(unsigned InletNumber, double d)
{
  if ((InletNumber < GetNumInlets())&& (tpDoubleFunc[InletNumber]))
    {
      (this->*tpDoubleFunc[InletNumber])(d);
    }
  
  else
    {
      IntInlet(InletNumber, DoubleToInt(d));
    }
  
}

inline void Delay::StringInlet(unsigned InletNumber, const char* s)
{
  if ((InletNumber < GetNumInlets())&&(tpStringFunc[InletNumber]))
    (this->*tpStringFunc[InletNumber])(s);
}

void Delay::StringInlet1(const char* s)
{
  if(!strcmp(s, "reset"))
    Reset();
}

BaseShell* Delay::Create(Patch* Parent)
{
  return new Delay(Parent);
}



void Delay::DelayVoid()
{
  if (!fStopProcess)
    {
      MessageCell* pDelayedMessage = new MessageCell;
      
      if (pDelayedMessage)
				{
					//send to the delay
					if (!GoOneShot((DWORD)pDelayedMessage))
						{
							Error (eDelayError, this);
							delete pDelayedMessage;
						}
				}
      
      else
				{
					Error (eDelayError, this);
				}
    }
}

void Delay::DelayInt(int i)
{
  if (!fStopProcess)
    {
      MessageCell* pDelayedMessage = new MessageCell(i);
      if (pDelayedMessage)
				{
					if (!GoOneShot((DWORD)pDelayedMessage))
						{
							Error (eDelayError, this);
							delete pDelayedMessage;
						}
				}
      
      else
				{
					Error (eDelayError, this);
				}
    }
}

void Delay::DelayString(const char* s)
{
  if (!fStopProcess)
    {
      MessageCell* pDelayedMessage = new MessageCell(s);
      if (pDelayedMessage)
				{
					if (!GoOneShot((DWORD)pDelayedMessage))
						{
							Error (eDelayError, this);
							delete pDelayedMessage;
						}
				}
      
      else
				{
					Error (eDelayError, this);
				}
    }
}

void Delay::DelayDouble(double d)
{
  if (!fStopProcess)
    {
      MessageCell* pDelayedMessage = new MessageCell(d);
      
      if (pDelayedMessage)
				{
					if (!GoOneShot((DWORD)pDelayedMessage))
						{
							Error (eDelayError, this);
							delete pDelayedMessage;
						}
				}
      
      else
				{
					Error (eDelayError, this);
				}
    }
}

void Delay::OutputFunction(DWORD ReturnMessage)
{
  MessageCell* TheMessage = (MessageCell*)ReturnMessage;
  SendMessage(*TheMessage);
  delete TheMessage;
  
}

void Delay::SendMessage (MessageCell& TheMessage)
{
	tpOutlet[0]->ProduceOutput(TheMessage);
}

void Delay::PurgeItem(DWORD pMessage)
{
  MessageCell* PurgeMessage = (MessageCell*) pMessage;
  delete PurgeMessage;
}

void Delay::SetResetInterval(int i)
{
  if(wResetInterval == (unsigned)i)
    return;
  wResetInterval = (unsigned)i;
  SetModified(true);
}

void Delay::Reset ()
{
  wInterval = wResetInterval;
  fStopProcess = true;
  Purge();
  fStopProcess = false;
}



const Delay::str_access Delay::aAccess[NumAccess] =
{
	
  {"Interval", &Delay::Interval, &Delay::Interval}  
};


const char* Delay::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool Delay::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool Delay::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}


const Delay::str_access Delay::aResetAccess[NumResetAccess] =
{
	
  {"ResetInterval", &Delay::ResetInterval, &Delay::ResetInterval}
  
};

const char* Delay::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool Delay::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool Delay::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}

bool Delay:: Interval (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetInterval (), ret, ret_size);
}

bool Delay:: ResetInterval (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetInterval(), ret, ret_size);
}


bool Delay:: Interval (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetInterval(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Delay:: ResetInterval (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetInterval(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}















