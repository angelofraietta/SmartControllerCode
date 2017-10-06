//## begin module%3A9C90EC00AA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A9C90EC00AA.cm

//## begin module%3A9C90EC00AA.cp preserve=no
//	Angelo Fraietta
//## end module%3A9C90EC00AA.cp

//## Module: BaseShellAnswer%3A9C90EC00AA; Package specification
//	Declaration file for BaseShellAnswer.
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\baseshellanswer.h

#ifndef baseshellanswer_h
#define baseshellanswer_h 1

//## begin module%3A9C90EC00AA.additionalIncludes preserve=no
//## end module%3A9C90EC00AA.additionalIncludes

//## begin module%3A9C90EC00AA.includes preserve=yes
//## end module%3A9C90EC00AA.includes

// InterfaceTypes
#include "interfacetypes.h"

class BaseShell;
class SMUtility;
class ConnectorAnswer;
class CBaseShellReset;
class CBaseShellSend;

//## begin module%3A9C90EC00AA.declarations preserve=no
//## end module%3A9C90EC00AA.declarations

//## begin module%3A9C90EC00AA.additionalDeclarations preserve=yes
//## end module%3A9C90EC00AA.additionalDeclarations


//## begin BaseShellAnswer%3A99D21A0030.preface preserve=yes
//## end BaseShellAnswer%3A99D21A0030.preface

//## Class: BaseShellAnswer%3A99D21A0030; Class Utility
//	Interface for accessing BaseShell operations. Parameters
//	are passed both through the const byte[] question
//	buffer.  The input parameters are stored in a contiguous
//	byte[], with each parameter existing in a big endian
//	format. The parameters are converted into the
//	appropriate endian through conversion functions and the
//	BaseShell function is called. When the BaseShell
//	function returns, the return values are packed into the
//	byte[] answer buffer in big endian format
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3ACAA5640001;ConnectorAnswer { -> F}
//## Uses: <unnamed>%3ACAB7EE01B5;SMUtility { -> F}

class BaseShellAnswer 
{
  //## begin BaseShellAnswer%3A99D21A0030.initialDeclarations preserve=yes
  //## end BaseShellAnswer%3A99D21A0030.initialDeclarations

  public:
    //## begin BaseShellAnswer::pFuncType%3AC960B8016F.preface preserve=yes
    //## end BaseShellAnswer::pFuncType%3AC960B8016F.preface

    //## Class: pFuncType%3AC960B8016F; Class Utility
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef unsigned (*pfunctype) (const BYTE*, BYTE*, unsigned);
    //## begin BaseShellAnswer::pFuncType%3AC960B8016F.postscript preserve=yes
    //## end BaseShellAnswer::pFuncType%3AC960B8016F.postscript

    //## begin BaseShellAnswer::TargetFunc%3ADF36E9012F.preface preserve=yes
    //## end BaseShellAnswer::TargetFunc%3ADF36E9012F.preface

    //## Class: TargetFunc%3ADF36E9012F; Class Utility
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef enum {eGetNumAttributes, eGetAttributeName,  eGetAttribute,  eSetAttribute, eGetNumResetAttributes, eGetResetAttributeName,  eGetResetAttribute,  eSetResetAttribute, eReset, eSend,  eCreate, eGetNumInlets,  eGetNumOutlets,  eGetInletName,  eGetOutletName,  eGetNumInletConnectors,  eGetNumOutletConnectors,  eCanConnectInlet,  eCanConnectOutlet,  eGetInletConnector,  eGetOutletConnector,  eFindOutletConnectorIndex,  eFindInletConnectorIndex,  eSwapOutletConnector, eGetNumObjectTypes, eGetObjectType, eCanHaveChildren, eCanChangeSize, eGetDefaultAttribute, eMaxFuncIndex} TargetFunc;

    //## begin BaseShellAnswer::TargetFunc%3ADF36E9012F.postscript preserve=yes
    //## end BaseShellAnswer::TargetFunc%3ADF36E9012F.postscript


    //## Other Operations (specified)
      //## Operation: GetBaseShell%983336549
      static BaseShell* GetBaseShell (const BYTE** buf	// Null terminated string that can be converted with a
      	// string function to a P_BASESHELL
      );

      //## Operation: PerformOperation%985819706
      static unsigned PerformOperation (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetObjectType%1048126422
      static unsigned GetObjectType (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: CanHaveChildren%1048130622; C++
      static unsigned CanHaveChildren (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: CanChangeSize%1048130623; C++
      static unsigned CanChangeSize (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

  public:
    // Additional Public Declarations
      //## begin BaseShellAnswer%3A99D21A0030.public preserve=yes
      //## end BaseShellAnswer%3A99D21A0030.public

  protected:
    // Additional Protected Declarations
      //## begin BaseShellAnswer%3A99D21A0030.protected preserve=yes
      //## end BaseShellAnswer%3A99D21A0030.protected

  private:

    //## Other Operations (specified)
      //## Operation: GetNumAttributes%986253862
      static unsigned GetNumAttributes (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetAttributeName%986253863
      static unsigned GetAttributeName (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetAttribute%986253855
      static unsigned GetAttribute (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SetAttribute%986253856
      static unsigned SetAttribute (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetNumResetAttributes%996206545
      static unsigned GetNumResetAttributes (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetResetAttributeName%996206546
      static unsigned GetResetAttributeName (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetResetAttribute%996206547
      static unsigned GetResetAttribute (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SetResetAttribute%996206548
      static unsigned SetResetAttribute (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: Reset%983336530; C++
      static unsigned Reset (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: Send%983336531; C++
      static unsigned Send (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: Create%983336533; C++
      static unsigned Create (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetNumInlets%983336536; C++
      static unsigned GetNumInlets (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetNumOutlets%983336537; C++
      static unsigned GetNumOutlets (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetInletName%983336538; C++
      static unsigned GetInletName (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetOutletName%983336539; C++
      static unsigned GetOutletName (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetNumInletConnectors%983336540; C++
      static unsigned GetNumInletConnectors (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetNumOutletConnectors%983336541; C++
      static unsigned GetNumOutletConnectors (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: CanConnectInlet%983336542; C++
      static unsigned CanConnectInlet (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: CanConnectOutlet%983336543; C++
      static unsigned CanConnectOutlet (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetInletConnector%983336544; C++
      static unsigned GetInletConnector (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetOutletConnector%983336545; C++
      static unsigned GetOutletConnector (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: FindInletConnectorIndex%983336547; C++
      static unsigned FindInletConnectorIndex (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: FindOutletConnectorIndex%983336546; C++
      static unsigned FindOutletConnectorIndex (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SwapOutletConnector%983336548; C++
      static unsigned SwapOutletConnector (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetNumObjectTypes%1048126421; C++
      static unsigned GetNumObjectTypes (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetDefaultAttribute%1051589360
      static unsigned GetDefaultAttribute (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

    // Additional Private Declarations
      //## begin BaseShellAnswer%3A99D21A0030.private preserve=yes
      //## end BaseShellAnswer%3A99D21A0030.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: pFunc%3AC9610A03E4
      //	Static array of member functions
      //## begin BaseShellAnswer::pFunc%3AC9610A03E4.attr preserve=no  private: static BaseShellAnswer::pfunctype [eMaxFuncIndex] {U} {GetNumAttributes, GetAttributeName, GetAttribute,  SetAttribute, GetNumResetAttributes, GetResetAttributeName, GetResetAttribute,  SetResetAttribute, Reset, Send, Create, GetNumInlets,  GetNumOutlets,  GetInletName,  GetOutletName,  GetNumInletConnectors,  GetNumOutletConnectors,  CanConnectInlet,  CanConnectOutlet,  GetInletConnector,  GetOutletConnector,  FindOutletConnectorIndex,  FindInletConnectorIndex,  SwapOutletConnector, GetNumObjectTypes, GetObjectType, CanHaveChildren, CanChangeSize, GetDefaultAttribute}
      static BaseShellAnswer::pfunctype  pFunc[eMaxFuncIndex];
      //## end BaseShellAnswer::pFunc%3AC9610A03E4.attr

    // Data Members for Associations

      //## Association: EngineInterface::<unnamed>%3A99EA140090
      //## Role: BaseShellAnswer::_BaseShellReset%3A99EA1402EA
      //## begin BaseShellAnswer::_BaseShellReset%3A99EA1402EA.role preserve=no  public: CBaseShellReset { -> 1VFHN}
      static CBaseShellReset _BaseShellReset;
      //## end BaseShellAnswer::_BaseShellReset%3A99EA1402EA.role

      //## Association: EngineInterface::<unnamed>%3A9DA2930337
      //## Role: BaseShellAnswer::<the_BaseShell>%3A9DA2940112
      //## begin BaseShellAnswer::<the_BaseShell>%3A9DA2940112.role preserve=no  public: BaseShell { -> RFHN}
      //## end BaseShellAnswer::<the_BaseShell>%3A9DA2940112.role

      //## Association: EngineInterface::<unnamed>%3A99E99E0159
      //## Role: BaseShellAnswer::_BaseShellSend%3A99E9A201E1
      //## begin BaseShellAnswer::_BaseShellSend%3A99E9A201E1.role preserve=no  public: CBaseShellSend { -> 1VFHN}
      static CBaseShellSend _BaseShellSend;
      //## end BaseShellAnswer::_BaseShellSend%3A99E9A201E1.role

    // Additional Implementation Declarations
      //## begin BaseShellAnswer%3A99D21A0030.implementation preserve=yes
      //## end BaseShellAnswer%3A99D21A0030.implementation

};

//## begin BaseShellAnswer%3A99D21A0030.postscript preserve=yes
//## end BaseShellAnswer%3A99D21A0030.postscript

// Class Utility BaseShellAnswer 

//## begin module%3A9C90EC00AA.epilog preserve=yes
//## end module%3A9C90EC00AA.epilog


#endif
