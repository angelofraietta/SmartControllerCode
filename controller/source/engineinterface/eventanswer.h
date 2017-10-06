//## begin module%3AC3D27D01A2.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AC3D27D01A2.cm

//## begin module%3AC3D27D01A2.cp preserve=no
//	Angelo Fraietta
//## end module%3AC3D27D01A2.cp

//## Module: EventAnswer%3AC3D27D01A2; Package specification
//	Interface for Event answer
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\eventanswer.h

#ifndef eventanswer_h
#define eventanswer_h 1

//## begin module%3AC3D27D01A2.additionalIncludes preserve=no
//## end module%3AC3D27D01A2.additionalIncludes

//## begin module%3AC3D27D01A2.includes preserve=yes
//## end module%3AC3D27D01A2.includes

//## begin module%3AC3D27D01A2.declarations preserve=no
//## end module%3AC3D27D01A2.declarations

//## begin module%3AC3D27D01A2.additionalDeclarations preserve=yes
//## end module%3AC3D27D01A2.additionalDeclarations


//## begin EventAnswer%3AA808F802AC.preface preserve=yes
//## end EventAnswer%3AA808F802AC.preface

//## Class: EventAnswer%3AA808F802AC
//	This class answers  event questions, such as trigger
//	messages, display messages, error messages.  This class
//	stores the messages passed to it fom the WindowMessage
//	Queue until it is questioned from the Patch Editor.
//	Each instance of this class must be registered with the
//	WindowMessageQueue in order to receive messages from it.
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class EventAnswer 
{
  //## begin EventAnswer%3AA808F802AC.initialDeclarations preserve=yes
  //## end EventAnswer%3AA808F802AC.initialDeclarations

  public:
    //## Constructors (generated)
      EventAnswer();

      EventAnswer(const EventAnswer &right);

    //## Destructor (generated)
      ~EventAnswer();

    //## Assignment Operation (generated)
      const EventAnswer & operator=(const EventAnswer &right);

    //## Equality Operations (generated)
      int operator==(const EventAnswer &right) const;

      int operator!=(const EventAnswer &right) const;


    //## Other Operations (specified)
      //## Operation: eventReady%985819702
      static bool eventReady ();

      //## Operation: GetEvent%985819708
      unsigned GetEvent (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

    // Additional Public Declarations
      //## begin EventAnswer%3AA808F802AC.public preserve=yes
      //## end EventAnswer%3AA808F802AC.public

  protected:
    // Additional Protected Declarations
      //## begin EventAnswer%3AA808F802AC.protected preserve=yes
      //## end EventAnswer%3AA808F802AC.protected

  private:
    // Additional Private Declarations
      //## begin EventAnswer%3AA808F802AC.private preserve=yes
      //## end EventAnswer%3AA808F802AC.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin EventAnswer%3AA808F802AC.implementation preserve=yes
      //## end EventAnswer%3AA808F802AC.implementation

};

//## begin EventAnswer%3AA808F802AC.postscript preserve=yes
//## end EventAnswer%3AA808F802AC.postscript

// Class EventAnswer 

//## begin module%3AC3D27D01A2.epilog preserve=yes
//## end module%3AC3D27D01A2.epilog


#endif
