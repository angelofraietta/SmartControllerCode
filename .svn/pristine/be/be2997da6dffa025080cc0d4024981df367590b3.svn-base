/************************************************************
counter class definition
*************************************************************/
#include "stdafx.h"
#include "control.h"
#include "counter.h"
#include "typenames.h"

#define NUM_INLETS  6
#define NUM_OUTLETS  3
#define COUNT_OUT tpOutlet[0]  	//outlet 0
#define UNDERFLOW_OUT tpOutlet[1] //Outlet1
#define OVERFLOW_OUT tpOutlet[2]  //outlet 2




const char*const Counter::szType = COUNTER_TYPE;
const unsigned Counter::NumAccess = Counter::eMaxAttribute;
const unsigned Counter::NumResetAccess = Counter::eMaxResetAttribute;

// create the default
static Counter *reference = new Counter(NULL);

const BaseShell* Counter::GetReference() const
{
	return reference;
}

Counter::Counter ( Patch* Parent,
		   const char* Name,
		   const char* Comment,
		   int LowerLimit,
		   int UpperLimit, 
		   bool CountDirection,
		   bool Bidirectional,
		   int StepSize,
		   int Count) // default constructor)
  :	BaseShell(Parent, NUM_INLETS, //NumInlets
		  NUM_OUTLETS, // NumOutlets
		  Name,	Comment),
  
  fResetDirection (CountDirection),
  fResetBidirectional(Bidirectional),    
  
  iResetUpperLimit(UpperLimit),  
  iResetLowerLimit(LowerLimit),  
  iResetStepSize(StepSize)
{
  // set the initial count
  if  ((Count > UpperLimit) || (Count < LowerLimit))
    { // outside counter limit
      if (Count > UpperLimit)
	iResetCount = UpperLimit;
      else
	iResetCount = LowerLimit;
    }
  else
    iResetCount = Count;
  
  Reset(); // load into current state
};

Counter::~Counter()
{
}

const Counter::pVoidFunc  Counter::tpVoidFunc [NUM_INLETS] = {
  &Counter::Count,
  NULL,
  &Counter::SetLowerLimit,
  &Counter::SetUpperLimit,
  &Counter::ChangeDirection,
  &Counter::ChangeBidirectional
};

const Counter::pIntFunc  Counter::tpIntFunc [NUM_INLETS] = {
  &Counter::SetCount,
  &Counter::SetStepSize,
  &Counter::SetLowerLimit,
  &Counter::SetUpperLimit,
  &Counter::SetDirection,
  &Counter::SetBidirectional
};

const Counter::pStringFunc  Counter::tpStringFunc [NUM_INLETS] = {
  &Counter::CountInlet,
  &Counter::SetStepSize,
  &Counter::SetLowerLimit,
  &Counter::SetUpperLimit,
  &Counter::SetDirection,
  &Counter::SetBidirectional
};

const char*const Counter::szaInletDetails[NUM_INLETS] = {
  "Count",
  "Step Size",
  "Set Lower Limit",
  "Set Upper Limit",
  "Change Direction",
  "Change Bidirectional"
  
};

const char*const Counter::szaOutletDetails[NUM_OUTLETS] = {
  "Count Out",
  "Underflow",
  "Overflow"
};

const char* Counter::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}

const char* Counter::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}


void Counter::VoidInlet(unsigned InletNumber)
{
  if ((InletNumber < GetNumInlets()) && (tpVoidFunc[InletNumber]))
    (this->*tpVoidFunc[InletNumber])();
}

void Counter::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}


void Counter::StringInlet(unsigned InletNumber, const char* s)
{
  if ((InletNumber < GetNumInlets())&& (tpStringFunc[InletNumber]))
    (this->*tpStringFunc[InletNumber])(s);
}

void Counter::SetStepSize(const char* s)
{
  if (!strcmp(s, "reset"))
    iStepSize = iResetStepSize;
}

void Counter::Count()
  // this module steps the counter the number of steps and the direction
  // set in the object
{
  if (fPreviouslyCounted & (iStepSize != 0)) // counter has not counted yet
    {                                           // or steps zero
      // convert negative step to positive and reverse count
      // and reverse count direction
      int iRealStepSize = iStepSize; // temp step size
      bool   fRealDirection = fDirection;
      if (iStepSize < 0)
				{
					iRealStepSize = -iStepSize; //make positive step
					if (fDirection == up)
						fRealDirection = down;
					else // must be down
						fRealDirection = up;
				} // end if   iStepSize < 0
      
      bool fIterate = false;  // causes counter to iterate until
      // iLowerLimit <= iCount <= iUpperLimit
      int iRemainder; //the amount counter may have overfloed by
      do
				{ //iterate
					if (!fRealDirection) // then is counting up
						{
            if (! fIterate) // first time
            	{
              iCount += iRealStepSize; 		// increment counter
              }

            if (iCount > iUpperLimit)  // above upper limit
              {
                iRemainder = iCount - iUpperLimit;
                if (! fBidirectional)
                  { // must be upcounter
                    // allow for count of lower limit by -1
                    iCount =  iRemainder + iLowerLimit - 1 ;
                    OverFlow();
                    fIterate = true;
                  }
                else // must be updown
                  {
                    iCount = iUpperLimit - iRemainder;
                    OverFlow();
                    fRealDirection = down; // change direction
                    ChangeDirection(); // change real counter

                    fIterate = true;
                  }// endif   (fBidirecrionalCounter)

              } // if  iCount > iUpperLimit
            else // is now within limit
              fIterate = false;    // clear flag
					  }

						else
            	{
							if (! fIterate) // first time
              	{
								iCount -= iRealStepSize; 		// decrement counter
                }

							if (iCount < iLowerLimit)  // below lower limit
								{
									iRemainder = iLowerLimit - iCount;
									if (! fBidirectional )
										{ // must be downcounter
											iCount = iUpperLimit - iRemainder + 1;
											UnderFlow();
											fIterate = true; // set flag
										}
									else // must be updown
										{
											iCount = iLowerLimit + iRemainder;
											UnderFlow();
											fRealDirection = up; // change direction
											ChangeDirection(); // change real counter
											fIterate = true;  // set flag
										} // endif   (fBidirecrionalCounter)
								} // iCount < iLowerLimit
							else
								fIterate = false; // within limit
							}

				} //do
      while (fIterate);
    } // end if fPreviouslyCounted
  fPreviouslyCounted = true;
  
  if (iCount == iLowerLimit)
    UNDERFLOW_OUT->ProduceOutput(1);
  if (iCount == iUpperLimit)
    OVERFLOW_OUT->ProduceOutput(1);
  
  COUNT_OUT->ProduceOutput(iCount);
};

void Counter::CountInlet (const char* s)
{
  if (strcmp(s,"reset")== 0 )
    {iCount = iResetCount; fPreviouslyCounted = false; return;}
  if (strcmp(s, "count")== 0)
    {Count(); return;}
  if (strcmp(s, "lower")== 0)
    {iCount = iLowerLimit; Send(); return;}
  if (strcmp(s, "upper")== 0)
    {iCount = iUpperLimit; Send(); return;}
}


void Counter::Reset()
  /* Resets the counter by loading the reset conditions into the current
     conditions.  This is because a counter may change during a performance*/
{
  iCount = iResetCount;
  iUpperLimit = iResetUpperLimit;
  iLowerLimit = iResetLowerLimit;
  iStepSize = iResetStepSize;
  fDirection = fResetDirection;
  fBidirectional = fResetBidirectional;
  fPreviouslyCounted = false;
};

void	Counter:: SetResetUpperLimit (int NewLimit)
  // if NewLimit is >= iResetLowerLimit will set iResetUpperLimit to NewLimit
  //  else does not change iResetUpperLimit and calls error
{
  if (NewLimit >= iResetLowerLimit)
    {
      if(iResetUpperLimit == NewLimit)
      	return;
      iResetUpperLimit = NewLimit;
      SetModified(true);
    }
  else
    Error (eCounterError, this, NewLimit);
};


void	Counter::SetResetLowerLimit(int NewLimit)
  // if NewLimit is <= iResetUpperLimit will set iResetLowerLimit to NewLimit
  //  else does not change iResetLowerLimit and calls error
{
  if (NewLimit <= iResetUpperLimit)
    {
      if(iResetLowerLimit == NewLimit)
      	return;
      iResetLowerLimit = NewLimit;
      SetModified(true);
    }
  else
    Error (eCounterError, this, NewLimit);
};

void	Counter:: SetUpperLimit (int NewLimit)
  // if NewLimit is >= iLowerLimit will set iUpperLimit to NewLimit
  //  else does not change iResetLimit and calls error
{
  if (NewLimit >= iLowerLimit)
    iUpperLimit = NewLimit;
  else
    Error (eCounterError, this, NewLimit);
};

void Counter::SetUpperLimit(const char* s)
{
  if (strcmp(s, "reset")== 0)
    SetUpperLimit(iResetUpperLimit);
}

void	Counter::SetLowerLimit(int NewLimit)
  // if NewLimit is <= iUpperLimit will set iLowerLimit to NewLimit
  //  else does not change iLowerLimit and calls error
{
  if (NewLimit <= iUpperLimit)
    iLowerLimit = NewLimit;
  else
    Error (eCounterError, this, NewLimit);
}

void Counter::SetLowerLimit(const char* s)
{
  if (strcmp(s, "reset")== 0)
    SetLowerLimit(iResetLowerLimit);
}
void Counter::SetDirection(const char* s)
{
  if (strcmp(s,"reset") == 0)
    {fDirection = fResetDirection; return;}
  if (strcmp(s,"down") == 0)
    {fDirection = down; return;}
  if (strcmp(s, "up")== 0)
    {fDirection = up; return;}
  if (strcmp(s, "change")==0)
    ChangeDirection();
}

void Counter::SetBidirectional(const char* s)
{
  if (strcmp(s, "reset")==0)
    {fBidirectional = fResetBidirectional; return;}
  if (strcmp(s, "down")==0)
    {fDirection = down; fBidirectional = false; return;}
  if (strcmp(s, "up")==0)
    {fDirection = up; fBidirectional = false; return;}
  if (strcmp(s,"change")== 0)
    {fBidirectional = !fBidirectional; return;}
  if (strcmp(s,"bi-directional")== 0)
    {fBidirectional = true; return;}
  if (strcmp(s,"unidirectional")== 0)
    {fBidirectional = false; return;}
  
}
//***************************************************************************
//***************************************************************************

void Counter::SetCount(int iNewCount)
{
  iCount = iNewCount;
  if  ((iNewCount > iUpperLimit) || (iNewCount < iLowerLimit))
    { // outside counter limit
      if (iNewCount > iUpperLimit)
	iUpperLimit = iNewCount;
      else
	iLowerLimit = iNewCount;
    }
  fPreviouslyCounted = false;
}

void Counter::SetResetCount(int iNewCount)
{
  iResetCount = iNewCount;
  if  ((iNewCount > iResetUpperLimit) || (iNewCount < iLowerLimit))
    { // outside counter limit
      if (iNewCount > iResetUpperLimit)
	{
	  if(iResetUpperLimit == iNewCount)
	    return;
	  iResetUpperLimit = iNewCount;
	}
      else
	{
	  if(iResetLowerLimit == iNewCount)
	    return;
	  
	  iResetLowerLimit = iNewCount;
	}
      SetModified(true);
    }
}


inline void Counter::OverFlow (){OVERFLOW_OUT->ProduceOutput();}

inline void Counter::UnderFlow (){UNDERFLOW_OUT->ProduceOutput();}


BaseShell* Counter::Create(Patch* Parent)
{
  return new Counter(Parent);
}




void Counter::SetResetDirection (int NewDirection)
{
  if(fResetDirection == (NewDirection))
    return;
  fResetDirection = (NewDirection);
  SetModified(true);
}

void Counter::SetResetBidirectional(int fBidirectional)
{
  if(fResetBidirectional == (fBidirectional))
    return;
  fResetBidirectional = (fBidirectional);
  SetModified(true);
}

void Counter::SetResetStepSize(int Size)
{
  if(iResetStepSize == Size)
    return;
  iResetStepSize = Size;
  SetModified(true);
}

void Counter::Send()
{
  COUNT_OUT->ProduceOutput(iCount);
}



const Counter::str_access Counter::aAccess[NumAccess] =
{
  {"Count", &Counter::Count, &Counter::Count},
  {"StepSize", &Counter::StepSize, &Counter::StepSize},
  {"LowerLimit", &Counter::LowerLimit, &Counter::LowerLimit},
  {"UpperLimit", &Counter::UpperLimit, &Counter::UpperLimit},
  {"Direction", &Counter::Direction, &Counter::Direction},
  {"Bidirectional", &Counter::Bidirectional, &Counter::Bidirectional}
  
};


const char* Counter::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool Counter::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool Counter::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}
// reset

const Counter::str_access Counter::aResetAccess[NumResetAccess] =
{
  {"ResetCount", &Counter::ResetCount, &Counter::ResetCount},
  {"ResetStepSize", &Counter::ResetStepSize, &Counter::ResetStepSize},
  {"ResetLowerLimit", &Counter::ResetLowerLimit, &Counter::ResetLowerLimit},
  {"ResetUpperLimit", &Counter::ResetUpperLimit, &Counter::ResetUpperLimit},
  {"ResetDirection", &Counter::ResetDirection, &Counter::ResetDirection},
  {"ResetBidirectional", &Counter::ResetBidirectional, &Counter::ResetBidirectional}
  
};


const char* Counter::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool Counter::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool Counter::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool Counter::Count (char* ret, unsigned ret_size) const 
{
	return SMUtility::IntToStr (GetCount(), ret, ret_size);
}

bool Counter::StepSize (char* ret, unsigned ret_size) const 
{
	return SMUtility::IntToStr (GetStepSize (), ret, ret_size);
}

bool Counter::LowerLimit (char* ret, unsigned ret_size) const 
{
	return SMUtility::IntToStr (GetLowerLimit(), ret, ret_size);
}

bool Counter::UpperLimit (char* ret, unsigned ret_size) const 
{
	return SMUtility::IntToStr (GetUpperLimit(), ret, ret_size);
}

bool Counter::Direction (char* ret, unsigned ret_size) const 
{
	return SMUtility::IntToStr (GetDirection(), ret, ret_size);
}

bool Counter::Bidirectional (char* ret, unsigned ret_size)const 
{
	return SMUtility::IntToStr (GetBidirectional(), ret, ret_size);
}

bool Counter::ResetCount (char* ret, unsigned ret_size)const 
{
	return SMUtility::IntToStr (GetResetCount(), ret, ret_size);
}

bool Counter::ResetStepSize (char* ret, unsigned ret_size)const 
{
	return SMUtility::IntToStr (GetResetStepSize(), ret, ret_size);
}

bool Counter::ResetLowerLimit (char* ret, unsigned ret_size)const 
{
	return SMUtility::IntToStr (GetResetLowerLimit(), ret, ret_size);
}

bool Counter::ResetUpperLimit (char* ret, unsigned ret_size)const 
{
	return SMUtility::IntToStr (GetResetUpperLimit(), ret, ret_size);
}

bool Counter::ResetDirection (char* ret, unsigned ret_size)const 
{
	return SMUtility::IntToStr (GetResetDirection(), ret, ret_size);
}

bool Counter::ResetBidirectional (char* ret, unsigned ret_size)const 
{
	return SMUtility::IntToStr (GetResetBidirectional(), ret, ret_size);
}


bool Counter::Count (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetCount(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Counter::StepSize (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetStepSize(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Counter::LowerLimit (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetLowerLimit(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Counter::UpperLimit (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetUpperLimit(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Counter::Direction (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetDirection(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Counter::Bidirectional (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetBidirectional(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Counter::ResetCount (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetCount(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Counter::ResetStepSize (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetStepSize(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Counter::ResetLowerLimit (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetLowerLimit(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Counter::ResetUpperLimit (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetUpperLimit(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Counter::ResetDirection (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetDirection(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Counter::ResetBidirectional (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetBidirectional(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Counter::GetDefaultAttribute (char* ret_value, unsigned buff_len)const
{
  // return the operator and the right val;

  //first get the operator
  char buff [256];
  
  sprintf(buff, "c = %i, l = %i, h = %i", iCount, iLowerLimit, iUpperLimit);
  
  strncpy(ret_value, buff, buff_len - 1);
  ret_value[buff_len - 1] = 0;
  
  return true;
  
}
