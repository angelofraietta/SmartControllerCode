//## begin module%3B2542A300C8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B2542A300C8.cm

//## begin module%3B2542A300C8.cp preserve=no
//	Angelo Fraietta
//## end module%3B2542A300C8.cp

//## Module: windows_answer_task%3B2542A300C8; Package body
//	Windows implementation for answer_task
//## Subsystem: hal_windows%3A80A55A00D8
//## Source file: c:\develop\SmartController\controller\source\hal_windows\windows_answer_task.cpp

//## begin module%3B2542A300C8.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3B2542A300C8.additionalIncludes

//## begin module%3B2542A300C8.includes preserve=yes
#include "presentationanswer.h"
#include "sessioninterface.h"
//## end module%3B2542A300C8.includes

// WinActiveObject
#include "winactiveobject.cpp"
// TaskThreads
#include "taskthreads.h"

class AnswerTask;

//## begin module%3B2542A300C8.declarations preserve=no
//## end module%3B2542A300C8.declarations

//## begin module%3B2542A300C8.additionalDeclarations preserve=yes
//## end module%3B2542A300C8.additionalDeclarations


namespace hal_include {
  //## begin hal_include%3A80CAE10028.initialDeclarations preserve=yes
  //## end hal_include%3A80CAE10028.initialDeclarations

  // Class hal_include::ActiveThread 


  //## Operation: ActiveThread%992298027
  //	Constructor
  ActiveThread::ActiveThread (AnswerTask* pTask)
    //## begin hal_include::ActiveThread::ActiveThread%992298027.hasinit preserve=no
        : _pTask(pTask)
    //## end hal_include::ActiveThread::ActiveThread%992298027.hasinit
    //## begin hal_include::ActiveThread::ActiveThread%992298027.initialization preserve=yes
    //## end hal_include::ActiveThread::ActiveThread%992298027.initialization
  {
    //## begin hal_include::ActiveThread::ActiveThread%992298027.body preserve=yes
    //## end hal_include::ActiveThread::ActiveThread%992298027.body
  }


  ActiveThread::~ActiveThread()
  {
    //## begin hal_include::ActiveThread::~ActiveThread%.body preserve=yes
    //## end hal_include::ActiveThread::~ActiveThread%.body
  }



  //## Other Operations (implementation)
  //## Operation: run%992298026
  //	The actual function of the task
  void ActiveThread::run ()
  {
    //## begin hal_include::ActiveThread::run%992298026.body preserve=yes
    while (!Terminated())
    {
      _pTask->processQuestion();
    }
    //## end hal_include::ActiveThread::run%992298026.body
  }

  // Additional Declarations
    //## begin hal_include::ActiveThread%3B25439B01E7.declarations preserve=yes
    //## end hal_include::ActiveThread%3B25439B01E7.declarations

} // namespace hal_include

//## begin module%3B2542A300C8.epilog preserve=yes
//## end module%3B2542A300C8.epilog
