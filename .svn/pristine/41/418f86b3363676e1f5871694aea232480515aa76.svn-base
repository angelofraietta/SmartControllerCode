//## begin module%3CE1AB7B0165.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CE1AB7B0165.cm

//## begin module%3CE1AB7B0165.cp preserve=no
//	Angelo Fraietta
//## end module%3CE1AB7B0165.cp

//## Module: FileQuestion%3CE1AB7B0165; Pseudo Package specification
//## Subsystem: engineinterface%3A9C858C00CB
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\filequestion.h

#ifndef filequestion_h
#define filequestion_h 1

//## begin module%3CE1AB7B0165.additionalIncludes preserve=no
//## end module%3CE1AB7B0165.additionalIncludes

//## begin module%3CE1AB7B0165.includes preserve=yes
//## end module%3CE1AB7B0165.includes

// InterfaceTypes
#include "interfacetypes.h"

class SMUtility;
class PresentationQuestion;
class PresentationAnswer;
class FileAnswer;

//## begin module%3CE1AB7B0165.additionalDeclarations preserve=yes
//## end module%3CE1AB7B0165.additionalDeclarations


//## begin FileQuestion%3CE1AB7B0165.preface preserve=yes
//## end FileQuestion%3CE1AB7B0165.preface

//## Class: FileQuestion%3CE1AB7B0165; Class Utility
//## Category: EngineInterface::Question%3AA7F96B037A
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: calls%3CE1AC6C0393;PresentationQuestion { -> F}
//## Uses: <unnamed>%3CE1B1850227;KeyBaseType { -> }
//## Uses: <unnamed>%3CE1B2E800B5;SMUtility { -> F}
//## Uses: <unnamed>%3CE1B30A0077;FileAnswer { -> F}
//## Uses: <unnamed>%3CE1B32C036F;PresentationAnswer { -> F}

class FileQuestion 
{
  //## begin FileQuestion%3CE1AB7B0165.initialDeclarations preserve=yes
  //## end FileQuestion%3CE1AB7B0165.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: OpenFileForWrite%1021420318
      static bool OpenFileForWrite (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      unsigned key, 	// The key that the file opened will be access with
      const char* filename);

      //## Operation: OpenFileForRead%1021420319
      static unsigned OpenFileForRead (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      unsigned key, 	// The key that the file opened will be access with
      const char* filename);

      //## Operation: WriteBytes%1021420320
      static unsigned WriteBytes (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      unsigned key, 	// File pointer
      unsigned block_num, unsigned num_bytes, const BYTE* data_bytes);

      //## Operation: ReadBytes%1021420321
      static unsigned ReadBytes (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      unsigned key, 	// The key that the file opened will be access with
      BYTE* data_bytes, unsigned bytes_to_read);

      //## Operation: CloseFile%1021420322
      static unsigned CloseFile (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      unsigned key	// The key that the file opened will be access with
      );

      //## Operation: SaveNVRAM%1032126401
      static unsigned SaveNVRAM (PresentationQuestion* pQuestion	// Pointer to the Presentation Question used to get the
      	// answer
      );

      //## Operation: EraseNVRAM%1032171149
      static unsigned EraseNVRAM (PresentationQuestion* pQuestion	// Pointer to the Presentation Question used to get the
      	// answer
      );

      //## Operation: SaveFileToDisk%1051589362
      static void SaveFileToDisk (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      unsigned long crc, 	// Will only perform if the crc of target file matches
      	// this one
      const char* filename);

    // Additional Public Declarations
      //## begin FileQuestion%3CE1AB7B0165.public preserve=yes
      //## end FileQuestion%3CE1AB7B0165.public

  protected:
    // Additional Protected Declarations
      //## begin FileQuestion%3CE1AB7B0165.protected preserve=yes
      //## end FileQuestion%3CE1AB7B0165.protected

  private:
    // Additional Private Declarations
      //## begin FileQuestion%3CE1AB7B0165.private preserve=yes
      //## end FileQuestion%3CE1AB7B0165.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin FileQuestion%3CE1AB7B0165.implementation preserve=yes
      //## end FileQuestion%3CE1AB7B0165.implementation

};

//## begin FileQuestion%3CE1AB7B0165.postscript preserve=yes
//## end FileQuestion%3CE1AB7B0165.postscript

// Class Utility FileQuestion 

//## begin module%3CE1AB7B0165.epilog preserve=yes
//## end module%3CE1AB7B0165.epilog


#endif
