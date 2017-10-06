//---------------------------------------------------------------------------
#ifndef ComSetupUnitH
#define ComSetupUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>

class PresentationQuestion;
//---------------------------------------------------------------------------
class TComSetup : public TForm
{
__published:	// IDE-managed Components
  TComboBox *ComPortName;
  TComboBox *ComPortSpeed;
  TButton *SetPortButton;
  TButton *OpenPortButton;
  TSaveDialog *SaveDialog1;
  TButton *SysexFileButton;
  TEdit *SysexFileName;
  TEdit *txtTo;
  TButton *SetTo;
  void __fastcall SetPortButtonClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall ComPortNameChange(TObject *Sender);
  void __fastcall OpenPortButtonClick(TObject *Sender);
  void __fastcall SysexFileButtonClick(TObject *Sender);
  void __fastcall SetToClick(TObject *Sender);
private:	// User declarations
  PresentationQuestion* sysex_question;
public:		// User declarations
  __fastcall TComSetup(TComponent* Owner);
  __fastcall ~TComSetup();
  AnsiString GetPortName ()const;
  unsigned GetPortSpeed ()const;
};
//---------------------------------------------------------------------------
extern PACKAGE TComSetup *ComSetup;
//---------------------------------------------------------------------------
#endif
