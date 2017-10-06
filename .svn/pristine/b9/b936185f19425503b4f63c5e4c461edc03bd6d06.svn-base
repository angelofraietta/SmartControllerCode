//## begin module%3D3359940267.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D3359940267.cm

//## begin module%3D3359940267.cp preserve=no
//	Angelo Fraietta
//## end module%3D3359940267.cp

//## Module: ViewQuestion%3D3359940267; Package body
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\viewquestion.cpp

//## begin module%3D3359940267.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3D3359940267.additionalIncludes

//## begin module%3D3359940267.includes preserve=yes
#include "typedefs.h"
#include "interfacetypes.h"
#include "smutility.h"
#include "dllinterface.h"

//## end module%3D3359940267.includes

// PresentationAnswer
#include "presentationanswer.h"
// ViewAnswer
#include "viewanswer.h"
// ViewQuestion
#include "viewquestion.h"
// PresentationQuestion
#include "presentationquestion.h"


//## begin module%3D3359940267.declarations preserve=no
//## end module%3D3359940267.declarations

//## begin module%3D3359940267.additionalDeclarations preserve=yes
//## end module%3D3359940267.additionalDeclarations


// Class Utility ViewQuestion 


//## Other Operations (implementation)
//## Operation: GetNumViews%1026777700
unsigned ViewQuestion::GetNumViews (PresentationQuestion* pQuestion, P_PATCH dwpPatch)
{
  //## begin ViewQuestion::GetNumViews%1026777700.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH); // dwpPatch

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eGetNumViews, cursor);
	dwpPatch.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;

  //## end ViewQuestion::GetNumViews%1026777700.body
}

//## Operation: GetNumViewObjects%1026777701
unsigned ViewQuestion::GetNumViewObjects (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum)
{
  //## begin ViewQuestion::GetNumViewObjects%1026777701.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH) // dwpPatch
    + sizeof(short); // viewNum

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eGetNumViewObjects, cursor);
	cursor = dwpPatch.toBuf(cursor);
  SMUtility::IntToBuf((short)viewNum, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;

  //## end ViewQuestion::GetNumViewObjects%1026777701.body
}

//## Operation: GetViewObject%1026777702
P_BASESHELL ViewQuestion::GetViewObject (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum, unsigned objectNum)
{
  //## begin ViewQuestion::GetViewObject%1026777702.body preserve=yes
	P_BASESHELL ret;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH) // dwpPatch
    + sizeof(short) // viewNum
    + sizeof(short); // objectNum

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(P_BASESHELL)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eGetViewObject, cursor);
	cursor = dwpPatch.toBuf(cursor);
  cursor = SMUtility::IntToBuf((short)viewNum, cursor);
  SMUtility::IntToBuf((short)objectNum, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = P_BASESHELL (&a_cursor);
		}
	delete [] question;
	return ret;

  //## end ViewQuestion::GetViewObject%1026777702.body
}

//## Operation: GetViewObjectDisplayParams%1026777703
//	Returns the display parameters of the object, being, P_
//	Basehell, top, left, height, width, and tag
bool ViewQuestion::GetViewObjectDisplayParams (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum, unsigned objectNum, P_BASESHELL* pObject, unsigned* top, unsigned* left, unsigned* height, unsigned* width, unsigned* tag)
{
  //## begin ViewQuestion::GetViewObjectDisplayParams%1026777703.body preserve=yes
  bool ret = false;
  
	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH) // dwpPatch
    + sizeof(short) // viewNum
    + sizeof(short); // objectNum

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(P_BASESHELL) + sizeof(short) * 5];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eGetViewObjectDisplayParams, cursor);
	cursor = dwpPatch.toBuf(cursor);
  cursor = SMUtility::IntToBuf((short)viewNum, cursor);
  SMUtility::IntToBuf((short)objectNum, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			*pObject = P_BASESHELL (&a_cursor);
      *top = SMUtility::BufToInt (&a_cursor);
      *left = SMUtility::BufToInt (&a_cursor);
      *height = SMUtility::BufToInt (&a_cursor);
      *width = SMUtility::BufToInt (&a_cursor);
      *tag = SMUtility::BufToInt (&a_cursor);
      ret = true;
		}
	delete [] question;
	return ret;

  //## end ViewQuestion::GetViewObjectDisplayParams%1026777703.body
}

//## Operation: AddViewObject%1026777704
//	Adds the display parameters of the object, being, p
//	Basehell, top, left, height, width, and tag
bool ViewQuestion::AddViewObject (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum, P_BASESHELL pObject, unsigned top, unsigned left, unsigned height, unsigned width, unsigned tag)
{
  //## begin ViewQuestion::AddViewObject%1026777704.body preserve=yes
	bool ret = false;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH) // dwpPatch
    + sizeof(short) // viewNum
    + sizeof(P_BASESHELL) // pObject
    + sizeof(short) * 5; //params

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eAddViewObject, cursor);
	cursor = dwpPatch.toBuf(cursor);
  cursor = SMUtility::IntToBuf((short)viewNum, cursor);
  cursor = pObject.toBuf(cursor);

  cursor = SMUtility::IntToBuf((short)top, cursor);
  cursor = SMUtility::IntToBuf((short)left, cursor);
  cursor = SMUtility::IntToBuf((short)height, cursor);
  cursor = SMUtility::IntToBuf((short)width, cursor);
  SMUtility::IntToBuf((short)tag, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			ret = true;
		}
    
	delete [] question;
	return ret;

  //## end ViewQuestion::AddViewObject%1026777704.body
}

//## Operation: ClearView%1026777705
//	Clears View
bool ViewQuestion::ClearView (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum)
{
  //## begin ViewQuestion::ClearView%1026777705.body preserve=yes
	bool ret = false;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH) // dwpPatch
    + sizeof(short); // viewNum

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eClearView, cursor);
	cursor = dwpPatch.toBuf(cursor);
  SMUtility::IntToBuf((short)viewNum, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			ret = true;
		}

	delete [] question;
	return ret;

  //## end ViewQuestion::ClearView%1026777705.body
}

//## Operation: GetViewName%1026777708
bool ViewQuestion::GetViewName (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum, char* ret_name, unsigned buf_len)
{
  //## begin ViewQuestion::GetViewName%1026777708.body preserve=yes
	bool success;
	const unsigned question_size = SMUtility::TargetFuncBufSize() // Target Function index
		+ sizeof (P_PATCH) // dwpPatch
    + sizeof(short); // viewNum

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE* answer  = (BYTE*) ret_name;


	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eGetViewName, cursor);
	cursor = dwpPatch.toBuf(cursor);
  SMUtility::IntToBuf((short)viewNum, cursor);
  
	//get the answer
	success = pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, buf_len);

	delete[] question;
	if (!success)
    {
      *ret_name = '\0';
    }

  return success;
  //## end ViewQuestion::GetViewName%1026777708.body
}

//## Operation: SetViewName%1026777709
bool ViewQuestion::SetViewName (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum, const char* name)
{
  //## begin ViewQuestion::SetViewName%1026777709.body preserve=yes
  bool ret;

  const unsigned name_len =  strlen (name) + 1;
	const unsigned question_size = SMUtility::TargetFuncBufSize()
  	+ sizeof(P_PATCH)
    + sizeof(short) // view num
		+ name_len;                             
          
	BYTE* question = new BYTE [question_size];

	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eSetViewName, cursor);
  cursor = dwpPatch.toBuf(cursor);
  cursor = SMUtility::IntToBuf((short)viewNum, cursor);

  memcpy (cursor, name, name_len);

	ret = pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, NULL, 0);

	delete [] question;
  return ret;

  //## end ViewQuestion::SetViewName%1026777709.body
}

//## Operation: ModifyViewObject%1026777710
//	Modifiesthe display parameters of the object, being,
//	top, left, height, width, and tag given a Baseshell
bool ViewQuestion::ModifyViewObject (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum, P_BASESHELL pObject, unsigned top, unsigned left, unsigned height, unsigned width, unsigned tag)
{
  //## begin ViewQuestion::ModifyViewObject%1026777710.body preserve=yes
	bool ret = false;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH) // dwpPatch
    + sizeof(short) // viewNum
    + sizeof(P_BASESHELL) // pObject
    + sizeof(short) * 5; //params

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eModifyViewObject, cursor);
	cursor = dwpPatch.toBuf(cursor);
  cursor = SMUtility::IntToBuf((short)viewNum, cursor);
  cursor = pObject.toBuf(cursor);

  cursor = SMUtility::IntToBuf((short)top, cursor);
  cursor = SMUtility::IntToBuf((short)left, cursor);
  cursor = SMUtility::IntToBuf((short)height, cursor);
  cursor = SMUtility::IntToBuf((short)width, cursor);
  SMUtility::IntToBuf((short)tag, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			ret = true;
		}

	delete [] question;
	return ret;

  //## end ViewQuestion::ModifyViewObject%1026777710.body
}

//## Operation: AddView%1026777712
unsigned ViewQuestion::AddView (PresentationQuestion* pQuestion, P_PATCH dwpPatch)
{
  //## begin ViewQuestion::AddView%1026777712.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH); // dwpPatch

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eAddView, cursor);
	dwpPatch.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;

  //## end ViewQuestion::AddView%1026777712.body
}

//## Operation: DeleteView%1026777713
void ViewQuestion::DeleteView (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum)
{
  //## begin ViewQuestion::DeleteView%1026777713.body preserve=yes
	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH) // dwpPatch
    + sizeof(short); // viewNum

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eDeleteView, cursor);
	cursor = dwpPatch.toBuf(cursor);
  SMUtility::IntToBuf((short)viewNum, cursor);

	//get the answer
	pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer));

	delete [] question;

  //## end ViewQuestion::DeleteView%1026777713.body
}

//## Operation: AddViewConnector%1049496130
//	Adds the Connector To View Object, returning the index
int ViewQuestion::AddViewConnector (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum, P_CONNECTOR pCon)
{
  //## begin ViewQuestion::AddViewConnector%1049496130.body preserve=yes
	int ret = -1;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH) // dwpPatch
    + sizeof(short) // viewNum
    + sizeof(P_CONNECTOR); // pCon

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eAddViewConnector, cursor);
	cursor = dwpPatch.toBuf(cursor);
  cursor = SMUtility::IntToBuf((short)viewNum, cursor);
  pCon.toBuf(cursor);


	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}

	delete [] question;
	return ret;

  //## end ViewQuestion::AddViewConnector%1049496130.body
}

//## Operation: GetNumViewConnectors%1049496131
//	Returns the Number OF View Connectors within View
unsigned ViewQuestion::GetNumViewConnectors (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum)
{
  //## begin ViewQuestion::GetNumViewConnectors%1049496131.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH) // dwpPatch
    + sizeof(short); // viewNum

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eGetNumViewConnectors, cursor);
	cursor = dwpPatch.toBuf(cursor);
  SMUtility::IntToBuf((short)viewNum, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;

  //## end ViewQuestion::GetNumViewConnectors%1049496131.body
}

//## Operation: GetViewConnector%1049496132
//	Returns the Connector Pointed to at ViewIndex
P_CONNECTOR ViewQuestion::GetViewConnector (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum, unsigned objectNum)
{
  //## begin ViewQuestion::GetViewConnector%1049496132.body preserve=yes
	P_CONNECTOR ret;
	const unsigned question_size =  SMUtility::TargetFuncBufSize() // eGetNumAttributes
		+ sizeof (P_PATCH) // dwpPatch
		+ sizeof (short) //viewNum
		+ sizeof (short); // objectNum
	const unsigned answer_size = sizeof (P_CONNECTOR);

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [answer_size];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eGetViewConnector, cursor);
	cursor = dwpPatch.toBuf(cursor);
	cursor = SMUtility::IntToBuf((short)viewNum, cursor);
	SMUtility::IntToBuf((short)objectNum, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = P_CONNECTOR (&a_cursor);
		}
	delete [] question;
	return ret;

  //## end ViewQuestion::GetViewConnector%1049496132.body
}

//## Operation: GetViewConnectorValue%1049496133
//	Returns the Value Stored at the point
int ViewQuestion::GetViewConnectorValue (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum, unsigned objectNum, unsigned value_num)
{
  //## begin ViewQuestion::GetViewConnectorValue%1049496133.body preserve=yes
	int ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH) // dwpPatch
    + sizeof(short) // viewNum
    + sizeof(short) //objectNum
    + sizeof(short); //value_num

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eGetViewConnectorValue, cursor);
	cursor = dwpPatch.toBuf(cursor);
  cursor = SMUtility::IntToBuf((short)viewNum, cursor);
  cursor = SMUtility::IntToBuf((short)objectNum, cursor);
  SMUtility::IntToBuf((short)value_num, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;

  //## end ViewQuestion::GetViewConnectorValue%1049496133.body
}

//## Operation: GetNumViewConnectorValues%1049496134
//	Returns the Number of Values at a given Connector View
//	Point
unsigned ViewQuestion::GetNumViewConnectorValues (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum, unsigned objectNum)
{
  //## begin ViewQuestion::GetNumViewConnectorValues%1049496134.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH) // dwpPatch
    + sizeof(short) // viewNum
    + sizeof(short); //objectNum

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eGetNumViewConnectorValues, cursor);
	cursor = dwpPatch.toBuf(cursor);
  cursor = SMUtility::IntToBuf((short)viewNum, cursor);
  SMUtility::IntToBuf((short)objectNum, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;
  //## end ViewQuestion::GetNumViewConnectorValues%1049496134.body
}

//## Operation: AddViewConnectorValue%1049496135
//	Adds A New View Connector Value
bool ViewQuestion::AddViewConnectorValue (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned viewNum, unsigned objectNum, int new_value)
{
  //## begin ViewQuestion::AddViewConnectorValue%1049496135.body preserve=yes
	bool ret = false;


	const unsigned question_size =  SMUtility::TargetFuncBufSize() //
		+ sizeof (P_PATCH) // dwpPatch
    + sizeof(short) // viewNum
    + sizeof(short) //objectNum
    + sizeof(short); //new_value

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (ViewAnswer::eAddViewConnectorValue, cursor);
	cursor = dwpPatch.toBuf(cursor);
  cursor = SMUtility::IntToBuf((short)viewNum, cursor);
  cursor = SMUtility::IntToBuf((short)objectNum, cursor);
  SMUtility::IntToBuf((short)new_value, cursor);


	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatchView, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;

  //## end ViewQuestion::AddViewConnectorValue%1049496135.body
}

// Additional Declarations
  //## begin ViewQuestion%3D33592700C6.declarations preserve=yes
  //## end ViewQuestion%3D33592700C6.declarations

//## begin module%3D3359940267.epilog preserve=yes
//## end module%3D3359940267.epilog
