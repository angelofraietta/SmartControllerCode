#include "stdafx.h"
#include "control.h"
#include "timer.h"
#include "scheduler.h"                               

using hal_include::Scheduler;
using hal_include::ScheduledObject;

MemoryCache DelayLine::DelayLineQueueItem::_mem_manager;
 
DWORD TimerObject::GetTime()const
{
  return Scheduler::getTime();
}

FreeRunning::FreeRunning(unsigned Interval)
  : pSchedule(NULL),
		CallbackTime (0),
    running (false)
   
  
  
{SetClockInterval(Interval);}


void FreeRunning::Start()
{
  if (IsRunning()) return;
	DWORD current_time = Scheduler::getTime();
  CallbackTime = current_time + wInterval;
  
	TimerQueueItem NextEvent (current_time, this);
    
  //start clock
  pSchedule = Scheduler::SetTimeEvent(NextEvent);
  running = true;
 }

void FreeRunning::Stop()
{
  running = false;
  if(!IsRunning())
    return; // Not Going
  
  Scheduler::KillTimeEvent(pSchedule);
  pSchedule = NULL;
  
}

void FreeRunning::SetClockInterval(unsigned NewInterval)
{
  if(!NewInterval)
		{ 
			NewInterval = 1; //set a minumum
		}

  wInterval = NewInterval;

}

void FreeRunning::Purge()
{
  pSchedule = NULL;
}

void FreeRunning::ReceiveClockTiming(void* pParam)
{
  //make the next time from here
  if (running)
    {
    CallbackTime = Scheduler::getTime() + wInterval;

    TimerQueueItem NextEvent (CallbackTime, this);

    // we need to start the scheduler again before we
    //output in case the output causes a stop
    pSchedule = Scheduler::SetTimeEvent(NextEvent);

    OutputFunction();
    }
  UNREFERENCED_PARAMETER (pParam);

}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
//DelayLine dfn

DelayLine::~DelayLine()
{
  Purge();
}


void DelayLine::ReceiveClockTiming(void* pParam)
{
	typedef list <DelayLineQueueItem*>::e_node node;
	if (!pParam)
		{
			Identity::Error (eTimerError, NULL);
			return;
		}

	node* pListItem = (node*)pParam;

  DelayLineQueueItem* pItem = pListItem->data();
  
  if (pItem)
    {
      DWORD Param = pItem->lParam;
      
      OutputFunction(Param);

      delete pItem;
			pListItem->data () = NULL;
    }
	else
		{
			Identity::Error (eTimerError, NULL);
		}

  qParam.erase(pListItem);
    
}


bool DelayLine::GoOneShot(unsigned long Param)
{

  
  bool ret = false;
  //get the time
  DWORD CallbackTime = Scheduler::getTime() + wInterval;


  DelayLineQueueItem*  pItem = new DelayLineQueueItem(Param);
  if (!pItem)
    {
      Identity::Error (eTimerError, NULL);
    }

  else
    {
			// we need to prevent any task entering the engine at this point
      // done in task now

      //if (Scheduler::LockEngine ())
      //{
        list<DelayLineQueueItem*>::e_node* pListItem = qParam.insert(pItem);

        //prepare the event
        TimerQueueItem NextEvent(CallbackTime, this, pListItem);

        //send to timer
        ScheduledObject* pSchedule = Scheduler::SetTimeEvent(NextEvent);

        pItem->SetSchedule (pSchedule);
        ret = true;

        //Scheduler::UnlockEngine ();
      //}

    }

  return ret;
}

void DelayLine::Purge()
{
  typedef sm_str::list<DelayLineQueueItem* >::iterator ListIterator;
  ListIterator iter;
  
  // kill all time events from scheduler first in case the scheduler is
  // running at full speed 
  for(iter = qParam.begin(); iter != qParam.end();++iter)
    {
      DelayLineQueueItem* pDelayLineItem = *iter;
      Scheduler::KillTimeEvent(pDelayLineItem->pSchedule);
			PurgeItem(pDelayLineItem->lParam);
      delete pDelayLineItem;
			*iter = NULL;
    }
  
  qParam.erase(qParam.begin(), qParam.end());
  
}

void* DelayLine::DelayLineQueueItem::operator new (size_t size)
{
	return _mem_manager.allocate(size);
}

void DelayLine::DelayLineQueueItem::operator delete (void* mem)
{
	_mem_manager.free (mem);
}

//------------------------------------------------------------------

OneShot::OneShot(unsigned Interval)
  :   pSchedule (NULL),
      CallbackTime (0)

{SetClockInterval(Interval);}


void OneShot::Start()
{
  if (IsRunning()) return;
  
  CallbackTime = Scheduler::getTime() + wInterval;
  
  TimerQueueItem NextEvent (CallbackTime, this);//make the event
  
  //start clock
  
  pSchedule = Scheduler::SetTimeEvent(NextEvent);
  
  OutputFunction();
}

void OneShot::Stop()
{
  if(!IsRunning())
    return; // Not Going
  
  Scheduler::KillTimeEvent(pSchedule);
  pSchedule = NULL;
  
}

void OneShot::SetClockInterval(unsigned NewInterval)
{
  if(!NewInterval)
    NewInterval = 1; //set a minumum
  wInterval = NewInterval;
  /*	if (fIsRunning) // clock must be running
	{
	Stop();
	Start(); //restart with new Interval
	}*/
}

void OneShot::Purge()
{
  pSchedule = NULL;
}

void OneShot::ReceiveClockTiming(void* pParam)
{
	UNREFERENCED_PARAMETER (pParam);
  OutputFunction();
  
  
  //for when going to stop
}

void OneShot::GoOneShot()
{
  //get the time
  CallbackTime = Scheduler::getTime() + wInterval;
  
  
  //prepare the event
  TimerQueueItem NextEvent (CallbackTime, this);//make the event
  
  pSchedule = Scheduler::SetTimeEvent(NextEvent);
  
}

TickCallback::TickCallback():
  wResolution(480),   
  flTempo(120),
  dwMicrosecondsPerTick(0), 
  dwmsCallbackTime(0),  
  dwTickCallbackTime(0),
  dwCurrentTickCount(0),
  dwStartTime(0)
{
  SetTicksPerMillisecond();
  wInterval = 1;
}

void TickCallback::SetTicksPerMillisecond()
{
  flTickDuration = 60000 / flTempo /wResolution;
}

void TickCallback::StartTiming()
{
  dwStartTime = GetTime();
  dwCurrentTickCount = 0;
}

void TickCallback::SetTickTempo(DWORD dwNewTempo)
{
  if(!dwNewTempo)
    return;
  flTempo = 60000000 / dwNewTempo;
  SetTicksPerMillisecond();
  StartTiming();
}

void TickCallback::SetTickTempo(float NewTempo)
{
  if(!NewTempo)
    return;
  flTempo = NewTempo;
  SetTicksPerMillisecond();
  StartTiming();
}

void TickCallback::OutputFunction()
{
  DWORD dwCurrentTime = GetTime();
  //check for right time
  if(dwCurrentTime < dwmsCallbackTime)//not time yet
    {
      GoOneShot();
      return;
    }
  
  OutputTick();
}

void TickCallback::GoTickOneshot(DWORD dwNumTicks)
{
  dwCurrentTickCount += dwNumTicks;
  
  //calculate the required time from start
  float ElapsedTime = dwCurrentTickCount * flTickDuration;
  
  dwmsCallbackTime = dwStartTime + (unsigned)ElapsedTime;
  
  OutputFunction();
}



