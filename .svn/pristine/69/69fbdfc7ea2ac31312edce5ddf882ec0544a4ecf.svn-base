#ifndef MESSAGESTORE_H
#define MESSAGESTORE_H


// sends message out the outlet
#include "messagecell.h"
#include "estring.h"

class MessageStore :public BaseShell {
  friend class TypeList;
  friend class TMessageStoreEditForm;
 public:
  enum {eMessage, eMaxAttribute};
enum {eResetMessage, eMaxResetAttribute};

  static BaseShell* Create(Patch*);

  
  MessageStore (Patch*,
		const char* = "",
		const char* = "");
  
  MessageStore (Patch*, const char*, const char*, int);
  MessageStore (Patch*, const char*, const char*, double);
  MessageStore (Patch*, const char*, const char*, const char*);
  
  void Reset () {StoredMessage = ResetMessage;}
  
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
  void Store (){StoredMessage.Store();}
  void Store (int i){StoredMessage.Store(i); }
  void Store (double d){StoredMessage.Store(d);}
  void Store (const char* s){StoredMessage.Store(s);}
  
  void StoreReset (){ResetMessage.Store();}
  void StoreReset (int i){ResetMessage.Store(i); }
  void StoreReset (double d){ResetMessage.Store(d);}
  void StoreReset (const char* s){ResetMessage.Store(s);}
  
  MessageCell ResetMessage, StoredMessage;
  void DeleteMessage();//removes stored memory allocated by a previous store
  void Send(const char*);
  
  static const char*const szType;
  // arrays to get names of inlets and outlets
  static const char*const szaInletDetails[];
  static const char*const szaOutletDetails[];
  
#ifdef CONSOLE
  void GetMessageFromConsole();
  void DisplayMessage(MessageCell&);
#endif
  
  
  // typedefs for inlet functions
  typedef void(MessageStore::*pVoidFunc)();
  typedef void(MessageStore::*pStringFunc)( const char*);
  typedef void(MessageStore::*pIntFunc)( int);
  typedef void(MessageStore::*pDoubleFunc)( double);
  
  static const pVoidFunc tpVoidFunc[];
  static const pStringFunc tpStringFunc[];
  static const pIntFunc tpIntFunc[];
  static const pDoubleFunc tpDoubleFunc[];
  
  // access functions
	static const unsigned NumAccess;
	typedef bool (MessageStore::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef void (MessageStore::*pSetFunc)(const char* new_value);
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


	bool GetMessage (char* buff, unsigned buff_len) const;
	bool GetResetMessage (char* buff, unsigned buff_len) const;
	bool GetDefaultAttribute (char* buf, unsigned buf_len)const;
	bool SetDefaultAttribute (const char* new_value);
};

#endif



