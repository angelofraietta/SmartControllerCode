//## begin module%3A92EBCC021A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A92EBCC021A.cm

//## begin module%3A92EBCC021A.cp preserve=no
//	Angelo Fraietta
//## end module%3A92EBCC021A.cp

//## Module: windows_scheduler%3A92EBCC021A; Package body
//	Windows Scheduler Implementation
//## Subsystem: hal_windows%3A80A55A00D8
//## Source file: d:\develop\SmartController\controller\source\hal_windows\scheduler.cpp

//## begin module%3A92EBCC021A.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3A92EBCC021A.additionalIncludes

//## begin module%3A92EBCC021A.includes preserve=yes
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
//## end module%3A92EBCC021A.includes

// memorycache
#include "memorycache.h"
// timer
#include "timer.h"
// scheduler
#include "scheduler.h"


//## begin module%3A92EBCC021A.declarations preserve=no
//## end module%3A92EBCC021A.declarations

//## begin module%3A92EBCC021A.additionalDeclarations preserve=yes
static unsigned TimerID = 0;//windows timer event
static HANDLE engine_lock;
//## end module%3A92EBCC021A.additionalDeclarations


namespace hal_include {
  //## begin hal_include%3A80CAE10028.initialDeclarations preserve=yes

  // callback function
  void CALLBACK ScheduleCallback(UINT wTimerID, UINT msg,
    DWORD dwUser, DWORD dw1, DWORD dw2);

  bool GoOneShot (unsigned milliseconds);

  //## end hal_include%3A80CAE10028.initialDeclarations

  // Class Utility hal_include::Scheduler 

  //## begin hal_include::Scheduler::initialised%3A9452E30298.attr preserve=no  private: static bool {UT} false
  volatile bool  Scheduler::initialised = false;
  //## end hal_include::Scheduler::initialised%3A9452E30298.attr

  //## begin hal_include::Scheduler::dwOffset%3A91E2CD00DB.attr preserve=no  private: static DWORD {UT} 0
  volatile DWORD  Scheduler::dwOffset = 0;
  //## end hal_include::Scheduler::dwOffset%3A91E2CD00DB.attr

  //## begin hal_include::Scheduler::dwPauseTime%3A9452F5004F.attr preserve=no  private: static DWORD {UT} 0
  volatile DWORD  Scheduler::dwPauseTime = 0;
  //## end hal_include::Scheduler::dwPauseTime%3A9452F5004F.attr

  //## begin hal_include::Scheduler::lock_wait_time%3A95CF7E0253.attr preserve=no  private: static unsigned {U} 10
  unsigned Scheduler::lock_wait_time = 10;
  //## end hal_include::Scheduler::lock_wait_time%3A95CF7E0253.attr

  //## begin hal_include::Scheduler::<the_ScheduledObjectPriority>%3A92EB3A02B0.role preserve=no  public: hal_include::ScheduledObjectPriority { -> RFHN}
  //## end hal_include::Scheduler::<the_ScheduledObjectPriority>%3A92EB3A02B0.role

  //## begin hal_include::Scheduler::ScheduledItems%3A92FF700133.role preserve=no  public: hal_include::ScheduledObjectQueue { -> 1VFHN}
  ScheduledObjectQueue Scheduler::ScheduledItems;
  //## end hal_include::Scheduler::ScheduledItems%3A92FF700133.role


  //## Other Operations (implementation)
  //## Operation: SetTimeEvent%981519022
  //	Tells scheduler to add a Time event. Returns true if
  //	successfull.
  //## Preconditions:
  //	The Scheduler must be initialised
  //## Postconditions:
  //	The new time event is added to que of events
  ScheduledObject* Scheduler::SetTimeEvent (const TimerQueueItem& item)
  {
        ScheduledObject* pSchedule = NULL;
        if (lock())
          {
            pSchedule = new ScheduledObject (item);
            
            if (pSchedule)
              {
                ScheduledObjectPriority NextEvent (pSchedule);
                ScheduledItems.push(NextEvent);
              }
            unlock();
          } // end Locked
        
        resume();
        return pSchedule;


    //## begin hal_include::Scheduler::SetTimeEvent%981519022.body preserve=yes
    //## end hal_include::Scheduler::SetTimeEvent%981519022.body
  }

  //## Operation: KillTimeEvent%981519023
  //	Tells scheduler to remove a Time event.
  //## Preconditions:
  //	The Scheduler must be initialised
  //## Postconditions:
  //	The Time event will not be called
  void Scheduler::KillTimeEvent (ScheduledObject* item)
  {
    if (item)
      {
        item->valid = false;
      }


    //## begin hal_include::Scheduler::KillTimeEvent%981519023.body preserve=yes
    //## end hal_include::Scheduler::KillTimeEvent%981519023.body
  }

  //## Operation: initialise%981603322
  //	Obtains reources used by the scheduler
  bool Scheduler::initialise ()
  {
    bool ret = true;
    if (!initialised)
    {
       dwOffset = 0;	
      //_mem_manager = new MemoryCache;
    }

    //## begin hal_include::Scheduler::initialise%981603322.body preserve=yes
		if (!initialised)
			{
				engine_lock =  CreateSemaphore (NULL, 1, 1, NULL);
				ret = (engine_lock);
			}
		initialised = true;

    //## end hal_include::Scheduler::initialise%981603322.body

    return ret;
  }

  //## Operation: deinitialise%981603323
  //	Releases reources used by the scheduler
  bool Scheduler::deinitialise ()
  {
    purge ();
    //delete _mem_manager;
    //_mem_manager = 0;
    initialised = false;

    //## begin hal_include::Scheduler::deinitialise%981603323.body preserve=yes
		// purge Items from here first
    return true;
    //## end hal_include::Scheduler::deinitialise%981603323.body
  }

  //## Operation: getTime%981603750
  //	Returns the current time in milliseconds of the scheduler
  //## Preconditions:
  //	The Scheduler must be initialised
  DWORD Scheduler::getTime ()
  {
    //## begin hal_include::Scheduler::getTime%981603750.body preserve=yes
    DWORD time = timeGetTime();
    return time;
    //## end hal_include::Scheduler::getTime%981603750.body
  }

  //## Operation: processCallback%982638343
  //	Processes the callback and sends CallbackMessages.
  //	Returns the time required for the next Callback
  DWORD Scheduler::processCallback ()
  {
    volatile DWORD dwCurrentTime = getTime() - dwOffset;
                
    DWORD return_event_time = (DWORD)-1;
                    
    if (lock())
      {
        ScheduledObject* NextEvent = NULL;
        // we will remove from Queue so we can release the lock
        if (!ScheduledItems.empty() && ScheduledItems.top().CallbackTime() <= dwCurrentTime)
          {
            NextEvent = ScheduledItems.top()._scheduler;
            ScheduledItems.pop ();
          }
        else
          {
            if (!ScheduledItems.empty())
              {
                return_event_time = ScheduledItems.top().CallbackTime() - dwCurrentTime;
              }
          }
                        
        unlock ();
                        
        //see if it is time yet
        while (NextEvent)
          {
            if(NextEvent->valid)
              {
                NextEvent->valid = false;
                //send the event
                // we need to protect this area so only one task can enter the engine
                if (LockEngine ((unsigned (-1))))
                  {
                  NextEvent->Timer()->ReceiveClockTiming(NextEvent->Param());
                  UnlockEngine();
        
                  delete NextEvent;
                  NextEvent = NULL;
                  }
              }
            else // not valid
              {
              delete NextEvent;
              NextEvent = NULL;
              }
        
        
            if (lock())
              {
                // re-read the time in case we took a long time
                dwCurrentTime = getTime() - dwOffset;
                if (!ScheduledItems.empty())
                  {
                    if(ScheduledItems.top().CallbackTime() <= dwCurrentTime)
                      {
                        NextEvent = ScheduledItems.top()._scheduler;
                        ScheduledItems.pop ();
                      }
                    else
                      {
                        return_event_time = ScheduledItems.top().CallbackTime() - dwCurrentTime;
                      }
                  }
                                
                unlock ();
              }
            else
              {
                printf("Unable to lock Schedule\r\n");
                return_event_time = 1;
              }
          } // end while
      }
    else
      {
        return_event_time = 1;
        printf("Unable to lock Schedule\r\n");
      }
                    
    return return_event_time;


    //## begin hal_include::Scheduler::processCallback%982638343.body preserve=yes
    //## end hal_include::Scheduler::processCallback%982638343.body
  }

  //## Operation: pause%982638344
  //	pause al callbacks until resume is called
  void Scheduler::pause ()
  {
    //## begin hal_include::Scheduler::pause%982638344.body preserve=yes
    //## end hal_include::Scheduler::pause%982638344.body
  }

  //## Operation: resume%982638345
  //	resume scheduling. Called to resume after pausing with
  //	pause.
  void Scheduler::resume ()
  {
    //## begin hal_include::Scheduler::resume%982638345.body preserve=yes
    GoOneShot (1);

    //## end hal_include::Scheduler::resume%982638345.body
  }

  //## Operation: purge%982879201
  //	Purge all items in queue
  void Scheduler::purge ()
  {
        while (!ScheduledItems.empty())
          {
            if (lock())
              {
                ScheduledObject* NextEvent = ScheduledItems.top()._scheduler;
                if(NextEvent->valid)
                  {
                    //Tell Timer to Purge all events
                    NextEvent->Timer()->Purge();
                  }
                ScheduledItems.pop(); //now remove item
                delete NextEvent;
              }
    				unlock();
          } // end while


    //## begin hal_include::Scheduler::purge%982879201.body preserve=yes
    //## end hal_include::Scheduler::purge%982879201.body
  }

  //## Operation: lock%982879202
  //	Locks the Scheduler to protect its critical sections.
  //	Returns true if successful.
  bool Scheduler::lock (unsigned period)
  {
    //## begin hal_include::Scheduler::lock%982879202.body preserve=yes
    return true;
    //## end hal_include::Scheduler::lock%982879202.body
  }

  //## Operation: unlock%982879203
  //	Unlocks the Scheduler and releases its critical
  //	sections. Returns true if unlocked.
  bool Scheduler::unlock ()
  {
    //## begin hal_include::Scheduler::unlock%982879203.body preserve=yes
    return true;
    //## end hal_include::Scheduler::unlock%982879203.body
  }

  //## Operation: LockEngine%1018482872
  //	A public lock to limit access to the engne to a single
  //	task
  bool Scheduler::LockEngine (unsigned wait_period)
  {
    //## begin hal_include::Scheduler::LockEngine%1018482872.body preserve=yes
    bool ret = (WaitForSingleObject (engine_lock, wait_period) == WAIT_OBJECT_0);
    return ret;
    //## end hal_include::Scheduler::LockEngine%1018482872.body
  }

  //## Operation: UnlockEngine%1018482873
  //	Release Function For LockEngineFunction
  bool Scheduler::UnlockEngine ()
  {
    //## begin hal_include::Scheduler::UnlockEngine%1018482873.body preserve=yes


    return ReleaseSemaphore (engine_lock, 1, NULL);
    //## end hal_include::Scheduler::UnlockEngine%1018482873.body
  }

  // Additional Declarations
    //## begin hal_include::Scheduler%3A80BBBF0082.declarations preserve=yes

void CALLBACK ScheduleCallback(UINT wTimerID, UINT msg,
    DWORD dwUser, DWORD dw1, DWORD dw2)
{
    TimerID = 0;
    unsigned duration = Scheduler::processCallback ();
    GoOneShot (duration);
    
    UNREFERENCED_PARAMETER (msg);
    UNREFERENCED_PARAMETER (dwUser);
    UNREFERENCED_PARAMETER (dw1);
    UNREFERENCED_PARAMETER (dw2);
    UNREFERENCED_PARAMETER (wTimerID);
}

bool GoOneShot (unsigned Interval)
  {
  if (TimerID)
  {
    timeKillEvent(TimerID);
  }
  
    TimerID = timeSetEvent(
            Interval,                    // delay
            1,                            // resolution in MS
           ScheduleCallback,               // callback function
           0,                              // user data
        TIME_ONESHOT );

    return (TimerID);
  }

    //## end hal_include::Scheduler%3A80BBBF0082.declarations
  // Class hal_include::ScheduledObject 





  //## begin hal_include::ScheduledObject::_mem_manager%3CCE19A8006D.role preserve=no  public: static MemoryCache { -> 1RHN}
  MemoryCache ScheduledObject::_mem_manager;
  //## end hal_include::ScheduledObject::_mem_manager%3CCE19A8006D.role

  //## Operation: operator new%1020137284
  //	Overloaded allocation operator
  //## Preconditions:
  //	The Scheduler is already locked before this function is
  //	called
  void* ScheduledObject::operator new (size_t size)
  {
    //## begin hal_include::ScheduledObject::operator new%1020137284.body preserve=yes
    //## end hal_include::ScheduledObject::operator new%1020137284.body

    return _mem_manager.allocate(size);
  }

  //## Operation: operator delete%1020137285
  //	Overloaded de allocation operator
  void ScheduledObject::operator delete (void* mem)
  {
    //## begin hal_include::ScheduledObject::operator delete%1020137285.body preserve=yes
    //## end hal_include::ScheduledObject::operator delete%1020137285.body

    Scheduler::lock();
    _mem_manager.free(mem);
    Scheduler::unlock();

  }


  // Additional Declarations
    //## begin hal_include::ScheduledObject%3A909E770117.declarations preserve=yes
    //## end hal_include::ScheduledObject%3A909E770117.declarations

} // namespace hal_include

//## begin module%3A92EBCC021A.epilog preserve=yes
//## end module%3A92EBCC021A.epilog
