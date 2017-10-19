//## begin module%3ADF3D6E03D8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ADF3D6E03D8.cm

//## begin module%3ADF3D6E03D8.cp preserve=no
//	Angelo Fraietta
//## end module%3ADF3D6E03D8.cp

//## Module: PresentationQuestion%3ADF3D6E03D8; Package specification
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: d:\develop\smartcontroller\controller\source\engineinterface\presentationquestion.h

#ifndef presentationquestion_h
#define presentationquestion_h 1

//## begin module%3ADF3D6E03D8.additionalIncludes preserve=no
//## end module%3ADF3D6E03D8.additionalIncludes

//## begin module%3ADF3D6E03D8.includes preserve=yes
//## end module%3ADF3D6E03D8.includes


class SMUtility;
class SessionQuestion;

//## begin module%3ADF3D6E03D8.declarations preserve=no
//## end module%3ADF3D6E03D8.declarations

//## begin module%3ADF3D6E03D8.additionalDeclarations preserve=yes
//## end module%3ADF3D6E03D8.additionalDeclarations


//## begin PresentationQuestion%3AA806020126.preface preserve=yes
//## end PresentationQuestion%3AA806020126.preface

//## Class: PresentationQuestion%3AA806020126
//	The Application Layer interface into the Patch
//	Editor.This provides a single function with which all
//	querries from the Patch Editor are sent from and
//	responded to.
//## Category: EngineInterface::Question%3AA7F96B037A
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AC3D9D602F1;SMUtility { -> F}

class PresentationQuestion 
{
  //## begin PresentationQuestion%3AA806020126.initialDeclarations preserve=yes
  //## end PresentationQuestion%3AA806020126.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: PresentationQuestion%986448515
      PresentationQuestion (const char* name = NULL, 	// The name of the port to open
      DWORD port_speed = 0	// The speed at which to open the port
      );

    //## Destructor (generated)
      ~PresentationQuestion();


    //## Other Operations (specified)
      //## Operation: AskQuestion%985819689
      bool AskQuestion (unsigned target_class, const BYTE* question, 	// These are the parameters that make up the question.
      	// Each parameter is a Null terminated string.  The first
      	// parameter is the size of the queston buffer
      unsigned q_size, 	// The size of the question
      BYTE* ret_answer, 	// This is where the answer to the question will be placed.
      unsigned r_size	// Size of return buffer
      );

      //## Operation: open%985819690
      bool open (const char* name, 	// The name of the interface
      DWORD port_speed	// The speed at which to open the port
      );

      //## Operation: close%985819691
      void close ();

      //## Operation: IsOpen%1020316780
      bool IsOpen ();

      //## Operation: openfile%1022540279
      bool openfile (const char* filename);

      //## Operation: SetInterfaceAddress%1082670125
      bool SetInterfaceAddress (const char* address);

    // Additional Public Declarations
      //## begin PresentationQuestion%3AA806020126.public preserve=yes
      //## end PresentationQuestion%3AA806020126.public

  protected:
    // Additional Protected Declarations
      //## begin PresentationQuestion%3AA806020126.protected preserve=yes
      //## end PresentationQuestion%3AA806020126.protected

  private:
    // Additional Private Declarations
      //## begin PresentationQuestion%3AA806020126.private preserve=yes
      //## end PresentationQuestion%3AA806020126.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _sequence_number%3AEDE30D0271
      //	A number that increments every time a question is
      //	asked.  This determines that the answer matches the
      //	question asked
      //## begin PresentationQuestion::_sequence_number%3AEDE30D0271.attr preserve=no  private: BYTE {U} 0
      BYTE _sequence_number;
      //## end PresentationQuestion::_sequence_number%3AEDE30D0271.attr

      //## Attribute: _retries%3AEDE4F601DE
      //	defines the number of times to retry asking the question
      //## begin PresentationQuestion::_retries%3AEDE4F601DE.attr preserve=no  private: unsigned {U} 1
      unsigned _retries;
      //## end PresentationQuestion::_retries%3AEDE4F601DE.attr

      //## Attribute: _answer%3CFBFE090237
      //## begin PresentationQuestion::_answer%3CFBFE090237.attr preserve=no  private: BYTE[1024] {U} 
      BYTE _answer[1024];
      //## end PresentationQuestion::_answer%3CFBFE090237.attr

    // Data Members for Associations

      //## Association: EngineInterface::<unnamed>%3AC018520060
      //## Role: PresentationQuestion::snLayer%3AC018520331
      //## begin PresentationQuestion::snLayer%3AC018520331.role preserve=no  public: SessionQuestion { -> 1RFHN}
      SessionQuestion *snLayer;
      //## end PresentationQuestion::snLayer%3AC018520331.role

    // Additional Implementation Declarations
      //## begin PresentationQuestion%3AA806020126.implementation preserve=yes
      //## end PresentationQuestion%3AA806020126.implementation

};

//## begin PresentationQuestion%3AA806020126.postscript preserve=yes
//## end PresentationQuestion%3AA806020126.postscript

// Class PresentationQuestion 

//## begin module%3ADF3D6E03D8.epilog preserve=yes
PresentationQuestion* GetSimulator ();
unsigned GetSelectedEngine ();
void SetCurrentEngine (unsigned new_engine);
void InitialisePresentation();
PresentationQuestion* getPresentation (unsigned key);
unsigned addPresentationQuestion(PresentationQuestion * pQuestion);
void erasePresentationQuestion(unsigned key);
PresentationQuestion* getPresentation (unsigned key);
//## end module%3ADF3D6E03D8.epilog


#endif
