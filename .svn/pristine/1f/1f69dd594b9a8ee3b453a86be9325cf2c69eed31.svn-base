#ifndef OSC_IN_H
#define OSC_IN_H

#ifdef _ROSE_ANALYSE
#include "control.h"
#endif

class OSCArg; // forward declaration

class OSCIn :public BaseShell
{
  friend class TypeList;
 public:

  enum {ePort, eAddressSpace, eMaxAttribute};
	enum {eResetPort, eResetAddressSpace, eMaxResetAttribute};

  OSCIn(Patch* = NULL, const char* Name = "",
	    const char* Comment = "",
	    unsigned Channel = 0,
      const char* osc_address = "*"); //

  ~OSCIn();

  void IntInlet(unsigned, int);
  void StringInlet(unsigned, const char*);

  static void OSCIn::ProcessInput(int port, const char* osc_address, const char* client_address, unsigned num_args, OSCArg* args);
  void GenerateOutput(int port, const char* osc_address, const char* client_address, unsigned num_args, OSCArg* args);

  static bool AcceptOSCMessage (int port, const char* osc_address);
  bool ObjectAcceptOSCMessage (int port, const char* osc_address);

  static BaseShell* Create(Patch*);

  const char* GetType()const {return szType;}
  const char* GetOutletName(unsigned)const;
  const char* GetInletName(unsigned)const;


  void Reset(){SetPort(_reset_port); _osc_address_space = _reset_osc_address_space;}


  int GetPort()const {return _port;}
  void SetPort(int port);

  void SetOscAddress (const char* address){OSCAddress(address);}
  int GetResetPort() const {return _reset_port;}
  void SetResetPort(int c){_reset_port =  c;   SetModified(true);}

	const BaseShell* GetReference() const;  
 private:
  static const char*const szType;

  //define the filters
  int _port, _reset_port;
  string _osc_address_space, _reset_osc_address_space;

  static const char*const szaOutletDetails[];
  static  const char*const szaInletDetails[];
  
  //list of all MidiIn objects
  static OSCIn** ObjectsList;
  static unsigned ListSize;
  static void AddObject(OSCIn*);

  typedef void(OSCIn::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];
  typedef void(OSCIn::*pStringFunc)( const char*);
  static const pStringFunc tpStringFunc[];
  // access functions
	static const unsigned NumAccess;
	typedef bool (OSCIn::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (OSCIn::*pSetFunc)(const char* new_value);
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
  bool GetDefaultAttribute (char* ret_value, unsigned buff_len)const;

  bool SetResetAttribute (unsigned index, const char* value);
  bool GetResetAttribute (unsigned index, char* ret_value, unsigned buf_size) const;

  bool Port (char* ret, unsigned ret_size) const;
  bool ResetPort (char* ret, unsigned ret_size) const;
  bool OSCAddress (char* ret, unsigned ret_size) const;
  bool ResetOSCAddress (char* ret, unsigned ret_size) const;

  bool Port (const char* new_val);
  bool ResetPort (const char* new_val);
	bool OSCAddress (const char* new_val);
	bool ResetOSCAddress (const char* new_val);  
};


#endif





