//## begin module%3D823D930073.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D823D930073.cm

//## begin module%3D823D930073.cp preserve=no
//	Angelo Fraietta
//## end module%3D823D930073.cp

//## Module: FileDriver%3D823D930073; Pseudo Package specification
//## Subsystem: MidiDriver%3CB215CA01F1
//## Source file: c:\develop\MidicontrollerPatchEditor\mididriver\filedriver.h

#ifndef filedriver_h
#define filedriver_h 1

//## begin module%3D823D930073.additionalIncludes preserve=no
//## end module%3D823D930073.additionalIncludes

//## begin module%3D823D930073.includes preserve=yes
//## end module%3D823D930073.includes

//## begin module%3D823D930073.additionalDeclarations preserve=yes
#include <stdio.h>
//## end module%3D823D930073.additionalDeclarations


//## begin FileDriver%3D823D930073.preface preserve=yes
//## end FileDriver%3D823D930073.preface

//## Class: FileDriver%3D823D930073; Class Utility
//	Saves and retrieves data received into a data file.
//## Category: MidiDriver%3C588B4A020C
//## Subsystem: MidiDriver%3CB215CA01F1
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class FileDriver 
{
  //## begin FileDriver%3D823D930073.initialDeclarations preserve=yes
  //## end FileDriver%3D823D930073.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: WriteByte%1031946743
      //	Writes byte to File
      //## Postconditions:
      //	If File was not open (!_fp), file is opened write/append
      //	and set to the position of _pos
      //
      //	_pos is incremented after writing to file
      static bool WriteByte (char data, 	// The byte to be written
      int file_index	// The file index of the file. This determines which file
      	// is opened, whether it is immitating the internal or
      	// external EEPROM on IO board
      );

      //## Operation: ReadByte%1031946744
      //	Reads a byte from the open file
      //## Postconditions:
      //	If File was not open (!_fp), file is opened read and set
      //	to the position of _pos
      //
      //	_pos is incremented after writing to file
      static bool ReadByte (char* ret_byte, 	// Address of byte to be returned
      int file_index	// The file index of the file. This determines which file
      	// is opened, whether it is immitating the internal or
      	// external EEPROM on IO board
      );

      //## Operation: InitPosition%1031946745
      //	Closes the file
      static void InitPosition ();

      //## Operation: Flush%1031953703
      //	Flushes file output
      static void Flush ();

    // Additional Public Declarations
      //## begin FileDriver%3D823D930073.public preserve=yes
      //## end FileDriver%3D823D930073.public

  protected:
    // Additional Protected Declarations
      //## begin FileDriver%3D823D930073.protected preserve=yes
      //## end FileDriver%3D823D930073.protected

  private:

    //## Other Operations (specified)
      //## Operation: OpenForWrite%1031946747
      //	Opens File for write / append
      static bool OpenForWrite (int index	// The file index of the file we need to open
      );

      //## Operation: OpenForRead%1031946748
      //	Opens file for read
      static bool OpenForRead (int index	// The file index of the file we need to open
      );

    // Data Members for Class Attributes

      //## Attribute: _fp%3D823E340377
      //	File pointer for open file
      //## begin FileDriver::_fp%3D823E340377.attr preserve=no  private: static FILE* {UA} 0
      static FILE* _fp;
      //## end FileDriver::_fp%3D823E340377.attr

    // Additional Private Declarations
      //## begin FileDriver%3D823D930073.private preserve=yes
      //## end FileDriver%3D823D930073.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin FileDriver%3D823D930073.implementation preserve=yes
      //## end FileDriver%3D823D930073.implementation

};

//## begin FileDriver%3D823D930073.postscript preserve=yes
//## end FileDriver%3D823D930073.postscript

// Class Utility FileDriver 

//## begin module%3D823D930073.epilog preserve=yes
//## end module%3D823D930073.epilog


#endif
