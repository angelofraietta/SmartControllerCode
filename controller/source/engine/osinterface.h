
#ifndef OS_INTERFACE_H
#define OS_INTERFACE_H

#ifndef _HAL_WINDOWS
typedef void (*LPTIMECALLBACK) (UINT16, UINT16, DWORD, DWORD, DWORD);
#define TIME_ONESHOT 1

#endif



SC_STATUS_CODE SendMessageToQueue (SC_QID queue_id, void* buffer, UINT32 buf_size);

UINT32 OS_timeGetTime ();

SC_STATUS_CODE OS_timeKillEvent (UINT16 event);

SC_STATUS_CODE OS_timeSetEvent(
			    DWORD uDelay,
			    DWORD uResolution,
			    LPTIMECALLBACK lpTimeProc,
			    DWORD dwUser,
			    UINT16 fuEvent
			    );



#endif






