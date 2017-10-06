#ifndef DIGITAL_IN
#define DIGITAL_IN

#ifdef _ROSE_ANALYSE
#include "control.h"
#endif
#include "messagecell.h"


class DigitalIn :public BaseShell
{
  friend class TypeList;
 public:

  enum {eChannel, eInputValue, eMaxAttribute};
	enum {eResetChannel, eFilter, eOffValue, eOnValue, eMaxResetAttribute};

  DigitalIn(Patch* = NULL, const char* Name = "",
	    const char* Comment = "",
	    unsigned Channel = 0); //

  ~DigitalIn();

  void IntInlet(unsigned, int);
    
  static void ProcessInput(unsigned channel, unsigned value);
  void OutputValue(unsigned channel, unsigned value);
  static BaseShell* Create(Patch*);

  const char* GetType()const {return szType;}
  const char* GetOutletName(unsigned)const;
  const char* GetInletName(unsigned)const;

  void Reset(){cChannel = cResetChannel; cValue = 0;}


  int GetChannel()const {return cChannel;}
  void SetChannel(int c) {cChannel = c;}

  int GetResetChannel() const {return cResetChannel;}
  void SetResetChannel(int c){cResetChannel = c;   SetModified(true);}

  int GetValue()const {return cValue;}
	const BaseShell* GetReference() const;

 private:
  static const char*const szType;

  MessageCell mOffMessage, mOnMessage;
  //define the filters
  unsigned cChannel, cResetChannel, cValue;
  bool filtered;

  static const char*const szaOutletDetails[];
  static  const char*const szaInletDetails[];

  typedef void(DigitalIn::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];

  //list of all MidiIn objects
  static DigitalIn** ObjectsList;
  static unsigned ListSize;
  static void AddObject(DigitalIn*);


  // access functions
	static const unsigned NumAccess;
	typedef bool (DigitalIn::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (DigitalIn::*pSetFunc)(const char* new_value);
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

  bool Channel (char* ret, unsigned ret_size) const;
  bool Value (char* ret, unsigned ret_size) const;
  bool ResetChannel (char* ret, unsigned ret_size) const;
  bool Filter (char* ret, unsigned ret_size) const;
  bool OnMessage (char* ret, unsigned ret_size) const;
  bool OffMessage (char* ret, unsigned ret_size) const;

  bool Channel (const char* new_val);
  bool ResetChannel (const char* new_val);
	bool Filter (const char* new_val);
	bool OnMessage (const char* new_val);
	bool OffMessage (const char* new_val);

};


#endif





