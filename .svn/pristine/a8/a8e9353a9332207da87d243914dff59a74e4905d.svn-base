/***************************************************************
Number abstract data type
****************************************************************/
#ifndef NUMBER_H
#define NUMBER_H


class NumberStore :public BaseShell
{
  friend class TypeList;
 public:
  enum{eValue, eMaxAttribute};
	enum {eResetValue, eLowerLimit, eUpperLimit, eMaxResetAttribute};

  static BaseShell* Create(Patch* );
  
  NumberStore (Patch*,
	       const char* Name = "",
	       const char* Comment = "",
	       int LowerLimit = 0,
	       int UpperLimit = 127,
	       int Number = 0); // default constructor) // default constructor
  
  virtual ~NumberStore ();
  
  void VoidInlet (unsigned);
  void IntInlet(unsigned, int);
  
  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  const char* GetType()const{return szType;}
  void	Reset(); // load initial conditions into current conditions
  
  //set properties
  void SetUpperLimit (int NewLimit);
  void SetLowerLimit(int NewLimit);
  
  void  SetNumber (int);
  void SetResetNumber(int);
  int GetNumber()const {return iNumber;}
  int GetUpperLimit()const {return iUpperLimit;}
  int GetLowerLimit()const {return iLowerLimit;}
  int GetResetNumber()const {return iResetNumber;}
  void Send();
  void NumberInlet(int i);
	const BaseShell* GetReference() const;
	void DoDefaultAction(){Send();}

 private:
  int	iResetNumber, iNumber;
  int   iUpperLimit;  	// the upper limit
  int   iLowerLimit;  	// the lower limit
  
  bool SetPerformanceNumber (int i);
  static const char*const szType;
  
  //IntInlet function table
  typedef void(NumberStore::*pVoidFunc)();
  static const pVoidFunc tpVoidFunc[];
  
  typedef void(NumberStore::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];
  
  typedef void(NumberStore::*pStringFunc)(const char*);
  static const pStringFunc tpStringFunc[];
  
  // arrays to get names of inlets and outlets
  static const char*const szaInletDetails[];
  static const char*const szaOutletDetails[];

  void StringInlet1(const char*);

  
  // access functions
	static const unsigned NumAccess;
	typedef bool (NumberStore::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (NumberStore::*pSetFunc)(const char* new_value);
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

  bool Number (char* ret, unsigned ret_size) const;
  bool ResetNumber (char* ret, unsigned ret_size) const;
  bool LowerLimit (char* ret, unsigned ret_size) const;
  bool UpperLimit (char* ret, unsigned ret_size) const;

  bool Number (const char* new_val);
  bool ResetNumber (const char* new_val);
  bool LowerLimit (const char* new_val);
  bool UpperLimit (const char* new_val);

};
#endif


