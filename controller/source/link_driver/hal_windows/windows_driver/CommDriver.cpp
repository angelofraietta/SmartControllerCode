//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <windows.h>
#include <string>
using std::string;
//## end module%3AE75EB7024E.includes

// WindowsCommPort
#include "networklayer.h"
#include "crc32.h"

#include "CommDriver.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define MAX_BUF_SIZE 4096

TDriver *Driver;
//---------------------------------------------------------------------------
__fastcall TDriver::TDriver(TComponent* Owner)
  : TForm(Owner), _port (NULL)
{
}
//---------------------------------------------------------------------------


__fastcall TDriver::~TDriver()
{
  delete _port;
}
void __fastcall TDriver::OpenPortButtonClick(TObject *Sender)
{
  delete _port;
  _port = NetworkLayer::create(ComPortList->Text.c_str(), StrToInt(PortNumber->Text));
  if (_port)
  {
    OpenPortButton->Visible = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TDriver::SendButtonClick(TObject *Sender)
{
  char buf [MAX_BUF_SIZE];
  //unsigned char tx_message = 0x0b;

  SendBuffer->SelectAll ();
  int buf_size = SendBuffer->GetSelTextBuf(buf, MAX_BUF_SIZE);


  if (_port)
  {
    _port->WriteBuffer ((const BYTE*)buf, buf_size);
  }
}
//---------------------------------------------------------------------------
void __fastcall TDriver::ComPortListChange(TObject *Sender)
{
  OpenPortButton->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TDriver::RxButtonClick(TObject *Sender)
{
  char buf [MAX_BUF_SIZE];
  if (_port)
  {
    memset(buf, 0, MAX_BUF_SIZE);
    long bytes_read = _port->ReadBuffer ((BYTE*)buf, MAX_BUF_SIZE);
    buf [bytes_read] = '\0';
    ReceiveDisplay->Lines->Add (String (buf));
    if (_port->GetFrom(buf, MAX_BUF_SIZE))
    {
      ReceiveDisplay->Lines->Add (String (buf));
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TDriver::SetToClick(TObject *Sender)
{
  _port->SetTo(txtToAddress->Text.c_str());
}
//---------------------------------------------------------------------------

