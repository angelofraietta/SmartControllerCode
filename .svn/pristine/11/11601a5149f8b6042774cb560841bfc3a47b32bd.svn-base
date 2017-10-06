//## begin module%3ACAB11802C7.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ACAB11802C7.cm

//## begin module%3ACAB11802C7.cp preserve=no
//	Angelo Fraietta
//## end module%3ACAB11802C7.cp

//## Module: PatchQuestion%3ACAB11802C7; Package body
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: d:\develop\smartcontroller\controller\source\engineinterface\patchquestion.cpp

//## begin module%3ACAB11802C7.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3ACAB11802C7.additionalIncludes

//## begin module%3ACAB11802C7.includes preserve=yes
#include "typedefs.h"
#include "interfacetypes.h"
#include "smutility.h"
#include "dllinterface.h"
#include <stdio.h>
//## end module%3ACAB11802C7.includes

// PresentationAnswer
#include "presentationanswer.h"
// PatchAnswer
#include "patchanswer.h"
// PatchQuestion
#include "patchquestion.h"
// PresentationQuestion
#include "presentationquestion.h"


//## begin module%3ACAB11802C7.declarations preserve=no
//## end module%3ACAB11802C7.declarations

//## begin module%3ACAB11802C7.additionalDeclarations preserve=yes
//## end module%3ACAB11802C7.additionalDeclarations


// Class Utility PatchQuestion 


//## Other Operations (implementation)
//## Operation: DetachBaseShellObject%2052505070; C++
void PatchQuestion::DetachBaseShellObject (PresentationQuestion* pQuestion, P_PATCH dwpPatch, P_BASESHELL dwpShell)
{
  //## begin PatchQuestion::DetachBaseShellObject%2052505070.body preserve=yes
	const unsigned question_size = SMUtility::TargetFuncBufSize() // eSetAttribute 
		+ sizeof (P_PATCH) // dwpPatch
		+ sizeof (P_BASESHELL); // dwpShell
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eDetachBaseShellObject, cursor);
	cursor = 	dwpPatch.toBuf(cursor);
	dwpShell.toBuf(cursor);


	pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, NULL, 0);
	delete [] question;

  //## end PatchQuestion::DetachBaseShellObject%2052505070.body
}

//## Operation: FindBaseShellPosition%633089553; C++
unsigned PatchQuestion::FindBaseShellPosition (PresentationQuestion* pQuestion, P_PATCH dwpPatch, P_BASESHELL dwpShell)
{
  //## begin PatchQuestion::FindBaseShellPosition%633089553.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size = SMUtility::TargetFuncBufSize() // eSetAttribute 
		+ sizeof (P_PATCH) // dwpPatch
		+ sizeof (P_BASESHELL); // dwpShell
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];
	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eFindBaseShellPosition, cursor);
	cursor = 	dwpPatch.toBuf(cursor);
	dwpShell.toBuf(cursor);
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;

  //## end PatchQuestion::FindBaseShellPosition%633089553.body
}

//## Operation: AddBaseShell%-1753633385; C++
void PatchQuestion::AddBaseShell (PresentationQuestion* pQuestion, P_PATCH dwpPatch, P_BASESHELL dwpShell)
{
  //## begin PatchQuestion::AddBaseShell%-1753633385.body preserve=yes
		const unsigned question_size = SMUtility::TargetFuncBufSize() // eSetAttribute 
		+ sizeof (P_PATCH) // dwpPatch
		+ sizeof (P_BASESHELL); // dwpShell
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eAddBaseShell, cursor);
	cursor = 	dwpPatch.toBuf(cursor);
	dwpShell.toBuf(cursor);


	pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, NULL, 0);
	delete [] question;

  //## end PatchQuestion::AddBaseShell%-1753633385.body
}

//## Operation: NumberBaseShells%-483082950; C++
unsigned PatchQuestion::NumberBaseShells (PresentationQuestion* pQuestion, P_PATCH dwpPatch)
{
  //## begin PatchQuestion::NumberBaseShells%-483082950.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // eGetNumAttributes
		+ sizeof (P_PATCH); // dwpPatch
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eNumberBaseShells, cursor);
	dwpPatch.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;

  //## end PatchQuestion::NumberBaseShells%-483082950.body
}

//## Operation: FindBaseShell%1580427729; C++
P_BASESHELL PatchQuestion::FindBaseShell (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned int Index)
{
  //## begin PatchQuestion::FindBaseShell%1580427729.body preserve=yes
	P_BASESHELL ret;	
	const unsigned question_size =  SMUtility::TargetFuncBufSize() 
		+ sizeof (P_PATCH) 
		+ sizeof (short); // Index
	const unsigned answer_size = sizeof (P_BASESHELL);
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [answer_size];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eFindBaseShell, cursor);
	cursor = dwpPatch.toBuf(cursor);
	SMUtility::IntToBuf((short)Index, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = P_BASESHELL (&a_cursor);
		}
	delete [] question;
	return ret;

  //## end PatchQuestion::FindBaseShell%1580427729.body
}

//## Operation: DetachConnector%1779840400; C++
void PatchQuestion::DetachConnector (PresentationQuestion* pQuestion, P_PATCH dwpPatch, P_CONNECTOR dwpCon)
{
  //## begin PatchQuestion::DetachConnector%1779840400.body preserve=yes
	const unsigned question_size = SMUtility::TargetFuncBufSize() // eSetAttribute 
		+ sizeof (P_PATCH) // dwpPatch
		+ sizeof (P_CONNECTOR); // dwpCon
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eDetachConnector, cursor);
	cursor = 	dwpPatch.toBuf(cursor);
	dwpCon.toBuf(cursor);


	pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, NULL, 0);
	delete [] question;

  //## end PatchQuestion::DetachConnector%1779840400.body
}

//## Operation: AddConnector%1383773166; C++
void PatchQuestion::AddConnector (PresentationQuestion* pQuestion, P_PATCH dwpPatch, P_CONNECTOR dwpCon)
{
  //## begin PatchQuestion::AddConnector%1383773166.body preserve=yes
	const unsigned question_size = SMUtility::TargetFuncBufSize() // eSetAttribute 
		+ sizeof (P_PATCH) // dwpPatch
		+ sizeof (P_CONNECTOR); // dwpCon
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eAddConnector, cursor);
	cursor = 	dwpPatch.toBuf(cursor);
	dwpCon.toBuf(cursor);


	pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, NULL, 0);
	delete [] question;

  //## end PatchQuestion::AddConnector%1383773166.body
}

//## Operation: NumberConnectors%-1454729344; C++
unsigned PatchQuestion::NumberConnectors (PresentationQuestion* pQuestion, P_PATCH dwpPatch)
{
  //## begin PatchQuestion::NumberConnectors%-1454729344.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // eGetNumAttributes
		+ sizeof (P_PATCH); // dwpPatch
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eNumberConnectors, cursor);
	dwpPatch.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;
  //## end PatchQuestion::NumberConnectors%-1454729344.body
}

//## Operation: FindConnector%794111187; C++
P_CONNECTOR PatchQuestion::FindConnector (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned int Index)
{
  //## begin PatchQuestion::FindConnector%794111187.body preserve=yes
	P_CONNECTOR ret;	
	const unsigned question_size =  SMUtility::TargetFuncBufSize() 
		+ sizeof (P_PATCH) 
		+ sizeof (short); // Index
	const unsigned answer_size = sizeof (P_BASESHELL);
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [answer_size];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eFindConnector, cursor);
	cursor = dwpPatch.toBuf(cursor);
	SMUtility::IntToBuf((short)Index, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = P_CONNECTOR (&a_cursor);
		}
	delete [] question;
	return ret;

  //## end PatchQuestion::FindConnector%794111187.body
}

//## Operation: GetDeadConnector%581481705; C++
P_CONNECTOR PatchQuestion::GetDeadConnector (PresentationQuestion* pQuestion, P_PATCH dwpPatch)
{
  //## begin PatchQuestion::GetDeadConnector%581481705.body preserve=yes
	P_CONNECTOR ret;
	const unsigned question_size =  SMUtility::TargetFuncBufSize() 
		+ sizeof (P_PATCH);

	const unsigned answer_size = sizeof (P_BASESHELL);
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [answer_size];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eGetDeadConnector, cursor);
	dwpPatch.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = P_CONNECTOR (&a_cursor);
		}
	delete [] question;
	return ret;

  //## end PatchQuestion::GetDeadConnector%581481705.body
}

//## Operation: AddInlet%-1660140033; C++
P_BASESHELL PatchQuestion::AddInlet (PresentationQuestion* pQuestion, P_PATCH dwpPatch)
{
  //## begin PatchQuestion::AddInlet%-1660140033.body preserve=yes
	P_BASESHELL ret;	
	const unsigned question_size =  SMUtility::TargetFuncBufSize() 
		+ sizeof (P_PATCH) ;
	const unsigned answer_size = sizeof (P_BASESHELL);
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [answer_size];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eAddInlet, cursor);
	dwpPatch.toBuf(cursor);
	

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = P_BASESHELL (&a_cursor);
		}
	delete [] question;
	return ret;

  //## end PatchQuestion::AddInlet%-1660140033.body
}

//## Operation: AddOutlet%-1013941598; C++
P_BASESHELL PatchQuestion::AddOutlet (PresentationQuestion* pQuestion, P_PATCH dwpPatch)
{
  //## begin PatchQuestion::AddOutlet%-1013941598.body preserve=yes
	P_BASESHELL ret;
	const unsigned question_size =  SMUtility::TargetFuncBufSize()
		+ sizeof (P_PATCH) ;
	const unsigned answer_size = sizeof (P_BASESHELL);

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [answer_size];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eAddOutlet, cursor);
	dwpPatch.toBuf(cursor);


	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = P_BASESHELL (&a_cursor);
		}
	delete [] question;
	return ret;

  //## end PatchQuestion::AddOutlet%-1013941598.body
}

//## Operation: MakeNew%-184639055; C++
P_PATCH PatchQuestion::MakeNew (PresentationQuestion* pQuestion, const char* Name)
{
  //## begin PatchQuestion::MakeNew%-184639055.body preserve=yes
	P_BASESHELL ret;
  const unsigned name_len =  strlen (Name) + 1;
	const unsigned question_size = SMUtility::TargetFuncBufSize()
		+ name_len;

	const unsigned answer_size = sizeof (P_BASESHELL);
	BYTE* question = new BYTE [question_size];
	BYTE* answer = new BYTE [answer_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eMakeNew, cursor);
  memcpy (cursor, Name, name_len);

	if (pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, answer_size))
		{
			const BYTE* c_answer = answer;
			ret = P_BASESHELL (&c_answer);
		}
	delete [] question;
	delete []answer;

  return ret;

  //## end PatchQuestion::MakeNew%-184639055.body
}

//## Operation: SetFileName%1235827609; C++
void PatchQuestion::SetFileName (PresentationQuestion* pQuestion, P_PATCH dwpPatch, const char* FileName)
{
  //## begin PatchQuestion::SetFileName%1235827609.body preserve=yes
	  const unsigned name_len =  strlen (FileName) + 1;
	const unsigned question_size = SMUtility::TargetFuncBufSize()
  		+ sizeof (P_PATCH)
      + name_len;

	BYTE* question = new BYTE [question_size];

	BYTE* cursor = question;
	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eSetFileName, cursor);
  cursor = dwpPatch.toBuf(cursor);
  memcpy (cursor, FileName, name_len);

  printf ("PatchQuestion::SetFileName %s\r\n", FileName);
	pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, NULL, 0);

	delete [] question;

  //## end PatchQuestion::SetFileName%1235827609.body
}

//## Operation: LoadPatchFile%-326480328; C++
P_PATCH PatchQuestion::LoadPatchFile (PresentationQuestion* pQuestion, const char* FileName, P_PATCH dwpParent)
{
  //## begin PatchQuestion::LoadPatchFile%-326480328.body preserve=yes
	P_PATCH ret;
  const unsigned len =  strlen (FileName) + 1;
	const unsigned question_size = SMUtility::TargetFuncBufSize()
		+ len
		+ sizeof (P_PATCH); // pParent
	const unsigned answer_size = sizeof (P_PATCH);
	BYTE* question = new BYTE [question_size];
	BYTE* answer = new BYTE [answer_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eLoadPatchFile, cursor);
	cursor = dwpParent.toBuf(cursor);
  memcpy (cursor, FileName, len);


	if (pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, answer_size))
		{
			const BYTE* c_answer = answer;
			ret = P_PATCH (&c_answer);
		}
	delete [] question;
	delete []answer;

  return ret;

  //## end PatchQuestion::LoadPatchFile%-326480328.body
}

//## Operation: GetFileName%690648392; C++
void PatchQuestion::GetFileName (PresentationQuestion* pQuestion, P_PATCH dwpPatch, char* FileName, unsigned buf_len)
{
  //## begin PatchQuestion::GetFileName%690648392.body preserve=yes
	bool success;
	const unsigned question_size = SMUtility::TargetFuncBufSize() // Target Function index
		+ sizeof (P_PATCH); // pIdentity
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE* answer  = (BYTE*) FileName; 


	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eGetFileName, cursor);
	dwpPatch.toBuf(cursor);

	//get the answer
	success = pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, buf_len);

	delete[] question;
	if (!success)
    {
      *FileName = '\0';
    }

  //## end PatchQuestion::GetFileName%690648392.body
}

//## Operation: Save%-1512333622; C++
bool PatchQuestion::Save (PresentationQuestion* pQuestion, P_PATCH dwpPatch, const char* FileName)
{
  //## begin PatchQuestion::Save%-1512333622.body preserve=yes
	bool ret = false;
  const unsigned name_len =  strlen (FileName) + 1;
	const unsigned question_size = SMUtility::TargetFuncBufSize() // eSetAttribute
		+ sizeof (P_PATCH) // 
		+ name_len;
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	const unsigned answer_size = sizeof(short);
	BYTE answer [answer_size];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eSave, cursor);
	cursor = dwpPatch.toBuf(cursor);
	memcpy (cursor, FileName, name_len);

	if (pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, answer_size))
		{
			const BYTE* a_cursor = answer;
			ret = (SMUtility::BufToInt (&a_cursor)); // convert answer

		}

	delete [] question;
	return ret;

  //## end PatchQuestion::Save%-1512333622.body
}

//## Operation: Destroy%-947060103; C++
void PatchQuestion::Destroy (PresentationQuestion* pQuestion, P_PATCH dwpPatch)
{
  //## begin PatchQuestion::Destroy%-947060103.body preserve=yes
	const unsigned question_size = SMUtility::TargetFuncBufSize() 
		+ sizeof (P_PATCH); 
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eDestroy, cursor);
	dwpPatch.toBuf(cursor);

	pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, NULL, 0);
	delete [] question;

  //## end PatchQuestion::Destroy%-947060103.body
}

//## Operation: SwapOutlets%1612806088; C++
void PatchQuestion::SwapOutlets (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned int Outlet1, unsigned int Outlet2)
{
  //## begin PatchQuestion::SwapOutlets%1612806088.body preserve=yes
	const unsigned question_size = SMUtility::TargetFuncBufSize() // eSetAttribute 
		+ sizeof (P_PATCH) 
		+ sizeof (short) * 2; // Outlet1, Outlet2
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eSwapOutlets, cursor);
	cursor = dwpPatch.toBuf(cursor);
	cursor = SMUtility::IntToBuf ((short)Outlet1, cursor);
	SMUtility::IntToBuf ((short)Outlet2, cursor);

	pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, NULL, 0);
	delete [] question;
  //## end PatchQuestion::SwapOutlets%1612806088.body
}

//## Operation: SwapInlets%-540055132; C++
void PatchQuestion::SwapInlets (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned int Inlet1, unsigned int Inlet2)
{
  //## begin PatchQuestion::SwapInlets%-540055132.body preserve=yes
	const unsigned question_size = SMUtility::TargetFuncBufSize() // eSetAttribute 
		+ sizeof (P_PATCH) 
		+ sizeof (short) * 2; // Inlet1, Inlet2
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eSwapInlets, cursor);
	cursor = dwpPatch.toBuf(cursor);
	cursor = SMUtility::IntToBuf ((short)Inlet1, cursor);
	SMUtility::IntToBuf ((short)Inlet2, cursor);

	pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, NULL, 0);
	delete [] question;
  //## end PatchQuestion::SwapInlets%-540055132.body
}

//## Operation: GetInlet%2006261230; C++
P_BASESHELL PatchQuestion::GetInlet (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned int SocketNum)
{
  //## begin PatchQuestion::GetInlet%2006261230.body preserve=yes
	P_BASESHELL ret;	
	const unsigned question_size =  SMUtility::TargetFuncBufSize() 
		+ sizeof (P_PATCH) 
		+ sizeof (short); // SocketNum
	const unsigned answer_size = sizeof (P_BASESHELL);
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [answer_size];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eGetInlet, cursor);
	cursor = dwpPatch.toBuf(cursor);
	SMUtility::IntToBuf((short)SocketNum, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = P_BASESHELL (&a_cursor);
		}
	delete [] question;
	return ret;

  //## end PatchQuestion::GetInlet%2006261230.body
}

//## Operation: GetOutlet%274728559; C++
P_BASESHELL PatchQuestion::GetOutlet (PresentationQuestion* pQuestion, P_PATCH dwpPatch, unsigned int SocketNum)
{
  //## begin PatchQuestion::GetOutlet%274728559.body preserve=yes
	P_BASESHELL ret;	
	const unsigned question_size =  SMUtility::TargetFuncBufSize() 
		+ sizeof (P_PATCH) 
		+ sizeof (short); // SocketNum
	const unsigned answer_size = sizeof (P_BASESHELL);
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [answer_size];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eGetOutlet, cursor);
	cursor = dwpPatch.toBuf(cursor);
	SMUtility::IntToBuf((short)SocketNum, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = P_BASESHELL (&a_cursor);
		}
	delete [] question;
	return ret;

  //## end PatchQuestion::GetOutlet%274728559.body
}

//## Operation: GetOutletPortNumber%988078469; C++
//	Gets the Port number of the Outlet port
unsigned PatchQuestion::GetOutletPortNumber (PresentationQuestion* pQuestion, P_BASESHELL dwpShell)
{
  //## begin PatchQuestion::GetOutletPortNumber%988078469.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // eGetNumAttributes
		+ sizeof (P_BASESHELL); // pBaseShell
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eGetOutletPortNumber, cursor);
	dwpShell.toBuf(cursor);
 
	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;

  //## end PatchQuestion::GetOutletPortNumber%988078469.body
}

//## Operation: GetInletPortNumber%988078470; C++
//	Gets the Port number of the Inlet port
unsigned PatchQuestion::GetInletPortNumber (PresentationQuestion* pQuestion, P_BASESHELL dwpShell)
{
  //## begin PatchQuestion::GetInletPortNumber%988078470.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // eGetNumAttributes
		+ sizeof (P_BASESHELL); // pBaseShell
	
	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eGetInletPortNumber, cursor);
	dwpShell.toBuf(cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;
  //## end PatchQuestion::GetInletPortNumber%988078470.body
}

//## Operation: NumberPatches%1020226581; C++
//	Returns the Number of orphan patches. Returns -1 if the
//	call to Presentation Question Fails
int PatchQuestion::NumberPatches (PresentationQuestion* pQuestion)
{
  //## begin PatchQuestion::NumberPatches%1020226581.body preserve=yes
	int ret = -1;

	const unsigned question_size =  SMUtility::TargetFuncBufSize(); // eGetNumAttributes

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [sizeof(short)];

	// fill question
	SMUtility::TargetFuncToBuf (PatchAnswer::eNumberPatches, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}
	delete [] question;
	return ret;

  //## end PatchQuestion::NumberPatches%1020226581.body
}

//## Operation: GetPatch%1020226582; C++
//	returns the Patch given an index
P_PATCH PatchQuestion::GetPatch (PresentationQuestion* pQuestion, unsigned patch_num)
{
  //## begin PatchQuestion::GetPatch%1020226582.body preserve=yes
	P_PATCH ret;
	const unsigned question_size =  SMUtility::TargetFuncBufSize()
		+ sizeof (short); // patchNum

	const unsigned answer_size = sizeof (P_BASESHELL);

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [answer_size];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (PatchAnswer::eGetPatch, cursor);
	SMUtility::IntToBuf((short)patch_num, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::ePatch, question, question_size, answer, sizeof(answer)))
		{
			const BYTE* a_cursor = answer;
			ret = P_PATCH (&a_cursor);
		}
	delete [] question;
	return ret;

  //## end PatchQuestion::GetPatch%1020226582.body
}

// Additional Declarations
  //## begin PatchQuestion%3A99CCB2003B.declarations preserve=yes
  //## end PatchQuestion%3A99CCB2003B.declarations

//## begin module%3ACAB11802C7.epilog preserve=yes
//## end module%3ACAB11802C7.epilog
