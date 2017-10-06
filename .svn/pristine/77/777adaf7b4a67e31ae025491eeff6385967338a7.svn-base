#include <iostream>
//#include "QTML.h"
#include "QuickTimeComponents.h"
//#include <Sound.h>
#include "QuickTimeMusic.h"
//#include "QtMusic.h"

using namespace std; 	//introduces namespace std

void QTMusic_PlayRisingNotesOnChannel (NoteAllocator theNoteAllocator, NoteChannel theNoteChannel)
{
	unsigned long			myDelay;
	long					myIndex;
	
	if ((theNoteAllocator == NULL) || (theNoteChannel == NULL))					// just makin' sure....
		return;
		
	NAPlayNote(theNoteAllocator, theNoteChannel, kMiddleC, 80);					// middle C at velocity 80
	Delay(40, &myDelay);														// delay 2/3 of a second
	NAPlayNote(theNoteAllocator, theNoteChannel, kMiddleC, 0);					// middle C at velocity 0: end note
	Delay(40, &myDelay);														// delay 2/3 of a second

	// obligatory loop of rising tones
	for (myIndex = kMiddleC; myIndex <= 94; myIndex++) {
		NAPlayNote(theNoteAllocator, theNoteChannel, myIndex, 80);				// pitch myIndex at velocity 80
		NAPlayNote(theNoteAllocator, theNoteChannel, myIndex + 7, 80);			// pitch myIndex + 7 (musical fifth) at velocity 80
		Delay(10, &myDelay);													// delay 1/6 of a second
		NAPlayNote(theNoteAllocator, theNoteChannel, myIndex, 0);				// pitch myIndex at velocity 0: end note
		NAPlayNote(theNoteAllocator, theNoteChannel, myIndex + 7, 0);			// pitch myIndex + 7 at velocity 0: end note
	}

}

void QTMusic_PlaySomeNotes (void)
{
	NoteAllocator			myNoteAllocator;
	NoteChannel				myNoteChannel;
	NoteRequest				myNoteRequest;
	ComponentResult			myErr = noErr;

	myNoteAllocator = NULL;
	myNoteChannel = NULL;

	// open the note allocator component
	myNoteAllocator = OpenDefaultComponent(kNoteAllocatorComponentType, 0);
	if (myNoteAllocator == NULL)
		goto bail;

	// fill out a note request, using NAStuffToneDescription
	myNoteRequest.info.flags = 0;
	//myNoteRequest.info.reserved = 0;
	*(short *)(&myNoteRequest.info.polyphony) = EndianS16_NtoB(2);				// simultaneous tones
	*(Fixed *)(&myNoteRequest.info.typicalPolyphony) = EndianU32_NtoB(0x00010000);

	myErr = NAStuffToneDescription(myNoteAllocator, 1, &myNoteRequest.tone);
	if (myErr != noErr)
		goto bail;
		
	// allocate a note channel
	myErr = NANewNoteChannel(myNoteAllocator, &myNoteRequest, &myNoteChannel);
	if ((myErr != noErr) || (myNoteChannel == NULL))
		goto bail;

	// if we've gotten this far, it's OK to play some musical notes; lovely
	QTMusic_PlayRisingNotesOnChannel(myNoteAllocator, myNoteChannel);
		
bail:
	if (myNoteChannel != NULL)
		NADisposeNoteChannel(myNoteAllocator, myNoteChannel);
		
	if (myNoteAllocator != NULL)
		CloseComponent(myNoteAllocator);
}

#if 0
ComponentResult QTMusic_ReadHook (MusicMIDIPacket *theMIDIPacket, long theRefCon)
{
	MIDIInputExample		*myMIE;
	Boolean					isMajor;
	short					myStatus, myPitch, myVeloc;

	if (theRefCon == 0L)
		return(paramErr);

	myMIE = (MIDIInputExample *)theRefCon;

	if (theMIDIPacket->reserved == kMusicPacketPortLost)							// port gone? make channel quiet
		NASetNoteChannelVolume(myMIE->fNoteAllocator, myMIE->fNoteChannel, 0);
	else if (theMIDIPacket->reserved == kMusicPacketPortFound)						// port back? raise volume
		NASetNoteChannelVolume(myMIE->fNoteAllocator, myMIE->fNoteChannel, 0x00010000);
	else if (theMIDIPacket->length == 3) {
		myStatus = theMIDIPacket->data[0] & 0xF0;
		myPitch = theMIDIPacket->data[1];
		myVeloc = theMIDIPacket->data[2];
		
		switch (myStatus) {
			case 0x80:
				myVeloc = 0;
				// falls thru into case 0x90; almost as fun as a goto, eh mom?
			case 0x90:
				isMajor = (myPitch % 5 == 0);
				NAPlayNote(myMIE->fNoteAllocator, myMIE->fNoteChannel, myPitch, myVeloc);
				NAPlayNote(myMIE->fNoteAllocator, myMIE->fNoteChannel, myPitch + 3 + isMajor, myVeloc);
				NAPlayNote(myMIE->fNoteAllocator, myMIE->fNoteChannel, myPitch + 7, myVeloc);
				break;
		}
	}
		
	return(noErr);
}

#endif
#if 0
void QTMusic_UseMIDIInput (void)
{
	MIDIInputExample		myMIE;
	NoteRequest				myNoteRequest;
	MusicMIDIReadHookUPP	myReadHookUPP = NULL;
	ComponentResult			myErr = noErr;
	SynthesizerConnections  sc;
	QTMIDIPortListHandle	inHandle, outHandle;
	

	// open the note allocator component
	myMIE.fNoteAllocator = OpenDefaultComponent(kNoteAllocatorComponentType, 0);
	if (myMIE.fNoteAllocator == NULL)
		goto bail;
	
	myErr = NAGetMIDIPorts (myMIE.fNoteAllocator, &inHandle,  &outHandle);
	
	if (myErr != noErr)
	{
		goto bail;
	}

	myErr = NAGetDefaultMIDIInput(myMIE.fNoteAllocator, &sc);
	
	if (myErr != noErr)
	{
		goto bail;
	}

	myNoteRequest.info.flags = 0;
//	myNoteRequest.info.reserved = 0;
	*(short *)(&myNoteRequest.info.polyphony) = EndianS16_NtoB(2);				// simultaneous tones
	*(Fixed *)(&myNoteRequest.info.typicalPolyphony) = EndianU32_NtoB(0x00010000);

	myErr = NAStuffToneDescription(myMIE.fNoteAllocator, kInst_AcousticGrandPiano, &myNoteRequest.tone);
	if (myErr != noErr)
		goto bail;
		
	// allocate a note channel
	myErr = NANewNoteChannel(myMIE.fNoteAllocator, &myNoteRequest, &myMIE.fNoteChannel);
	if (myErr != noErr)
		goto bail;
		
	myReadHookUPP = NewMusicMIDIReadHookProc(QTMusic_ReadHook);
	myErr = NAUseDefaultMIDIInput(myMIE.fNoteAllocator, myReadHookUPP, (long)&myMIE, 0L);
	//myErr = NAUseDefaultMIDIInput(myMIE.fNoteAllocator, QTMusic_ReadHook, (long)&myMIE, 0L);
	if (myErr == noErr)
	{
		while (!Button())
			;
		NALoseDefaultMIDIInput(myMIE.fNoteAllocator);
	}

bail: 
	if (myReadHookUPP != NULL)
		DisposeRoutineDescriptor(myReadHookUPP);
		
	if (myMIE.fNoteAllocator != NULL)
		CloseComponent(myMIE.fNoteAllocator);									// disposes note channel too
}

#endif

int main( void )
{

	ComponentResult			myErr;
	//myErr = InitializeQTML(0); 
	QTMusic_PlaySomeNotes ();
	cout << "This is a test" ;

	//QTMusic_UseMIDIInput();
	
	//TerminateQTML(); 

	
	return 0;
}