//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ViewFormUnit.h"
#include "ObjectBox.h"
#include "ConnectorLine.h"
#include "EditPatchUnit.h"
#include "PerformanceView.h"
#include "ObjectSocket.h"
#include "ShellDisplayParam.h"
#include "PatchUnit.h"
#include "TypeElementUnit.h"
#include "NewObjectsList.h"
#include "ViewRefresh.h"
#include "DragBaseShell.h"
#include "Main.h"
#include "DragLine.h"
#include "TComment.h"
#include "help.h"
#include "NumberBox.h"
#include "NumberBoxWindowUnit.h"

#include <KillerUnit.h>

#define DEFAULT_NUM_COLUMNS 4
#define DEFAULT_COLUMN_WIDTH 100
#define DEFAULT_ROW_HEIGHT 100
#define TOP_BORDER 50
#define LEFT_BORDER 10

#define HIDDEN false

#define DRAG_THRESHOLD 3 //the number of pixels to befin a drag
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TViewForm *ViewForm;
//---------------------------------------------------------------------------
__fastcall TViewForm::TViewForm(TEditPatchForm* Owner, P_PATCH ptPatch)
    : TForm(Owner), pPatch(ptPatch), pEditForm(Owner), pView(NULL),
        NumColumns(DEFAULT_NUM_COLUMNS), RowHeight(DEFAULT_ROW_HEIGHT),
        ColumnWidth(DEFAULT_COLUMN_WIDTH), DisplayMode(!HIDDEN)
{
  pKiller = new TKillerObject(this);
}
//---------------------------------------------------------------------------
__fastcall TViewForm::TViewForm(TPerformanceView* Owner, P_PATCH ptPatch)
    : TForm(Owner), pPatch(ptPatch), pEditForm(NULL), pView(Owner),
        NumColumns(DEFAULT_NUM_COLUMNS), RowHeight(DEFAULT_ROW_HEIGHT),
        ColumnWidth(DEFAULT_COLUMN_WIDTH), DisplayMode(!HIDDEN)
{
    pKiller = new TKillerObject(this);
}

TObjectBox* TViewForm::AddObject(TBaseShellHook* pNewObject)
{
  if (pNewObject)
  {
    P_BASESHELL pShell = pNewObject->GetHook();
    if((!pShell) || (ObjectMap.count(pShell)))
        return NULL; //do not add more than once

    //create an objct box based on type
    String Type = pNewObject->GetType();
    pfnCreateObject pCreate = TTypeElementList::GetCreateObjectBox(Type);

    TObjectBox* pBox;

    if(pCreate)
      pBox = pCreate(pNewObject, this); //create based on type
    else
      pBox = new TObjectBox(pNewObject, this);//create default

    pBox->Parent = this;
    pBox->Top = TOP_BORDER;
    ObjectMap[pShell] = pBox;
    //now see if the object has connectors that need to be added

    //first inlets
    for(unsigned InletNum = 0; InletNum < BaseShellQuestion::GetNumInlets(GetCurrentEngine(), pShell); InletNum++)
    {
      for (unsigned ConNum = 0; ConNum < BaseShellQuestion::GetNumInletConnectors(GetCurrentEngine(), pShell, InletNum);
                                ConNum++)
      {
        P_CONNECTOR pCon = BaseShellQuestion::GetInletConnector(GetCurrentEngine(), pShell, InletNum, ConNum);
        AddConnector(pNewObject->GetPatchForm()->GetConnectorHook(pCon));//only adds if can
      }
    }

    for(unsigned OutletNum = 0; OutletNum < BaseShellQuestion::GetNumOutlets(GetCurrentEngine(), pShell); OutletNum++)
    {
      for (unsigned ConNum = 0; ConNum < BaseShellQuestion::GetNumOutletConnectors(GetCurrentEngine(), pShell, OutletNum);
                                ConNum++)
      {
        P_CONNECTOR pCon = BaseShellQuestion::GetOutletConnector(GetCurrentEngine(), pShell, OutletNum, ConNum);
        AddConnector(pNewObject->GetPatchForm()->GetConnectorHook(pCon));//only adds if can
      }
    }
    pBox->NotifyFollowers(true);//place the inlets and outlets in the right place
    return pBox;
  }

  else
  {
    return NULL;
  }
}

bool TViewForm::AddConnector(TConnectorHook* pConHook)
{
  if (pConHook)
  {
    P_CONNECTOR pCon = pConHook->GetHook();
    P_BASESHELL pInletBase = ConnectorQuestion::GetInletBase(GetCurrentEngine(), pCon);
    P_BASESHELL pOutletBase = ConnectorQuestion::GetOutletBase(GetCurrentEngine(), pCon);

    if ((pCon())
    && ObjectMap.count(pInletBase)
    && ObjectMap.count(pOutletBase)
    && !ConnectorMap.count(pCon))
    {
      //create the line and add to list
      TConnectorLine* pLine = new TConnectorLine(pConHook, this);
      ConnectorMap[pCon] = pLine;

      //set the start point
      unsigned InletNum = ConnectorQuestion::GetInletNum(GetCurrentEngine(), pCon);
      TObjectBox* pInletBaseBox = ObjectMap[pInletBase];
      TObjectSocket* pInlet = (TObjectSocket*)(pInletBaseBox->GetFollower(InletNum, true));
      pInlet->AddFollower(pLine);
      pLine->StartLeader(pInlet);

      //set the end point
      unsigned OutletNum = ConnectorQuestion::GetOutletNum(GetCurrentEngine(), pCon);
      TObjectBox* pOutletBaseBox = ObjectMap[pOutletBase];
      TObjectSocket* pOutlet = (TObjectSocket*)(pOutletBaseBox->GetFollower(OutletNum, false));
      pOutlet->AddFollower(pLine);
      pLine->EndLeader(pOutlet);

      //make them all follow
      pLine->Follow(true);
//        pLine->Visible = true;
      pLine->Invalidate();
      return true;
    }

    else
        return false;
  }

  else
  {
    return false;
  }
}


void __fastcall TViewForm::FormDragOver(TObject *Sender, TObject *Source,
      int X, int Y, TDragState State, bool &Accept)
{
    TGraphicControlBox* pControl = dynamic_cast<TGraphicControlBox*> (Source);
    if(pControl)
        {
        TPoint Pos; Pos.x = X; Pos.y = Y;
        Pos = pControl->ScreenToClient(ClientToScreen(Pos));
        pControl ->ProcessDrag(Pos.x, Pos.y);
        Accept = true;
        return;
    }
    if(dynamic_cast<TLineFollow*>(Source))
        {
         TPoint Pos;//the new position
         Pos.x = X;
         Pos.y = Y;

         if(!((TLineFollow*)Source)->DragPoint(Pos))
            DragCursor = crDefault;
         Accept = true;
         return;
        }
    if(IsDragObject(Source)
    && dynamic_cast<TDragBaseShell*> ((TDragObject*)Source))//see if is a drag object
      {
      TDragBaseShell* pProspect = (TDragBaseShell*)Source;
      TBaseShellHook* pObject = (pProspect->pObject);
      Accept =  !ObjectMap.count(pObject->GetHook());
      Accept &= (pProspect->pPatch == pPatch);

      return;
      }
    if(dynamic_cast<TDragLine*>(Source))
        {
        Accept = true;

        TPoint Pos; Pos.x = X; Pos.y = Y;
        ((TDragLine*)Source)->DoDrag(Pos);
        return;
        }
    if(dynamic_cast<TComment*>(Source))
      {
      Accept = (((TComment*)Source)->GetParent() == this);
      return;
      }
    Accept = false;

}
//---------------------------------------------------------------------------

void __fastcall TViewForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if(pEditForm && Parent == pEditForm->ViewPanel)
        {
        CanClose = false;
        Align = alClient;
        Parent = NULL;
        return;
        }
    if(pEditForm && !Parent)
        {
        CanClose = false;
        Parent = pEditForm->ViewPanel;
        Align = alClient;
        return;
        }

    //close the form
    CanClose = true;
    if(IdentityQuestion::CanSave(GetCurrentEngine(), pPatch) && !AutoArrangeButton->Down)
       StoreView();

}
//---------------------------------------------------------------------------
void __fastcall TViewForm::AutoArrange()
{
    std::map<P_BASESHELL, TObjectBox*>::iterator iter;
    for(iter = ObjectMap.begin(); iter != ObjectMap.end(); iter++)
        {
        P_BASESHELL pShell = (*iter).first;
        TObjectBox* pBox = (*iter).second;
        unsigned Index = PatchQuestion::FindBaseShellPosition(GetCurrentEngine(), pPatch, pShell);
        unsigned RowNumber = Index / NumColumns;
        unsigned ColumnNumber = Index % NumColumns;
        pBox->Top = RowNumber * RowHeight + TOP_BORDER;
        pBox->Left = ColumnNumber * ColumnWidth + LEFT_BORDER;
        pBox->NotifyFollowers(true);
        }

    ArrangeConnectorsClick(this);

}
void TViewForm::Detach(TObjectBox* pBox)
{
    if(ObjectMap.count(pBox->GetObject()))
        ObjectMap.erase(pBox->GetObject());
}

void TViewForm::Detach(TConnectorLine* pLine)
{
    if(ConnectorMap.count(pLine->GetObject()))
        ConnectorMap.erase(pLine->GetObject());
}

//---------------------------------------------------------------------------



void __fastcall TViewForm::FormDestroy(TObject *Sender)
{
    pRefresher->Terminate();
       //remove all objects
    {
    std::map<P_BASESHELL, TObjectBox*>::iterator ObIter;
    for(ObIter = ObjectMap.begin(); ObIter != ObjectMap.end(); ObIter++)
        {
        TObjectBox* pBox = (*ObIter).second;
        pBox->Detach();
        delete pBox;
        }
    ObjectMap.erase(ObjectMap.begin(), ObjectMap.end());

    std::map<P_CONNECTOR, TConnectorLine*>::iterator ConIter;
    for(ConIter = ConnectorMap.begin(); ConIter != ConnectorMap.end(); ConIter++)
    {
      TConnectorLine* pLine = (*ConIter).second;
      if (pLine)
      {
        pLine->Detach();
        delete pLine;
      }
    }
    ConnectorMap.erase(ConnectorMap.begin(), ConnectorMap.end());
    }

}
void TViewForm::ClearView()
{
    std::map<P_BASESHELL, TObjectBox*>::iterator ObIter;
    for(ObIter = ObjectMap.begin(); ObIter != ObjectMap.end(); ObIter++)
    {
      TObjectBox* pBox = (*ObIter).second;

      if(pBox)
      {
        pBox->Detach();
        delete pBox;
      }
    }

    ObjectMap.erase(ObjectMap.begin(), ObjectMap.end());

    std::map<P_CONNECTOR, TConnectorLine*>::iterator ConIter;
    for(ConIter = ConnectorMap.begin(); ConIter != ConnectorMap.end(); ConIter++)
    {
      TConnectorLine* pLine = (*ConIter).second;

      if(pLine)
      {
        pLine->Detach();
        delete pLine;
      }
    }
    ConnectorMap.erase(ConnectorMap.begin(), ConnectorMap.end());

    for (unsigned i = 0; i < CommentList.size (); i++)
    {
      delete CommentList[i];
      CommentList [i] = NULL;
    }

    CommentList.erase(CommentList.begin(), CommentList.end());
}

//---------------------------------------------------------------------------

void __fastcall TViewForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    if(pView)
        pView->SetViewForm(NULL);

	Action = caFree;
}

void TViewForm::StoreView()
{
    TPerformanceView* ThisView;
    if(!pView)
        ThisView = GetPatchForm()->MakeView(pPatch);
    else
        ThisView = pView;

    //clear ThisView
    ThisView->ClearView();
    //store Objects

    std::map<P_BASESHELL, TObjectBox*>::iterator ObIter;
    for(ObIter = ObjectMap.begin(); ObIter != ObjectMap.end(); ObIter++)
    {
      ShellDisplayParam ViewParam (GetCurrentEngine());
      TObjectBox* pBox = (*ObIter).second;

      if (pBox)
      {
        ViewParam.Left = pBox->DisplayParams.Left;
        ViewParam.Top = pBox->DisplayParams.Top;
        ViewParam.Height = pBox->DisplayParams.Height;
        ViewParam.Width = pBox->DisplayParams.Width;
        ViewParam.Tag = pBox->Tag;
        ViewParam.Visible = pBox->Width;
        ViewParam.pObject = pBox->GetObject ();
        ThisView->Add(ViewParam);
      }
    }

    //store connectors
    std::map<P_CONNECTOR, TConnectorLine*>::iterator ConIter;
    for(ConIter = ConnectorMap.begin(); ConIter != ConnectorMap.end(); ConIter++)
    {
      TConnectorLine* pLine = (*ConIter).second;

      if (pLine)
      {
        LineDisplayParam ViewParam(GetCurrentEngine());
        ViewParam.Points = *(pLine->GetPoints());
        ViewParam.Visible = pLine->NormallyVisible;
        ViewParam.pCon = pLine->GetObject();
        ThisView->Add(ViewParam);
      }
    }

    //storee the comments
    std::vector<TComment*>::iterator CommentIter;
    for(CommentIter = CommentList.begin(); CommentIter != CommentList.end(); CommentIter++)
    {
      TComment* pComment = *CommentIter;

      if (pComment)
      {
        TPoint position = pComment->GetPosition ();

        CommentDisplayParam ViewParam(GetCurrentEngine());
        ViewParam.Left = position.x;
        ViewParam.Top = position.y;
        ViewParam.Width = pComment->Width;
        ViewParam.Height = pComment->Height;
        ViewParam.Visible = pComment->Visible;
        ViewParam.CommentText = pComment->GetComment();
        ViewParam.pComment = pComment;
        ThisView->Add(ViewParam);
      }
    }

}
//---------------------------------------------------------------------------
TPatchForm* TViewForm::GetPatchForm()
{
    if(pView)
        return pView->GetPatchForm();
    else
        return pEditForm->GetPatchForm();
}
void __fastcall TViewForm::SaveView1Click(TObject *Sender)
{
    StoreView();
}
//---------------------------------------------------------------------------

void TViewForm::LoadView()
{
    if(!pView)
        return; //can only load from a performance view
    //clear currnent view
    ClearView();

    //load the objects first
    std::vector<ShellDisplayParam>::iterator ObIter;
    for(ObIter = pView->ObjectsList.begin(); ObIter != pView->ObjectsList.end(); ObIter++)
    {
      ShellDisplayParam& NextObject = *(ObIter);
      TBaseShellHook* ObHook = GetPatchForm()->GetBaseShellHook(NextObject.pObject);

      if (!ObHook)
      {
        continue;
      }

      AddObject(ObHook);
      //now set the position of the objects
      TObjectBox* pBox = ObjectMap[NextObject.pObject];
      if (pBox)
      {
        if (pBox->Left < LEFT_BORDER)
            pBox->Left = LEFT_BORDER;
        pBox->Left = NextObject.Left;

        if (pBox->Top < TOP_BORDER)
            pBox->Top = TOP_BORDER;
        pBox->Top = NextObject.Top;
        pBox->Width = NextObject.Width;
        pBox->Height = NextObject.Height;
        pBox->NormallyVisible = NextObject.Visible;
        pBox->Tag = NextObject.Tag;
        // now copy the static Parameters
        pBox->DisplayParams = NextObject;

        //pBox->NotifyFollowers(true);
      }

    } // end for
    //The connectors will already be there
    // they are added by AddObject
    std::vector<LineDisplayParam>::iterator ConIter;
    for(ConIter = pView->ConnectorsList.begin(); ConIter != pView->ConnectorsList.end(); ConIter++)
    {
      //set the lines for
      LineDisplayParam& LineParam = *ConIter;
      TConnectorLine* pLine = ConnectorMap[LineParam.pCon];

      if (pLine)
      {
        pLine->StorePoints(&(LineParam.Points));
        pLine->NormallyVisible = LineParam.Visible;
        if(pLine->Visible)
            Invalidate();
      }
    }

    std::vector<CommentDisplayParam>::iterator ComIter;
    for(ComIter = pView->CommentList.begin(); ComIter != pView->CommentList.end(); ComIter++)
    {
      CommentDisplayParam& NextObject = *(ComIter);
      TComment* pComment = new TComment(NextObject.CommentText.c_str(), this);

      if (pComment)
      {
        CommentList.push_back(pComment);
        pComment->Left = NextObject.Left;
        pComment->Top = NextObject.Top;
        pComment->Width = NextObject.Width;
        pComment->Height = NextObject.Height;
        pComment->Visible = true;
      }
    }

    UpdateView();
}

void __fastcall TViewForm::AutoArrangeClick(TObject *Sender)
{
    if(pView)
        {
        if(AutoArrangeButton->Down)
            {
            StoreView(); //save first
            AutoArrange();
            }
        else
            LoadView();
        }
    else
       AutoArrange();

}
//---------------------------------------------------------------------------



void __fastcall TViewForm::ObjectNormallyVisibleClick(TObject *Sender)
{
    ((TObjectBox*)CallingObject)->NormallyVisible = true;
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::ObjectNormallyHiddenClick(TObject *Sender)
{
    ((TObjectBox*)CallingObject)->NormallyVisible = false;
}
//---------------------------------------------------------------------------
void __fastcall TViewForm::ObjectPopupPopup(TObject *Sender)
{
   ObjectNormallyHidden->Checked = !((TObjectBox*)CallingObject)->NormallyVisible;

   //set the other check different
   ObjectNormallyVisible->Checked = !ObjectNormallyHidden->Checked;

   DisplayControlItem->Enabled = ((TObjectBox*)CallingObject)->HasControls();
   DisplayControlItem->Checked = (((TObjectBox*)CallingObject)->Tag);
   RemoveFromView1->Enabled = IdentityQuestion::CanSave(GetCurrentEngine(), pPatch) && (!Parent);//this form has no Parent
	 DeleteFromPatch1->Enabled = RemoveFromView1->Enabled && IdentityQuestion::CanSave(GetCurrentEngine(), IdentityQuestion::GetParent(GetCurrentEngine(), ((TObjectBox*)CallingObject)->GetObject()));   
	 
   ObjectPopup->HelpContext = (((TObjectBox*)CallingObject)->GetHook ()->HelpContext ());
}
//---------------------------------------------------------------------------
void __fastcall TViewForm::ArrangeConnectorsClick(TObject *Sender)
{
    std::map<P_CONNECTOR, TConnectorLine*>::iterator ConIter;
    for(ConIter = ConnectorMap.begin(); ConIter != ConnectorMap.end(); ConIter++)
        {
        TConnectorLine* pLine = (*ConIter).second;
        Show();
        pLine->AutoArrange();
        }

}
//---------------------------------------------------------------------------

void __fastcall TViewForm::ConnectorPopupMenuPopup(TObject *Sender)
{
    if(((TConnectorLine*)CallingObject)->NormallyVisible)
        ConnectorNormallyHidden->Checked = false;
    else
        ConnectorNormallyHidden->Checked = true;

    //set the other check different
    ConnectorNormallyVisible->Checked = !ConnectorNormallyHidden->Checked;
    DeleteConnectorMenu->Enabled = IdentityQuestion::CanSave(GetCurrentEngine(), pPatch);
    ConnectorPopupMenu->HelpContext = HID_CONNECTORS;
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::ConnectorNormallyVisibleClick(TObject *Sender)
{
    ((TConnectorLine*)CallingObject)->NormallyVisible = true;
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::ConnectorNormallyHiddenClick(TObject *Sender)
{
    ((TConnectorLine*)CallingObject)->NormallyVisible = false;    
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::ArrangeConnectorClick(TObject *Sender)
{
    ((TConnectorLine*)CallingObject)->AutoArrange();
}
//---------------------------------------------------------------------------



void __fastcall TViewForm::ShowHideButtonClick(TObject *Sender)
{
    //change state of button
    if(DisplayMode != HIDDEN)
        ShowHideButton->Down = true;
    else
        ShowHideButton->Down = false;

    DisplayMode = !ShowHideButton->Down;

    UpdateView();//show or hide
}

void TViewForm::UpdateView()
{

    std::map<P_BASESHELL, TObjectBox*>::iterator iter;
    for(iter = ObjectMap.begin(); iter != ObjectMap.end(); iter++)
    {
      TObjectBox* pBox = (*iter).second;
      if (pBox)
      {
        pBox->ShowObject(pBox->NormallyVisible || DisplayMode);
        pBox->NotifyFollowers(true);
        pBox->UpdateDisplay();
      }
    }

    std::map<P_CONNECTOR, TConnectorLine*>::iterator ConIter;
    for(ConIter = ConnectorMap.begin(); ConIter != ConnectorMap.end(); ConIter++)
    {
      TConnectorLine* pLine = (*ConIter).second;
      if (pLine)
      {
        pLine->Visible = pLine->NormallyVisible || DisplayMode;
      }
    }
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::SocketHideConnectorsClick(TObject *Sender)
{
    ((TObjectSocket*)CallingObject)->ShowConnectors(false);
    UpdateView();
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::SocketShowConnectorsClick(TObject *Sender)
{
    ((TObjectSocket*)CallingObject)->ShowConnectors(true);
    UpdateView();    
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::DisplayControlItemClick(TObject *Sender)
{
   //set depending on Menu item checked
   ((TObjectBox*)CallingObject)->DisplayControl(!DisplayControlItem->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::NumberBoxPopupPopup(TObject *Sender)
{
      int WindowType = ((TObjectBox*)CallingObject)->Tag;
      //uncheck all
      NoControl1->Checked = false;
      NumberBox1->Checked = false;
      NoteName1->Checked = false;
      VerticalSlider1->Checked = false;
      HorizontalSlider1->Checked = false;
      Guage1->Checked = false;

      switch(WindowType){
         case TNumberBoxWindow::nbwNone:
            NoControl1->Checked = true;
            break;
         case TNumberBoxWindow::nbwNumber:
            NumberBox1->Checked = true;
            break;
         case TNumberBoxWindow::nbwMidiNote:
            NoteName1->Checked = true;
            break;
         case TNumberBoxWindow::nbwVSlider:
            VerticalSlider1->Checked = true;
            break;
         case TNumberBoxWindow::nbwHSlider:
            HorizontalSlider1->Checked = true;
            break;
         case TNumberBoxWindow::nbwGuage:
            Guage1->Checked = true;
            break;
         default:
            break;
      };
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::NoControl1Click(TObject *Sender)
{
   ((TObjectBox*)CallingObject)->Tag = TNumberBoxWindow::nbwNone;
   ((TObjectBox*)CallingObject)->UpdateDisplay();
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::NumberBox1Click(TObject *Sender)
{
   ((TObjectBox*)CallingObject)->Tag = TNumberBoxWindow::nbwNumber;
   ((TObjectBox*)CallingObject)->UpdateDisplay();

}
//---------------------------------------------------------------------------

void __fastcall TViewForm::VerticalSlider1Click(TObject *Sender)
{
   ((TObjectBox*)CallingObject)->Tag = TNumberBoxWindow::nbwVSlider;
   ((TObjectBox*)CallingObject)->UpdateDisplay();

}
//---------------------------------------------------------------------------

void __fastcall TViewForm::HorizontalSlider1Click(TObject *Sender)
{
   ((TObjectBox*)CallingObject)->Tag = TNumberBoxWindow::nbwHSlider;
   ((TObjectBox*)CallingObject)->UpdateDisplay();

}
//---------------------------------------------------------------------------

void __fastcall TViewForm::Guage1Click(TObject *Sender)
{
   ((TObjectBox*)CallingObject)->Tag = TNumberBoxWindow::nbwGuage;
   ((TObjectBox*)CallingObject)->UpdateDisplay();

}
//---------------------------------------------------------------------------

void __fastcall TViewForm::NewObject1Click(TObject *Sender)
{
   ObjectsForm->ShowList(this, pPatch);
}
//---------------------------------------------------------------------------
TBaseShellHook* TViewForm::AddObject(const String& ObjectType)
{
   TBaseShellHook* NewObject = GetPatchForm()->AddObject(ObjectType, pPatch);
   if(NewObject)
      AddObject(NewObject);
   return NewObject;

}
void __fastcall TViewForm::FormCreate(TObject *Sender)
{
  HelpContext = HID_PERFORMANCE_VIEW;
   pRefresher = new TViewRefresh(this); //allows automatic updating
   PlaceForm();
}
void __fastcall TViewForm::PlaceForm()
{
   if(!Parent)
      {
      Top = GetPatchForm()->Top;
      Height = GetPatchForm()->Height;
      Left = GetPatchForm()->Left + GetPatchForm()->Width;
      Width = MainForm->ClientWidth - Left;
      }

}
//---------------------------------------------------------------------------
void TViewForm::UpdateForm()
{
    std::map<P_BASESHELL, TObjectBox*>::iterator ObIter;
   //update objects values
   for(ObIter = ObjectMap.begin(); ObIter != ObjectMap.end(); ObIter++)
      {
      (*ObIter).second->UpdateDisplay();
      }
}
void __fastcall TViewForm::HideControl1Click(TObject *Sender)
{
   ((TObjectBox*)CallingObject)->Tag = 0;
   ((TObjectBox*)CallingObject)->UpdateDisplay();

}
//---------------------------------------------------------------------------

void __fastcall TViewForm::DeleteFromPatch1Click(TObject *Sender)
{

      TBaseShellHook* pObjectHook = ((TObjectBox*)CallingObject)->GetHook();
      pObjectHook->KillObject(pObjectHook);
      //try this instead

/*      TTreeNode* Node = pObjectHook->GetNode();
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
      GetPatchForm()->SetModified();
 */
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::RemoveFromView1Click(TObject *Sender)
{
   RemoveObject(((TObjectBox*)CallingObject)->GetObject());
}

//------------------------------------------------------------
void TViewForm::RemoveConnector(P_CONNECTOR pCon)
{
   if(!ConnectorMap.count(pCon))
      return;
   TConnectorLine* pLine = ConnectorMap[pCon];
   pLine->Detach();
   delete pLine;
   ConnectorMap.erase(pCon);
}

void TViewForm::RemoveObject(P_BASESHELL pShell)
{
   if(!ObjectMap.count(pShell))
      return;
   TObjectBox* pBox = ObjectMap[pShell];
   pBox->Detach();
   delete pBox;
   ObjectMap.erase(pShell);

    //now see if the object has connectors that need to be added

    //first inlets
    for(unsigned InletNum = 0; InletNum < BaseShellQuestion::GetNumInlets(GetCurrentEngine(), pShell); InletNum++)
        {
        for (unsigned ConNum = 0; ConNum < BaseShellQuestion::GetNumInletConnectors(GetCurrentEngine(), pShell, InletNum);
                                  ConNum++)
            {
            P_CONNECTOR pCon = BaseShellQuestion::GetInletConnector(GetCurrentEngine(), pShell, InletNum, ConNum);
            RemoveConnector(pCon);
            }
        }

    for(unsigned OutletNum = 0; OutletNum < BaseShellQuestion::GetNumOutlets(GetCurrentEngine(), pShell); OutletNum++)
        {
        for (unsigned ConNum = 0; ConNum < BaseShellQuestion::GetNumOutletConnectors(GetCurrentEngine(), pShell, OutletNum);
                                  ConNum++)
            {
            P_CONNECTOR pCon = BaseShellQuestion::GetOutletConnector(GetCurrentEngine(), pShell, OutletNum, ConNum);
            RemoveConnector(pCon);
            }
        }

}

//---------------------------------------------------------------------------

void __fastcall TViewForm::DeleteConnector(TObject *Sender)
{
      TConnectorHook* pObjectHook = ((TConnectorLine*)CallingObject)->GetHook();
      //try this now
      pObjectHook->KillObject(pObjectHook);
/*      pObjectHook->DeleteHook();
      GetPatchForm()->RemoveConnector(((TConnectorLine*)CallingObject)->GetObject());
*/
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::EditObject1Click(TObject *Sender)
{
   ((TObjectBox*)CallingObject)->GetHook()->DisplayEditForm();
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::FormDragDrop(TObject *Sender, TObject *Source,
      int X, int Y)
{
    if(IsDragObject(Source)
    && dynamic_cast<TDragBaseShell*> ((TDragObject*)Source))//see if is a drag object
      {
      TBaseShellHook* pObject =((TDragBaseShell*)Source)->pObject;
      TObjectBox* pBox = AddObject(pObject);
      pBox->PlaceObject(X,Y);
      return;
      }

    if(dynamic_cast<TComment*>(Source))
      {
      TComment* pComment = (TComment*)Source;
      pComment->Left = X;
      pComment->Top = Y;
      pComment->Visible = true;
      Invalidate();
      return;
      }

}
//---------------------------------------------------------------------------

void __fastcall TViewForm::DragToView1Click(TObject *Sender)
{

   ((TObjectBox*)CallingObject)->DragType = TObjectBox::dtView;
   ((TObjectBox*)CallingObject)->BeginDrag(true, DRAG_THRESHOLD);

}
//---------------------------------------------------------------------------

void __fastcall TViewForm::FormMouseUp(TObject *Sender,
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
        ViewPopupMenu->Popup(MousePosition.x,MousePosition.y);
    }
}
//---------------------------------------------------------------------------


void __fastcall TViewForm::NoteName1Click(TObject *Sender)
{
   //((TObjectBox*)CallingObject)->Tag = TNumberBoxWindow::nbwMidiNote;
   ((TObjectBox*)CallingObject)->UpdateDisplay();

}
//---------------------------------------------------------------------------
void __fastcall TViewForm::ResetObject1Click(TObject *Sender)
{
(BaseShellQuestion::Reset(GetCurrentEngine(), ((TObjectBox*)CallingObject)->GetObject()));
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::EditDetails1Click(TObject *Sender)
{
((TConnectorLine*)CallingObject)->GetHook()->DisplayEditForm();
}
//---------------------------------------------------------------------------


void __fastcall TViewForm::ViewPopupMenuPopup(TObject *Sender)
{
    if(TPatchForm::EditedNode)
        TPatchForm::EditedNode->EndEdit(false);

}
//---------------------------------------------------------------------------

void __fastcall TViewForm::AutoArrange1Click(TObject *Sender)
{
    AutoArrange();
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::RestoreViewButtonClick(TObject *Sender)
{
    ClearView();
    LoadView();
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::SaveViewButtonClick(TObject *Sender)
{
    StoreView();
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::AddComment()
  {

  TComment* pComment = new TComment("New Comment", this);
  CommentList.push_back(pComment);
  pComment->BeginDrag(true, 0);
  }

void __fastcall TViewForm::InsertCommentClick(TObject *Sender)
{
  AddComment();
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::KillButtonClick(TObject *Sender)
{
  pKiller->BeginDrag(true, 0);
}

void TViewForm::RemoveComment(TComment* Victim)
  {
  for(unsigned i = 0; i < CommentList.size(); i++)
    {
    if(CommentList[i] == Victim)
      {
      CommentList.erase(&CommentList[i]);
      break;
      }
    }

  }
//---------------------------------------------------------------------------

void __fastcall TViewForm::Help1Click(TObject *Sender)
{
  Application->HelpContext ((((TObjectBox*)CallingObject)->GetHook ()->HelpContext ()));
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::ConHelpClick(TObject *Sender)
{
  Application->HelpContext(HID_CONNECTORS);
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::FormActivate(TObject *Sender)
{
  MainForm->DragButton->Enabled = true;
  MainForm->ResizeButton->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TViewForm::FormDeactivate(TObject *Sender)
{
  MainForm->DragButton->Enabled = false;
  MainForm->ResizeButton->Enabled = false;
}

PresentationQuestion* TViewForm::GetCurrentEngine ()
{
  return GetPatchForm()->GetCurrentEngine ();
}
//---------------------------------------------------------------------------

