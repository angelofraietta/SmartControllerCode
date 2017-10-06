//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "NewObjectsList.h"
#include "TypeNames.h" //contains NewObjectsTypeList
#include "TypeElementUnit.h"
#include "PatchUnit.h"
#include "DragBaseShell.h"
#include "ObjectBox.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define DRAG_THRESHOLD 3 //the number of pixels to befin a drag

TObjectsForm *ObjectsForm;
//---------------------------------------------------------------------------
__fastcall TObjectsForm::TObjectsForm(TComponent* Owner)
	: TForm(Owner)
{
    ObjectTypeList->Items->Add(String(PATCH_FILE_ID));
    for (unsigned i = 0; i < TTypeElementList::NumElements(); i++)
        { // create an element
        ObjectTypeList->Items->Add(TTypeElementList::GetType(i));
        }

}
//---------------------------------------------------------------------------
void __fastcall TObjectsForm::FormActivate(TObject *Sender)
{

	ObjectTypeList->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TObjectsForm::ObjectTypeListDblClick(TObject *Sender)
{
   int ObjectIndex = ObjectTypeList->ItemIndex;
   if (ObjectIndex < 0)
       return;

   String SelectedType = ObjectTypeList->Items->Strings[ObjectIndex];
   Hide();

   if (dynamic_cast<TPatchForm*> (Caller))
   	    {
          pDragObject = ((TPatchForm*)Caller)->AddObject(SelectedType, pPatch);
          if(pDragObject)
              ObjectTypeList->BeginDrag(true, DRAG_THRESHOLD);
          return;
          }
   if (dynamic_cast<TViewForm*>(Caller))
      {
      P_PATCH pPatch = ((TViewForm*)Caller)->pPatch;

      pDragObject = ((TViewForm*)Caller)->GetPatchForm ()->AddObject(SelectedType, pPatch);
      if(pDragObject)
          ObjectTypeList->BeginDrag(true, DRAG_THRESHOLD);
      }

}
//---------------------------------------------------------------------------
void __fastcall TObjectsForm::ShowList(TComponent* Invoker, P_PATCH ParentPatch)
{
    pPatch = ParentPatch;
	Caller = Invoker;
    Show();
}


void __fastcall TObjectsForm::FormDeactivate(TObject *Sender)
{
    Hide();
}
//---------------------------------------------------------------------------

void __fastcall TObjectsForm::ObjectTypeListStartDrag(TObject *Sender,
      TDragObject *&DragObject)
{   if(pDragObject)
        {
        DragObject = new TDragBaseShell((TBaseShellHook*)pDragObject, pPatch);
        pDragObject = NULL;
        }
}
//---------------------------------------------------------------------------

