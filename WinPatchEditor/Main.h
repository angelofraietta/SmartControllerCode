//----------------------------------------------------------------------------
#ifndef MainH
#define MainH
//----------------------------------------------------------------------------

#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Messages.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <StdCtrls.hpp>
#include <Menus.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <System.hpp>
#include <ImgList.hpp>
//----------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *FileNewItem;
	TMenuItem *FileOpenItem;
	TMenuItem *FileCloseItem;
	TMenuItem *Window1;
	TMenuItem *Help1;
	TMenuItem *N1;
	TMenuItem *FileExitItem;
	TMenuItem *WindowCascadeItem;
	TMenuItem *WindowTileItem;
	TMenuItem *WindowArrangeItem;
	TMenuItem *HelpAboutItem;
	TOpenDialog *OpenDialog;
	TMenuItem *FileSaveItem;
	TMenuItem *FileSaveAsItem;
	TMenuItem *Edit1;
	TMenuItem *CutItem;
	TMenuItem *CopyItem;
	TMenuItem *PasteItem;
	TMenuItem *WindowMinimizeItem;
	TPanel *SpeedPanel;
	TSpeedButton *OpenBtn;
	TSpeedButton *SaveBtn;
	TSpeedButton *CutBtn;
	TSpeedButton *CopyBtn;
	TSpeedButton *PasteBtn;
	TSpeedButton *ExitBtn;
	TStatusBar *StatusBar;
	TSaveDialog *SaveDialog;
    TMenuItem *Settings;
    TMenuItem *MidiSetup;
    TImageList *PlugHoldList;
  TMenuItem *Contents1;
  TMenuItem *Search1;
  TMenuItem *Find1;
  TMenuItem *N2;
  TSpeedButton *SelectButton;
  TSpeedButton *DragButton;
  TSpeedButton *ResizeButton;
  TMenuItem *ComSetup1;
  TMenuItem *ReadPatch;
  TMenuItem *N3;
  TMenuItem *SendFile1;
  TProgressBar *FileSendProgress;
  TMenuItem *ReadFile1;
  TMenuItem *ExecutePatch1;
  TMenuItem *KillAllPatches1;
  TMenuItem *SaveNVRAM1;
  TMenuItem *EraseNVRAM1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FileNewItemClick(TObject *Sender);
	void __fastcall WindowCascadeItemClick(TObject *Sender);
	void __fastcall UpdateMenuItems(TObject *Sender);
	void __fastcall WindowTileItemClick(TObject *Sender);
	void __fastcall WindowArrangeItemClick(TObject *Sender);
	void __fastcall FileCloseItemClick(TObject *Sender);
	void __fastcall FileOpenItemClick(TObject *Sender);
	void __fastcall FileExitItemClick(TObject *Sender);
	void __fastcall FileSaveItemClick(TObject *Sender);
	void __fastcall FileSaveAsItemClick(TObject *Sender);
	void __fastcall CutItemClick(TObject *Sender);
	void __fastcall CopyItemClick(TObject *Sender);
	void __fastcall PasteItemClick(TObject *Sender);
	void __fastcall WindowMinimizeItemClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);

	void __fastcall HelpAboutItemClick(TObject *Sender);

	
    void __fastcall FormShow(TObject *Sender);
    void __fastcall MidiSetupClick(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
  void __fastcall Contents1Click(TObject *Sender);
  void __fastcall Search1Click(TObject *Sender);
  void __fastcall Find1Click(TObject *Sender);
  bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
  void __fastcall DragButtonClick(TObject *Sender);
  void __fastcall ResizeButtonClick(TObject *Sender);
  void __fastcall SelectButtonClick(TObject *Sender);
  void __fastcall ComSetup1Click(TObject *Sender);
  void __fastcall ReadPatchClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall SendFile1Click(TObject *Sender);
  void __fastcall ReadFile1Click(TObject *Sender);
  void __fastcall ExecutePatch1Click(TObject *Sender);
  void __fastcall KillAllPatches1Click(TObject *Sender);

  void __fastcall File1Click(TObject *Sender);
  void __fastcall SaveNVRAM1Click(TObject *Sender);
  void __fastcall EraseNVRAM1Click(TObject *Sender);
   
    
private:
public:
	virtual __fastcall TMainForm(TComponent *Owner);
	void __fastcall ShowHint(TObject *Sender);
  void __fastcall AppMessage(tagMSG &Msg, bool &Handled);
};
//----------------------------------------------------------------------------
extern TMainForm *MainForm;

//----------------------------------------------------------------------------
#endif
 