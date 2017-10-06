//## begin module%3AC3DECF0279.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AC3DECF0279.cm

//## begin module%3AC3DECF0279.cp preserve=no
//	Angelo Fraietta
//## end module%3AC3DECF0279.cp

//## Module: ConnectorAnswer%3AC3DECF0279; Package specification
//	Specification for ConnectorAnswer
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\connectoranswer.h

#ifndef connectoranswer_h
#define connectoranswer_h 1

//## begin module%3AC3DECF0279.additionalIncludes preserve=no
//## end module%3AC3DECF0279.additionalIncludes

//## begin module%3AC3DECF0279.includes preserve=yes
//## end module%3AC3DECF0279.includes

// InterfaceTypes
#include "interfacetypes.h"
//## begin module%3AC3DECF0279.declarations preserve=no
//## end module%3AC3DECF0279.declarations

//## begin module%3AC3DECF0279.additionalDeclarations preserve=yes
//## end module%3AC3DECF0279.additionalDeclarations


//## begin ConnectorAnswer%3A999736037B.preface preserve=yes
//## end ConnectorAnswer%3A999736037B.preface

//## Class: ConnectorAnswer%3A999736037B; Class Utility
//	Interface for accessing Connector operations. Parameters
//	are passed both through the const byte[] question
//	buffer.  The input parameters are stored in a contiguous
//	byte[], with each parameter existing in a big endian
//	format. The parameters are converted into the
//	appropriate endian through conversion functions and the
//	Connector function is called. When the Connector
//	function returns, the return values are packed into the
//	byte[] answer buffer in big endian format
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class ConnectorAnswer 
{
  //## begin ConnectorAnswer%3A999736037B.initialDeclarations preserve=yes
  //## end ConnectorAnswer%3A999736037B.initialDeclarations

  public:
    //## begin ConnectorAnswer::TargetFunc%3ADF47A603A7.preface preserve=yes
    //## end ConnectorAnswer::TargetFunc%3ADF47A603A7.preface

    //## Class: TargetFunc%3ADF47A603A7; Class Utility
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef enum {eIsValid, eGetInletBase, eGetOutletBase, eGetInletNum,  eGetOutletNum,  eGetOutletIndex,  eSetInletBase,  eSetInletNum,  eSetOutletBase,  eSetOutletNum,  eMakeConnection,  eCreate,  eDestroy, eMaxFuncIndex} TargetFunc;

    //## begin ConnectorAnswer::TargetFunc%3ADF47A603A7.postscript preserve=yes
    //## end ConnectorAnswer::TargetFunc%3ADF47A603A7.postscript

    //## begin ConnectorAnswer::pFuncType%3ADFBBB502E1.preface preserve=yes
    //## end ConnectorAnswer::pFuncType%3ADFBBB502E1.preface

    //## Class: pFuncType%3ADFBBB502E1; Class Utility
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef unsigned (*pfunctype) (const BYTE*, BYTE*, unsigned);
    //## begin ConnectorAnswer::pFuncType%3ADFBBB502E1.postscript preserve=yes
    //## end ConnectorAnswer::pFuncType%3ADFBBB502E1.postscript


    //## Other Operations (specified)
      //## Operation: IsValid%983336511; C++
      static unsigned IsValid (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetInletBase%983336512; C++
      static unsigned GetInletBase (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetInletNum%983336513; C++
      static unsigned GetInletNum (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetOutletBase%983336514; C++
      static unsigned GetOutletBase (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetOutletNum%983336515; C++
      static unsigned GetOutletNum (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetOutletIndex%983336516; C++
      static unsigned GetOutletIndex (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SetInletBase%983336518; C++
      static unsigned SetInletBase (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SetInletNum%983336519; C++
      static unsigned SetInletNum (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SetOutletBase%983336520; C++
      static unsigned SetOutletBase (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SetOutletNum%983336521; C++
      static unsigned SetOutletNum (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: MakeConnection%983336522; C++
      static unsigned MakeConnection (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: Create%983336524; C++
      static unsigned Create (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: Destroy%983336525; C++
      static unsigned Destroy (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetConnector%983336527
      static Connector* GetConnector (const BYTE** buf	// Null terminated string that can be converted with a
      	// string function to a P_CONNECTOR
      );

      //## Operation: PerformOperation%985819707
      static unsigned PerformOperation (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

  public:
    // Additional Public Declarations
      //## begin ConnectorAnswer%3A999736037B.public preserve=yes
      //## end ConnectorAnswer%3A999736037B.public

  protected:
    // Additional Protected Declarations
      //## begin ConnectorAnswer%3A999736037B.protected preserve=yes
      //## end ConnectorAnswer%3A999736037B.protected

  private:
    // Additional Private Declarations
      //## begin ConnectorAnswer%3A999736037B.private preserve=yes
      //## end ConnectorAnswer%3A999736037B.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: pFunc%3ADFBC0502FA
      //	Static array of member functions
      //## begin ConnectorAnswer::pFunc%3ADFBC0502FA.attr preserve=no  private: static ConnectorAnswer::pfunctype [eMaxFuncIndex] {U} {IsValid, GetInletBase, GetOutletBase, GetInletNum,  GetOutletNum,  GetOutletIndex,  SetInletBase,  SetInletNum,  SetOutletBase,  SetOutletNum,  MakeConnection,  Create,  Destroy}
      static ConnectorAnswer::pfunctype  pFunc[eMaxFuncIndex];
      //## end ConnectorAnswer::pFunc%3ADFBC0502FA.attr

    // Additional Implementation Declarations
      //## begin ConnectorAnswer%3A999736037B.implementation preserve=yes
      //## end ConnectorAnswer%3A999736037B.implementation

};

//## begin ConnectorAnswer%3A999736037B.postscript preserve=yes
//## end ConnectorAnswer%3A999736037B.postscript

// Class Utility ConnectorAnswer 

//## begin module%3AC3DECF0279.epilog preserve=yes
//## end module%3AC3DECF0279.epilog


#endif
