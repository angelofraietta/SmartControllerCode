// Creates an object that performs operations on two numbers
// based on Calculate Class
#include "stdafx.h"
#include "control.h"
#include "calculate.h"
#include "typenames.h"
#include <math.h>

#define NUM_INLETS 3
#define NUM_OUTLETS 1



const char*const Calculate::szType = CALCULATE_TYPE;
const unsigned Calculate::wNumOperators = Calculate::MAX_OPERATORS;
const unsigned Calculate::NumAccess = Calculate::eMaxAttribute;
const unsigned Calculate::NumResetAccess = Calculate::eMaxResetAttribute;


// create the default
static Calculate *reference = new Calculate (NULL);

const BaseShell* Calculate::GetReference() const
{
	return reference;
}                                                  


typedef struct 
{
  int value;
  const char* name;
}str_name_map;

static const str_name_map OperatorMap [Calculate::wNumOperators] =
{
  {Calculate::ADD, "+"},
  {Calculate::SUBTRACT, "-"},
  {Calculate::DIVIDE,     "/"},
  {Calculate::MULTIPLY, "*"},
  {Calculate::MODULO, "%"},
  {Calculate::AND, "&"},
  {Calculate::OR, "|"},
  {Calculate::ARE_EQUAL, "=="},
  {Calculate::ARE_NOT_EQUAL, "!="},
  {Calculate::LESS, "<"},
  {Calculate::LESS_OR_EQUAL, "<="},
  {Calculate::GREATER, ">"},
  {Calculate::GREATER_OR_EQUAL, ">="},
  {Calculate::POW, "Pow"},
  
  {Calculate::SIN, "Sin"},
  {Calculate::COS, "Cos"},
  {Calculate::TAN, "Tan"},
  {Calculate::ARC_SIN, "aSin"},
  {Calculate::ARC_COS, "aCos"},
  {Calculate::ARC_TAN, "aTan"},
  
  {Calculate::LOG, "Log"},
  {Calculate::LOG_10, "Log10"},
  {Calculate::EXP, "Exp"}
  
};

const char* Calculate::GetOperator(int Op)
{
  const char* ret = NULL;
  if ((unsigned)Op < wNumOperators)
    {
      ret = OperatorMap [Op].name;
    }
  return ret;
}

const Calculate::pIntFunc  Calculate::tpIntFunc [NUM_INLETS] = {
  &Calculate::SetLValue,
  &Calculate::SetOperator,
  &Calculate::SetRValue
};

const Calculate::pStringFunc  Calculate::tpStringFunc [NUM_INLETS] = {
  &Calculate::OperandInlet,
  &Calculate::SetOperator,
  &Calculate::OperandInlet
};

const Calculate::pDoubleFunc  Calculate::tpDoubleFunc [] = {
  &Calculate::SetLValue,
  &Calculate::SetOperator,
  &Calculate::SetRValue
};


const char*const Calculate::szaInletDetails[NUM_INLETS] = {
  "Left Operand",
  "Operator",
  "Right Operand"
};

const char*const Calculate::szaOutletDetails[NUM_OUTLETS] = {
  "Calculate Result"
};

const char* Calculate::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}

const char* Calculate::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}

void Calculate::SetOperator(const char* Operator)
{
  bool found = false;
  for (unsigned i = 0; i < wNumOperators && !found; i++)
    {
      if (!strcmp(OperatorMap [i].name, Operator))
				{
					iOperator = OperatorMap[i].value;
					found = true;
				}
    }
}

void Calculate::SetResetOperator(const char* Operator)
{
  bool found = false;
  for (unsigned i = 0; i < wNumOperators && !found; i++)
    {
      if (!strcmp(OperatorMap [i].name, Operator))
				{
					iResetOperator = OperatorMap[i].value;
					found = true;
				}
    }
}

Calculate::Calculate (Patch* Parent, const char* Name,const char* Comment,
		      double LValue, double RValue, int Operator, bool Trigger)
  :BaseShell (Parent,NUM_INLETS, NUM_OUTLETS, Name, Comment),
   dResetLValue(LValue), dResetRValue(RValue), iResetOperator(Operator),
   fRightTriggerCalc(Trigger)
{
  Reset();
}



inline double Calculate::Divide ()const
{
  if (dRValue != 0) // prevent divide by zero
    return dLValue / dRValue;
  else
    Error (eDivideByZero, this);
  return -1;

}

inline int Calculate::Modulo ()const
{
  if (dRValue != 0) // prevent divide by zero
    return ((int)dLValue) % ((int)dRValue);
  else
    Error (eDivideByZero, this);
  return -1;
}

double Calculate::Sin()const
{
  double ret = sin(radian(dLValue));
  
  return ret;
}

double Calculate::Cos()const
{
  double ret = cos(radian(dLValue));
  
  return ret;  
}

double Calculate::Tan()const
{
  double ret = tan(radian(dLValue));
  
  return ret;  
}

double Calculate::ArcSin()const
{
  double ret = degree(asin(dLValue));
  
  
  return ret;  
}

double Calculate::ArcCos()const
{
  double ret = degree(acos(dLValue));
  
  return ret;  
}

double Calculate::ArcTan()const  
{
  double ret = degree(atan(dLValue));
  
  return ret;  
}

double Calculate::Log()const
{
  if (dLValue > 0)
  {
    return log(dLValue);
  }
  else
  {
    Error (eInvalidDataValue, this);
  }
  return -1;
}

double Calculate::Log10()const
{
  if (dLValue > 0)
  {
    return log10(dLValue);
  }
  else
  {
    Error (eInvalidDataValue, this);
  }
  return -1;

}
double Calculate::Exp()const
{
  return exp(dLValue);
  

}

double Calculate::Pow()const
{
  double ret = 0;
    
  try
  {
    if (dLValue != 0)
    {
        ret = pow(dLValue, dRValue);
    }
    else
    {
      Error (eInvalidDataValue, this);
    }

    }
    catch (...)
    {
      Error (eInvalidDataValue, this);

    }
  return ret;
}
  
void Calculate::Reset ()
{
  dLValue = dResetLValue;
  dRValue = dResetRValue;
  iOperator = iResetOperator;
}

BaseShell* Calculate::Create(Patch* Parent)
{
  return new Calculate(Parent);
}



void Calculate::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    {
      (this->*tpIntFunc[InletNumber])(i);
      if ((InletNumber == 0)||
	  (fRightTriggerCalc &&(InletNumber == 2)))
    CalculateValues();
    }
}

void Calculate::DoubleInlet(unsigned InletNumber, double d)
  {
  if ((InletNumber < GetNumInlets())&& (tpDoubleFunc[InletNumber]))
    {
      (this->*tpDoubleFunc[InletNumber])(d);
      if ((InletNumber == 0)||
	  (fRightTriggerCalc &&(InletNumber == 2)))
    CalculateValues();
    }
  }

void Calculate::CalculateValues()const
{
  switch(iOperator){
  case ADD: tpOutlet[0]->ProduceOutput(Add());
    break;
  case SUBTRACT: tpOutlet[0]->ProduceOutput(Subtract());
    break;
  case MULTIPLY: tpOutlet[0]->ProduceOutput(Multiply());
    break;
  case DIVIDE: tpOutlet[0]->ProduceOutput(Divide());
    break;
  case MODULO: tpOutlet[0]->ProduceOutput(Modulo());
    break;
  case AND: tpOutlet[0]->ProduceOutput(And());
    break;
  case OR: tpOutlet[0]->ProduceOutput(Or());
    break;
  case ARE_EQUAL: tpOutlet[0]->ProduceOutput((int)IsEqual());
    break;
  case ARE_NOT_EQUAL: tpOutlet[0]->ProduceOutput((int)!IsEqual());
    break;
  case LESS: tpOutlet[0]->ProduceOutput((int)IsLess());
    break;
  case LESS_OR_EQUAL: tpOutlet[0]->ProduceOutput((int)(IsLess() || IsEqual()));
    break;
  case GREATER: tpOutlet[0]->ProduceOutput((int)IsGreater());
    break;
  case GREATER_OR_EQUAL: tpOutlet[0]->ProduceOutput((int)(IsGreater() || IsEqual()));
  
  case SIN: tpOutlet[0]->ProduceOutput(Sin());
    break;

  case COS: tpOutlet[0]->ProduceOutput(Cos());
    break;
    
  case TAN: tpOutlet[0]->ProduceOutput(Tan());
    break;
    
  case ARC_SIN: tpOutlet[0]->ProduceOutput(ArcSin());
    break;

  case ARC_COS: tpOutlet[0]->ProduceOutput(ArcCos());
    break;
    
  case ARC_TAN: tpOutlet[0]->ProduceOutput(ArcTan());
    break;
    
  case LOG: tpOutlet[0]->ProduceOutput(Log());
    break;

  case LOG_10: tpOutlet[0]->ProduceOutput(Log10());
    break;

  case EXP: tpOutlet[0]->ProduceOutput(Exp());
    break;

  case POW: tpOutlet[0]->ProduceOutput(Pow());
    break;

    
        
          
    break;
  default: break;
  };
}
void Calculate::StringInlet(unsigned InletNumber, const char* s)
{
  if ((InletNumber < GetNumInlets())&&(tpStringFunc[InletNumber]))
    (this->*tpStringFunc[InletNumber])(s);
}

void Calculate::OperandInlet(const char* s)
{
  if (!strcmp(s, "reset"))
    {Reset(); return;}
  if (!strcmp(s, "calculate"))
    {CalculateValues(); return;}
}

void Calculate::SetResetLValue (double val)
{
  if(dResetLValue == val)
    return;
  dResetLValue = val;
  SetModified(true);
}

void Calculate::SetResetRValue (double val)
{
  if(dResetRValue == val)
    return;
  dResetRValue = val;
  SetModified(true);
}

void Calculate::SetResetOperator(int NewOperator)
{
  if(iResetOperator == NewOperator)
    return;
  iResetOperator = NewOperator;
  SetModified(true);
}


const Calculate::str_access Calculate::aAccess[NumAccess] =
{
  {"NumOperators", &Calculate::NumOperators, NULL},
  {"LeftValue", &Calculate::LeftValue, &Calculate::LeftValue},
  {"Operator", &Calculate::Operator, &Calculate::Operator},
  {"RightValue", &Calculate::RightValue, &Calculate::RightValue}
};

const char* Calculate::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool Calculate::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool Calculate::GetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}

// reset attributes

const Calculate::str_access Calculate::aResetAccess[NumResetAccess] =
{
  {"ResetLValue", &Calculate::ResetLValue, &Calculate::ResetLValue},
  {"ResetOperator", &Calculate::ResetOperator, &Calculate::ResetOperator},
  {"ResetRValue", &Calculate::ResetRValue, &Calculate::ResetRValue},
  {"RightTriggerCalc", &Calculate::RightTriggerCalc, &Calculate::RightTriggerCalc}
};

const char* Calculate::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool Calculate::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool Calculate::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool Calculate::NumOperators (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (wNumOperators, ret, ret_size);
}

bool Calculate::LeftValue (char* ret, unsigned ret_size) const
{
	return SMUtility::FltToStr (dLValue, ret, ret_size);
}

bool Calculate::Operator (char* ret, unsigned ret_size) const
{
	bool success = false;

	if (iOperator < wNumOperators)
		{
			strncpy (ret, GetOperator(iOperator), ret_size);
			ret [ret_size -1] = '\0';
			success = true;
		}
	return success;
}

bool Calculate::RightValue (char* ret, unsigned ret_size) const
{
	return SMUtility::FltToStr (dRValue, ret, ret_size);
}

bool Calculate::ResetLValue (char* ret, unsigned ret_size) const
{
	return SMUtility::FltToStr (dResetLValue, ret, ret_size);
}

bool Calculate::ResetOperator (char* ret, unsigned ret_size) const
{
	bool success = false;

	if (iResetOperator < wNumOperators)
		{
			strncpy (ret, GetOperator(iResetOperator), ret_size);
			ret [ret_size -1] = '\0';
			success = true;
		}
	return success;

}

bool Calculate::ResetRValue (char* ret, unsigned ret_size) const
{
	return SMUtility::FltToStr (dResetRValue, ret, ret_size);
}

bool Calculate::RightTriggerCalc (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetRTriggerCalc(), ret, ret_size);
}


bool Calculate::LeftValue  (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			SetLValue(SMUtility::StrToFlt(new_val));
			ret = true;
		}
	return ret;
}

bool Calculate::Operator  (const char* new_val)
{
	if (SMUtility::IsInt(new_val))
		{
			SetOperator(SMUtility::StrToInt(new_val));
		}
	else
		{
			SetOperator (new_val);
		}
	return true;
}

bool Calculate::RightValue  (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			SetRValue(SMUtility::StrToFlt(new_val));
			ret = true;
		}
	return ret;
}

bool Calculate::ResetLValue  (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			SetResetLValue(SMUtility::StrToFlt(new_val));
			ret = true;
		}
	return ret;
}

bool Calculate::ResetOperator  (const char* new_val)
{
	if (SMUtility::IsInt(new_val))
		{
			SetResetOperator(SMUtility::StrToInt(new_val));
		}
	else
		{
			SetResetOperator(new_val);
		}
	return true;
}

bool Calculate::ResetRValue  (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			SetResetRValue(SMUtility::StrToFlt(new_val));
			ret = true;
		}
	return ret;
}

bool Calculate::RightTriggerCalc  (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetRTriggerCalc(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Calculate::GetDefaultAttribute (char* ret_value, unsigned buff_len)const
{
  // return the operator and the right val;

  //first get the operator
  bool ret = Operator(ret_value, buff_len);

  
  // first put the
  if (ret && iOperator <= Calculate::POW)
  {
    unsigned new_start = strlen(ret_value);
    buff_len -= new_start;

    if (buff_len > 2)
    {
       ret_value [new_start] = ' '; // place a SPACE IN
       ret = RightValue ( ret_value + new_start + 1, buff_len -1);
    }


  }

  return ret;
}
