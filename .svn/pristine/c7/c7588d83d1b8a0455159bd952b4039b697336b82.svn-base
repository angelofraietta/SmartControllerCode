// Object for selecting int messages between two values

#ifndef SELECTOR_H
#define SELECTOR_H

class Selector : public BaseShell
{
  friend class TypeList;
 public:
  enum {eLowerLimit, eUpperLimit, eMaxAttribute};
	enum {eResetLowerLimit, eResetUpperLimit, eMaxResetAttribute};

  Selector (Patch*, const char* Name = "", const char* = "",
	    double LValue = 0, double RValue = 0);
  ~Selector(){}

  static BaseShell* Create(Patch*);

  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;

  const char* GetType()const {return szType;}
  void VoidInlet(unsigned);
  void IntInlet(unsigned, int);
  void StringInlet(unsigned, const char*);
  void DoubleInlet(unsigned, double);
  void Reset ();

  void SetLowerValue (int NewInt){SetLowerValue((double)NewInt);}
  void SetLowerValue (double NewInt){iLowerValue = NewInt;}

  void SetUpperValue (int NewInt){SetUpperValue((double)NewInt);}
  void SetUpperValue (double NewInt){iUpperValue = NewInt;}

  void SetResetLowerValue (int NewInt){SetResetLowerValue((double)NewInt);}
  void SetResetLowerValue (double NewInt);

  void SetResetUpperValue (double NewInt);
  void SetResetUpperValue (int NewInt){SetResetUpperValue((double)NewInt);}

  double GetLowerValue ()const {return iLowerValue;}
  double GetUpperValue ()const {return iUpperValue;}
  double GetResetLowerValue ()const {return iResetLowerValue;}
  double GetResetUpperValue ()const {return iResetUpperValue;}

	const BaseShell* GetReference() const;
 private:
  static const char*const szType;
  double iResetLowerValue, iResetUpperValue, iLowerValue,iUpperValue;

  void Filter(double);
  void Filter(int val) {Filter ((double)val);}

  typedef void(Selector::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];


  typedef void(Selector::*pDoubleFunc)( double);
  static const pDoubleFunc tpDoubleFunc[];

  // arrays to get names of inlets and outlets
  static  const char*const szaInletDetails[];
  static  const char*const szaOutletDetails[];

  // access functions
	static const unsigned NumAccess;
	typedef bool (Selector::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (Selector::*pSetFunc)(const char* new_value);
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
  bool GetAttribute (unsigned index, char* ret_value, unsigned buf_size)const;

	static const unsigned NumResetAccess;
  static const str_access aResetAccess[];
  unsigned GetNumResetAccess ()const {return NumResetAccess;}
  const char* GetResetAccessName (unsigned index)const;

  bool SetResetAttribute (unsigned index, const char* value);
  bool GetResetAttribute (unsigned index, char* ret_value, unsigned buf_size) const;

	bool LowerValue (char* ret, unsigned ret_size) const;
  bool UpperValue (char* ret, unsigned ret_size) const;
	bool ResetLowerValue (char* ret, unsigned ret_size) const;
  bool ResetUpperValue (char* ret, unsigned ret_size) const;

	bool LowerValue (const char* new_val);
  bool UpperValue (const char* new_val);
	bool ResetLowerValue (const char* new_val);
  bool ResetUpperValue (const char* new_val);

};





#endif
