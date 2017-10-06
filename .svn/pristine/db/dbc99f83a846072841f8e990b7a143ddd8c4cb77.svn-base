//abstract Switch class from which switch types are derived
#ifndef SWITCH_H
#define SWITCH_H


class Switch :public BaseShell
{
 public:
  enum {eSwitchPosition, eMaxAttribute};
	enum {eNumContacts, eResetPosition, eMaxResetAttribute};
  Switch (Patch* Parent,
	  unsigned NumInlets,
	  unsigned NumOutlets,
	  const char* Name,
	  const char* Comment,
	  unsigned SwitchPosition) // initial position
    :BaseShell(Parent, NumInlets, NumOutlets,  Name, Comment),
    iResetSwitchPosition(SwitchPosition)
    {Reset();}
  
  void Reset() {iSwitchPosition = iResetSwitchPosition;}
  int GetSwitchPos()const {return iSwitchPosition;}
  int GetResetSwitchPos()const {return iResetSwitchPosition;}
  virtual void SetNumContacts(int)= 0; //allows the switch to be resized
  virtual int GetNumContacts()const = 0;

  // Switches can change size
  virtual bool CanChangeSize()const {return true;}

  void SetResetSwitchPos (int i);
  void SetSwitchPos (int i) {iSwitchPosition = (unsigned) i;}
	void DoDefaultAction();

 protected:
  unsigned iResetSwitchPosition, iSwitchPosition;
  
  static const char*const szInletZeroName;

  
  // access functions
	static const unsigned NumAccess;
	typedef bool (Switch::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (Switch::*pSetFunc)(const char* new_value);
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

  bool SwitchPosition (char* ret, unsigned ret_size) const;
  bool NumberOfContacts (char* ret, unsigned ret_size) const;
  bool ResetSwitchPosition (char* ret, unsigned ret_size) const;

  bool SwitchPosition (const char* new_val);
  bool NumberOfContacts (const char* new_val);
  bool ResetSwitchPosition (const char* new_val);

};
//*****************************************************************

class SwitchInlets :public Switch
{
  //switches multiple inlets to a single oulet according to
  // the value of iSwitchPosition
  friend class TypeList;
 public:
  
  SwitchInlets(Patch* Parent,
	       unsigned NumContacts = 1,
	       const char* Name = "",
	       const char* Comment = "",
	       unsigned SwitchPosition = 0);
  
  static BaseShell* Create(Patch*);

  void VoidInlet (unsigned);
  void IntInlet (unsigned, int);
  void DoubleInlet (unsigned, double);
  void StringInlet (unsigned, const char*);
  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  const char* GetType()const {return szType;}
  
  void SetNumContacts(int);
  int GetNumContacts()const;
	const BaseShell* GetReference() const;
	bool GetDefaultAttribute (char* ret_value, unsigned buff_len)const;
 private:
  void PassMessage (unsigned);
  void PassMessage (unsigned, const char*);
  void PassMessage (unsigned, int);
  void PassMessage (unsigned, double);
  static const char*const szInletName;
  static const char*const szOutletName;
  static const char*const szType;
};//end SwitchInlets class
//*************************************************************

class SwitchOutlets :public Switch
{
  //  Switches the single inlet to one of multiple outlets
  friend class TypeList;
 public:
  SwitchOutlets(Patch* Parent,
		unsigned NumContacts = 1,
		const char* Name = "",
		const char* Comment = "",
		unsigned SwitchPosition = 0);
  
  static BaseShell* Create(Patch*);

  //pass messages to be switched in this inlet
  void VoidInlet (unsigned);
  void IntInlet (unsigned, int);
  void StringInlet (unsigned, const char*);
  void DoubleInlet (unsigned, double);
  
  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  const char* GetType()const {return szType;}
  void SetNumContacts(int);
  int GetNumContacts()const;
	const BaseShell* GetReference() const;
	bool GetDefaultAttribute (char* ret_value, unsigned buff_len)const;
 private:
  static const char*const szInletName;
  static const char*const szOutletName;
  static const char*const szType;
};//end SwitchOutets class

#endif






