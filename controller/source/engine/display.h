//Display class
#ifndef DISPLAY_H
#define DISPLAY_H

class Display :public BaseShell
{
  friend class TypeList;
 public:
  Display(Patch* Parent, const char* Name = "", const char* Comment = "");
  
  ~Display();
  static BaseShell* Create(Patch*);
  
  const char* GetInletName(unsigned)const;
  const char* GetType()const {return szType;}
  void VoidInlet(unsigned InletNumber);
  void IntInlet(unsigned InletNumber, int i);
  void DoubleInlet(unsigned InletNumber, double d);
  void StringInlet(unsigned InletNumber, const char* s);
  
  void Reset(){}

	const BaseShell* GetReference() const;
 private:

  static const char*const szInletDetails;
  static const char*const szType;
  
};
#endif

