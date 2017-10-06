//---------------------------------------------------------------------------
#ifndef ErrorUnitH
#define ErrorUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WindowsMessages.h"
//---------------------------------------------------------------------------
class TErrorForm : public TForm
{
__published:	// IDE-managed Components
    TMemo *ErrorMemo;void __fastcall FormCreate(TObject *Sender);
  bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);

private:	// User declarations
    String FileName;
public:		// User declarations
    __fastcall TErrorForm(TComponent* Owner);
    void DisplayMessage(const char*);
    void Save();
    void Save(const String& FileName);
protected:
    void __fastcall OnErrorMessage(TMessage* Message);
    void __fastcall OnErrorMessage32(TMessage* Message);

	BEGIN_MESSAGE_MAP
    	MESSAGE_HANDLER(ERROR_MESSAGE, TMessage*, OnErrorMessage)
      MESSAGE_HANDLER(ERROR_MESSAGE_32, TMessage*, OnErrorMessage32)
    END_MESSAGE_MAP(TForm)

};
//---------------------------------------------------------------------------
extern PACKAGE TErrorForm *ErrorForm;
//---------------------------------------------------------------------------
#endif
