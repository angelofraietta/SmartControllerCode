//---------------------------------------------------------------------------
#ifndef PatchUnitH
#define PatchUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <vector>
#include <map>
#include "ViewFormUnit.h" //Patch Views
#include "TreeNodeFlasher.h"
#include "interfacebridge.h"
#include <fstream.h>



class TBaseShellHook;// forward declarations
class TConnectorHook;
class TTypeElement;
//---------------------------------------------------------------------------
class TPatchForm : public TForm
{
__published:	// IDE-managed Components
	TTreeView *PatchTreeView;
	TImageList *TreeImageList;
	TPopupMenu *TreePopupMenu;
	TMenuItem *NewDevice1;
	TMenuItem *MenuDelete;
	TMenuItem *RenameItem;
	TSaveDialog *SavePatchDialog;
    TOpenDialog *PatchFileOpenDialog;
    TOpenDialog *TableOpenDialog;
   TMenuItem *NewView1;
   TMenuItem *N1;
   TMenuItem *N2;
    TPanel *NamePanel;
    TLabel *TreeSortLabel;
    TSplitter *Splitter1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall PatchTreeViewCollapsed(TObject *Sender, TTreeNode *Node);
	void __fastcall PatchTreeViewExpanded(TObject *Sender, TTreeNode *Node);
	void __fastcall PatchTreeViewDblClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall NewDevice1Click(TObject *Sender);
	void __fastcall PatchTreeViewEditing(TObject *Sender, TTreeNode *Node,
          bool &AllowEdit);
	void __fastcall PatchTreeViewEdited(TObject *Sender, TTreeNode *Node,
          AnsiString &S);
	void __fastcall TreePopupMenuPopup(TObject *Sender);
	void __fastcall PatchTreeViewMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
	void __fastcall MenuDeleteClick(TObject *Sender);

	void __fastcall RenameItemClick(TObject *Sender);



    void __fastcall PatchTreeViewCompare(TObject *Sender, TTreeNode *Node1,
          TTreeNode *Node2, int Data, int &Compare);
    
    void __fastcall TreeSortLabelClick(TObject *Sender);
    
    void __fastcall PatchTreeViewDeletion(TObject *Sender,
          TTreeNode *Node);
    
   void __fastcall NewView1Click(TObject *Sender);
   void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
   void __fastcall PatchTreeViewMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall PatchTreeViewStartDrag(TObject *Sender,
          TDragObject *&DragObject);
   void __fastcall PatchTreeViewDragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
   void __fastcall PatchTreeViewDragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
   void __fastcall PatchTreeViewEndDrag(TObject *Sender, TObject *Target,
          int X, int Y);
   void __fastcall PatchTreeViewMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations
	P_PATCH pPatch; // The patch that this form contains

	std::vector<TForm*> PerformanceViews;
   static unsigned wNumNewPatches;
   bool Modified;
   void SavePatch();
   //static ofstream& SavePatchViews(ofstream& OutFile, TTreeNode* PatchNode);
   static void SavePatchViews(TTreeNode* PatchNode);

   typedef std::map<P_BASESHELL, TBaseShellHook*, std::less<P_BASESHELL> > ObjectMap;
   typedef std::map<P_CONNECTOR, TConnectorHook*, std::less<P_CONNECTOR> > ConnectorMap;
   //std::map<Identity*, TIdentityHook*, std::less<Identity*> >
   ObjectMap DevicesMap; // maps all objects withn patch and its sub-patches
   ConnectorMap ConnectorsMap; // ditto for connctors
   static TStringList* ObjectTypeList; // used for creating new Object Types
   void LoadPatchNode(TTreeNode*, P_PATCH);
   void LoadPatchNodeImages(TTreeNode* PatchNode);
   String GetHint(TTreeNode*);
   //void RestoreViews(TTreeNode* PatchNode, String ViewFileName, int FileType);
   void LoadViews (TTreeNode* PatchNode);
   //ifstream& RestoreView(TTreeNode* ViewsParentNode, ifstream& InFile, TBaseShellHook* Owner, int FileType);
   //ifstream& RestorePatchViews(TTreeNode* PatchNode, ifstream& InFile, TBaseShellHook* Owner, int FileType);
   void ShowMainView(); //Displays the first performance view

   PresentationQuestion* this_engine;

public:		// User declarations
	__fastcall TPatchForm(TComponent* Owner);
	__fastcall TPatchForm(TComponent* Owner, String FileName);
  __fastcall TPatchForm(TComponent* Owner, P_PATCH ParentPatch);
   __fastcall ~TPatchForm();

   bool IsModified();
   void SetModified();
   TBaseShellHook* AddObject(const String& Type, P_PATCH ParentPatch); //from new
   TBaseShellHook* AddObject(P_BASESHELL);
   bool RemoveConnector(P_CONNECTOR);
   void ClearObject(P_BASESHELL);
   void ClearConnector(P_CONNECTOR);
   void DisplayBaseShell(P_BASESHELL);
   void DisplayConnector(P_CONNECTOR);
   void LocateBaseShell(P_BASESHELL);
   void LocateConnector(P_CONNECTOR);
   void AddConnector(TConnectorHook*);
   TBaseShellHook* GetBaseShellHook(P_BASESHELL);// get Hook to BaseShell
   TConnectorHook* GetConnectorHook(P_CONNECTOR);
   void Save();
   void Save(const String);
   static void SavePatchFile(TBaseShellHook* pPatchFile);
   static void SavePatchFile(TBaseShellHook* pPatchFile, const String& FileName);
   static void SavePatchNode(TTreeNode* PatchNode);
   TPerformanceView* MakeView(P_PATCH pPatch);
   P_PATCH GetSelectedPatch(TTreeNode**); // return the Patch selected in tree view

   //if a TTreenode is being edited, it seems to capture the mouse in Windows95
   //so We will remove focus forcefully
   static TTreeNode* EditedNode;
    TTreeNode* GetPatchNode(P_PATCH p_patch);
    void UpdatePatchNodeImages(P_PATCH p_patch);
    PresentationQuestion* GetCurrentEngine () {return this_engine;}
};
//---------------------------------------------------------------------------
extern PACKAGE TPatchForm *PatchForm;
//---------------------------------------------------------------------------
#endif
