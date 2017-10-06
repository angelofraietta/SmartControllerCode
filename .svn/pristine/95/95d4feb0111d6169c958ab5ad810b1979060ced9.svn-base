#ifndef ANALOGIN_H
#define ANALOGIN_H

#ifdef _ROSE_ANALYSE
#include "control.h"
#endif



class AnalogIn :public BaseShell
{
  friend class TypeList;
 public:

  enum {eChannel, eInputValue, eMaxAttribute};
	enum {eResetChannel, eFilter, eLowerScale, eUpperScale, eLowerThreshold, eUpperThreshold, eIntegerOnly, eMaxResetAttribute};
                                                                                              
  AnalogIn(Patch* = NULL, const char* Name = "",
	    const char* Comment = "",
	    unsigned Channel = 0,
      float lower_scale = 0,
      float upper_scale = 255,
      unsigned lower_threshold = 0,
      unsigned upper_threshold = 255 ); //

  ~AnalogIn();

  void IntInlet(unsigned, int);

  static void ProcessInput(unsigned channel, unsigned value);
  void OutputValue(unsigned channel, unsigned value);

  void OutputIntValue(unsigned channel, unsigned value);
  void OutputFloatValue(unsigned channel, unsigned value);
  static BaseShell* Create(Patch*);

  const char* GetType()const {return szType;}
  const char* GetOutletName(unsigned)const;
  const char* GetInletName(unsigned)const;


  void Reset(){cChannel = cResetChannel; cValue = 0; fValue = 0; CalculateRange();}


  int GetChannel()const {return cChannel;}
  void SetChannel(int c) {cChannel = c;}

  int GetResetChannel() const {return cResetChannel;}
  void SetResetChannel(int c){cResetChannel =  c;   SetModified(true);}

  int GetValue()const {return cValue;}
	const BaseShell* GetReference() const;  
 private:
  static const char*const szType;

  //define the filters
  int cChannel, cResetChannel, cValue, iLowerScale, iUpperScale, iRange;
  float fLowerScale, fUpperScale, fValue;

  float fRange; // this is caluclated each time
  void CalculateRange ();
  int iLowerThreshold, iUpperThreshold;
  bool filtered, enable_float;

  static const char*const szaOutletDetails[];
  static  const char*const szaInletDetails[];
  
  //list of all MidiIn objects
  static AnalogIn** ObjectsList;
  static unsigned ListSize;
  static void AddObject(AnalogIn*);

  typedef void(AnalogIn::*pIntFunc)( int);
  static const pIntFunc tpIntFunc[];

  // access functions
	static const unsigned NumAccess;
	typedef bool (AnalogIn::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (AnalogIn::*pSetFunc)(const char* new_value);
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
  bool LowerScale(char* ret, unsigned ret_size) const;
  bool UpperScale(char* ret, unsigned ret_size) const;
  bool LowerThreshold(char* ret, unsigned ret_size) const;
  bool UpperThreshold(char* ret, unsigned ret_size) const;
  bool EnableFloat(char* ret, unsigned ret_size) const;

  bool Channel (const char* new_val);
  bool ResetChannel (const char* new_val);
	bool Filter (const char* new_val);
  bool LowerScale(const char* new_val);
  bool UpperScale(const char* new_val);
  bool LowerThreshold(const char* new_val);
  bool UpperThreshold(const char* new_val);
  bool EnableFloat(const char* new_val);

  //Function To See whether we need to do a scaling
  bool DoScale()const;
};


#endif





