//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "NumberBox.h"
#include "NumberBoxWindowUnit.h"
#define WINDOW_BORDER 2

// these values are copied from number.h

enum{eValue, eMaxAttribute};
enum {eResetValue, eLowerLimit, eUpperLimit, eMaxResetAttribute};

__fastcall TNumberBox::TNumberBox(TBaseShellHook* Owner, TViewForm* pParent)
   :TObjectBox(Owner, pParent), pWindowDisplay(NULL), fIsDragging(false)
{
   Tag = 1;
   BoxDisplayMenu = pParentForm->NumberBoxPopup;
}

__fastcall TNumberBox::~TNumberBox()
{
}


TObjectBox* TNumberBox::Create(TBaseShellHook* Owner, TViewForm* pParent)
{
   return new TNumberBox(Owner, pParent);
}

void TNumberBox::DisplayControl(bool Display)
{
   // Tags of zero will not display
   if((Tag) != Display)
      Tag = Display;

   if(Display) //we want to display a window
      {
      if(!pWindowDisplay)
         pWindowDisplay = new TNumberBoxWindow(this);

      UpdateDisplay();
      pWindowDisplay->HelpContext = HelpContext ();
      }
   else
      {
      if(pWindowDisplay)
         {
         delete pWindowDisplay;
         pWindowDisplay = NULL;
         }
      }
}

void __fastcall TNumberBox::MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if(!Shift.Contains(ssCtrl)) //let ancestor process
      TObjectBox::MouseUp(Button, Shift, X, Y);
   else
      {
      DisplayControl(true);
      }
}

void __fastcall TNumberBox::DoStartDrag(TDragObject *&DragObject)
{
   fIsDragging = true;
   if(pWindowDisplay)
      pWindowDisplay->Hide();

   TObjectBox::DoStartDrag(DragObject);
}
void __fastcall TNumberBox::DoEndDrag(TObject *Source, int X, int Y)
{
   TObjectBox::DoEndDrag(Source, X, Y);
   fIsDragging = false;
   UpdateDisplay();
}


void TNumberBox::UpdateDisplay()
{
   if(fIsDragging)
      return;
   TObjectBox::UpdateDisplay();
   if(Tag && !pWindowDisplay)
      pWindowDisplay = new TNumberBoxWindow(this);

   if(pWindowDisplay)
      {
      if(!Tag)
         {
         delete pWindowDisplay;
         pWindowDisplay = NULL;
         }
      else
         {
         pWindowDisplay->Left = Left + WINDOW_BORDER;
         pWindowDisplay->Top = Top + WINDOW_BORDER;
         pWindowDisplay->Height = Height - WINDOW_BORDER *2;
         pWindowDisplay->Width = Width - WINDOW_BORDER - 2;
         pWindowDisplay->SetDisplayType(Tag);
         pWindowDisplay->UpdateDisplay();
         pWindowDisplay->Visible = true;
         pWindowDisplay->BringToFront();
         pWindowDisplay->HelpContext = HelpContext ();
         }
      }

}

void __fastcall TNumberBox::ChildMouseUp(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button == mbRight && !Shift.Contains(ssShift))
      {
      TPoint MousePosition;
      MousePosition.x = X;
      MousePosition.y = Y;
      MousePosition = ClientToScreen(MousePosition);

      pParentForm->CallingObject = this;
      BoxDisplayMenu->Popup(MousePosition.x,MousePosition.y);
      }
    else
      MouseUp(Button, Shift, X, Y);
}

void TNumberBox::SetNumber(int new_val)
{
  char attribute  [MAX_NAME_LEN];
  sprintf (attribute, "%d", new_val);
  BaseShellQuestion::SetAttribute(GetCurrentEngine(), pObject, eValue, attribute);
}

int TNumberBox::GetNumber()
{
  char attribute  [MAX_NAME_LEN];
  BaseShellQuestion::GetAttribute(GetCurrentEngine(), pObject, eValue, attribute, MAX_NAME_LEN);
  return (atoi (attribute));
}

int TNumberBox::GetLowerLimit()
{
  char attribute  [MAX_NAME_LEN];
  BaseShellQuestion::GetResetAttribute(GetCurrentEngine(), pObject, eLowerLimit, attribute, MAX_NAME_LEN);
  return (atoi (attribute));
}

int TNumberBox::GetUpperLimit()
{
  char attribute  [MAX_NAME_LEN];
  BaseShellQuestion::GetResetAttribute(GetCurrentEngine(), pObject, eUpperLimit, attribute, MAX_NAME_LEN);
  return (atoi (attribute));
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
