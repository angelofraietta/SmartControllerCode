//---------------------------------------------------------------------------
#ifndef MidiSetupUnitH
#define MidiSetupUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>


//---------------------------------------------------------------------------

void GetDeviceSettings(TStringList*, TStringList*);
class TMidiSetupForm : public TForm
{
__published:	// IDE-managed Components
    TListBox *AvailableInputList;
    TListBox *AvailableOutputList;
    TBevel *Bevel1;
    TBevel *Bevel2;
    TButton *OKButton;
    TButton *ChangeButton;
    TListBox *CurrentInputList;
    TListBox *CurrentOutputList;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TUpDown *OutputUpDown;
    TUpDown *InputUpDown;
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ChangeButtonClick(TObject *Sender);
    void __fastcall OKButtonClick(TObject *Sender);

    void __fastcall AvailableOutputListDblClick(TObject *Sender);
    void __fastcall CurrentOutputListDblClick(TObject *Sender);
    void __fastcall AvailableInputListDblClick(TObject *Sender);
    void __fastcall CurrentInputListDblClick(TObject *Sender);
    void __fastcall CurrentInputListExit(TObject *Sender);
    void __fastcall CurrentInputListClick(TObject *Sender);
    void __fastcall CurrentOutputListClick(TObject *Sender);
    void __fastcall OutputUpDownClick(TObject *Sender, TUDBtnType Button);

    void __fastcall InputUpDownClick(TObject *Sender, TUDBtnType Button);

    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
  void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
    TStringList* InputDevices;
    TStringList* OutputDevices;
    String FileName;
    void GetDeviceSettings(TStringList* InputList, TStringList* OutputList);
public:		// User declarations
    __fastcall TMidiSetupForm(TComponent* Owner);
    __fastcall ~TMidiSetupForm();
    void CloseDevices();
    void OpenDevices();
    void ReloadForm();
};
//---------------------------------------------------------------------------
extern PACKAGE TMidiSetupForm *MidiSetupForm;
//---------------------------------------------------------------------------
#endif
