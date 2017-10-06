#ifndef DELAY_H
#define DELAY_H

//Delay class
#include "timer.h"
#include "messagecell.h"


class Delay: public BaseShell, DelayLine
{
  friend class TypeList;
 public:
  enum{eInterval, eMaxAttribute};
	enum {eResetInterval, eMaxResetAttribute};

  Delay(Patch* = NULL, const char* Name = "",
				const char* Comment = "", unsigned Interval = 500);
  
  ~Delay();
  
  void VoidInlet(unsigned);
  void DoubleInlet(unsigned, double);
  void IntInlet(unsigned, int);
  void StringInlet(unsigned, const char*);
  
  static BaseShell* Create(Patch*);

  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  
  void Reset ();
  void SetInterval(int i){wInterval = (unsigned)i;}
  void SetResetInterval(int i);
  int GetInterval()const{return wInterval;}
  int GetResetInterval()const{return wResetInterval;}
  
  const char* GetType()const {return szType;}
  
  static const char*const szType;  
	const BaseShell* GetReference() const;

 private:
  unsigned wResetInterval;
  bool fStopProcess;
  void OutputFunction(DWORD);
  void PurgeItem(DWORD);
  void DelayVoid();
  void DelayInt(int);
  void DelayString(const char*);
  void DelayDouble(double);
  
  void SendMessage(MessageCell&);
  
	
  
  typedef void(Delay::*pVoidFunc)();
  static const pVoidFunc tpVoidFunc[];
  
  typedef void(Delay::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];
  
  typedef void(Delay::*pDoubleFunc)(double);
  static const pDoubleFunc tpDoubleFunc[];
  
  typedef void(Delay::*pStringFunc)(const char*);
  static const pStringFunc tpStringFunc[];
  
  // arrays to get names of inlets and outlets
  static  const char*const szaInletDetails[];
  static  const char*const szaOutletDetails[];


  // access functions
	static const unsigned NumAccess;
 	typedef bool (Delay::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (Delay::*pSetFunc)(const char* new_value);
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

  bool Interval (char* ret, unsigned ret_size) const;
  bool ResetInterval (char* ret, unsigned ret_size) const;

  bool Interval (const char* new_val);
  bool ResetInterval (const char* new_val);
  
	
  void StringInlet1(const char*);
  
};

#endif

