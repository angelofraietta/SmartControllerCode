//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("SmartController.res");
USEFORM("About.cpp", AboutBox);
USEFORM("BaseShellsUnit.cpp", BaseShellEditForm);
USEFORM("ConnectorEditUnit.cpp", ConnectorEditForm);
USEUNIT("ConnectorLine.cpp");
USEUNIT("CursorsUnit.cpp");
USEUNIT("DragConnector.cpp");
USEFORM("EditPatchUnit.cpp", EditPatchForm);
USEFORM("ErrorUnit.cpp", ErrorForm);
USEUNIT("FormRefresh.cpp");
USEUNIT("IdentityHook.cpp");
USEFORM("Main.cpp", MainForm);
USEFORM("NewObjectsList.cpp", ObjectsForm);
USEUNIT("ObjectBox.cpp");
USEUNIT("ObjectSocket.cpp");
USEFORM("PatchUnit.cpp", PatchForm);
USEUNIT("PerformanceView.cpp");
USEUNIT("ShellDisplayParam.cpp");
USEUNIT("TreeNodeFlasher.cpp");
USEUNIT("TypeElementUnit.cpp");
USEUNIT("VariableSizeBox.cpp");
USEUNIT("VCLGLOBFUNC.cpp");
USEFORM("ViewFormUnit.cpp", ViewForm);
USEUNIT("ViewRefresh.cpp");
USEUNIT("graphics\GraphicShape.cpp");
USEUNIT("graphics\DragLine.cpp");
USEUNIT("graphics\GraphicBoxFollow.cpp");
USEUNIT("graphics\GraphicBoxUnit.cpp");
USEUNIT("graphics\GraphicLine.cpp");
USEUNIT("graphics\GraphicLineFollow.cpp");
USEUNIT("graphics\CommonFunctions.cpp");
USEFORM("SaveChanged.cpp", FileChangedDialog);
USERES("ComposerCursors.res");
USEUNIT("TComment.cpp");
USEFORM("CommentFormUnit.cpp", CommentDialog);
USEUNIT("graphics\KillerUnit.cpp");
USEUNIT("..\controller\source\engineinterface\patchquestion.cpp");
USEUNIT("..\controller\source\engineinterface\baseshellquestion.cpp");
USEUNIT("..\controller\source\engineinterface\connectorquestion.cpp");
USEUNIT("..\controller\source\engineinterface\eventquestion.cpp");
USEUNIT("..\controller\source\engineinterface\identityquestion.cpp");
USEUNIT("..\controller\source\engineinterface\presentationquestion.cpp");
USEUNIT("..\controller\source\engineinterface\smutility.cpp");
USEUNIT("ToggleBox.cpp");
USEUNIT("..\controller\source\engineinterface\sessionquestion.cpp");
USEFORM("ComSetupUnit.cpp", ComSetup);
USEUNIT("..\controller\source\link_driver\linkprotocol.cpp");
USEUNIT("..\controller\source\link_driver\linklayer.cpp");
USEUNIT("..\controller\source\link_driver\hal_windows\windowscommstream.cpp");
USEUNIT("..\controller\source\link_driver\hal_windows\windowscommport.cpp");
USELIB("..\controller\source\hal_windows\smartcontrol.lib");
USEUNIT("..\controller\source\link_driver\crc32.cpp");
USEUNIT("..\controller\source\engineinterface\filequestion.cpp");
USEUNIT("..\controller\source\engineinterface\sysexfilequestion.cpp");
USEUNIT("..\controller\source\engineinterface\QUESTIONTASK.cpp");
USEUNIT("..\threads\source\activeobject.cpp");
USEUNIT("..\threads\source\hal_windows\windowsevent.cpp");
USEUNIT("..\threads\source\hal_windows\windowsthread.cpp");
USEUNIT("numberboxwindowunit.cpp");
USEUNIT("NumberBox.cpp");
USEUNIT("..\controller\source\engineinterface\viewquestion.cpp");
USEFORM("MidiSetupUnit.cpp", MidiSetupForm);
USEUNIT("..\controller\source\link_driver\UDPPORT.cpp");
USEUNIT("..\controller\source\link_driver\networklayer.cpp");
//---------------------------------------------------------------------------
#include "PatchUnit.h"
#include "windowsmessages.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, int argc)
{
  const char* file_name = NULL;
  if (strlen (argv))
    {
    if (argv [strlen (argv) -1] == '\"')
      {
      argv [strlen (argv) -1] = '\0';
      }

    if (argv [0] == '\"')
      {
      file_name = argv + 1;
      }

    else
      {
      file_name = argv;
      }
      
    }
       Application->Title = "";
        HWND hPrevApp = ::FindWindow(NULL, "SmartController");

        // FindWindow returns a non-zero HWND if it finds the window
        // If the window was found, restore it and return without running
    /*    if(hPrevApp)
            {
            ATOM atom_file_name = 0;
            if (file_name)
              {
              atom_file_name = GlobalAddAtom (file_name);
              }

            PostMessage(hPrevApp, WM_SYSCOMMAND, APPLICATION_OPEN_FILE, atom_file_name);
            return 0;
            }
      */
     try
        {
                 Application->Initialize();
                 Application->Title = "SmartController";
                 //Application->HelpFile = "AlgCmp.hlp";
     Application->CreateForm(__classid(TMainForm), &MainForm);
     Application->CreateForm(__classid(TAboutBox), &AboutBox);
     Application->CreateForm(__classid(TErrorForm), &ErrorForm);
     Application->CreateForm(__classid(TObjectsForm), &ObjectsForm);
     Application->CreateForm(__classid(TFileChangedDialog), &FileChangedDialog);
     Application->CreateForm(__classid(TCommentDialog), &CommentDialog);
     Application->CreateForm(__classid(TComSetup), &ComSetup);
     Application->CreateForm(__classid(TMidiSetupForm), &MidiSetupForm);
     if (file_name)
      {
      new TPatchForm(Application, file_name);
      }

     Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------



