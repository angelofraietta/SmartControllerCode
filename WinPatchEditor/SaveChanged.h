//---------------------------------------------------------------------------
#ifndef SaveChangedH
#define SaveChangedH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFileChangedDialog : public TForm
{
__published:	// IDE-managed Components
   TLabel *MessageLabel;
  TLabel *QuestionLabel;
   TLabel *FilenameLabel;
   TBitBtn *BitBtn1;
   TBitBtn *BitBtn2;
  TBitBtn *CancelButton;
private:	// User declarations
public:		// User declarations
   __fastcall TFileChangedDialog(TComponent* Owner);
   void ShowKill();
   void ShowSave();

};
//---------------------------------------------------------------------------
extern PACKAGE TFileChangedDialog *FileChangedDialog;
//---------------------------------------------------------------------------
#endif
