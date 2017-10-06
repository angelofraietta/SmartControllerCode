//## begin module%3AC3CD1A005E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AC3CD1A005E.cm

//## begin module%3AC3CD1A005E.cp preserve=no
//	Angelo Fraietta
//## end module%3AC3CD1A005E.cp

//## Module: PresentationAnswer%3AC3CD1A005E; Package specification
//	Header for Application Answer
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\presentationanswer.h

#ifndef presentationanswer_h
#define presentationanswer_h 1

//## begin module%3AC3CD1A005E.additionalIncludes preserve=no
//## end module%3AC3CD1A005E.additionalIncludes

//## begin module%3AC3CD1A005E.includes preserve=yes
//## end module%3AC3CD1A005E.includes

// EventAnswer
#include "eventanswer.h"

class BaseShellAnswer;
class PatchAnswer;
class IdentityAnswer;
class ConnectorAnswer;
class ViewAnswer;
class FileAnswer;

//## begin module%3AC3CD1A005E.declarations preserve=no
//## end module%3AC3CD1A005E.declarations

//## begin module%3AC3CD1A005E.additionalDeclarations preserve=yes
//## end module%3AC3CD1A005E.additionalDeclarations


//## begin PresentationAnswer%3AA802130023.preface preserve=yes
//## end PresentationAnswer%3AA802130023.preface

//## Class: PresentationAnswer%3AA802130023
//	The Application Layer interface into the Engine. This
//	provides a single function with which all querries to
//	the Engine are sent to and responded from.
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: calls%3AC3CF0E01EE;ConnectorAnswer { -> F}
//## Uses: calls%3AC3CF120103;IdentityAnswer { -> F}
//## Uses: calls%3AC3CF1A01E1;PatchAnswer { -> F}
//## Uses: calls%3AC3CF1C02FC;BaseShellAnswer { -> F}
//## Uses: calls%3AC3CF1F0198;EventAnswer { -> F}
//## Uses: calls%3CE19E170261;FileAnswer { -> F}
//## Uses: calls%3D34A34C0224;ViewAnswer { -> F}

class PresentationAnswer 
{
  //## begin PresentationAnswer%3AA802130023.initialDeclarations preserve=yes
  //## end PresentationAnswer%3AA802130023.initialDeclarations

  public:
    //## begin PresentationAnswer::pfunctype%3AC3C9490302.preface preserve=yes
    //## end PresentationAnswer::pfunctype%3AC3C9490302.preface

    //## Class: pfunctype%3AC3C9490302
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef unsigned (*pfunctype) (const BYTE*, BYTE*, unsigned);
    //## begin PresentationAnswer::pfunctype%3AC3C9490302.postscript preserve=yes
    //## end PresentationAnswer::pfunctype%3AC3C9490302.postscript

    //## begin PresentationAnswer::TargetClass%3ADF3B1901F9.preface preserve=yes
    //## end PresentationAnswer::TargetClass%3ADF3B1901F9.preface

    //## Class: TargetClass%3ADF3B1901F9
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef enum {eIdentity, eBaseShell, eConnector, ePatch, eFile,  ePatchView, eEvent, eMaxclass} TargetClass;

    //## begin PresentationAnswer::TargetClass%3ADF3B1901F9.postscript preserve=yes
    //## end PresentationAnswer::TargetClass%3ADF3B1901F9.postscript

    //## Constructors (generated)
      PresentationAnswer();

    //## Destructor (generated)
      ~PresentationAnswer();


    //## Other Operations (specified)
      //## Operation: GetAnswer%985819695
      unsigned GetAnswer (const BYTE* question, 	// These are the parameters that make up the question.
      	// Each parameter is a Null terminated string.  The first
      	// parameter is the size of the queston buffer
      BYTE** ret_answer, 	// This is where the pointer to answer to the question
      	// will be placed. The address is owned by this class
      unsigned r_size	// the max size of application return buffer
      );

      //## Operation: ReturnBytes%988676983
      static unsigned ReturnBytes ();

      //## Operation: GetAnswer%1020660146
      unsigned GetAnswer (const BYTE* question, 	// These are the parameters that make up the question.
      	// Each parameter is a Null terminated string.  The first
      	// parameter is the size of the queston buffer
      BYTE* ret_answer, 	// Copies the Data into ret_anser
      unsigned r_size	// the max size of application return buffer
      );

  public:
    // Additional Public Declarations
      //## begin PresentationAnswer%3AA802130023.public preserve=yes
      //## end PresentationAnswer%3AA802130023.public

  protected:
    // Additional Protected Declarations
      //## begin PresentationAnswer%3AA802130023.protected preserve=yes
      //## end PresentationAnswer%3AA802130023.protected

  private:
    // Additional Private Declarations
      //## begin PresentationAnswer%3AA802130023.private preserve=yes
      //## end PresentationAnswer%3AA802130023.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: pFunc%3AC3C9B802A8
      //	Static array of member functions. The NULL function
      //	defines that a function must not be called via this array
      //## begin PresentationAnswer::pFunc%3AC3C9B802A8.attr preserve=no  private: static PresentationAnswer::pfunctype [] {U} {IdentityAnswer::PerformOperation, BaseShellAnswer::PerformOperation, ConnectorAnswer::PerformOperation, PatchAnswer::PerformOperation, FileAnswer::PerformOperation, ViewAnswer::PerformOperation, NULL}
      static PresentationAnswer::pfunctype  pFunc[];
      //## end PresentationAnswer::pFunc%3AC3C9B802A8.attr

      //## Attribute: _answer_buf%3CD609DE0229
      //## begin PresentationAnswer::_answer_buf%3CD609DE0229.attr preserve=no  private: BYTE* {U} new BYTE[1024]
      BYTE* _answer_buf;
      //## end PresentationAnswer::_answer_buf%3CD609DE0229.attr

    // Data Members for Associations

      //## Association: EngineInterface::<unnamed>%3AEE4CF90057
      //## Role: PresentationAnswer::_event_container%3AEE4CF902F6
      //## begin PresentationAnswer::_event_container%3AEE4CF902F6.role preserve=no  public: EventAnswer { -> 1VHN}
      EventAnswer _event_container;
      //## end PresentationAnswer::_event_container%3AEE4CF902F6.role

    // Additional Implementation Declarations
      //## begin PresentationAnswer%3AA802130023.implementation preserve=yes
      //## end PresentationAnswer%3AA802130023.implementation

};

//## begin PresentationAnswer%3AA802130023.postscript preserve=yes
//## end PresentationAnswer%3AA802130023.postscript

// Class PresentationAnswer 


//## Other Operations (inline)
//## Operation: ReturnBytes%988676983
//	Returns the number of bytes for the Presentation
//	houskeeping
inline unsigned PresentationAnswer::ReturnBytes ()
{
  return sizeof (BYTE) // sequence number
  + sizeof (BYTE) // we need to add one for event flag
  + sizeof (short); // number of bytes returned


  //## begin PresentationAnswer::ReturnBytes%988676983.body preserve=yes
  //## end PresentationAnswer::ReturnBytes%988676983.body
}

//## begin module%3AC3CD1A005E.epilog preserve=yes
//## end module%3AC3CD1A005E.epilog


#endif
