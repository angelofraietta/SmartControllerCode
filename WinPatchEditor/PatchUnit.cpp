//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "PatchUnit.h"

#include "IdentityHook.h"

#include "ViewFormUnit.h"
#include "NewObjectsList.h"
#include "TypeElementUnit.h"
#include "TypeNames.h"
#include "PerformanceView.h"
#include "EditPatchUnit.h"
#include "Main.h"
#include "SaveChanged.h"
#include "ErrorUnit.h"
#include "DragBaseShell.h"
#include "DragViewNode.h"
#include "fileQuestion.h"
#include "ErrorUnit.h"
#include "viewquestion.h"

//define the Image list Indexes
#define FOLDER_CLOSED 1
#define FOLDER_OPENED 2
#define PATCH_ICON 3
#define OBJECT_ICON 4
#define CONNECTOR_ICON 5
#define VIEW_ICON 6
#define UWS_ICON 7
#define PATCH_DISK_ICON 8
#define OBJECT_DISK_ICON 9
#define CONNECTOR_DISK_ICON 10
#define VIEW_DISK_ICON 11

// define Patch file Parameters
#define FILE_TYPE 4
//static const char* START_PATCH_ID = "<PATCH>";
static const char* END_PATCH_ID = "<ENDPATCH>";


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define VIEW_EXT ".vw" //the view file extensions
#define PATCH_EXT ".pch"

// define Treenode names
#define DEVICES_TEXT "Devices"
#define LINKS_TEXT "Links"
#define VIEWS_TEXT "Views"

#define NO_TREE_SORT //stop sorting of tree view
#define DRAG_THRESHOLD 3 //the number of pixels to befin a drag

TPatchForm *PatchForm;

TTreeNode* TPatchForm::EditedNode = NULL;
unsigned TPatchForm::wNumNewPatches = 0; //initialise
//---------------------------------------------------------------------------
__fastcall TPatchForm::TPatchForm(TComponent* Owner)
	: TForm(Owner), Modified(false), this_engine (GetSelectedEngine ())
{
	wNumNewPatches++;

	String Name("New Patch File" + IntToStr(wNumNewPatches));

    pPatch = PatchQuestion::MakeNew(GetCurrentEngine(), Name.c_str());

    Caption = Name;

    if (!(pPatch.Key()))
    {
      ErrorForm->DisplayMessage ("Unable to Create Patch or establish Comm Link");
      Close();
    }
}

__fastcall TPatchForm::TPatchForm(TComponent* Owner, P_PATCH ParentPatch)
	: TForm(Owner), Modified(false), pPatch(ParentPatch) ,this_engine (GetSelectedEngine ())
{
}
//---------------------------------------------------------------------------
__fastcall TPatchForm::TPatchForm(TComponent *Owner, String FileName)
	: TForm(Owner), Modified(false), this_engine (GetSelectedEngine ())
{
// Load a patch from file
    Screen->Cursor = crHourGlass;
    AnsiString filename = ExtractFileName(FileName);

    pPatch = PatchQuestion::LoadPatchFile(GetCurrentEngine(), filename.c_str(), (DWORD)0);
    Screen->Cursor = crDefault;
    if (pPatch())
        {
        Caption = FileName;
        }
    else
        Close();
}

__fastcall TPatchForm::~TPatchForm()
{
    delete PatchTreeView;//must be destroyed before Form destruction coplete

    PresentationQuestion* simulator = GetSimulator();
    if (this_engine == simulator)
      {
      PatchQuestion::Destroy(GetCurrentEngine(), pPatch);//delete the patch from within dll
      }
    else
    {
     if (pPatch())
     {
       FileChangedDialog->ShowKill();
       FileChangedDialog->FilenameLabel->Caption = AnsiString("Smart Controller");
       FileChangedDialog->ShowModal();
       if(FileChangedDialog->ModalResult == mrYes)
          {
          PatchQuestion::Destroy(GetCurrentEngine(), pPatch);
          }
       }
      }
}
//----------------------------------------------------------------
P_PATCH TPatchForm::GetSelectedPatch(TTreeNode** PatchNode )
{
	//See which item is selected in TreeView

   	if(!(PatchTreeView->Selected) || (PatchTreeView->Selected) == PatchTreeView->Items->Item[0])
    	{
       	*PatchNode = PatchTreeView->Items->Item[0]; //set node
    	return pPatch; // the base Patch
        }

    P_PATCH SelectedPatch = (DWORD)0; // the Immediate patch ancestor
    TTreeNode* Node = PatchTreeView->Selected;

    do{
    	//get a Data Node
     	while(!(Node->Data))//is not a data node
             Node = Node->Parent;
        //get Data
      	typedef TObject* pTObject; //typedef allows access of data
      	//get data
      	TObject* pObject = pTObject(Node->Data);
	   	//check for Patch type
        if(Node != PatchTreeView->Selected && dynamic_cast<TBaseShellHook*> (pObject))
            {
            bool IsPatch = (((TBaseShellHook*)pObject)->GetType() == PATCH_TYPE);
            if (IsPatch)
	            SelectedPatch = (P_PATCH)((TBaseShellHook*)pObject)->GetHook();
            else
            	Node=Node->Parent;
            }
        else
        	Node=Node->Parent;
    }while(!SelectedPatch);

    *PatchNode = Node; // the tree node where the patch is
    return SelectedPatch;
}
//--------------------------------------------------------------
TBaseShellHook* TPatchForm::AddObject(const String& ObjectType, P_PATCH ParentPatch)
{
    P_BASESHELL pObject = (DWORD)0;

    if(ObjectType == PATCH_FILE_ID)
      {//load a patch from file
      if(PatchFileOpenDialog->Execute())
        {
        TCursor CurrentCursor =  Screen->Cursor;
        Screen->Cursor = crHourGlass;
        pObject = PatchQuestion::LoadPatchFile(GetCurrentEngine(), ExtractFileName(ExtractFileName(PatchFileOpenDialog->FileName)).c_str(),ParentPatch);
        Screen->Cursor = CurrentCursor;
        }
      }
    else if (ObjectType == "Dummy")
      {//load a Table from file
      if(TableOpenDialog->Execute())
        {
        TCursor CurrentCursor =  Screen->Cursor;
        Screen->Cursor = crHourGlass;
        //pObject = TableLoadTable(ExtractFileName(TableOpenDialog->FileName).c_str(),ParentPatch);
        Screen->Cursor = CurrentCursor;
        }
      }

    else
        pObject = BaseShellQuestion::Create(GetCurrentEngine(), ObjectType.c_str(), ParentPatch);

   if (!pObject)
        {
   		return NULL;
        }
   //add to patch
   PatchQuestion::AddBaseShell(GetCurrentEngine(), ParentPatch, pObject);
   //add to tree node
   TBaseShellHook* pObjectHook = AddObject(pObject);

   //see if any performance views need to be loaded
   if(ObjectType == PATCH_FILE_ID && *pObject!= NULL)
      {
      char NameBuf [MAX_NAME_LEN +1];
      PatchQuestion::GetFileName(GetCurrentEngine(), pObject, NameBuf, MAX_NAME_LEN);
      int FileType = 0;
      //find the file type
      ifstream InFile(NameBuf);
      if(InFile)
         {

         const int BuffLen = 1024;
         char buff[BuffLen];
         InFile.getline(buff, BuffLen);
         if(!strcmp(buff, FILE_VERSION_PREFIX))
            {
            char* cursor = buff + strlen(buff) + 1;
            FileType = atoi(cursor);
            }
            InFile.close();
         }
      else
        return NULL;
      String ViewFileName = String(NameBuf);
      if (!FileType)
        ViewFileName = ViewFileName + String(VIEW_EXT); //add file extension
      //get the Treeview node
      TTreeNode* PatchNode = pObjectHook->GetNode();
      //RestoreViews(PatchNode, ViewFileName, FileType);

      }
   SetModified();
   return pObjectHook;
}


//-----------------------------------------------------------------
TBaseShellHook* TPatchForm::AddObject(P_BASESHELL pObject)
{
  if (pObject())
  {
     //create a hook
     TBaseShellHook* pObjectHook = new TBaseShellHook(this, pObject);
     //add to map
     DevicesMap.insert(ObjectMap::value_type (pObject, pObjectHook));
     //add to tree view
     TTreeNode* PatchNode = DevicesMap[IdentityQuestion::GetParent(GetCurrentEngine(), pObject)]->GetNode();
     TTreeNode* DeviceNode = PatchNode->getFirstChild();
     TTreeNode* ThisNode = PatchTreeView->Items->AddChildObject (DeviceNode,
                        pObjectHook->GetName(),
                        pObjectHook);

     if(IdentityQuestion::CanSave(GetCurrentEngine(), pObject))
        pObjectHook->StateIndex = OBJECT_ICON;
     else
        pObjectHook->StateIndex = OBJECT_DISK_ICON;


     ThisNode->StateIndex = pObjectHook->StateIndex; // image for the view
     pObjectHook->SetViewNode(ThisNode); // let hook know where this node is
     // see if this node is a Patch
     bool IsPatch = !strcmp(pObjectHook->GetType().c_str(), PATCH_TYPE);
     if(IsPatch) // load children
        LoadPatchNode(ThisNode, (P_PATCH)(pObjectHook->GetHook()));

     //Add to PatchEdit form
     TBaseShellHook* PatchHook = ((TBaseShellHook*)PatchNode->Data);
     if (PatchHook->pEditForm) //add to view form
          ((TEditPatchForm*)(PatchHook->pEditForm))->pViewForm->AddObject(pObjectHook);

     //allow naming
     ThisNode->MakeVisible();
     EditedNode = ThisNode; //only needed for win95
     ThisNode->EditText();
     SetModified();
     return pObjectHook;
  }
  else
  {
    return NULL;
  }

}


void TPatchForm::LoadPatchNode(TTreeNode* PatchNode, P_PATCH PatchObject)
{
   if(IdentityQuestion::CanSave(GetCurrentEngine(), PatchObject))
      PatchNode->StateIndex = PATCH_ICON;
   else
      PatchNode->StateIndex  = PATCH_DISK_ICON;

  ((TBaseShellHook*)(PatchNode->Data))->StateIndex = PatchNode->StateIndex;

  // add The Nodes
  TTreeNode* DeviceNode = PatchTreeView->Items->AddChild(PatchNode, DEVICES_TEXT);
  DeviceNode->StateIndex = FOLDER_CLOSED;

  TTreeNode* ConnectorNode = PatchTreeView->Items->AddChild(PatchNode, LINKS_TEXT);
  ConnectorNode->StateIndex = FOLDER_CLOSED;

  TTreeNode* ViewsNode = PatchTreeView->Items->AddChild(PatchNode, VIEWS_TEXT);
  ViewsNode->StateIndex = FOLDER_CLOSED;

  //Load maps into TreeView

	if(!PatchObject)
	   	return;

    unsigned NumObjects = PatchQuestion::NumberBaseShells(GetCurrentEngine(), PatchObject);
    //create the master performance view
   // Load the Devices Map;

   for (unsigned i = 0; i < NumObjects; i++)
   	{
      P_BASESHELL pObject = PatchQuestion::FindBaseShell(GetCurrentEngine(), PatchObject, i);//get pointer to object
      TBaseShellHook* ObjectHook = new TBaseShellHook(this, pObject); // and assign to hook
      //load into map
      DevicesMap.insert(ObjectMap::value_type (pObject, ObjectHook));
      TTreeNode* ThisNode = PatchTreeView->Items->AddChildObject (DeviceNode,
         							ObjectHook->GetName(),
     									ObjectHook);

      ObjectHook->SetViewNode(ThisNode); // let hook know where this node is


      if(IdentityQuestion::CanSave(GetCurrentEngine(), pObject))
         ObjectHook->StateIndex = OBJECT_ICON;
      else
         ObjectHook->StateIndex = OBJECT_DISK_ICON;

      ThisNode->StateIndex = ObjectHook->StateIndex;

      // see if this node is a Patch

      if(ObjectHook->GetType() == PATCH_TYPE)
         LoadPatchNode(ThisNode,(P_PATCH) (ObjectHook->GetHook()));
      }
   //load ConnectorMap in same way
   for (unsigned i = 0; i < PatchQuestion::NumberConnectors(GetCurrentEngine(), PatchObject); i++)
   	{

      P_CONNECTOR pObject = PatchQuestion::FindConnector(GetCurrentEngine(), PatchObject, i);//get pointer to object
      TConnectorHook* ObjectHook = new TConnectorHook(this, pObject);    // and assign to hook
      ConnectorsMap.insert(ConnectorMap::value_type (pObject, ObjectHook));
      TTreeNode* ThisNode = PatchTreeView->Items->AddChildObject (ConnectorNode,
         							ObjectHook->GetName(),
	      							ObjectHook);

      ObjectHook->SetViewNode(ThisNode); // let hook know where this node is
      if(IdentityQuestion::CanSave(GetCurrentEngine(), pObject))
         ObjectHook->StateIndex = CONNECTOR_ICON;
      else
         ObjectHook->StateIndex = CONNECTOR_DISK_ICON;
      ThisNode->StateIndex = ObjectHook->StateIndex;

    }

   LoadViews (PatchNode);
}
//---------------------------------------------------------------

void __fastcall TPatchForm::FormCreate(TObject *Sender)
{
  if(!pPatch)
    return;

  Left = 0;
  Top = 0;
  
//   HelpContext = HID_TREE_STRUCTURE;
    TCursor CurrentCursor =  Screen->Cursor;
    Screen->Cursor = crHourGlass;

    TreeSortLabel->Parent = NamePanel;
  PatchTreeView->Items->Clear(); // remove any existing nodes
  TBaseShellHook* ObjectHook = new TBaseShellHook(this, (P_PATCH)pPatch); // and assign to hook
  TTreeNode* PatchNode = PatchTreeView->Items->AddChildObject(NULL, ObjectHook->GetName(),
  																	ObjectHook);

  ObjectHook->SetViewNode(PatchNode); //let the Hook know where the tree node is                                  
  LoadPatchNode(PatchNode, pPatch);
  DevicesMap.insert(ObjectMap::value_type (pPatch, ObjectHook));
#ifndef NO_TREE_SORT
  PatchTreeView->SortType = stData;
  PatchNode->AlphaSort();
  TreeSortLabel->Caption = "Sort by Name";
#endif
  char NameBuf [MAX_NAME_LEN +1];
  PatchQuestion::GetFileName(GetCurrentEngine(), pPatch, NameBuf, MAX_NAME_LEN);
  int FileType = 0;
  //find the file type
  ifstream InFile(NameBuf);
  if(InFile)
    {

    const int BuffLen = 1024;
    char buff[BuffLen];
    InFile.getline(buff, BuffLen);
    if(!strcmp(buff, FILE_VERSION_PREFIX))
        {
        char* cursor = buff + strlen(buff) + 1;
        FileType = atoi(cursor);
        }
        InFile.close();
    }

    String ViewFileName = String(NameBuf);
    if (!FileType)
        ViewFileName = ViewFileName + String(VIEW_EXT); //add file extension
  //get the Treeview node

  //LoadViews (PatchNode);

  //adjust the size
  Height = MainForm->ClientHeight-Top;
  Width = 140;
  Left = 0;
  if (GetCurrentEngine() == GetSimulator())
  {
    ShowMainView();
  }
  Screen->Cursor = CurrentCursor;
}
//---------------------------------------------------------------------------

void __fastcall TPatchForm::PatchTreeViewCollapsed(TObject *Sender,
      TTreeNode *Node)
{
	if(!(Node->Data))
		Node->StateIndex = FOLDER_CLOSED;
}
//---------------------------------------------------------------------------

void __fastcall TPatchForm::PatchTreeViewExpanded(TObject *Sender,
      TTreeNode *Node)
{
	if(!(Node->Data))
		Node->StateIndex = FOLDER_OPENED;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TPatchForm::PatchTreeViewDblClick(TObject *Sender)
{
   	if(!(PatchTreeView->Selected) || !(PatchTreeView->Selected->Data))//is not a data node
      	return;

      typedef TObject* pTObject; //typedef allows access of data
      //get data
      TObject* pObject = pTObject(PatchTreeView->Selected->Data);


	   //check for BaseShell type
   	if (dynamic_cast <TBaseShellHook*> (pObject))
       	{
        TBaseShellHook* ObjectHook = (TBaseShellHook*)pObject; //cast
        DisplayBaseShell(ObjectHook->GetHook());
        }
     //check for connector
    if (dynamic_cast <TConnectorHook*> (pObject))
       	{
       	TConnectorHook* ObjectHook = (TConnectorHook*)pObject; //cast
        DisplayConnector(ObjectHook->GetHook());
        }
    //Object is a form
    if (dynamic_cast <TPerformanceView*> (pObject))
        ((TPerformanceView*)pObject)->Display();

}

//---------------------------------------------------------------------------

void __fastcall TPatchForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------


void __fastcall TPatchForm::NewDevice1Click(TObject *Sender)
{
    TTreeNode* PatchNode;
    P_PATCH pPatch = GetSelectedPatch(&PatchNode);
	ObjectsForm->ShowList(this, pPatch);
}
//---------------------------------------------------------------------------

void __fastcall TPatchForm::PatchTreeViewEditing(TObject *Sender,
      TTreeNode *Node, bool &AllowEdit)
{
	//do not allow editing of Non object nodes
	if (!(Node->Data))
    	AllowEdit = false;
}
//---------------------------------------------------------------------------

void __fastcall TPatchForm::PatchTreeViewEdited(TObject *Sender,
      TTreeNode *Node, AnsiString &S)
{
     typedef TObject* pTObject; //typedef allows access of data
      //get data
      TObject* pObject = pTObject(Node->Data);

	   //check for BaseShell type
   	if (dynamic_cast <TBaseShellHook*> (pObject))
       	{
        TBaseShellHook* ObjectHook = (TBaseShellHook*)pObject; //cast
        ObjectHook->SetHookName(S.c_str());
        }
     //check for connector
    if (dynamic_cast <TConnectorHook*> (pObject))
       	{
       	TConnectorHook* ObjectHook = (TConnectorHook*)pObject; //cast
        ObjectHook->SetHookName(S.c_str());
        }
    //Object is a View
    if (dynamic_cast <TPerformanceView*> (pObject))
      {
      TPerformanceView* pView = (TPerformanceView*)pObject; //cast
      pView->SetViewName(S.c_str());
      }
#ifndef NO_TREE_SORT
    PatchTreeView->AlphaSort();
#endif    
    EditedNode = NULL;//clear the edited node  from Patchform
    SetModified();
}
//---------------------------------------------------------------------------

void __fastcall TPatchForm::TreePopupMenuPopup(TObject *Sender)
{
    if(!(PatchTreeView->Selected->Data))
        {
       TTreeNode* ParentPatchNode = PatchTreeView->Selected->Parent;
       P_PATCH ParentPatch = ((TBaseShellHook*)(ParentPatchNode->Data))->GetHook();
       bool CanSave = IdentityQuestion::CanSave(GetCurrentEngine(), ParentPatch);

       NewView1->Enabled = CanSave;
       NewDevice1->Enabled = CanSave;
       }
   	if(!(PatchTreeView->Selected) || // not selected
    	!(PatchTreeView->Selected->Data)||
       (!PatchTreeView->Selected->Parent))//is the base Patch
       {
       MenuDelete->Enabled = false;
       RenameItem->Enabled = false;
       }
    else
       {
       //see whether the patch parent can be saved
       TTreeNode* ParentPatchNode = PatchTreeView->Selected->Parent->Parent;
       P_PATCH ParentPatch = ((TBaseShellHook*)(ParentPatchNode->Data))->GetHook();
       bool CanSave = IdentityQuestion::CanSave(GetCurrentEngine(), ParentPatch);
       MenuDelete->Enabled = CanSave;
       RenameItem->Enabled = CanSave;
       NewView1->Enabled = CanSave;
       NewDevice1->Enabled = CanSave;
       }
}
//---------------------------------------------------------------------------

void __fastcall TPatchForm::PatchTreeViewMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
	TTreeNode* Node = PatchTreeView->GetNodeAt(X,Y);
    if(Node)
    	{
    	PatchTreeView->Hint = GetHint(Node);
        ShowHint;
        }
    else
        PatchTreeView->Hint = "";
}
//---------------------------------------------------------------------------
String TPatchForm::GetHint (TTreeNode* Node)
{
	if (!Node->Data)
    	return "Click to expand";

    typedef TObject* pTObject; //typedef allows access of data
    //get data
    TObject* pObject = pTObject(Node->Data);


    //check for BaseShell type
   	if (dynamic_cast <TBaseShellHook*> (pObject))
       	{
        TBaseShellHook* ObjectHook = (TBaseShellHook*)pObject; //cast
        return ObjectHook->GetHint();
        }
     //check for connector
    if (dynamic_cast <TConnectorHook*> (pObject))
       	{
       	TConnectorHook* ObjectHook = (TConnectorHook*)pObject; //cast
        return ObjectHook->GetHint();
        }
    //Object is a View
    if (dynamic_cast <TPerformanceView*> (pObject))
        return "Display Performance View";

    return "";
}
//------------------------------------------------------------------
bool TPatchForm::RemoveConnector (P_CONNECTOR pCon)
{
	if (ConnectorsMap.count(pCon)) // it exist here
    	{
      TConnectorHook* pHook = ConnectorsMap[pCon];
      //clear from performance views
      TTreeNode* PatchNode = pHook->GetNode()->Parent->Parent;
      TTreeNode* ViewNode = PatchNode->GetLastChild()->getFirstChild();
      while(ViewNode)
         {
         ((TPerformanceView*)(ViewNode->Data))->RemoveConnector(pCon);
         ViewNode = ViewNode->getNextSibling();
         }

        ConnectorsMap.erase(pCon);

        //tell the hook to free itself
        pHook->Delete();

        SetModified();
        return true;
        }
    else
        return false;
}
void __fastcall TPatchForm::MenuDeleteClick(TObject *Sender)
{
// pre-requires a data node selected in tree view
//deletes the Object that the node contains
    typedef TObject* pTObject; //typedef allows access of data
    //get data

    TTreeNode* Node = PatchTreeView->Selected;
    TObject* pObject = pTObject(Node->Data);

    if (dynamic_cast<TBaseShellHook*> (pObject))
    	{
        TBaseShellHook* pObjectHook = (TBaseShellHook*)pObject;
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
      SetModified();
      return;
      }
    if (dynamic_cast<TConnectorHook*> (pObject))
    	{
      TConnectorHook* pObjectHook = (TConnectorHook*)pObject;
      ConnectorsMap.erase(pObjectHook->GetHook());
      //clear from performance views
      TTreeNode* PatchNode = Node->Parent->Parent;
      TTreeNode* ViewNode = PatchNode->GetLastChild()->getFirstChild();
      while(ViewNode)
         {
         ((TPerformanceView*)(ViewNode->Data))->RemoveConnector(pObjectHook->GetHook());
         ViewNode = ViewNode->getNextSibling();
         }

      pObjectHook->DeleteHook();
      pObjectHook->Delete();                 //delete the node
      SetModified();
      return;
      }
    //delete the node
    Node->Delete();
}


void TPatchForm::DisplayBaseShell(P_BASESHELL Object)
{
	if(DevicesMap.count(Object))
    	{
        TBaseShellHook* ObjectHook = DevicesMap[Object];
        ObjectHook->DisplayEditForm();
    	}
}

//----------------------------------------------------------------------------
void TPatchForm::DisplayConnector(P_CONNECTOR Object)
{
	if(ConnectorsMap.count(Object))
    	{
        TConnectorHook* ObjectHook = ConnectorsMap[Object];
        ObjectHook->DisplayEditForm();
        }
}

//---------------------------------------------------------------------------
TConnectorHook* TPatchForm::GetConnectorHook(P_CONNECTOR Object)
{
	if(ConnectorsMap.count(Object))
        return ConnectorsMap[Object];
    else
    	return NULL;
}

TBaseShellHook* TPatchForm::GetBaseShellHook(P_BASESHELL Object)
{
	if(DevicesMap.count(Object))
        return DevicesMap[Object];
    else
    	return NULL;
}
//----------------------------------------------------------------
void TPatchForm::Save()
{
	if(!pPatch)
    	return;
    char Buff[MAX_NAME_LEN];
    PatchQuestion::GetFileName(GetCurrentEngine(), pPatch, Buff, MAX_NAME_LEN);
    String Filename = Buff;
    if (Filename == "")
    	{
        if(SavePatchDialog->Execute())
        	{
          Filename = ExtractFileName(SavePatchDialog->FileName);
          }
      }
    if (Filename == "") //still no Name
    	return;

    Save(Filename);
}

void TPatchForm::Save(const String FileName)
{
	if(!pPatch)
    	return;
#ifndef NO_TREE_SORT
   //sort the tree
   PatchTreeView->SortType = stData;
   PatchTreeView->AlphaSort();
   TreeSortLabel->Caption = "Sort by Name"; //update caption
#endif

   TBaseShellHook* PatchHook = (TBaseShellHook*)DevicesMap[pPatch];
   SavePatchFile(PatchHook, FileName);
   Modified = false;
}

void TPatchForm::SavePatchFile(TBaseShellHook* pPatchFile, const String& FileName)
{
   Screen->Cursor = crHourGlass;

    //traverse Patch tree and save views
   //String ViewFileName = String(FileName + String(VIEW_EXT));
   //ofstream OutFile(ViewFileName.c_str());
   //if(!OutFile)
   //   return;

   TTreeNode* ParentNode = pPatchFile->GetNode();

   //first save the views
   TTreeNode* ViewsNode = ParentNode->GetLastChild();

   TTreeNode* PerfView = ViewsNode->getFirstChild();
   unsigned NumViews = 0;
   //OutFile<<START_PATCH_ID<<endl;
   while(PerfView)
      {
      NumViews++;
      SavePatchViews(PerfView);
      PerfView = PerfView->getNextSibling();
      }

   //OutFile<<END_PATCH_ID<<endl;

   //store the number in he patch
   //PatchSetNumViews(pPatchFile->GetHook(), NumViews);

   //now see if any objects are Patches
   TTreeNode* ObjectsNode = ParentNode->getFirstChild();
   TTreeNode* ObjectItem =  ObjectsNode->getFirstChild();
   while(ObjectItem)
      {
      if(ObjectItem->getFirstChild()) //thenmust be a pathc
         SavePatchNode(ObjectItem);

      ObjectItem = ObjectItem->getNextSibling();
      }

   //OutFile<<END_VIEW_ID<<endl;
   //OutFile.close();


   //save the Patch
   AnsiString filename = ExtractFileName(FileName);

   PatchQuestion::Save(pPatchFile->GetCurrentEngine(), pPatchFile->GetHook(), filename .c_str());


    if (GetSelectedEngine() != GetSimulator())
    {
      unsigned key = 1;
      unsigned bytes_to_read = FileQuestion::OpenFileForRead(GetSelectedEngine(), key, filename.c_str());


      FILE* out_file = fopen(filename.c_str(), "w+");
      if (out_file)
      {
        MainForm->FileSendProgress->Position = 0;
        MainForm->FileSendProgress->Max = bytes_to_read;
        MainForm->FileSendProgress->Visible = true;

        BYTE data_buf [256];

        unsigned bytes_read = FileQuestion::ReadBytes(GetSelectedEngine(), key, data_buf, 256);

        while (bytes_read)
        {
          MainForm->FileSendProgress->Position += bytes_read;
          fwrite (data_buf, 1, bytes_read, out_file);
          bytes_read = FileQuestion::ReadBytes(GetSelectedEngine(), key, data_buf, 256);
        }

        MainForm->FileSendProgress->Visible = false;
        fclose(out_file);
      }

      FileQuestion::CloseFile(GetSelectedEngine(), key);
    }
   Screen->Cursor = crDefault;
}

void TPatchForm::SavePatchNode(TTreeNode* PatchNode)
{
   //assume must be a patch node
   TBaseShellHook* PatchHook = (TBaseShellHook*)(PatchNode->Data);
   //see if has a file name
   char Buf [MAX_NAME_LEN +1];
   PatchQuestion::GetFileName(PatchHook->GetCurrentEngine(), PatchHook->GetHook(), Buf, MAX_NAME_LEN);

   if(strlen(Buf)) //then this has a file name. Do not save
      return ;

   //first save the views
   TTreeNode* ViewsNode = PatchNode->GetLastChild();
   TTreeNode* PerfView = ViewsNode->getFirstChild();

//   OutFile<<START_PATCH_ID<<endl;

   unsigned NumViews = 0;
   while(PerfView)
      {
      NumViews++;
      SavePatchViews(PerfView);
      PerfView = PerfView->getNextSibling();
      }

   //OutFile<<END_PATCH_ID<<endl;
   //store the number in the patch
  // PatchSetNumViews(PatchHook->GetHook(), NumViews);


   //now see if any objects are Patches
   TTreeNode* ObjectsNode = PatchNode->getFirstChild();
   TTreeNode* ObjectItem =  ObjectsNode->getFirstChild();
   while(ObjectItem)
      {
      if(ObjectItem->getFirstChild()) //then must be a pathc
         SavePatchNode(ObjectItem);
      ObjectItem = ObjectItem->getNextSibling();
      }

   //return OutFile;
}

void TPatchForm::SavePatchViews(TTreeNode* NextNode)
{
   if(!(NextNode->Data))//is not a data node
      	return ;

   typedef TObject* pTObject; //typedef allows access of data
      //get data
   TObject* pObject = pTObject(NextNode->Data);

   if (dynamic_cast <TPerformanceView*> (pObject))
      {
      //((TPerformanceView*)pObject)->Save(OutFile);
      ((TPerformanceView*)pObject)->SaveView();
      }

}


void __fastcall TPatchForm::RenameItemClick(TObject *Sender)
{
    TTreeNode* Node = PatchTreeView->Selected;
    EditedNode = Node;
    Node->EditText();
}
//---------------------------------------------------------------------------

void TPatchForm::AddConnector(TConnectorHook* NewCon)
{
      ConnectorsMap.insert(ConnectorMap::value_type (NewCon->GetHook(), NewCon));
      P_PATCH ParentPatch = IdentityQuestion::GetParent(GetCurrentEngine(), NewCon->GetHook());
      //get the node of the parent patch
      TTreeNode* ParentPatchNode = ((TBaseShellHook*)DevicesMap[ParentPatch])->GetNode();
      //get the second child of the Patch node
      TTreeNode* ConnectorNode = ParentPatchNode->GetNextChild(ParentPatchNode->getFirstChild());

      TTreeNode* ThisNode = PatchTreeView->Items->AddChildObject (ConnectorNode,
         							NewCon->GetName(),
	      							NewCon);
      NewCon->SetViewNode(ThisNode); // let hook know where this node is

      if(IdentityQuestion::CanSave(GetCurrentEngine(), NewCon->GetHook()))
         NewCon->StateIndex = CONNECTOR_ICON;
      else
         NewCon->StateIndex = CONNECTOR_DISK_ICON;

      ThisNode->StateIndex = NewCon->StateIndex;
      ThisNode->MakeVisible();
      EditedNode = ThisNode;
      ThisNode->EditText();

      NewCon->UpdateObject();//update forms

      //update view nodes
      //first the PatchEdit form
      TBaseShellHook* PatchHook = ((TBaseShellHook*)DevicesMap[ParentPatch]);
      if (PatchHook->pEditForm) //add to view form
        ((TEditPatchForm*)(PatchHook->pEditForm))->pViewForm->AddConnector(NewCon);

      //now store into all views
      TTreeNode* ViewNode = ParentPatchNode->GetLastChild()->getFirstChild();
      while(ViewNode)
         {
         TViewForm* pView = ((TPerformanceView*)(ViewNode->Data))->GetViewForm();
         if(pView)
            pView->AddConnector(NewCon);
         ViewNode = ViewNode->getNextSibling();
         }

      SetModified();
}

TPerformanceView* TPatchForm::MakeView(P_PATCH ParentPatch)
{
    TBaseShellHook* PatchHook =(TBaseShellHook*)DevicesMap[ParentPatch];
    //create a new view
    TPerformanceView* pView = new TPerformanceView(PatchHook);

    unsigned view_index = ViewQuestion::AddView(GetCurrentEngine(), (P_PATCH)(PatchHook->GetHook()));

    //get the patch node
    TTreeNode* ParentPatchNode = (PatchHook->GetNode());

    //get the Third child of the Patch node
    TTreeNode* ConnectorNode = ParentPatchNode->GetNextChild(ParentPatchNode->getFirstChild());
    TTreeNode* ViewNode = ParentPatchNode->GetNextChild(ConnectorNode);



    TTreeNode* NewNode = PatchTreeView->Items->AddChildObject (ViewNode,
         							"New View",
	      							pView);

    pView->SetViewNode(NewNode);
    pView->SetViewName(String("New View"));

    if(IdentityQuestion::CanSave(GetCurrentEngine(), ParentPatch))
      pView->StateIndex = VIEW_ICON;
    else
      pView->StateIndex = VIEW_DISK_ICON;

    NewNode->StateIndex = pView->StateIndex;

    NewNode->MakeVisible();
    EditedNode = NewNode;
    NewNode->EditText();
    SetModified();
    return pView;

}

//********************************************************************
void TPatchForm::LocateBaseShell(P_BASESHELL pObject)
{
//sets focus to the node in the patch tree represented by pObject
if (DevicesMap.count(pObject))
    {
    TBaseShellHook* pHook = DevicesMap[pObject];
    TTreeNode* pNode = pHook->GetNode();
    pNode->MakeVisible();
    new TTreeNodeFlasher(pNode, PatchTreeView);
    }
}




void __fastcall TPatchForm::PatchTreeViewCompare(TObject *Sender,
      TTreeNode *Node1, TTreeNode *Node2, int Data, int &Compare)
{
    typedef TObject* pTObject; //typedef allows access of data

    if (PatchTreeView->SortType == stText)
        {
        if(Node1->Data && dynamic_cast<TPerformanceView*> ((pTObject)(Node1->Data)) )
            Compare = -1;//do not sort views
        else
            Compare = AnsiStrIComp(Node1->Text.c_str(), Node2->Text.c_str());
        return;
        }
    //sort by position
    //assumes all siblings are that same type
    if (!(Node1->Data) || !(Node2->Data))
        {
        //use the node text
        Compare = AnsiStrIComp(Node1->Text.c_str(), Node2->Text.c_str());
        return;
        }

    if (dynamic_cast<TBaseShellHook*> ((pTObject)(Node1->Data)) )
        {
        TBaseShellHook* HookNode1 = (TBaseShellHook*)(Node1->Data);
        TBaseShellHook* HookNode2 = (TBaseShellHook*)(Node2->Data);
        if (*HookNode1 < *HookNode2)
            Compare = -1;
        else
            Compare = 1;

        return;
        }
    if (dynamic_cast<TConnectorHook*> ((pTObject)(Node1->Data)) )
        {
        TConnectorHook* HookNode1 = (TConnectorHook*)(Node1->Data);
        TConnectorHook* HookNode2 = (TConnectorHook*)(Node2->Data);
        if (*HookNode1 < *HookNode2)
            Compare = -1;
        else
            Compare = 1;

        return;
        }
    if (dynamic_cast<TPerformanceView*> ((pTObject)(Node1->Data)) )
        Compare = -1;

}
//---------------------------------------------------------------------------

void __fastcall TPatchForm::TreeSortLabelClick(TObject *Sender)
{
#ifndef NO_TREE_SORT
    if(PatchTreeView->SortType == stData)
        {
        PatchTreeView->SortType = stText;
        TreeSortLabel->Caption = "Sort by Age";
        }
    else
        {
        PatchTreeView->SortType = stData;
        TreeSortLabel->Caption = "Sort by Name";
        }
    PatchTreeView->AlphaSort();
#endif
}
//---------------------------------------------------------------------------


void __fastcall TPatchForm::PatchTreeViewDeletion(TObject *Sender,
      TTreeNode *Node)
  {
  typedef TObject* pTObject; //typedef allows access of data
  if (!(Node->Data))
      return;
  TObject* pObject = pTObject(Node->Data);

  if(EditedNode == Node)
      EditedNode = NULL;
  SetModified();
  delete pObject;     //the node is  deletes  this data
  }
//---------------------------------------------------------------------------
void TPatchForm::ClearObject(P_BASESHELL pRef)
{
    //removes the object from its map
    if(DevicesMap.count(pRef))
        DevicesMap.erase(pRef);
}


void TPatchForm::ClearConnector(P_CONNECTOR pRef)
  {
  if(ConnectorsMap.count(pRef))
      {
      ConnectorsMap.erase(pRef);
      }

  }

void TPatchForm::SetModified()
{
   Modified = true;
   MainForm->UpdateMenuItems(this);
}

bool TPatchForm::IsModified()
{
    if(pPatch())
    {
        return Modified || IdentityQuestion::GetModified(GetCurrentEngine(), pPatch);
    }
    else
        return false;
}

#if 0
void TPatchForm::RestoreViews(TTreeNode* PatchNode, String ViewFileName, int FileType)
{
   ifstream InFile(ViewFileName.c_str());

   if(!InFile)
      return;

   const int BuffLen = 1024;
   char buff[BuffLen];
   InFile.getline(buff, BuffLen);
   if(strcmp(buff, FILE_VERSION_PREFIX)) //if not the same
        InFile.seekg(0, ios::beg);  //reset to file to start

   //first restore own views
   TTreeNode* ViewsNode = PatchNode->GetLastChild();
   TBaseShellHook* PatchHook =(TBaseShellHook*)(PatchNode->Data);

   /*
   if (FileType <= 3)
   {
     unsigned NumViews = 0; //PatchGetNumViews(PatchHook->GetHook());
     for(unsigned i = 0; i < NumViews; i++)
        RestoreView(ViewsNode, InFile, PatchHook, FileType);
   }

   else
   */{
    if(InFile.getline(buff, MAX_NAME_LEN).eof())
    {
      InFile.close ();
      return;
    }

    while (strcmp (buff, END_PATCH_ID))
    {
      // read view
      RestoreView(ViewsNode, InFile, PatchHook, FileType);

      if(InFile.getline(buff, MAX_NAME_LEN).eof())
      {
        InFile.close ();
        return;
      }
    }

   }
   //now restore objects list
   TTreeNode* ObjectsNode = PatchNode->getFirstChild();
   TTreeNode* ObjectItem =  ObjectsNode->getFirstChild();
   while(ObjectItem)
      {
      if(ObjectItem->getFirstChild()) //then must be a pathc
         RestorePatchViews(ObjectItem, InFile, (TBaseShellHook*)(ObjectItem->Data), FileType);
      ObjectItem = ObjectItem->getNextSibling();
      }

    InFile.close();

}
#endif
void TPatchForm::LoadViews(TTreeNode* PatchNode)
{
   TTreeNode* ViewsNode = PatchNode->GetLastChild();
   TBaseShellHook* PatchHook =(TBaseShellHook*)(PatchNode->Data);
   P_PATCH dwpPatch = (P_PATCH) (PatchHook->GetHook());
   unsigned num_views = ViewQuestion::GetNumViews(GetCurrentEngine(), dwpPatch);

   for (unsigned i = 0; i < num_views; i++)
   {
    char view_name [MAX_NAME_LEN];

    ViewQuestion::GetViewName(GetCurrentEngine(), dwpPatch, i, view_name, sizeof(view_name));
      // create the views
    TPerformanceView* pView = new TPerformanceView(PatchHook);

    //get the patch node
    TTreeNode* ParentPatchNode = PatchNode;

    //get the Third child of the Patch node
    TTreeNode* ConnectorNode = ParentPatchNode->GetNextChild(ParentPatchNode->getFirstChild());
    TTreeNode* ViewNode = ParentPatchNode->GetNextChild(ConnectorNode);



    TTreeNode* NewNode = PatchTreeView->Items->AddChildObject (ViewNode,
         							view_name,
	      							pView);

    pView->SetViewNode(NewNode);
    pView->SetViewName(String(view_name));

    if(IdentityQuestion::CanSave(GetCurrentEngine(), dwpPatch))
      pView->StateIndex = VIEW_ICON;
    else
      pView->StateIndex = VIEW_DISK_ICON;

    NewNode->StateIndex = pView->StateIndex;

    NewNode->MakeVisible();
    EditedNode = NewNode;
    NewNode->EditText();
   }
}

#if 0
ifstream& TPatchForm::RestorePatchViews(TTreeNode* PatchNode, ifstream& InFile, TBaseShellHook* Owner, int FileType)
{
    //assume must be a patch node
  TBaseShellHook* PatchHook = (TBaseShellHook*)(PatchNode->Data);
  //see if has a file name
  char Buf [MAX_NAME_LEN +1];
  PatchQuestion::GetFileName(GetCurrentEngine(), PatchHook->GetHook(), Buf, MAX_NAME_LEN);

  if(strlen(Buf)) //then this has a file name
  {
    int newFileType = 0;

    //find the file type
    ifstream newInFile(Buf);
    if(newInFile)
    {
      const int BuffLen = 1024;
      char buff[BuffLen];
      newInFile.getline(buff, BuffLen);
      if(!strcmp(buff, FILE_VERSION_PREFIX))
      {
        char* cursor = buff + strlen(buff) + 1;
        newFileType = atoi(cursor);
      }

      newInFile.close();

      String ViewFileName = String(Buf);
      if (!newFileType)
      {
        ViewFileName = ViewFileName + String(VIEW_EXT); //add file extension
      }
        //restore with filename

      RestoreViews(PatchNode, ViewFileName, newFileType);
    } // end if infile

    return InFile;
  } // else no filename

  //else these are not separate files
  //first restore the views
  TTreeNode* ViewsNode = PatchNode->GetLastChild();
/*
  if (FileType <= 3)
  {
    unsigned NumViews = 0; //PatchGetNumViews(PatchHook->GetHook());

    for (unsigned i = 0; i < NumViews; i++)
    {
      RestoreView(ViewsNode, InFile, PatchHook, 0);
    }
  }

  else
  */{
    if(InFile.getline(Buf, MAX_NAME_LEN).eof())
      return InFile;

    while (strcmp (Buf, END_PATCH_ID))
    {
      // read view
      RestoreView(ViewsNode, InFile, PatchHook, FileType);

      if(InFile.getline(Buf, MAX_NAME_LEN).eof())
        return InFile;
    }

  }

  //Now see if objects node has patches

  TTreeNode* ObjectsNode = PatchNode->getFirstChild();
  TTreeNode* ObjectItem =  ObjectsNode->getFirstChild();
  while(ObjectItem)
  {
    if(ObjectItem->getFirstChild()) //then must be a patch
    {
      RestorePatchViews(ObjectItem, InFile, (TBaseShellHook*)(ObjectItem->Data), FileType);
    }

    ObjectItem = ObjectItem->getNextSibling();
  } // while ObjectItem


  return InFile;
}

ifstream& TPatchForm::RestoreView(TTreeNode* ViewsParentNode, ifstream& InFile,
          TBaseShellHook* Owner, int FileType )
{
     TPerformanceView* pView = new TPerformanceView(Owner);

     pView->Restore(InFile, FileType);

     TTreeNode* NewNode = PatchTreeView->Items->AddChildObject (ViewsParentNode,
         							pView->GetViewName(),
	      							pView);

    pView->SetViewNode(NewNode);

    if(IdentityQuestion::CanSave(GetCurrentEngine(), Owner->GetHook()))
      pView->StateIndex = VIEW_ICON;
    else
      pView->StateIndex = VIEW_DISK_ICON;

    NewNode->StateIndex = pView->StateIndex;

    return InFile;
}
#endif

void __fastcall TPatchForm::NewView1Click(TObject *Sender)
{
	TTreeNode* PatchNode;
	//Find which patch to insert new object
   P_PATCH ParentPatch = GetSelectedPatch(&PatchNode);
   MakeView(ParentPatch);
   SetModified();
}
//---------------------------------------------------------------------------

void __fastcall TPatchForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   if(!IsModified())
      {
      CanClose = true;
      return;
      }
   FileChangedDialog->ShowSave();
   FileChangedDialog->FilenameLabel->Caption = Caption;
   FileChangedDialog->ShowModal();
   if(FileChangedDialog->ModalResult == mrYes)
      {
      Save();
      CanClose = true;
      return;
      }
   if(FileChangedDialog->ModalResult == mrNo)
      {
      CanClose = true;
      return;
      }
   CanClose = false;
}

void TPatchForm::ShowMainView()
{
   TTreeNode* PatchNode = PatchTreeView->Items->Item[0];
   TTreeNode* ViewsNode = PatchNode->GetLastChild();
   TTreeNode* MainView = ViewsNode->getFirstChild();
   if(!MainView)
      MakeView(pPatch)->Display();
   else
      {
      ((TPerformanceView*)(MainView->Data))->Display();
      MainView->MakeVisible();
      }
}

//---------------------------------------------------------------------------

void __fastcall TPatchForm::PatchTreeViewMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if(Button != mbLeft)
      return;
   //prepare for drags
	TTreeNode* Node = PatchTreeView->Selected;
   if(!Node  || !Node->Data)
      return;

   typedef TObject* pTObject; //typedef allows access of data
   //get data
   TObject* pObject = pTObject(Node->Data);


   //check for BaseShell type
   if (dynamic_cast <TBaseShellHook*> (pObject)
   || dynamic_cast <TPerformanceView*> (pObject))
      //do a drag
      PatchTreeView->BeginDrag(false, DRAG_THRESHOLD);

}
//---------------------------------------------------------------------------

void __fastcall TPatchForm::PatchTreeViewStartDrag(TObject *Sender,
      TDragObject *&DragObject)
{
   if(!(PatchTreeView->Selected) || !(PatchTreeView->Selected->Data))//is not a data node
      return;

   typedef TObject* pTObject; //typedef allows access of data
   //get data
   TObject* pObject = pTObject(PatchTreeView->Selected->Data);


   //check for BaseShell type
   if (dynamic_cast <TBaseShellHook*> (pObject))
      {
      TBaseShellHook* ObjectHook = (TBaseShellHook*)pObject; //cast
      P_PATCH PatchParent = IdentityQuestion::GetParent(GetCurrentEngine(), ObjectHook->GetHook());
      TDragBaseShell* pDragObject = new TDragBaseShell(ObjectHook, PatchParent);
      DragObject = pDragObject;
      return;
      }
    //Object is a view
    if (dynamic_cast <TPerformanceView*> (pObject))
      {
      DragViewNode* pDragObject = new DragViewNode(PatchTreeView->Selected);
      DragObject = pDragObject;
      }
}
//---------------------------------------------------------------------------

void __fastcall TPatchForm::PatchTreeViewDragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
   Accept = false;//initialise
   //find which node over
	TTreeNode* Node = PatchTreeView->GetNodeAt(X,Y);
   if (!Node)
      return;

   //first try for View Node drag
   if(dynamic_cast<DragViewNode*>(Source))
      {
      DragViewNode* DragNode = (DragViewNode*)Source;
      if(DragNode->Node->Parent == Node->Parent
      || DragNode->Node->Parent == Node)
         Accept = true;
      return;
      }
   //try drag baseshell
   if(dynamic_cast<TDragBaseShell*>(Source))
      {
      TDragBaseShell* DragShell = (TDragBaseShell*)Source;

      typedef TObject* pTObject; //typedef allows access of data
      //check for performance view
      if(!Node->Data || ! dynamic_cast<TPerformanceView*>((pTObject)Node->Data))
         return;
      Accept = ((TPerformanceView*)(Node->Data))->CanAdd(DragShell->pObject->GetHook());
      return;
      }

}
//---------------------------------------------------------------------------

void __fastcall TPatchForm::PatchTreeViewDragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
   //first see if view node

   TTreeNode* Node = PatchTreeView->GetNodeAt(X,Y);
   if(dynamic_cast<DragViewNode*>(Source))
      {
      DragViewNode* DragNode = (DragViewNode*)Source;
      if(DragNode->Node->Parent == Node->Parent)//is sibling
         DragNode->Node->MoveTo(Node, naInsert);
      else
         DragNode->Node->MoveTo(Node, naAddChildFirst);//is parent

      return;
      }
   //try baseshell
   if(dynamic_cast<TDragBaseShell*>(Source))
      {
      TDragBaseShell* DragShell = (TDragBaseShell*)Source;

      typedef TObject* pTObject; //typedef allows access of data
      //check for performance view
      if(!Node->Data || ! dynamic_cast<TPerformanceView*>((pTObject)Node->Data))
         return;

      ((TPerformanceView*)(Node->Data))->AddObject(DragShell->pObject->GetHook());
      }
}
//---------------------------------------------------------------------------

void __fastcall TPatchForm::PatchTreeViewEndDrag(TObject *Sender,
      TObject *Target, int X, int Y)
{
;
}
//---------------------------------------------------------------------------

void __fastcall TPatchForm::PatchTreeViewMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button == mbRight)
    {
        TPoint MousePosition;
        MousePosition.x = X;
        MousePosition.y = Y;
        MousePosition = ClientToScreen(MousePosition);

        ObjectsForm->Left = MousePosition.x;
        ObjectsForm->Top = MousePosition.y;
        TreePopupMenu->Popup(MousePosition.x,MousePosition.y);
    }
}

void TPatchForm::LoadPatchNodeImages(TTreeNode* PatchNode)
{
}
//---------------------------------------------------------------------------


TTreeNode* TPatchForm::GetPatchNode(P_PATCH p_patch)
{
  TTreeNode* pNode = NULL;

  if (DevicesMap.count(p_patch))
    {
    TBaseShellHook* pHook = DevicesMap[p_patch];
    pNode = pHook->GetNode();
    }

  return pNode;
}


void TPatchForm::UpdatePatchNodeImages(P_PATCH p_patch)
{
    TTreeNode* PatchNode = GetPatchNode (p_patch);

    if(PatchNode)
    {
     TBaseShellHook* PatchHook = (TBaseShellHook*)(PatchNode->Data);
     bool can_save;
     //see if has a file name
     char Buf [MAX_NAME_LEN +1];
     PatchQuestion::GetFileName(GetCurrentEngine(), PatchHook->GetHook(), Buf, MAX_NAME_LEN);
     can_save = !(strlen(Buf));

     //first do the views
     TTreeNode* ViewsNode = PatchNode->GetLastChild();
     TTreeNode* PerfView = ViewsNode->getFirstChild();

      if (can_save)
      {
        PatchNode->StateIndex = PATCH_ICON;
      }
     else
      {
        PatchNode->StateIndex  = PATCH_DISK_ICON;
      }

      while(PerfView)
      {
        if (can_save)
        {
          PerfView->StateIndex = VIEW_ICON;
        }
        else
        {
          PerfView->StateIndex = VIEW_DISK_ICON;
        }

        PerfView = PerfView->getNextSibling();
      }

       //now see if any objects are Patches
      TTreeNode* ObjectsNode = PatchNode->getFirstChild();
      TTreeNode* ObjectItem =  ObjectsNode->getFirstChild();
      while(ObjectItem)
          {
          if(ObjectItem->getFirstChild()) //then must be a patch
          {
            UpdatePatchNodeImages (((TBaseShellHook*)(ObjectItem->Data))->GetHook());
          }
          else
          {
          if (can_save)
             ObjectItem->StateIndex = OBJECT_ICON;
          else
             ObjectItem->StateIndex = OBJECT_DISK_ICON;
          }
          ObjectItem = ObjectItem->getNextSibling();
      }

      TTreeNode* ConnectorsNode = ObjectsNode->getNextSibling();
      TTreeNode* ConnectorItem =  ConnectorsNode->getFirstChild();

      while (ConnectorItem)
      {
        if (can_save)
        {
          ConnectorItem->StateIndex = CONNECTOR_ICON;
        }
        else
        {
          ConnectorItem->StateIndex = CONNECTOR_DISK_ICON;
        }

      ConnectorItem = ConnectorItem->getNextSibling();
      }
    }

}


