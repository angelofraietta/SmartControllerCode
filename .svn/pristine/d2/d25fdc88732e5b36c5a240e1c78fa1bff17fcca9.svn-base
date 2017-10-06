/************************************************************
NumberStore class definition
*************************************************************/
#include "stdafx.h"
#include "control.h"
#include "number.h"
#include "typenames.h"

#define NUM_INLETS  1
#define NUM_OUTLETS  1

const char*const NumberStore::szType = NUMBERSTORE_TYPE;
const unsigned NumberStore::NumAccess = NumberStore::eMaxAttribute;
const unsigned NumberStore::NumResetAccess = NumberStore::eMaxResetAttribute;


// create the default
static NumberStore *reference = new NumberStore (NULL);

const BaseShell* NumberStore::GetReference() const
{
	return reference;
}

NumberStore::NumberStore ( Patch* Parent,
			   const char* Name,
			   const char* Comment,
			   int LowerLimit,
			   int UpperLimit,
			   int Number) // default constructor)
  :	BaseShell(Parent, NUM_INLETS, //NumInlets
		  NUM_OUTLETS, // NumOutlets
		  Name,	Comment),
  iResetNumber(Number),
  iUpperLimit(UpperLimit),
  iLowerLimit(LowerLimit)
  
{
  
  Reset(); // load into current state
};

NumberStore::~NumberStore()
{
}

const NumberStore::pVoidFunc  NumberStore::tpVoidFunc [NUM_INLETS] = {
  &NumberStore::Send
};

const NumberStore::pIntFunc  NumberStore::tpIntFunc [NUM_INLETS] = {
  &NumberStore::NumberInlet
};


const char*const NumberStore::szaInletDetails[NUM_INLETS] = {
  "NumberIn",
};

const char*const NumberStore::szaOutletDetails[NUM_OUTLETS] = {
  "Number Out"
};

const char* NumberStore::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}

const char* NumberStore::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}


void NumberStore::VoidInlet(unsigned InletNumber)
{
  if ((InletNumber < GetNumInlets()) && (tpVoidFunc[InletNumber]))
    {
      (this->*tpVoidFunc[InletNumber])();
      if(InletNumber == 0)
      	Send();
    }
}

void NumberStore::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}



void NumberStore::Reset()
  /* Resets the NumberStore by loading the reset conditions into the current
     conditions.  This is because a NumberStore may change during a performance*/
{
  iNumber = iResetNumber;
}


void	NumberStore:: SetUpperLimit (int NewLimit)
  // if NewLimit is > iLowerLimit will set iUpperLimit to NewLimit
  //  else does not change iResetLimit and calls error
{
  iUpperLimit = NewLimit;
  SetModified(true);
};

void	NumberStore::SetLowerLimit(int NewLimit)
  // if NewLimit is < iUpperLimit will set iLowerLimit to NewLimit
  //  else does not change iLowerLimit and calls error
{
  iLowerLimit = NewLimit;
  SetModified(true);
}

//***************************************************************************
//***************************************************************************

void NumberStore::SetNumber(int iNewNumber)
{
  SetPerformanceNumber (iNewNumber);
}

void NumberStore::SetResetNumber(int iNewNumber)
{
  iResetNumber = iNewNumber;
  SetModified(true);
}




BaseShell* NumberStore::Create(Patch* Parent)
{
  return new NumberStore(Parent);
}






void NumberStore::Send()
{
  tpOutlet[0]->ProduceOutput(iNumber);
}

void NumberStore::NumberInlet(int i)
{
  if (SetPerformanceNumber(i))
    {
      Send();
    }
}

bool NumberStore::SetPerformanceNumber (int iNewNumber)
{
	iNumber = iNewNumber;

  return true;
}

const NumberStore::str_access NumberStore::aAccess[NumAccess] =
{

  {"Number", &NumberStore::Number, &NumberStore::Number}
  
};


const char* NumberStore::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool NumberStore::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool NumberStore::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}

const NumberStore::str_access NumberStore::aResetAccess[NumResetAccess] =
{

  {"ResetNumber", &NumberStore::ResetNumber, &NumberStore::ResetNumber},
  {"LowerLimit", &NumberStore::LowerLimit, &NumberStore::LowerLimit},
  {"UpperLimit", &NumberStore::UpperLimit, &NumberStore::UpperLimit}
  
};

const char* NumberStore::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool NumberStore::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool NumberStore::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool NumberStore:: Number (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetNumber (), ret, ret_size);
}

bool NumberStore:: ResetNumber (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetNumber (), ret, ret_size);
}

bool NumberStore:: LowerLimit (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetLowerLimit (), ret, ret_size);
}

bool NumberStore:: UpperLimit (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetUpperLimit (), ret, ret_size);
}


bool NumberStore:: Number (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetNumber(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool NumberStore:: ResetNumber (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetNumber(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool NumberStore:: LowerLimit (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetLowerLimit(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool NumberStore:: UpperLimit (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetUpperLimit(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}


