//## begin module%3ACAAE7B00C6.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ACAAE7B00C6.cm

//## begin module%3ACAAE7B00C6.cp preserve=no
//	Angelo Fraietta
//## end module%3ACAAE7B00C6.cp

//## Module: PresentationAnswer%3ACAAE7B00C6; Package body
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\presentationanswer.cpp

//## begin module%3ACAAE7B00C6.additionalIncludes preserve=no
#include "stdafx.h"
#include "smutility.h"
//## end module%3ACAAE7B00C6.additionalIncludes

//## begin module%3ACAAE7B00C6.includes preserve=yes
#include "crc32.h"

#include <string.h>
#include "control.h"
#include "sessioninterface.h"
#include "answertask.h"
//## end module%3ACAAE7B00C6.includes

// PresentationAnswer
#include "presentationanswer.h"
// IdentityAnswer
#include "identityanswer.h"
// PatchAnswer
#include "patchanswer.h"
// BaseShellAnswer
#include "baseshellanswer.h"
// ViewAnswer
#include "viewanswer.h"
// ConnectorAnswer
#include "connectoranswer.h"
// FileAnswer
#include "fileanswer.h"


//## begin module%3ACAAE7B00C6.declarations preserve=no
//## end module%3ACAAE7B00C6.declarations

//## begin module%3ACAAE7B00C6.additionalDeclarations preserve=yes
#define SHOW_DEBUG
//## end module%3ACAAE7B00C6.additionalDeclarations


// Class PresentationAnswer 

//## begin PresentationAnswer::pFunc%3AC3C9B802A8.attr preserve=no  private: static PresentationAnswer::pfunctype [] {U} {IdentityAnswer::PerformOperation, BaseShellAnswer::PerformOperation, ConnectorAnswer::PerformOperation, PatchAnswer::PerformOperation, FileAnswer::PerformOperation, ViewAnswer::PerformOperation, NULL}
PresentationAnswer::pfunctype  PresentationAnswer::pFunc[] = {IdentityAnswer::PerformOperation, BaseShellAnswer::PerformOperation, ConnectorAnswer::PerformOperation, PatchAnswer::PerformOperation, FileAnswer::PerformOperation, ViewAnswer::PerformOperation, NULL};
//## end PresentationAnswer::pFunc%3AC3C9B802A8.attr






PresentationAnswer::PresentationAnswer()
  //## begin PresentationAnswer::PresentationAnswer%.hasinit preserve=no
      : _answer_buf(new BYTE[1024])
  //## end PresentationAnswer::PresentationAnswer%.hasinit
  //## begin PresentationAnswer::PresentationAnswer%.initialization preserve=yes
  //## end PresentationAnswer::PresentationAnswer%.initialization
{
  //## begin PresentationAnswer::PresentationAnswer%.body preserve=yes
  //## end PresentationAnswer::PresentationAnswer%.body
}


PresentationAnswer::~PresentationAnswer()
{
  //## begin PresentationAnswer::~PresentationAnswer%.body preserve=yes
  delete []_answer_buf;
  //## end PresentationAnswer::~PresentationAnswer%.body
}



//## Other Operations (implementation)
//## Operation: GetAnswer%985819695
//	The single function with which all querries to the
//	Engine are sent and responded to from.  The number of
//	bytes in the returned buffer is returned.
unsigned PresentationAnswer::GetAnswer (const BYTE* question, BYTE** ret_answer, unsigned r_size)
{
  //## begin PresentationAnswer::GetAnswer%985819695.body preserve=yes
  // first get event waiting flag
  bool valid_question;
  unsigned long crc;
  *ret_answer = _answer_buf;
  BYTE* a_cursor = *ret_answer;

  unsigned q_size;

  a_cursor[0] = *question; // copy the sequence number frm the question to the answer

  a_cursor[1] = (BYTE)_event_container.eventReady(); // write the event waiting

  unsigned ret_bytes = ReturnBytes();

  a_cursor += ret_bytes;

  // now deal with the question
  const BYTE* q_cursor = question +1; // we do not include the sequence number
  unsigned target_class_index = SMUtility::BufToTargetClass (&q_cursor);
  q_size = SMUtility::BufToInt (&q_cursor);

  const BYTE* crc_cursor = q_cursor + q_size;


  crc = calculate_crc (q_cursor, q_size);

  valid_question = (crc == SMUtility::BufToDword (&crc_cursor));

  if (valid_question && target_class_index < (BYTE)eMaxclass)
    {
      unsigned app_bytes;
      if (pFunc[target_class_index]) // then there is a class function to perform
        {
          app_bytes = (pFunc[target_class_index]) (q_cursor, a_cursor, r_size - ReturnBytes() - sizeof(DWORD) );
        }
      else // this must be some sort of event question
        {
          app_bytes = _event_container.GetEvent (q_cursor, a_cursor, r_size - ReturnBytes() - sizeof(DWORD));
        }
      ret_bytes += app_bytes;
      SMUtility::IntToBuf((short)app_bytes, *ret_answer + sizeof(short)); // write number of bytes after the flag
    }

  // now move to CRC
  a_cursor = *ret_answer + ret_bytes;

  crc = calculate_crc ((*ret_answer), ret_bytes);

  SMUtility::DwordToBuf (crc, a_cursor);

  return ret_bytes + sizeof(DWORD);
  //## end PresentationAnswer::GetAnswer%985819695.body
}

//## Operation: GetAnswer%1020660146
//	The single function with which all querries to the
//	Engine are sent and responded to from.  The number of
//	bytes in the returned buffer is returned.
unsigned PresentationAnswer::GetAnswer (const BYTE* question, BYTE* ret_answer, unsigned r_size)
{
  //## begin PresentationAnswer::GetAnswer%1020660146.body preserve=yes
  bool valid_question;
  unsigned long crc, given_crc;
  unsigned ret_bytes = 0;

	BYTE* a_cursor = ret_answer;

  unsigned q_size;

  if (a_cursor)
  {
		a_cursor[0] = *question; // copy the sequence number frm the question to the answer

		a_cursor[1] = (BYTE)_event_container.eventReady(); // write the event waiting

		ret_bytes = ReturnBytes();

		a_cursor += ret_bytes;
  }

	// now deal with the question
	const BYTE* q_cursor = question +1; // we do not include the sequence number
	unsigned target_class_index = SMUtility::BufToTargetClass (&q_cursor);
  q_size = SMUtility::BufToInt (&q_cursor);

  const BYTE* crc_cursor = q_cursor + q_size;


  crc = calculate_crc (q_cursor, q_size);
  given_crc = SMUtility::BufToDword (&crc_cursor);
  valid_question = (crc == given_crc);

#ifdef SHOW_DEBUG
	if (!valid_question)
		{
			const char message []= "Bad CRC\r\n";
			printf(message);
			DisplayDiags (message);

		}
#endif

	if (valid_question && target_class_index < (BYTE)eMaxclass)
		{
      unsigned app_bytes;
      unsigned return_bytes = 0;

      if (r_size)
      {
      	return_bytes = r_size - ReturnBytes() - sizeof(DWORD);
      }

			if (pFunc[target_class_index]) // then there is a class function to perform
				{
					app_bytes = (pFunc[target_class_index]) (q_cursor, a_cursor, return_bytes);
				}
			else // this must be some sort of event question
				{
					app_bytes = _event_container.GetEvent (q_cursor, a_cursor, return_bytes);
				}

      if (a_cursor)
      {
				ret_bytes += app_bytes;
      	SMUtility::IntToBuf((short)app_bytes, ret_answer + 2); // write number of bytes after the flag
      }
		}

  if (a_cursor)
  {
	  // now move to CRC
  	a_cursor = ret_answer + ret_bytes;

  	crc = calculate_crc (ret_answer, ret_bytes);

  	SMUtility::DwordToBuf (crc, a_cursor);
    ret_bytes += sizeof(DWORD);
  }
  return ret_bytes;

  //## end PresentationAnswer::GetAnswer%1020660146.body
}

// Additional Declarations
  //## begin PresentationAnswer%3AA802130023.declarations preserve=yes
  //## end PresentationAnswer%3AA802130023.declarations

//## begin module%3ACAAE7B00C6.epilog preserve=yes
//## end module%3ACAAE7B00C6.epilog
