// a abstract base class type peripheral though which Inlets and Oulets are derived

#ifndef SOCKET_H
#define SOCKET_H

class BaseShell; // forward declaration;
class Connector;

#ifndef _ROSE_ANALYSE
//using std::vector;
#endif

#ifndef _ROSE_ANALYSE
typedef sm_ptr::vector<Connector*> ArrayOf_pConnectors;
#else
#define ArrayOf_pConnectors Connector*
#endif

class SocketDetails
{
 public:
  SocketDetails(BaseShell* Base = NULL, unsigned ThisSocketNumber = 0     )
    :pBase(Base), wSocketNumber(ThisSocketNumber) {};
  
  BaseShell* pBase;
  unsigned wSocketNumber;
  
  int operator==(const SocketDetails& Ad)const
  {
    return ((pBase == Ad.pBase) && (wSocketNumber == Ad.wSocketNumber));
  }
  
  int operator!()const {return (!pBase);}
  
};

class SocketContainer  // base class outlets
{
  friend class BaseShell;
 public:
  
  SocketContainer(BaseShell* Parent , unsigned SocketNumber = 0)
    :ThisSocketDetails(Parent, SocketNumber)
    {}
  
  bool RemoveConnector (const Connector* pCon);
  
  bool AddConnector (Connector* pCon);
  Connector* GetConnector(unsigned);
  unsigned FindIndex (const Connector*)const;
  unsigned GetNumConnectors()const;
  void SwapConnector(unsigned Index1, unsigned Index2);
 protected:
  
  SocketDetails ThisSocketDetails;
  
  ArrayOf_pConnectors apConnector;
  
  // virtual bool DeleteConnectors () = 0;
  
  bool HasConnector (const Connector*)const;
  
};
//*****************************************************************
class InletContainer :public SocketContainer
{
 public:
  InletContainer(BaseShell* Parent = NULL, unsigned SocketNumber = 0)
    :SocketContainer(Parent, SocketNumber){}
  
  ~InletContainer() {DeleteConnectors();}
 private:
  bool DeleteConnectors();
  
  
};


#endif

