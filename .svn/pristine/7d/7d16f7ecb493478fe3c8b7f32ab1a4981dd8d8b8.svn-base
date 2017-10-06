
#ifndef FLIP_FLOP
#define FLIP_FLOP

class FlipFlop: public BaseShell
{
  friend class TypeList;
 public:
  enum {eState, eMaxAttribute};
	enum {eResetState, eMaxResetAttribute};
 
  FlipFlop(Patch* = NULL, const char* Name = "",
	   const char* Comment = "", bool Status = false);
  
  ~FlipFlop(){};
  void VoidInlet(unsigned);
  void IntInlet(unsigned, int);
  void StringInlet(unsigned, const char*);
  static BaseShell* Create(Patch*);

  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  
  void Reset() {_State = _ResetState;}
  void SetState(int f){_State = (f);}
  void SetResetState(int f);
  int GetState()const{return _State?1:0;}
  int GetResetState()const{return _ResetState?1:0;}
  const char* GetType()const {return szType;}
  
  //inputs of FlipFlop
  void SetFlipFlop();
  void SetFlipFlop(int i);
  void ClearFlipFlop();
  void ClearFlipFlop(int i);
	void DoDefaultAction();  
  void Send();
	const BaseShell* GetReference() const;

 private:
  bool _State:1, _ResetState:1;//ie. reset performance state

  typedef void(FlipFlop::*pVoidFunc)();
  static const pVoidFunc tpVoidFunc[];
  
  typedef void(FlipFlop::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];
  static const char*const szType;
  
  // arrays to get names of inlets and outlets
  static  const char*const szaInletDetails[];
  static  const char*const szaOutletDetails[];


  // access functions
	static const unsigned NumAccess;
	typedef bool (FlipFlop::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (FlipFlop::*pSetFunc)(const char* new_value);
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

	bool State (char* ret, unsigned ret_size) const;
	bool ResetState (char* ret, unsigned ret_size) const;
 
	bool State(const char* new_val);
	bool ResetState (const char* new_val);
 
};

#endif

