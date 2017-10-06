//MessageFilter class
#ifndef MESSAGE_FILTER_H
#define MESSAGE_FILTER_H

class MessageFilter :public BaseShell
{
  friend class TypeList;
 public:
  MessageFilter(Patch* Parent, const char* Name = "", const char* Comment = "");
  ~MessageFilter();
  static BaseShell* Create(Patch*);

  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;      
  const char* GetType()const {return szType;}
  void VoidInlet(unsigned);
  void IntInlet(unsigned InletNumber, int i);
  void DoubleInlet(unsigned InletNumber, double d);
  void StringInlet(unsigned InletNumber, const char* s);
  
  void Reset(){}
  void Send(){};
	void DoDefaultAction(){Send();};
	const BaseShell* GetReference() const;

 private:

  // arrays to get names of inlets and outlets
  static const char*const szInletDetails;
  static const char*const szaOutletDetails[];

  static const char*const szType;
};
#endif
