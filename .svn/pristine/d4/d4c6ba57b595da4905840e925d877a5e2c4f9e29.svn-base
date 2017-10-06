//## begin module%3CF2B905003C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CF2B905003C.cm

//## begin module%3CF2B905003C.cp preserve=no
//	Angelo Fraietta
//## end module%3CF2B905003C.cp

//## Module: SysexFileQuestion%3CF2B905003C; Pseudo Package specification
//## Subsystem: engineinterface%3A9C858C00CB
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\sysexfilequestion.h

#ifndef sysexfilequestion_h
#define sysexfilequestion_h 1

//## begin module%3CF2B905003C.additionalIncludes preserve=no
//## end module%3CF2B905003C.additionalIncludes

//## begin module%3CF2B905003C.includes preserve=yes
#include <stdio.h>
#include "linkprotocol.h"
//## end module%3CF2B905003C.includes

// SessionInterface
#include "sessioninterface.h"


//## begin module%3CF2B905003C.additionalDeclarations preserve=yes
//## end module%3CF2B905003C.additionalDeclarations


//## begin SysexFileQuestion%3CF2B905003C.preface preserve=yes
//## end SysexFileQuestion%3CF2B905003C.preface

//## Class: SysexFileQuestion%3CF2B905003C
//	Writes the Questions To a SysexData file
//## Category: EngineInterface::Question%3AA7F96B037A
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class SysexFileQuestion : public SessionQuestion  //## Inherits: <unnamed>%3CF2B95A034B
{
  //## begin SysexFileQuestion%3CF2B905003C.initialDeclarations preserve=yes
  //## end SysexFileQuestion%3CF2B905003C.initialDeclarations

  public:
    //## Constructors (generated)
      SysexFileQuestion();

    //## Destructor (generated)
      ~SysexFileQuestion();


    //## Other Operations (specified)
      //## Operation: AskQuestion%1022540280
      bool AskQuestion (const BYTE* question, 	// These are the parameters that make up the question.
      	// Each parameter is a Null terminated string.  The first
      	// parameter is the size of the queston buffer
      unsigned q_size, 	// Size of the question
      BYTE* ret_answer, 	// This is where the answer to the question will be placed.
      unsigned r_size, 	// Maximum allowed size of answer
      unsigned timeout = 2000	// The amount of toime to wait
      );

      //## Operation: open%1022540281
      bool open (const char* file_name	// Name of the file to be generated
      );

      //## Operation: close%1022540282
      void close ();

    // Additional Public Declarations
      //## begin SysexFileQuestion%3CF2B905003C.public preserve=yes
      //## end SysexFileQuestion%3CF2B905003C.public

  protected:
    // Additional Protected Declarations
      //## begin SysexFileQuestion%3CF2B905003C.protected preserve=yes
      //## end SysexFileQuestion%3CF2B905003C.protected

  private:
    // Additional Private Declarations
      //## begin SysexFileQuestion%3CF2B905003C.private preserve=yes
      //## end SysexFileQuestion%3CF2B905003C.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _fp%3CF2B9D001BA
      //	File Pointer
      //## begin SysexFileQuestion::_fp%3CF2B9D001BA.attr preserve=no  private: FILE* {U} NULL
      FILE* _fp;
      //## end SysexFileQuestion::_fp%3CF2B9D001BA.attr

    // Data Members for Associations

      //## Association: EngineInterface::Question::<unnamed>%3DFD66850399
      //## Role: SysexFileQuestion::_encoder%3DFD668600E9
      //## begin SysexFileQuestion::_encoder%3DFD668600E9.role preserve=no  public: LinkProtocol { -> 1VFHN}
      LinkProtocol _encoder;
      //## end SysexFileQuestion::_encoder%3DFD668600E9.role

    // Additional Implementation Declarations
      //## begin SysexFileQuestion%3CF2B905003C.implementation preserve=yes
      //## end SysexFileQuestion%3CF2B905003C.implementation

};

//## begin SysexFileQuestion%3CF2B905003C.postscript preserve=yes
//## end SysexFileQuestion%3CF2B905003C.postscript

// Class SysexFileQuestion 

//## begin module%3CF2B905003C.epilog preserve=yes
//## end module%3CF2B905003C.epilog


#endif
