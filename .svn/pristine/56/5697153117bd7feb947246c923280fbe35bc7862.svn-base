/*
 *  Simple test program -- simplified version of sample test hello.
 */


#define CONFIGURE_INIT
#include "system.h"
#include <stdio.h>
#include <rtems/monitor.h>
#include <rtems/rtems_bsdnet.h>

#include "scheduler.h"
#include "bsp-cs8900.h"

using hal_include::Scheduler;

extern "C" void DiagTask(void);

extern "C" void InitialiseNet();
extern "C" void MountIDE();

#define USE_BOOTP          0
#define UDP_ECHO_HOST      "192.168.0.1"

rtems_task Console_task(
  rtems_task_argument unused
)
{
  DiagTask();
}


/*
 *  Keep the names and IDs in global variables so another task can use them.
 */

rtems_id   Console_Task_id;         // id of console task
rtems_name Console_Task_name;       /* Console task name */

rtems_task Init(
  rtems_task_argument argument
)
{
  rtems_status_code status;

	MountIDE();

  rtems_monitor_init (0);

	Console_Task_name = rtems_build_name( 'D', 'I', 'A', 'G' );
  
  status = rtems_task_create(Console_Task_name, 10, RTEMS_MINIMUM_STACK_SIZE * 5, RTEMS_DEFAULT_MODES, RTEMS_DEFAULT_ATTRIBUTES, &Console_Task_id );

	if (status != RTEMS_SUCCESSFUL)
		{
			printf("unable to create task\r\n");
		}
	



	InitialiseNet();
	
  Scheduler::initialise();

  status = rtems_task_start( Console_Task_id, Console_task, 10 );

  status = rtems_task_delete( RTEMS_SELF );
}







