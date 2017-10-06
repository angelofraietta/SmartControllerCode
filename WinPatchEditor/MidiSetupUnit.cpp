//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <fstream.h>
#include "MidiSetupUnit.h"

#include "interfacebridge.h"
#include "ErrorUnit.h"
//#include "help.h"
#define MIDI_SETUP_FILE "MidiSetup.ini"
#define INPUT_DEVICES_DELIMIT "[input devices]"
#define OUTPUT_DEVICES_DELIMIT "[output devices]"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMidiSetupForm *MidiSetupForm;

// declare functions imported in dll
extern "C"
{
	void OpenCommPorts ();
  bool OpenMidiInputDevice (unsigned device_num, unsigned device_index);
  bool OpenMidiOutputDevice (unsigned device_num, unsigned device_index);
  void CloseMidiInputDevices ();
  void CloseMidiOutputDevices ();
}


class IndexObj: public TObject
{
  public :
    IndexObj(unsigned val) :_val(val){}
    unsigned _val;

};

bool GetMidiOutDescription(WORD wDeviceID, char* lpzDesc)
{
  bool ret = false;

	MIDIOUTCAPS Caps;

	if(midiOutGetDevCaps(wDeviceID, (LPMIDIOUTCAPS) &Caps, sizeof(Caps)) != MMSYSERR_BADDEVICEID)
		{
	  lstrcpy(lpzDesc, (char*)Caps.szPname);
	  ret = true;
    }
  return ret;
}

bool GetMidiInDescription(WORD wDeviceID, char* lpzDesc)
{
  bool ret = false;
	MIDIINCAPS Caps;

	if(midiInGetDevCaps(wDeviceID, (LPMIDIINCAPS) &Caps, sizeof(Caps)) !=
			MMSYSERR_BADDEVICEID)
  {
		lstrcpy(lpzDesc, (LPSTR)Caps.szPname);
	  ret = true;
  }
  return ret;

}

//---------------------------------------------------------------------------
__fastcall TMidiSetupForm::TMidiSetupForm(TComponent* Owner)
    : TForm(Owner)
{
    InputDevices = new TStringList;
    OutputDevices = new TStringList;

//    HelpContext = HID_MIDI_SETUP;

    char buf [MAXPNAMELEN];
    for (WORD i = 0; i < (WORD)midiInGetNumDevs(); i++)
        {
        bool Valid = GetMidiInDescription(i, buf);
        if (Valid)
            {
            IndexObj* pObj = new IndexObj(i);
            InputDevices->AddObject(buf, pObj);
            }
        }

    for (WORD i = 0; i < (WORD)midiOutGetNumDevs(); i++)
        {
        bool Valid = GetMidiOutDescription(i, buf);
        if (Valid)
            {
            IndexObj* pObj = new IndexObj(i);
            OutputDevices->AddObject(buf, pObj);
            }
        }

    //set the filename Variable
    FileName = GetCurrentDir() + String("\\") + MIDI_SETUP_FILE;

}
//---------------------------------------------------------------------------

__fastcall TMidiSetupForm::~TMidiSetupForm()
{
    delete InputDevices;
    delete OutputDevices;
}

void __fastcall TMidiSetupForm::FormDestroy(TObject *Sender)
{
    CloseDevices();
    InputDevices->Clear();
    OutputDevices->Clear();

}
//---------------------------------------------------------------------------


void __fastcall TMidiSetupForm::ChangeButtonClick(TObject *Sender)
{
    Screen->Cursor = crHourGlass;
    ofstream OutFile(FileName.c_str());
    if(!OutFile)
        throw (String("Unable to save Midi Settings"));
    //save input device settings
    OutFile<<INPUT_DEVICES_DELIMIT<<'\n';
    for (int i = 0; i < CurrentInputList->Items->Count; i++)
         OutFile<<CurrentInputList->Items->Strings[i].c_str()<<'\n';

    //save output device settings
    OutFile<<OUTPUT_DEVICES_DELIMIT<<'\n';
    for (unsigned i = 0; i < (unsigned)CurrentOutputList->Items->Count; i++)
         OutFile<<CurrentOutputList->Items->Strings[i].c_str()<<'\n';
    OutFile.close();
    //apply new device settings
    CloseDevices();
    OpenDevices();
    Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void TMidiSetupForm::GetDeviceSettings(TStringList* InputList, TStringList* OutputList)
{
    ifstream InFile(FileName.c_str());
    if(InFile)
        {
        const BuffLen = 50;
        char buff[BuffLen];
        //read input devices
        do{
            //get input device delimit
           InFile.getline(buff, BuffLen);
           }while (!strcmp(buff, INPUT_DEVICES_DELIMIT));

        //read the first value
        while (strcmp(buff, OUTPUT_DEVICES_DELIMIT))
            {
            InputList->Add(buff);
            InFile.getline(buff, BuffLen);
            }
        //read output devices
        while (!InFile.getline(buff, BuffLen).eof())
            OutputList->Add(buff);

        //now close
        InFile.close();
        }

    else
    {
      ShowModal ();
    }

}
void __fastcall TMidiSetupForm::OKButtonClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------


void __fastcall TMidiSetupForm::AvailableOutputListDblClick(
      TObject *Sender)
{
    //move from available list to current list
    int Index = AvailableOutputList->ItemIndex;
    if( Index >= 0)
        {
        String DeviceName = AvailableOutputList->Items->Strings[Index];
        TObject* DeviceObject = AvailableOutputList->Items->Objects[Index];
        CurrentOutputList->Items->AddObject(DeviceName, DeviceObject);
        AvailableOutputList->Items->Delete(Index);
        }
}
//---------------------------------------------------------------------------

void __fastcall TMidiSetupForm::CurrentOutputListDblClick(TObject *Sender)
{
    //move from current list to available list
    int Index = CurrentOutputList->ItemIndex;
    if( Index >= 0)
        {
        String DeviceName = CurrentOutputList->Items->Strings[Index];
        TObject* DeviceObject = CurrentOutputList->Items->Objects[Index];
        AvailableOutputList->Items->AddObject(DeviceName, DeviceObject);
        CurrentOutputList->Items->Delete(Index);
        }
    OutputUpDown->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TMidiSetupForm::AvailableInputListDblClick(TObject *Sender)
{
    //move from available list to current list
    int Index = AvailableInputList->ItemIndex;
    if( Index >= 0)
        {
        String DeviceName = AvailableInputList->Items->Strings[Index];
        TObject* DeviceObject = AvailableInputList->Items->Objects[Index];
        CurrentInputList->Items->AddObject(DeviceName, DeviceObject);
        AvailableInputList->Items->Delete(Index);
        }
}
//---------------------------------------------------------------------------

void __fastcall TMidiSetupForm::CurrentInputListDblClick(TObject *Sender)
{
    //move from current list to available list
    int Index = CurrentInputList->ItemIndex;
    if( Index >= 0)
        {
        String DeviceName = CurrentInputList->Items->Strings[Index];
        TObject* DeviceObject = CurrentInputList->Items->Objects[Index];
        AvailableInputList->Items->AddObject(DeviceName, DeviceObject);
        CurrentInputList->Items->Delete(Index);
        }
    InputUpDown->Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall TMidiSetupForm::CurrentInputListExit(TObject *Sender)
{
//        InputUpDown->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TMidiSetupForm::CurrentInputListClick(TObject *Sender)
{
 if(CurrentInputList->ItemIndex > -1 && CurrentInputList->Items->Count > 1)
    {
    InputUpDown->Max = 0;
    InputUpDown->Min = (short) - (((int)CurrentInputList->Items->Count) -1);
    InputUpDown->Position = (short) - ((int)CurrentInputList->ItemIndex);
    InputUpDown->Visible = true;
    }

 else
    InputUpDown->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TMidiSetupForm::CurrentOutputListClick(TObject *Sender)
{
 if(CurrentOutputList->ItemIndex > -1 && CurrentOutputList->Items->Count > 1)
    {
    OutputUpDown->Max = 0;
    OutputUpDown->Min = (short) - (((int)CurrentOutputList->Items->Count) -1);
    OutputUpDown->Position =(short) - ((int)CurrentOutputList->ItemIndex);
    OutputUpDown->Visible = true;
    }

 else
    OutputUpDown->Visible = false;

}
//---------------------------------------------------------------------------

void __fastcall TMidiSetupForm::OutputUpDownClick(TObject *Sender,
      TUDBtnType Button)
{
    int iPosition = - OutputUpDown->Position;
    //make the selected device move up or down in list
    String SwapString = CurrentOutputList->Items->Strings[iPosition];
    TObject* SwapObject = CurrentOutputList->Items->Objects[iPosition];
    String DeviceName;
    TObject* DeviceObject;
    if (Button == Comctrls::btPrev)//pressed up
        {
        DeviceName = CurrentOutputList->Items->Strings[iPosition -1];
        DeviceObject = CurrentOutputList->Items->Objects[iPosition -1];
        CurrentOutputList->Items->Strings[iPosition - 1] = SwapString;
        CurrentOutputList->Items->Objects[iPosition - 1] = SwapObject;
        }
    else
        {
        DeviceName = CurrentOutputList->Items->Strings[iPosition +1];
        DeviceObject = CurrentOutputList->Items->Objects[iPosition +1];
        CurrentOutputList->Items->Strings[iPosition + 1] = SwapString;
        CurrentOutputList->Items->Objects[iPosition + 1] = SwapObject;
        }
    CurrentOutputList->Items->Strings[iPosition] = DeviceName;
    CurrentOutputList->Items->Objects[iPosition] = DeviceObject;
    CurrentOutputList->ItemIndex = iPosition;
}
//---------------------------------------------------------------------------


void __fastcall TMidiSetupForm::InputUpDownClick(TObject *Sender,
      TUDBtnType Button)
{
    int iPosition = - InputUpDown->Position;
    //make the selected device move up or down in list
    String SwapString = CurrentInputList->Items->Strings[iPosition];
    TObject* SwapObject = CurrentInputList->Items->Objects[iPosition];
    String DeviceName;
    TObject* DeviceObject;
    if (Button == Comctrls::btPrev)//pressed up
        {
        DeviceName = CurrentInputList->Items->Strings[iPosition -1];
        DeviceObject = CurrentInputList->Items->Objects[iPosition -1];
        CurrentInputList->Items->Strings[iPosition - 1] = SwapString;
        CurrentInputList->Items->Objects[iPosition - 1] = SwapObject;
        }
    else
        {
        DeviceName = CurrentInputList->Items->Strings[iPosition +1];
        DeviceObject = CurrentInputList->Items->Objects[iPosition +1];
        CurrentInputList->Items->Strings[iPosition + 1] = SwapString;
        CurrentInputList->Items->Objects[iPosition + 1] = SwapObject;
        }
    CurrentInputList->Items->Strings[iPosition] = DeviceName;
    CurrentInputList->Items->Objects[iPosition] = DeviceObject;
    CurrentInputList->ItemIndex = iPosition;
}
//---------------------------------------------------------------------------

void TMidiSetupForm::CloseDevices()
{
  //close input devices
  CloseMidiInputDevices ();
  CloseMidiOutputDevices ();
}

void TMidiSetupForm::OpenDevices()
{

    //open current inputs
    for (unsigned i = 0; i <(unsigned) CurrentInputList->Items->Count; i++)
        {
        IndexObj* pObj = (IndexObj*)(CurrentInputList->Items->Objects[i]);
        OpenMidiInputDevice (pObj->_val, i);
        //pDevice->Start();
        //pDevice->wDeviceSetupNum = i;
        }
    //open current output devices
    for (unsigned i = 0; i <(unsigned) CurrentOutputList->Items->Count; i++)
        {
        IndexObj* pObj = (IndexObj*)(CurrentOutputList->Items->Objects[i]);
        OpenMidiOutputDevice (pObj->_val, i);
        }

}

void TMidiSetupForm::ReloadForm()
{
    AvailableInputList->Clear();
    AvailableOutputList->Clear();
    CurrentInputList->Clear();
    CurrentOutputList->Clear();
    //load the list from the user settings
    TStringList* InputList = new TStringList;
    TStringList* OutputList = new TStringList;
    //place all system devives in Available
    AvailableInputList->Items = InputDevices;
    AvailableOutputList->Items = OutputDevices;

    //get the user settings
    GetDeviceSettings(InputList, OutputList);


    //see if the user settings are valid
    for (int i = 0 ; i < InputList->Count; i++)
        {
        String UserDevice = InputList->Strings[i];
        int DeviceIndex;
        //see if this device is available on this system
        if ((DeviceIndex = InputDevices->IndexOf(UserDevice)) != -1)
            {
            TObject* DeviceObject =  InputDevices->Objects[DeviceIndex];
            //remove from available
            CurrentInputList->Items->AddObject(UserDevice, DeviceObject);
            DeviceIndex = AvailableInputList->Items->IndexOf(UserDevice);
            AvailableInputList->Items->Delete(DeviceIndex);
            }
        }

    for (int i = 0 ; i < OutputList->Count; i++)
        {
        String UserDevice = OutputList->Strings[i];
        int DeviceIndex;
        //see if this device is available on this system
        if ((DeviceIndex = OutputDevices->IndexOf(UserDevice)) != -1)
            {
            TObject* DeviceObject =  OutputDevices->Objects[DeviceIndex];
            //remove from available
            CurrentOutputList->Items->AddObject(UserDevice, DeviceObject);
            DeviceIndex = AvailableOutputList->Items->IndexOf (UserDevice);
            AvailableOutputList->Items->Delete(DeviceIndex);
            }

        }

    //load the system settings
    ChangeButtonClick(this);
    delete InputList;
    delete OutputList;

}



void __fastcall TMidiSetupForm::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
    if(Sender != this)
        CloseDevices();
}



void __fastcall TMidiSetupForm::FormCreate(TObject *Sender)
{
  ReloadForm();  
}
//---------------------------------------------------------------------------

