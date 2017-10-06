#ifndef TMAXMIDIN_H
#define TMAXMIDIN_H

#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>

#include "MaxMidi.h"

//---------------------------------------------------------------------------
//	CMaxMidiIn Class Definition
//  adapted to builder by Angelo Fraietta
//	(C) Copyright, Paul A. Messick, 1996
//---------------------------------------------------------------------------
class TMaxMidiIn : public TWinControl
{
// Class-specific data
protected:
	HMIN		hDevice;		// handle to the MidiIn device
	DWORD		dwFlags;		// current flags for this device
	WORD		wDeviceID;		// device id, in case we need to reopen

	bool		fIsOpen;		// true if device is open
	char		Description[MAXPNAMELEN +1]; // description string

#ifdef _SYNC
	TMaxMidiSync* pSync; 		// the sync device object
#endif
#ifdef _TRACK
	TMaxMidiTrack* pTrack;		// track object associated with this input (only one)
#endif
	bool		fIsStarted;		// true if input started

public:
// Constructors/Destructor
	TMaxMidiIn(TComponent*, WORD);				// default constructor
	__fastcall ~TMaxMidiIn();				// destructor

// sync-dependent functions
#ifdef _SYNC
	TMaxMidiIn(TComponent*, WORD wDeviceID, TMaxMidiSync* pSync = NULL, DWORD dwFlags = MIDIIN_DEFAULT);
	void Attach(TMaxMidiSync* pSync);	// attaches the sync device
	void Detach(TMaxMidiSync* pSync);	// detaches the sync device
	TMaxMidiSync* GetSync(void) { return pSync; };
#endif

// track-dependent functions
#ifdef _TRACK
	void Attach(TMaxMidiTrack* pTrack); // attaches the track object
	void Detach(TMaxMidiTrack* pTrack);	// detaches the track object
#endif

// Implementation
	WORD GetIDFromName(LPSTR lpszDesc); // find corresponding ID given string name

	bool IsOpen(void);			// returns true if device is open
	LPSTR GetDescription(void); // returns pointer to desc string
	int GetNumDevices(void);	// returns number of input devices available

	bool Open(DWORD dwFlags = MIDIIN_DEFAULT);
	void Close(void);			// close the device without destroying class object

	void Start(void);			// start midi in
	void Stop(void);			// stop midi in
	void Reset(void);			// reset the timestamp to zero, if started
	LPMIDIEVENT Get(void);		// get received event, if any

	// *** V1.55 DLL ***
	DWORD GetFilters(void) { return GetMidiInFilters(hDevice); };
	void SetFilters(DWORD dwFilters) { SetMidiInFilters(hDevice, dwFilters); };

	virtual bool ProcessMidiData(LPMIDIEVENT lpEvent);
    unsigned        wDeviceSetupNum;//the number in the setup
// Generated message map functions
protected:
    void __fastcall OnMidiData(TMessage* Message);
    void __fastcall OnInClose(TMessage* Message);

	BEGIN_MESSAGE_MAP
    	MESSAGE_HANDLER(MIDI_DATA, TMessage*, OnMidiData)
      MESSAGE_HANDLER(MIM_CLOSE, TMessage*, OnInClose)
    END_MESSAGE_MAP(TWinControl)
};

#endif
