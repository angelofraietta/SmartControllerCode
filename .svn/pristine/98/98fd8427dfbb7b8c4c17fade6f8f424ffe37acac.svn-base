//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ConnectorLine.h"
#include "ViewFormUnit.h"
#include "IdentityHook.h"
#include "KillerUnit.h"

#define LEADER_SIZE 10
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TConnectorLine::TConnectorLine(TConnectorHook* Owner, TViewForm* pParent)
    :TLineFollow(Owner, pParent), pParentForm(pParent),NormallyVisible(true)
{
    pObject = Owner->GetHook();
    ConnectorPopup = pParentForm->ConnectorPopupMenu;
}

void TConnectorLine::AutoArrange()
{
    //clear all points
    LinePoints.erase(LinePoints.begin(), LinePoints.end());
    //add leaders
    TPoint Leader = StartPoint;
    Leader.y = Leader.y - LEADER_SIZE;
    AddPoint(Leader, 0);

    Leader = EndPoint;
    Leader.y = Leader.y + LEADER_SIZE;
    AddPoint(Leader, 0);

    if(Visible)
        Invalidate();

}

void TConnectorLine::Detach()
{
    pParentForm = NULL;
}

__fastcall TConnectorLine::~TConnectorLine()
{
    if(pParentForm)
        pParentForm->Detach(this);
}

const std::vector<TPoint>*const TConnectorLine::GetPoints()const
{
    return &LinePoints;
}

void TConnectorLine::StorePoints(const std::vector<TPoint>*const NewPoints)
{
    //clear all points
    LinePoints.erase(LinePoints.begin(), LinePoints.end());

    LinePoints = *NewPoints;
    if(Visible)
        Invalidate();
}

void __fastcall TConnectorLine::MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button == mbLeft)
        ProcessSelect(Button, Shift, X, Y);
    else
        {
        //convert mouse pos
        TPoint MousePosition;
        MousePosition.x = X;
        MousePosition.y = Y;
        MousePosition = ClientToScreen(MousePosition);

        if(pFocusedControl != this ||!fIsOver)
            //Display Parent Popup
            {
            pParentForm->ViewPopupMenu->Popup(MousePosition.x,MousePosition.y);
            return; //only process for focussed control
            }

        if(fIsOver)
            {
            //process this popup
            pParentForm->CallingObject = this;
            ConnectorPopup->Popup(MousePosition.x,MousePosition.y);
            fIsOver = false; //prevent a drag from taking place
                             //if mouse moves
            }
        }
}

void __fastcall TConnectorLine::DoStartDrag(TDragObject *&DragObject)
{
   pParentForm->GetPatchForm()->SetModified();
   TLineFollow::DoStartDrag(DragObject);
}

TConnectorHook* TConnectorLine::GetHook()
{
   return (TConnectorHook*) Owner;
}

void __fastcall TConnectorLine::DragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
   if(dynamic_cast<TConnectorLine*> (Source))
      {
      TLineFollow::DragOver(Source, X, Y, State, Accept);
      return;
      }

  if(dynamic_cast<TKiller*> (Source))
    {
    Accept = (IsOverAndAtFront(X, Y) && IdentityQuestion::CanSave(GetCurrentEngine(), pParentForm->pPatch));
    return;
    }

  TPoint MousePos;
  MousePos.x = X;
  MousePos.y = Y;
  MousePos = pParentForm->ScreenToClient(ClientToScreen(MousePos));
  pParentForm->DragOver(Source, MousePos.x, MousePos.y, State, Accept);
}

void __fastcall TConnectorLine::DragDrop(TObject *Source, int X, int Y)
{
   if(dynamic_cast<TConnectorLine*> (Source))
      TLineFollow::DragDrop(Source, X, Y);
   else
      {
      TPoint MousePos;
      MousePos.x = X;
      MousePos.y = Y;
      MousePos =pParentForm->ScreenToClient(ClientToScreen(MousePos));

      pParentForm->DragDrop(Source, MousePos.x, MousePos.y);
      }
}

void TConnectorLine::DisplayMouseMove (bool show)
  {
  if (show)
    {
    Hint = IntToStr (((TConnectorHook*) Owner)->OutletIndex ());
    ShowHint = true;
    }

  else
    {
    Hint ="";
    ShowHint = false;
    }
  }

TPatchForm* TConnectorLine::GetPatchForm()
{
  return pParentForm->GetPatchForm();
}

PresentationQuestion* TConnectorLine::GetCurrentEngine ()
{
  return GetPatchForm()->GetCurrentEngine ();
}
