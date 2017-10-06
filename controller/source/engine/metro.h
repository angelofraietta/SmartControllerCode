#ifndef METRO_H
#define METRO_H

//Metronome class
#include "timer.h"


class Metro: public BaseShell, public  FreeRunning
{
  friend class TypeList;
 public:
  enum{eInterval, eIsOn, eMaxAttribute};
	enum {eResetInterval, eMaxResetAttribute};

  Metro(Patch* = NULL, const char* Name = "",
	const char* Comment = "", unsigned Interval = 500);
  
  ~Metro();
  
  void IntInlet(unsigned, int);
  void StringInlet(unsigned, const char*);
  static BaseShell* Create(Patch*);

  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  
  void Reset () {Stop(); SetClockInterval(wResetInterval);}
  void SetResetInterval(int i);
  int GetResetInterval()const{return wResetInterval;}
  void SetInterval(int i);
  int GetInterval()const {return wInterval;}
  const char* GetType()const {return szType;}
  void Activate(int);
  
  void Send(){tpOutlet[0]->ProduceOutput();}
	void DoDefaultAction();

	const BaseShell* GetReference() const;
 private:
  unsigned wResetInterval;
  
  static const char*const szType;
  void OutputFunction(){Send();}
  void DecodeStringInlet0(const char*);
  
  typedef void(Metro::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];
  typedef void(Metro::*pStringFunc)(const char*);
  static const pStringFunc tpStringFunc[];
  
  // arrays to get names of inlets and outlets
  static  const char*const szaInletDetails[];
  static  const char*const szaOutletDetails[];
  //sets interval from IntInlet
  void SetIntInterval(int i){SetInterval((unsigned)i);}
  
  // access functions
	static const unsigned NumAccess;
	typedef bool (Metro::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (Metro::*pSetFunc)(const char* new_value);
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

  bool IsOn (char* ret, unsigned ret_size) const;
  bool IsOn (const char* new_val);  
};

#endif

