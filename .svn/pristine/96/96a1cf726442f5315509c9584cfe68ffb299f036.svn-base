/***************************************************************
Random abstract data type
****************************************************************/
#ifndef ANALOG_OUT_H
#define ANALOG_OUT_H

#ifdef _ROSE_ANALYSE
#include "control.h"
#endif

class AnalogOut :public BaseShell
{
  friend class TypeList;
 public:
  enum {eChannel, eValue, eMaxAttribute};
	enum {eResetChannel, eResetValue, eGenerateOnReset, eMaxResetAttribute};

  static BaseShell* Create(Patch* );

  AnalogOut (Patch*,
             const char* Name = "",
             const char* Comment = "",
             int channel = 1, int value = 0); // default constructor) // default constructor

  virtual ~AnalogOut ();

  void IntInlet(unsigned, int);

  const char* GetInletName(unsigned)const;

  const char* GetType()const{return szType;}
  void	Reset(); // load initial conditions into current conditions
  
  //set properties
  void SetUpperLimit (int NewLimit);
  void SetResetUpperLimit(int NewLimit);
  
  void  SetChannel (int i) {iChannel = i;}
  int GetChannel()const {return iChannel;}

	void SetValue (int i) {iValue = i; Send();}
  int GetValue()const {return iValue;}

  int GetResetChannel()const {return iResetChannel;}
	void SetResetChannel (int i);

  int GetResetValue()const {return iResetValue;}
	void SetResetValue (int i);

  int GetGenerateOnReset()const {if (fGenerateOnReset) return 1; else return 0;}
  void SetGenerateOnReset(int);
  
  void Send();

	const BaseShell* GetReference() const;
 private:
  int	iChannel, iValue, iResetChannel, iResetValue;  	// the upper limit

	bool fGenerateOnReset;

  static const char*const szType;

  //IntInlet function table
  typedef void(AnalogOut::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];


  // arrays to get names of inlets and outlets
  static const char*const szaInletDetails[];


  // access functions
	static const unsigned NumAccess;
	typedef bool (AnalogOut::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (AnalogOut::*pSetFunc)(const char* new_value);

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
  bool ResetValue (char* ret, unsigned ret_size) const;
  bool GenerateOnReset (char* ret, unsigned ret_size) const;

  bool Channel (const char* new_val);
  bool Value (const char* new_val);
  bool ResetChannel (const char* new_val);
  bool ResetValue (const char* new_val);
  bool GenerateOnReset (const char* new_val);

};
#endif
