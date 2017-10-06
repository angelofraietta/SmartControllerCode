#include "stdafx.h"

#include "ostypes.h"
#include "osinterface.h"

SC_STATUS_CODE SendMessageToQueue (SC_QID queue_id, void* buffer, UINT32 buf_size)
{
  UNREFERENCED_PARAMETER (queue_id);
  UNREFERENCED_PARAMETER (buffer);
  UNREFERENCED_PARAMETER (buf_size);
  return 0;
}


UINT32 OS_timeGetTime ()
{
  return 0;
}

SC_STATUS_CODE OS_timeKillEvent (UINT16 event)
{
  return 0;
}

SC_STATUS_CODE OS_timeSetEvent(
			    UINT16 uDelay,
			    UINT16 uResolution,
			    LPTIMECALLBACK lpTimeProc,
			    DWORD dwUser,
			    UINT16 fuEvent
			    )
{
  return 0;
}









