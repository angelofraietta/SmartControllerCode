//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ComSetupUnit.h"
#include "interfacebridge.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TComSetup *ComSetup;

#define NUM_PORTS   6

// functions from dll
extern "C"
{
	void OpenCommPorts ();

}

typedef struct
{
  const char* port_name;
  PresentationQuestion* engine;
} str_engines;

static str_engines engines [NUM_PORTS] =
{
  {"simulator", NULL},
  {"COM1", NULL},
  {"COM2", NULL},
  {"COM3", NULL},
  {"COM4", NULL},
  {"UDP", NULL}
};

//---------------------------------------------------------------------------

__fastcall TComSetup::TComSetup(TComponent* Owner)
  : TForm(Owner), sysex_question(NULL)
{
  engines[0].engine = GetSimulator();
}

__fastcall TComSetup::~TComSetup()
{
  // we do not kill the simulator as it is not ours
  for (unsigned i = 1; i <  NUM_PORTS; i++)
  {
    if (engines[i].engine)
    {
      engines[i].engine->close();
      delete engines[i].engine;
    }
  }

}
//---------------------------------------------------------------------------
AnsiString TComSetup::GetPortName ()const
{
  AnsiString port_name = ComPortName->Text;
  return port_name;
}

unsigned TComSetup::GetPortSpeed ()const
{
  return StrToInt (ComPortSpeed->Text);
}

void __fastcall TComSetup::SetPortButtonClick(TObject *Sender)
{
  int index = ComPortName->ItemIndex;

  if (index >= 0 && index < NUM_PORTS)
  {
    SetCurrentEngine (engines[index].engine);
    Close();
  }
}
//---------------------------------------------------------------------------

void __fastcall TComSetup::FormCreate(TObject *Sender)
{
  for (unsigned i = 0; i <  NUM_PORTS; i++)
  {
    ComPortName->Items->Add (engines[i].port_name);
  }
  ComPortName->ItemIndex = 0;

}
//---------------------------------------------------------------------------

void __fastcall TComSetup::ComPortNameChange(TObject *Sender)
{
  int index = ComPortName->ItemIndex;

  if (index >= 0 && index < NUM_PORTS)
  {
    OpenPortButton->Enabled = !(engines[index].engine);
    SetPortButton->Enabled = (engines[index].engine);
  }
}
//---------------------------------------------------------------------------

void __fastcall TComSetup::OpenPortButtonClick(TObject *Sender)
{
  int index = ComPortName->ItemIndex;

  if (index >= 0 && index < NUM_PORTS)
  {
    const char* port_name = engines[index].port_name;

    engines[index].engine = new PresentationQuestion (port_name , GetPortSpeed ());

    if(engines[index].engine->IsOpen ())
    {
      SetCurrentEngine (engines[index].engine);
      OpenPortButton->Enabled = false;
      SetPortButton->Enabled = true;
    }
    else
    {
      Application->MessageBox ("Unable to open Port", "Error", IDOK);
      delete engines[index].engine;
      engines[index].engine = NULL;
    }

  }
  //Close();
}
//---------------------------------------------------------------------------

void __fastcall TComSetup::SysexFileButtonClick(TObject *Sender)
{
  if(sysex_question)
  {
    delete sysex_question;
    sysex_question = NULL;
    SysexFileButton->Caption = AnsiString("Open Sysex");
    SysexFileName->Text = AnsiString("");

    // set teh simulator as engine
    SetCurrentEngine(engines[0].engine);
  }
  else
  {
    if (SaveDialog1->Execute())
    {
      const char* filename = SaveDialog1->FileName.c_str();
      sysex_question = new PresentationQuestion;
      if(sysex_question->openfile(filename))
      {
        SetCurrentEngine(sysex_question);
        SysexFileButton->Caption = AnsiString("Close Sysex");
      }

      else
      {
        delete sysex_question;
        sysex_question = NULL;
      }
    }
  }


}
//---------------------------------------------------------------------------

void __fastcall TComSetup::SetToClick(TObject *Sender)
{
  const char* address = txtTo->Text.c_str();
  engines[ComPortName->ItemIndex].engine->SetInterfaceAddress(txtTo->Text.c_str());

}
//---------------------------------------------------------------------------

