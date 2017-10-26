//## begin module%3D473347019E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D473347019E.cm

//## begin module%3D473347019E.cp preserve=no
//	Angelo Fraietta
//## end module%3D473347019E.cp

//## Module: MacEvent%3D473347019E; Package body
//## Subsystem: hal_mac%3B255F3402D7
//## Source file: c:\develop\multithreads\source\hal_mac\macevent.cpp

//## begin module%3D473347019E.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3D473347019E.additionalIncludes

//## begin module%3D473347019E.includes preserve=yes
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <mach/mach.h>
#include <mach/clock.h>
#include <mach/mach_error.h>
//## end module%3D473347019E.includes

// Event
#include "event.h"
//## begin module%3D473347019E.declarations preserve=no
//## end module%3D473347019E.declarations

//## begin module%3D473347019E.additionalDeclarations preserve=yes
//## end module%3D473347019E.additionalDeclarations


//## begin MacEvent%3D4732CC026A.preface preserve=yes
//## end MacEvent%3D4732CC026A.preface

//## Class: MacEvent%3D4732CC026A
//	The event for the Mac is implemented as a semaphore.
//## Category: MultiThread::hal_mac%3D4719390298
//## Subsystem: hal_mac%3B255F3402D7
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class MacEvent : public Event  //## Inherits: <unnamed>%3D4732DA0089
{
  //## begin MacEvent%3D4732CC026A.initialDeclarations preserve=yes
  //## end MacEvent%3D4732CC026A.initialDeclarations

  public:
    //## Constructors (generated)
      MacEvent();

    //## Destructor (generated)
      ~MacEvent();


    //## Other Operations (specified)
      //## Operation: Wait%1028069953
      bool Wait (int timeout = -1);

      //## Operation: Release%1028069954
      void Release ();

    // Additional Public Declarations
      //## begin MacEvent%3D4732CC026A.public preserve=yes
      //## end MacEvent%3D4732CC026A.public

  protected:
    // Additional Protected Declarations
      //## begin MacEvent%3D4732CC026A.protected preserve=yes
      //## end MacEvent%3D4732CC026A.protected

  private:
    // Additional Private Declarations
      //## begin MacEvent%3D4732CC026A.private preserve=yes
      //## end MacEvent%3D4732CC026A.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin MacEvent%3D4732CC026A.implementation preserve=yes
      pthread_cond_t _eventId;
  pthread_mutex_t count_mutex;
      //## end MacEvent%3D4732CC026A.implementation
};

//## begin MacEvent%3D4732CC026A.postscript preserve=yes
//## end MacEvent%3D4732CC026A.postscript

// Class MacEvent 

// Class Event 


//## Other Operations (implementation)
//## Operation: create%1012532984
//	Static create function that returns the sub class,
//	depending upon the component
Event* Event::create ()
{
  //## begin Event::create%1012532984.body preserve=yes
	return new MacEvent;
  //## end Event::create%1012532984.body
}

// Additional Declarations
  //## begin Event%3C58CD02004A.declarations preserve=yes
  //## end Event%3C58CD02004A.declarations

// Class MacEvent 

MacEvent::MacEvent()
  //## begin MacEvent::MacEvent%.hasinit preserve=no
  //## end MacEvent::MacEvent%.hasinit
  //## begin MacEvent::MacEvent%.initialization preserve=yes
  //## end MacEvent::MacEvent%.initialization
{
  //## begin MacEvent::MacEvent%.body preserve=yes
  pthread_cond_init (&_eventId, NULL);
  pthread_mutex_init(&count_mutex, NULL);
  //## end MacEvent::MacEvent%.body
}


MacEvent::~MacEvent()
{
  //## begin MacEvent::~MacEvent%.body preserve=yes
  Release();
  pthread_cond_destroy(&_eventId);
  pthread_mutex_destroy(&count_mutex);
  //## end MacEvent::~MacEvent%.body
}



//## Other Operations (implementation)
//## Operation: Wait%1028069953
bool MacEvent::Wait (int timeout)
{
  //## begin MacEvent::Wait%1028069953.body preserve=yes
  bool ret = false;
  pthread_mutex_lock(&count_mutex);
  if (timeout == -1)
    {
      ret = !(pthread_cond_wait(&_eventId, &count_mutex));
    }
  else
    {
      struct timespec tv;
      struct timeval current_time;
      int wait_ret;
      long wait_sec, wait_ms;
      wait_sec = timeout / 1000;
      wait_ms = timeout % 1000;

      if (gettimeofday(&current_time, NULL))
				{
					printf("Unable to get current time");
				}
      else
				{
					wait_ms += current_time.tv_usec / 1000;
					// see if we are greater than 1000 in the milliseconds

					if (wait_ms >= 1000)
						{
							// reduce the ms by 1000 and increase seconds by 1
							wait_ms -= 1000;
							wait_sec++;
						}

					tv.tv_sec = current_time.tv_sec + wait_sec;
					tv.tv_nsec =  1000000 * wait_ms;   
					
					wait_ret = pthread_cond_timedwait(&_eventId, &count_mutex, &tv);
					
					switch (wait_ret)
						{
						case 0:
							ret = true;
							break;
							
						default:
							//printf (" event fail\r\n");
							break;
						}
				}
    }
  pthread_mutex_unlock(&count_mutex);
  return ret;
  //## end MacEvent::Wait%1028069953.body
}

//## Operation: Release%1028069954
void MacEvent::Release ()
{
  //## begin MacEvent::Release%1028069954.body preserve=yes
  pthread_mutex_lock(&count_mutex);
  pthread_cond_signal(&_eventId);
  pthread_mutex_unlock(&count_mutex);
  //## end MacEvent::Release%1028069954.body
}

// Additional Declarations
  //## begin MacEvent%3D4732CC026A.declarations preserve=yes
  //## end MacEvent%3D4732CC026A.declarations

//## begin module%3D473347019E.epilog preserve=yes
//## end module%3D473347019E.epilog
