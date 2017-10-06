/************************************************************
random generator class definition
*************************************************************/
#include "stdafx.h"
#include <stdlib.h>
#include "control.h"
#include "randomgen.h"
#include "typenames.h"


#define NUM_INLETS  2
#define NUM_OUTLETS  1

const char*const RandomGen::szType = RANDOMGEN_TYPE;
const unsigned RandomGen::NumAccess = RandomGen::eMaxAttribute;
const unsigned RandomGen::NumResetAccess = RandomGen::eMaxResetAttribute;


// create the default
static RandomGen *reference = new RandomGen (NULL);

const BaseShell* RandomGen::GetReference() const
{
	return reference;
}

RandomGen::RandomGen ( Patch* Parent,
		       const char* Name,
		       const char* Comment,
		       int UpperLimit) // default constructor)
  :	BaseShell(Parent, NUM_INLETS, //NumInlets
		  NUM_OUTLETS, // NumOutlets
		  Name,	Comment),
  iNumber(0), iResetUpperLimit(UpperLimit)
{
  
  Reset(); // load into current state
};

RandomGen::~RandomGen()
{
}

const RandomGen::pVoidFunc  RandomGen::tpVoidFunc [NUM_INLETS] = {
  &RandomGen::OutputNumber,
  NULL
};

const RandomGen::pIntFunc  RandomGen::tpIntFunc [NUM_INLETS] = {
  &RandomGen::SetNumber,
  &RandomGen::SetUpperLimit
};


const char*const RandomGen::szaInletDetails[NUM_INLETS] = {
  "Generate",
  "Range"
};

const char*const RandomGen::szaOutletDetails[NUM_OUTLETS] = {
  "Number Out"
};

const char* RandomGen::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}

const char* RandomGen::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}


void RandomGen::VoidInlet(unsigned InletNumber)
{
  if ((InletNumber < GetNumInlets()) && (tpVoidFunc[InletNumber]))
    (this->*tpVoidFunc[InletNumber])();
}

void RandomGen::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}



void RandomGen::Reset()
  /* Resets the RandomGen by loading the reset conditions into the current
     conditions.  This is because a RandomGen may change during a performance*/
{
  //	iNumber = 0;
  iUpperLimit = iResetUpperLimit;
}


void	RandomGen:: SetUpperLimit (int NewLimit)
{
  iUpperLimit = NewLimit;
};

void	RandomGen::SetResetUpperLimit(int NewLimit)
{
  iResetUpperLimit = NewLimit;
  SetModified(true);
}

//***************************************************************************
//***************************************************************************

void RandomGen::SetNumber(int iNewNumber)
{
  iNumber = iNewNumber;
}




BaseShell* RandomGen::Create(Patch* Parent)
{
  return new RandomGen(Parent);
}




void RandomGen::OutputNumber()
{
  Generate();
  Send();
}

void RandomGen::Send()
{
  tpOutlet[0]->ProduceOutput(iNumber);
}

void RandomGen::Generate()
{
  iNumber = rand() % iUpperLimit;
}

inline void RandomGen::StringInlet(unsigned InletNumber, const char* s)
{
  if (InletNumber >= GetNumInlets())
    return;
  
  if (!strcmp(s, "reset"))
    Reset();
}

const RandomGen::str_access RandomGen::aAccess[NumAccess] =
{

  {"Number", &RandomGen::Number, &RandomGen::Number},
  {"UpperLimit", &RandomGen::UpperLimit, &RandomGen::UpperLimit}
  
};

const char* RandomGen::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool RandomGen::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool RandomGen::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}

const RandomGen::str_access RandomGen::aResetAccess[NumResetAccess] =
{
  {"ResetUpperLimit", &RandomGen::ResetUpperLimit, &RandomGen::ResetUpperLimit}
  
};


const char* RandomGen::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool RandomGen::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool RandomGen::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool RandomGen:: Number (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetNumber (), ret, ret_size);
}

bool RandomGen:: UpperLimit (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetUpperLimit (), ret, ret_size);
}

bool RandomGen:: ResetUpperLimit (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetUpperLimit (), ret, ret_size);
}


bool RandomGen:: Number (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetNumber(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool RandomGen:: UpperLimit (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetUpperLimit(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}



bool RandomGen::ResetUpperLimit (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetUpperLimit(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}


