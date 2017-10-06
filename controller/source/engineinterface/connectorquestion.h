//## begin module%3ADF40B8007B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ADF40B8007B.cm

//## begin module%3ADF40B8007B.cp preserve=no
//	Angelo Fraietta
//## end module%3ADF40B8007B.cp

//## Module: ConnectorQuestion%3ADF40B8007B; Package specification
//	Declaraton for ConnectorQuestion whcih is exposed to the
//	Patch editor
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\connectorquestion.h

#ifndef connectorquestion_h
#define connectorquestion_h 1

//## begin module%3ADF40B8007B.additionalIncludes preserve=no
//## end module%3ADF40B8007B.additionalIncludes

//## begin module%3ADF40B8007B.includes preserve=yes
//## end module%3ADF40B8007B.includes

// InterfaceTypes
#include "interfacetypes.h"

class PresentationQuestion;
class ConnectorAnswer;

//## begin module%3ADF40B8007B.declarations preserve=no
//## end module%3ADF40B8007B.declarations

//## begin module%3ADF40B8007B.additionalDeclarations preserve=yes
//## end module%3ADF40B8007B.additionalDeclarations


//## begin ConnectorQuestion%3A9AC6B103AE.preface preserve=yes
//## end ConnectorQuestion%3A9AC6B103AE.preface

//## Class: ConnectorQuestion%3A9AC6B103AE; Class Utility
//	Assembles Connector questions and sends them to the
//	Engine for an answer
//## Category: EngineInterface::Question%3AA7F96B037A
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: calls%3AC3D0AE03B9;PresentationQuestion { -> F}
//## Uses: <unnamed>%3ADF447F004A;ConnectorAnswer { -> F}

class ConnectorQuestion 
{
  //## begin ConnectorQuestion%3A9AC6B103AE.initialDeclarations preserve=yes
  //## end ConnectorQuestion%3A9AC6B103AE.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: IsValid%767826064; C++
      static bool IsValid (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_CONNECTOR dwpCon);

      //## Operation: Create%777073519; C++
      static P_CONNECTOR Create (PresentationQuestion* pQuestion	// Pointer to the Presentation Question used to get the
      	// answer
      );

      //## Operation: Delete%1310936690; C++
      static void Delete (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_CONNECTOR dwpCon);

      //## Operation: SetOutletNum%-698908714; C++
      static void SetOutletNum (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_CONNECTOR dwpCon, unsigned int wSocketNum);

      //## Operation: SetOutletBase%-1335169627; C++
      static void SetOutletBase (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_CONNECTOR dwpCon, P_BASESHELL dwpShell);

      //## Operation: SetInletNum%-2101368277; C++
      static void SetInletNum (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_CONNECTOR dwpCon, unsigned int wSocketNum);

      //## Operation: SetInletBase%251329370; C++
      static void SetInletBase (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_CONNECTOR dwpCon, P_BASESHELL dwpShell);

      //## Operation: MakeConnection%-1151122548; C++
      static bool MakeConnection (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_CONNECTOR dwpCon);

      //## Operation: GetOutletNum%2017325574; C++
      static unsigned GetOutletNum (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_CONNECTOR dwpCon);

      //## Operation: GetOutletIndex%-456492498; C++
      static unsigned GetOutletIndex (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_CONNECTOR dwpCon);

      //## Operation: GetInletNum%-1763345739; C++
      static unsigned GetInletNum (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_CONNECTOR dwpCon);

      //## Operation: GetOutletBase%-166014066; C++
      static P_BASESHELL GetOutletBase (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_CONNECTOR dwpCon);

      //## Operation: GetInletBase%-959579559; C++
      static P_BASESHELL GetInletBase (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_CONNECTOR dwpCon);

    // Additional Public Declarations
      //## begin ConnectorQuestion%3A9AC6B103AE.public preserve=yes
      //## end ConnectorQuestion%3A9AC6B103AE.public

  protected:
    // Additional Protected Declarations
      //## begin ConnectorQuestion%3A9AC6B103AE.protected preserve=yes
      //## end ConnectorQuestion%3A9AC6B103AE.protected

  private:
    // Additional Private Declarations
      //## begin ConnectorQuestion%3A9AC6B103AE.private preserve=yes
      //## end ConnectorQuestion%3A9AC6B103AE.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ConnectorQuestion%3A9AC6B103AE.implementation preserve=yes
      //## end ConnectorQuestion%3A9AC6B103AE.implementation

};

//## begin ConnectorQuestion%3A9AC6B103AE.postscript preserve=yes
//## end ConnectorQuestion%3A9AC6B103AE.postscript

// Class Utility ConnectorQuestion 

//## begin module%3ADF40B8007B.epilog preserve=yes
//## end module%3ADF40B8007B.epilog


#endif
