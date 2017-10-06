//## begin module%3CB613C5000E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CB613C5000E.cm

//## begin module%3CB613C5000E.cp preserve=no
//	Angelo Fraietta
//## end module%3CB613C5000E.cp

//## Module: EngineDataInput%3CB613C5000E; Pseudo Package specification
//## Subsystem: engine%39F51CB901B8
//## Source file: D:\develop\smartcontroller\controller\source\engine\enginedatainput.h

#ifndef enginedatainput_h
#define enginedatainput_h 1

//## begin module%3CB613C5000E.additionalIncludes preserve=no
//## end module%3CB613C5000E.additionalIncludes

//## begin module%3CB613C5000E.includes preserve=yes
//## end module%3CB613C5000E.includes

// MidiInputSync
#include "midiinputsync.h"

class StdMidiIn;
class AnalogIn;
class SysexDriver;
class DigitalIn;
namespace hal_include {
  class Scheduler;
} // namespace hal_include

class NVRAMStore;

//## begin module%3CB613C5000E.additionalDeclarations preserve=yes
//## end module%3CB613C5000E.additionalDeclarations


//## begin EngineDataInput%3CB613C5000E.preface preserve=yes
//## end EngineDataInput%3CB613C5000E.preface

//## Class: EngineDataInput%3CB613C5000E
//	Input DataDriver for the Engine. Runs in its own thread
//	and passes all Data into the engine
//## Category: engine%39F4C4E2005F
//## Subsystem: engine%39F51CB901B8
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3CB616C100B7;StdMidiIn { -> F}
//## Uses: <unnamed>%3CB61A9B010F;hal_include::Scheduler { -> F}
//## Uses: <unnamed>%3D827E5B037D;NVRAMStore { -> F}
//## Uses: <unnamed>%3F64EE260050;DigitalIn { -> F}
//## Uses: <unnamed>%3F64EE290130;AnalogIn { -> F}

class EngineDataInput : public MidiInputSync  //## Inherits: <unnamed>%3CB613D80142
{
  //## begin EngineDataInput%3CB613C5000E.initialDeclarations preserve=yes
  //## end EngineDataInput%3CB613C5000E.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: EngineDataInput%1018564229
      EngineDataInput (unsigned queue_size = 1024);

    //## Destructor (generated)
      ~EngineDataInput();


    //## Other Operations (specified)
      //## Operation: processMidiInput%1018564230
      void processMidiInput ();

      //## Operation: processMidiByte%1018564231
      bool processMidiByte (unsigned char data);

      //## Operation: AddAnalogueVal%1096227731
      void AddAnalogueVal (unsigned channel, unsigned value);

      //## Operation: AddDigitalVal%1096227732
      void AddDigitalVal (unsigned channel, bool value);

      //## Operation: processData%1096227734
      void processData (IOData iodata);

    // Additional Public Declarations
      //## begin EngineDataInput%3CB613C5000E.public preserve=yes
      //## end EngineDataInput%3CB613C5000E.public

  protected:
    // Additional Protected Declarations
      //## begin EngineDataInput%3CB613C5000E.protected preserve=yes
      //## end EngineDataInput%3CB613C5000E.protected

  private:
    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: _midi_bytes_remaining%3CB619750239
      //	The Number Of Midi Bytes required to finish the message
      const int get__midi_bytes_remaining () const;
      void set__midi_bytes_remaining (int value);

    // Additional Private Declarations
      //## begin EngineDataInput%3CB613C5000E.private preserve=yes
      //## end EngineDataInput%3CB613C5000E.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _in_sysex%3CB6194D003D
      //	Flag Indicating that we are in a sysex message
      //## begin EngineDataInput::_in_sysex%3CB6194D003D.attr preserve=no  private: bool {U} false
      bool _in_sysex;
      //## end EngineDataInput::_in_sysex%3CB6194D003D.attr

      //## begin EngineDataInput::_midi_bytes_remaining%3CB619750239.attr preserve=no  private: int {U} 0
      int _midi_bytes_remaining;
      //## end EngineDataInput::_midi_bytes_remaining%3CB619750239.attr

    // Data Members for Associations

      //## Association: engine::<unnamed>%3CB618EB0212
      //## Role: EngineDataInput::_current_message%3CB618EC00CA
      //## begin EngineDataInput::_current_message%3CB618EC00CA.role preserve=no  public: MidiData { -> 1VFHN}
      MidiData _current_message;
      //## end EngineDataInput::_current_message%3CB618EC00CA.role

      //## Association: engine::<unnamed>%3CF1B0A10240
      //## Role: EngineDataInput::_sysexDriver%3CF1B0A103D1
      //## begin EngineDataInput::_sysexDriver%3CF1B0A103D1.role preserve=no  public: SysexDriver { -> 1RFHN}
      SysexDriver *_sysexDriver;
      //## end EngineDataInput::_sysexDriver%3CF1B0A103D1.role

    // Additional Implementation Declarations
      //## begin EngineDataInput%3CB613C5000E.implementation preserve=yes
      //## end EngineDataInput%3CB613C5000E.implementation

};

//## begin EngineDataInput%3CB613C5000E.postscript preserve=yes
//## end EngineDataInput%3CB613C5000E.postscript

// Class EngineDataInput 

//## Get and Set Operations for Class Attributes (inline)

inline const int EngineDataInput::get__midi_bytes_remaining () const
{
  //## begin EngineDataInput::get__midi_bytes_remaining%3CB619750239.get preserve=no
  return _midi_bytes_remaining;
  //## end EngineDataInput::get__midi_bytes_remaining%3CB619750239.get
}

inline void EngineDataInput::set__midi_bytes_remaining (int value)
{
  //## begin EngineDataInput::set__midi_bytes_remaining%3CB619750239.set preserve=no
  _midi_bytes_remaining = value;
  //## end EngineDataInput::set__midi_bytes_remaining%3CB619750239.set
}

//## begin module%3CB613C5000E.epilog preserve=yes
//## end module%3CB613C5000E.epilog


#endif
