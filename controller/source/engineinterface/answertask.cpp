//## begin module%3B2542A300C8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B2542A300C8.cm

//## begin module%3B2542A300C8.cp preserve=no
//	Angelo Fraietta
//## end module%3B2542A300C8.cp

//## Module: AnswerTask%3B2542A300C8; Package body
//	Windows implementation for answer_task
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\answertask.cpp

//## begin module%3B2542A300C8.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3B2542A300C8.additionalIncludes

//## begin module%3B2542A300C8.includes preserve=yes
#include <stddef.h>
#include <stdio.h>
#include "event.h"
#include "equeue.h"
//## end module%3B2542A300C8.includes

// SessionInterface
#include "sessioninterface.h"
// PresentationAnswer
#include "presentationanswer.h"
// AnswerTask
#include "answertask.h"


//## begin module%3B2542A300C8.declarations preserve=no
//## end module%3B2542A300C8.declarations

//## begin module%3B2542A300C8.additionalDeclarations preserve=yes
//#define SHOW_DEBUG
class DiagTask;
static DiagTask* _diag_task = 0;
//## end module%3B2542A300C8.additionalDeclarations


//## begin DiagTask%3ED673DC000B.preface preserve=yes
//## end DiagTask%3ED673DC000B.preface

//## Class: DiagTask%3ED673DC000B
//	Task That writes data to the AnswerTask within its own
//	thread
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class DiagTask : public ActiveObject  //## Inherits: <unnamed>%3ED673E60377
{
  //## begin DiagTask%3ED673DC000B.initialDeclarations preserve=yes
  //## end DiagTask%3ED673DC000B.initialDeclarations

  public:
    //## Constructors (generated)
      DiagTask();

    //## Destructor (generated)
      ~DiagTask();


    //## Other Operations (specified)
      //## Operation: run%1054242215
      void run ();

      //## Operation: WriteData%1054242216
      bool WriteData (const char* message);

    // Additional Public Declarations
      //## begin DiagTask%3ED673DC000B.public preserve=yes
      //## end DiagTask%3ED673DC000B.public

  protected:
    // Additional Protected Declarations
      //## begin DiagTask%3ED673DC000B.protected preserve=yes
      //## end DiagTask%3ED673DC000B.protected

  private:
    // Additional Private Declarations
      //## begin DiagTask%3ED673DC000B.private preserve=yes
      sm_str::e_static_queue<char> pData;
      //## end DiagTask%3ED673DC000B.private

  private: //## implementation
    // Data Members for Associations

      //## Association: EngineInterface::Answer::<unnamed>%3ED674DD01F6
      //## Role: DiagTask::_pEvent%3ED674DD039B
      //## begin DiagTask::_pEvent%3ED674DD039B.role preserve=no  public: Event { -> 1RFHN}
      Event *_pEvent;
      //## end DiagTask::_pEvent%3ED674DD039B.role

    // Additional Implementation Declarations
      //## begin DiagTask%3ED673DC000B.implementation preserve=yes
      //## end DiagTask%3ED673DC000B.implementation

};

//## begin DiagTask%3ED673DC000B.postscript preserve=yes
//## end DiagTask%3ED673DC000B.postscript

// Class DiagTask 

// Class AnswerTask 

//## begin AnswerTask::_default_task%3E48260E01E9.attr preserve=no  public: static AnswerTask* {U} NULL
AnswerTask* AnswerTask::_default_task = NULL;
//## end AnswerTask::_default_task%3E48260E01E9.attr




AnswerTask::AnswerTask()
  //## begin AnswerTask::AnswerTask%.hasinit preserve=no
      : _pThread(new ActiveThread (this)), _presentation(new PresentationAnswer), _stream(new StreamedAnswer)
  //## end AnswerTask::AnswerTask%.hasinit
  //## begin AnswerTask::AnswerTask%.initialization preserve=yes
  //## end AnswerTask::AnswerTask%.initialization
{
  //## begin AnswerTask::AnswerTask%.body preserve=yes
  //## end AnswerTask::AnswerTask%.body
}


AnswerTask::~AnswerTask()
{
  //## begin AnswerTask::~AnswerTask%.body preserve=yes
    delete _pThread;
    delete _stream;
    delete _presentation;

  //## end AnswerTask::~AnswerTask%.body
}



//## Other Operations (implementation)
//## Operation: startTask%992232180
//	Opens the lower layer device, using the name and speed
//	as a parameter, and starts the thead task
bool AnswerTask::startTask (const char* name, unsigned port_speed)
{
  //## begin AnswerTask::startTask%992232180.body preserve=yes
	_stream->open (name, port_speed, 1024);
    _pThread->start();
    //return (_stream);
		return true;
  //## end AnswerTask::startTask%992232180.body
}

//## Operation: stopTask%992232181
//	Closes the comm port and exits the thread
bool AnswerTask::stopTask ()
{
  //## begin AnswerTask::stopTask%992232181.body preserve=yes
  return false;
  //## end AnswerTask::stopTask%992232181.body
}

//## Operation: processQuestion%992473059
//	Reads and writes from stream
void AnswerTask::processQuestion ()
{
  //## begin AnswerTask::processQuestion%992473059.body preserve=yes
    // read the question

    const BYTE* question;
				
		unsigned return_buffer_size = _stream->GetQuestion(&question);

#ifdef SHOW_DEBUG
	printf ("ProcessQuestion %u\r\n", return_buffer_size);
#endif

		BYTE* p_answer;
		
		unsigned bytes_to_write = _presentation->GetAnswer (question, &p_answer, return_buffer_size);

#ifdef SHOW_DEBUG
	printf ("Send Answer %u\r\n", bytes_to_write);
#endif

		_stream->SendAnswer (p_answer, bytes_to_write);
				

  //## end AnswerTask::processQuestion%992473059.body
}

//## Operation: WriteRawData%1044915130
//	Writes raw data to default ANSWER TASK
void AnswerTask::WriteRawData (const char* buf, unsigned long buf_len)
{
  //## begin AnswerTask::WriteRawData%1044915130.body preserve=yes
  if (_default_task)
  {
    _default_task->_stream->SendRaw ((const BYTE*)buf, buf_len);
  }
  //## end AnswerTask::WriteRawData%1044915130.body
}

// Additional Declarations
  //## begin AnswerTask%3AEF323701FF.declarations preserve=yes
  //## end AnswerTask%3AEF323701FF.declarations

// Class ActiveThread 


//## Operation: ActiveThread%992298027
//	Constructor
ActiveThread::ActiveThread (AnswerTask* pTask)
  //## begin ActiveThread::ActiveThread%992298027.hasinit preserve=no
      : _pTask(pTask)
  //## end ActiveThread::ActiveThread%992298027.hasinit
  //## begin ActiveThread::ActiveThread%992298027.initialization preserve=yes
  //## end ActiveThread::ActiveThread%992298027.initialization
{
  //## begin ActiveThread::ActiveThread%992298027.body preserve=yes
  //## end ActiveThread::ActiveThread%992298027.body
}


ActiveThread::~ActiveThread()
{
  //## begin ActiveThread::~ActiveThread%.body preserve=yes
  //## end ActiveThread::~ActiveThread%.body
}



//## Other Operations (implementation)
//## Operation: run%992298026
//	The actual function of the task
void ActiveThread::run ()
{
  //## begin ActiveThread::run%992298026.body preserve=yes

    while (!Terminated())
    {
      _pTask->processQuestion();
    }  
  //## end ActiveThread::run%992298026.body
}

// Additional Declarations
  //## begin ActiveThread%3B25439B01E7.declarations preserve=yes
  //## end ActiveThread%3B25439B01E7.declarations

// Class DiagTask 


DiagTask::DiagTask()
  //## begin DiagTask::DiagTask%.hasinit preserve=no
      : _pEvent(Event::create())
  //## end DiagTask::DiagTask%.hasinit
  //## begin DiagTask::DiagTask%.initialization preserve=yes
  , pData (1024) // this is the buffer size
  //## end DiagTask::DiagTask%.initialization
{
  //## begin DiagTask::DiagTask%.body preserve=yes
  //## end DiagTask::DiagTask%.body
}


DiagTask::~DiagTask()
{
  //## begin DiagTask::~DiagTask%.body preserve=yes
  kill();
  delete _pEvent;
  //## end DiagTask::~DiagTask%.body
}



//## Other Operations (implementation)
//## Operation: run%1054242215
//	The actual function of the task
void DiagTask::run ()
{
  //## begin DiagTask::run%1054242215.body preserve=yes
  while (!Terminated())
		{
			if (_pEvent->Wait())
				{
					if (!Terminated())
						{
							char c;
              while (!pData.empty())
                {
                  c =  pData.top();
                  pData.pop();
                  AnswerTask::WriteRawData (&c, 1);
                  printf ("%c", c);
                }
						}
				}
			else
				{
					//cout<<"TestThread:event not received (this is OK)"<<endl;
					printf("Diag Task::Event not received\r\n");
				}
		}

  //## end DiagTask::run%1054242215.body
}

//## Operation: WriteData%1054242216
//	Writes data to diag and sets event
bool DiagTask::WriteData (const char* message)
{
  //## begin DiagTask::WriteData%1054242216.body preserve=yes
  bool ret = true;
  while (ret && *message)
  {
    ret = pData.push(*message);
    message++;
  }

  _pEvent->Release();
  return ret;
  //## end DiagTask::WriteData%1054242216.body
}

// Additional Declarations
  //## begin DiagTask%3ED673DC000B.declarations preserve=yes
extern "C" void DisplayDiags(const char* message)
{
	  if (_diag_task)
  {
    _diag_task->WriteData(message);
  }
	
}
  //## end DiagTask%3ED673DC000B.declarations
//## begin module%3B2542A300C8.epilog preserve=yes
extern "C" int StartDiagTask()
{
  bool ret = false;

  if (!_diag_task)
  {
    _diag_task = new DiagTask();
    _diag_task->start();
    ret = true;
  }

  return ret;
}
//## end module%3B2542A300C8.epilog
