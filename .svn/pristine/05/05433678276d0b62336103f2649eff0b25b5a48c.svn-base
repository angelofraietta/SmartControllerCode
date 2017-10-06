//## begin module%3C60834100AF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C60834100AF.cm

//## begin module%3C60834100AF.cp preserve=no
//	Angelo Fraietta
//## end module%3C60834100AF.cp

//## Module: RtemsMidiDriver%3C60834100AF; Package specification
//## Subsystem: MidiDriver::hal_rtems%3C5F008D0309
//## Source file: c:\develop\MidicontrollerPatchEditor\mididriver\hal_rtems\rtemsmididriver.h

#ifndef rtemsmididriver_h
#define rtemsmididriver_h 1

//## begin module%3C60834100AF.additionalIncludes preserve=no
//## end module%3C60834100AF.additionalIncludes

//## begin module%3C60834100AF.includes preserve=yes
#include "iodata.h"
//## end module%3C60834100AF.includes


class MidiOutputDriver;
class MidiInputDriver;

//## begin module%3C60834100AF.declarations preserve=no
//## end module%3C60834100AF.declarations

//## begin module%3C60834100AF.additionalDeclarations preserve=yes
#define MAX_MIDI_DEVICES 3

class MidiInputDriver;
class MidiOutputDriver;
//## end module%3C60834100AF.additionalDeclarations


//## begin RtemsMidiDriver%3C607DDD03E0.preface preserve=yes
//## end RtemsMidiDriver%3C607DDD03E0.preface

//## Class: RtemsMidiDriver%3C607DDD03E0; Class Utility
//	Static class that joins input and output drivers to the
//	one module.
//	MAX_MIDI_DEVICES must be difined within this module in
//	the source.
//
//	Must be called by the device driver initialize function
//## Category: MidiDriver::hal_rtems%3C606B4B0131
//## Subsystem: MidiDriver::hal_rtems%3C5F008D0309
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class RtemsMidiDriver 
{
  //## begin RtemsMidiDriver%3C607DDD03E0.initialDeclarations preserve=yes
  //## end RtemsMidiDriver%3C607DDD03E0.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: AddInputDevice%1012952111
      //	Registers input device. Returns the device address to
      //	write to
      static short AddInputDevice (int device_num, MidiInputDriver* pDriver);

      //## Operation: AddOutputDevice%1012952112
      //	Registers Output device. Returns the device address to
      //	write to
      static short AddOutputDevice (int device_num, MidiOutputDriver* pDriver);

      //## Operation: initialize%1012952113
      //	Initializes irq handler for each device. Device number
      //	is givven as a parameter
      static bool initialize (int device_number);

      //## Operation: interrupt1%1012952117
      //	Function called by ISR function
      static void interrupt1 ();

      //## Operation: interrupt2%1012952118
      //	Function called by ISR function
      static void interrupt2 ();

      //## Operation: interrupt3%1012952119
      //	Function called by ISR function
      static void interrupt3 ();

      //## Operation: WriteOutputReady%1013139105
      //	Write function called by Output device in order to
      //	notify PIC that there is Data ready. Returns false if it
      //	was unable to write because the PLA was ready
      static bool WriteOutputReady (int device_num);

      //## Operation: OutputPlaStatus%1018482874
      //	Reads whether the PLA can be written to
      static bool OutputPlaStatus (int device_num);

      //## Operation: midiinterrupt1%1024352806
      //	Function called by ISR function
      static void midiinterrupt1 ();

      //## Operation: midiinterrupt2%1024352807
      //	Function called by ISR function
      static void midiinterrupt2 ();

      //## Operation: midiinterrupt3%1024352808
      //	Function called by ISR function
      static void midiinterrupt3 ();

    // Additional Public Declarations
      //## begin RtemsMidiDriver%3C607DDD03E0.public preserve=yes
      //## end RtemsMidiDriver%3C607DDD03E0.public

  protected:
    // Additional Protected Declarations
      //## begin RtemsMidiDriver%3C607DDD03E0.protected preserve=yes
      //## end RtemsMidiDriver%3C607DDD03E0.protected

  private:

    //## Other Operations (specified)
      //## Operation: interrupt%1012952114
      //	Function called by ISR. This function reads a word from
      //	the pla, which can be any type, and sends it to the midi
      //	iunput driver. The message can be any type. It then
      //	sends a message from the output driver if available
      static void interrupt (int dev_num);

      //## Operation: midiinterrupt%1024352805
      //	Function called by ISR. This receives only MIDI bytes
      //	and returns a diag message response. Tis is a faster
      //	functyion than interrupt 1 so we can handle the maximum
      //	midi rx rate
      static void midiinterrupt (int dev_num);

    // Additional Private Declarations
      //## begin RtemsMidiDriver%3C607DDD03E0.private preserve=yes
      //## end RtemsMidiDriver%3C607DDD03E0.private

  private: //## implementation
    // Data Members for Associations

      //## Association: MidiDriver::hal_rtems::<unnamed>%3C607E730255
      //## Role: RtemsMidiDriver::pMidiOut%3C607E74003B
      //## begin RtemsMidiDriver::pMidiOut%3C607E74003B.role preserve=no  public: MidiOutputDriver { -> 0..nUFHN}
      static MidiOutputDriver*  pMidiOut[MAX_MIDI_DEVICES];
      //## end RtemsMidiDriver::pMidiOut%3C607E74003B.role

      //## Association: MidiDriver::hal_rtems::<unnamed>%3C607E48004B
      //## Role: RtemsMidiDriver::pMidiIn%3C607E48025F
      //## begin RtemsMidiDriver::pMidiIn%3C607E48025F.role preserve=no  public: MidiInputDriver { -> 0..nUFHN}
      static MidiInputDriver*  pMidiIn[MAX_MIDI_DEVICES];
      //## end RtemsMidiDriver::pMidiIn%3C607E48025F.role

    // Additional Implementation Declarations
      //## begin RtemsMidiDriver%3C607DDD03E0.implementation preserve=yes
      //## end RtemsMidiDriver%3C607DDD03E0.implementation

};

//## begin RtemsMidiDriver%3C607DDD03E0.postscript preserve=yes
//## end RtemsMidiDriver%3C607DDD03E0.postscript

// Class Utility RtemsMidiDriver 

//## begin module%3C60834100AF.epilog preserve=yes
//## end module%3C60834100AF.epilog


#endif
