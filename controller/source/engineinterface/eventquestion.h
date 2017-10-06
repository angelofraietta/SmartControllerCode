//## begin module%3ADF42A902ED.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ADF42A902ED.cm

//## begin module%3ADF42A902ED.cp preserve=no
//	Angelo Fraietta
//## end module%3ADF42A902ED.cp

//## Module: EventQuestion%3ADF42A902ED; Package specification
//	Declaration for EventQuestion, whcih is exposed to the
//	Patch Editor
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\eventquestion.h

#ifndef eventquestion_h
#define eventquestion_h 1

//## begin module%3ADF42A902ED.additionalIncludes preserve=no
//## end module%3ADF42A902ED.additionalIncludes

//## begin module%3ADF42A902ED.includes preserve=yes
//## end module%3ADF42A902ED.includes


class PresentationQuestion;

//## begin module%3ADF42A902ED.declarations preserve=no
//## end module%3ADF42A902ED.declarations

//## begin module%3ADF42A902ED.additionalDeclarations preserve=yes
//## end module%3ADF42A902ED.additionalDeclarations


//## begin EventQuestion%3AA808AA012E.preface preserve=yes
//## end EventQuestion%3AA808AA012E.preface

//## Class: EventQuestion%3AA808AA012E; Class Utility
//	This class asks for event questions, such as trigger
//	messages, display messages, error messages.
//## Category: EngineInterface::Question%3AA7F96B037A
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: calls%3AC3D0C403A6;PresentationQuestion { -> F}

class EventQuestion 
{
  //## begin EventQuestion%3AA808AA012E.initialDeclarations preserve=yes
  //## end EventQuestion%3AA808AA012E.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: EventWaiting%985819709
      static void EventWaiting ();

    // Additional Public Declarations
      //## begin EventQuestion%3AA808AA012E.public preserve=yes
      //## end EventQuestion%3AA808AA012E.public

  protected:
    // Additional Protected Declarations
      //## begin EventQuestion%3AA808AA012E.protected preserve=yes
      //## end EventQuestion%3AA808AA012E.protected

  private:
    // Additional Private Declarations
      //## begin EventQuestion%3AA808AA012E.private preserve=yes
      //## end EventQuestion%3AA808AA012E.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin EventQuestion%3AA808AA012E.implementation preserve=yes
      //## end EventQuestion%3AA808AA012E.implementation

};

//## begin EventQuestion%3AA808AA012E.postscript preserve=yes
//## end EventQuestion%3AA808AA012E.postscript

// Class Utility EventQuestion 

//## begin module%3ADF42A902ED.epilog preserve=yes
//## end module%3ADF42A902ED.epilog


#endif
