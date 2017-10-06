//trigger class
#ifndef TRIGGER_H
#define TRIGGER_H

class Trigger :public BaseShell
{
  friend class TypeList;
 public:
  Trigger(Patch* Parent, const char* Name = "", const char* Comment = "")
    :BaseShell (Parent, 1,1,Name,Comment), display_messages (false){}
  ~Trigger();
  static BaseShell* Create(Patch*);

  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;      
  const char* GetType()const {return szType;}
  void VoidInlet(unsigned);
  void IntInlet(unsigned InletNumber, int i);
  void DoubleInlet(unsigned InletNumber, double d);
  void StringInlet(unsigned InletNumber, const char* s);
  
  void Reset(){}
  void Send();
	void DoDefaultAction(){Send();};
	void EnableDisplay (bool add);
	const BaseShell* GetReference() const;

 private:
	unsigned display_messages; // whether we will display messages or not

  static const char*const szInletDetails;
  static const char*const szOutletDetails;
  static const char*const szType;
};
#endif
