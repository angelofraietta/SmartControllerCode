#include "stdafx.h"
#include "control.h"
#include "toggle.h"
#include "estring.h"
#include "typenames.h"

#define NUM_INLETS  1
#define NUM_OUTLETS  1


const char*const Toggle::szType = TOGGLE_TYPE;
const unsigned Toggle::NumAccess = Toggle::eMaxAttribute;
const unsigned Toggle::NumResetAccess = Toggle::eMaxResetAttribute;


// create the default
static Toggle *reference = (NULL);

const BaseShell* Toggle::GetReference() const
{
	return reference;
}


const char*const Toggle::szaInletDetails = "Input";

const char*const Toggle::szaOutletDetails = "Output";


const char* Toggle::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails;
  else
    return NULL;
}

const char* Toggle::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails;
  else
    return NULL;
}


Toggle::Toggle(Patch* Parent, const char* Name,
	       const char* Comment, bool State)
  :BaseShell(Parent, NUM_INLETS, NUM_OUTLETS,
	     Name, Comment),
  ResetState((State))
{Reset();}

void Toggle::VoidInlet(unsigned InletNumber)
{
  if (InletNumber >= GetNumInlets())
    return;
  ChangeState();
  Send();
}

void Toggle::IntInlet(unsigned InletNumber, int i)
{
  if (InletNumber >= GetNumInlets())
    return;
  State = (i);
  Send();
}

inline void Toggle::StringInlet(unsigned InletNumber, const char* s)
{
  if (InletNumber >= GetNumInlets())
    return;
  
  if (!strcmp(s, "reset"))
    Reset();
}


BaseShell* Toggle::Create(Patch* Parent)
{
  return new Toggle(Parent);
}

void Toggle::SetResetState(int f)
{
  ResetState = (f);
  SetModified(true);
}

void Toggle::Send()
{
	int val = 0;
	if (State)
		{
			val = 1;
		}

  tpOutlet[0]->ProduceOutput(val);
}


const Toggle::str_access Toggle::aAccess[NumAccess] =
{

  {"State", &Toggle::GetState, &Toggle::SetState}

  
};


const char* Toggle::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool Toggle::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool Toggle::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}

const Toggle::str_access Toggle::aResetAccess[NumResetAccess] =
{
  {"ResetState", &Toggle::GetResetState, &Toggle::SetResetState}
  
};


const char* Toggle::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool Toggle::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool Toggle::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool Toggle::GetState (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetState(), ret, ret_size);
}

bool Toggle::GetResetState (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetState(), ret, ret_size);
}

bool Toggle::SetState (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetState(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Toggle::SetResetState (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetState(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}


bool Toggle::GetDefaultAttribute (char* buf, unsigned buf_len)const
{
	return GetState (buf, buf_len);
}

bool Toggle::SetDefaultAttribute (const char* new_value)
{
	return SetState (new_value);
}
