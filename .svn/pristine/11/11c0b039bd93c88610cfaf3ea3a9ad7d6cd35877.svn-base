//## begin module%3CFC0279023A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CFC0279023A.cm

//## begin module%3CFC0279023A.cp preserve=no
//	Angelo Fraietta
//## end module%3CFC0279023A.cp

//## Module: QuestionTask%3CFC0279023A; Pseudo Package body
//## Subsystem: engineinterface%3A9C858C00CB
//## Source file: d:\develop\smartcontroller\controller\source\engineinterface\questiontask.cpp

//## begin module%3CFC0279023A.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3CFC0279023A.additionalIncludes

//## begin module%3CFC0279023A.includes preserve=yes
#include <stdio.h>
#include "simulatorinterface.h"
//## end module%3CFC0279023A.includes

// SessionInterface
#include "sessioninterface.h"
// QuestionTask
#include "questiontask.h"
// Event
#include "event.h"
//## begin module%3CFC0279023A.additionalDeclarations preserve=yes
//## end module%3CFC0279023A.additionalDeclarations


// Class QuestionTask 





//## Operation: QuestionTask%1023147565
//	Constructor
QuestionTask::QuestionTask (StreamedQuestion* pQuestion)
  //## begin QuestionTask::QuestionTask%1023147565.hasinit preserve=no
      : _timeout(2000), _pWaitEvent(Event::create()), _pQuestionEvent(Event::create()), _pQuestion(pQuestion)
  //## end QuestionTask::QuestionTask%1023147565.hasinit
  //## begin QuestionTask::QuestionTask%1023147565.initialization preserve=yes
  //## end QuestionTask::QuestionTask%1023147565.initialization
{
  //## begin QuestionTask::QuestionTask%1023147565.body preserve=yes
  //## end QuestionTask::QuestionTask%1023147565.body
}


QuestionTask::~QuestionTask()
{
  //## begin QuestionTask::~QuestionTask%.body preserve=yes
  delete _pWaitEvent;
  delete _pQuestionEvent;
  //## end QuestionTask::~QuestionTask%.body
}



//## Other Operations (implementation)
//## Operation: run%1023147566
void QuestionTask::run ()
{
  //## begin QuestionTask::run%1023147566.body preserve=yes
  while (!Terminated())
  {
    _pQuestionEvent->Wait(0); // clear any event currently here
    
  	_pWaitEvent->Wait();
    if (!Terminated())
    {
      if (!_pQuestionEvent->Wait(_timeout))
      {
        _pQuestion->Flush();
      }
    }
  }

  //## end QuestionTask::run%1023147566.body
}

//## Operation: go%1023147567
bool QuestionTask::go (int timeout)
{
  //## begin QuestionTask::go%1023147567.body preserve=yes
  _timeout = timeout;
  _pWaitEvent->Release();

  return true;
  //## end QuestionTask::go%1023147567.body
}

//## Operation: flush%1029987707
//	Abstract function that tells superclass to stop what it
//	is doing and return.
void QuestionTask::flush ()
{
  //## begin QuestionTask::flush%1029987707.body preserve=yes
  _pWaitEvent->Release();
  _pQuestionEvent->Release();
  //## end QuestionTask::flush%1029987707.body
}

//## Operation: wait%1083901317
//	Sets the event to preent the task from flushing the
//	buffer
void QuestionTask::wait ()
{
  //## begin QuestionTask::wait%1083901317.body preserve=yes
  _pQuestionEvent->Release();
  //## end QuestionTask::wait%1083901317.body
}

// Additional Declarations
  //## begin QuestionTask%3CFC0279023A.declarations preserve=yes
  //## end QuestionTask%3CFC0279023A.declarations

//## begin module%3CFC0279023A.epilog preserve=yes
//## end module%3CFC0279023A.epilog
