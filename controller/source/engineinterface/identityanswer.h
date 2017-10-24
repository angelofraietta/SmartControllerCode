//## begin module%3AC149EA02D0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AC149EA02D0.cm

//## begin module%3AC149EA02D0.cp preserve=no
//	Angelo Fraietta
//## end module%3AC149EA02D0.cp

//## Module: IdentityAnswer%3AC149EA02D0; Package specification
//	Declaration for IdentityAnswer
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\identityanswer.h

#ifndef identityanswer_h
#define identityanswer_h 1

//## begin module%3AC149EA02D0.additionalIncludes preserve=no
//## end module%3AC149EA02D0.additionalIncludes

//## begin module%3AC149EA02D0.includes preserve=yes
//## end module%3AC149EA02D0.includes

// InterfaceTypes
#include "interfacetypes.h"

class Identity;

//## begin module%3AC149EA02D0.declarations preserve=no
//## end module%3AC149EA02D0.declarations

//## begin module%3AC149EA02D0.additionalDeclarations preserve=yes
//## end module%3AC149EA02D0.additionalDeclarations


//## begin IdentityAnswer%3A99D27700DE.preface preserve=yes
//## end IdentityAnswer%3A99D27700DE.preface

//## Class: IdentityAnswer%3A99D27700DE; Class Utility
//	Interface for accessing Identity operations. Parameters
//	are passed both through the const byte[] question
//	buffer.  The input parameters are stored in a contiguous
//	byte[], with each parameter existing in a big endian
//	format. The parameters are converted into the
//	appropriate endian through conversion functions and the
//	Identity function is called. When the Identity function
//	returns, the return values are packed into the byte[]
//	answer buffer in big endian format
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3A9C8AF503A7;Identity { -> F}

class IdentityAnswer 
{
  //## begin IdentityAnswer%3A99D27700DE.initialDeclarations preserve=yes
  //## end IdentityAnswer%3A99D27700DE.initialDeclarations

  public:
    //## begin IdentityAnswer::pfunctype%3AC15DA0033A.preface preserve=yes
    //## end IdentityAnswer::pfunctype%3AC15DA0033A.preface

    //## Class: pfunctype%3AC15DA0033A; Class Utility
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef unsigned (*pfunctype) (const BYTE*, BYTE*, unsigned);
    //## begin IdentityAnswer::pfunctype%3AC15DA0033A.postscript preserve=yes
    //## end IdentityAnswer::pfunctype%3AC15DA0033A.postscript

    //## begin IdentityAnswer::TartgetFunc%3ADF375D00AA.preface preserve=yes
    //## end IdentityAnswer::TartgetFunc%3ADF375D00AA.preface

    //## Class: TartgetFunc%3ADF375D00AA; Class Utility
    //## Category: EngineInterface::Answer%3AA7F4FF028C
    //## Subsystem: engineinterface%3A9C858C00CB
    //## Persistence: Transient
    //## Cardinality/Multiplicity: n

    typedef enum {eGetName, eGetComment, eGetType, eGetModified, eSetName, eSetComment, eGetDefaultAttribute, eSetDefaultAttribute, eCanSave, eGetParent, eSetParent, eMaxFuncIndex} TartgetFunc;

    //## begin IdentityAnswer::TartgetFunc%3ADF375D00AA.postscript preserve=yes
    //## end IdentityAnswer::TartgetFunc%3ADF375D00AA.postscript


    //## Other Operations (specified)
      //## Operation: GetIdentity%983336508
      static Identity* GetIdentity (const BYTE** buf	// address of BYTE array containing the P_IDENTITY
      );

      //## Operation: PerformOperation%985746356
      static unsigned PerformOperation (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: AddIdentity%1020302311
      static bool AddIdentity (Identity* id, unsigned* ret_key);

      //## Operation: RemoveIdentity%1020302312
      static bool RemoveIdentity (Identity* id);

      //## Operation: GetIdentity%1020302313
      static Identity* GetIdentity (P_IDENTITY pid);

      static unsigned GetIdentityKey (Identity* id);

  public:
    // Additional Public Declarations
      //## begin IdentityAnswer%3A99D27700DE.public preserve=yes
      //## end IdentityAnswer%3A99D27700DE.public

  protected:
    // Additional Protected Declarations
      //## begin IdentityAnswer%3A99D27700DE.protected preserve=yes
      //## end IdentityAnswer%3A99D27700DE.protected

  private:

    //## Other Operations (specified)
      //## Operation: GetDefaultAttribute%984007434
      static unsigned GetDefaultAttribute (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetName%986510811
      static unsigned GetName (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetComment%986510812
      static unsigned GetComment (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetType%986510813
      static unsigned GetType (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetModified%986510814
      static unsigned GetModified (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SetName%986510815
      static unsigned SetName (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SetComment%986510816
      static unsigned SetComment (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SetDefaultAttribute%986947728
      static unsigned SetDefaultAttribute (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: CanSave%986947730; C++
      static unsigned CanSave (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: GetParent%986947732; C++
      static unsigned GetParent (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

      //## Operation: SetParent%986947733; C++
      static unsigned SetParent (const BYTE* question, 	// The parameters are passed into here as big endian
      	// parameters
      BYTE* answer, 	// This is where the paramaters are returned from the
      	// function as big endian.
      unsigned answer_size	// The maximum size of the answer buffer
      );

    // Additional Private Declarations
      //## begin IdentityAnswer%3A99D27700DE.private preserve=yes
      //## end IdentityAnswer%3A99D27700DE.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: pFunc%3AC15EF100E6
      //	Static array of member functions
      //## begin IdentityAnswer::pFunc%3AC15EF100E6.attr preserve=no  private: static IdentityAnswer::pfunctype [eMaxFuncIndex] {V} {GetName, GetComment, GetType, GetModified, SetName, SetComment, GetDefaultAttribute, SetDefaultAttribute, CanSave, GetParent, SetParent}
      static IdentityAnswer::pfunctype  pFunc[eMaxFuncIndex];
      //## end IdentityAnswer::pFunc%3AC15EF100E6.attr

    // Additional Implementation Declarations
      //## begin IdentityAnswer%3A99D27700DE.implementation preserve=yes
      //## end IdentityAnswer%3A99D27700DE.implementation

};

//## begin IdentityAnswer%3A99D27700DE.postscript preserve=yes
//## end IdentityAnswer%3A99D27700DE.postscript

// Class Utility IdentityAnswer 

//## begin module%3AC149EA02D0.epilog preserve=yes
//## end module%3AC149EA02D0.epilog


#endif
