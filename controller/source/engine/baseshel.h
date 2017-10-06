// The superclass shell by which all action classes are derived
// BaseShell class. a BaseShell class is an abstract class that
// enables a common input and output to derived objects
// through virtual inlet and outlet functions
#ifndef BASESHEL_H
#define  BASESHEL_H

#include "identity.h"


class BaseShell;
class Patch;
class TypeListElement;
class TypeList;
class OutletContainer;
class InletContainer;
class Connector;
class ConnectorMessage;
class Identity;


#ifndef _ROSE_ANALYSE
typedef sm_ptr::vector<OutletContainer*> ArrayOfpOutlets;
typedef sm_ptr::vector<InletContainer*> ArrayOfpInlets;
#else
#define ArrayOfpOutlets OutletContainer*
#define ArrayOfpInlets InletContainer*
#endif

class BaseShell : public Identity{
  friend class Patch;
  friend class TBaseShellHook;
 public:
  // inlet virtual functions
  // this allows pointers to derived functions to be given through
  // one class
  // ten inlets all overloaded with different types for function calls
  
  // the functions are not made pure virtual so they do not have to
  // be overloaded
  BaseShell (Patch*, unsigned NumInlets, unsigned NumOutlets,
	     const char* Name , const char* Comment );
  ~BaseShell();
  
  bool operator==(const BaseShell& BS)const {return (&BS == this);}
  
  virtual void Reset()=0;
  
  virtual void VoidInlet (unsigned InletNumber) {}
  virtual void IntInlet (unsigned InletNumber, int) {}
  virtual void DoubleInlet (unsigned InletNumber, double d) {IntInlet (InletNumber, DoubleToInt(d));}
  virtual void StringInlet (unsigned InletNumber, const char*) {}
  
  int DoubleToInt (double dval);
  
  //find connector details inside inlets and outlets
  unsigned GetNumInletConnectors(unsigned)const;
  unsigned GetNumOutletConnectors(unsigned)const;
  Connector* GetInletConnector(unsigned, unsigned);
  Connector* GetOutletConnector(unsigned, unsigned);
  void SwapOutletConnector(unsigned OutletNumber, unsigned Index1, unsigned Index2);
  
  // Allows addresses of Connectors pointing to this class
  // do be notified by destruction of this
  virtual bool Connect(ConnectorMessage Address);
  
  bool CanConnectInlet(unsigned, Connector*);
  bool CanConnectOutlet(unsigned, Connector*);
  bool CanSave()const;
  virtual void SetModified(bool Modified);
  // return number of inlets and outlets this has
  virtual unsigned GetNumInlets ()const {return wNumInlets;}
  virtual unsigned GetNumOutlets ()const {return wNumOutlets;}
  virtual const char* GetInletName(unsigned)const {return NULL;}
  virtual const char* GetOutletName(unsigned)const {return NULL;}
  unsigned FindOutletConnectorIndex(unsigned, const Connector*)const;
  unsigned FindInletConnectorIndex(unsigned, const Connector*)const;
  unsigned PatchPosition()const;
  virtual bool Restore(FILE* infile);
  virtual void DoDefaultAction(){};

  // the number of access functions will be overridden within subclass
  virtual unsigned GetNumAccess ()const {return 0;}

  // attributes that can be overloaded as class attributes
  virtual bool CanHaveChildren()const {return false;}
  virtual bool CanChangeSize()const {return false;}

  // define the set and set access functions
  virtual bool SetAttribute (unsigned index, const char* value) {return false;}
  virtual bool GetAttribute (unsigned index, char* ret_value, unsigned buff_len)const {return false;}
  // the default is the 1st attrinute. Otherwise Overload function
  virtual bool GetDefaultAttribute (char* ret_value, unsigned buff_len)const {return GetAttribute (0, ret_value, buff_len);}

  virtual const char* GetAccessName (unsigned index)const {return NULL;}

	// now do same for reset attributes
  virtual unsigned GetNumResetAccess ()const {return 0;}
  
  // define the set and set access functions
  virtual bool SetResetAttribute (unsigned index, const char* value) {return false;}
  virtual bool GetResetAttribute (unsigned index, char* ret_value, unsigned buff_len)const {return false;}

  virtual const char* GetResetAccessName (unsigned index)const {return NULL;}

  static const char *const StartBlock;

  static unsigned GetNumObjectTypes();
  static const char* GetObjectType(unsigned index);
protected:
  

  unsigned wNumInlets; // the number of inlets this object has
  unsigned wNumOutlets; // ditto for outlets
  
  void CreateOutlets();
  void CreateInletLists();
  void RemoveInlet(); //removes one
  void RemoveOutlet();
  void AddInlet();
  void AddOutlet();

	void Save(FILE*);
	void SaveConnectors (FILE*)const;
  virtual const BaseShell* GetReference() const = 0;
  //list of Connectors pointing to this
  ArrayOfpInlets tpInletConnections;
  
  //table of pointers to Outlets belonging to this
  ArrayOfpOutlets tpOutlet;
}; // end class BaseShell



// the old and new address of the connector is sent to inlets and outlets
typedef int (BaseShell::*pOutlet)(unsigned, ConnectorMessage);




#endif





