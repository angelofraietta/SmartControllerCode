//## begin module%3AC3CD4901CE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AC3CD4901CE.cm

//## begin module%3AC3CD4901CE.cp preserve=no
//	Angelo Fraietta
//## end module%3AC3CD4901CE.cp

//## Module: PresentationQuestion%3AC3CD4901CE; Package body
//	body for Application question and answer
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: d:\develop\smartcontroller\controller\source\engineinterface\presentationquestion.cpp

//## begin module%3AC3CD4901CE.additionalIncludes preserve=no
#include "stdafx.h"
#include "smutility.h"
//## end module%3AC3CD4901CE.additionalIncludes

//## begin module%3AC3CD4901CE.includes preserve=yes
#include "crc32.h"
//## end module%3AC3CD4901CE.includes

// EventAnswer
#include "eventanswer.h"
// SessionInterface
#include "sessioninterface.h"
// PresentationAnswer
#include "presentationanswer.h"
// EventQuestion
#include "eventquestion.h"
// PresentationQuestion
#include "presentationquestion.h"
// SMUtility
#include "smutility.h"

#include "indexserver.h"

//## begin module%3AC3CD4901CE.declarations preserve=no
//## end module%3AC3CD4901CE.declarations

//## begin module%3AC3CD4901CE.additionalDeclarations preserve=yes
static PresentationQuestion simulator ("simulator");
static unsigned current_interface = 0;

static IndexServer <PresentationQuestion> presentation_index_server;

PresentationQuestion* getPresentation (unsigned key)
{
    return presentation_index_server.getIdentityFromIndex(key);
}

unsigned addPresentationQuestion(PresentationQuestion * pQuestion)
{
    return presentation_index_server.addIndex(pQuestion);
}
void InitialisePresentation()
{
    current_interface = presentation_index_server.addIndex(&simulator);
}

void erasePresentationQuestion(unsigned key)
{
    presentation_index_server.eraseIndex(key);
}
unsigned GetSelectedEngine ()
{
    return current_interface;
}

void SetCurrentEngine (unsigned new_engine)
{
	current_interface = new_engine;
}
     
PresentationQuestion* GetSimulator ()
{
  return  &simulator;
}

//## end module%3AC3CD4901CE.additionalDeclarations


// Class PresentationQuestion 





//## Operation: PresentationQuestion%986448515
//	Constructor
PresentationQuestion::PresentationQuestion (const char* name, DWORD port_speed)
  //## begin PresentationQuestion::PresentationQuestion%986448515.hasinit preserve=no
      : _sequence_number(0), _retries(1), snLayer(NULL)
  //## end PresentationQuestion::PresentationQuestion%986448515.hasinit
  //## begin PresentationQuestion::PresentationQuestion%986448515.initialization preserve=yes
  //## end PresentationQuestion::PresentationQuestion%986448515.initialization
{
  if (name) 
  {  
    open (name, port_speed);
  }

  //## begin PresentationQuestion::PresentationQuestion%986448515.body preserve=yes
  //## end PresentationQuestion::PresentationQuestion%986448515.body
}


PresentationQuestion::~PresentationQuestion()
{
  //## begin PresentationQuestion::~PresentationQuestion%.body preserve=yes
  close();
  //## end PresentationQuestion::~PresentationQuestion%.body
}



//## Other Operations (implementation)
//## Operation: AskQuestion%985819689
//	The single function with which all querries to the
//	Engine are sent and responded to from. The parameters
//	are passed in and out as a series of Null terminated
//	strings. The function returns true ff the reply was
//	successful.
bool PresentationQuestion::AskQuestion (unsigned target_class, const BYTE* question, unsigned q_size, BYTE* ret_answer, unsigned r_size)
{
  //## begin PresentationQuestion::AskQuestion%985819689.body preserve=yes
  bool ret = false;
  unsigned long crc;

  const unsigned question_size = sizeof (short) // answer size
    + sizeof (BYTE) // one for sequence number
    + SMUtility::TargetClassBufSize () // for target class
    + sizeof (short) // the size of the question data
    + q_size // the callers q size
    + sizeof (DWORD); // CRC 32


  const unsigned answer_size = PresentationAnswer::ReturnBytes()
    + r_size // the callers return buffer
    + sizeof (DWORD); // CRC 32

  BYTE* app_question = new BYTE [question_size];
  BYTE* cursor = app_question;
  BYTE* app_answer = _answer;

  // now fill question
  cursor = SMUtility::IntToBuf ((short)answer_size, cursor); // rx buffer size
  *cursor = _sequence_number;
  cursor++;

  cursor = SMUtility::TargetClassToBuf (target_class, cursor);

  cursor = SMUtility::IntToBuf ((short)q_size, cursor); // question size buffer size

  memcpy (cursor, question, q_size); // calling function question buffer
  crc =  calculate_crc (cursor, q_size);

  cursor += q_size;

  SMUtility::DwordToBuf (crc, cursor);

  if (snLayer)
    {
      bool valid_answer = false; // we test for a valid answer by testing sequence number
      unsigned num_attempts = 0; // this is the number of times we have asked the question
      do
        {
          if (snLayer->AskQuestion (app_question, question_size, app_answer, answer_size))
            {
              const BYTE* cursor = app_answer;
              const BYTE ret_sequence = *cursor;
              cursor++;

              if (ret_sequence == _sequence_number)
                {
                  valid_answer = true;

                  bool event_waiting = (*cursor);
                  cursor++;
                  unsigned num_rx_bytes = SMUtility::BufToInt (&cursor);
                  if (event_waiting)
                    {
                      // prompt EventQuestion to ask a question
                      EventQuestion::EventWaiting();
                    }

                  if (num_rx_bytes <= r_size)
                    {
                      // Cursor is wRONG HERE
                      unsigned crc_offset = num_rx_bytes + PresentationAnswer::ReturnBytes();
                      const BYTE* crc_cursor = app_answer + crc_offset;
                      unsigned ret_crc = SMUtility::BufToDword (&crc_cursor);

                      crc =  calculate_crc (app_answer, num_rx_bytes + PresentationAnswer::ReturnBytes());

                      if (crc == ret_crc)
                      {
                        if (num_rx_bytes)
                          {
                          memcpy (ret_answer, cursor, num_rx_bytes);
                          }
                        ret = true;
                      }
                    }
                }

            }
          num_attempts++;
        } while (!valid_answer && _retries >= num_attempts);

      _sequence_number++;
    }

  delete [] app_question;

  return ret;
  //## end PresentationQuestion::AskQuestion%985819689.body
}

//## Operation: open%985819690
//	Opens  Presentation Question, using the name to
//	instantiate and open the lower layer interface
bool PresentationQuestion::open (const char* name, DWORD port_speed)
{
  //## begin PresentationQuestion::open%985819690.body preserve=yes
  close();

	snLayer = SessionQuestion::create(name, port_speed);
	return (snLayer);
  //## end PresentationQuestion::open%985819690.body
}

//## Operation: close%985819691
//	closes the interface that was previously opened
void PresentationQuestion::close ()
{
  //## begin PresentationQuestion::close%985819691.body preserve=yes
  if (snLayer)
  {
    SessionQuestion::destroy(snLayer);
    snLayer = NULL;
  }
  //## end PresentationQuestion::close%985819691.body
}

//## Operation: IsOpen%1020316780
bool PresentationQuestion::IsOpen ()
{
  return (snLayer);

  //## begin PresentationQuestion::IsOpen%1020316780.body preserve=yes
  //## end PresentationQuestion::IsOpen%1020316780.body
}

//## Operation: openfile%1022540279
//	Opens a SYSEX file question
bool PresentationQuestion::openfile (const char* filename)
{
  //## begin PresentationQuestion::openfile%1022540279.body preserve=yes
  close();

	snLayer = SessionQuestion::createfile(filename);
	return (snLayer);
  //## end PresentationQuestion::openfile%1022540279.body
}

//## Operation: SetInterfaceAddress%1082670125
//	Sets the Interface address of network Layer
bool PresentationQuestion::SetInterfaceAddress (const char* address)
{
  //## begin PresentationQuestion::SetInterfaceAddress%1082670125.body preserve=yes
  return snLayer->SetInterfaceAddress(address);
  //## end PresentationQuestion::SetInterfaceAddress%1082670125.body
}

// Additional Declarations
  //## begin PresentationQuestion%3AA806020126.declarations preserve=yes
  //## end PresentationQuestion%3AA806020126.declarations

//## begin module%3AC3CD4901CE.epilog preserve=yes
//## end module%3AC3CD4901CE.epilog
