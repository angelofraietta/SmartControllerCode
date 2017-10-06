//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "IdentityHook.h"
//#include "BaseShel.h"
//#include "Connect.h"
#include "BaseShellsUnit.h"
#include "ConnectorEditUnit.h"
#include "PatchUnit.h"                                                  

//#include "Patch.h"
#include "PerformanceView.h"

//---------------------------------------------------------------------------
//load the map for creating edit forms
CreateFormMapType TBaseShellHook::EditFormMap = CreateFormMap();

TBaseShellHook::TBaseShellHook(TPatchForm* Owner, P_BASESHELL Hook)
	:TComponent(Owner), pHook(Hook), pEditForm(NULL), ViewNode(NULL), sHookName(""),
  m_help_Context (0), _owner(Owner)
{
  char Buf [MAX_NAME_LEN +1];

    GetHookName();

	if (pHook())
		{
    IdentityQuestion::GetType(GetCurrentEngine(), pHook, Buf, MAX_NAME_LEN);
    m_type  = Buf;
    }
   else
   	m_type = "";

  m_help_Context = TTypeElementList::HelpContext (GetType ());
}

__fastcall TBaseShellHook::~TBaseShellHook()
{
    if(pHook())
        GetPatchForm()->ClearObject(pHook);
    if  (pEditForm)
        pEditForm->Close();
}

P_BASESHELL TBaseShellHook::GetHook()
{
	return pHook;
}

void TBaseShellHook::Reset()
{
    BaseShellQuestion::Reset(GetCurrentEngine(), pHook);
}

void TBaseShellHook::SetHookName(String Name)
{
	if (!pHook)
    	return;

  IdentityQuestion::SetName(GetCurrentEngine(), pHook,  Name.c_str ());

    GetHookName();
    if (pEditForm)
    	pEditForm->UpdateForm();
}

void TBaseShellHook::SetComment(String Comment)
{
	if (pHook())
    IdentityQuestion::SetComment(GetCurrentEngine(), pHook,  Comment.c_str ());
   	    
}

const String& TBaseShellHook::GetName()
{
   	return sHookName;

}

void TBaseShellHook::GetHookName()
{
    char* Buf = new char[MAX_NAME_LEN +1];
    IdentityQuestion::GetName(GetCurrentEngine(), pHook, Buf, MAX_NAME_LEN);

    sHookName = String(Buf);
    delete []Buf;
}

TPatchForm* TBaseShellHook::GetPatchForm()
{
    return _owner;
}

String TBaseShellHook::GetComment()
{
	if (pHook())
		{
        char* Buf = new char[MAX_COMMENT_LEN +1];
        IdentityQuestion::GetComment(GetCurrentEngine(), pHook, Buf, MAX_COMMENT_LEN);

        String SBuff(Buf);
        delete []Buf;
        return SBuff;
        }
   else
   	return "";

}

String TBaseShellHook::GetHint()
{
    return GetType();
}

void  TBaseShellHook::DisplayEditForm()
{
	if (!pEditForm) //create a form
        {
        if(EditFormMap.count(GetType())&& EditFormMap[GetType()])//must lso have a type of form
            pEditForm =(TBaseShellEditForm*) EditFormMap[GetType()](this);
        else
       		pEditForm = new TBaseShellEditForm(this);
        }
	pEditForm->Show();
}

void  TBaseShellHook::ClearEditForm()
{
	// clear any reference to the Edit Form
  	pEditForm = NULL;
}

void  TBaseShellHook::Update()
{
	if (ViewNode)
    	ViewNode->Text = GetName();
    if (pEditForm)
    	pEditForm->UpdateForm();
}

void  TBaseShellHook::SetViewNode(TTreeNode* Node)
{
	ViewNode = Node;
}

void TBaseShellHook::DeleteHook()
{
    if (pEditForm)
        {
        pEditForm->Close();
        pEditForm = NULL;
        }
	if(!pHook)
    	return;
     //remove from map
    GetPatchForm()->ClearObject(pHook);


   P_PATCH HookParent = IdentityQuestion::GetParent(GetCurrentEngine(), pHook);
	PatchQuestion::DetachBaseShellObject(GetCurrentEngine(), HookParent, pHook); // remove from Patch

    //now get connectors that have been detached
    P_CONNECTOR pCon = PatchQuestion::GetDeadConnector(GetCurrentEngine(), HookParent);
    while(pCon())
        {
        //tell patch form
        GetPatchForm()->RemoveConnector(pCon);

        pCon = PatchQuestion::GetDeadConnector(GetCurrentEngine(), HookParent);
        }
	pHook = (DWORD)0;
   //if the object is an inlet or outlet, Connectors from its
   //parent's patch need to be removed
   HookParent = IdentityQuestion::GetParent(GetCurrentEngine(), HookParent);
   if(HookParent())
      {
      pCon = PatchQuestion::GetDeadConnector(GetCurrentEngine(), HookParent);
      while(pCon())
        {
        //tell patch form
        GetPatchForm()->RemoveConnector(pCon);

        pCon = PatchQuestion::GetDeadConnector(GetCurrentEngine(), HookParent);
        }
      }
}

TTreeNode* TBaseShellHook::GetNode()
{
	return ViewNode;
}

bool TBaseShellHook::operator < (TBaseShellHook& Ref)
{
    P_PATCH PatchParent = IdentityQuestion::GetParent(GetCurrentEngine(), pHook);
    unsigned wPosition = PatchQuestion::FindBaseShellPosition(GetCurrentEngine(), PatchParent, pHook);
    unsigned wRefPosition = PatchQuestion::FindBaseShellPosition(GetCurrentEngine(), PatchParent, Ref.pHook);

    return wPosition < wRefPosition;
}

void TBaseShellHook::Delete()
{
   //releases only the memory it owns
    if(!ViewNode)
      return;

   ViewNode->Delete();
}

bool TBaseShellHook::KillObject(TBaseShellHook* pObjectHook)
  {
  TPatchForm* pPatchForm = pObjectHook->GetPatchForm();

  TTreeNode* Node = pObjectHook->GetNode();
  //clear from performance views
  TTreeNode* PatchNode = Node->Parent->Parent;
  TTreeNode* ViewNode = PatchNode->GetLastChild()->getFirstChild();

  while(ViewNode)
    {
    ((TPerformanceView*)(ViewNode->Data))->RemoveObject(pObjectHook->GetHook());
    ViewNode = ViewNode->getNextSibling();
    }

  pObjectHook->DeleteHook();      //delete inside the patch
  pObjectHook->Delete();          //free itself from node
  pPatchForm->SetModified();
  return true;
  }

PresentationQuestion* TBaseShellHook::GetCurrentEngine ()
{
  return GetPatchForm()->GetCurrentEngine ();
}
//---------------------------------------------------------------------------
TConnectorHook::TConnectorHook(TPatchForm* Owner, P_CONNECTOR Hook)
	:TComponent(Owner), pHook(Hook), ViewNode(NULL), _owner(Owner)
{
    ValidConnection = ConnectorQuestion::IsValid(GetCurrentEngine(), pHook);
    //m_help_Context = HID_CONNECTORS;
}

__fastcall TConnectorHook::~TConnectorHook()
{
    if(pHook())
        GetPatchForm()->ClearConnector(pHook);
    if(pEditForm)
        pEditForm->Close();
}

P_CONNECTOR TConnectorHook::GetHook()
{
	return pHook;
}
void TConnectorHook::SetHookName(String Name)
{
    IdentityQuestion::SetName(GetCurrentEngine(), pHook,  Name.c_str ());

    if(pEditForm)
        pEditForm->UpdateForm();
}

void TConnectorHook::SetComment(String Comment)
{
  IdentityQuestion::SetComment(GetCurrentEngine(), pHook, Comment.c_str ());
    if(pEditForm)
        pEditForm->UpdateForm();

}

String TConnectorHook::GetName()
{
	if (pHook())
		{
        char* Buf = new char[MAX_NAME_LEN +1];
        IdentityQuestion::GetName(GetCurrentEngine(), pHook, Buf, MAX_NAME_LEN);
        String SBuff(Buf);
        delete []Buf;
        return SBuff;
        }
   else
   	return "";
}

String TConnectorHook::GetComment()
{
	if (pHook())
		{
        char* Buf = new char[MAX_COMMENT_LEN +1];
        IdentityQuestion::GetComment(GetCurrentEngine(), pHook, Buf, MAX_COMMENT_LEN);
        String SBuff(Buf);
        delete []Buf;
        return SBuff;
        }
   else
   	return "";
}


String TConnectorHook::GetHint()
{
     String Comment = GetComment();
     if (Comment == "") //no comment
     	{
        //get outlet details
        P_BASESHELL pOutlet = ConnectorQuestion::GetOutletBase(GetCurrentEngine(), pHook);
        unsigned wOutletNum = ConnectorQuestion::GetOutletNum(GetCurrentEngine(), pHook);
		String OutletType = GetPatchForm()->GetBaseShellHook(pOutlet)->GetType();
    	String OutletName = GetPatchForm()->GetBaseShellHook(pOutlet)->GetName();

        // get Inlet details
        P_BASESHELL pInlet = ConnectorQuestion::GetInletBase(GetCurrentEngine(), pHook);
        unsigned wInletNum = ConnectorQuestion::GetInletNum(GetCurrentEngine(), pHook);
		String InletType = GetPatchForm()->GetBaseShellHook(pInlet)->GetType();
    	String InletName = GetPatchForm()->GetBaseShellHook(pInlet)->GetName();
        // return the addition of these details
        return String(OutletType + " - " + OutletName + " Outlet " + IntToStr(wOutletNum) +
        			  " -> " + InletType + " - " + InletName + " Inlet " + IntToStr(wInletNum));
        }
     else
     	return Comment;
}


void  TConnectorHook::DisplayEditForm()
{
	if (!pEditForm) //create a form
   		pEditForm = new TConnectorEditForm(this);
    pEditForm->Show();

}

void  TConnectorHook::ClearEditForm()
{
	// clear any reference to the Edit Form
  	pEditForm = NULL;
}

void  TConnectorHook::SetViewNode(TTreeNode* Node)
{
	ViewNode = Node;
}

void  TConnectorHook::UpdateObject()
{
	if (ViewNode)
    	ViewNode->Text = GetName();
}

void TConnectorHook::DisplayOutlet()
{
    P_BASESHELL pOutlet = ConnectorQuestion::GetOutletBase(GetCurrentEngine(), pHook);
    ((TPatchForm*)Owner)->DisplayBaseShell(pOutlet);
}

void TConnectorHook::DisplayInlet()
{
    P_BASESHELL pInlet = ConnectorQuestion::GetInletBase(GetCurrentEngine(), pHook);
    ((TPatchForm*)Owner)->DisplayBaseShell(pInlet);
}

void TConnectorHook::DeleteHook()
{
    P_PATCH pParent = IdentityQuestion::GetParent(GetCurrentEngine(), pHook);
    //remove the hook
    PatchQuestion::DetachConnector(GetCurrentEngine(), pParent, pHook); // remove from Patch



	pHook = (DWORD)0;
}

TTreeNode* TConnectorHook::GetNode()
{
	return ViewNode;
}

bool TConnectorHook::CanConnectInlet(P_BASESHELL pTestBase, unsigned InletNum)
{
    //Inlet and outlet must share same Parent
    //get inlet base parent
    P_BASESHELL pOutletBase = ConnectorQuestion::GetOutletBase(GetCurrentEngine(), pHook);
    if(!pOutletBase || !pTestBase)
        return false; //must have a base

    P_PATCH OutletParent = IdentityQuestion::GetParent(GetCurrentEngine(), pOutletBase);

    if  (*OutletParent  != *IdentityQuestion::GetParent(GetCurrentEngine(), pTestBase)
        || !OutletParent)
        return false;

	//set the internals
	ConnectorQuestion::SetInletBase(GetCurrentEngine(), pHook, pTestBase);
    ConnectorQuestion::SetInletNum(GetCurrentEngine(), pHook, InletNum);

    //see if connection is possible
	bool CanConnect = BaseShellQuestion::CanConnectInlet(GetCurrentEngine(), pTestBase,InletNum, pHook );

    if(CanConnect)
        return true;
    else
        {
    	ConnectorQuestion::SetInletBase(GetCurrentEngine(), pHook, (DWORD)0);
        return false;
        }
}


bool TConnectorHook::CanConnectOutlet(P_BASESHELL pTestBase, unsigned OutletNum)
{
    //Inlet and outlet must share same Parent
    //get inlet base parent
    P_BASESHELL pInletBase = ConnectorQuestion::GetInletBase(GetCurrentEngine(), pHook);
    if(!pInletBase || !pTestBase)
        return false; //must have a base

    P_PATCH InletParent = IdentityQuestion::GetParent(GetCurrentEngine(), pInletBase);

    if  (*InletParent  != *IdentityQuestion::GetParent(GetCurrentEngine(), pTestBase)
        || !InletParent)
        return false;

	//set the internals
	ConnectorQuestion::SetOutletBase(GetCurrentEngine(), pHook, pTestBase);
    ConnectorQuestion::SetOutletNum(GetCurrentEngine(), pHook, OutletNum);

    //see if connection is possible
	bool CanConnect = BaseShellQuestion::CanConnectOutlet(GetCurrentEngine(), pTestBase,OutletNum, pHook );

    if(CanConnect)
        return true;
    else
        {
    	ConnectorQuestion::SetOutletBase(GetCurrentEngine(), pHook, (DWORD)0);
        return false;
        }

}

void TConnectorHook::SetOutlet(P_BASESHELL pBase, unsigned OutletNum)
{
    if (ValidConnection)
        return;
	//set internals
	ConnectorQuestion::SetOutletBase(GetCurrentEngine(), pHook, pBase);
    ConnectorQuestion::SetOutletNum(GetCurrentEngine(), pHook, OutletNum);
}


void TConnectorHook::SetInlet(P_BASESHELL pBase, unsigned InletNum)
{
    if(ValidConnection)
        return;
	//set internals
	ConnectorQuestion::SetInletBase(GetCurrentEngine(), pHook, pBase);
    ConnectorQuestion::SetInletNum(GetCurrentEngine(), pHook, InletNum);
}

bool TConnectorHook::MakeConnection()
{
    //make the connection
    ValidConnection = ConnectorQuestion::MakeConnection(GetCurrentEngine(), pHook);
    SetHookName("NewConnector");
    SetComment("");
    //set the parent
    P_PATCH pParent = IdentityQuestion::GetParent(GetCurrentEngine(), ConnectorQuestion::GetOutletBase(GetCurrentEngine(), pHook));
    IdentityQuestion::SetParent(GetCurrentEngine(), pHook, pParent);
    //Add to ConnectorList in Patch
    PatchQuestion::AddConnector(GetCurrentEngine(), pParent,pHook);
    ((TPatchForm*)Owner)->AddConnector(this);
    return ValidConnection;
}

bool TConnectorHook::operator < (TConnectorHook& Ref)
{
    //check that they are in the same Patch
    if (*IdentityQuestion::GetParent(GetCurrentEngine(), pHook) != *IdentityQuestion::GetParent(GetCurrentEngine(), Ref.pHook))
        throw String("Connectors in different Patches cannot be compared");

    P_PATCH pParent = IdentityQuestion::GetParent(GetCurrentEngine(), pHook);
    P_BASESHELL ThisOutlet = ConnectorQuestion::GetOutletBase(GetCurrentEngine(), pHook);
    P_BASESHELL RefOutlet = ConnectorQuestion::GetOutletBase(GetCurrentEngine(), Ref.pHook);
    //compare OutletBases
    if (*ThisOutlet != *RefOutlet) // the Outlets will define order
        {
        unsigned wPosition = PatchQuestion::FindBaseShellPosition(GetCurrentEngine(), pParent, ThisOutlet);
        unsigned wRefPosition = PatchQuestion::FindBaseShellPosition(GetCurrentEngine(), pParent, RefOutlet);
        return wPosition < wRefPosition;
        }
     //are in same object, compare Outlet Number
     unsigned wOutletNumber = ConnectorQuestion::GetOutletNum(GetCurrentEngine(), pHook);
     unsigned wRefOutletNumber = ConnectorQuestion::GetOutletNum(GetCurrentEngine(), Ref.pHook);
     if (wOutletNumber != wRefOutletNumber)
        return wOutletNumber < wRefOutletNumber;

     //are in same outlet check Position
     bool Compare;
     try{
        Compare = BaseShellQuestion::FindOutletConnectorIndex(GetCurrentEngine(), ThisOutlet, wOutletNumber, pHook) <
                  BaseShellQuestion::FindOutletConnectorIndex(GetCurrentEngine(), ThisOutlet,wOutletNumber, Ref.pHook);
        }
     catch (const char* s) {throw String(s);}
        return Compare;
}

TPatchForm* TConnectorHook::GetPatchForm()const
{
  	return (TPatchForm*)Owner;
}

void TConnectorHook::Delete()
{

//releases only the memory it owns
    if(!ViewNode)
      return;

    ViewNode->Delete();
}

bool TConnectorHook::KillObject(TConnectorHook* pObjectHook)
  {
  TPatchForm* pPatchForm = pObjectHook->GetPatchForm();
  P_CONNECTOR pHook = pObjectHook->GetHook();
  pObjectHook->DeleteHook();
  pPatchForm->RemoveConnector(pHook);
  return true;
  }

unsigned TConnectorHook::OutletIndex () 
{
  return ConnectorQuestion::GetOutletIndex (GetCurrentEngine(), pHook) + 1;
}

PresentationQuestion* TConnectorHook::GetCurrentEngine ()
{
  return GetPatchForm()->GetCurrentEngine ();
}

TPatchForm* TConnectorHook::GetPatchForm()
{
    return _owner;
}


