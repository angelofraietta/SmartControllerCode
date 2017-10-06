//## begin module%3ADF39F9029F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ADF39F9029F.cm

//## begin module%3ADF39F9029F.cp preserve=no
//	Angelo Fraietta
//## end module%3ADF39F9029F.cp

//## Module: BaseShellQuestion%3ADF39F9029F; Package specification
//	This is the declaration of the BaseShellQuestion
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\baseshellquestion.h

#ifndef baseshellquestion_h
#define baseshellquestion_h 1

//## begin module%3ADF39F9029F.additionalIncludes preserve=no
//## end module%3ADF39F9029F.additionalIncludes

//## begin module%3ADF39F9029F.includes preserve=yes
//## end module%3ADF39F9029F.includes

// InterfaceTypes
#include "interfacetypes.h"

class SMUtility;
class PresentationQuestion;
class BaseShellAnswer;

//## begin module%3ADF39F9029F.declarations preserve=no
//## end module%3ADF39F9029F.declarations

//## begin module%3ADF39F9029F.additionalDeclarations preserve=yes
//## end module%3ADF39F9029F.additionalDeclarations


//## begin BaseShellQuestion%3A9AC62001BA.preface preserve=yes
//## end BaseShellQuestion%3A9AC62001BA.preface

//## Class: BaseShellQuestion%3A9AC62001BA; Class Utility
//	Assembles BaseShell questions and sends them to the
//	Engine for an answer
//## Category: EngineInterface::Question%3AA7F96B037A
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: calls%3AC3D0CB022A;PresentationQuestion { -> F}
//## Uses: <unnamed>%3ACAB7EB0341;SMUtility { -> F}
//## Uses: <unnamed>%3ADF44500132;BaseShellAnswer { -> F}

class BaseShellQuestion 
{
  //## begin BaseShellQuestion%3A9AC62001BA.initialDeclarations preserve=yes
  //## end BaseShellQuestion%3A9AC62001BA.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: GetNumAttributes%986253860
      static unsigned GetNumAttributes (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL objKey	// The key associated with the Identity
      );

      //## Operation: GetAttributeName%986253861
      static void GetAttributeName (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL objKey, 	// The key associated with the Identity
      unsigned attribute_key, 	// The key associated with the attribute
      char* ret_value, 	// This has the attribute value returned as a null
      	// terminated string
      unsigned buf_len	// The length of the ret_value buffer
      );

      //## Operation: GetAttribute%986253853
      static bool GetAttribute (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL objKey, 	// The key associated with the Identity
      unsigned attribute_key, 	// The key associated with the attribute
      char* ret_value, 	// This has the attribute value returned as a null
      	// terminated string
      unsigned buf_len	// The length of the ret_value buffer
      );

      //## Operation: SetAttribute%986253854
      static bool SetAttribute (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL objKey, 	// The key associated with the Identity
      unsigned attribute_key, 	// The key associated with the attribute
      const char* new_value	// This has the attribute value returned as a null
      	// terminated string
      );

      //## Operation: GetNumResetAttributes%996206541
      static unsigned GetNumResetAttributes (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL objKey	// The key associated with the Identity
      );

      //## Operation: GetResetAttributeName%996206542
      static void GetResetAttributeName (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL objKey, 	// The key associated with the Identity
      unsigned attribute_key, 	// The key associated with the attribute
      char* ret_value, 	// This has the attribute value returned as a null
      	// terminated string
      unsigned buf_len	// The length of the ret_value buffer
      );

      //## Operation: GetResetAttribute%996206543
      static bool GetResetAttribute (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL objKey, 	// The key associated with the Identity
      unsigned attribute_key, 	// The key associated with the attribute
      char* ret_value, 	// This has the attribute value returned as a null
      	// terminated string
      unsigned buf_len	// The length of the ret_value buffer
      );

      //## Operation: SetResetAttribute%996206544
      static bool SetResetAttribute (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL objKey, 	// The key associated with the Identity
      unsigned attribute_key, 	// The key associated with the attribute
      const char* new_value	// This has the attribute value returned as a null
      	// terminated string
      );

      //## Operation: Reset%-626865097; C++
      static void Reset (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell);

      //## Operation: Send%-2018118597; C++
      static void Send (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell);

      //## Operation: Create%-589452350; C++
      static P_BASESHELL Create (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      const char* Type, P_PATCH pParent);

      //## Operation: GetNumInlets%1308397307; C++
      static unsigned GetNumInlets (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell);

      //## Operation: GetNumOutlets%-1922982991; C++
      static unsigned GetNumOutlets (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell);

      //## Operation: GetInletName%884347129; C++
      static void GetInletName (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell, unsigned int wSocketNum, char* Buf, unsigned buf_len	// The length of the buffer
      );

      //## Operation: GetOutletName%1385329752; C++
      static void GetOutletName (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell, unsigned int wSocketNum, char* Buf, unsigned buf_len	// The length of the buffer
      );

      //## Operation: GetNumInletConnectors%-1254667311; C++
      static unsigned GetNumInletConnectors (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell, unsigned int wSocketNum);

      //## Operation: GetNumOutletConnectors%563684372; C++
      static unsigned GetNumOutletConnectors (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell, unsigned int wSocketNum);

      //## Operation: CanConnectInlet%-704190606; C++
      static bool CanConnectInlet (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell, unsigned int wSocketNum, P_CONNECTOR dwpCon);

      //## Operation: CanConnectOutlet%890428262; C++
      static bool CanConnectOutlet (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell, unsigned int wSocketNum, P_CONNECTOR dwpCon);

      //## Operation: GetInletConnector%557037002; C++
      static P_CONNECTOR GetInletConnector (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell, unsigned int wSocketNum, unsigned int Index);

      //## Operation: GetOutletConnector%1073042389; C++
      static P_CONNECTOR GetOutletConnector (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell, unsigned int wSocketNum, unsigned int Index);

      //## Operation: FindInletConnectorIndex%-715723704; C++
      static unsigned FindInletConnectorIndex (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell, unsigned wSocketNum, P_CONNECTOR dwpCon);

      //## Operation: FindOutletConnectorIndex%-1415674172; C++
      static unsigned FindOutletConnectorIndex (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell, unsigned int wSocketNum, P_CONNECTOR dwpCon);

      //## Operation: SwapOutletConnector%251269562; C++
      static void SwapOutletConnector (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell, 	// The BaseShell key
      unsigned outlet_number, 	// The outlet number containg the connectors
      unsigned connector1_index, 	// The index of the first connector within the outlet
      unsigned connector2_index	// The index of the second connector within the outlet
      );

      //## Operation: GetNumObjectTypes%1048126423
      static unsigned GetNumObjectTypes (PresentationQuestion* pQuestion	// Pointer to the Presentation Question used to get the
      	// answer
      );

      //## Operation: GetObjectType%1048126424
      static void GetObjectType (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      unsigned index, 	// The key associated with the attribute
      char* ret_value, 	// This has the attribute value returned as a null
      	// terminated string
      unsigned buf_len	// The length of the ret_value buffer
      );

      //## Operation: CanHaveChildren%1048130624; C++
      static bool CanHaveChildren (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell	// The BaseShell key
      );

      //## Operation: CanChangeSize%1048130625; C++
      static bool CanChangeSize (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell	// The BaseShell key
      );

      //## Operation: GetDefaultAttribute%1051589361
      static bool GetDefaultAttribute (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL objKey, 	// The key associated with the Identity
      char* ret_value, 	// This has the attribute value returned as a null
      	// terminated string
      unsigned buf_len	// The length of the ret_value buffer
      );

    // Additional Public Declarations
      //## begin BaseShellQuestion%3A9AC62001BA.public preserve=yes
      //## end BaseShellQuestion%3A9AC62001BA.public

  protected:
    // Additional Protected Declarations
      //## begin BaseShellQuestion%3A9AC62001BA.protected preserve=yes
      //## end BaseShellQuestion%3A9AC62001BA.protected

  private:
    // Additional Private Declarations
      //## begin BaseShellQuestion%3A9AC62001BA.private preserve=yes
      //## end BaseShellQuestion%3A9AC62001BA.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin BaseShellQuestion%3A9AC62001BA.implementation preserve=yes
      //## end BaseShellQuestion%3A9AC62001BA.implementation

};

//## begin BaseShellQuestion%3A9AC62001BA.postscript preserve=yes
//## end BaseShellQuestion%3A9AC62001BA.postscript

// Class Utility BaseShellQuestion 

//## begin module%3ADF39F9029F.epilog preserve=yes
//## end module%3ADF39F9029F.epilog


#endif
