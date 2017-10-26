#ifndef WINDOWS_TIMER_H
#define WINDOWS_TIMER_H

#include "funcdec.h"
#include "typedefs.h"
#include "memorycache.h"

#include "elist.h"
#ifndef _ROSE_ANALYSE

#include <stdlib.h>
#endif

//---------------------------------------------------------------------------

#ifndef _NO_NAMESPACES
using sm_str::list;

// declare namespace
namespace hal_include {class ScheduledObject;}
using hal_include::ScheduledObject;
#else
class ScheduledObject;
#endif

class TimerObject;



class TimerQueueItem
{
  // this Item is Stored by the scheduler, and as such, contains all the relevant information
 public:
  TimerQueueItem():CallbackTime(0),pTimer(0), pParam (NULL){}
  TimerQueueItem(DWORD i, TimerObject* l, void* Param = NULL): CallbackTime(i), pTimer(l),  pParam (Param){}
  bool operator==(const TimerQueueItem& right)const {return CallbackTime == right.CallbackTime && pTimer == right.pTimer && pParam == right.pParam;}
  DWORD CallbackTime; //when the device must be called
  TimerObject* pTimer;              //Pointer to the device
	void*        pParam;              //Parameter That Must be passed back by Scheduler
};



class TimerQueueItemPriority{
 public:
  bool operator()(const TimerQueueItem& x, const TimerQueueItem& y)const
            //Greater time has less priority
    {return x.CallbackTime > y.CallbackTime;}
};
 
class TimerItemEqual{
 public:
  bool operator()(const TimerQueueItem& x, const TimerQueueItem& y)const
		{return x.CallbackTime == y.CallbackTime;}
};

class TimerObject{
 public:
  
  virtual void ReceiveClockTiming(void* pParam) = 0;

  virtual void Purge(){};
  DWORD GetTime()const;
};

class FreeRunning :protected TimerObject
{
 public:
  FreeRunning(unsigned Interval = 1000);
  
  virtual ~FreeRunning(){Stop();}
  
  void Start();
  
  void Stop();
  
  void SetClockInterval(unsigned );
  
  virtual void OutputFunction(){};
  
  bool IsRunning()const;
  
  void ReceiveClockTiming(void* pParam);
  
 protected:
  unsigned wInterval; // the clocking speed
  ScheduledObject* pSchedule;
  DWORD CallbackTime;
  
  void Purge();
  volatile bool running;
  
};

//************************************************************
class DelayLine :protected TimerObject
{
	
 public:
    class DelayLineQueueItem
      {
      public:
        static void* operator new(size_t);
				static void operator delete(void*);

        DelayLineQueueItem(unsigned long p = 0):lParam(p), pSchedule(NULL)
        {
        //printf ("DelayLineQueueItem %lu\r\n", p);
        }
        void SetSchedule (ScheduledObject* Schedule){pSchedule = Schedule;}

	unsigned long lParam;         //Parameter to be returned after event has arived
        ScheduledObject* pSchedule; // handle that must be returned if we want to kill the event
				static MemoryCache _mem_manager;
      };
    
    
    DelayLine(unsigned Interval = 1000){}
		
    virtual ~DelayLine();
    void SetInterval(unsigned);
    unsigned GetInterval()const {return wInterval;}
    
    bool GoOneShot(unsigned long);
    
    virtual void OutputFunction(unsigned long){};
    
    void ReceiveClockTiming(void* pParam);
    
 protected:
    unsigned wInterval;
    
    list<DelayLineQueueItem*> qParam; //List of items in queue awaiting callback
    
    
    void Purge();
    virtual void PurgeItem(unsigned long) {}; //its derived class will receive one for each param
};


class OneShot :protected TimerObject
{
 public:
  OneShot(unsigned Interval = 1000);
  
  virtual ~OneShot(){Stop();}
  
  void Start();
  
  void Stop();
  
  void SetClockInterval(unsigned );
  
  virtual void OutputFunction(){};
  
  bool IsRunning()const;
  
  void ReceiveClockTiming(void* pParam);
  
 protected:
  unsigned wInterval; // the clocking speed
  ScheduledObject* pSchedule;
  DWORD CallbackTime;

  void GoOneShot();
  void Purge();

};

class TickCallback :protected OneShot
{
 public:
  TickCallback();
  
  void SetDivision(unsigned NewDivision);
  void SetTickTempo(float NewTempo);
  void SetTickTempo(DWORD NewTempo);
  void OutputFunction();
  virtual void OutputTick(){};
  void StartTiming();
  void GoTickOneshot(DWORD dwNumTicks);
 protected:
  unsigned wResolution;              //ticks per beat
  float flTempo;                   //in bpmin
  float flTickDuration;            //in milliseconds
  DWORD dwMillisecondsPerTick;     //division  millisecond part
  DWORD dwMicrosecondsPerTick;     //microsecond part
  DWORD dwmsCallbackTime;       //when to callback in milliseconds
  DWORD dwTickCallbackTime;         //when to callback in ticks
  DWORD dwCurrentTickCount;         //currentCount
  DWORD dwStartTime;            //in milliseconds
 private:
  void SetTicksPerMillisecond();
  DWORD ConvertTicks(DWORD NumTicks); //convert to milliseconds
};
//---------------------------------------------------------------
//inline functions
//---------------------------------------------------------------
inline bool FreeRunning::IsRunning()const
{return  (pSchedule);}

inline bool OneShot::IsRunning()const
{return (pSchedule);}

#endif

