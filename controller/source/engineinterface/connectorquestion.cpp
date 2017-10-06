//## begin module%3AC3DEEB0283.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AC3DEEB0283.cm

//## begin module%3AC3DEEB0283.cp preserve=no
//	Angelo Fraietta
//## end module%3AC3DEEB0283.cp

//## Module: ConnectorQuestion%3AC3DEEB0283; Package body
//	Connector Question and answer
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\connectorquestion.cpp

//## begin module%3AC3DEEB0283.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3AC3DEEB0283.additionalIncludes

//## begin module%3AC3DEEB0283.includes preserve=yes
#include "smutility.h"
#include "typedefs.h"
#include "interfacetypes.h"

//## end module%3AC3DEEB0283.includes

// ConnectorQuestion
#include "connectorquestion.h"
// PresentationQuestion
#include "presentationquestion.h"
// ConnectorAnswer
#include "connectoranswer.h"
// PresentationAnswer
#include "presentationanswer.h"


//## begin module%3AC3DEEB0283.declarations preserve=no
//## end module%3AC3DEEB0283.declarations

//## begin module%3AC3DEEB0283.additionalDeclarations preserve=yes
//## end module%3AC3DEEB0283.additionalDeclarations


// Class Utility ConnectorQuestion 


//## Other Operations (implementation)
//## Operation: IsValid%767826064; C++
bool ConnectorQuestion::IsValid (PresentationQuestion* pQuestion, P_CONNECTOR dwpCon)
{
  //## begin ConnectorQuestion::IsValid%767826064.body preserve=yes
	bool ret = false;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // 
		+ sizeof (P_CONNECTOR); // dwpCon
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ConnectorAnswer::eIsValid, cursor);
	dwpCon.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eConnector, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return (ret);
  //## end ConnectorQuestion::IsValid%767826064.body
}

//## Operation: Create%777073519; C++
P_CONNECTOR ConnectorQuestion::Create (PresentationQuestion* pQuestion)
{
  //## begin ConnectorQuestion::Create%777073519.body preserve=yes
	P_CONNECTOR ret;	
	const unsigned question_size =  SMUtility::TargetFuncBufSize(); // target func
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(P_CONNECTOR)];

	// fill question
	 SMUtility::TargetFuncToBuf (ConnectorAnswer::eCreate, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eConnector, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = P_CONNECTOR (&a_cursor);
		}
	delete [] question;
	return ret;

  //## end ConnectorQuestion::Create%777073519.body
}

//## Operation: Delete%1310936690; C++
void ConnectorQuestion::Delete (PresentationQuestion* pQuestion, P_CONNECTOR dwpCon)
{
  //## begin ConnectorQuestion::Delete%1310936690.body preserve=yes

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // eGetNumAttributes
		+ sizeof (P_CONNECTOR); // dwpCon
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ConnectorAnswer::eDestroy, cursor);
	dwpCon.toBuf(cursor);

	//get the answer
	pQuestion->AskQuestion (PresentationAnswer::eConnector, question, question_size, NULL, 0);

	delete [] question;

  //## end ConnectorQuestion::Delete%1310936690.body
}

//## Operation: SetOutletNum%-698908714; C++
void ConnectorQuestion::SetOutletNum (PresentationQuestion* pQuestion, P_CONNECTOR dwpCon, unsigned int wSocketNum)
{
  //## begin ConnectorQuestion::SetOutletNum%-698908714.body preserve=yes
	
	const unsigned question_size =  SMUtility::TargetFuncBufSize() // Target Function index
		+ sizeof (P_CONNECTOR) // pwpCon
		+ sizeof (short); // socket nmum
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ConnectorAnswer::eSetOutletNum, cursor);
	cursor = dwpCon.toBuf(cursor);
	SMUtility::IntToBuf((short)wSocketNum, cursor);

	//get the answer
	pQuestion->AskQuestion (PresentationAnswer::eConnector, question, question_size, NULL, 0);
	
  //## end ConnectorQuestion::SetOutletNum%-698908714.body
}

//## Operation: SetOutletBase%-1335169627; C++
void ConnectorQuestion::SetOutletBase (PresentationQuestion* pQuestion, P_CONNECTOR dwpCon, P_BASESHELL dwpShell)
{
  //## begin ConnectorQuestion::SetOutletBase%-1335169627.body preserve=yes

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // Target Function index
		+ sizeof (P_CONNECTOR) // pwpCon
		+ sizeof (P_BASESHELL); // dwpShell
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ConnectorAnswer::eSetOutletBase, cursor);
	cursor = dwpCon.toBuf(cursor);
	dwpShell.toBuf(cursor);

	//get the answer
	pQuestion->AskQuestion (PresentationAnswer::eConnector, question, question_size, NULL, 0);
  //## end ConnectorQuestion::SetOutletBase%-1335169627.body
}

//## Operation: SetInletNum%-2101368277; C++
void ConnectorQuestion::SetInletNum (PresentationQuestion* pQuestion, P_CONNECTOR dwpCon, unsigned int wSocketNum)
{
  //## begin ConnectorQuestion::SetInletNum%-2101368277.body preserve=yes

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // Target Function index
		+ sizeof (P_CONNECTOR) // pwpCon
		+ sizeof (short); // socket nmum
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ConnectorAnswer::eSetInletNum, cursor);
	cursor = dwpCon.toBuf(cursor);
	SMUtility::IntToBuf((short)wSocketNum, cursor);

	//get the answer
	pQuestion->AskQuestion (PresentationAnswer::eConnector, question, question_size, NULL, 0);
	
  //## end ConnectorQuestion::SetInletNum%-2101368277.body
}

//## Operation: SetInletBase%251329370; C++
void ConnectorQuestion::SetInletBase (PresentationQuestion* pQuestion, P_CONNECTOR dwpCon, P_BASESHELL dwpShell)
{
  //## begin ConnectorQuestion::SetInletBase%251329370.body preserve=yes

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // Target Function index
		+ sizeof (P_CONNECTOR) // pwpCon
		+ sizeof (P_BASESHELL); // dwpShell
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ConnectorAnswer::eSetInletBase, cursor);
	cursor = dwpCon.toBuf(cursor);
	dwpShell.toBuf(cursor);

	//get the answer
	pQuestion->AskQuestion (PresentationAnswer::eConnector, question, question_size, NULL, 0);

  //## end ConnectorQuestion::SetInletBase%251329370.body
}

//## Operation: MakeConnection%-1151122548; C++
bool ConnectorQuestion::MakeConnection (PresentationQuestion* pQuestion, P_CONNECTOR dwpCon)
{
  //## begin ConnectorQuestion::MakeConnection%-1151122548.body preserve=yes
	bool ret = false;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // 
		+ sizeof (P_CONNECTOR); // dwpCon
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ConnectorAnswer::eMakeConnection, cursor);
	dwpCon.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eConnector, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return (ret);

  //## end ConnectorQuestion::MakeConnection%-1151122548.body
}

//## Operation: GetOutletNum%2017325574; C++
unsigned ConnectorQuestion::GetOutletNum (PresentationQuestion* pQuestion, P_CONNECTOR dwpCon)
{
  //## begin ConnectorQuestion::GetOutletNum%2017325574.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // 
		+ sizeof (P_CONNECTOR); // dwpCon
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ConnectorAnswer::eGetOutletNum, cursor);
	dwpCon.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eConnector, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;

  //## end ConnectorQuestion::GetOutletNum%2017325574.body
}

//## Operation: GetOutletIndex%-456492498; C++
unsigned ConnectorQuestion::GetOutletIndex (PresentationQuestion* pQuestion, P_CONNECTOR dwpCon)
{
  //## begin ConnectorQuestion::GetOutletIndex%-456492498.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // 
		+ sizeof (P_CONNECTOR); // dwpCon
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ConnectorAnswer::eGetOutletIndex, cursor);
	dwpCon.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eConnector, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;
  //## end ConnectorQuestion::GetOutletIndex%-456492498.body
}

//## Operation: GetInletNum%-1763345739; C++
unsigned ConnectorQuestion::GetInletNum (PresentationQuestion* pQuestion, P_CONNECTOR dwpCon)
{
  //## begin ConnectorQuestion::GetInletNum%-1763345739.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // 
		+ sizeof (P_CONNECTOR); // dwpCon
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ConnectorAnswer::eGetInletNum, cursor);
	dwpCon.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eConnector, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;
  //## end ConnectorQuestion::GetInletNum%-1763345739.body
}

//## Operation: GetOutletBase%-166014066; C++
P_BASESHELL ConnectorQuestion::GetOutletBase (PresentationQuestion* pQuestion, P_CONNECTOR dwpCon)
{
  //## begin ConnectorQuestion::GetOutletBase%-166014066.body preserve=yes
	P_BASESHELL ret;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // 
		+ sizeof (P_CONNECTOR); // dwpCon
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(P_BASESHELL)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ConnectorAnswer::eGetOutletBase, cursor);
	dwpCon.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eConnector, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = P_BASESHELL (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;

  //## end ConnectorQuestion::GetOutletBase%-166014066.body
}

//## Operation: GetInletBase%-959579559; C++
P_BASESHELL ConnectorQuestion::GetInletBase (PresentationQuestion* pQuestion, P_CONNECTOR dwpCon)
{
  //## begin ConnectorQuestion::GetInletBase%-959579559.body preserve=yes
	P_BASESHELL ret;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // 
		+ sizeof (P_CONNECTOR); // dwpCon
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(P_BASESHELL)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ConnectorAnswer::eGetInletBase, cursor);
	dwpCon.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eConnector, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = P_BASESHELL (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;
  //## end ConnectorQuestion::GetInletBase%-959579559.body
}

// Additional Declarations
  //## begin ConnectorQuestion%3A9AC6B103AE.declarations preserve=yes
  //## end ConnectorQuestion%3A9AC6B103AE.declarations

//## begin module%3AC3DEEB0283.epilog preserve=yes
//## end module%3AC3DEEB0283.epilog
