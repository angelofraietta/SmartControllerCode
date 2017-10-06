//## begin module%3A92F41D00A8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A92F41D00A8.cm

//## begin module%3A92F41D00A8.cp preserve=no
//	Angelo Fraietta
//## end module%3A92F41D00A8.cp

//## Module: rtems_scheduler%3A92F41D00A8; Package body
//	RTEMS implementation of Scheduler
//## Subsystem: hal_rtems%3A80A5EB020D
//## Source file: d:\develop\SmartController\controller\source\hal_rtems_pc386\scheduler.cpp

//## begin module%3A92F41D00A8.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3A92F41D00A8.additionalIncludes

//## begin module%3A92F41D00A8.includes preserve=yes
#include <rtems.h>
#include <stdio.h>

//## end module%3A92F41D00A8.includes

// memorycache
#include "memorycache.h"
// timer
#include "timer.h"
// scheduler
#include "scheduler.h"


//## begin module%3A92F41D00A8.declarations preserve=no
//## end module%3A92F41D00A8.declarations

//## begin module%3A92F41D00A8.additionalDeclarations preserve=yes
//#define  _DISPLAY_TICKS
#define SCHEDULE_EVENT_EVENT_FLAG RTEMS_EVENT_1

static rtems_id   schedule_task_id;
static rtems_id schedule_task;
static rtems_id schedule_sem;
static rtems_id engine_sem;

static rtems_name Task_name;
static volatile bool exit_schedule = false;
static volatile bool scheduler_initialised = false;
rtems_task Scheduler_task ( rtems_task_argument unused); 

using hal_include::Scheduler;
//## end module%3A92F41D00A8.additionalDeclarations


namespace hal_include {
  //## begin hal_include%3A80CAE10028.initialDeclarations preserve=yes
	DWORD ms_per_tick = 1;
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
    exit_schedule = false;
    rtems_status_code status;
		rtems_interval ticks_per_second;

		rtems_clock_get( RTEMS_CLOCK_GET_TICKS_PER_SECOND, &ticks_per_second );  
		ms_per_tick = (DWORD)1000 / (DWORD)ticks_per_second;

    Task_name = rtems_build_name( 'S', 'C', 'H', 'S' ); 

		if (rtems_semaphore_create(Task_name, 1, 
															 RTEMS_PRIORITY | RTEMS_BINARY_SEMAPHORE,
															 RTEMS_NO_PRIORITY_CEILING, &schedule_sem ) != RTEMS_SUCCESSFUL)
			{
				printf("Unable To Create Scheduler Semaphore\r\n");
			}

    Task_name = rtems_build_name( 'E', 'N', 'G', 'S' ); 

		if (rtems_semaphore_create(Task_name, 1, 
															 RTEMS_PRIORITY | RTEMS_BINARY_SEMAPHORE,
															 RTEMS_NO_PRIORITY_CEILING, &engine_sem ) != RTEMS_SUCCESSFUL)
			{
				printf("Unable To Create Engine Lock Semaphore\r\n");
			}



		printf("Scheduler MS per tick: %u\r\n", (unsigned)ms_per_tick);

    Task_name = rtems_build_name( 'S', 'C', 'H', 'D' ); 
    
    status = rtems_task_create( Task_name, 2, RTEMS_MINIMUM_STACK_SIZE * 10, 
                                RTEMS_DEFAULT_MODES,
                                RTEMS_DEFAULT_ATTRIBUTES, &schedule_task_id );
		if (status != RTEMS_SUCCESSFUL)
			{
				printf("Unable to create Scheduler Task\r\n");
			}
		else
			{
				if (rtems_task_start( schedule_task_id, Scheduler_task , 1 ) != RTEMS_SUCCESSFUL)
					{
						printf("Unable To Start Schedule task\r\n");
					}
			}
    
    
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
    exit_schedule = true;
    
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
    DWORD current_time = 0;
    rtems_interval time_val;
    if (rtems_clock_get (RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &time_val) == RTEMS_SUCCESSFUL)
      {
        current_time = (DWORD)time_val * ms_per_tick;
      }
		else
			{
				printf ("Scheduler >> Unable to Get Time");
			}
    return current_time;
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
		if (scheduler_initialised)
			rtems_event_send (schedule_task, SCHEDULE_EVENT_EVENT_FLAG);
		else
			printf("Schedule:resume -- not initialised\r\n");
	
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
		bool ret = false;

		if (scheduler_initialised)
			{
				if (!period)
					{
						ret = rtems_semaphore_obtain (schedule_sem, RTEMS_NO_WAIT, period) == RTEMS_SUCCESSFUL;
					}
				else
					{
						ret = rtems_semaphore_obtain (schedule_sem, RTEMS_WAIT, period) == RTEMS_SUCCESSFUL;
					}

			}
		return ret;

    //## end hal_include::Scheduler::lock%982879202.body
  }

  //## Operation: unlock%982879203
  //	Unlocks the Scheduler and releases its critical
  //	sections. Returns true if unlocked.
  bool Scheduler::unlock ()
  {
    //## begin hal_include::Scheduler::unlock%982879203.body preserve=yes
		
		bool ret = false;

		if(scheduler_initialised)
			{
				ret = (rtems_semaphore_release (schedule_sem) == RTEMS_SUCCESSFUL);
			}
		return ret;

    //## end hal_include::Scheduler::unlock%982879203.body
  }

  //## Operation: LockEngine%1018482872
  //	A public lock to limit access to the engne to a single
  //	task
  bool Scheduler::LockEngine (unsigned wait_period)
  {
    //## begin hal_include::Scheduler::LockEngine%1018482872.body preserve=yes
		bool ret = false;

		if (scheduler_initialised)
			{
				if (!wait_period)
					{
						ret = rtems_semaphore_obtain (engine_sem, RTEMS_NO_WAIT, wait_period) == RTEMS_SUCCESSFUL;
					}
				else
					{
						ret = rtems_semaphore_obtain (engine_sem, RTEMS_WAIT, wait_period) == RTEMS_SUCCESSFUL;
					}

			}
		return ret;

    //## end hal_include::Scheduler::LockEngine%1018482872.body
  }

  //## Operation: UnlockEngine%1018482873
  //	Release Function For LockEngineFunction
  bool Scheduler::UnlockEngine ()
  {
    //## begin hal_include::Scheduler::UnlockEngine%1018482873.body preserve=yes
		
		bool ret = false;

		if(scheduler_initialised)
			{
				ret = (rtems_semaphore_release (engine_sem) == RTEMS_SUCCESSFUL);
			}
		return ret;

    //## end hal_include::Scheduler::UnlockEngine%1018482873.body
  }

  // Additional Declarations
    //## begin hal_include::Scheduler%3A80BBBF0082.declarations preserve=yes
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

//## begin module%3A92F41D00A8.epilog preserve=yes
void StartCommTasks();


rtems_task Scheduler_task ( rtems_task_argument unused)
{
	rtems_event_set dummy;
	rtems_interval wait_interval = 5;

#ifdef _DISPLAY_TICKS
	unsigned i = 0;
	unsigned num_ticks = 0;
	const unsigned display_val = 1000;
#endif

	rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &schedule_task);

	scheduler_initialised = true;

	StartCommTasks();

  printf("Schedule Task Started Waiting event\r\n");

  while (1)
    {
			rtems_event_receive (SCHEDULE_EVENT_EVENT_FLAG, RTEMS_WAIT, 
											 rtems_interval(wait_interval), &dummy);

#ifdef _DISPLAY_TICKS
			i++;
			num_ticks++;
			rtems_interval ticks_per_second;
      if (i == display_val)
				{
					printf ("\r\nSchedule Tick  %u", num_ticks);
					i = 0;
					DWORD current_time = 0;
					rtems_interval time_val;
					if (rtems_clock_get (RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &time_val)== RTEMS_SUCCESSFUL)
						{
							current_time = (DWORD)time_val;
						}
					
					printf ("\r\nTicks since boot %u", (unsigned)current_time);
          printf ("\r\nMS since boot %u", (unsigned)Scheduler::getTime());
					rtems_clock_get( RTEMS_CLOCK_GET_TICKS_PER_SECOND, &ticks_per_second );  
					printf ("\r\n Ticks per second :%d", (unsigned)ticks_per_second);
				} 
#endif
      wait_interval = hal_include::Scheduler::processCallback ();

			// we need to calculate how long to wait for the event now
    }
  
  //exit( 0 );
  
}


//## end module%3A92F41D00A8.epilog
