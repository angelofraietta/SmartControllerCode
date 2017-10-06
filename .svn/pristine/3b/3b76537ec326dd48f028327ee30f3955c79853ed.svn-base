//## begin module%3ADF41A402E8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ADF41A402E8.cm

//## begin module%3ADF41A402E8.cp preserve=no
//	Angelo Fraietta
//## end module%3ADF41A402E8.cp

//## Module: PatchQuestion%3ADF41A402E8; Package specification
//	Declaration for Patch Interface which is exposed to
//	Patch Editor
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: d:\develop\smartcontroller\controller\source\engineinterface\patchquestion.h

#ifndef patchquestion_h
#define patchquestion_h 1

//## begin module%3ADF41A402E8.additionalIncludes preserve=no
//## end module%3ADF41A402E8.additionalIncludes

//## begin module%3ADF41A402E8.includes preserve=yes
//## end module%3ADF41A402E8.includes

// InterfaceTypes
#include "interfacetypes.h"

class PresentationQuestion;
class PatchAnswer;

//## begin module%3ADF41A402E8.declarations preserve=no
//## end module%3ADF41A402E8.declarations

//## begin module%3ADF41A402E8.additionalDeclarations preserve=yes
//## end module%3ADF41A402E8.additionalDeclarations


//## begin PatchQuestion%3A99CCB2003B.preface preserve=yes
//## end PatchQuestion%3A99CCB2003B.preface

//## Class: PatchQuestion%3A99CCB2003B; Class Utility
//	Assembles Patch questions and sends them to the Engine
//	for an answer
//## Category: EngineInterface::Question%3AA7F96B037A
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3A99CCB2015D;P_IDENTITY { -> F}
//## Uses: <unnamed>%3A99CCB201A4;P_BASESHELL { -> F}
//## Uses: <unnamed>%3A99CCB201C2;P_PATCH { -> F}
//## Uses: <unnamed>%3A99CCB201FE;P_CONNECTOR { -> F}
//## Uses: calls%3AC3D0BE0249;PresentationQuestion { -> F}
//## Uses: <unnamed>%3ADF443B0377;PatchAnswer { -> F}

class PatchQuestion 
{
  //## begin PatchQuestion%3A99CCB2003B.initialDeclarations preserve=yes
  //## end PatchQuestion%3A99CCB2003B.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: DetachBaseShellObject%2052505070; C++
      static void DetachBaseShellObject (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, P_BASESHELL dwpShell);

      //## Operation: FindBaseShellPosition%633089553; C++
      static unsigned FindBaseShellPosition (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, P_BASESHELL dwpShell);

      //## Operation: AddBaseShell%-1753633385; C++
      static void AddBaseShell (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, P_BASESHELL dwpShell);

      //## Operation: NumberBaseShells%-483082950; C++
      static unsigned NumberBaseShells (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch);

      //## Operation: FindBaseShell%1580427729; C++
      static P_BASESHELL FindBaseShell (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned int Index);

      //## Operation: DetachConnector%1779840400; C++
      static void DetachConnector (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, P_CONNECTOR dwpCon);

      //## Operation: AddConnector%1383773166; C++
      static void AddConnector (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, P_CONNECTOR dwpCon);

      //## Operation: NumberConnectors%-1454729344; C++
      static unsigned NumberConnectors (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch);

      //## Operation: FindConnector%794111187; C++
      static P_CONNECTOR FindConnector (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned int Index);

      //## Operation: GetDeadConnector%581481705; C++
      static P_CONNECTOR GetDeadConnector (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch);

      //## Operation: AddInlet%-1660140033; C++
      static P_BASESHELL AddInlet (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch);

      //## Operation: AddOutlet%-1013941598; C++
      static P_BASESHELL AddOutlet (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch);

      //## Operation: MakeNew%-184639055; C++
      static P_PATCH MakeNew (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      const char* Name);

      //## Operation: SetFileName%1235827609; C++
      static void SetFileName (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, const char* FileName);

      //## Operation: LoadPatchFile%-326480328; C++
      static P_PATCH LoadPatchFile (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      const char* FileName, P_PATCH dwpParent);

      //## Operation: GetFileName%690648392; C++
      static void GetFileName (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, char* FileName, unsigned buf_len);

      //## Operation: Save%-1512333622; C++
      static bool Save (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, const char* FileName);

      //## Operation: Destroy%-947060103; C++
      static void Destroy (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch);

      //## Operation: SwapOutlets%1612806088; C++
      static void SwapOutlets (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned int Outlet1, unsigned int Outlet2);

      //## Operation: SwapInlets%-540055132; C++
      static void SwapInlets (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned int Inlet1, unsigned int Inlet2);

      //## Operation: GetInlet%2006261230; C++
      static P_BASESHELL GetInlet (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned int SocketNum);

      //## Operation: GetOutlet%274728559; C++
      static P_BASESHELL GetOutlet (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_PATCH dwpPatch, unsigned int SocketNum);

      //## Operation: GetOutletPortNumber%988078469; C++
      static unsigned GetOutletPortNumber (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell);

      //## Operation: GetInletPortNumber%988078470; C++
      static unsigned GetInletPortNumber (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      P_BASESHELL dwpShell);

      //## Operation: NumberPatches%1020226581; C++
      static int NumberPatches (PresentationQuestion* pQuestion	// Pointer to the Presentation Question used to get the
      	// answer
      );

      //## Operation: GetPatch%1020226582; C++
      static P_PATCH GetPatch (PresentationQuestion* pQuestion, 	// Pointer to the Presentation Question used to get the
      	// answer
      unsigned patch_num);

    // Additional Public Declarations
      //## begin PatchQuestion%3A99CCB2003B.public preserve=yes
      //## end PatchQuestion%3A99CCB2003B.public

  protected:
    // Additional Protected Declarations
      //## begin PatchQuestion%3A99CCB2003B.protected preserve=yes
      //## end PatchQuestion%3A99CCB2003B.protected

  private:
    // Additional Private Declarations
      //## begin PatchQuestion%3A99CCB2003B.private preserve=yes
      //## end PatchQuestion%3A99CCB2003B.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin PatchQuestion%3A99CCB2003B.implementation preserve=yes
      //## end PatchQuestion%3A99CCB2003B.implementation

};

//## begin PatchQuestion%3A99CCB2003B.postscript preserve=yes
//## end PatchQuestion%3A99CCB2003B.postscript

// Class Utility PatchQuestion 

//## begin module%3ADF41A402E8.epilog preserve=yes
//## end module%3ADF41A402E8.epilog


#endif
