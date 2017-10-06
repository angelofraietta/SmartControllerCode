//---------------------------------------------------------------------------
#ifndef PatchPortsH
#define PatchPortsH



//forward declaration
class Patch;
class BaseShell;

class PatchInletPort :public BaseShell
{
  friend class TypeList;
  friend class Patch;
 public:
  enum {eInletNumber};
  PatchInletPort(Patch*,  const char* = "", const char* = "", unsigned = 0);
  ~PatchInletPort();
  static PatchInletPort* Create(Patch*);

  void Reset(){};
  
  const char* GetOutletName(unsigned)const;
  const char* GetType()const {return szType;}

  int GetInletNumber()const{return wInletNumber;}
	const BaseShell* GetReference() const {return NULL;}

 private:
  static const char*const szType;
  void SetInletNumber(int i){wInletNumber = (unsigned)i;}
  void RemoveFromPatch();
  void Input();
  void Input(int);
  void Input(double);
  void Input(const char*);
  unsigned wInletNumber;

  
  // access functions
	static const unsigned NumAccess;
	typedef bool (PatchInletPort::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (PatchInletPort::*pSetFunc)(const char* new_value);
	typedef struct
	{
		const char* access_name;
		pGetFunc get_func;
		pSetFunc set_func;
	} str_access;

  static const str_access aAccess[];

  unsigned GetNumAccess ()const {return NumAccess;}
  const char* GetAccessName (unsigned index)const;
  
  bool GetAttribute (unsigned index, char* ret_value, unsigned buf_size)const;

	bool InletNumber (char* ret, unsigned ret_size) const;


};
//**********************************************************

class PatchOutletPort :public BaseShell
{
  friend class TypeList;
  friend class Patch;
 public:
  enum {eOutletNumber};
  PatchOutletPort(Patch*, const char* = "", const char* = "", unsigned = 0);
  ~PatchOutletPort();
  void VoidInlet(unsigned);
  void IntInlet(unsigned, int);
  void DoubleInlet(unsigned, double);
  void StringInlet(unsigned, const char*);
  static PatchOutletPort* Create(Patch*);

  void Reset(){};
  
  const char* GetInletName(unsigned)const;
  const char* GetType()const {return szType;}

  int GetOutletNumber()const{return OutletNumber;}
	const BaseShell* GetReference() const {return NULL;}
 private:
  static const char*const szType;
  unsigned OutletNumber;
  void RemoveFromPatch();
  
  void SetOutletNumber(int i) {OutletNumber = (unsigned)i;}

  
  // access functions
	static const unsigned NumAccess;
	typedef bool (PatchOutletPort::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (PatchOutletPort::*pSetFunc)(const char* new_value);
	typedef struct
	{
		const char* access_name;
		pGetFunc get_func;
		pSetFunc set_func;
	} str_access;

  static const str_access aAccess[];

  unsigned GetNumAccess ()const {return NumAccess;}
  const char* GetAccessName (unsigned index)const;
  
  bool GetAttribute (unsigned index, char* ret_value, unsigned buf_size)const;

	bool GetOutletNumber (char* ret, unsigned ret_size) const;

  
};

//---------------------------------------------------------------------------
#endif


