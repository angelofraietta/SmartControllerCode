//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CommentFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCommentDialog *CommentDialog;
//---------------------------------------------------------------------------
__fastcall TCommentDialog::TCommentDialog(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCommentDialog::CommentKeyPress(TObject *Sender, char &Key)
{
  if(Key == 13) //new line
    {
    Button1->Click();
    }
}
//---------------------------------------------------------------------------
void __fastcall TCommentDialog::Button1Click(TObject *Sender)
{
  Close();  
}
//---------------------------------------------------------------------------
void __fastcall TCommentDialog::FormShow(TObject *Sender)
{
    Comment->SetFocus();
}
//---------------------------------------------------------------------------
