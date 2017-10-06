//## begin module%3CE1AB7B0165.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CE1AB7B0165.cm

//## begin module%3CE1AB7B0165.cp preserve=no
//	Angelo Fraietta
//## end module%3CE1AB7B0165.cp

//## Module: FileQuestion%3CE1AB7B0165; Pseudo Package body
//## Subsystem: engineinterface%3A9C858C00CB
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\filequestion.cpp

//## begin module%3CE1AB7B0165.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3CE1AB7B0165.additionalIncludes

//## begin module%3CE1AB7B0165.includes preserve=yes
//## end module%3CE1AB7B0165.includes

// PresentationQuestion
#include "presentationquestion.h"
// PresentationAnswer
#include "presentationanswer.h"
// SMUtility
#include "smutility.h"
// FileQuestion
#include "filequestion.h"
// FileAnswer
#include "fileanswer.h"
//## begin module%3CE1AB7B0165.additionalDeclarations preserve=yes
//## end module%3CE1AB7B0165.additionalDeclarations


// Class Utility FileQuestion 


//## Other Operations (implementation)
//## Operation: OpenFileForWrite%1021420318
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
bool FileQuestion::OpenFileForWrite (PresentationQuestion* pQuestion, unsigned key, const char* filename)
{
  //## begin FileQuestion::OpenFileForWrite%1021420318.body preserve=yes
	bool ret = false;
  const unsigned len =  sizeof(short) +  // key
  strlen (filename) + 1;

	const unsigned question_size = SMUtility::TargetFuncBufSize()
		+ len;

	const unsigned answer_size = 2;
	BYTE* question = new BYTE [question_size];
	BYTE answer [answer_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (FileAnswer::eOpenFileForWrite, cursor);
  cursor = SMUtility::IntToBuf((short)key, cursor);

  strcpy ((char*)cursor, filename);


	if (pQuestion->AskQuestion (PresentationAnswer::eFile, question, question_size, answer, answer_size))
		{
			ret = true;
		}

	delete [] question;

  return ret;
  //## end FileQuestion::OpenFileForWrite%1021420318.body
}

//## Operation: OpenFileForRead%1021420319
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned FileQuestion::OpenFileForRead (PresentationQuestion* pQuestion, unsigned key, const char* filename)
{
  //## begin FileQuestion::OpenFileForRead%1021420319.body preserve=yes
	unsigned ret = 0;
  const unsigned len =  sizeof(short) +  // key
  strlen (filename) + 1;

	const unsigned question_size = SMUtility::TargetFuncBufSize()
		+ len;

	const unsigned answer_size = sizeof(short);
	BYTE* question = new BYTE [question_size];
	BYTE answer [answer_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (FileAnswer::eOpenFileForRead, cursor);
  cursor = SMUtility::IntToBuf((short)key, cursor);

  strcpy ((char*)cursor, filename);


	if (pQuestion->AskQuestion (PresentationAnswer::eFile, question, question_size, answer, answer_size))
		{
      const BYTE* ret_answer = answer;
			ret = SMUtility::BufToInt(&ret_answer);
		}

	delete [] question;

  return ret;

  //## end FileQuestion::OpenFileForRead%1021420319.body
}

//## Operation: WriteBytes%1021420320
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned FileQuestion::WriteBytes (PresentationQuestion* pQuestion, unsigned key, unsigned block_num, unsigned num_bytes, const BYTE* data_bytes)
{
  //## begin FileQuestion::WriteBytes%1021420320.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // eGetNumAttributes
    + sizeof (short) // key
		+ sizeof (short) //block_num
    + sizeof (short) //num _bytes
    + num_bytes; // data
	const unsigned answer_size = 2;

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [answer_size];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (FileAnswer::eWriteBytes, cursor);
	cursor = SMUtility::IntToBuf((short)key, cursor);
  cursor = SMUtility::IntToBuf ((short)block_num, cursor);
  cursor = SMUtility::IntToBuf ((short)num_bytes, cursor);

  // now copy data across
  memcpy (cursor, data_bytes, num_bytes);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eFile, question, question_size, answer, answer_size))
		{
			ret = 0;
		}

	delete [] question;
	return ret;

  //## end FileQuestion::WriteBytes%1021420320.body
}

//## Operation: ReadBytes%1021420321
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned FileQuestion::ReadBytes (PresentationQuestion* pQuestion, unsigned key, BYTE* data_bytes, unsigned bytes_to_read)
{
  //## begin FileQuestion::ReadBytes%1021420321.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // eGetNumAttributes
    + sizeof (short) // key
    + sizeof (short); //num _bytes

	const unsigned answer_size = sizeof (short) //num _bytes read
    + bytes_to_read;

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE* answer = new BYTE [answer_size];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (FileAnswer::eReadBytes, cursor);
	cursor = SMUtility::IntToBuf((short)key, cursor);
  SMUtility::IntToBuf ((short)bytes_to_read, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eFile, question, question_size, answer, answer_size))
		{
      const BYTE* ret_answer = answer;
			ret = SMUtility::BufToInt(&ret_answer);

      if (ret <= bytes_to_read)
      {
        // nopw copy the data
        memcpy(data_bytes, ret_answer, ret);
      }
      else
      {
        ret = 0;
      }

		}

	delete [] question;
  delete []answer;
	return ret;

  //## end FileQuestion::ReadBytes%1021420321.body
}

//## Operation: CloseFile%1021420322
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned FileQuestion::CloseFile (PresentationQuestion* pQuestion, unsigned key)
{
  //## begin FileQuestion::CloseFile%1021420322.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize() // eGetNumAttributes
    + sizeof (short);
	const unsigned answer_size = 2;

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [answer_size];

	// fill question
	cursor = SMUtility::TargetFuncToBuf (FileAnswer::eCloseFile, cursor);
	SMUtility::IntToBuf((short)key, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eFile, question, question_size, answer, answer_size))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}

	delete [] question;
	return ret;

  //## end FileQuestion::CloseFile%1021420322.body
}

//## Operation: SaveNVRAM%1032126401
//	Stores the Data to NVRAM
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned FileQuestion::SaveNVRAM (PresentationQuestion* pQuestion)
{
  //## begin FileQuestion::SaveNVRAM%1032126401.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize(); // eGetNumAttributes

	const unsigned answer_size = 2;

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [answer_size];

	// fill question
  SMUtility::TargetFuncToBuf (FileAnswer::eSaveNVRAM, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eFile, question, question_size, answer, answer_size))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}

	delete [] question;
	return ret;

  //## end FileQuestion::SaveNVRAM%1032126401.body
}

//## Operation: EraseNVRAM%1032171149
//	Clears NVRAM
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned FileQuestion::EraseNVRAM (PresentationQuestion* pQuestion)
{
  //## begin FileQuestion::EraseNVRAM%1032171149.body preserve=yes
	unsigned ret = 0;

	const unsigned question_size =  SMUtility::TargetFuncBufSize(); // eGetNumAttributes

	const unsigned answer_size = 2;

	BYTE* question = new BYTE [question_size];
	BYTE* cursor = question;
	BYTE answer [answer_size];

	// fill question
  SMUtility::TargetFuncToBuf (FileAnswer::eEraseNVRAM, cursor);

	//get the answer
	if(pQuestion->AskQuestion (PresentationAnswer::eFile, question, question_size, answer, answer_size))
		{
			const BYTE* a_cursor = answer;
			ret = SMUtility::BufToInt (&a_cursor); // convert answer
		}

	delete [] question;
	return ret;

  //## end FileQuestion::EraseNVRAM%1032171149.body
}

//## Operation: SaveFileToDisk%1051589362
//	Saves a file to onboard IDE
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
void FileQuestion::SaveFileToDisk (PresentationQuestion* pQuestion, unsigned long crc, const char* filename)
{
  //## begin FileQuestion::SaveFileToDisk%1051589362.body preserve=yes
  const unsigned len =  sizeof(crc) +
  strlen (filename) + 1;

	const unsigned question_size = SMUtility::TargetFuncBufSize()
		+ len;

	const unsigned answer_size = 2;
	BYTE* question = new BYTE [question_size];
	BYTE answer [answer_size];
	BYTE* cursor = question;

	// fill question
	cursor = SMUtility::TargetFuncToBuf (FileAnswer::eSaveFileToDisk, cursor);
  cursor = SMUtility::DwordToBuf(crc, cursor);

  strcpy ((char*)cursor, filename);


	pQuestion->AskQuestion (PresentationAnswer::eFile, question, question_size, answer, answer_size);

	delete [] question;

  //## end FileQuestion::SaveFileToDisk%1051589362.body
}

// Additional Declarations
  //## begin FileQuestion%3CE1AB7B0165.declarations preserve=yes
  //## end FileQuestion%3CE1AB7B0165.declarations

//## begin module%3CE1AB7B0165.epilog preserve=yes
//## end module%3CE1AB7B0165.epilog
