//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ErrorUnit.h"
#include "TypeDefs.h"
#include "interfacebridge.h"
#include "Main.h"

#include <fstream.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TErrorForm *ErrorForm;
//---------------------------------------------------------------------------
__fastcall TErrorForm::TErrorForm(TComponent* Owner)
    : TForm(Owner)
{
    ErrorMemo->Clear();
    //SetErrorWindow(Handle);
    //SetErrorWindow32(Handle);
    FileName = String(GetCurrentDir() + "\\ErrorLog.log");
    //HelpContext = HID_ERROR_LOG;
}
//---------------------------------------------------------------------------
void __fastcall TErrorForm::FormCreate(TObject *Sender)
{
   Top = 0;
   Height = 100;
   Width =MainForm->ClientWidth;

}
//---------------------------------------------------------------------------
void TErrorForm::DisplayMessage(const char* Message)
{
    ErrorMemo->Lines->Add(String(Message));
}

void __fastcall TErrorForm::OnErrorMessage(TMessage* Message)
{
/*
    char Buf[MAX_ERROR_LEN +1];
    while(GetErrorMessage(Buf))
    {
      DisplayMessage(Buf);
    }

  Show ();
  */
}

void __fastcall TErrorForm::OnErrorMessage32(TMessage* Message)
{
/*
    char Buf[MAX_ERROR_LEN +1];
    while(GetErrorMessage(Buf))
        DisplayMessage(Buf);
*/        
}

void TErrorForm::Save()
{
    Save(FileName);
}

void TErrorForm::Save(const String& FileName)
{
    ofstream Outfile(FileName.c_str());
    if(Outfile)
        {
         Outfile<<ErrorMemo->Text.c_str();
         Outfile.close();
         }
}

bool __fastcall TErrorForm::FormHelp(WORD Command, int Data,
      bool &CallHelp)
{
  CallHelp = true;
  return true;
}
//---------------------------------------------------------------------------

