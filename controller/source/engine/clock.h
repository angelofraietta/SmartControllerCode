#ifndef CLOCK_H
#define CLOCK_H

void CALLBACK ReceiveClockTiming(unsigned wTimerID, unsigned msg,
				 DWORD dwUser, DWORD dw1, DWORD dw2);

class FreeRunning
{
 public:
  FreeRunning(unsigned Interval = 1000, unsigned Resolution = 1):
    wTimerID(0){SetResolution(Resolution);
    SetClockInterval(Interval);}
  
  virtual ~FreeRunning(){Stop();}
  
  void Start();
  
  void Stop();
  
  void SetClockInterval(unsigned );
  
  void SetResolution(unsigned);
  
  virtual void OutputFunction() = 0;
  
 private:
  unsigned iResolution;
  unsigned iInterval; // the clocking speed
  unsigned wTimerID; // the ID of the current timer
};

//************************************************************

inline void FreeRunning::Start()
{
  if (wTimerID) return;
  
  //set resolution
  timeBeginPeriod(iResolution);
  
  //start clock
  wTimerID = timeSetEvent(iInterval, iResolution,
			  ReceiveClockTiming, (DWORD)this,
			  TIME_PERIODIC);
  OutputFunction();
}

inline void FreeRunning::Stop()
{
  if(!wTimerID)
    return; // Not Going
  
  timeKillEvent(wTimerID);
  wTimerID = 0;
  timeEndPeriod(iResolution);
}

inline void FreeRunning::SetClockInterval(unsigned NewInterval)
{
  if(!NewInterval)
    NewInterval = 1; //set a minumum
  iInterval = NewInterval;
  if (wTimerID) // clock must be running
    {
      Stop();
      Start(); //restart with new Interval
    }
}

inline void FreeRunning::SetResolution(unsigned NewResolution)
{
  TIMECAPS tc;
  UINT     wTimerRes;
  
  if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR)
    {
      // Error; application can't continue.
    }
  
  wTimerRes = min(max(tc.wPeriodMin, NewResolution), tc.wPeriodMax);
  
  if (wTimerID) // clock must be running
    {
      Stop();
      iResolution = wTimerRes;
      Start(); //restart with new Interval
    }
  else // No FreeRunning Running
    iResolution = wTimerRes;
}


inline void CALLBACK ReceiveClockTiming(UINT wTimerID, UINT msg,
					DWORD dwUser, DWORD dw1, DWORD dw2)
{
  FreeRunning* handle;
  handle = (FreeRunning*)dwUser;
  
  handle->OutputFunction();     // handle tasks
}


#endif

