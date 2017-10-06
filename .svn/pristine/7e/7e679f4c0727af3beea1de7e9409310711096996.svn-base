/***************************************************************
Counter abstract data type
****************************************************************/
#ifndef COUNTER_H
#define COUNTER_H


class Counter :public BaseShell
{
  friend class TypeList;
  enum  {up, down}; // the possible directions to count
 public:
  enum {eCount, eStepSize, eLowerLimit, eUpperLimit, eDirection, eBidirectional, eMaxAttribute};
	enum {eResetCount, eResetStepSize, eResetLowerLimit, eResetUpperLimit, eResetDirection, eResetBidirectional, eMaxResetAttribute};

  static BaseShell* Create(Patch* );
  
  Counter (Patch*,
	   const char* Name = "",
	   const char* Comment = "",
	   int LowerLimit = 0,
	   int UpperLimit = 127,
	   bool CountDirection = (bool)up,
	   bool Bidirectional = false,
	   int StepSize = 1,
	   int Count = 0); // default constructor) // default constructor
  
  virtual ~Counter ();
  
  void VoidInlet (unsigned);
  void IntInlet(unsigned, int);
  void StringInlet(unsigned, const char*);
  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  const char* GetType()const{return szType;}
  void	Reset(); // load initial conditions into current conditions
  
  //set reset counter properties
  void SetResetCount(int);
  void	SetResetUpperLimit (int NewLimit);
  void	SetResetLowerLimit(int NewLimit);
  
  void SetResetStepSize(int NewSize);
  
  void SetResetDirection (int NewDirection);
  
  
  void SetResetBidirectional(int fBidirectional);
  
  //set current counter properties
  void SetUpperLimit(){iCount = iUpperLimit;}
  void SetUpperLimit (int NewLimit);
  void SetUpperLimit (const char*);
  void SetLowerLimit (){iCount = iLowerLimit;}
  void SetLowerLimit(int NewLimit);
  void SetLowerLimit (const char*);
  void SetStepSize(int NewSize)  {iStepSize = NewSize;}
  void SetStepSize(const char* s);
  
  void SetDirection (int NewDirection){fDirection = (NewDirection);}
  void SetDirection(const char*);
  void SetBidirectional(int Bidirectional){fBidirectional = (Bidirectional);}
  void SetBidirectional(const char*);
  void  ChangeDirection() {fDirection = !fDirection;} // change direction of counter
  void ChangeBidirectional(){fBidirectional = !fBidirectional;}
  void  SetCount (int); // Load new count forced between limits
  int GetCount()const {return iCount;}
  int GetUpperLimit()const {return iUpperLimit;}
  int GetLowerLimit()const {return iLowerLimit;}
  int GetStepSize ()const {return iStepSize;}
  int GetDirection()const {return (fDirection)?1:0;}
  int GetBidirectional()const {return (fBidirectional)?1:0;}
  int GetResetCount()const {return iResetCount;}
  int GetResetUpperLimit()const {return iResetUpperLimit;}
  int GetResetLowerLimit()const {return iResetLowerLimit;}
  int GetResetStepSize ()const {return iResetStepSize;}
  int GetResetDirection()const {return (fResetDirection)?1:0;}
  int GetResetBidirectional()const {return (fResetBidirectional)?1: 0;}
  void Send();
	void DoDefaultAction(){Count();}
 	const BaseShell* GetReference() const;
  bool GetDefaultAttribute (char* ret_value, unsigned buff_len)const;
 private:
  bool	fDirection:1;		// the current direction to count
  bool fResetDirection:1;		// the Reset direction to count  
  bool	fResetBidirectional:1;		// is bidirectional on reset
  bool	fBidirectional:1;	// is it an up/down counter
  
  bool  fPreviouslyCounted:1;   // false if counter has previously counted
  
  int   iResetUpperLimit;  	// the Reset upper limit
  int   iResetLowerLimit;  	// the Reset lower limit
  int   iResetStepSize;		// the Reset step size
  int	iResetCount;			// the Reset count
  
  int	iCount;			// the current count
  int   iLowerLimit;  	// the lower limit
  int   iUpperLimit;  	// the upper limit

  int   iStepSize;		// the size counted
  
  static const char*const szType;
  
  
  //IntInlet function table
  typedef void(Counter::*pVoidFunc)();
  static const pVoidFunc tpVoidFunc[];
  
  typedef void(Counter::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];
  
  typedef void(Counter::*pStringFunc)(const char*);
  static const pStringFunc tpStringFunc[];
  
  // arrays to get names of inlets and outlets
  static const char*const szaInletDetails[];
  static const char*const szaOutletDetails[];

  
  // access functions
	static const unsigned NumAccess;
	typedef bool (Counter::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (Counter::*pSetFunc)(const char* new_value);
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

	bool Count (char* ret, unsigned ret_size) const;
  bool StepSize (char* ret, unsigned ret_size) const;
  bool LowerLimit (char* ret, unsigned ret_size) const;
  bool UpperLimit (char* ret, unsigned ret_size) const;
  bool Direction (char* ret, unsigned ret_size) const;
  bool Bidirectional (char* ret, unsigned ret_size)const;
  bool ResetCount (char* ret, unsigned ret_size)const;
  bool ResetStepSize (char* ret, unsigned ret_size)const;
  bool ResetLowerLimit (char* ret, unsigned ret_size)const;
  bool ResetUpperLimit (char* ret, unsigned ret_size)const;
  bool ResetDirection (char* ret, unsigned ret_size)const;
  bool ResetBidirectional (char* ret, unsigned ret_size)const;

	bool Count (const char* new_val);
  bool StepSize (const char* new_val);
  bool LowerLimit (const char* new_val);
  bool UpperLimit (const char* new_val);
  bool Direction (const char* new_val);
  bool Bidirectional (const char* new_val);
  bool ResetCount (const char* new_val);
  bool ResetStepSize (const char* new_val);
  bool ResetLowerLimit (const char* new_val);
  bool ResetUpperLimit (const char* new_val);
  bool ResetDirection (const char* new_val);
  bool ResetBidirectional (const char* new_val);

  void OverFlow ();
  void UnderFlow ();
  
  //direction
  void	Count(); // step the counter
  void CountInlet(const char* s);
};
#endif

















