//---------------------------------------------------------------------------
#ifndef BaseShellsUnitH
#define BaseShellsUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "VCLGLOBFUNC.h"
#include "interfacebridge.h"
#include <Menus.hpp>
#include <Graphics.hpp>

class TBaseShellHook;
class TPatchForm;
class TConnectorHook;
class TFormRefresh;
//---------------------------------------------------------------------------
class TBaseShellEditForm : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *DataSheet;
	TButton *ResetButton;
	TTabSheet *ConnectionsSheet;
	TLabel *OutletLabel;
	TLabel *InletLabel;
	TTabControl *OutletTab;
	TListBox *OutletsList;
	TTabControl *InletTab;
	TListBox *InletsList;
	TTabSheet *GeneralSheet;
	TMemo *EditComment;
	TLabel *TypeLabel;
    TButton *CancelButton;
	TButton *UpdateButton;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TBevel *Bevel3;
    TButton *LocateButton;
    TEdit *EditName;
    TLabel *NameLabel;
    TImage *Image1;
    TImage *InletConnectImage;
    TImage *OutletConnectImage;
    TImage *ModifiedImage;
   TButton *BaseShellSendButton;
   TPopupMenu *PopupMenu1;
   TMenuItem *DragToView1;
   TButton *DragToViewButton;
    TUpDown *OutletConnectorUpDown;
    TButton *REorderButton;
  TListBox *AttributeList;
  TListBox *ResetAttributeList;
  TEdit *AttributeValue;
  TEdit *ResetAttributeValue;
	void __fastcall EditNameClick(TObject *Sender);
	void __fastcall EditCommentClick(TObject *Sender);

	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ResetButtonClick(TObject *Sender);

	void __fastcall InletTabChange(TObject *Sender);
	void __fastcall OutletTabChange(TObject *Sender);

	void __fastcall CancelButtonClick(TObject *Sender);
	void __fastcall UpdateButtonClick(TObject *Sender);
	void __fastcall InletsListDblClick(TObject *Sender);
	void __fastcall EditNameExit(TObject *Sender);
	void __fastcall EditCommentExit(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall OutletsListStartDrag(TObject *Sender,
          TDragObject *&DragObject);

    void __fastcall OutletsListMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall OutletsListDblClick(TObject *Sender);
    void __fastcall InletsListDragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
    void __fastcall OutletsListDragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
    void __fastcall InletsListStartDrag(TObject *Sender,
          TDragObject *&DragObject);
    void __fastcall InletsListMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall InletsListDragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
    void __fastcall OutletsListDragDrop(TObject *Sender, TObject *Source,
          int X, int Y);

    void __fastcall LocateButtonClick(TObject *Sender);

    void __fastcall PageControl1Change(TObject *Sender);
   void __fastcall BaseShellSendButtonClick(TObject *Sender);
   void __fastcall EditNameChange(TObject *Sender);
   void __fastcall EditCommentChange(TObject *Sender);
   
   void __fastcall DragToView1Click(TObject *Sender);
   void __fastcall DragToViewButtonStartDrag(TObject *Sender,
          TDragObject *&DragObject);
    void __fastcall OutletsListClick(TObject *Sender);
    void __fastcall OutletsListEnter(TObject *Sender);
    void __fastcall OutletsListExit(TObject *Sender);
    void __fastcall OutletConnectorUpDownClick(TObject *Sender,
          TUDBtnType Button);
    void __fastcall REorderButtonClick(TObject *Sender);
  void __fastcall AttributeListClick(TObject *Sender);
  void __fastcall ResetAttributeListClick(TObject *Sender);
  void __fastcall AttributeValueEnter(TObject *Sender);
  void __fastcall AttributeValueExit(TObject *Sender);
  void __fastcall AttributeValueKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall ResetAttributeValueKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall ResetAttributeValueEnter(TObject *Sender);
  void __fastcall ResetAttributeValueExit(TObject *Sender);

private:	// User declarations
    volatile bool fAllowUpdate; //allow update of the form
    TFormRefresh* pRefresher;

protected:
    void StoreOutletConnectors();
   P_BASESHELL pObject; // The object that is edited
   void StoreName();   // to object object
   void StoreComment();// ditto
   void LoadType();    // from object
   void LoadName();    // from object
   void LoadComment(); // ditto
   void LoadInletsList(); //loads list of inlet connections for display
   void LoadOutletsList(); // ditto for outlets
   void SetInletsTabs(); // sets the Tab list for inlet list
   void SetOutletsTabs();//ditto for outlets

public:		// User declarations
	__fastcall TBaseShellEditForm(TBaseShellHook* Owner);
    __fastcall ~TBaseShellEditForm();
   void UpdateForm(); //update the fields in the form
   virtual void LoadData();
   TPatchForm* GetPatchForm();
   void HideConnectionImages();
   PresentationQuestion* GetCurrentEngine ();
   volatile bool AllowUpdate()const {return fAllowUpdate;}
};
//---------------------------------------------------------------------------
extern PACKAGE TBaseShellEditForm *BaseShellEditForm;
//---------------------------------------------------------------------------
#endif
