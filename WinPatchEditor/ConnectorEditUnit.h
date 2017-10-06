//---------------------------------------------------------------------------
#ifndef ConnectorEditUnitH
#define ConnectorEditUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "interfacebridge.h"
#include <Graphics.hpp>

class TConnectorHook;
class TPatchForm;

//---------------------------------------------------------------------------
class TConnectorEditForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *EditName;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button1;
	TMemo *EditComment;
	TMemo *OutletMemo;
	TBevel *Bevel1;
	TStaticText *StaticText1;
	TBevel *Bevel2;
	TMemo *InletMemo;
	TImage *Image1;
	TStaticText *StaticText2;
  TLabel *OutletIndexLabel;
  TLabel *OutletIndex;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

	void __fastcall OutletMemoDblClick(TObject *Sender);
	void __fastcall InletMemoDblClick(TObject *Sender);
    void __fastcall EditNameExit(TObject *Sender);
    void __fastcall EditCommentExit(TObject *Sender);
private:	// User declarations
	P_CONNECTOR pObject;
   void StoreName();
   void StoreComment();
   void LoadName();
   void LoadComment();

   void LoadOutletMemo();
   void LoadInletMemo();
public:		// User declarations
	__fastcall TConnectorEditForm(TConnectorHook* Owner);
	void UpdateForm();
  TPatchForm* GetPatchForm()const;
  PresentationQuestion* GetCurrentEngine ();
};
//---------------------------------------------------------------------------
extern PACKAGE TConnectorEditForm *ConnectorEditForm;
//---------------------------------------------------------------------------
#endif
