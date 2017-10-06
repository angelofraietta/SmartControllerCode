//## begin module%3B4A2C260046.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B4A2C260046.cm

//## begin module%3B4A2C260046.cp preserve=no
//	Angelo Fraietta
//## end module%3B4A2C260046.cp

//## Module: RtemsThread%3B4A2C260046; Package body
//## Subsystem: hal_rtems%3B255F2C0271
//## Source file: c:\develop\multithreads\source\hal_rtems\rtemsthread.cpp

//## begin module%3B4A2C260046.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3B4A2C260046.additionalIncludes

//## begin module%3B4A2C260046.includes preserve=yes
#include <rtems.h>

#include "activeobject.h"
#include <stdio.h>
//## end module%3B4A2C260046.includes

// MultiThread
#include "multithread.h"

class MacThread;
class WindowsThread;
class RtemsThread;

//## begin module%3B4A2C260046.declarations preserve=no
//## end module%3B4A2C260046.declarations

//## begin module%3B4A2C260046.additionalDeclarations preserve=yes
rtems_task thread_task(rtems_task_argument param );
//## end module%3B4A2C260046.additionalDeclarations


//## begin RtemsThread%3B4A2B500066.preface preserve=yes
//## end RtemsThread%3B4A2B500066.preface

//## Class: RtemsThread%3B4A2B500066
//## Category: MultiThread::hal_rtems%3B4A2D6C0207
//## Subsystem: hal_rtems%3B255F2C0271
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class RtemsThread : public MultiThread  //## Inherits: <unnamed>%3B4A2B930211
{
  //## begin RtemsThread%3B4A2B500066.initialDeclarations preserve=yes
  //## end RtemsThread%3B4A2B500066.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: RtemsThread%994716926
      RtemsThread (ActiveObject* pActive);

    //## Destructor (generated)
      ~RtemsThread();


    //## Other Operations (specified)
      //## Operation: resume%994716927
      void resume ();

      //## Operation: wait%994716928
      void wait (unsigned long period	// The period we are going to wait
      );

    // Additional Public Declarations
      //## begin RtemsThread%3B4A2B500066.public preserve=yes
      //## end RtemsThread%3B4A2B500066.public

  protected:
    // Additional Protected Declarations
      //## begin RtemsThread%3B4A2B500066.protected preserve=yes
      //## end RtemsThread%3B4A2B500066.protected

  private:
    // Additional Private Declarations
      //## begin RtemsThread%3B4A2B500066.private preserve=yes
	rtems_id   Task_id;
	rtems_name Task_name;
	ActiveObject * _pActive;
      //## end RtemsThread%3B4A2B500066.private
  private: //## implementation
    // Additional Implementation Declarations
      //## begin RtemsThread%3B4A2B500066.implementation preserve=yes
      //## end RtemsThread%3B4A2B500066.implementation

};

//## begin RtemsThread%3B4A2B500066.postscript preserve=yes
//## end RtemsThread%3B4A2B500066.postscript

// Class RtemsThread 

// Class MultiThread 



//## Other Operations (implementation)
//## Operation: create%994716922
//	Static create function that returns the sub class,
//	depending upon the component
MultiThread* MultiThread::create (ActiveObject* pActive)
{
  //## begin MultiThread::create%994716922.body preserve=yes
	return new RtemsThread(pActive);
  //## end MultiThread::create%994716922.body
}

// Additional Declarations
  //## begin MultiThread%3B255966033E.declarations preserve=yes
  //## end MultiThread%3B255966033E.declarations

// Class RtemsThread 

//## Operation: RtemsThread%994716926
//	Constructor with parameter that points to ActiveObject
RtemsThread::RtemsThread (ActiveObject* pActive)
  //## begin RtemsThread::RtemsThread%994716926.hasinit preserve=no
  //## end RtemsThread::RtemsThread%994716926.hasinit
  //## begin RtemsThread::RtemsThread%994716926.initialization preserve=yes
	:MultiThread (pActive), _pActive(pActive)
  //## end RtemsThread::RtemsThread%994716926.initialization
{
  //## begin RtemsThread::RtemsThread%994716926.body preserve=yes
	rtems_status_code status;	
	Task_name = rtems_build_name( 'T', 'A', '4', ' ' );
  
  status = rtems_task_create(Task_name, 10, RTEMS_MINIMUM_STACK_SIZE * 10, RTEMS_TIMESLICE, RTEMS_DEFAULT_ATTRIBUTES, &Task_id );

	if (status != RTEMS_SUCCESSFUL)
		{
			printf("unable to create task\r\n");
		}

  //## end RtemsThread::RtemsThread%994716926.body
}


RtemsThread::~RtemsThread()
{
  //## begin RtemsThread::~RtemsThread%.body preserve=yes
  //## end RtemsThread::~RtemsThread%.body
}



//## Other Operations (implementation)
//## Operation: resume%994716927
void RtemsThread::resume ()
{
  //## begin RtemsThread::resume%994716927.body preserve=yes
	rtems_status_code status;	

	status = rtems_task_start( Task_id, thread_task, (rtems_task_argument)_pActive );

	if (status != RTEMS_SUCCESSFUL)
		{
			printf ("unable to Start task\r\n");
		}

		

  //## end RtemsThread::resume%994716927.body
}

//## Operation: wait%994716928
//	Waits for the thread to finish
void RtemsThread::wait (unsigned long period)
{
  //## begin RtemsThread::wait%994716928.body preserve=yes
  //## end RtemsThread::wait%994716928.body
}

// Additional Declarations
  //## begin RtemsThread%3B4A2B500066.declarations preserve=yes
rtems_task thread_task(rtems_task_argument param )
{ 
	ActiveObject * pActive = (ActiveObject *) param;
	pActive->initialise ();
	pActive->run ();

}
  //## end RtemsThread%3B4A2B500066.declarations
//## begin module%3B4A2C260046.epilog preserve=yes
//## end module%3B4A2C260046.epilog
