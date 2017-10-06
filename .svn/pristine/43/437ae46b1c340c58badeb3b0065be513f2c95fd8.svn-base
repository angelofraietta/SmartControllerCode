#include "stdafx.h"

#include "control.h"
#include "flipflop.h"
#include "typenames.h"
#include "estring.h"


#define NUM_INLETS  2
#define NUM_OUTLETS  2


const char*const FlipFlop::szType = FLIPFLOP_TYPE;
const unsigned FlipFlop::NumAccess = FlipFlop::eMaxAttribute;
const unsigned FlipFlop::NumResetAccess = FlipFlop::eMaxResetAttribute;


// create the default
static FlipFlop *reference = new FlipFlop (NULL);

const BaseShell* FlipFlop::GetReference() const
{
	return reference;
}


const FlipFlop::pIntFunc  FlipFlop::tpIntFunc [NUM_INLETS] = {
  &FlipFlop::SetFlipFlop,
  &FlipFlop::ClearFlipFlop
};

const FlipFlop::pVoidFunc  FlipFlop::tpVoidFunc [NUM_INLETS] = {
  &FlipFlop::SetFlipFlop,
  &FlipFlop::ClearFlipFlop
};



const char*const FlipFlop::szaInletDetails[NUM_INLETS] = {
  "Set Input",
  "Clear Input"
};

const char*const FlipFlop::szaOutletDetails[NUM_OUTLETS] = {
  "Q",
  "Not Q"
};

const char* FlipFlop::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}

const char* FlipFlop::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}

void FlipFlop::SetFlipFlop()
{
  if (_State)
    return;
  _State = true;
  Send();
  }

void FlipFlop::ClearFlipFlop()
{
  if (!_State)
    return;
  _State = false;
  Send();
}

void FlipFlop::SetFlipFlop(int Input)
{
  
  if ((Input == 0) || _State)
    return;
  SetFlipFlop();
}

void FlipFlop::ClearFlipFlop(int Input)
{
  if ((Input == 0 ) || !_State)
    return;
  ClearFlipFlop();
}

FlipFlop::FlipFlop(Patch* Parent, const char* Name,
		   const char* Comment, bool State)
  :BaseShell(Parent, NUM_INLETS, NUM_OUTLETS,
	     Name, Comment),
  _ResetState((State))
{Reset();}

void FlipFlop::VoidInlet(unsigned InletNumber)
{
  if ((InletNumber < GetNumInlets())&& (tpVoidFunc[InletNumber]))
    (this->*tpVoidFunc[InletNumber])();
}

void FlipFlop::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}

inline void FlipFlop::StringInlet(unsigned InletNumber, const char* s)
{
  if (InletNumber >= GetNumInlets())
    return;
  
  if (!strcmp(s, "reset"))
    Reset();
}


BaseShell* FlipFlop::Create(Patch* Parent)
{
  return new FlipFlop(Parent);
}


void FlipFlop::DoDefaultAction()
{
	_State = !_State;
	Send();
}

void FlipFlop::Send()
{
  if (_State)
  {
    tpOutlet[0]->ProduceOutput((int)1);
    tpOutlet[1]->ProduceOutput((int)0);
  }
  else
  {
    tpOutlet[0]->ProduceOutput((int)0);
    tpOutlet[1]->ProduceOutput((int)1);

  }
}

void FlipFlop::SetResetState(int f)
{
  if(_ResetState == (f))
    return;
  _ResetState = f?1:0;
  SetModified(true);
}


const FlipFlop::str_access FlipFlop::aAccess[NumAccess] =
{

 {"State", &FlipFlop::State, &FlipFlop::State}
  
};


const char* FlipFlop::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool FlipFlop::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool FlipFlop::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}


const FlipFlop::str_access FlipFlop::aResetAccess[NumResetAccess] =
{

  {"ResetState", &FlipFlop::ResetState, &FlipFlop::ResetState}
  
};

const char* FlipFlop::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool FlipFlop::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool FlipFlop::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}

bool FlipFlop::State (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetState(), ret, ret_size);
}

bool FlipFlop::ResetState (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetState(), ret, ret_size);
}


bool FlipFlop::State(const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetState(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool FlipFlop::ResetState (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetState(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

