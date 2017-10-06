//Patch is a series of objects grouped together
#ifndef PATCH_H
#define PATCH_H
#include "patchports.h"

#ifndef _ROSE_ANALYSE
#include <deque>
#endif

#include "estring.h"
#include "evector.h"

class Connector;
class PatchView;

#ifndef _NO_NAMESPACES
using sm_ptr::vector;
using std::deque;
#endif

typedef vector<BaseShell*> ArrayOfpObjects;
typedef vector<Connector*> ArrayOfpConnectors;
typedef deque<Connector*> QueueOfDeadConnectors;
typedef vector<PatchInletPort*> ArrayOfPatchInletPorts;
typedef vector<PatchOutletPort*> ArrayOfPatchOutletPorts;
typedef string StringObject;
typedef sm_ptr::vector<Patch*> ArrayOfPatches;
typedef sm_ptr::vector<PatchView*> ArrayOfViews;

class PatchAnswer; //forward dec

//************************************************************
class Patch :public BaseShell {

  friend class TypeList;
  friend void PatchInletPort::RemoveFromPatch();
  friend void PatchOutletPort::RemoveFromPatch();
  friend void PatchOutletPort::VoidInlet(unsigned);
  friend void PatchOutletPort::IntInlet(unsigned, int);
  friend void PatchOutletPort::DoubleInlet(unsigned, double);
  friend void PatchOutletPort::StringInlet(unsigned, const char*);
  friend class PatchAnswer;
  
 public:
  enum {ByUserInterface, ByConnector};
  enum {eNumObjects, eNumConnectors, eIsOrphan, eFilename};
  Patch(Patch*, unsigned,
	unsigned, const char*, const char*, const char*);
  
	Patch (const char* name = "NewPatch");
  ~Patch();
  
  static BaseShell* Create(Patch* = NULL);
  static BaseShell* CreatePatchFile(Patch* = NULL);
  static BaseShell* LoadPatchFile(const char*, Patch* = NULL);
  static BaseShell* AddOutletPort(Patch*);
  static BaseShell* AddInletPort(Patch*);

  static unsigned NumPatches();
  static Patch* GetPatch(unsigned index);
  
  BaseShell* AddInlet();
  BaseShell* AddOutlet();
  
  bool Detach(BaseShell*);
  //methods of Connector Deletion
  bool Detach(Connector*, int Method);
  
  bool Add(BaseShell*);
  bool Add(Connector*);
  int NumObjects()const;
  int NumConnectors()const;
  Connector* FindConnector(unsigned);
  BaseShell* FindObject(unsigned);
  unsigned FindPosition(const BaseShell*)const;

  // Patches can change size and havbe children
  virtual bool CanHaveChildren()const {return true;}
  virtual bool CanChangeSize()const {return true;}

  void VoidInlet (unsigned InletNumber);
  void IntInlet (unsigned InletNumber, int);
  void DoubleInlet (unsigned InletNumber, double);
  void StringInlet (unsigned InletNumber, const char*);
  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  const char* GetType()const {return szType;}
  bool GetFileName(char* buf, unsigned buf_len)const;
  const char* GetFileName()const {return sFileName.c_str();}
  bool SetFileName(const char* FileName);

  void Reset();
  Connector* GetDeadConnector();
  
  PatchInletPort* GetInlet(unsigned InletNum);
  PatchOutletPort* GetOutlet(unsigned OutletNum);
  void SwapInlets(unsigned InletNumber1, unsigned InletNumber2);
  void SwapOutlets(unsigned OutletNumber1, unsigned OutletNumber2);  
  int IsOrphan()const {return (pParent)?0:1;}
  bool Save();
  void Save(FILE*);
	bool CanSave()const;

	unsigned GetNumViews(){ return ViewList.size();}
	PatchView* GetView(unsigned index);
	unsigned AddView();
	const BaseShell* GetReference() const {return NULL;}
	static void SetError() {_load_error = true;} // setsb an error
	static void ClearError(){_load_error = false;}
	virtual bool GetName (char* buf, unsigned buf_len)const;

  static unsigned _max_patch_load_depth; // this increments and decrements as we are loading patch
private:
	static volatile bool _load_error;
  static volatile unsigned _patch_load_depth; // this increments and decrements as we are loading patch


  ArrayOfpObjects ObjectList; // a list of all object contained in patch
  ArrayOfpConnectors ConnectorList;
  QueueOfDeadConnectors DeadConnectorList;
  ArrayOfViews ViewList; // a list of views contained within patch

  static const char*const szType;
  ArrayOfPatchInletPorts ptInletPort;
  ArrayOfPatchOutletPorts ptOutletPort;

  static ArrayOfPatches pPatchList;

  static void RemovePatch(Patch* pPatch);
  static void AddPatch (Patch* pPatch);


  bool RestoreInletPorts(char* inbuf);
  bool RestoreOutletPorts(char* inbuf);
  //if stored as a file sFileName has a value, else NULL
  StringObject sFileName;

  void RemoveInlet(PatchInletPort*);
  void RemoveOutlet(PatchOutletPort*);
  void ProduceOutput (unsigned );
  void ProduceOutput (unsigned , int);
  void ProduceOutput (unsigned , double);
  void ProduceOutput (unsigned , const char*);

  bool HasFileAncestor(const char*)const; //has the filename as an ancestor

  bool Restore(FILE* infile);
  
  // access functions
	static const unsigned NumAccess;
	typedef bool (Patch::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (Patch::*pSetFunc)(const char* new_value);
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

	bool NumObjects (char* ret, unsigned ret_size) const;
	bool NumConnectors (char* ret, unsigned ret_size) const;
	bool IsOrphan (char* ret, unsigned ret_size) const;
};


#endif
