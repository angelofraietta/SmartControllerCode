//---------------------------------------------------------------------------
#ifndef MidiOutControlH
#define MidiOutControlH

#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>

#include "MaxMidi.h"

//---------------------------------------------------------------------------
//	CMaxMidiOut Class Definition
//  Adapted to Builder by Angelo Fraietta
//	(C) Copyright, Paul A. Messick, 1996
//---------------------------------------------------------------------------


class TMidiOutControl : public TComponent
{
// Class-specific data
protected:
	HMOUT		hDevice;		// handle to the MidiOut device
	DWORD		dwFlags;		// current flags, in case we reopen
	WORD		wDeviceID;		// device ID of attached device

	bool		fIsOpen;		// true if device is open
	char		Description[MAXPNAMELEN +1]; // description string


public:
	__fastcall TMidiOutControl(TComponent*, WORD wDeviceID = 0);
	__fastcall ~TMidiOutControl();				// destructor

    HMOUT GetHandle() {return hDevice;}

// Implementation
	WORD GetIDFromName(LPSTR lpszDesc); // find corresponding ID given string name

	bool IsOpen(void);			// returns true if device is open
	LPSTR GetDescription(void); // returns pointer to desc string
	int GetNumDevices(void);	// returns number of output devices available

	bool Open(DWORD dwFlags = MIDIOUT_DEFAULT);
	void Close(void);			// close the device without destroying class object

	bool Put(LPMIDIEVENT lpEvent); // output an event
	void Reset(void);			// reset the output device
	void Flush(void);			// flush the output queue

	// *** V1.55 DLL ***
	DWORD GetFilters(void) { return GetMidiOutFilters(hDevice); };
	void SetFilters(DWORD dwFilters) { SetMidiOutFilters(hDevice, dwFilters); };

	virtual void ProcessOutBufferReady(void) { };

// Generated message map functions
protected:
};

#define MERGE_BUFFER_SIZE 512	// should be the size of the output device buffer

#endif
