//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EditPatchUnit.h"
#include "IdentityHook.h"
#include "ViewFormUnit.h"
#include "NewObjectsList.h"
#include "TypeElementUnit.h"
#include "ViewFormUnit.h"
#include "Typenames.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseShellsUnit"
#pragma link "PatchUnit"
#pragma resource "*.dfm"

enum {SAVE_WITH_PARENT, SAVE_AS_FILE};
TEditPatchForm *EditPatchForm;


//---------------------------------------------------------------------------
__fastcall TEditPatchForm::TEditPatchForm(TBaseShellHook* Owner)
	: TBaseShellEditForm(Owner)
{
    pViewForm = new TViewForm(this, (P_PATCH)pObject);
    LoadViewForm();
    pViewForm->Caption = String(Owner->GetName() + " - MasterView");
    pViewForm->Parent = ViewPanel;
    pViewForm->Align = alClient;
    pViewForm->AutoArrange();
    pViewForm->Visible = true;
    pViewForm->Show();
    UpdateForm();
}

void __fastcall TEditPatchForm::LoadViewForm()
{
    unsigned NumShells = PatchQuestion::NumberBaseShells(GetCurrentEngine(), pObject);
    for(unsigned i = 0; i < NumShells; i++)
        {
        P_BASESHELL pShell = PatchQuestion::FindBaseShell(GetCurrentEngine(), pObject, i);
        pViewForm->AddObject(GetPatchForm()->GetBaseShellHook(pShell));
        }
}
//-------------------------------------------------------------------
TForm* TEditPatchForm::Create(TBaseShellHook* Owner)
{
    return new TEditPatchForm(Owner);
}

//---------------------------------------------------------------------------


void __fastcall TEditPatchForm::AddInletButtonClick(TObject *Sender)
{
    GetPatchForm()->AddObject(INLETPORT_TYPE, (P_PATCH)pObject);
    UpdateForm();

}
//---------------------------------------------------------------------------

void __fastcall TEditPatchForm::AddOutletButtonClick(TObject *Sender)
{
    GetPatchForm()->AddObject(OUTLETPORT_TYPE, (P_PATCH)pObject);
    UpdateForm();
}
//---------------------------------------------------------------------------
void TEditPatchForm::LoadData()
{
   SetInletsTabs(); // sets the Tab list for inlet list
   SetOutletsTabs();//ditto for outlets
   PatchSaveGroup->Visible = (IdentityQuestion::GetParent(GetCurrentEngine(), pObject))();
   PatchSaveGroup->Enabled = !IdentityQuestion::GetParent(GetCurrentEngine(), pObject)
                                || (IdentityQuestion::CanSave(GetCurrentEngine(),
                                IdentityQuestion::GetParent(GetCurrentEngine(), pObject)));
   if(IdentityQuestion::CanSave(GetCurrentEngine(), pObject))
        {
        PatchSaveGroup->ItemIndex = SAVE_WITH_PARENT;
        FileNameEdit->Visible = false;
        }
   else
        {
        PatchSaveGroup->ItemIndex = SAVE_AS_FILE;
        FileNameEdit->Visible = true;
        char NameBuf [MAX_NAME_LEN+1];
        PatchQuestion::GetFileName(GetCurrentEngine(), pObject, NameBuf, MAX_NAME_LEN);
        FileNameEdit->SetTextBuf(NameBuf);
        }
   AddOutletButton->Enabled = IdentityQuestion::CanSave(GetCurrentEngine(), pObject);
   AddInletButton->Enabled = IdentityQuestion::CanSave(GetCurrentEngine(), pObject);
   LoadInletPorts();
   LoadOutletPorts();
}

void __fastcall TEditPatchForm::ViewPanelDblClick(TObject *Sender)
{
    pViewForm->Parent = ViewPanel;
    pViewForm->FormStyle = fsNormal;
    pViewForm->Align = alClient;

}
//---------------------------------------------------------------------------

void __fastcall TEditPatchForm::StoreButtonClick(TObject *Sender)
{
   if(!PatchSaveGroup->Enabled)
      return;

   StoreInletPorts();
   StoreOutletPorts();
      
   //get the existing filename
   char NameBuf [MAX_NAME_LEN+1];
   PatchQuestion::GetFileName(GetCurrentEngine(), pObject, NameBuf, MAX_NAME_LEN);

   if(PatchSaveGroup->ItemIndex == SAVE_AS_FILE)
      {
      if(!strcmp(NameBuf, "") && SavePatchDialog->Execute())
         {
         GetPatchForm()->SavePatchFile((TBaseShellHook*)Owner,
                        ExtractFileName(SavePatchDialog->FileName));
         GetPatchForm()->SetModified();
         }
      }
    else //save with patch
        {
        if(strcmp(NameBuf, "")) //there is a filename
            {
            PatchQuestion::SetFileName(GetCurrentEngine(), pObject, "");
            GetPatchForm()->SetModified();
            }
         }

   GetPatchForm()->UpdatePatchNodeImages ((P_PATCH)pObject);
   LoadData();
}
//---------------------------------------------------------------------------
void TEditPatchForm::LoadInletPorts()
{
    InletPortList->Clear();
    //load the inlets
    for(unsigned i = 0; i < BaseShellQuestion::GetNumInlets(GetCurrentEngine(), pObject); i++)
        {
         P_BASESHELL pShell = PatchQuestion::GetInlet(GetCurrentEngine(), pObject, i);
         TBaseShellHook* pShellHook = GetPatchForm()->GetBaseShellHook(pShell);
         InletPortList->Items->AddObject(pShellHook->GetName(), pShellHook);
         }
    InletPortUpDown->Max = 0;
    InletPortUpDown->Min = (short)-((int)BaseShellQuestion::GetNumInlets(GetCurrentEngine(), pObject)-1);
}
void TEditPatchForm::LoadOutletPorts()
{
    OutletPortList->Clear();
    //load the outlets
    for(unsigned i = 0; i < BaseShellQuestion::GetNumOutlets(GetCurrentEngine(), pObject); i++)
        {
         P_BASESHELL pShell = PatchQuestion::GetOutlet(GetCurrentEngine(), pObject, i);
         TBaseShellHook* pShellHook = GetPatchForm()->GetBaseShellHook(pShell);
         OutletPortList->Items->AddObject(pShellHook->GetName(), pShellHook);
         }
    OutletPortUpDown->Max = 0;
    OutletPortUpDown->Min = (short) -((int)BaseShellQuestion::GetNumOutlets(GetCurrentEngine(), pObject)-1);
}
void __fastcall TEditPatchForm::InletPortListEnter(TObject *Sender)
{
    InletPortUpDown->Visible = (InletPortList->Items->Count > 1);
    InletPortUpDown->Position = (short)- InletPortList->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TEditPatchForm::InletPortListExit(TObject *Sender)
{
    InletPortUpDown->Visible = false;

}
//---------------------------------------------------------------------------

void __fastcall TEditPatchForm::OutletPortListEnter(TObject *Sender)
{
    OutletPortUpDown->Visible = (OutletPortList->Items->Count > 1);
    OutletPortUpDown->Position = (short)- OutletPortList->ItemIndex;    
}
//---------------------------------------------------------------------------

void __fastcall TEditPatchForm::OutletPortListExit(TObject *Sender)
{
    OutletPortUpDown->Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall TEditPatchForm::InletPortUpDownClick(TObject *Sender,
      TUDBtnType Button)
{

    int ItemIndex = InletPortList->ItemIndex;
    if(ItemIndex < 0)
        return;

    if (Button != Comctrls::btPrev)//pressed up
        {
        if(ItemIndex < 1)
            return;
        TObject* TempOb = InletPortList->Items->Objects[ItemIndex];
        String TempSt = InletPortList->Items->Strings[ItemIndex];
        InletPortList->Items->Strings[ItemIndex] = InletPortList->Items->Strings[ItemIndex - 1];
        InletPortList->Items->Objects[ItemIndex] = InletPortList->Items->Objects[ItemIndex - 1];
        InletPortList->Items->Strings[ItemIndex -1 ] = TempSt;
        InletPortList->Items->Objects[ItemIndex -1] = TempOb;
        InletPortList->ItemIndex--;
        }
    else
        {
        if(ItemIndex == InletPortList->Items->Count)
            return;
        TObject* TempOb = InletPortList->Items->Objects[ItemIndex];
        String TempSt = InletPortList->Items->Strings[ItemIndex];
        InletPortList->Items->Strings[ItemIndex] = InletPortList->Items->Strings[ItemIndex + 1];
        InletPortList->Items->Objects[ItemIndex] = InletPortList->Items->Objects[ItemIndex + 1];
        InletPortList->Items->Strings[ItemIndex +1 ] = TempSt;
        InletPortList->Items->Objects[ItemIndex +1] = TempOb;
        InletPortList->ItemIndex++;
        InletPortUpDown->Position = (short)- InletPortList->ItemIndex;
        }
    InletPortUpDown->Position = (short)- InletPortList->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TEditPatchForm::InletPortListClick(TObject *Sender)
{
    InletPortUpDown->Position = (short)- InletPortList->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TEditPatchForm::OutletPortListClick(TObject *Sender)
{
    OutletPortUpDown->Position = (short)- OutletPortList->ItemIndex;    
}
//---------------------------------------------------------------------------

void __fastcall TEditPatchForm::OutletPortUpDownClick(TObject *Sender,
      TUDBtnType Button)
{

    int ItemIndex = OutletPortList->ItemIndex;
    if(ItemIndex < 0)
        return;

    if (Button != Comctrls::btPrev)//pressed up
        {
        if(ItemIndex < 1)
            return;
        TObject* TempOb = OutletPortList->Items->Objects[ItemIndex];
        String TempSt = OutletPortList->Items->Strings[ItemIndex];
        OutletPortList->Items->Strings[ItemIndex] = OutletPortList->Items->Strings[ItemIndex - 1];
        OutletPortList->Items->Objects[ItemIndex] = OutletPortList->Items->Objects[ItemIndex - 1];
        OutletPortList->Items->Strings[ItemIndex -1 ] = TempSt;
        OutletPortList->Items->Objects[ItemIndex -1] = TempOb;
        OutletPortList->ItemIndex--;
        }
    else
        {
        if(ItemIndex == OutletPortList->Items->Count)
            return;
        TObject* TempOb = OutletPortList->Items->Objects[ItemIndex];
        String TempSt = OutletPortList->Items->Strings[ItemIndex];
        OutletPortList->Items->Strings[ItemIndex] = OutletPortList->Items->Strings[ItemIndex + 1];
        OutletPortList->Items->Objects[ItemIndex] = OutletPortList->Items->Objects[ItemIndex + 1];
        OutletPortList->Items->Strings[ItemIndex +1 ] = TempSt;
        OutletPortList->Items->Objects[ItemIndex +1] = TempOb;
        OutletPortList->ItemIndex++;
        OutletPortUpDown->Position = (short)- OutletPortList->ItemIndex;
        }
    OutletPortUpDown->Position = (short)- OutletPortList->ItemIndex;

}
//---------------------------------------------------------------------------

void TEditPatchForm::StoreInletPorts()
{
    //swap any Inlet ports that have changed
    for(int i = 0; i < InletPortList->Items->Count -1; i++)
        {
        TBaseShellHook* pShell = (TBaseShellHook*)(InletPortList->Items->Objects[i]);
        unsigned OldPortNumber = PatchQuestion::GetInletPortNumber(GetCurrentEngine(), pShell->GetHook());
        if(OldPortNumber != (unsigned)i)
            {
            PatchQuestion::SwapInlets(GetCurrentEngine(), pObject, OldPortNumber, (unsigned)i);
            GetPatchForm()->SetModified();
            }
        }
}
void TEditPatchForm::StoreOutletPorts()
{
    for(int i = 0; i < OutletPortList->Items->Count -1; i++)
        {
        TBaseShellHook* pShell = (TBaseShellHook*)(OutletPortList->Items->Objects[i]);
        unsigned OldPortNumber = PatchQuestion::GetOutletPortNumber(GetCurrentEngine(), pShell->GetHook());
        if(OldPortNumber != (unsigned)i)
            {
            PatchQuestion::SwapOutlets(GetCurrentEngine(), pObject, OldPortNumber, (unsigned)i);
            GetPatchForm()->SetModified();
            }
        }

}
void __fastcall TEditPatchForm::InletPortListDblClick(TObject *Sender)
{
    int ItemIndex = InletPortList->ItemIndex;
    if(ItemIndex > 0)
        ((TBaseShellHook*) InletPortList->Items->Objects[ItemIndex])
            ->DisplayEditForm();
}
//---------------------------------------------------------------------------

void __fastcall TEditPatchForm::OutletPortListDblClick(TObject *Sender)
{
    int ItemIndex = OutletPortList->ItemIndex;
    if(ItemIndex > 0)
        ((TBaseShellHook*) OutletPortList->Items->Objects[ItemIndex])
            ->DisplayEditForm();
}
//---------------------------------------------------------------------------

