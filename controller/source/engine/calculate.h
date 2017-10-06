// Object for performing calculations on two numbers
//   operations include +, -, *, / , %, &&, ||
#ifndef CALCULATE_H
#define CALCULATE_H


#include "estring.h"


class Calculate : public BaseShell
{
  friend class TypeList;
 public:
  enum {ADD, SUBTRACT, DIVIDE, MULTIPLY, MODULO, AND, OR, ARE_EQUAL, 
	ARE_NOT_EQUAL,	LESS, LESS_OR_EQUAL, GREATER, GREATER_OR_EQUAL, POW, SIN, COS, TAN, ARC_SIN, ARC_COS, ARC_TAN, LOG, LOG_10, EXP, MAX_OPERATORS};
  // enumerate access values
  enum {eNumOperators, eLValue, eOperator, eRValue,  eMaxAttribute};
	
	//enumerate reset attributes
	enum {eResetLValue, eResetOperator,	eResetRValue, eRTriggerCalc, eMaxResetAttribute};

  Calculate (Patch*, const char* Name = "", const char* = "",
	     double LValue = 0, double RValue = 0, int Operand = 0, bool Trigger = false);
  
  ~Calculate(){}
  
  static BaseShell* Create(Patch*);
  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  
  const char* GetType()const {return szType;}
  void IntInlet(unsigned, int);
  void StringInlet(unsigned, const char*);
  void DoubleInlet(unsigned InletNumber, double d);
  void Reset ();
  
  void SetLValue (int NewInt){SetLValue((double)NewInt);}
  void SetLValue (double val){dLValue = val;}
  
  void SetRValue (int NewInt){SetRValue((double)NewInt);}
  void SetRValue (double val){dRValue = val;}
  
  void SetResetLValue (double val);
  void SetResetRValue (double val);
  
  void SetOperator(double NewOperator){SetOperator((int)NewOperator);}
  void SetOperator(int NewOperator){iOperator = NewOperator;}
  void SetOperator(const char* NewOperator);
  void SetResetOperator(const char* NewOperator);
  void SetResetOperator(int NewOperator);
  int GetOperator()const{return iOperator;}
  int GetResetOperator()const {return iResetOperator;}
  
  double GetLeftValue ()const {return dLValue;}
  double GetRightValue ()const {return dRValue;}
  double GetResetLValue ()const {return dResetLValue;}
  double GetResetRValue ()const {return dResetRValue;}
  int GetRTriggerCalc()const {return fRightTriggerCalc;}
  void SetRTriggerCalc(int f){fRightTriggerCalc = (f);}
  void CalculateValues()const;
  
	void DoDefaultAction(){CalculateValues();}
  int NumOperators()const {return wNumOperators;}
  
  static unsigned GetNumOperators() {return wNumOperators;}
  static const char* GetOperator(int);

  static const unsigned wNumOperators;
	const BaseShell* GetReference() const;

 private:
  static const char*const szType;
  
  double dLValue, dRValue;
  double dResetLValue, dResetRValue;
  int iResetOperator, iOperator;
  
  //if true, a message into the right operand inlet will
  //trigger a calculation, otherwise only the left operand
  //will trigger calculation
  bool fRightTriggerCalc;
  
  double Multiply ()const {return dLValue * dRValue;}
  double Divide ()const;
  int Modulo ()const;
  double Add ()const {return dLValue + dRValue;}
  double Subtract()const {return dLValue - dRValue;}
  double And ()const {return ((int)dLValue) & ((int)dRValue);}
  double Or () const {return ((int)dLValue) | ((int)dRValue);}
  bool IsEqual() const {return dLValue == dRValue;}
  bool IsLess() const {return dLValue < dRValue;}
  bool IsGreater() const {return dLValue > dRValue;}
  
  double Sin()const;
  double Cos()const;
  double Tan()const;
  double ArcSin()const;
  double ArcCos()const;
  double ArcTan()const;  
  
  double Log()const;
  double Log10()const;
  double Exp()const;
  double Pow()const;  

  double radian(double angle)const {return angle * 3.14159265 / 180;}
  double degree(double rad)const {return rad * 180 / 3.14159265;}
  
  void OperandInlet(const char*);
  
  typedef void(Calculate::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];
  
  
  typedef void(Calculate::*pStringFunc)(const char*);
  static const pStringFunc tpStringFunc[];
  
  typedef void(Calculate::*pDoubleFunc)( double);
  static const pDoubleFunc tpDoubleFunc[];
  
  // access functions
	static const unsigned NumAccess;
	static const unsigned NumResetAccess;
	typedef bool (Calculate::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (Calculate::*pSetFunc)(const char* new_value);
	typedef struct
	{
		const char* access_name;
		pGetFunc get_func;
		pSetFunc set_func;
	} str_access;

  static const str_access aAccess[];
  unsigned GetNumAccess ()const {return NumAccess;}
  const char* GetAccessName (unsigned index)const;

  bool SetAttribute (unsigned index, const char* value);
  bool GetAttribute (unsigned index, char* ret_value, unsigned buf_size) const;
  bool GetDefaultAttribute (char* ret_value, unsigned buff_len)const;

  static const str_access aResetAccess[];
  unsigned GetNumResetAccess ()const {return NumResetAccess;}
  const char* GetResetAccessName (unsigned index)const;

  bool SetResetAttribute (unsigned index, const char* value);
  bool GetResetAttribute (unsigned index, char* ret_value, unsigned buf_size) const;

  bool NumOperators (char* ret, unsigned ret_size) const;
  bool LeftValue (char* ret, unsigned ret_size) const;
  bool Operator (char* ret, unsigned ret_size) const;
  bool RightValue (char* ret, unsigned ret_size) const;
  bool ResetLValue (char* ret, unsigned ret_size) const;
  bool ResetOperator (char* ret, unsigned ret_size) const;
  bool ResetRValue (char* ret, unsigned ret_size) const;
  bool RightTriggerCalc (char* ret, unsigned ret_size) const;

  bool LeftValue  (const char* new_val);
  bool Operator  (const char* new_val);
  bool RightValue  (const char* new_val);
  bool ResetLValue  (const char* new_val);
  bool ResetOperator  (const char* new_val);
  bool ResetRValue  (const char* new_val);
  bool RightTriggerCalc  (const char* new_val);

  // arrays to get names of inlets and outlets
  static  const char*const szaInletDetails[];
  static  const char*const szaOutletDetails[];
  
};

#endif







