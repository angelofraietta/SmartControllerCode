//---------------------------------------------------------------------------
#ifndef MidiInputUnitH
#define MidiInputUnitH

#include "midiinputsync.h"

class TTestWrapperForm;

typedef void (*receiveFunction)(unsigned char);
//---------------------------------------------------------------------------

class MidiInDriver:public MidiInputSync
{
	public:
  	MidiInDriver (receiveFunction display,  int queue_size) : MidiInputSync (queue_size),
    _display(display){}
    ~MidiInDriver() {Purge(); kill();}
    void processMidiInput();

  private :
    receiveFunction _display;

};


#endif
