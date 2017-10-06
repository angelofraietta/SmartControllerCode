//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <sys\stat.h>

#include "Main.h"
#include "About.h"
#include "PatchUnit.h"
#include "BaseShellsUnit.h"
#include "CursorsUnit.h"
#include "ErrorUnit.h"
#include "ViewFormUnit.h"
#include "BaseShellsUnit.h"
#include "GraphicBoxUnit.h"
#include "windowsmessages.h"
#include "ComSetupUnit.h"
#include "simulatorinterface.h"
#include "fileQuestion.h"
#include "MidiSetupUnit.h"

//---------------------------------------------------------------------
#pragma resource "*.dfm"
TMainForm *MainForm;

//---------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent *Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{

 	Application->OnHint = ShowHint;
	Screen->OnActiveFormChange = UpdateMenuItems;
    LoadBoxCursors();

  Application->OnMessage = AppMessage;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ShowHint(TObject *Sender)
{
	StatusBar->SimpleText = Application->Hint;
}
//---------------------------------------------------------------------
void __fastcall TMainForm::FileNewItemClick(TObject *Sender)
{
//	CreateMDIChild("NONAME" + IntToStr(MDIChildCount + 1));
	new TPatchForm(Application);
}
//---------------------------------------------------------------------
void __fastcall TMainForm::FileOpenItemClick(TObject *Sender)
{
	if (OpenDialog->Execute())
//		CreateMDIChild(OpenDialog->FileName);
		new TPatchForm(Application, OpenDialog->FileName);
}
//---------------------------------------------------------------------
void __fastcall TMainForm::FileCloseItemClick(TObject *Sender)
{
	if (ActiveMDIChild)
		ActiveMDIChild->Close();
}
//---------------------------------------------------------------------
void __fastcall TMainForm::FileSaveItemClick(TObject *Sender)
{
	//---- save current file (ActiveMDIChild points to the window) ----
    if (ActiveMDIChild == ErrorForm)
        {
        ErrorForm->Save();
        return;
        }
    if(dynamic_cast<TPatchForm*> (ActiveMDIChild))
        {
         Screen->Cursor = crHourGlass;
        ((TPatchForm*) (ActiveMDIChild))->Save();
        Screen->Cursor = crDefault;
        return;
        }
    if(dynamic_cast<TBaseShellEditForm*> (ActiveMDIChild))
        {
        ((TBaseShellEditForm*)(ActiveMDIChild))->GetPatchForm()->Save();
        return;
        }
    if(dynamic_cast<TViewForm*> (ActiveMDIChild))
        {
        ((TViewForm*)(ActiveMDIChild))->GetPatchForm()->Save();
        return;
        }

}
//---------------------------------------------------------------------
void __fastcall TMainForm::FileSaveAsItemClick(TObject *Sender)
{
	//---- save current file under new name ----
    if(ActiveMDIChild == ErrorForm)
        {
        SaveDialog->Filter = "Log files (*.log)|*.log";
        SaveDialog->DefaultExt = "*.log";
        }
    else
        {
        SaveDialog->Filter = "Patch Files (*.pch)|*.pch";
        SaveDialog->DefaultExt = "*.pch";
        }

    if (SaveDialog->Execute())
        {
        if (ActiveMDIChild == ErrorForm)
            {
            ErrorForm->Save(SaveDialog->FileName);
            return;
            }

        if(dynamic_cast<TPatchForm*> (ActiveMDIChild))
            {
            ((TPatchForm*) (ActiveMDIChild))->Save(SaveDialog->FileName);
            return;
            }
        if(dynamic_cast<TBaseShellEditForm*> (ActiveMDIChild))
            {
            ((TBaseShellEditForm*)(ActiveMDIChild))->GetPatchForm()->Save(SaveDialog->FileName);
            return;
            }
        if(dynamic_cast<TViewForm*> (ActiveMDIChild))
            {
            ((TViewForm*)(ActiveMDIChild))->GetPatchForm()->Save(SaveDialog->FileName);
            return;
            }
        }

}
//---------------------------------------------------------------------
void __fastcall TMainForm::FileExitItemClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------
void __fastcall TMainForm::CutItemClick(TObject *Sender)
{
	//---- cut selection to clipboard ----
}
//---------------------------------------------------------------------
void __fastcall TMainForm::CopyItemClick(TObject *Sender)
{
	//---- copy selection to clipboard ----
}
//---------------------------------------------------------------------
void __fastcall TMainForm::PasteItemClick(TObject *Sender)
{
	//---- paste from clipboard ----
}
//---------------------------------------------------------------------
void __fastcall TMainForm::WindowCascadeItemClick(TObject *Sender)
{
	Cascade();
}
//---------------------------------------------------------------------
void __fastcall TMainForm::WindowTileItemClick(TObject *Sender)
{
	Tile();
}
//---------------------------------------------------------------------
void __fastcall TMainForm::WindowArrangeItemClick(TObject *Sender)
{
	ArrangeIcons();
   ErrorForm->Top = ClientHeight - ErrorForm->Height; //lace at bottom of form
   ErrorForm->Width = ClientWidth;
}
//---------------------------------------------------------------------
void __fastcall TMainForm::WindowMinimizeItemClick(TObject *Sender)
{
	int i;

	//---- Must be done backwards through the MDIChildren array ----
	for (i=MDIChildCount-1; i >= 0; i--)
		MDIChildren[i]->WindowState = wsMinimized;
}
//---------------------------------------------------------------------
void __fastcall TMainForm::UpdateMenuItems(TObject *Sender)
{
	FileCloseItem->Enabled = MDIChildCount > 0;
	FileSaveItem->Enabled = MDIChildCount > 0;
	FileSaveAsItem->Enabled = MDIChildCount > 0;

	CutItem->Enabled = MDIChildCount > 0;
	CopyItem->Enabled = MDIChildCount > 0;
	PasteItem->Enabled = MDIChildCount > 0;
	SaveBtn->Enabled = MDIChildCount > 0;
	CutBtn->Enabled = MDIChildCount > 0;
	CopyBtn->Enabled = MDIChildCount > 0;
	PasteBtn->Enabled = MDIChildCount > 0;
	WindowCascadeItem->Enabled = MDIChildCount > 0;
	WindowTileItem->Enabled = MDIChildCount > 0;
	WindowArrangeItem->Enabled = MDIChildCount > 0;
	WindowMinimizeItem->Enabled = MDIChildCount > 0;
}
//---------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
	Screen->OnActiveFormChange = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::HelpAboutItemClick(TObject *Sender)
{
    AboutBox->ShowModal();
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::FormShow(TObject *Sender)
{
    //ErrorForm->Align = alBottom;

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::MidiSetupClick(TObject *Sender)
{
  MidiSetupForm->ReloadForm();
  MidiSetupForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   Screen->Cursor = crHourGlass;
   MidiSetupForm->CloseDevices();

}
//---------------------------------------------------------------------------




void __fastcall TMainForm::Contents1Click(TObject *Sender)
{
  static char MacroName [] =  "CONTENTS()";

  Application->HelpContext (0);
  Application->HelpCommand (HELP_COMMAND, (DWORD) MacroName);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Search1Click(TObject *Sender)
{
 static char MacroName [] =  "SEARCH()";

  Application->HelpContext (0);
  Application->HelpCommand (HELP_COMMAND, (DWORD) MacroName);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Find1Click(TObject *Sender)
{
 static char MacroName [] =  "FIND()";

  Application->HelpContext (0);
  Application->HelpCommand (HELP_COMMAND, (DWORD) MacroName);
}
//---------------------------------------------------------------------------

bool __fastcall TMainForm::FormHelp(WORD Command, int Data, bool &CallHelp)
{
  CallHelp = false;
  return CallHelp;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DragButtonClick(TObject *Sender)
{
  TGraphicControlBox::AllowResize (false);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ResizeButtonClick(TObject *Sender)
{
TGraphicControlBox::AllowResize (true);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SelectButtonClick(TObject *Sender)
{
TGraphicControlBox::AllowResize (false);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AppMessage(tagMSG &Msg, bool  &Handled)
{
  if (Msg.message == WM_SYSCOMMAND)
  {
    if (Msg.wParam == APPLICATION_OPEN_FILE)
    {
      Handled = true;
      Application->BringToFront ();

      if (Msg.lParam)
      {
        char file_name [255];
        if (GlobalGetAtomName ((ATOM)Msg.lParam, file_name, 255))
        {
          new TPatchForm(Application, file_name);
          GlobalDeleteAtom ((ATOM)Msg.lParam);
        }
      }

    }
  }
  /* for all other messages, Handled remains False so that other message handlers can respond */
}

void __fastcall TMainForm::ComSetup1Click(TObject *Sender)
{
  ComSetup->ShowModal ();  
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ReadPatchClick(TObject *Sender)
{
  if(PatchQuestion::NumberPatches(GetSelectedEngine()))
  {
    P_PATCH pPatch = PatchQuestion::GetPatch(GetSelectedEngine(), 0);
    new TPatchForm(Application, pPatch);
  }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  //DeleteAllPatches();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SendFile1Click(TObject *Sender)
{
  static unsigned key = 0;

	if (OpenDialog->Execute())
  {
    AnsiString filename (ExtractFileName(OpenDialog->FileName));

    if (GetSelectedEngine() == GetSimulator())
    {
      filename = filename + AnsiString(".bak");
    }


    FileQuestion::OpenFileForWrite(GetSelectedEngine(), key, filename.c_str());

    struct stat statbuf;
    FILE* in_file = fopen(OpenDialog->FileName.c_str(), "r+b");
    if (in_file)
    {
      unsigned block_num = 0;

      fstat(fileno(in_file), &statbuf);
      unsigned file_size = statbuf.st_size;


      FileSendProgress->Position = 0;
      FileSendProgress->Max = file_size;
      FileSendProgress->Visible = true;

      BYTE data_buf [256];

      unsigned bytes_read = fread(data_buf, 1, 256, in_file);

      while (bytes_read)
      {
        FileQuestion::WriteBytes(GetSelectedEngine(), key, block_num, bytes_read, data_buf);

        FileSendProgress->Position += bytes_read;
        bytes_read = fread(data_buf, 1, 256, in_file);
        block_num++;
      }

      FileSendProgress->Visible = false;
      fclose(in_file);
    }

    FileQuestion::CloseFile(GetSelectedEngine(), key);

  }
  key++;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ReadFile1Click(TObject *Sender)
{
  unsigned key = 0;

	if (OpenDialog->Execute())
  {
    AnsiString filename (ExtractFileName(OpenDialog->FileName));


    unsigned bytes_to_read = FileQuestion::OpenFileForRead(GetSelectedEngine(), key, filename.c_str());

    if (GetSelectedEngine() == GetSimulator())
    {
      filename = filename + AnsiString(".bak");
    }

    FILE* out_file = fopen(filename.c_str(), "w+");
    if (out_file)
    {
      FileSendProgress->Position = 0;
      FileSendProgress->Max = bytes_to_read;
      FileSendProgress->Visible = true;

      BYTE data_buf [256];

      unsigned bytes_read = FileQuestion::ReadBytes(GetSelectedEngine(), key, data_buf, 256);

      while (bytes_read)
      {
        FileSendProgress->Position += bytes_read;
        fwrite (data_buf, 1, bytes_read, out_file);
        bytes_read = FileQuestion::ReadBytes(GetSelectedEngine(), key, data_buf, 256);
      }

      FileSendProgress->Visible = false;
      fclose(out_file);
    }

    FileQuestion::CloseFile(GetSelectedEngine(), key);

  }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ExecutePatch1Click(TObject *Sender)
{
	if (GetSelectedEngine() != GetSimulator() && OpenDialog->Execute())
    {
    unsigned key = 0;
    
    Screen->Cursor = crHourGlass;
    AnsiString filename = ExtractFileName(OpenDialog->FileName);

    FileQuestion::OpenFileForWrite(GetSelectedEngine(), key, filename.c_str());

    struct stat statbuf;
    FILE* in_file = fopen(OpenDialog->FileName.c_str(), "r");
    if (in_file)
    {
      unsigned block_num = 0;

      fstat(fileno(in_file), &statbuf);
      unsigned file_size = statbuf.st_size;


      FileSendProgress->Position = 0;
      FileSendProgress->Max = file_size;
      FileSendProgress->Visible = true;

      BYTE data_buf [256];

      unsigned bytes_read = fread(data_buf, 1, 256, in_file);

      while (bytes_read)
      {
        FileQuestion::WriteBytes(GetSelectedEngine(), key, block_num, bytes_read, data_buf);

        FileSendProgress->Position += bytes_read;
        bytes_read = fread(data_buf, 1, 256, in_file);
        block_num++;
      }

      FileSendProgress->Visible = false;
      fclose(in_file);
    }

    FileQuestion::CloseFile(GetSelectedEngine(), key);

    PatchQuestion::LoadPatchFile(GetSelectedEngine(), filename.c_str(), (DWORD)0);
    Screen->Cursor = crDefault;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::KillAllPatches1Click(TObject *Sender)
{
  if (GetSelectedEngine() != GetSimulator())
  {
    PatchQuestion::Destroy(GetSelectedEngine(), (unsigned long)0);
    while(PatchQuestion::NumberPatches(GetSelectedEngine()))
    {
      P_PATCH pPatch = PatchQuestion::GetPatch(GetSelectedEngine(), 0);
      PatchQuestion::Destroy(GetSelectedEngine(), pPatch);
    }
  }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TMainForm::File1Click(TObject *Sender)
{
  bool disable_local = GetSelectedEngine() != GetSimulator();
  ExecutePatch1->Enabled = disable_local;
  KillAllPatches1->Enabled = disable_local;
  SendFile1->Enabled = disable_local;
  ReadFile1->Enabled = disable_local;
  ReadPatch->Enabled = disable_local;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveNVRAM1Click(TObject *Sender)
{
  FileQuestion::SaveNVRAM(GetSelectedEngine());
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EraseNVRAM1Click(TObject *Sender)
{
  FileQuestion::EraseNVRAM(GetSelectedEngine());
}
//---------------------------------------------------------------------------




