//## begin module%3D4719D5004D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D4719D5004D.cm

//## begin module%3D4719D5004D.cp preserve=no
//	Angelo Fraietta
//## end module%3D4719D5004D.cp

//## Module: MacThread%3D4719D5004D; Package body
//## Subsystem: hal_mac%3B255F3402D7
//## Source file: c:\develop\multithreads\source\hal_mac\macthread.cpp

//## begin module%3D4719D5004D.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3D4719D5004D.additionalIncludes

//## begin module%3D4719D5004D.includes preserve=yes
#include <stdio.h>
#include <unistd.h>
#include "activeobject.h"
#include <pthread.h>
#include <iostream>
//## end module%3D4719D5004D.includes

// MultiThread
#include "multithread.h"

class MacThread;
class WindowsThread;
class RtemsThread;

//## begin module%3D4719D5004D.declarations preserve=no
//## end module%3D4719D5004D.declarations

//## begin module%3D4719D5004D.additionalDeclarations preserve=yes

#define kDefaultThreadStackSize 0
extern "C" void* ThreadEntry (void* param);

//## end module%3D4719D5004D.additionalDeclarations


//## begin MacThread%3D47197A0363.preface preserve=yes
//## end MacThread%3D47197A0363.preface

//## Class: MacThread%3D47197A0363
//## Category: MultiThread::hal_mac%3D4719390298
//## Subsystem: hal_mac%3B255F3402D7
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class MacThread : public MultiThread  //## Inherits: <unnamed>%3D4719900076
{
  //## begin MacThread%3D47197A0363.initialDeclarations preserve=yes
  //## end MacThread%3D47197A0363.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: MacThread%1028069949
      MacThread (ActiveObject* pActive);


    //## Other Operations (specified)
      //## Operation: resume%1028069950
      void resume ();

      //## Operation: wait%1028069951
      void wait (unsigned long period // The period we are going to wait
      );

    // Additional Public Declarations
      //## begin MacThread%3D47197A0363.public preserve=yes
      //## end MacThread%3D47197A0363.public

  protected:
    // Additional Protected Declarations
      //## begin MacThread%3D47197A0363.protected preserve=yes
      //## end MacThread%3D47197A0363.protected

  private:
    // Additional Private Declarations
      //## begin MacThread%3D47197A0363.private preserve=yes
      //## end MacThread%3D47197A0363.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin MacThread%3D47197A0363.implementation preserve=yes
  pthread_t _threadId;

      //## end MacThread%3D47197A0363.implementation
};

//## begin MacThread%3D47197A0363.postscript preserve=yes
//## end MacThread%3D47197A0363.postscript

// Class MacThread 

// Class MultiThread 



//## Other Operations (implementation)
//## Operation: create%994716922
//	Static create function that returns the sub class,
//	depending upon the component
MultiThread* MultiThread::create (ActiveObject* pActive)
{
  //## begin MultiThread::create%994716922.body preserve=yes
  return new MacThread(pActive);
  //## end MultiThread::create%994716922.body
}

// Additional Declarations
  //## begin MultiThread%3B255966033E.declarations preserve=yes
  //## end MultiThread%3B255966033E.declarations

// Class MacThread 

//## Operation: MacThread%1028069949
//	Constructor with parameter that points to ActiveObject
MacThread::MacThread (ActiveObject* pActive)
  //## begin MacThread::MacThread%1028069949.hasinit preserve=no
  //## end MacThread::MacThread%1028069949.hasinit
  //## begin MacThread::MacThread%1028069949.initialization preserve=yes
	:MultiThread (pActive)
  //## end MacThread::MacThread%1028069949.initialization
{
  //## begin MacThread::MacThread%1028069949.body preserve=yes
  //## end MacThread::MacThread%1028069949.body
}



//## Other Operations (implementation)
//## Operation: resume%1028069950
void MacThread::resume ()
{
  //## begin MacThread::resume%1028069950.body preserve=yes

  if (pthread_create(&_threadId, NULL, ThreadEntry, (void*)_pActive))
  {
    printf("Unable to create task");
  }
  
  //## end MacThread::resume%1028069950.body
}

//## Operation: wait%1028069951
//	Waits for the thread to finish
void MacThread::wait (unsigned long period)
{
  //## begin MacThread::wait%1028069951.body preserve=yes
  pthread_kill (_threadId, 0);
 #pragma unused(period)

  //## end MacThread::wait%1028069951.body
}

// Additional Declarations
  //## begin MacThread%3D47197A0363.declarations preserve=yes
  //## end MacThread%3D47197A0363.declarations

//## begin module%3D4719D5004D.epilog preserve=yes
extern "C" void* ThreadEntry (void* param)
{
    ActiveObject * pActive = (ActiveObject *) param;

	//sleep(1);
    pActive->initialise ();
    pActive->run ();
    
    

	printf("End Thread Entry");
	pthread_exit (NULL);
	
}

//## end module%3D4719D5004D.epilog
