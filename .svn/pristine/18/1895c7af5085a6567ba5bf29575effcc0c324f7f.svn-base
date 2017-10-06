//## begin module%3A92E14D0158.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A92E14D0158.cm

//## begin module%3A92E14D0158.cp preserve=no
//	Angelo Fraietta
//## end module%3A92E14D0158.cp

//## Module: scheduler%3A92E14D0158; Package body
//	Common Sheduler implementation
//## Subsystem: hal_include%3A80CC250114
//## Source file: c:\develop\SmartController\source\hal_include\scheduler.cpp

//## begin module%3A92E14D0158.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3A92E14D0158.additionalIncludes

//## begin module%3A92E14D0158.includes preserve=yes
//## end module%3A92E14D0158.includes

// scheduler
#include "scheduler.h"


//## begin module%3A92E14D0158.declarations preserve=no
//## end module%3A92E14D0158.declarations

//## begin module%3A92E14D0158.additionalDeclarations preserve=yes
//## end module%3A92E14D0158.additionalDeclarations


namespace hal_include {
  //## begin hal_include%3A80CAE10028.initialDeclarations preserve=yes
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
          ScheduledObject* pSchedule = new ScheduledObject (item);
          if (pSchedule)
            {
              ScheduledObjectPriority NextEvent (pSchedule);
              if (lock(lock_wait_time))
              {
                ScheduledItems.push(NextEvent);
              }
              else
              {
                delete pSchedule;
                pSchedule = NULL;
              }
            }
    
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
    bool ret = false;
    dwOffset = 0;	


    //## begin hal_include::Scheduler::initialise%981603322.body preserve=yes
    //## end hal_include::Scheduler::initialise%981603322.body

    return ret;
  }

  //## Operation: deinitialise%981603323
  //	Releases reources used by the scheduler
  bool Scheduler::deinitialise ()
  {
    purge ();

    //## begin hal_include::Scheduler::deinitialise%981603323.body preserve=yes
    //## end hal_include::Scheduler::deinitialise%981603323.body
  }

  //## Operation: getTime%981603750
  //	Returns the current time in milliseconds of the scheduler
  //## Preconditions:
  //	The Scheduler must be initialised
  DWORD Scheduler::getTime ()
  {
    //## begin hal_include::Scheduler::getTime%981603750.body preserve=yes
    //## end hal_include::Scheduler::getTime%981603750.body
  }

  //## Operation: processCallback%982638343
  //	Processes the callback and sends CallbackMessages
  void Scheduler::processCallback ()
  {
    volatile DWORD dwCurrentTime = getTime() - dwOffset;
    
    if (lock())
      {
        ScheduledObject* NextEvent = NULL;
        // we will remove from Queue so we can release the lock
        if (!ScheduledItems.empty() && ScheduledItems.top().CallbackTime() <= dwCurrentTime)
          {
            NextEvent = ScheduledItems.top()._scheduler;
            ScheduledItems.pop ();
          }
    
        unlock ();
    
        //see if it is time yet
        while (NextEvent)
          {
            if(NextEvent->valid)
              {
                NextEvent->valid = false;
                 //send the event
                NextEvent->Timer()->ReceiveClockTiming(NextEvent->Param());
              }
    
            delete NextEvent;
            NextEvent = NULL;
    
            if (lock())
            {
              // re-read the time in case we took a long time
              dwCurrentTime = getTime() - dwOffset;
              if (!ScheduledItems.empty() && ScheduledItems.top().CallbackTime() <= dwCurrentTime)
                {
                  NextEvent = ScheduledItems.top()._scheduler;
                  ScheduledItems.pop ();
                }
    
              unlock ();
            }
          } // end while
      }


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
    //## end hal_include::Scheduler::lock%982879202.body
  }

  //## Operation: unlock%982879203
  //	Unlocks the Scheduler and releases its critical
  //	sections. Returns true if unlocked.
  bool Scheduler::unlock ()
  {
    //## begin hal_include::Scheduler::unlock%982879203.body preserve=yes
    //## end hal_include::Scheduler::unlock%982879203.body
  }

  // Additional Declarations
    //## begin hal_include::Scheduler%3A80BBBF0082.declarations preserve=yes
    //## end hal_include::Scheduler%3A80BBBF0082.declarations

  // Class hal_include::ScheduledObject 





  // Additional Declarations
    //## begin hal_include::ScheduledObject%3A909E770117.declarations preserve=yes
    //## end hal_include::ScheduledObject%3A909E770117.declarations

  // Class hal_include::ScheduledObjectPriority 



  // Additional Declarations
    //## begin hal_include::ScheduledObjectPriority%3A91DD400060.declarations preserve=yes
    //## end hal_include::ScheduledObjectPriority%3A91DD400060.declarations

  //## begin hal_include::ScheduledObjectQueue.instantiation preserve=no
  template class sm_str::priority_queue< ScheduledObjectPriority >;
  //## end hal_include::ScheduledObjectQueue.instantiation
} // namespace hal_include

//## begin module%3A92E14D0158.epilog preserve=yes
//## end module%3A92E14D0158.epilog
