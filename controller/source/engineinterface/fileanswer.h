//## begin module%3CE19DE0008B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CE19DE0008B.cm

//## begin module%3CE19DE0008B.cp preserve=no
//	Angelo Fraietta
//## end module%3CE19DE0008B.cp

//## Module: FileAnswer%3CE19DE0008B; Pseudo Package specification
//## Subsystem: engineinterface%3A9C858C00CB
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\fileanswer.h

#ifndef fileanswer_h
#define fileanswer_h 1

//## begin module%3CE19DE0008B.additionalIncludes preserve=no
//## end module%3CE19DE0008B.additionalIncludes

//## begin module%3CE19DE0008B.includes preserve=yes
//## end module%3CE19DE0008B.includes


class KeyBaseType;

//## begin module%3CE19DE0008B.additionalDeclarations preserve=yes
//## end module%3CE19DE0008B.additionalDeclarations


//## begin FileAnswer%3CE19DE0008B.preface preserve=yes
//## end FileAnswer%3CE19DE0008B.preface

//## Class: FileAnswer%3CE19DE0008B; Class Utility
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3CE1A6DD00EE;SMUtility { -> }
//## Uses: <unnamed>%3CE1A758011D;KeyBaseType { -> F}

class FileAnswer 
{
  //## begin FileAnswer%3CE19DE0008B.initialDeclarations preserve=yes
  //## end FileAnswer%3CE19DE0008B.initialDeclarations

  public:
    //## begin FileAnswer::pFuncType%3CE19E6F0195.preface preserve=yes
    //## end FileAnswer::pFuncType%3CE19E6F0195.preface

    //## Class: pFuncType%3CE19E6F0195; Class Utility
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef unsigned (*pfunctype) (const BYTE*, BYTE*, unsigned);
    //## begin FileAnswer::pFuncType%3CE19E6F0195.postscript preserve=yes
    //## end FileAnswer::pFuncType%3CE19E6F0195.postscript

    //## begin FileAnswer::TargetFunc%3CE19EB002D9.preface preserve=yes
    //## end FileAnswer::TargetFunc%3CE19EB002D9.preface

    //## Class: TargetFunc%3CE19EB002D9; Class Utility
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef enum {eOpenFileForWrite, eOpenFileForRead, eWriteBytes, eReadBytes, eCloseFile, eSaveNVRAM, eEraseNVRAM, eSaveFileToDisk, eMaxFuncIndex} TargetFunc;

    //## begin FileAnswer::TargetFunc%3CE19EB002D9.postscript preserve=yes
    //## end FileAnswer::TargetFunc%3CE19EB002D9.postscript


    //## Other Operations (specified)
      //## Operation: PerformOperation%1021420312
      static unsigned PerformOperation (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SetDefaultDirectory%1022123229
      static void SetDefaultDirectory (const char* dir_name);

      //## Operation: GetDefaultDirName%1022123230
      static const char* GetDefaultDirName ();

  public:
    // Additional Public Declarations
      //## begin FileAnswer%3CE19DE0008B.public preserve=yes
      //## end FileAnswer%3CE19DE0008B.public

  protected:
    // Additional Protected Declarations
      //## begin FileAnswer%3CE19DE0008B.protected preserve=yes
      //## end FileAnswer%3CE19DE0008B.protected

  private:

    //## Other Operations (specified)
      //## Operation: OpenFileForWrite%1021420313
      static unsigned OpenFileForWrite (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: OpenFileForRead%1021420314
      static unsigned OpenFileForRead (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: WriteBytes%1021420315
      static unsigned WriteBytes (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: ReadBytes%1021420316
      static unsigned ReadBytes (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: CloseFile%1021420317
      static unsigned CloseFile (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SaveNVRAM%1032126400
      static unsigned SaveNVRAM (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: EraseNVRAM%1032171148
      static unsigned EraseNVRAM (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SaveFileToDisk%1051589363
      static unsigned SaveFileToDisk (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

    // Additional Private Declarations
      //## begin FileAnswer%3CE19DE0008B.private preserve=yes
      //## end FileAnswer%3CE19DE0008B.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: pFunc%3CE1A195039C
      //	Static array of member functions
      //## begin FileAnswer::pFunc%3CE1A195039C.attr preserve=no  private: static FileAnswer::pfunctype [eMaxFuncIndex] {U} {OpenFileForWrite, OpenFileForRead, WriteBytes, ReadBytes, CloseFile, SaveNVRAM, EraseNVRAM, SaveFileToDisk}
      static FileAnswer::pfunctype  pFunc[eMaxFuncIndex];
      //## end FileAnswer::pFunc%3CE1A195039C.attr

      //## Attribute: default_directory%3CEC5C40008F
      //	This is the default directory for patches to be loaded
      //	from.
      //## begin FileAnswer::default_directory%3CEC5C40008F.attr preserve=no  private: static string {U} 
      static string default_directory;
      //## end FileAnswer::default_directory%3CEC5C40008F.attr

    // Additional Implementation Declarations
      //## begin FileAnswer%3CE19DE0008B.implementation preserve=yes
      //## end FileAnswer%3CE19DE0008B.implementation

};

//## begin FileAnswer%3CE19DE0008B.postscript preserve=yes
//## end FileAnswer%3CE19DE0008B.postscript

// Class Utility FileAnswer 

//## begin module%3CE19DE0008B.epilog preserve=yes
//## end module%3CE19DE0008B.epilog


#endif
