//---------------------------------------------------------------------------
#ifndef ViewFormUnitH
#define ViewFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <ImgList.hpp>
#include <map>
#include <vector>
#include "TypeDefs.h"
#include "interfacetypes.h"

class TObjectBox;
class TBaseShellHook;
class TEditPatchForm;
class TPerformanceView;
class TConnectorHook;
class TConnectorLine;
class TPatchForm;
class TViewRefresh;
class TConnectorLine;
class TComment;
class TKillerObject;
class PresentationQuestion;

//---------------------------------------------------------------------------
class TViewForm : public TForm
{
friend class TPerformanceView;
friend class TEditPatchForm;
friend class TConnectorLine;
__published:	// IDE-managed Components
    TPopupMenu *ViewPopupMenu;
    TMenuItem *SaveView1;
    TSplitter *Splitter1;
    TMenuItem *AutoArrange1;
    TToolBar *ToolBar1;
    TPopupMenu *ObjectPopup;
    TMenuItem *ObjectNormallyVisible;
    TMenuItem *ObjectNormallyHidden;
    TMenuItem *AutoArrangeConnectors;
    TPopupMenu *ConnectorPopupMenu;
    TMenuItem *ConnectorNormallyVisible;
    TMenuItem *ConnectorNormallyHidden;
    TMenuItem *ArrangeConnector;
    TSpeedButton *ShowHideButton;
    TPopupMenu *SocketPopupMenu;
    TMenuItem *SocketHideConnectors;
    TMenuItem *SocketShowConnectors;
   TMenuItem *DisplayControlItem;
   TPopupMenu *NumberBoxPopup;
   TMenuItem *NoControl1;
   TMenuItem *VerticalSlider1;
   TMenuItem *HorizontalSlider1;
   TMenuItem *NumberBox1;
   TMenuItem *Guage1;
   TMenuItem *NewObject1;
   TMenuItem *N2;
   TPopupMenu *TriggerMenu;
   TMenuItem *HideControl1;
   TImageList *TriggerImageList;
   TMenuItem *N1;
   TMenuItem *RemoveFromView1;
   TMenuItem *DeleteFromPatch1;
   TMenuItem *N3;
   TMenuItem *DragToView1;
   TMenuItem *DeleteConnectorMenu;
   TMenuItem *N5;
   TMenuItem *EditObject1;
   TSplitter *Splitter2;
   TMenuItem *NoteName1;
   TSplitter *Splitter3;
   TMenuItem *ResetObject1;
   TMenuItem *N4;
   TMenuItem *EditDetails1;
    TSpeedButton *AutoArrangeButton;
    TSpeedButton *RestoreViewButton;
    TSpeedButton *SaveViewButton;
  TMenuItem *InsertComment;
  TPopupMenu *CommentPopupMenu;
  TMenuItem *EditComment;
  TMenuItem *DeleteComment;
  TSpeedButton *KillButton;
  TMenuItem *Help1;
  TMenuItem *ConHelp;
    void __fastcall FormDragOver(TObject *Sender, TObject *Source, int X,
          int Y, TDragState State, bool &Accept);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall SaveView1Click(TObject *Sender);
    void __fastcall AutoArrangeClick(TObject *Sender);

    void __fastcall ObjectNormallyVisibleClick(TObject *Sender);
    void __fastcall ObjectNormallyHiddenClick(TObject *Sender);
    void __fastcall ObjectPopupPopup(TObject *Sender);
    void __fastcall ArrangeConnectorsClick(TObject *Sender);
    void __fastcall ConnectorPopupMenuPopup(TObject *Sender);
    void __fastcall ConnectorNormallyVisibleClick(TObject *Sender);
    void __fastcall ConnectorNormallyHiddenClick(TObject *Sender);
    void __fastcall ArrangeConnectorClick(TObject *Sender);
    void __fastcall ShowHideButtonClick(TObject *Sender);
    void __fastcall SocketHideConnectorsClick(TObject *Sender);
    void __fastcall SocketShowConnectorsClick(TObject *Sender);
   void __fastcall DisplayControlItemClick(TObject *Sender);
   void __fastcall NumberBoxPopupPopup(TObject *Sender);
   void __fastcall NoControl1Click(TObject *Sender);
   void __fastcall NumberBox1Click(TObject *Sender);
   void __fastcall VerticalSlider1Click(TObject *Sender);
   void __fastcall HorizontalSlider1Click(TObject *Sender);
   void __fastcall Guage1Click(TObject *Sender);
   void __fastcall NewObject1Click(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall HideControl1Click(TObject *Sender);
   void __fastcall DeleteFromPatch1Click(TObject *Sender);
   void __fastcall RemoveFromView1Click(TObject *Sender);
   void __fastcall DeleteConnector(TObject *Sender);
   void __fastcall EditObject1Click(TObject *Sender);
   void __fastcall FormDragDrop(TObject *Sender, TObject *Source, int X,
          int Y);
   void __fastcall DragToView1Click(TObject *Sender);
   void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
   void __fastcall NoteName1Click(TObject *Sender);
   void __fastcall ResetObject1Click(TObject *Sender);
   void __fastcall EditDetails1Click(TObject *Sender);

    void __fastcall ViewPopupMenuPopup(TObject *Sender);
    void __fastcall AutoArrange1Click(TObject *Sender);
    void __fastcall RestoreViewButtonClick(TObject *Sender);
    void __fastcall SaveViewButtonClick(TObject *Sender);
    void __fastcall AddComment();
  void __fastcall InsertCommentClick(TObject *Sender);
  void __fastcall KillButtonClick(TObject *Sender);
  void __fastcall Help1Click(TObject *Sender);
  void __fastcall ConHelpClick(TObject *Sender);
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall FormDeactivate(TObject *Sender);
private:	// User declarations
    bool DisplayMode;
    unsigned NumColumns, RowHeight, ColumnWidth; // to display objects
    std::map<P_BASESHELL, TObjectBox*> ObjectMap;
    TEditPatchForm* pEditForm;
    TPerformanceView* pView;
    std::map<P_CONNECTOR, TConnectorLine*> ConnectorMap;
    std::vector<TComment*> CommentList;
    TViewRefresh* pRefresher;
    TComment* pActiveComment;  //the last selected comment
    TKillerObject* pKiller;
public:		// User declarations

    __fastcall TViewForm(TEditPatchForm* Owner, P_PATCH ptPatch);
    __fastcall TViewForm(TPerformanceView* Owner, P_PATCH ptPatch);
    void UpdateView();
    void __fastcall PlaceForm();
    TObjectBox* AddObject(TBaseShellHook*);
    bool AddConnector(TConnectorHook* pCon);

    void UpdateForm();
    P_PATCH pPatch;
    void __fastcall AutoArrange();
    void StoreView();
    TPatchForm* GetPatchForm();
    void LoadView();
    TObject* CallingObject;
    TBaseShellHook* AddObject(const String& ObjectType);
    void Detach(TObjectBox* pBox);
    void Detach(TConnectorLine* pLine);
    void RemoveConnector(P_CONNECTOR pCon);
    void RemoveObject(P_BASESHELL pObject);
    void ClearView();
    void SetActiveComment(TComment* pComment){pActiveComment = pComment;}
    void RemoveComment(TComment* Victim);

    PresentationQuestion* GetCurrentEngine ();
};
//---------------------------------------------------------------------------
extern PACKAGE TViewForm *ViewForm;
//---------------------------------------------------------------------------
#endif
