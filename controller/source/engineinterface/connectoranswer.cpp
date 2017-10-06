//## begin module%3ACAB17602E0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ACAB17602E0.cm

//## begin module%3ACAB17602E0.cp preserve=no
//	Angelo Fraietta
//## end module%3ACAB17602E0.cp

//## Module: ConnectorAnswer%3ACAB17602E0; Package body
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\connectoranswer.cpp

//## begin module%3ACAB17602E0.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3ACAB17602E0.additionalIncludes

//## begin module%3ACAB17602E0.includes preserve=yes
#include <string.h>
#include "identityanswer.h"
//## end module%3ACAB17602E0.includes

// ConnectorAnswer
#include "connectoranswer.h"
// BaseShellAnswer
#include "baseshellanswer.h"
//## begin module%3ACAB17602E0.declarations preserve=no
//## end module%3ACAB17602E0.declarations

//## begin module%3ACAB17602E0.additionalDeclarations preserve=yes
#include "control.h"
//## end module%3ACAB17602E0.additionalDeclarations


// Class Utility ConnectorAnswer 

//## begin ConnectorAnswer::pFunc%3ADFBC0502FA.attr preserve=no  private: static ConnectorAnswer::pfunctype [eMaxFuncIndex] {U} {IsValid, GetInletBase, GetOutletBase, GetInletNum,  GetOutletNum,  GetOutletIndex,  SetInletBase,  SetInletNum,  SetOutletBase,  SetOutletNum,  MakeConnection,  Create,  Destroy}
ConnectorAnswer::pfunctype  ConnectorAnswer::pFunc[eMaxFuncIndex] = {IsValid, GetInletBase, GetOutletBase, GetInletNum,  GetOutletNum,  GetOutletIndex,  SetInletBase,  SetInletNum,  SetOutletBase,  SetOutletNum,  MakeConnection,  Create,  Destroy};
//## end ConnectorAnswer::pFunc%3ADFBC0502FA.attr


//## Other Operations (implementation)
//## Operation: IsValid%983336511; C++
//	Returns whether a Connector has a complete set of valid
//	connections.
unsigned ConnectorAnswer::IsValid (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::IsValid%983336511.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Connector* pCon = GetConnector (&cursor);
	if (pCon)
		{
			unsigned modified = (!!(*pCon))?1:0; // check if is valid
			SMUtility::IntToBuf ((short) modified, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end ConnectorAnswer::IsValid%983336511.body
}

//## Operation: GetInletBase%983336512; C++
//	Returns the BaseShell pointed to at the Connectors Inlet.
unsigned ConnectorAnswer::GetInletBase (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::GetInletBase%983336512.body preserve=yes
	if (answer_size < sizeof (P_BASESHELL))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Connector* pCon = GetConnector (&cursor);
	if (pCon)
		{
			P_BASESHELL pShell (pCon->GetInletBase());
			pShell.toBuf (answer);
			ret_bytes = sizeof(P_BASESHELL);
		}
	return ret_bytes;

  //## end ConnectorAnswer::GetInletBase%983336512.body
}

//## Operation: GetInletNum%983336513; C++
//	Returns the Inlet Number of the Connector.
unsigned ConnectorAnswer::GetInletNum (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::GetInletNum%983336513.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Connector* pCon = GetConnector (&cursor);
	if (pCon)
		{
			unsigned ret = pCon->GetInletNum();
			SMUtility::IntToBuf ((short)ret, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end ConnectorAnswer::GetInletNum%983336513.body
}

//## Operation: GetOutletBase%983336514; C++
//	Returns the BaseShell pointed to at the Connectors
//	Outlet.
unsigned ConnectorAnswer::GetOutletBase (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::GetOutletBase%983336514.body preserve=yes
	if (answer_size < sizeof (P_BASESHELL))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Connector* pCon = GetConnector (&cursor);
	if (pCon)
		{
			P_BASESHELL pShell (pCon->GetOutletBase());
			pShell.toBuf (answer);
			ret_bytes = sizeof(P_BASESHELL);
		}
	return ret_bytes;

  //## end ConnectorAnswer::GetOutletBase%983336514.body
}

//## Operation: GetOutletNum%983336515; C++
//	Returns the Outlet Number of the Connector.
unsigned ConnectorAnswer::GetOutletNum (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::GetOutletNum%983336515.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Connector* pCon = GetConnector (&cursor);
	if (pCon)
		{
			unsigned ret = pCon->GetOutletNum();
			SMUtility::IntToBuf ((short)ret, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end ConnectorAnswer::GetOutletNum%983336515.body
}

//## Operation: GetOutletIndex%983336516; C++
//	Returns the Index that the Connector is at its Base
//	Shell's Outlet
unsigned ConnectorAnswer::GetOutletIndex (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::GetOutletIndex%983336516.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Connector* pCon = GetConnector (&cursor);
	if (pCon)
		{
      const SocketDetails Connection = pCon->OutletDetails();
      
      if (Connection.pBase)
				{
					unsigned ret = Connection.pBase ->FindOutletConnectorIndex(Connection.wSocketNumber, pCon);
					
					SMUtility::IntToBuf ((short)ret, answer);
					ret_bytes = sizeof(short);
				}
		}
	return ret_bytes;

  //## end ConnectorAnswer::GetOutletIndex%983336516.body
}

//## Operation: SetInletBase%983336518; C++
//	Sets the BaseShell associated with Connector Inlet.
unsigned ConnectorAnswer::SetInletBase (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::SetInletBase%983336518.body preserve=yes

	const BYTE* cursor = question;
	Connector* pCon = GetConnector (&cursor);
	if (pCon)
		{
			BaseShell* pShell = BaseShellAnswer::GetBaseShell (&cursor);
			pCon->SetInletBase(pShell);
		}

  UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);

	return 0;

  //## end ConnectorAnswer::SetInletBase%983336518.body
}

//## Operation: SetInletNum%983336519; C++
//	Sets the SocketNumber associated with Connector Inlet.
unsigned ConnectorAnswer::SetInletNum (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::SetInletNum%983336519.body preserve=yes

	const BYTE* cursor = question;
	Connector* pCon = GetConnector (&cursor);
	if (pCon)
		{
			unsigned socketNum = SMUtility::BufToInt (&cursor);
			pCon->SetInletNum(socketNum);
		}

  UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);

	return 0;

  //## end ConnectorAnswer::SetInletNum%983336519.body
}

//## Operation: SetOutletBase%983336520; C++
//	Sets the BaseShell associated with Connector Outlet.
unsigned ConnectorAnswer::SetOutletBase (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::SetOutletBase%983336520.body preserve=yes

	const BYTE* cursor = question;
	Connector* pCon = GetConnector (&cursor);
	if (pCon)
		{
			BaseShell* pShell = BaseShellAnswer::GetBaseShell (&cursor);
			pCon->SetOutletBase(pShell);
		}

  UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);

	return 0;

  //## end ConnectorAnswer::SetOutletBase%983336520.body
}

//## Operation: SetOutletNum%983336521; C++
//	Sets the SocketNumber associated with Connector Outlet.
unsigned ConnectorAnswer::SetOutletNum (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::SetOutletNum%983336521.body preserve=yes

	const BYTE* cursor = question;
	Connector* pCon = GetConnector (&cursor);
	if (pCon)
		{
			unsigned socketNum = SMUtility::BufToInt (&cursor);
			pCon->SetOutletNum(socketNum);
		}

  UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);

	return 0;

  //## end ConnectorAnswer::SetOutletNum%983336521.body
}

//## Operation: MakeConnection%983336522; C++
//	Attempts to make the Connection between the Inlet and
//	the Outlet.
unsigned ConnectorAnswer::MakeConnection (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::MakeConnection%983336522.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Connector* pCon = GetConnector (&cursor);
	if (pCon)
		{
			bool success = pCon->ConnectToInlet() && pCon->ConnectToOutlet();

			SMUtility::IntToBuf ((short)(success?1:0), answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end ConnectorAnswer::MakeConnection%983336522.body
}

//## Operation: Create%983336524; C++
//	Creates a free Connector, with no Inlet or outlet
//	associations.
unsigned ConnectorAnswer::Create (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::Create%983336524.body preserve=yes
	if (answer_size < sizeof (P_CONNECTOR))
		{
			return 0;
		}
	
	P_CONNECTOR dwpCon (new Connector());
	dwpCon.toBuf (answer);
	
	UNREFERENCED_PARAMETER (question);

	return sizeof (P_CONNECTOR);

  //## end ConnectorAnswer::Create%983336524.body
}

//## Operation: Destroy%983336525; C++
//	Deletes a Connector.
unsigned ConnectorAnswer::Destroy (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::Destroy%983336525.body preserve=yes
	const BYTE* cursor = question;
	Connector* pCon = GetConnector (&cursor);
	if (pCon)
		{
			delete pCon;
		}

  UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);
	return 0;
  //## end ConnectorAnswer::Destroy%983336525.body
}

//## Operation: GetConnector%983336527
//	Determines whether a Connector key is valid by testing
//	the dwpCon. If the dwpCon is Valid, a pointer to the
//	Connector associated with the dwpCon key is returned.
Connector* ConnectorAnswer::GetConnector (const BYTE** buf)
{
  //## begin ConnectorAnswer::GetConnector%983336527.body preserve=yes
 	const BYTE* cursor = *buf;
	P_CONNECTOR pId (&cursor);
	*buf = cursor;
	return (Connector*) IdentityAnswer::GetIdentity (pId);

  //## end ConnectorAnswer::GetConnector%983336527.body
}

//## Operation: PerformOperation%985819707
//	Public function by which all answers are derived.  The
//	member function index is the first byte in the question
//	parameter. After the index is obtained, the appropriate
//	member function is called.
unsigned ConnectorAnswer::PerformOperation (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ConnectorAnswer::PerformOperation%985819707.body preserve=yes
	unsigned ret_bytes = 0;

	// deal with the question
	const BYTE* q_cursor = question;
	unsigned func_index = (unsigned)SMUtility::BufToTargetFunc (&q_cursor);


	if (func_index < eMaxFuncIndex)
		{
			ret_bytes += (pFunc[func_index]) (q_cursor, answer, answer_size);
		}
	return ret_bytes;

  //## end ConnectorAnswer::PerformOperation%985819707.body
}

// Additional Declarations
  //## begin ConnectorAnswer%3A999736037B.declarations preserve=yes
  //## end ConnectorAnswer%3A999736037B.declarations

//## begin module%3ACAB17602E0.epilog preserve=yes
//## end module%3ACAB17602E0.epilog
