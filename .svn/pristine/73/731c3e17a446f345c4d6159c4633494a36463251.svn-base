
//===========================================================================
//	TMaxMidiIn Class Implementation
//  adapted to builder by Angelo Fraietta
//	(C) Copyright, Paul A. Messick, 1996
//===========================================================================


#include "TMaxMidiIn.h"
#include "MidiSetupUnit.h"
#include "interfacebridge.h"
#include <fstream.h>

//---------------------------------------------------------------------------
//	TMaxMidiIn Constructors
//---------------------------------------------------------------------------

TMaxMidiIn::TMaxMidiIn(TComponent* Owner, WORD DeviceID)
    :TWinControl(Owner), wDeviceID(DeviceID)
{
	hDevice = 0;
	fIsOpen = false;
	Description[0] = 0;
    ParentWindow = MidiSetupForm->Handle;
#ifdef _SYNC
	pSync = 0;
#endif
#ifdef _TRACK
	pTrack = 0;
#endif

}

#ifdef _SYNC
TMaxMidiIn::TMaxMidiIn(TComponent* Owner, WORD DeviceID, TMaxMidiSync* pSync, DWORD dwFlags)
TWinControl(Owner), wDeviceID(DeviceID)
{
#ifdef _TRACK
	pTrack = 0;
#endif

	Attach(pSync);
	Open(dwFlags);
}
#endif


//---------------------------------------------------------------------------
//	GetIDFromName
//---------------------------------------------------------------------------
WORD TMaxMidiIn::GetIDFromName(LPSTR lpszDesc)
{
	WORD id;
	char thisDesc[MAXPNAMELEN];
	WORD MaxDevs = (WORD)GetNumInDevices();

	for(id = 0; id < MaxDevs; id++)
	{
		GetMidiInDescription(id, thisDesc);
		if(strcmp(thisDesc, lpszDesc) == 0)
			return id;

		id++;
	}

	return ERR_NOMATCH;
}

//---------------------------------------------------------------------------
//	Attach/Detach
//---------------------------------------------------------------------------

#ifdef _SYNC
void TMaxMidiIn::Attach(TMaxMidiSync* pSync)
{
	TMaxMidiIn::pSync = pSync;
}

void TMaxMidiIn::Detach(TMaxMidiSync* pSync)
{
	// detach this sync device, if it is attached
	if(pSync == TMaxMidiIn::pSync)
		pSync = NULL;

	// close and reopen the device
	if(fIsOpen)
	{
		Close();
		Open(dwFlags);
	}
}
#endif

#ifdef _TRACK
void TMaxMidiIn::Attach(CMaxMidiTrack* pTrack)
{
	// detach the track if one was already attached
	if(TMaxMidiIn::pTrack != NULL)
		TMaxMidiIn::pTrack->Detach(this);

	// attach the new track
	TMaxMidiIn::pTrack = pTrack;

	// tell the track about this input device
	pTrack->Attach(this);
}

void TMaxMidiIn::Detach(CMaxMidiTrack* pTrack)
{
	// detach this track, if it is attached
	if(pTrack == TMaxMidiIn::pTrack)
		pTrack = NULL;
}
#endif

//---------------------------------------------------------------------------
//	TMaxMidiIn Destructor
//---------------------------------------------------------------------------
__fastcall TMaxMidiIn::~TMaxMidiIn()
{
	Close();
}

//---------------------------------------------------------------------------
//	Open
//---------------------------------------------------------------------------
bool TMaxMidiIn::Open(DWORD dwFlags)
{
	HSYNC hSync = 0;

	// get the description of the device
	GetMidiInDescription(wDeviceID, Description);

#ifdef _SYNC
	// get the sync device handle
	if(TMaxMidiIn::pSync)
		hSync = TMaxMidiIn::pSync->GetHSync();
#endif

	if(!fIsOpen)
	{
		TMaxMidiIn::dwFlags = dwFlags;
		hDevice = OpenMidiIn(this->Handle, wDeviceID, hSync, dwFlags);
	}

	if(hDevice > MXMIDIERR_MAXERR)
		fIsOpen = TRUE;
	else
		hDevice = 0;

 	return fIsOpen;
}

//---------------------------------------------------------------------------
//	Close
//---------------------------------------------------------------------------
void TMaxMidiIn::Close(void)
{
	if(fIsOpen)
	{
		Stop();
		CloseMidiIn(hDevice);
	}


	fIsOpen = FALSE;
}

//---------------------------------------------------------------------------
//	Information Functions
//---------------------------------------------------------------------------
bool TMaxMidiIn::IsOpen(void)
{
	return fIsOpen;
}

LPSTR TMaxMidiIn::GetDescription(void)
{
	return Description;
}

int TMaxMidiIn::GetNumDevices(void)
{
	return GetNumInDevices();
}

//---------------------------------------------------------------------------
//	Start/Stop
//---------------------------------------------------------------------------
void TMaxMidiIn::Start(void)
{
	if(fIsOpen)
	{
		fIsStarted = TRUE;
		StartMidiIn(hDevice);
	}
}

void TMaxMidiIn::Stop(void)
{
	if(fIsOpen)
	{
		fIsStarted = FALSE;
		StopMidiIn(hDevice);
	}
}

void TMaxMidiIn::Reset(void)
{
	if(fIsOpen && fIsStarted)
	{
		StopMidiIn(hDevice);
		StartMidiIn(hDevice);
	}
}

//---------------------------------------------------------------------------
//	Get Data
//---------------------------------------------------------------------------
LPMIDIEVENT TMaxMidiIn::Get(void)
{
	return GetMidiIn(hDevice);
}

/////////////////////////////////////////////////////////////////////////////
// TMaxMidiIn message handlers

//---------------------------------------------------------------------------
//	OnMimData
//---------------------------------------------------------------------------
void __fastcall TMaxMidiIn::OnMidiData(TMessage* Message)
{
	LPMIDIEVENT lpEvent;

	// send the data to the track object, if attached
	while((lpEvent = Get()) != 0)
	{
		if(ProcessMidiData(lpEvent) == TRUE)
#ifdef _TRACK
			if(pTrack)
				pTrack->Write(lpEvent);
#else
			;
#endif
	}
}


void __fastcall TMaxMidiIn::OnInClose(TMessage* Message)
{
   ;
//    fIsOpen = false; // if enabled, will cause device to close
                        //when it may have been re-opened
}


bool TMaxMidiIn::ProcessMidiData(LPMIDIEVENT lpEvent)
{
    //StdMidiInProcessMidiIn(wDeviceSetupNum, lpEvent);
    return true;
}
