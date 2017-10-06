//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "BaseShellsUnit.h"
#include "IdentityHook.h"	// contains declaration of TBaseShellHook

#include "CursorsUnit.h"
#include "FormRefresh.h"
#include "DragConnector.h"
#include "DragBaseShell.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define DRAG_THRESHOLD 3 //the number of pixels to befin a drag

TBaseShellEditForm *BaseShellEditForm;

//---------------------------------------------------------------------------
__fastcall TBaseShellEditForm::TBaseShellEditForm(TBaseShellHook* Owner)
	: TForm(Owner), fAllowUpdate(true)
{
  char buff [256];
  HelpContext = Owner->HelpContext ();

   pObject = ((TBaseShellHook*)Owner)->GetHook();
   LoadType();
   SetInletsTabs(); // sets the Tab list for inlet list
   SetOutletsTabs();//ditto for outlets
   UpdateForm();
   pRefresher = new TFormRefresh(this); //allows automatic updating
   InletsList->DragCursor = (TCursor)crHoldPlugDown;
   OutletsList->DragCursor = (TCursor)crHoldPlugUp;

   unsigned num_attributes = BaseShellQuestion::GetNumAttributes (GetCurrentEngine(), pObject);

    for (unsigned i = 0; i < num_attributes; i++)
    {
      BaseShellQuestion::GetAttributeName(GetCurrentEngine(), pObject, i, buff, 256);
      AttributeList->Items->Add (String(buff));

    }
   num_attributes = BaseShellQuestion::GetNumResetAttributes (GetCurrentEngine(), pObject);

    for (unsigned i = 0; i < num_attributes; i++)
    {
      BaseShellQuestion::GetResetAttributeName(GetCurrentEngine(), pObject, i, buff, 256);
      ResetAttributeList->Items->Add (String(buff));

    }

}

__fastcall TBaseShellEditForm::~TBaseShellEditForm()
{
    fAllowUpdate = false;

}

//----------------------------------------------------------------------------
TPatchForm* TBaseShellEditForm::GetPatchForm()
{
	if(dynamic_cast<TBaseShellHook*> (Owner))
    	return ((TBaseShellHook*)Owner)->GetPatchForm();
    else
    	return NULL;
}

void TBaseShellEditForm::LoadType()
{
  String Type = ((TBaseShellHook*)Owner)->GetType();
  TypeLabel->SetTextBuf(Type.c_str()); //Puts Text into Buffer
}

void TBaseShellEditForm::LoadName()
{
   if(EditName->Focused())
      return;
  String Name = ((TBaseShellHook*)Owner)->GetName();
  EditName->SetTextBuf(Name.c_str()); //Puts Text into Buffer
}

void TBaseShellEditForm::LoadComment()
{
   if(EditComment->Focused())
      return;
  String Comment = ((TBaseShellHook*)Owner)->GetComment();
  EditComment->SetTextBuf(Comment.c_str()); //Puts Text into Buffer
}

void TBaseShellEditForm::StoreName()
{
  String Name = EditName->Text;
  ((TBaseShellHook*)Owner)->SetHookName(Name);
  ((TBaseShellHook*)Owner)->Update();
}

void TBaseShellEditForm::StoreComment()
{
	if(!pObject)
   	return;

  String Comment = EditComment->Text;
  ((TBaseShellHook*)Owner)->SetComment(Comment);
  ((TBaseShellHook*)Owner)->Update();

}
//---------------------------------------------------------------------------







void __fastcall TBaseShellEditForm::EditNameClick(TObject *Sender)
{
	EditName->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::EditCommentClick(TObject *Sender)
{
	EditComment->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TBaseShellEditForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    fAllowUpdate = false;
    pRefresher->Terminate();
    ((TBaseShellHook*)Owner)->ClearEditForm();
    Action = caFree;

}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::ResetButtonClick(TObject *Sender)
{
   	((TBaseShellHook*)Owner)->Reset();
    UpdateForm();
}
//---------------------------------------------------------------------------
void TBaseShellEditForm::LoadData()
{
  char buff [256];
  int attribute_num = AttributeList->ItemIndex;
  if (attribute_num >= 0)
  {
    BaseShellQuestion::GetAttribute(GetCurrentEngine(), pObject, attribute_num, buff, 256);
    AttributeValue->SetTextBuf (buff);
  }

  attribute_num = ResetAttributeList->ItemIndex;
  if (attribute_num >= 0)
  {
    BaseShellQuestion::GetResetAttribute(GetCurrentEngine(), pObject, attribute_num, buff, 256);
    ResetAttributeValue->SetTextBuf (buff);
  }

}
void TBaseShellEditForm::UpdateForm()
{
    if(fAllowUpdate)
        {
    	  LoadName();
        //display the modified state
        ModifiedImage->Visible = IdentityQuestion::GetModified(GetCurrentEngine(), pObject);

        if (PageControl1->ActivePage->Name == "ConnectionsSheet")
            {
            LoadInletsList(); //loads list of inlet connections for display
       	    LoadOutletsList(); // ditto for outlets
            }
        else if (PageControl1->ActivePage->Name  == "GeneralSheet")
            LoadComment();
        else
            LoadData();
        }

}

void TBaseShellEditForm::SetInletsTabs()
 // sets the number of tabs to the number of Inlets on Tab list for inlet list
{
    TStrings* TempList = new TStringList();
    for (unsigned x = 0; x < BaseShellQuestion::GetNumInlets(GetCurrentEngine(), pObject); x++)
    	TempList->Add(IntToStr(x + 1));
    InletTab->Tabs = TempList;

    delete TempList;
}

void TBaseShellEditForm::SetOutletsTabs()
{
    TStrings* TempList = new TStringList();
    for (unsigned x = 0; x < BaseShellQuestion::GetNumOutlets(GetCurrentEngine(), pObject); x++)
    	TempList->Add(IntToStr(x +1));
    OutletTab->Tabs = TempList;

    delete TempList;

}

void TBaseShellEditForm::LoadInletsList()
 //loads list of inlet connections for display
{
    InletsList->Clear();
    if(InletTab->TabIndex < 0)
        {
        InletsList->Visible = false;
        return;
        }
	//which inlet
    unsigned InletNumber = (unsigned)InletTab->TabIndex;

    char Buff[MAX_NAME_LEN+1];

    BaseShellQuestion::GetInletName(GetCurrentEngine(), pObject, InletNumber, Buff, MAX_NAME_LEN);
    //get name of inlet
    String InletType = Buff;
    //asigne to label
    InletLabel->SetTextBuf(InletType.c_str());
    //GET NAMES OF CONNECTORS
    if(!GetPatchForm())
    	return;

    if (BaseShellQuestion::GetNumInlets(GetCurrentEngine(), pObject) == 0
        || InletNumber >= BaseShellQuestion::GetNumInlets(GetCurrentEngine(), pObject))
        {
        InletsList->Visible = false;
    	return;
        }
    else
        InletsList->Visible = true;

    unsigned NumConnectors = BaseShellQuestion::GetNumInletConnectors(GetCurrentEngine(), pObject, InletNumber);

    for (unsigned j = 0; j < NumConnectors; j++)
    	{
        P_CONNECTOR pCon = BaseShellQuestion::GetInletConnector(GetCurrentEngine(), pObject, InletNumber, j); // get connector
        TConnectorHook* pObjectHook = GetPatchForm()->GetConnectorHook(pCon);
        String ObName =  pObjectHook->GetName();
        if (ObName == "")
        	ObName = "No - Name";

        InletsList->Items->AddObject(ObName, pObjectHook);
        }
}

void TBaseShellEditForm::LoadOutletsList()
// ditto for outlets
{
    if (OutletTab->TabIndex < 0)
        {
        OutletsList->Visible = false;
        return;
        }

	unsigned OutletNumber = (unsigned) OutletTab->TabIndex;
    char Buff [MAX_NAME_LEN+1];

    BaseShellQuestion::GetOutletName(GetCurrentEngine(), pObject, OutletNumber, Buff, MAX_NAME_LEN);

    OutletLabel->SetTextBuf(Buff);
    //get name of inlet

    //GET NAMES OF CONNECTORS
    if(!GetPatchForm())
    	return;

    OutletsList->Clear();

    if(BaseShellQuestion::GetNumOutlets(GetCurrentEngine(), pObject) == 0
        || OutletNumber >= BaseShellQuestion::GetNumOutlets(GetCurrentEngine(), pObject))
        {
        OutletsList->Visible = false;
    	return;
        }
    else
        OutletsList->Visible = true;

    //get Inlet Container
    unsigned NumConnectors = BaseShellQuestion::GetNumOutletConnectors(GetCurrentEngine(), pObject, OutletNumber);

    for (unsigned j = 0; j < NumConnectors; j++)
    	{
        P_CONNECTOR pCon = BaseShellQuestion::GetOutletConnector(GetCurrentEngine(), pObject, OutletNumber, j); // get connector
        TConnectorHook* pObjectHook = GetPatchForm()->GetConnectorHook(pCon);
        String ObName =  pObjectHook->GetName();
        if (ObName == "")
        	ObName = "No - Name";

        OutletsList->Items->AddObject(ObName, pObjectHook);
        }
    OutletConnectorUpDown->Max = 0;
    OutletConnectorUpDown->Min = (short)-((int)NumConnectors-1);

}

void __fastcall TBaseShellEditForm::InletTabChange(TObject *Sender)
{
	LoadInletsList(); //load the connections list into List
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::OutletTabChange(TObject *Sender)
{
	LoadOutletsList(); //load the connections list into List

}
//---------------------------------------------------------------------------


void __fastcall TBaseShellEditForm::CancelButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::UpdateButtonClick(TObject *Sender)
{
	UpdateForm();
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::InletsListDblClick(TObject *Sender)
{
	int SelectedIndex = InletsList->ItemIndex;
	TConnectorHook* pCon = (TConnectorHook*)(InletsList->Items->Objects[SelectedIndex]);
    pCon->DisplayEditForm();
}
//---------------------------------------------------------------------------


void __fastcall TBaseShellEditForm::EditNameExit(TObject *Sender)
{
	StoreName();
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::EditCommentExit(TObject *Sender)
{
	StoreComment();
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::FormShow(TObject *Sender)
{
	WindowState = wsNormal;
   LoadData();
   UpdateForm();
}
//---------------------------------------------------------------------------





void __fastcall TBaseShellEditForm::OutletsListStartDrag(TObject *Sender,
      TDragObject *&DragObject)
{
	//create a new connection
	P_CONNECTOR TestCon = ConnectorQuestion::Create(GetCurrentEngine()); //make a test connector
    TDragConnector* pDragCon = new TDragConnector(TestCon, true, GetCurrentEngine(), this);

    OutletConnectImage->Visible = true; //display an image to show connection

    int OutletNum = OutletTab->TabIndex;
    pDragCon->SetOutlet(pObject, OutletNum);
    DragObject = pDragCon;
}
//---------------------------------------------------------------------------


void __fastcall TBaseShellEditForm::OutletsListMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(IdentityQuestion::CanSave(GetCurrentEngine(), pObject) && Button == mbRight) //Right button drag
       OutletsList->BeginDrag(false, DRAG_THRESHOLD );
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::OutletsListDblClick(TObject *Sender)
{
	TConnectorHook* pCon = (TConnectorHook*)(OutletsList->Items->Objects[OutletsList->ItemIndex]);
    pCon->DisplayEditForm();
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::InletsListDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
    //process an InletsList or OutletsList
    if(IsDragObject(Source)
        && dynamic_cast<TDragConnector*> ((TDragObject*)Source))
        {
        TDragConnector* pDragCon = (TDragConnector*)Source;
        Accept = (pDragCon->fConnectingToInlet)
            && pDragCon->CanConnectInlet(pObject, InletTab->TabIndex);
        }
    else
        Accept = false;
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::OutletsListDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
    if(IsDragObject(Source)
        && dynamic_cast<TDragConnector*> ((TDragObject*)Source))//see if is a drag object
        {
        TDragConnector* pCon = (TDragConnector*)Source;
        Accept = !(pCon->fConnectingToInlet)
            && pCon->CanConnectOutlet(pObject, OutletTab->TabIndex);
        }
    else
        Accept = false;
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::InletsListStartDrag(TObject *Sender,
      TDragObject *&DragObject)
{
	//create a new connection
	P_CONNECTOR TestCon = ConnectorQuestion::Create(GetCurrentEngine()); //make a test connector
    TDragConnector* pDragCon = new TDragConnector(TestCon, false, GetCurrentEngine(), this);
    InletConnectImage->Visible = true; //display an image to show connection
    int InletNum = InletTab->TabIndex;
    pDragCon->SetInlet(pObject, InletNum);
    DragObject = pDragCon;
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::InletsListMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(IdentityQuestion::CanSave(GetCurrentEngine(), pObject) && Button == mbRight) //Right button drag
       InletsList->BeginDrag(false, DRAG_THRESHOLD );
}

//---------------------------------------------------------------------------


void __fastcall TBaseShellEditForm::InletsListDragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
    TDragConnector* NewCon = (TDragConnector*) Source;
    NewCon->MakeConnection();
    TConnectorHook* pHook = new TConnectorHook(GetPatchForm(),NewCon->pCon);
    GetPatchForm()->AddConnector(pHook);
    LoadInletsList();
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::OutletsListDragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
    TDragConnector* NewCon = (TDragConnector*) Source;
    NewCon->MakeConnection();
    TConnectorHook* pHook = new TConnectorHook(GetPatchForm(),NewCon->pCon);
    GetPatchForm()->AddConnector(pHook);
    LoadOutletsList();
}
//---------------------------------------------------------------------------


void __fastcall TBaseShellEditForm::LocateButtonClick(TObject *Sender)
{
    GetPatchForm()->LocateBaseShell(pObject);
}

//---------------------------------------------------------------------------


void __fastcall TBaseShellEditForm::PageControl1Change(TObject *Sender)
{
    UpdateForm();
    fAllowUpdate = false;
}
//---------------------------------------------------------------------------

void TBaseShellEditForm::HideConnectionImages()
{
    OutletConnectImage->Visible = false;
    InletConnectImage->Visible = false;
    UpdateForm();
}

void __fastcall TBaseShellEditForm::BaseShellSendButtonClick(
      TObject *Sender)
{
   BaseShellQuestion::Send(GetCurrentEngine(), pObject);
   LoadData();   
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::EditNameChange(TObject *Sender)
{
   if(EditName->Focused())
      StoreName();   
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::EditCommentChange(TObject *Sender)
{
   if(EditComment->Focused())
      StoreComment();   
}
//---------------------------------------------------------------------------


void __fastcall TBaseShellEditForm::DragToView1Click(TObject *Sender)
{
   DragToViewButton->BeginDrag(false, DRAG_THRESHOLD );

}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::DragToViewButtonStartDrag(
      TObject *Sender, TDragObject *&DragObject)
{
      TBaseShellHook* ObjectHook = (TBaseShellHook*)Owner; //cast
      P_PATCH PatchParent = IdentityQuestion::GetParent(GetCurrentEngine(), ObjectHook->GetHook());
      TDragBaseShell* pDragObject = new TDragBaseShell(ObjectHook, PatchParent);
      DragObject = pDragObject;   
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::OutletsListClick(TObject *Sender)
{
    OutletConnectorUpDown->Position = (short)- OutletsList->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::OutletsListEnter(TObject *Sender)
{
    OutletConnectorUpDown->Visible = (OutletsList->Items->Count > 1);
    OutletConnectorUpDown->Position = (short)- OutletsList->ItemIndex;

}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::OutletsListExit(TObject *Sender)
{
    OutletConnectorUpDown->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::OutletConnectorUpDownClick(
      TObject *Sender, TUDBtnType Button)
{
    int ItemIndex = OutletsList->ItemIndex;
    if(ItemIndex < 0)
        return;

    if (Button != Comctrls::btPrev)//pressed up
        {
        if(ItemIndex < 1)
            return;
        TObject* TempOb = OutletsList->Items->Objects[ItemIndex];
        String TempSt = OutletsList->Items->Strings[ItemIndex];
        OutletsList->Items->Strings[ItemIndex] = OutletsList->Items->Strings[ItemIndex - 1];
        OutletsList->Items->Objects[ItemIndex] = OutletsList->Items->Objects[ItemIndex - 1];
        OutletsList->Items->Strings[ItemIndex -1 ] = TempSt;
        OutletsList->Items->Objects[ItemIndex -1] = TempOb;
        OutletsList->ItemIndex--;
        }
    else
        {
        if(ItemIndex == OutletsList->Items->Count)
            return;
        TObject* TempOb = OutletsList->Items->Objects[ItemIndex];
        String TempSt = OutletsList->Items->Strings[ItemIndex];
        OutletsList->Items->Strings[ItemIndex] = OutletsList->Items->Strings[ItemIndex + 1];
        OutletsList->Items->Objects[ItemIndex] = OutletsList->Items->Objects[ItemIndex + 1];
        OutletsList->Items->Strings[ItemIndex +1 ] = TempSt;
        OutletsList->Items->Objects[ItemIndex +1] = TempOb;
        OutletsList->ItemIndex++;
        OutletConnectorUpDown->Position = (short)- OutletsList->ItemIndex;
        }
    OutletConnectorUpDown->Position = (short)- OutletsList->ItemIndex;
}
//---------------------------------------------------------------------------
void TBaseShellEditForm::StoreOutletConnectors()
{
  for(int i = 0; i < OutletsList->Items->Count -1; i++)
  {
    TConnectorHook* pConHook = (TConnectorHook*)(OutletsList->Items->Objects[i]);
    P_CONNECTOR pCon = pConHook->GetHook();
    unsigned OutletNum = OutletTab->TabIndex;
    unsigned OldConnectorIndex = ConnectorQuestion::GetOutletIndex(GetCurrentEngine(), pCon);

    if(OldConnectorIndex != (unsigned)i)
    {
      BaseShellQuestion::SwapOutletConnector(GetCurrentEngine(), pObject, OutletNum, OldConnectorIndex, (unsigned)i);
      GetPatchForm()->SetModified();
    }
  }

}

void __fastcall TBaseShellEditForm::REorderButtonClick(TObject *Sender)
{
    StoreOutletConnectors();
    UpdateForm();
}
//---------------------------------------------------------------------------


void __fastcall TBaseShellEditForm::AttributeListClick(TObject *Sender)
{
  LoadData();  
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::ResetAttributeListClick(
      TObject *Sender)
{
  LoadData();  
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::AttributeValueEnter(TObject *Sender)
{
  LoadData();
  fAllowUpdate = false;
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::AttributeValueExit(TObject *Sender)
{
  fAllowUpdate = true;
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::AttributeValueKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if (Key == 0x0d)
  {
    int attribute_num = AttributeList->ItemIndex;
    if (attribute_num >= 0)
    {
      BaseShellQuestion::SetAttribute(GetCurrentEngine(), pObject, attribute_num, AttributeValue->Text.c_str());
    }

  }
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::ResetAttributeValueKeyDown(
      TObject *Sender, WORD &Key, TShiftState Shift)
{
  if (Key == 0x0d)
  {
    int attribute_num = ResetAttributeList->ItemIndex;
    if (attribute_num >= 0)
    {
      BaseShellQuestion::SetResetAttribute(GetCurrentEngine(), pObject, attribute_num, ResetAttributeValue->Text.c_str());
    }

  }
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::ResetAttributeValueEnter(
      TObject *Sender)
{
  LoadData();
  fAllowUpdate = false;
}
//---------------------------------------------------------------------------

void __fastcall TBaseShellEditForm::ResetAttributeValueExit(
      TObject *Sender)
{
  fAllowUpdate = false;
}
//---------------------------------------------------------------------------

PresentationQuestion* TBaseShellEditForm::GetCurrentEngine ()
{
  return GetPatchForm()->GetCurrentEngine ();
}
