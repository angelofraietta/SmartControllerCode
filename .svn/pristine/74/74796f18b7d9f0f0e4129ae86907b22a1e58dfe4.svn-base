//## begin module%3AC14A26020E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AC14A26020E.cm

//## begin module%3AC14A26020E.cp preserve=no
//	Angelo Fraietta
//## end module%3AC14A26020E.cp

//## Module: IdentityQuestion%3AC14A26020E; Package body
//	Implementation for Identity
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\identityquestion.cpp

//## begin module%3AC14A26020E.additionalIncludes preserve=no
#include "stdafx.h"
#include "control.h"
//## end module%3AC14A26020E.additionalIncludes

//## begin module%3AC14A26020E.includes preserve=yes
#include "smutility.h"
//## end module%3AC14A26020E.includes

// PresentationQuestion
#include "presentationquestion.h"
// IdentityQuestion
#include "identityquestion.h"
// PresentationAnswer
#include "presentationanswer.h"
// IdentityAnswer
#include "identityanswer.h"


//## begin module%3AC14A26020E.declarations preserve=no
//## end module%3AC14A26020E.declarations

//## begin module%3AC14A26020E.additionalDeclarations preserve=yes
//## end module%3AC14A26020E.additionalDeclarations


// Class Utility IdentityQuestion 


//## Other Operations (implementation)
//## Operation: GetDefaultAttribute%985746352
//	Gets the Attribute defininded by the P_IDENTITY and
//	index  parameters.  The Attribute value is returned as a
//	parameter. Function returns true if the Attribute is
//	valid
//## Postconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
//	attribute_key
bool IdentityQuestion::GetDefaultAttribute (PresentationQuestion* pQuestion, P_IDENTITY objKey, char* ret_value, unsigned buf_len)
{
  //## begin IdentityQuestion::GetDefaultAttribute%985746352.body preserve=yes
	bool success;
	const unsigned question_size = SMUtility::TargetFuncBufSize() // Target Function index
		+ sizeof (P_IDENTITY); // pIdentity
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE* answer  = (BYTE*) ret_value; 


	// fill question
	cursor = SMUtility::TargetFuncToBuf (IdentityAnswer::eGetDefaultAttribute, cursor);
	cursor = objKey.toBuf(cursor);

	//get the answer
	success = pQuestion->AskQuestion (PresentationAnswer::eIdentity, question, question_size, answer, buf_len);

	delete[] question;
	return success;

  //## end IdentityQuestion::GetDefaultAttribute%985746352.body
}

//## Operation: GetName%986510805
//	Gets the name of identity defininded by the P_IDENTITY
//	parameter.  The identity name is returned as parameters.
//## Postconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
void IdentityQuestion::GetName (PresentationQuestion* pQuestion, P_IDENTITY objKey, char* ret_value, unsigned buf_len)
{
  //## begin IdentityQuestion::GetName%986510805.body preserve=yes
	bool success;
	const unsigned question_size = SMUtility::TargetFuncBufSize() // Target Function index
		+ sizeof (P_IDENTITY); // pIdentity
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE* answer  = (BYTE*) ret_value; 


	// fill question
	cursor = SMUtility::TargetFuncToBuf (IdentityAnswer::eGetName, cursor);
	cursor = objKey.toBuf(cursor);

	//get the answer
	success = pQuestion->AskQuestion (PresentationAnswer::eIdentity, question, question_size, answer, buf_len);

	delete[] question;
	if (!success)
    {
      *ret_value = '\0';
    }
  //## end IdentityQuestion::GetName%986510805.body
}

//## Operation: GetComment%986510806
//	Gets the comment of the identity defininded by the P_
//	IDENTITY  parameter.  The identity name is returned as
//	parameters.
//## Postconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
void IdentityQuestion::GetComment (PresentationQuestion* pQuestion, P_IDENTITY objKey, char* ret_value, unsigned buf_len)
{
  //## begin IdentityQuestion::GetComment%986510806.body preserve=yes
	bool success;
	const unsigned question_size = SMUtility::TargetFuncBufSize() // Target Function index
		+ sizeof (P_IDENTITY); // pIdentity
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE* answer  = (BYTE*) ret_value; 


	// fill question
	cursor = SMUtility::TargetFuncToBuf (IdentityAnswer::eGetComment, cursor);
	cursor = objKey.toBuf(cursor);

	//get the answer
	success = pQuestion->AskQuestion (PresentationAnswer::eIdentity, question, question_size, answer, buf_len);

	delete[] question;

  if (!success)
    {
      *ret_value = '\0';
    }
  //## end IdentityQuestion::GetComment%986510806.body
}

//## Operation: GetType%986510807
//	Gets the type of the identity defininded by the P_
//	IDENTITY  parameter.  The identity name is returned as
//	parameters.
//## Postconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
void IdentityQuestion::GetType (PresentationQuestion* pQuestion, P_IDENTITY objKey, char* ret_value, unsigned buf_len)
{
  //## begin IdentityQuestion::GetType%986510807.body preserve=yes
	bool success;
	const unsigned question_size = SMUtility::TargetFuncBufSize() // Target Function index
		+ sizeof (P_IDENTITY); // pIdentity
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE* answer  = (BYTE*) ret_value; 


	// fill question
	cursor = SMUtility::TargetFuncToBuf (IdentityAnswer::eGetType, cursor);
	cursor = objKey.toBuf(cursor);

	//get the answer
	success = pQuestion->AskQuestion (PresentationAnswer::eIdentity, question, question_size, answer, buf_len);

	delete[] question;
  if (!success)
    {
      *ret_value = '\0';
    }
  //## end IdentityQuestion::GetType%986510807.body
}

//## Operation: SetName%986510808
//	Sets the name defininded by the P_IDENTITY parameter.
//	Function returns true if the name has been set.
//## Postconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
//	new_value
bool IdentityQuestion::SetName (PresentationQuestion* pQuestion, P_IDENTITY objKey, const char* new_value)
{
  //## begin IdentityQuestion::SetName%986510808.body preserve=yes
	bool ret = false;
	
	const unsigned question_size = SMUtility::TargetFuncBufSize() // eSetAttribute
		+ sizeof (P_IDENTITY) // pIdentity
		+ strlen (new_value) + 1; // new value buffer

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (IdentityAnswer::eSetName, cursor);
	cursor = objKey.toBuf(cursor);
	SMUtility::StrToBuf (new_value, cursor);

	//get the answer 
	if(pQuestion->AskQuestion (PresentationAnswer::eIdentity, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = (SMUtility::BufToInt (&a_cursor)); // convert answer
		}

	delete [] question;
	return ret;
  //## end IdentityQuestion::SetName%986510808.body
}

//## Operation: SetComment%986510809
//	Sets the comment defininded by the P_IDENTITY
//	parameter.  Function returns true if the name has been
//	set.
//## Postconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
//	new_value
bool IdentityQuestion::SetComment (PresentationQuestion* pQuestion, P_IDENTITY objKey, const char* new_value)
{
  //## begin IdentityQuestion::SetComment%986510809.body preserve=yes
	bool ret = false;
	
	const unsigned question_size = SMUtility::TargetFuncBufSize() // eSetAttribute
		+ sizeof (P_IDENTITY) // pIdentity
		+ strlen (new_value) + 1; // new value buffer

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (IdentityAnswer::eSetComment, cursor);
	cursor = objKey.toBuf(cursor);
	SMUtility::StrToBuf (new_value, cursor);

	//get the answer 
	if(pQuestion->AskQuestion (PresentationAnswer::eIdentity, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = (SMUtility::BufToInt (&a_cursor)); // convert answer
		}

	delete [] question;
	return ret;
  //## end IdentityQuestion::SetComment%986510809.body
}

//## Operation: GetModified%986510810
//	Returns true if the identity has been modified
//## Postconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
bool IdentityQuestion::GetModified (PresentationQuestion* pQuestion, P_IDENTITY objKey)
{
  //## begin IdentityQuestion::GetModified%986510810.body preserve=yes
	bool ret = false;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // eGetNumAttributes
		+ sizeof (P_IDENTITY); // pIdentity
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (IdentityAnswer::eGetModified, cursor);
	objKey.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eIdentity, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return (ret);
  //## end IdentityQuestion::GetModified%986510810.body
}

//## Operation: SetDefaultAttribute%986947729
//	Sets the default attribute defininded by the P_IDENTITY
//	parameter.  Function returns true if the name has been
//	set.
//## Postconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
//	new_value
bool IdentityQuestion::SetDefaultAttribute (PresentationQuestion* pQuestion, P_IDENTITY objKey, const char* new_value)
{
  //## begin IdentityQuestion::SetDefaultAttribute%986947729.body preserve=yes
	bool ret = false;
	
	const unsigned question_size = SMUtility::TargetFuncBufSize() // eSetAttribute
		+ sizeof (P_IDENTITY) // pIdentity
		+ strlen (new_value) + 1; // new value buffer

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (IdentityAnswer::eSetDefaultAttribute, cursor);
	cursor = objKey.toBuf(cursor);
	SMUtility::StrToBuf (new_value, cursor);

	//get the answer 
	if(pQuestion->AskQuestion (PresentationAnswer::eIdentity, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = (SMUtility::BufToInt (&a_cursor)); // convert answer
		}

	delete [] question;
	return ret;

  //## end IdentityQuestion::SetDefaultAttribute%986947729.body
}

//## Operation: CanSave%986947731; C++
//## Postconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
bool IdentityQuestion::CanSave (PresentationQuestion* pQuestion, P_IDENTITY dwpId)
{
  //## begin IdentityQuestion::CanSave%986947731.body preserve=yes
	bool ret = false;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // eGetNumAttributes
		+ sizeof (P_IDENTITY); // pIdentity
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (IdentityAnswer::eCanSave, cursor);
	dwpId.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eIdentity, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return (ret);

  //## end IdentityQuestion::CanSave%986947731.body
}

//## Operation: GetParent%986947734; C++
P_PATCH IdentityQuestion::GetParent (PresentationQuestion* pQuestion, P_IDENTITY dwpId)
{
  //## begin IdentityQuestion::GetParent%986947734.body preserve=yes
	P_PATCH ret_patch;	
	const unsigned question_size = SMUtility::TargetFuncBufSize() // eSetAttribute 
		+ sizeof (P_IDENTITY); // dwpId
	const unsigned answer_size = sizeof (P_PATCH);
	BYTE* question = new BYTE [question_size];
	BYTE* answer = new BYTE [answer_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (IdentityAnswer::eGetParent, cursor);
	cursor = dwpId.toBuf(cursor);

	if (pQuestion->AskQuestion (PresentationAnswer::eIdentity, question, question_size, answer, answer_size))
		{
			const BYTE* c_answer = answer;
			ret_patch = P_PATCH (&c_answer);
		}
	delete [] question;
	delete []answer;

  return ret_patch;
  //## end IdentityQuestion::GetParent%986947734.body
}

//## Operation: SetParent%986947735; C++
void IdentityQuestion::SetParent (PresentationQuestion* pQuestion, P_IDENTITY dwpId, P_PATCH dwpParent)
{
  //## begin IdentityQuestion::SetParent%986947735.body preserve=yes
	const unsigned question_size = SMUtility::TargetFuncBufSize() // eSetAttribute 
		+ sizeof (P_IDENTITY) // pIdentity
		+ sizeof (P_PATCH);
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (IdentityAnswer::eSetParent, cursor);
	cursor = dwpId.toBuf(cursor);
	cursor = dwpParent.toBuf(cursor);

	pQuestion->AskQuestion (PresentationAnswer::eIdentity, question, question_size, NULL, 0);
	delete [] question;
  //## end IdentityQuestion::SetParent%986947735.body
}

// Additional Declarations
  //## begin IdentityQuestion%3A9AC69203C7.declarations preserve=yes
  //## end IdentityQuestion%3A9AC69203C7.declarations

//## begin module%3AC14A26020E.epilog preserve=yes
//## end module%3AC14A26020E.epilog
