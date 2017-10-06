//## begin module%3C5F3F20005A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C5F3F20005A.cm

//## begin module%3C5F3F20005A.cp preserve=no
//	Angelo Fraietta
//## end module%3C5F3F20005A.cp

//## Module: MidiUtilities%3C5F3F20005A; Pseudo Package specification
//## Subsystem: <Top Level>
//## Source file: c:\develop\MidiDriver\midiutilities.h

#ifndef midiutilities_h
#define midiutilities_h 1

//## begin module%3C5F3F20005A.additionalIncludes preserve=no
//## end module%3C5F3F20005A.additionalIncludes

//## begin module%3C5F3F20005A.includes preserve=yes
//## end module%3C5F3F20005A.includes

//## begin module%3C5F3F20005A.additionalDeclarations preserve=yes
#define NOTEOFF_MASK 0x80
#define NOTEON_MASK 0x90
#define POLYPRESS_MASK 0xA0
#define CONTROLLER_MASK 0xB0
#define PROGCHANGE_MASK 0xC0
#define CHANPRESS_MASK 0xD0
#define PITCHBEND_MASK 0xE0
#define SYSTEM_MASK    0xF0

#define SYSEX_BEGIN 0xF0
#define SYSEX_END 0xF7
#define SYSTEM_RESET 0xFF
#define SYSTEM_QUARTER_FRAME 0xF1
#define SYSTEM_SONG_POS 0xF2
#define SYSTEM_SONG_SELECT 0xF3

//## end module%3C5F3F20005A.additionalDeclarations


//## begin MidiUtilities%3C5F3F20005A.preface preserve=yes
//## end MidiUtilities%3C5F3F20005A.preface

//## Class: MidiUtilities%3C5F3F20005A; Class Utility
//## Category: MidiDevDriver%3C588B4A020C
//## Subsystem: <Top Level>
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class MidiUtilities 
{
  //## begin MidiUtilities%3C5F3F20005A.initialDeclarations preserve=yes
  //## end MidiUtilities%3C5F3F20005A.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: num_bytes%1012864651
      //	returns the number of bytes required given a particular
      //	status byte. Sysex returns -1
      static int num_bytes (char status);

    // Additional Public Declarations
      //## begin MidiUtilities%3C5F3F20005A.public preserve=yes
      //## end MidiUtilities%3C5F3F20005A.public

  protected:
    // Additional Protected Declarations
      //## begin MidiUtilities%3C5F3F20005A.protected preserve=yes
      //## end MidiUtilities%3C5F3F20005A.protected

  private:
    // Additional Private Declarations
      //## begin MidiUtilities%3C5F3F20005A.private preserve=yes
      //## end MidiUtilities%3C5F3F20005A.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin MidiUtilities%3C5F3F20005A.implementation preserve=yes
      //## end MidiUtilities%3C5F3F20005A.implementation

};

//## begin MidiUtilities%3C5F3F20005A.postscript preserve=yes
//## end MidiUtilities%3C5F3F20005A.postscript

// Class Utility MidiUtilities 


//## Other Operations (inline)
inline int MidiUtilities::num_bytes (char status)
{
  //## begin MidiUtilities::num_bytes%1012864651.body preserve=yes

	// we need to declare ints as switch statements require them
	int status_nibble;
  int num_bytes;
	int status_byte = status & 0xFF;

	status_nibble = status & 0xF0; // first nibble

	switch (status_nibble)
		{
		case NOTEOFF_MASK:
		case NOTEON_MASK:
		case POLYPRESS_MASK:
		case CONTROLLER_MASK:
		case PITCHBEND_MASK:
 			num_bytes = 3;
      break;

		case PROGCHANGE_MASK:
		case CHANPRESS_MASK:
			num_bytes = 2;
      break;

    case SYSTEM_MASK:
      switch (status_byte)
        {
        case SYSEX_BEGIN:
					num_bytes = -1;
          break;

        case SYSTEM_QUARTER_FRAME:
          num_bytes = 2;
          break;

        case SYSTEM_SONG_POS:
          num_bytes = 3;
          break;

        case SYSTEM_SONG_SELECT:
					num_bytes = 2;
          break;

        case SYSEX_END:
					num_bytes = -1;
          break;

        case SYSTEM_RESET:
					num_bytes = 1;
          break;

        default:
          // just ignore
          num_bytes = -1;
				}
        break;

		default:
       num_bytes = -1;
		}
    
    return	num_bytes;
  //## end MidiUtilities::num_bytes%1012864651.body
}

//## begin module%3C5F3F20005A.epilog preserve=yes
//## end module%3C5F3F20005A.epilog


#endif
