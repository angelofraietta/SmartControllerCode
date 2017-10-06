//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SaveChanged.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFileChangedDialog *FileChangedDialog;
//---------------------------------------------------------------------------
__fastcall TFileChangedDialog::TFileChangedDialog(TComponent* Owner)
   : TForm(Owner)
{
}

void TFileChangedDialog::ShowKill()
{
    MessageLabel->Visible = false;
    CancelButton->Visible = false;
    QuestionLabel->Caption = AnsiString("Would You Like to Kill Patch?");
}
void TFileChangedDialog::ShowSave()
{
  MessageLabel->Visible = true;
  CancelButton->Visible = true;
  QuestionLabel->Caption = AnsiString("Would You Like to save It?");
}
//---------------------------------------------------------------------------
