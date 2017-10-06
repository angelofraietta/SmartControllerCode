//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MidiOutControl.h"
#include "MidiSetupUnit.h"
#include <fstream>
//===========================================================================
//	MidiOutControl Class Implementation
//  Adapted to Builder by Angelo Fraietta

//===========================================================================



//---------------------------------------------------------------------------
//	TMidiOutControl Constructors
//---------------------------------------------------------------------------

__fastcall TMidiOutControl::TMidiOutControl(TComponent* Owner, WORD DeviceID)
    :TComponent(Owner),wDeviceID(DeviceID)
{
	hDevice = 0;
	fIsOpen = false;
	Description[0] = 0;
}


//---------------------------------------------------------------------------
//	GetIDFromName
//---------------------------------------------------------------------------
WORD TMidiOutControl::GetIDFromName(LPSTR lpszDesc)
{
	WORD id;
	char thisDesc[MAXPNAMELEN];
	WORD MaxDevs = (WORD)GetNumOutDevices();

	for(id = 0; id < MaxDevs; id++)
	{
		GetMidiOutDescription(id, thisDesc);
		if(strcmp(thisDesc, lpszDesc) == 0)
			return id;

		id++;
	}

	return ERR_NOMATCH;
}


//---------------------------------------------------------------------------
//	TMidiOutControl Destructor
//---------------------------------------------------------------------------
__fastcall TMidiOutControl::~TMidiOutControl()
{
	Close();
}

//---------------------------------------------------------------------------
//	Open/Close
//---------------------------------------------------------------------------
bool TMidiOutControl::Open(DWORD dwFlags)
{
	HSYNC hSync = 0;

	// get the description of the device
	GetMidiOutDescription(wDeviceID, Description);

	if(!fIsOpen)
	{
		TMidiOutControl::dwFlags = dwFlags;
		TMidiOutControl::wDeviceID = wDeviceID;
		hDevice = OpenMidiOut(NULL, wDeviceID, hSync, dwFlags);
	}

	if(hDevice > MXMIDIERR_MAXERR)
		fIsOpen = true;
	else
		hDevice = 0;
	return fIsOpen;
}

void TMidiOutControl::Close(void)
{
	if(fIsOpen)
	{
		Reset();
		CloseMidiOut(hDevice);
    }

	fIsOpen = false;
}

//---------------------------------------------------------------------------
//	Information Functions
//---------------------------------------------------------------------------
bool TMidiOutControl::IsOpen(void)
{
	return fIsOpen;
}

LPSTR TMidiOutControl::GetDescription(void)
{
	return Description;
}

int TMidiOutControl::GetNumDevices(void)
{
	return GetNumOutDevices();
}

//---------------------------------------------------------------------------
//	Put
//---------------------------------------------------------------------------
bool TMidiOutControl::Put(LPMIDIEVENT lpEvent)
{
	if(fIsOpen)
		return (PutMidiOut(hDevice, lpEvent) == 0);

	return true;		// act as though it accepts everything
						// in case Put is called when not open
}

//---------------------------------------------------------------------------
//	Reset/Flush
//---------------------------------------------------------------------------
void TMidiOutControl::Reset(void)
{
    TCursor CurrentCursor = (TCursor)Screen->Cursor;
    Screen->Cursor = crHourGlass;

	if(fIsOpen)
		ResetMidiOut(hDevice);

    Screen->Cursor = CurrentCursor;
}

void TMidiOutControl::Flush(void)
{
	if(fIsOpen)
		FlushMidiOut(hDevice);
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
