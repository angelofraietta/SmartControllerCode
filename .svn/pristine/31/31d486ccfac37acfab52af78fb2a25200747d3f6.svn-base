//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "VCLGLOBFUNC.h"

void IntMaskEditBox(TEdit* Edit1)
{
    try {
         StrToInt(Edit1->Text);
         Edit1->SetTextBuf(Edit1->Text.c_str());
         Edit1->ClearUndo();

         }
    catch(...)
        {
        Edit1->Undo();
        Edit1->SetFocus();
        }
}

void DoubleMaskEditBox(TEdit* Edit1)
{
    try {
         Edit1->Text.ToDouble();
         Edit1->SetTextBuf(Edit1->Text.c_str());
         Edit1->ClearUndo();

         }
    catch(...)
        {
        Edit1->Undo();
        Edit1->SetFocus();
        }
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
