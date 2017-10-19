// a base class type inlet though which inlets to DeviceObjects inlets
// are derived.  An inlet is called through a connector.
#ifndef OUTLET_H
#define OUTLET_H

class SocketContainer;
class BaseShell;
class MessageCell;

class OutletContainer	:public SocketContainer  // base class for inlets
{
 public:
  OutletContainer (BaseShell* Parent = NULL, unsigned OutletNumber= 0)
    :SocketContainer(Parent, (unsigned)OutletNumber), _mutex(false){}
  
  ~OutletContainer ();
  void ProduceOutput();
  void ProduceOutput (const char* sVal);
  void ProduceOutput (int iVal);
  void ProduceOutput (double dVal);
  void ProduceOutput (const MessageCell& TheMessage);
  void SaveConnectors (FILE*);
 private:
  bool _mutex;
  bool DeleteConnectors();
};

#endif

