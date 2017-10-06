//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ConnectorEditUnit.h"
#include "IdentityHook.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConnectorEditForm *ConnectorEditForm;
//---------------------------------------------------------------------------
__fastcall TConnectorEditForm::TConnectorEditForm(TConnectorHook* Owner)
	: TForm(Owner)
{
    HelpContext = Owner->HelpContext ();
    pObject = ((TConnectorHook*)Owner)->GetHook();

	UpdateForm();
}



void TConnectorEditForm::LoadName()
{
  String Name = ((TConnectorHook*)Owner)->GetName();
  EditName->SetTextBuf(Name.c_str()); //Puts Text into Buffer
 }

void TConnectorEditForm::LoadComment()
{
  String Comment = ((TConnectorHook*)Owner)->GetComment();
  EditComment->SetTextBuf(Comment.c_str()); //Puts Text into Buffer
}

void TConnectorEditForm::StoreName()
{
  String Name = EditName->Text;

  ((TConnectorHook*)Owner)->SetHookName(Name);
  ((TConnectorHook*)Owner)->UpdateObject();
}

void TConnectorEditForm::StoreComment()
{
  String Comment = EditComment->Text;

  ((TConnectorHook*)Owner)->SetComment(Comment);
  ((TConnectorHook*)Owner)->UpdateObject();

}
//---------------------------------------------------------------------------
void __fastcall TConnectorEditForm::Button1Click(TObject *Sender)
{
	StoreName();
	StoreComment();
    Close();
}
//---------------------------------------------------------------------------

void TConnectorEditForm::UpdateForm()
{
  unsigned index = ((TConnectorHook*) Owner)->OutletIndex ();
	LoadName();
	LoadComment();
  LoadOutletMemo();
  LoadInletMemo();
  OutletIndex->SetTextBuf(IntToStr(index).c_str ());
}
//---------------------------------------------------------------------------




void __fastcall TConnectorEditForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	if(dynamic_cast<TConnectorHook*>(Owner))
   	((TConnectorHook*)Owner)->ClearEditForm();

   Action = caFree;
}
//---------------------------------------------------------------------------

void TConnectorEditForm::LoadOutletMemo()
{
    //get details of Outlet Base
    TBaseShellHook* OutletHook = GetPatchForm()->GetBaseShellHook(ConnectorQuestion::GetOutletBase(GetCurrentEngine(), pObject));
    String Type = OutletHook->GetType();
    String Name = OutletHook->GetName();

    //get details about the outlet
    unsigned OutletNum = ConnectorQuestion::GetOutletNum(GetCurrentEngine(), pObject);
    char Buff [MAX_NAME_LEN +1]; //used to get outlet name
    BaseShellQuestion::GetOutletName(GetCurrentEngine(), OutletHook->GetHook(), OutletNum, Buff, MAX_NAME_LEN);
    String OutletName(Buff);

    //create a list
    TStrings* TempList = new TStringList();
    TempList->Add("Type - " + Type);
    TempList->Add("Name - " + Name);
    TempList->Add("Outlet Number " + IntToStr(OutletNum +1));
    TempList->Add(OutletName);
    //Store in Memo
    OutletMemo->Clear();
    OutletMemo->Lines->AddStrings(TempList);

    delete TempList;
}
//------------------------------------------------------------------------------
void TConnectorEditForm::LoadInletMemo()
{

    TBaseShellHook* InletHook = GetPatchForm()->GetBaseShellHook(ConnectorQuestion::GetInletBase(GetCurrentEngine(), pObject));
    String Type = InletHook->GetType();
    String Name = InletHook->GetName();

    //get details about the outlet
    unsigned InletNum = ConnectorQuestion::GetInletNum(GetCurrentEngine(), pObject);
    char Buff [MAX_NAME_LEN +1];
    BaseShellQuestion::GetInletName(GetCurrentEngine(), InletHook->GetHook(), InletNum, Buff, MAX_NAME_LEN);
    String InletName(Buff);

    //create a list
    TStrings* TempList = new TStringList();
    TempList->Add("Type - " + Type);
    TempList->Add("Name - " +Name);
    TempList->Add("Inlet Number " + IntToStr(InletNum +1));
    TempList->Add(InletName);
    //Store in Memo
    InletMemo->Clear();
    InletMemo->Lines->AddStrings(TempList);

    delete TempList;
}
//--------------------------------------------------------------------




void __fastcall TConnectorEditForm::OutletMemoDblClick(TObject *Sender)
{
   	((TConnectorHook*)Owner)->DisplayOutlet();
}
//---------------------------------------------------------------------------

void __fastcall TConnectorEditForm::InletMemoDblClick(TObject *Sender)
{
   	((TConnectorHook*)Owner)->DisplayInlet();

}
//---------------------------------------------------------------------------

void __fastcall TConnectorEditForm::EditNameExit(TObject *Sender)
{
	StoreName();
    ((TConnectorHook*)Owner)->UpdateObject();
}
//---------------------------------------------------------------------------

void __fastcall TConnectorEditForm::EditCommentExit(TObject *Sender)
{
	StoreComment();
}

TPatchForm* TConnectorEditForm::GetPatchForm()const
{
    return ((TConnectorHook*)Owner)->GetPatchForm();
}
//---------------------------------------------------------------------------

PresentationQuestion* TConnectorEditForm::GetCurrentEngine ()
{
  return GetPatchForm()->GetCurrentEngine ();
}


