// connector class

#ifndef CONNECT_H
#define CONNECT_H

class Patch;
class Outlet;
class InletConnectorList;
class Identity;
class SocketDetails;
class BaseShell;


class Connector :public Identity
{
  friend class OutletContainer;
  friend class Patch;
  friend class TConnectorHook;
 public:
  enum{ByParent, ByInlet, ByOutlet};
  Connector();
  Connector(Patch*, SocketDetails, SocketDetails,
            const char* Name , const char* Comment );
  
  bool operator==(const Connector&)const ;
  
  bool operator!(){return !InletConnection || !OutletConnection;}
  
  SocketDetails InletDetails()const {return InletConnection;}
  SocketDetails OutletDetails()const {return OutletConnection;}

  unsigned GetInletNum ()const {return InletConnection.wSocketNumber;}
  unsigned GetOutletNum ()const {return OutletConnection.wSocketNumber;}

  BaseShell* GetInletBase ()const {return InletConnection.pBase;}
  BaseShell* GetOutletBase ()const {return OutletConnection.pBase;}
  
	bool Disconnect(int);
  
  bool DisconnectFromInlet ();
  
  bool DisconnectFromOutlet();
  
  bool DisconnectFromParent();
  
  bool ConnectToInlet (SocketDetails);
  
  bool ConnectToOutlet(SocketDetails);
  
  bool ConnectToOutlet();
  
  bool ConnectToInlet();
  
  
  
  const char* GetType()const {return szType;}
  void Save(FILE*);
  
  // special access from Package interface
  void SetInletBase(BaseShell* pBase) {InletConnection.pBase = pBase;}
  void SetInletNum(unsigned i) {InletConnection.wSocketNumber = i;}
  void SetOutletBase(BaseShell* pBase) {OutletConnection.pBase = pBase;}
  void SetOutletNum(unsigned i) {OutletConnection.wSocketNumber = i;}
  void SetModified(bool Modified);
  bool CanSave()const;

	static const char *const StartBlock;
	bool Restore(FILE* infile, Patch* parent);
  
 private:
  SocketDetails InletConnection, OutletConnection;
  static const char*const szType;

};
#endif









