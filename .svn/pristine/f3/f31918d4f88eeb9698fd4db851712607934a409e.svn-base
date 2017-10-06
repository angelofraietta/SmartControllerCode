// Creates an object that performs operations on two numbers
// based on Selector Class
#include "stdafx.h"
#include "control.h"
#include "selector.h"
#include "typenames.h"

#define NUM_INLETS 3
#define NUM_OUTLETS 2



const char*const Selector::szType = SELECTOR_TYPE;
const unsigned Selector::NumAccess = Selector::eMaxAttribute;
const unsigned Selector::NumResetAccess = Selector::eMaxResetAttribute;


// create the default
static Selector *reference = new Selector (NULL);

const BaseShell* Selector::GetReference() const
{
	return reference;
}

const Selector::pIntFunc  Selector::tpIntFunc [NUM_INLETS] = {
  &Selector::Filter,
  &Selector::SetLowerValue,
  &Selector::SetUpperValue
};

const Selector::pDoubleFunc  Selector::tpDoubleFunc [NUM_INLETS] = {
  &Selector::Filter,
  &Selector::SetLowerValue,
  &Selector::SetUpperValue
};


const char*const Selector::szaInletDetails[NUM_INLETS] = {
  "Message Input",
  "Lower Limit",
  "Upper Limit"
};

const char*const Selector::szaOutletDetails[NUM_OUTLETS] = {
  "Matching Value",
  "Non-Matching Value"
};

const char* Selector::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}

const char* Selector::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}


Selector::Selector (Patch* Parent, const char* Name,const char* Comment,
		    double LValue, double UValue)
  :BaseShell (Parent,NUM_INLETS, NUM_OUTLETS, Name, Comment),
   iResetLowerValue(LValue),iResetUpperValue(UValue)
{
  Reset();
}





void Selector::Reset ()
{
  iLowerValue = iResetLowerValue;
  iUpperValue = iResetUpperValue;
}

void Selector::Filter(double i)
{
  if ((i < iLowerValue) || (i > iUpperValue))
    // produce unselected output
    tpOutlet[1]->ProduceOutput(i);
  else
    tpOutlet[0]->ProduceOutput(i);
}


BaseShell* Selector::Create(Patch* Parent)
{
  return new Selector(Parent);
}



void Selector::VoidInlet(unsigned InletNumber)
{
  if(InletNumber == 0)
    tpOutlet[1]->ProduceOutput();

}

void Selector::DoubleInlet(unsigned InletNumber, double d)
{
  if ((InletNumber < GetNumInlets())&& (tpDoubleFunc[InletNumber]))
    {
      (this->*tpDoubleFunc[InletNumber])(d);
    }
}


void Selector::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}

void Selector::StringInlet(unsigned InletNumber, const char* s)
{
  if (InletNumber == 0)
    {
      if (!strcmp(s, "reset"))
      	Reset();
      tpOutlet[1]->ProduceOutput(s);
    }
}


void Selector::SetResetLowerValue (double NewInt)
{
  iResetLowerValue = NewInt;
  SetModified(true);
}

void Selector::SetResetUpperValue (double NewInt)
{
  iResetUpperValue = NewInt;
  SetModified(true);
}



const Selector::str_access Selector::aAccess[NumAccess] =
{
	{"LowerValue", &Selector::LowerValue, &Selector::LowerValue},
  {"UpperValue", &Selector::UpperValue, &Selector::UpperValue}

};


const char* Selector::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool Selector::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool Selector::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}


const Selector::str_access Selector::aResetAccess[NumResetAccess] =
{
	{"ResetLowerValue", &Selector::ResetLowerValue, &Selector::ResetLowerValue},
	{"ResetUpperValue", &Selector::ResetUpperValue, &Selector::ResetUpperValue}
   
};

const char* Selector::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool Selector::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool Selector::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}

bool Selector::LowerValue (char* ret, unsigned ret_size) const
{
	return SMUtility::FltToStr (GetLowerValue(), ret, ret_size);
}

bool Selector::UpperValue (char* ret, unsigned ret_size) const
{
	return SMUtility::FltToStr (GetUpperValue(), ret, ret_size);
}

bool Selector::ResetLowerValue (char* ret, unsigned ret_size) const
{
	return SMUtility::FltToStr (GetResetLowerValue(), ret, ret_size);
}

bool Selector::ResetUpperValue (char* ret, unsigned ret_size) const
{
	return SMUtility::FltToStr (GetResetUpperValue(), ret, ret_size);
}


bool Selector::LowerValue (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			SetLowerValue(SMUtility::StrToFlt(new_val));
			ret = true;
		}
	return ret;
}

bool Selector::UpperValue (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			SetUpperValue(SMUtility::StrToFlt(new_val));
			ret = true;
		}
	return ret;
}

bool Selector::ResetLowerValue (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			SetResetLowerValue(SMUtility::StrToFlt(new_val));
			ret = true;
		}
	return ret;
}

bool Selector::ResetUpperValue (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			SetResetUpperValue(SMUtility::StrToFlt(new_val));
			ret = true;
		}
	return ret;
}

