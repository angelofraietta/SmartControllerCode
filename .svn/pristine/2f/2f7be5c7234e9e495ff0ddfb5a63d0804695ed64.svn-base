//## begin module%3A9C9220036A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A9C9220036A.cm

//## begin module%3A9C9220036A.cp preserve=no
//	Angelo Fraietta
//## end module%3A9C9220036A.cp

//## Module: PatchAnswer%3A9C9220036A; Package specification
//	Contains the header information for obtaining Answers to
//	Patchs.
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\patchanswer.h

#ifndef patchanswer_h
#define patchanswer_h 1

//## begin module%3A9C9220036A.additionalIncludes preserve=no
//## end module%3A9C9220036A.additionalIncludes

//## begin module%3A9C9220036A.includes preserve=yes
//## end module%3A9C9220036A.includes

// InterfaceTypes
#include "interfacetypes.h"
// BaseShellAnswer
#include "baseshellanswer.h"

class DetachBaseShell;
class PatchDeleter;

//## begin module%3A9C9220036A.declarations preserve=no
//## end module%3A9C9220036A.declarations

//## begin module%3A9C9220036A.additionalDeclarations preserve=yes
//## end module%3A9C9220036A.additionalDeclarations


//## begin PatchAnswer%3A99D2AC01DF.preface preserve=yes
//## end PatchAnswer%3A99D2AC01DF.preface

//## Class: PatchAnswer%3A99D2AC01DF; Class Utility
//	Interface for accessing Patch operations. Parameters are
//	passed both through the const byte[] question buffer.
//	The input parameters are stored in a contiguous byte[],
//	with each parameter existing in a big endian format. The
//	parameters are converted into the appropriate endian
//	through conversion functions and the Patch function is
//	called. When the Patch function returns, the return
//	values are packed into the byte[] answer buffer in big
//	endian format
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class PatchAnswer 
{
  //## begin PatchAnswer%3A99D2AC01DF.initialDeclarations preserve=yes
  //## end PatchAnswer%3A99D2AC01DF.initialDeclarations

  public:
    //## begin PatchAnswer::pFuncType%3ADFC14603B3.preface preserve=yes
    //## end PatchAnswer::pFuncType%3ADFC14603B3.preface

    //## Class: pFuncType%3ADFC14603B3; Class Utility
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef unsigned (*pfunctype) (const BYTE*, BYTE*, unsigned);
    //## begin PatchAnswer::pFuncType%3ADFC14603B3.postscript preserve=yes
    //## end PatchAnswer::pFuncType%3ADFC14603B3.postscript

    //## begin PatchAnswer::TargetFunc%3ADFC1E7029C.preface preserve=yes
    //## end PatchAnswer::TargetFunc%3ADFC1E7029C.preface

    //## Class: TargetFunc%3ADFC1E7029C; Class Utility
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef enum {eDetachBaseShellObject, eFindBaseShellPosition, eAddBaseShell, eNumberBaseShells, eFindBaseShell, eDetachConnector, eAddConnector, eNumberConnectors, eFindConnector, eGetDeadConnector, eAddInlet, eAddOutlet, eMakeNew, eSetFileName, eLoadPatchFile, eGetFileName, eSave, eDestroy, eSwapOutlets, eSwapInlets, eGetInlet, eGetOutlet, eGetOutletPortNumber, eGetInletPortNumber, eNumberPatches, eGetPatch, eMaxFuncIndex} TargetFunc;

    //## begin PatchAnswer::TargetFunc%3ADFC1E7029C.postscript preserve=yes
    //## end PatchAnswer::TargetFunc%3ADFC1E7029C.postscript


    //## Other Operations (specified)
      //## Operation: GetPatch%983336498
      static Patch* GetPatch (const BYTE** buf	// address of BYTE array containing the P_PATCH
      );

      //## Operation: PerformOperation%985819705
      static unsigned PerformOperation (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

  public:
    // Additional Public Declarations
      //## begin PatchAnswer%3A99D2AC01DF.public preserve=yes
      //## end PatchAnswer%3A99D2AC01DF.public

  protected:
    // Additional Protected Declarations
      //## begin PatchAnswer%3A99D2AC01DF.protected preserve=yes
      //## end PatchAnswer%3A99D2AC01DF.protected

  private:

    //## Other Operations (specified)
      //## Operation: DetachBaseShellObject%983336476; C++
      static unsigned DetachBaseShellObject (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: FindBaseShellPosition%983336477; C++
      static unsigned FindBaseShellPosition (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: AddBaseShell%983336478; C++
      static unsigned AddBaseShell (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: NumberBaseShells%983336479; C++
      static unsigned NumberBaseShells (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: FindBaseShell%983336480; C++
      static unsigned FindBaseShell (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: DetachConnector%983336481; C++
      static unsigned DetachConnector (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: AddConnector%983336482; C++
      static unsigned AddConnector (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: NumberConnectors%983336483; C++
      static unsigned NumberConnectors (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: FindConnector%983336484; C++
      static unsigned FindConnector (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetDeadConnector%983336485; C++
      static unsigned GetDeadConnector (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: AddInlet%983336486; C++
      static unsigned AddInlet (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: AddOutlet%983336487; C++
      static unsigned AddOutlet (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: MakeNew%983336488; C++
      static unsigned MakeNew (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SetFileName%983336489; C++
      static unsigned SetFileName (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: LoadPatchFile%983336490; C++
      static unsigned LoadPatchFile (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetFileName%983336491; C++
      static unsigned GetFileName (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: Save%983336492; C++
      static unsigned Save (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: Destroy%983336493; C++
      static unsigned Destroy (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SwapOutlets%983336494; C++
      static unsigned SwapOutlets (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SwapInlets%983336495; C++
      static unsigned SwapInlets (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetInlet%983336496; C++
      static unsigned GetInlet (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetOutlet%983336497; C++
      static unsigned GetOutlet (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetOutletPortNumber%988078471; C++
      static unsigned GetOutletPortNumber (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetInletPortNumber%988078472; C++
      static unsigned GetInletPortNumber (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: NumberPatches%1020226579; C++
      static unsigned NumberPatches (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetPatch%1020226580; C++
      static unsigned GetPatch (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

    // Additional Private Declarations
      //## begin PatchAnswer%3A99D2AC01DF.private preserve=yes
      //## end PatchAnswer%3A99D2AC01DF.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: pFunc%3ADFC3F40369
      //	Static array of member functions
      //## begin PatchAnswer::pFunc%3ADFC3F40369.attr preserve=no  private: static PatchAnswer::pfunctype [eMaxFuncIndex] {U} {DetachBaseShellObject, FindBaseShellPosition, AddBaseShell, NumberBaseShells, FindBaseShell, DetachConnector, AddConnector, NumberConnectors, FindConnector, GetDeadConnector, AddInlet, AddOutlet, MakeNew, SetFileName, LoadPatchFile, GetFileName, Save, Destroy, SwapOutlets, SwapInlets, GetInlet, GetOutlet, GetOutletPortNumber, GetInletPortNumber, NumberPatches, GetPatch}
      static PatchAnswer::pfunctype  pFunc[eMaxFuncIndex];
      //## end PatchAnswer::pFunc%3ADFC3F40369.attr

    // Data Members for Associations

      //## Association: EngineInterface::<unnamed>%3A99EC5F01CB
      //## Role: PatchAnswer::_PatchDelete%3A99EC60000A
      //## begin PatchAnswer::_PatchDelete%3A99EC60000A.role preserve=no  public: static PatchDeleter { -> 1VFHN}
      static PatchDeleter _PatchDelete;
      //## end PatchAnswer::_PatchDelete%3A99EC60000A.role

      //## Association: EngineInterface::<unnamed>%3A99EFF60263
      //## Role: PatchAnswer::_DetachBaseShell%3A99EFF80144
      //## begin PatchAnswer::_DetachBaseShell%3A99EFF80144.role preserve=no  public: static DetachBaseShell { -> 1VFHN}
      static DetachBaseShell _DetachBaseShell;
      //## end PatchAnswer::_DetachBaseShell%3A99EFF80144.role

    // Additional Implementation Declarations
      //## begin PatchAnswer%3A99D2AC01DF.implementation preserve=yes
      //## end PatchAnswer%3A99D2AC01DF.implementation

};

//## begin PatchAnswer%3A99D2AC01DF.postscript preserve=yes
//## end PatchAnswer%3A99D2AC01DF.postscript

// Class Utility PatchAnswer 

//## begin module%3A9C9220036A.epilog preserve=yes
//## end module%3A9C9220036A.epilog


#endif
