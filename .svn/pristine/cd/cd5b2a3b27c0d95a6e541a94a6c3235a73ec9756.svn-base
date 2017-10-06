//## begin module%3ADF3C4A01ED.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ADF3C4A01ED.cm

//## begin module%3ADF3C4A01ED.cp preserve=no
//	Angelo Fraietta
//## end module%3ADF3C4A01ED.cp

//## Module: IdentityQuestion%3ADF3C4A01ED; Package specification
//	Declaration of the IdentityQuestion which is the exposed
//	interface to the PatchEditor
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\identityquestion.h

#ifndef identityquestion_h
#define identityquestion_h 1

//## begin module%3ADF3C4A01ED.additionalIncludes preserve=no
//## end module%3ADF3C4A01ED.additionalIncludes

//## begin module%3ADF3C4A01ED.includes preserve=yes
//## end module%3ADF3C4A01ED.includes

// InterfaceTypes
#include "interfacetypes.h"

class PresentationQuestion;
class IdentityAnswer;

//## begin module%3ADF3C4A01ED.declarations preserve=no
//## end module%3ADF3C4A01ED.declarations

//## begin module%3ADF3C4A01ED.additionalDeclarations preserve=yes
//## end module%3ADF3C4A01ED.additionalDeclarations


//## begin IdentityQuestion%3A9AC69203C7.preface preserve=yes
//## end IdentityQuestion%3A9AC69203C7.preface

//## Class: IdentityQuestion%3A9AC69203C7; Class Utility
//	Assembles Identity questions and sends them to the
//	PresentationQuestion for an answer.
//## Category: EngineInterface::Question%3AA7F96B037A
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: calls%3AC2CFA200DC;PresentationQuestion { -> F}
//## Uses: <unnamed>%3ADF445F03DD;IdentityAnswer { -> F}

class IdentityQuestion 
{
  //## begin IdentityQuestion%3A9AC69203C7.initialDeclarations preserve=yes
  //## end IdentityQuestion%3A9AC69203C7.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: GetDefaultAttribute%985746352
      static bool GetDefaultAttribute (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_IDENTITY objKey, 	// The key associated with the Identity
      char* ret_value, 	// This has the attribute value returned as a null
      	// terminated string
      unsigned buf_len	// The length of the ret_value buffer
      );

      //## Operation: GetName%986510805
      static void GetName (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_IDENTITY objKey, 	// The key associated with the Identity
      char* ret_value, 	// This has the attribute value returned as a null
      	// terminated string
      unsigned buf_len	// The length of the ret_value buffer
      );

      //## Operation: GetComment%986510806
      static void GetComment (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_IDENTITY objKey, 	// The key associated with the Identity
      char* ret_value, 	// This has the attribute value returned as a null
      	// terminated string
      unsigned buf_len	// The length of the ret_value buffer
      );

      //## Operation: GetType%986510807
      static void GetType (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_IDENTITY objKey, 	// The key associated with the Identity
      char* ret_value, 	// This has the attribute value returned as a null
      	// terminated string
      unsigned buf_len	// The length of the ret_value buffer
      );

      //## Operation: SetName%986510808
      static bool SetName (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_IDENTITY objKey, 	// The key associated with the Identity
      const char* new_value	// This has the attribute value returned as a null
      	// terminated string
      );

      //## Operation: SetComment%986510809
      static bool SetComment (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_IDENTITY objKey, 	// The key associated with the Identity
      const char* new_value	// This has the attribute value returned as a null
      	// terminated string
      );

      //## Operation: GetModified%986510810
      static bool GetModified (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_IDENTITY objKey	// The key associated with the Identity
      );

      //## Operation: SetDefaultAttribute%986947729
      static bool SetDefaultAttribute (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_IDENTITY objKey, 	// The key associated with the Identity
      const char* new_value	// This has the attribute value returned as a null
      	// terminated string
      );

      //## Operation: CanSave%986947731; C++
      static bool CanSave (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_IDENTITY dwpId);

      //## Operation: GetParent%986947734; C++
      static P_PATCH GetParent (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_IDENTITY dwpId);

      //## Operation: SetParent%986947735; C++
      static void SetParent (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_IDENTITY dwpId, P_PATCH dwpParent);

    // Additional Public Declarations
      //## begin IdentityQuestion%3A9AC69203C7.public preserve=yes
      //## end IdentityQuestion%3A9AC69203C7.public

  protected:
    // Additional Protected Declarations
      //## begin IdentityQuestion%3A9AC69203C7.protected preserve=yes
      //## end IdentityQuestion%3A9AC69203C7.protected

  private:
    // Additional Private Declarations
      //## begin IdentityQuestion%3A9AC69203C7.private preserve=yes
      //## end IdentityQuestion%3A9AC69203C7.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin IdentityQuestion%3A9AC69203C7.implementation preserve=yes
      //## end IdentityQuestion%3A9AC69203C7.implementation

};

//## begin IdentityQuestion%3A9AC69203C7.postscript preserve=yes
//## end IdentityQuestion%3A9AC69203C7.postscript

// Class Utility IdentityQuestion 

//## begin module%3ADF3C4A01ED.epilog preserve=yes
//## end module%3ADF3C4A01ED.epilog


#endif
