/***************************************************************
Random abstract data type
****************************************************************/
#ifndef RANDOM_H
#define RANDOM_H


class RandomGen :public BaseShell
{
  friend class TypeList;
 public:
  enum {eNumber, eUpperLimit, eMaxAttribute};
	enum {eResetUpperLimit, eMaxResetAttribute};

  static BaseShell* Create(Patch* );


  RandomGen (Patch*,
             const char* Name = "",
             const char* Comment = "",
             int UpperLimit = 127); // default constructor) // default constructor
  
  virtual ~RandomGen ();
  
  void VoidInlet (unsigned);
  void IntInlet(unsigned, int);
  void StringInlet(unsigned, const char*);
  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  const char* GetType()const{return szType;}
  void	Reset(); // load initial conditions into current conditions
  
  //set properties
  void SetUpperLimit (int NewLimit);
  void SetResetUpperLimit(int NewLimit);
  
  void  SetNumber (int);
  int GetNumber()const {return iNumber;}
  int GetUpperLimit()const {return iUpperLimit;}
  int GetResetUpperLimit()const {return iResetUpperLimit;}
  void OutputNumber();
  void Generate();
  void Send();
	const BaseShell* GetReference() const;
	void DoDefaultAction(){Generate(); Send();}

 private:
  int	iNumber;
  int   iUpperLimit, iResetUpperLimit;  	// the upper limit
  
  static const char*const szType;
  
  //IntInlet function table
  typedef void(RandomGen::*pVoidFunc)();
  static const pVoidFunc tpVoidFunc[];
  
  typedef void(RandomGen::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];
  
  typedef void(RandomGen::*pStringFunc)(const char*);
  static const pStringFunc tpStringFunc[];
  
  // arrays to get names of inlets and outlets
  static const char*const szaInletDetails[];
  static const char*const szaOutletDetails[];
  
  
  // access functions
	static const unsigned NumAccess;
	typedef bool (RandomGen::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (RandomGen::*pSetFunc)(const char* new_value);
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
  bool UpperLimit (char* ret, unsigned ret_size) const;
  bool ResetUpperLimit (char* ret, unsigned ret_size) const;

  bool Number (const char* new_val);
  bool UpperLimit (const char* new_val);
  bool ResetUpperLimit (const char* new_val);

};
#endif
