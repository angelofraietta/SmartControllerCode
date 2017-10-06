//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ToggleBox.h"

const char*const true_state = "1";
const char*const false_state = "0";

__fastcall TToggleBox::TToggleBox(TBaseShellHook* Owner, TViewForm* pParent)
   :TObjectBox(Owner, pParent)
   {
   }

__fastcall TToggleBox::~TToggleBox()
{
}

TObjectBox* TToggleBox::Create(TBaseShellHook* Owner, TViewForm* pParent)
{
   return new TToggleBox(Owner, pParent);
}

void TToggleBox::UpdateDisplay()
{
   TObjectBox::UpdateDisplay();
  bool new_state = GetState ();
   if(new_state != PrevState)
      {
      Invalidate();
      PrevState = new_state;
      }

}

void __fastcall TToggleBox::Paint()
{
   TObjectBox::Paint();
//draw a cross
   Canvas->Pen->Color = clBlue;
   bool new_state = GetState ();

   if(new_state)
      {
      Canvas->MoveTo(0,0);
      Canvas->LineTo(Width, Height);

      Canvas->MoveTo(Width,0);
      Canvas->LineTo(0, Height);
      }
}

void __fastcall TToggleBox::MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    //make toggle change state on click
    if(Button == mbLeft
    && !Shift.Contains(ssShift)
    && !Shift.Contains(ssCtrl))
        {
        bool new_state = GetState ();
        const char* new_attrib;
        if (new_state)
        {
          new_attrib = false_state;
        }

        else
        {
          new_attrib = true_state;;
        }

        IdentityQuestion::SetDefaultAttribute(GetCurrentEngine(), pObject, new_attrib);
        Send();
        }
    else
        TObjectBox::MouseDown(Button, Shift, X, Y);
}

bool TToggleBox::GetState ()
{
  char default_attribute  [MAX_NAME_LEN];
  IdentityQuestion::GetDefaultAttribute (GetCurrentEngine(), GetObject (), default_attribute, MAX_NAME_LEN);
  return (atoi (default_attribute));
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
