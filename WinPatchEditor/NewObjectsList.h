//---------------------------------------------------------------------------
#ifndef NewObjectsListH
#define NewObjectsListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Typedefs.h"
#include "interfacetypes.h"

class TBaseShellHook; //forward dec
//---------------------------------------------------------------------------
class TObjectsForm : public TForm
{
__published:	// IDE-managed Components
	TListBox *ObjectTypeList;
	void __fastcall FormActivate(TObject *Sender);
	
	void __fastcall ObjectTypeListDblClick(TObject *Sender);
    
    void __fastcall FormDeactivate(TObject *Sender);
    void __fastcall ObjectTypeListStartDrag(TObject *Sender,
          TDragObject *&DragObject);
private:	// User declarations
   TComponent* Caller; // the object that calls this
   TBaseShellHook* pDragObject;
   P_PATCH pPatch;
public:		// User declarations
	__fastcall TObjectsForm(TComponent* Owner);
   void __fastcall ShowList(TComponent* Caller, P_PATCH pPatch); //allows form to now who made it show

};
//---------------------------------------------------------------------------
extern PACKAGE TObjectsForm *ObjectsForm;
//---------------------------------------------------------------------------
#endif
