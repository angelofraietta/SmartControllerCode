#ifndef TOGGLE_H
#define TOGGLE_H


class Toggle: public BaseShell
{
  friend class TypeList;
 public:
  enum {eState, eMaxAttribute};
	enum {eResetState, eMaxResetAttribute};
  
  Toggle(Patch* = NULL, const char* Name = "",
	 const char* Comment = "", bool Status = false);
  
  ~Toggle(){};
  void VoidInlet(unsigned);
  void IntInlet(unsigned, int);
  void StringInlet(unsigned, const char*);
  static BaseShell* Create(Patch*);

  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  
  void Reset() {State = ResetState;}
  void SetState(int f){State = (f);}
  void SetResetState(int f);
  int GetState()const{return State?1:0;}
  int GetResetState()const{return ResetState?1:0;}
  const char* GetType()const {return szType;}
  
	void DoDefaultAction(){State = !State; Send();};
  void Send();
	const BaseShell* GetReference() const;

 private:
  bool State, ResetState;//ie. reset performance state
  
  void ChangeState(){State = !State;}
  static const char*const szType;
  
  // arrays to get names of inlets and outlets
  static  const char*const szaInletDetails;
  static  const char*const szaOutletDetails;

  
  // access functions
	static const unsigned NumAccess;
	typedef bool (Toggle::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (Toggle::*pSetFunc)(const char* new_value);
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
  
	bool GetState (char* ret, unsigned ret_size) const;
	bool GetResetState (char* ret, unsigned ret_size) const;

	bool SetState (const char* new_val);
	bool SetResetState (const char* new_val);


	bool GetDefaultAttribute (char* buf, unsigned buf_len)const;
	bool SetDefaultAttribute (const char* new_value);

};

#endif

