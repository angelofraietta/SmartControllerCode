//---------------------------------------------------------------------------
#ifndef CommDriverH
#define CommDriverH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

class LinkLayer; // forward declaration
//---------------------------------------------------------------------------
class TDriver : public TForm
{
__published:	// IDE-managed Components
  TComboBox *ComPortList;
  TLabel *Label1;
  TEdit *SendBuffer;
  TLabel *Label2;
  TMemo *ReceiveDisplay;
  TLabel *Label3;
  TButton *OpenPortButton;
  TButton *SendButton;
  TButton *RxButton;
  TEdit *PortNumber;
  TEdit *txtToAddress;
  TButton *SetTo;
  void __fastcall OpenPortButtonClick(TObject *Sender);
  void __fastcall SendButtonClick(TObject *Sender);
  void __fastcall ComPortListChange(TObject *Sender);
  void __fastcall RxButtonClick(TObject *Sender);
  void __fastcall SetToClick(TObject *Sender);
private:	// User declarations
  NetworkLayer* _port;
public:		// User declarations
  __fastcall TDriver(TComponent* Owner);
  __fastcall  ~TDriver();
};
//---------------------------------------------------------------------------
extern PACKAGE TDriver *Driver;
//---------------------------------------------------------------------------
#endif
