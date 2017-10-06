//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ObjectBox.h"
#include "ObjectSocket.h"
#include "interfacebridge.h"
#include "DragBaseShell.h"

//placement of the sockets
#define IS_TOP true
#define IS_BOTTOM false

#define DRAG_THRESHOLD 3 //the number of pixels to befin a drag

__fastcall TObjectBox::TObjectBox(TBaseShellHook* Owner, TViewForm* pParent)
:TGraphicControlBox(Owner), pParentForm((TViewForm*)pParent),NormallyVisible(true),
   DragType(NULL), DisplayParams (GetCurrentEngine())
{
    m_help_context = Owner->HelpContext ();
    Parent = pParent;
    pObject = Owner->GetHook();
    ObjectPopup = pParentForm->ObjectPopup;

    SetTextBuf(Owner->GetName().c_str());
    //load the sockets
    for (unsigned i = 0; i < BaseShellQuestion::GetNumInlets(GetCurrentEngine(), pObject); i++)
        {
        TObjectSocket* InletDisplay = new TObjectSocket(this, i, IS_TOP);
        AddFollower(InletDisplay, IS_TOP);
        InletDisplay->pObject = pObject; //give same base
        InletDisplay->Hint = InletDisplay->GetSocketDetails();
        InletDisplay->ShowHint = true;

        }

    for (unsigned i = 0; i < BaseShellQuestion::GetNumOutlets(GetCurrentEngine(), pObject); i++)
        {
        TObjectSocket* OutletDisplay = new TObjectSocket(this, i, IS_BOTTOM);
        AddFollower(OutletDisplay, IS_BOTTOM);
        OutletDisplay->pObject = pObject; //give same base
        OutletDisplay->Hint = OutletDisplay->GetSocketDetails();
        OutletDisplay->ShowHint = true;

        }
   Hint = ((TBaseShellHook*)Owner)->GetType();
   ShowHint = true;

}

__fastcall TObjectBox::~TObjectBox()
{
    if (pParentForm)
        pParentForm->Detach(this);
}

void __fastcall TObjectBox::Detach()
{
    DisplayControl(false);
    pParentForm = NULL;
}

TPatchForm* TObjectBox::GetPatchForm()
{
    return ((TBaseShellHook*)Owner)->GetPatchForm();
}
void __fastcall TObjectBox::MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    TPoint MousePosition;
    MousePosition.x = X;
    MousePosition.y = Y;
    MousePosition = ClientToScreen(MousePosition);

    if(Button == mbRight)
        {
        pParentForm->CallingObject = this;
        ObjectPopup->Popup(MousePosition.x,MousePosition.y);
        }
}

void __fastcall TObjectBox::MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button == mbLeft)
        BeginDrag(false, DRAG_THRESHOLD);
}

void __fastcall TObjectBox::DoStartDrag(TDragObject *&DragObject)
{
   TDragBaseShell* pDragShell;
   switch(DragType){
      case dtView:
         pDragShell = new TDragBaseShell((TBaseShellHook*)Owner,
                                          pParentForm->pPatch);
         DragType = NULL;
         DragObject = pDragShell;
         break;
      case dtObjectBox:

         //set the modified flag
         pParentForm->GetPatchForm()->SetModified();
         TGraphicControlBox::DoStartDrag(DragObject);

      };
}                   

void __fastcall TObjectBox::DoEndDrag(TObject *Source, int X, int Y)
{
  TGraphicControlBox::DoEndDrag (Source, X, Y);
  TPoint Position = GetPosition ();

  DisplayParams.Left = Position.x;
  DisplayParams.Top = Position.y;
  DisplayParams.Width = Width;
  DisplayParams.Height = Height;
}

TBaseShellHook* TObjectBox::GetHook()
{
   return (TBaseShellHook*)Owner;
}

void TObjectBox::PlaceObject(int X, int Y)
{
   Left = X - Width/2;
   Top = Y - Height/2;

  TPoint Position = GetPosition ();

  DisplayParams.Left = Position.x;
  DisplayParams.Top = Position.y;
  DisplayParams.Width = Width;
  DisplayParams.Height = Height;


   NotifyFollowers(true);
}


void TObjectBox::UpdateDisplay()
{
  char default_attribute  [MAX_NAME_LEN];
  IdentityQuestion::GetDefaultAttribute (GetCurrentEngine(), GetObject (), default_attribute, MAX_NAME_LEN);

  bool viewable_atribute = (strlen (default_attribute));

  String new_text = GetHook()->GetName();
  if (viewable_atribute)
  {
   new_text = new_text +  String (": ") + String (default_attribute);
  }

  if (new_text != Text)
  {
    SetTextBuf(new_text.c_str());
    Invalidate();
  }

}

PresentationQuestion* TObjectBox::GetCurrentEngine ()
{
  return GetPatchForm()->GetCurrentEngine ();
}

void TObjectBox::Send()
{
  BaseShellQuestion::Send(GetCurrentEngine(), pObject);
}
//---------------------------------------------------------------------------

