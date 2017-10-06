#ifndef OSC_OUT_H
#define OSC_OUT_H


#include "estring.h"
#include "OSC-client.h"

class OscOut :public BaseShell {
  friend class TypeList;
 public:
  enum {eDestinationAddress, ePort, eOSCAddress, ePortOpen, eMaxAttribute};
  enum {eResetDestinationAddress, eResetPort, eResetOSCAddress, eResetOnSend, eSendOnMessage, eMaxResetAttribute};

  static BaseShell* Create(Patch*);

  
  OscOut (Patch*,
		const char* = "",
		const char* = "");

  ~OscOut(){CloseHtmSocket();}
  
  void Reset ();
  
  void VoidInlet (unsigned);
  void StringInlet(unsigned, const char*);
  void IntInlet(unsigned, int);
  void DoubleInlet(unsigned, double);
  
  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  const char* GetType()const {return szType;}
  void Send();

	void DoDefaultAction(){Send();}

	const BaseShell* GetReference() const;

 private:
  string _destinationAddress, _resetDesintationAddress;
  int _port, _reset_port;
  string _osc_address, _reset_osc_address;
  char _osc_buf_memory [1024]; // Alocated memory fo OSCBuf
  OSCbuf _OSCBuf;
  void* _htmsocket;
  int _reset_on_send; // Reset The message each time a message is sent - actually bool but we'll keep int for performance 
  // define functions for control by inlets
  bool _send_on_message; // flag to cause a send on each message

  bool OpenHtmSocket();
  void CloseHtmSocket();
  // inlet 1
  void ControlStringInlet(const char*);
  void SetDestAddress (const char*s) {SetDestinationAddress(s);}
  void SetDestPort (int);
  void SendOSC() {Send();}

  // inlet 2
  void SetOscAddress (const char*);

  // inlet 3
  // add messages to OSCbuf
  void AddMessage ();
  void AddMessage (int i);
  void AddMessage (double d);
  void AddMessage (const char* s);

  /*
  void StoreReset (){ResetMessage.Store();}
  void StoreReset (int i){ResetMessage.Store(i); }
  void StoreReset (double d){ResetMessage.Store(d);}
  void StoreReset (const char* s){ResetMessage.Store(s);}
  */


  static const char*const szType;
  // arrays to get names of inlets 
  static const char*const szaInletDetails[];

  // typedefs for inlet functions
  typedef void(OscOut::*pVoidFunc)();
  typedef void(OscOut::*pStringFunc)( const char*);
  typedef void(OscOut::*pIntFunc)( int);
  typedef void(OscOut::*pDoubleFunc)( double);

  static const pVoidFunc tpVoidFunc[];
  static const pStringFunc tpStringFunc[];
  static const pIntFunc tpIntFunc[];
  static const pDoubleFunc tpDoubleFunc[];

  // access functions
	static const unsigned NumAccess;
	typedef bool (OscOut::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (OscOut::*pSetFunc)(const char* new_value);
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


	bool GetDestinationAddress (char* buff, unsigned buff_len) const;
	bool GetResetDestinationAddress (char* buff, unsigned buff_len) const;

	bool GetPort (char* buff, unsigned buff_len) const;
	bool GetResetPort (char* buff, unsigned buff_len) const;

	bool GetOSCAddress (char* buff, unsigned buff_len) const;
	bool GetResetOSCAddress (char* buff, unsigned buff_len) const;
  bool GetResetOnSend (char* buff, unsigned buff_len) const;
  bool GetSendOnMessage (char* buff, unsigned buff_len) const;
  bool GetPortOpen (char* buff, unsigned buff_len) const;

	bool GetDefaultAttribute (char* buf, unsigned buf_len)const;

	bool SetDestinationAddress (const char* new_value);
	bool SetResetDestinationAddress (const char* new_value);
	bool SetPort (const char* new_value);

	bool SetResetPort (const char* new_value);
	bool SetOSCAddress (const char* new_value);
	bool SetResetOSCAddress  (const char* new_value);
  bool SetResetOnSend  (const char* new_value);
  bool SetSendOnMessage  (const char* new_value);
  bool SetPortOpen  (const char* new_value);
};

#endif



