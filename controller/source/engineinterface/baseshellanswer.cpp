//## begin module%3ACAB0AA02AA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ACAB0AA02AA.cm

//## begin module%3ACAB0AA02AA.cp preserve=no
//	Angelo Fraietta
//## end module%3ACAB0AA02AA.cp

//## Module: BaseShellAnswer%3ACAB0AA02AA; Package body
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\baseshellanswer.cpp

//## begin module%3ACAB0AA02AA.additionalIncludes preserve=no
#include "stdafx.h"
#include "control.h"
//## end module%3ACAB0AA02AA.additionalIncludes

//## begin module%3ACAB0AA02AA.includes preserve=yes
#include <string.h>
#include "typelist.h"
#include "identityanswer.h"
#include "scheduler.h"
//## end module%3ACAB0AA02AA.includes

// baseshel
#include "baseshel.h"
// timer
#include "timer.h"
// PatchAnswer
#include "patchanswer.h"
// BaseShellAnswer
#include "baseshellanswer.h"
// ConnectorAnswer
#include "connectoranswer.h"
// SMUtility
#include "smutility.h"

class CBaseShellReset;
class CBaseShellSend;

//## begin module%3ACAB0AA02AA.declarations preserve=no
//## end module%3ACAB0AA02AA.declarations

//## begin module%3ACAB0AA02AA.additionalDeclarations preserve=yes
//## end module%3ACAB0AA02AA.additionalDeclarations


//## begin CBaseShellSend%3A970A970173.preface preserve=yes
//## end CBaseShellSend%3A970A970173.preface

//## Class: CBaseShellSend%3A970A970173
//	This class is responsible for passing the send message
//	to the Baseshell.  This is accomplished by receiving the
//	request and passing it to the scheduler.  The call is
//	returned in the context of the Scheduler task, thus
//	allowing only one task to initiate sending messages.
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class CBaseShellSend : public DelayLine  //## Inherits: <unnamed>%3A970CB8025D
{
  //## begin CBaseShellSend%3A970A970173.initialDeclarations preserve=yes
  //## end CBaseShellSend%3A970A970173.initialDeclarations

  public:
    //## Constructors (generated)
      CBaseShellSend();

    //## Destructor (generated)
      ~CBaseShellSend();


    //## Other Operations (specified)
      //## Operation: Send%982978159
      bool Send (BaseShell* receiver);

    // Additional Public Declarations
      //## begin CBaseShellSend%3A970A970173.public preserve=yes
      //## end CBaseShellSend%3A970A970173.public

  protected:

    //## Other Operations (specified)
      //## Operation: PurgeItem%983336554; C++
      void PurgeItem (unsigned long );

    // Additional Protected Declarations
      //## begin CBaseShellSend%3A970A970173.protected preserve=yes
      //## end CBaseShellSend%3A970A970173.protected

  private:

    //## Other Operations (specified)
      //## Operation: OutputFunction%982978160; C++
      void OutputFunction (DWORD receiver);

    // Additional Private Declarations
      //## begin CBaseShellSend%3A970A970173.private preserve=yes
      //## end CBaseShellSend%3A970A970173.private

  private: //## implementation
    // Data Members for Associations

      //## Association: engine::<unnamed>%3A970FED0268
      //## Role: CBaseShellSend::receiver%3A970FEE00ED
      //## begin CBaseShellSend::receiver%3A970FEE00ED.role preserve=no  public: BaseShell { -> nRFHN}
      //## end CBaseShellSend::receiver%3A970FEE00ED.role

    // Additional Implementation Declarations
      //## begin CBaseShellSend%3A970A970173.implementation preserve=yes
      //## end CBaseShellSend%3A970A970173.implementation

};

//## begin CBaseShellSend%3A970A970173.postscript preserve=yes
//## end CBaseShellSend%3A970A970173.postscript

//## begin CBaseShellReset%3A99A4C90256.preface preserve=yes
//## end CBaseShellReset%3A99A4C90256.preface

//## Class: CBaseShellReset%3A99A4C90256
//	Controls resetting of BaseShell objects
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class CBaseShellReset : public DelayLine  //## Inherits: <unnamed>%3A99A4F40171
{
  //## begin CBaseShellReset%3A99A4C90256.initialDeclarations preserve=yes
  //## end CBaseShellReset%3A99A4C90256.initialDeclarations

  public:
    //## Constructors (generated)
      CBaseShellReset();

    //## Destructor (generated)
      ~CBaseShellReset();


    //## Other Operations (specified)
      //## Operation: Reset%983336509
      bool Reset (BaseShell* receiver);

    // Additional Public Declarations
      //## begin CBaseShellReset%3A99A4C90256.public preserve=yes
      //## end CBaseShellReset%3A99A4C90256.public

  protected:

    //## Other Operations (specified)
      //## Operation: PurgeItem%983336556; C++
      void PurgeItem (unsigned long );

    // Additional Protected Declarations
      //## begin CBaseShellReset%3A99A4C90256.protected preserve=yes
      //## end CBaseShellReset%3A99A4C90256.protected

  private:

    //## Other Operations (specified)
      //## Operation: OutputFunction%983336510; C++
      void OutputFunction (DWORD receiver);

    // Additional Private Declarations
      //## begin CBaseShellReset%3A99A4C90256.private preserve=yes
      //## end CBaseShellReset%3A99A4C90256.private

  private: //## implementation
    // Data Members for Associations

      //## Association: EngineInterface::<unnamed>%3A99A4F9007E
      //## Role: CBaseShellReset::receiver%3A99A4F902C3
      //## begin CBaseShellReset::receiver%3A99A4F902C3.role preserve=no  public: BaseShell { -> nRFHN}
      //## end CBaseShellReset::receiver%3A99A4F902C3.role

    // Additional Implementation Declarations
      //## begin CBaseShellReset%3A99A4C90256.implementation preserve=yes
      //## end CBaseShellReset%3A99A4C90256.implementation

};

//## begin CBaseShellReset%3A99A4C90256.postscript preserve=yes
//## end CBaseShellReset%3A99A4C90256.postscript

// Class CBaseShellSend 


//## Other Operations (inline)
//## Operation: PurgeItem%983336554; C++
//	Empty function required by DelayLine anccestor class
inline void CBaseShellSend::PurgeItem (unsigned long )
{
  //## begin CBaseShellSend::PurgeItem%983336554.body preserve=yes
  //## end CBaseShellSend::PurgeItem%983336554.body
}

// Class CBaseShellReset 


//## Other Operations (inline)
//## Operation: PurgeItem%983336556; C++
//	Empty function required by DelayLine anccestor class
inline void CBaseShellReset::PurgeItem (unsigned long )
{
  //## begin CBaseShellReset::PurgeItem%983336556.body preserve=yes
  //## end CBaseShellReset::PurgeItem%983336556.body
}

// Class Utility BaseShellAnswer 

//## begin BaseShellAnswer::pFunc%3AC9610A03E4.attr preserve=no  private: static BaseShellAnswer::pfunctype [eMaxFuncIndex] {U} {GetNumAttributes, GetAttributeName, GetAttribute,  SetAttribute, GetNumResetAttributes, GetResetAttributeName, GetResetAttribute,  SetResetAttribute, Reset, Send, Create, GetNumInlets,  GetNumOutlets,  GetInletName,  GetOutletName,  GetNumInletConnectors,  GetNumOutletConnectors,  CanConnectInlet,  CanConnectOutlet,  GetInletConnector,  GetOutletConnector,  FindOutletConnectorIndex,  FindInletConnectorIndex,  SwapOutletConnector, GetNumObjectTypes, GetObjectType, CanHaveChildren, CanChangeSize, GetDefaultAttribute}
BaseShellAnswer::pfunctype  BaseShellAnswer::pFunc[eMaxFuncIndex] = {GetNumAttributes, GetAttributeName, GetAttribute,  SetAttribute, GetNumResetAttributes, GetResetAttributeName, GetResetAttribute,  SetResetAttribute, Reset, Send, Create, GetNumInlets,  GetNumOutlets,  GetInletName,  GetOutletName,  GetNumInletConnectors,  GetNumOutletConnectors,  CanConnectInlet,  CanConnectOutlet,  GetInletConnector,  GetOutletConnector,  FindOutletConnectorIndex,  FindInletConnectorIndex,  SwapOutletConnector, GetNumObjectTypes, GetObjectType, CanHaveChildren, CanChangeSize, GetDefaultAttribute};
//## end BaseShellAnswer::pFunc%3AC9610A03E4.attr

//## begin BaseShellAnswer::_BaseShellReset%3A99EA1402EA.role preserve=no  public: CBaseShellReset { -> 1VFHN}
CBaseShellReset BaseShellAnswer::_BaseShellReset;
//## end BaseShellAnswer::_BaseShellReset%3A99EA1402EA.role

//## begin BaseShellAnswer::<the_BaseShell>%3A9DA2940112.role preserve=no  public: BaseShell { -> RFHN}
//## end BaseShellAnswer::<the_BaseShell>%3A9DA2940112.role

//## begin BaseShellAnswer::_BaseShellSend%3A99E9A201E1.role preserve=no  public: CBaseShellSend { -> 1VFHN}
CBaseShellSend BaseShellAnswer::_BaseShellSend;
//## end BaseShellAnswer::_BaseShellSend%3A99E9A201E1.role


//## Other Operations (implementation)
//## Operation: GetNumAttributes%986253862
//	Gets the number of attributes for the P_IDENTITY
//	parameter.  The P_IDENTITY and Number of Attributes are
//	returned as parameters.  Returns the number of bytes in
//	ret buffer.
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned BaseShellAnswer::GetNumAttributes (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetNumAttributes%986253862.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned num_attributes = pBaseShell->GetNumAccess();
			SMUtility::IntToBuf ((short) num_attributes, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;
  //## end BaseShellAnswer::GetNumAttributes%986253862.body
}

//## Operation: GetAttributeName%986253863
//	Gets the name of the attribute defininded by the P_
//	IDENTITY and index  parameters.  The P_IDENTITY and
//	Attribute name are returned as parameters  Returns the
//	number of bytes in ret buffer
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
//	attribute_key
unsigned BaseShellAnswer::GetAttributeName (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetAttributeName%986253863.body preserve=yes
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;

  // force last char to me NULL
  answer[answer_size-1] = 0;


	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned attribute_key = SMUtility::BufToInt (&cursor);
			const char* name = pBaseShell->GetAccessName (attribute_key);
			if (name)
				{
					strncpy ((char*)answer, name, answer_size - 1);
					ret_bytes = strlen ((const char*)answer) + 1;
				}
		}

	return ret_bytes;
  //## end BaseShellAnswer::GetAttributeName%986253863.body
}

//## Operation: GetAttribute%986253855
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//	attribute_key
unsigned BaseShellAnswer::GetAttribute (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetAttribute%986253855.body preserve=yes
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned attribute_key = SMUtility::BufToInt (&cursor);
			if (pBaseShell->GetAttribute (attribute_key, (char*)answer, answer_size))
				{
					ret_bytes = strlen ((const char*)answer) + 1;
				}
		}
	return ret_bytes;
  //## end BaseShellAnswer::GetAttribute%986253855.body
}

//## Operation: SetAttribute%986253856
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//	attribute_key
//	new_value
unsigned BaseShellAnswer::SetAttribute (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::SetAttribute%986253856.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned attribute_key = SMUtility::BufToInt (&cursor);
			bool success = pBaseShell->SetAttribute (attribute_key, (const char*)cursor);

			SMUtility::IntToBuf ((short) (success?1:0), answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;
  //## end BaseShellAnswer::SetAttribute%986253856.body
}

//## Operation: GetNumResetAttributes%996206545
//	Gets the number of attributes for the P_IDENTITY
//	parameter.  The P_IDENTITY and Number of Attributes are
//	returned as parameters.  Returns the number of bytes in
//	ret buffer.
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned BaseShellAnswer::GetNumResetAttributes (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetNumResetAttributes%996206545.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned num_attributes = pBaseShell->GetNumResetAccess();
			SMUtility::IntToBuf ((short) num_attributes, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end BaseShellAnswer::GetNumResetAttributes%996206545.body
}

//## Operation: GetResetAttributeName%996206546
//	Gets the name of the attribute defininded by the P_
//	IDENTITY and index  parameters.  The P_IDENTITY and
//	Attribute name are returned as parameters  Returns the
//	number of bytes in ret buffer
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
//	attribute_key
unsigned BaseShellAnswer::GetResetAttributeName (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetResetAttributeName%996206546.body preserve=yes
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;

  // force last char to me NULL
  answer[answer_size-1] = 0;
  
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned attribute_key = SMUtility::BufToInt (&cursor);
			const char* name = pBaseShell->GetResetAccessName (attribute_key);
			if (name)
				{
					strncpy ((char*)answer, name, answer_size - 1);
					ret_bytes = strlen ((const char*)answer) + 1;
				}
		}
	return ret_bytes;
  //## end BaseShellAnswer::GetResetAttributeName%996206546.body
}

//## Operation: GetResetAttribute%996206547
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//	attribute_key
unsigned BaseShellAnswer::GetResetAttribute (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetResetAttribute%996206547.body preserve=yes
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned attribute_key = SMUtility::BufToInt (&cursor);
			if (pBaseShell->GetResetAttribute (attribute_key, (char*)answer, answer_size))
				{
					ret_bytes = strlen ((const char*)answer) + 1;
				}
		}
	return ret_bytes;
  //## end BaseShellAnswer::GetResetAttribute%996206547.body
}

//## Operation: SetResetAttribute%996206548
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//	attribute_key
//	new_value
unsigned BaseShellAnswer::SetResetAttribute (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::SetResetAttribute%996206548.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned attribute_key = SMUtility::BufToInt (&cursor);
			bool success = pBaseShell->SetResetAttribute (attribute_key, (const char*)cursor);

			SMUtility::IntToBuf ((short) (success?1:0), answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;
  //## end BaseShellAnswer::SetResetAttribute%996206548.body
}

//## Operation: Reset%983336530; C++
//	Resets the BaseShell object within context of scheduler.
//## Concurrency: Guarded
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
unsigned BaseShellAnswer::Reset (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::Reset%983336530.body preserve=yes
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			_BaseShellReset.Reset(pBaseShell);
		}
  UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);

	return 0;
  //## end BaseShellAnswer::Reset%983336530.body
}

//## Operation: Send%983336531; C++
//	Calls a Send message to the BaseShell object within the
//	context of the Scheduler
//## Concurrency: Guarded
//## Postconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
unsigned BaseShellAnswer::Send (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::Send%983336531.body preserve=yes
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			_BaseShellSend.Send(pBaseShell);
		}

  UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);
	return 0;

  //## end BaseShellAnswer::Send%983336531.body
}

//## Operation: Create%983336533; C++
//	Creates a BaseShell based upon the input type and P_
//	PATCH parent.
//## Preconditions:
//	question buf has the parameters as follows
//	type (strlen (type +1)
//	P_PATCH
unsigned BaseShellAnswer::Create (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::Create%983336533.body preserve=yes
	if (answer_size < sizeof (P_BASESHELL))
		{
			return 0;
		}

	const BYTE* cursor = question;
	const char* type = (const char*)cursor;
	cursor += strlen (type) + 1;
	Patch* pParent = PatchAnswer::GetPatch (&cursor);
	P_BASESHELL pObj;
	if (pParent)
		{
			pObj = TypeList::Create(type, pParent);
		}

	pObj.toBuf(answer);
	
	return sizeof (P_BASESHELL);
  //## end BaseShellAnswer::Create%983336533.body
}

//## Operation: GetNumInlets%983336536; C++
//	Returns the number of inlets a BaseShell Object has The
//	BaseShell is associated with the input parameter dwpShell
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
unsigned BaseShellAnswer::GetNumInlets (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetNumInlets%983336536.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned num = pBaseShell->GetNumInlets();
			SMUtility::IntToBuf ((short) num, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end BaseShellAnswer::GetNumInlets%983336536.body
}

//## Operation: GetNumOutlets%983336537; C++
//	Returns the number of Outlets a BaseShell Object has.
//	The BaseShell object is associated with the input
//	parameter dwpShell
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//## Postconditions:
//	The PatchEditor uses the interface to ask questions
//	about the internals of the engine
unsigned BaseShellAnswer::GetNumOutlets (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetNumOutlets%983336537.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned num = pBaseShell->GetNumOutlets();
			SMUtility::IntToBuf ((short) num, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end BaseShellAnswer::GetNumOutlets%983336537.body
}

//## Operation: GetInletName%983336538; C++
//	Returns the Name of the inlet of  BaseShell Object . The
//	BaseShell is defined by parameter dwpShell and the inlet
//	number by unsigned parameter SocketNumber
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//	socket_number
unsigned BaseShellAnswer::GetInletName (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetInletName%983336538.body preserve=yes
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;

  // force last char to me NULL
  answer[answer_size-1] = 0;
  
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned socket_num = SMUtility::BufToInt (&cursor);
			const char* name = pBaseShell->GetInletName (socket_num);
			if (name)
				{
					strncpy ((char*)answer, name, answer_size - 1);
					ret_bytes = strlen ((const char*)answer) + 1;
				}
		}
	return ret_bytes;

  //## end BaseShellAnswer::GetInletName%983336538.body
}

//## Operation: GetOutletName%983336539; C++
//	Returns the Name of the outlet of  BaseShell Object .
//	The BaseShell is defined by parameter dwpShell and the
//	outlet number by unsigned parameter SocketNumber
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//	socket_number
unsigned BaseShellAnswer::GetOutletName (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetOutletName%983336539.body preserve=yes
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;

  // force last char to me NULL
  answer[answer_size-1] = 0;
  
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned socket_num = SMUtility::BufToInt (&cursor);
			const char* name = pBaseShell->GetOutletName (socket_num);
			if (name)
				{
					strncpy ((char*)answer, name, answer_size - 1);
					ret_bytes = strlen ((const char*)answer) + 1;
				}
		}
	return ret_bytes;

  //## end BaseShellAnswer::GetOutletName%983336539.body
}

//## Operation: GetNumInletConnectors%983336540; C++
//	Returns the Number of connectors an inlet to a BaseShell
//	BaseShell Object has.  The BaseShell is defined by
//	parameter dwpShell and the inlet number by unsigned
//	parameter SocketNumber.
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//	socket_number
unsigned BaseShellAnswer::GetNumInletConnectors (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetNumInletConnectors%983336540.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned socket_num = SMUtility::BufToInt(&cursor);
			unsigned num = pBaseShell->GetNumInletConnectors(socket_num);
			SMUtility::IntToBuf ((short) num, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end BaseShellAnswer::GetNumInletConnectors%983336540.body
}

//## Operation: GetNumOutletConnectors%983336541; C++
//	Returns the Number of connectors an outllet to a Base
//	Shell BaseShell Object has.  The BaseShell is defined by
//	parameter dwpShell and the outlet number by unsigned
//	parameter SocketNumber.
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//	socket_number
unsigned BaseShellAnswer::GetNumOutletConnectors (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetNumOutletConnectors%983336541.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned socket_num = SMUtility::BufToInt(&cursor);
			unsigned num = pBaseShell->GetNumOutletConnectors(socket_num);
			SMUtility::IntToBuf ((short) num, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end BaseShellAnswer::GetNumOutletConnectors%983336541.body
}

//## Operation: CanConnectInlet%983336542; C++
//	Returns whether a Connector can connect to a BaseShell
//	object inlet. The BaseShell is defined by parameter dwp
//	Shell, the inlet number by unsigned parameter Socket
//	Number, and the Connector by dwpCon.
//## Preconditions:
//	Question Packed as
//
//	P_BASESHELL
//	wSocketNum
//	P_CONNECTOR
unsigned BaseShellAnswer::CanConnectInlet (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::CanConnectInlet%983336542.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	unsigned wSocketNum = SMUtility::BufToInt(&cursor);
	Connector* pCon = ConnectorAnswer::GetConnector (&cursor);
	if (pBaseShell)
		{
			bool can_connect = pBaseShell->CanConnectInlet(wSocketNum, pCon);
			SMUtility::IntToBuf ((short)(can_connect?1:0), answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;
  //## end BaseShellAnswer::CanConnectInlet%983336542.body
}

//## Operation: CanConnectOutlet%983336543; C++
//	Returns whether a Connector can connect to a BaseShell
//	object outlet. The BaseShell is defined by parameter dwp
//	Shell, the outlet number by unsigned parameter Socket
//	Number, and the Connector by dwpCon.
//## Preconditions:
//	Question Packed as
//
//	P_BASESHELL
//	wSocketNum
//	P_CONNECTOR
unsigned BaseShellAnswer::CanConnectOutlet (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::CanConnectOutlet%983336543.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	unsigned wSocketNum = SMUtility::BufToInt(&cursor);
	Connector* pCon = ConnectorAnswer::GetConnector (&cursor);
	if (pBaseShell)
		{
			bool can_connect = pBaseShell->CanConnectOutlet(wSocketNum, pCon);
			SMUtility::IntToBuf ((short)(can_connect?1:0), answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end BaseShellAnswer::CanConnectOutlet%983336543.body
}

//## Operation: GetInletConnector%983336544; C++
//	Returns the Connector that is attached to a BaseShell
//	object inlet at the specified index. The BaseShell is
//	defined by parameter dwpShell, the inlet number by
//	unsigned parameter SocketNumber, and the Connector index
//	by ConnectorNum .
//## Preconditions:
//	Question Packed as
//
//	P_BASESHELL
//	wSocketNum
//	index
unsigned BaseShellAnswer::GetInletConnector (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetInletConnector%983336544.body preserve=yes
	if (answer_size < sizeof (P_CONNECTOR))
		{
			return 0;
		}

	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned socket_num = SMUtility::BufToInt(&cursor);
			unsigned index = SMUtility::BufToInt(&cursor);
			P_CONNECTOR dwpCon (pBaseShell->GetInletConnector(socket_num, index));
			dwpCon.toBuf(answer);
		}

	return  sizeof(P_CONNECTOR);
  //## end BaseShellAnswer::GetInletConnector%983336544.body
}

//## Operation: GetOutletConnector%983336545; C++
//	Returns the Connector that is attached to a BaseShell
//	object outlet at the specified index. The BaseShell is
//	defined by parameter dwpShell, the outlet number by
//	unsigned parameter SocketNumber, and the Connector index
//	by ConnectorNum .
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//	socket_number
//	index
unsigned BaseShellAnswer::GetOutletConnector (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetOutletConnector%983336545.body preserve=yes
	if (answer_size < sizeof (P_CONNECTOR))
		{
			return 0;
		}

	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned socket_num = SMUtility::BufToInt(&cursor);
			unsigned index = SMUtility::BufToInt(&cursor);
			P_CONNECTOR dwpCon (pBaseShell->GetOutletConnector(socket_num, index));
			dwpCon.toBuf(answer);
		}

	return  sizeof(P_CONNECTOR);

  //## end BaseShellAnswer::GetOutletConnector%983336545.body
}

//## Operation: FindInletConnectorIndex%983336547; C++
//	Returns the Index that a Connector is associated with in
//	an Object's Inlet.
//## Preconditions:
//	Question Packed as
//
//	P_BASESHELL
//	wSocketNum
//	P_CONNECTOR
unsigned BaseShellAnswer::FindInletConnectorIndex (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::FindInletConnectorIndex%983336547.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}

	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned socket_num = SMUtility::BufToInt(&cursor);
      Connector* pCon = ConnectorAnswer::GetConnector (&cursor);
			unsigned index = pBaseShell->FindInletConnectorIndex(socket_num, pCon);
			SMUtility::IntToBuf((short)index, answer);
		}

	return  sizeof(short);

  //## end BaseShellAnswer::FindInletConnectorIndex%983336547.body
}

//## Operation: FindOutletConnectorIndex%983336546; C++
//	Returns the Index that a Connector is associated with in
//	an Object's Outlet.  This is used to determine the
//	sequence with with thie Connector is executed
//## Preconditions:
//	Question Packed as
//
//	P_BASESHELL
//	wSocketNum
//	P_CONNECTOR
unsigned BaseShellAnswer::FindOutletConnectorIndex (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::FindOutletConnectorIndex%983336546.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}

	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned socket_num = SMUtility::BufToInt(&cursor);
      Connector* pCon = ConnectorAnswer::GetConnector (&cursor);
			unsigned index = pBaseShell->FindOutletConnectorIndex(socket_num, pCon);
			SMUtility::IntToBuf((short)index, answer);
		}

	return  sizeof(short);
  //## end BaseShellAnswer::FindOutletConnectorIndex%983336546.body
}

//## Operation: SwapOutletConnector%983336548; C++
//	Swaps the position of two connectors within a BaseShell
//	object's outlet. This in turn affects the order at which
//	the two Connectors will be executed. The Object
//	parameter is dwpShell, the Outlet Number as socket_
//	number, and the two connector indexes are Con1_index and
//	Con2_index.
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//	outlet_number
//	outlet1_index
//	outlet2_index
unsigned BaseShellAnswer::SwapOutletConnector (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::SwapOutletConnector%983336548.body preserve=yes
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned outlet_number = SMUtility::BufToInt(&cursor);
			unsigned outlet1_index = SMUtility::BufToInt(&cursor);
			unsigned outlet2_index = SMUtility::BufToInt(&cursor);
			pBaseShell->SwapOutletConnector (outlet_number, outlet1_index, outlet2_index);
			UNREFERENCED_PARAMETER (answer);
			UNREFERENCED_PARAMETER (answer_size);
		}

	return 0;

  //## end BaseShellAnswer::SwapOutletConnector%983336548.body
}

//## Operation: GetBaseShell%983336549
//	Determines whether an BaseShellkey is valid by testing
//	the BYTE** buf If the key is Valid, a pointer to the Base
//	Shell associated with the cursor key is returned. buf
//	is incremented to one after the last byte.
BaseShell* BaseShellAnswer::GetBaseShell (const BYTE** buf)
{
  //## begin BaseShellAnswer::GetBaseShell%983336549.body preserve=yes
 	const BYTE* cursor = *buf;
	P_BASESHELL pId (&cursor);
	*buf = cursor;
	return (BaseShell*) IdentityAnswer::GetIdentity (pId);
  //## end BaseShellAnswer::GetBaseShell%983336549.body
}

//## Operation: PerformOperation%985819706
//	Public function by which all answers are derived.  The
//	member function index is the first byte in the question
//	parameter. After the index is obtained, the appropriate
//	member function is called.
unsigned BaseShellAnswer::PerformOperation (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::PerformOperation%985819706.body preserve=yes
	unsigned ret_bytes = 0;

	// deal with the question
	const BYTE* q_cursor = question;
	unsigned func_index = (unsigned)SMUtility::BufToTargetFunc (&q_cursor);


	if (func_index < eMaxFuncIndex)
		{
			ret_bytes += (pFunc[func_index]) (q_cursor, answer, answer_size);
		}
	return ret_bytes;
  //## end BaseShellAnswer::PerformOperation%985819706.body
}

//## Operation: GetNumObjectTypes%1048126421; C++
//	Gets the Number of Object Types
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//	outlet_number
//	outlet1_index
//	outlet2_index
unsigned BaseShellAnswer::GetNumObjectTypes (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetNumObjectTypes%1048126421.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}

	unsigned ret_bytes ;
  unsigned num_attributes = BaseShell::GetNumObjectTypes();
  SMUtility::IntToBuf ((short) num_attributes, answer);
  ret_bytes = sizeof(short);

  UNREFERENCED_PARAMETER(question);
	return ret_bytes;

  //## end BaseShellAnswer::GetNumObjectTypes%1048126421.body
}

//## Operation: GetObjectType%1048126422
//	Gets the name of the Object type defined by index
//	parameters.  The  Objectname is returned as parameters
//## Postconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//	attribute_key
unsigned BaseShellAnswer::GetObjectType (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetObjectType%1048126422.body preserve=yes
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;

  // force last char to me NULL
  answer[answer_size-1] = 0;


  unsigned attribute_key = SMUtility::BufToInt (&cursor);
  const char* name = BaseShell::GetObjectType (attribute_key);
  if (name)
    {
      strncpy ((char*)answer, name, answer_size - 1);
      ret_bytes = strlen ((const char*)answer) + 1;
    }

	return ret_bytes;


  //## end BaseShellAnswer::GetObjectType%1048126422.body
}

//## Operation: CanHaveChildren%1048130622; C++
//	Returns true if The Object Type can have children
//## Postconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned BaseShellAnswer::CanHaveChildren (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::CanHaveChildren%1048130622.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned num_attributes = pBaseShell->CanHaveChildren();
			SMUtility::IntToBuf ((short) num_attributes, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end BaseShellAnswer::CanHaveChildren%1048130622.body
}

//## Operation: CanChangeSize%1048130623; C++
//	Returns true if The Object Type can change the number of
//	Inlets or Outlets it has
//## Postconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned BaseShellAnswer::CanChangeSize (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::CanChangeSize%1048130623.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			unsigned num_attributes = pBaseShell->CanChangeSize();
			SMUtility::IntToBuf ((short) num_attributes, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end BaseShellAnswer::CanChangeSize%1048130623.body
}

//## Operation: GetDefaultAttribute%1051589360
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
//	attribute_key
unsigned BaseShellAnswer::GetDefaultAttribute (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin BaseShellAnswer::GetDefaultAttribute%1051589360.body preserve=yes
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	BaseShell* pBaseShell = GetBaseShell (&cursor);
	if (pBaseShell)
		{
			if (pBaseShell->GetDefaultAttribute ((char*)answer, answer_size))
				{
					ret_bytes = strlen ((const char*)answer) + 1;
				}
		}
	return ret_bytes;

  //## end BaseShellAnswer::GetDefaultAttribute%1051589360.body
}

// Additional Declarations
  //## begin BaseShellAnswer%3A99D21A0030.declarations preserve=yes
  //## end BaseShellAnswer%3A99D21A0030.declarations

// Class CBaseShellSend 



CBaseShellSend::CBaseShellSend()
  //## begin CBaseShellSend::CBaseShellSend%.hasinit preserve=no
  //## end CBaseShellSend::CBaseShellSend%.hasinit
  //## begin CBaseShellSend::CBaseShellSend%.initialization preserve=yes
  //## end CBaseShellSend::CBaseShellSend%.initialization
{
  //## begin CBaseShellSend::CBaseShellSend%.body preserve=yes
  //## end CBaseShellSend::CBaseShellSend%.body
}


CBaseShellSend::~CBaseShellSend()
{
  //## begin CBaseShellSend::~CBaseShellSend%.body preserve=yes
  //## end CBaseShellSend::~CBaseShellSend%.body
}



//## Other Operations (implementation)
//## Operation: Send%982978159
//	Sends a request message to the Scheduler. Returns true
//	if request was successful
bool CBaseShellSend::Send (BaseShell* receiver)
{
  //## begin CBaseShellSend::Send%982978159.body preserve=yes
  bool ret = false;

  if (hal_include::Scheduler::LockEngine ())
  {
    ret = GoOneShot ((DWORD)receiver);
    hal_include::Scheduler::UnlockEngine ();
  }
  return ret;
  //## end CBaseShellSend::Send%982978159.body
}

//## Operation: OutputFunction%982978160; C++
void CBaseShellSend::OutputFunction (DWORD receiver)
{
  BaseShell* pShell = (BaseShell*)receiver;
  pShell->DoDefaultAction();

  //## begin CBaseShellSend::OutputFunction%982978160.body preserve=yes
  //## end CBaseShellSend::OutputFunction%982978160.body
}

// Additional Declarations
  //## begin CBaseShellSend%3A970A970173.declarations preserve=yes
  //## end CBaseShellSend%3A970A970173.declarations

// Class CBaseShellReset 



CBaseShellReset::CBaseShellReset()
  //## begin CBaseShellReset::CBaseShellReset%.hasinit preserve=no
  //## end CBaseShellReset::CBaseShellReset%.hasinit
  //## begin CBaseShellReset::CBaseShellReset%.initialization preserve=yes
  //## end CBaseShellReset::CBaseShellReset%.initialization
{
  //## begin CBaseShellReset::CBaseShellReset%.body preserve=yes
  //## end CBaseShellReset::CBaseShellReset%.body
}


CBaseShellReset::~CBaseShellReset()
{
  //## begin CBaseShellReset::~CBaseShellReset%.body preserve=yes
  //## end CBaseShellReset::~CBaseShellReset%.body
}



//## Other Operations (implementation)
//## Operation: Reset%983336509
//	Sends a request message to the Scheduler. Rteurns true
//	if request was successful
bool CBaseShellReset::Reset (BaseShell* receiver)
{
  //## begin CBaseShellReset::Reset%983336509.body preserve=yes
  bool ret = false;

  if (hal_include::Scheduler::LockEngine ())
  {
    ret = GoOneShot ((DWORD)receiver);
    hal_include::Scheduler::UnlockEngine ();
  }
  return ret;
  
  //## end CBaseShellReset::Reset%983336509.body
}

//## Operation: OutputFunction%983336510; C++
void CBaseShellReset::OutputFunction (DWORD receiver)
{
  BaseShell* pShell = (BaseShell*)receiver;
  pShell->Reset ();

  //## begin CBaseShellReset::OutputFunction%983336510.body preserve=yes
  //## end CBaseShellReset::OutputFunction%983336510.body
}

// Additional Declarations
  //## begin CBaseShellReset%3A99A4C90256.declarations preserve=yes
  //## end CBaseShellReset%3A99A4C90256.declarations

//## begin module%3ACAB0AA02AA.epilog preserve=yes
//## end module%3ACAB0AA02AA.epilog
