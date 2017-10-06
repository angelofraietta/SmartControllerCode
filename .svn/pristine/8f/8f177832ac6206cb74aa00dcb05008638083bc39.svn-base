//---------------------------------------------------------------------------
#ifndef EditPatchUnitH
#define EditPatchUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "BaseShellsUnit.h"
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Outline.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include "PatchUnit.h"
#include <Dialogs.hpp>
#include <Graphics.hpp>
#include <map>
#include <vector>
#include "ViewFormUnit.h" //Patch Views

//define the different type of cursors
#define crPlug 1    //Flying Plug
#define crConnect 2 //can connect

class TTypeElement;
class TViewForm;

//---------------------------------------------------------------------------
class TEditPatchForm : public TBaseShellEditForm
{
friend class TPatchForm;

__published:	// IDE-managed Components

    TButton *AddInletButton;
    TButton *AddOutletButton;
   TSaveDialog *SavePatchDialog;
   TRadioGroup *PatchSaveGroup;
    TEdit *FileNameEdit;
    TTabSheet *TabSheet1;
    TPanel *ViewPanel;
    TUpDown *InletPortUpDown;
    TListBox *InletPortList;
    TListBox *OutletPortList;
    TUpDown *OutletPortUpDown;
    void __fastcall AddInletButtonClick(TObject *Sender);
    void __fastcall AddOutletButtonClick(TObject *Sender);

    
    void __fastcall ViewPanelDblClick(TObject *Sender);
   void __fastcall StoreButtonClick(TObject *Sender);
    void __fastcall InletPortListEnter(TObject *Sender);
    void __fastcall InletPortListExit(TObject *Sender);
    void __fastcall OutletPortListEnter(TObject *Sender);
    void __fastcall OutletPortListExit(TObject *Sender);
    void __fastcall InletPortUpDownClick(TObject *Sender,
          TUDBtnType Button);
    void __fastcall InletPortListClick(TObject *Sender);
    void __fastcall OutletPortListClick(TObject *Sender);
    void __fastcall OutletPortUpDownClick(TObject *Sender,
          TUDBtnType Button);
    void __fastcall InletPortListDblClick(TObject *Sender);
    void __fastcall OutletPortListDblClick(TObject *Sender);
private:	// User declarations
    void LoadData();
    TViewForm* pViewForm; //holds a master view of patch
    void __fastcall LoadViewForm();
    void LoadInletPorts();
    void LoadOutletPorts();
    void StoreInletPorts();
    void StoreOutletPorts();
public:		// User declarations
	__fastcall TEditPatchForm(TBaseShellHook* Owner);
    static TForm* Create(TBaseShellHook*);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditPatchForm *EditPatchForm;
//---------------------------------------------------------------------------
#endif
