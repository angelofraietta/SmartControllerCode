//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ObjectSocket.h"
#include "CursorsUnit.h"
#include "DragConnector.h"
#include "ConnectorLine.h"
#define DRAG_THRESHOLD 3 //the number of pixels to befin a drag

__fastcall TObjectSocket::TObjectSocket(TObjectBox* Owner, unsigned SocketNum, bool IsInlet)
    :TGraphicBoxFollow(Owner, SocketNum, IsInlet), pObject((DWORD)0),
        fIsInlet(IsInlet), wSocketNumber(SocketNum)
{
    pParentForm = (TViewForm*) (Owner->Parent);
    SocketPopup = pParentForm->SocketPopupMenu;
}


TPatchForm* TObjectSocket::GetPatchForm()
{
    return ((TObjectBox*)Owner)->GetPatchForm();
}

void __fastcall TObjectSocket::DragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
    if(IsDragObject(Source)
        && dynamic_cast<TDragConnector*> ((TDragObject*)Source))//see if is a drag object
        {
        TDragConnector* pCon = (TDragConnector*)Source;

        if(fIsInlet)  //this is an inlet
            Accept = (pCon->fConnectingToInlet)
                && pCon->CanConnectInlet(pObject, wSocketNumber);
        else //this is an outlet
            Accept = !(pCon->fConnectingToInlet)
                && pCon->CanConnectOutlet(pObject, wSocketNumber);
        }
    else
        Accept = false;

}

void __fastcall TObjectSocket::DoStartDrag(TDragObject *&DragObject)
{
	P_CONNECTOR TestCon = ConnectorQuestion::Create(GetCurrentEngine()); //make a test connector
    TDragConnector* pDragCon = new TDragConnector(TestCon, !fIsInlet, GetCurrentEngine(), this);

    if(fIsInlet)
        pDragCon->SetInlet(pObject, wSocketNumber);
    else
        pDragCon->SetOutlet(pObject, wSocketNumber);

    DragObject = pDragCon;

}

void __fastcall TObjectSocket::DragDrop(TObject *Source, int X, int Y)
{
    TDragConnector* NewCon = (TDragConnector*) Source;
    NewCon->MakeConnection();
    TConnectorHook* pHook = new TConnectorHook(GetPatchForm(),NewCon->pCon);
    GetPatchForm()->AddConnector(pHook);
}

void __fastcall TObjectSocket::MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if(!IdentityQuestion::CanSave(GetCurrentEngine(), pParentForm->pPatch))
      return;
      
   if(Button == mbLeft
   || Button == mbRight && Shift.Contains(ssCtrl))
      BeginDrag(false, DRAG_THRESHOLD);
}

void __fastcall TObjectSocket::MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button == mbRight)
        {
        TPoint MousePosition;
        MousePosition.x = X;
        MousePosition.y = Y;
        MousePosition = ClientToScreen(MousePosition);
        pParentForm->CallingObject = this;
        SocketPopup->Popup(MousePosition.x, MousePosition.y);
        }
}
void TObjectSocket::ShowConnectors(bool ShowObjects)
{
    for(unsigned i = 0; i < Followers.size(); i++)
        ((TConnectorLine*)Followers[i])->NormallyVisible = ShowObjects;
}

String TObjectSocket::GetSocketDetails()
{
   char Buf[MAX_NAME_LEN+1]; //to store the name
   if(fIsInlet)
      BaseShellQuestion::GetInletName(GetCurrentEngine(), pObject,wFollowerNum, Buf, MAX_NAME_LEN);
   else
       BaseShellQuestion::GetOutletName(GetCurrentEngine(), pObject, wFollowerNum, Buf, MAX_NAME_LEN);
   return String(Buf);
}


PresentationQuestion* TObjectSocket::GetCurrentEngine ()
{
  return GetPatchForm()->GetCurrentEngine ();
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
