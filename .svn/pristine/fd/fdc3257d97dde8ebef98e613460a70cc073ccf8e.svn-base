
#include <rtems.h>
#include <tty_drv.h>
#include <console.h>
#include <clockdrv.h>
#include <timerdrv.h>
#include <stdio.h>
#include "midibsp.h"

rtems_task Init(rtems_task_argument ignored);

rtems_driver_address_table Device_drivers[] = {
        CONSOLE_DRIVER_TABLE_ENTRY,
        MIDIPORT_1_DRIVER_TABLE_ENTRY,
        CLOCK_DRIVER_TABLE_ENTRY,
        {NULL,NULL,NULL,NULL,NULL,NULL},
};

#define CONFIGURE_HAS_OWN_DEVICE_DRIVER_TABLE
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_MAXIMUM_TASKS             4

#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 20

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_USE_IMFS_AS_BASE_FILESYSTEM
#define CONFIGURE_INIT
#define CONFIGURE_EXTRA_TASK_STACKS (CONFIGURE_MAXIMUM_TASKS*4*RTEMS_MINIMUM_STACK_SIZE)
		 
#include <confdefs.h>

#include <fcntl.h>
#include <unistd.h>

rtems_id   Task_id;
rtems_name Task_name;

const char* tty_ports [] =
{
	"/dev/ttyS1",
	"/dev/ttyS2"
};
void mainline();

rtems_task Test_task(
  rtems_task_argument unused
)
{

}

rtems_task Init(rtems_task_argument ignored)

{
	mainline();
	/*
	rtems_status_code status;	
	Task_name = rtems_build_name( 'T', 'A', '1', ' ' );
  
  status = rtems_task_create(
    Task_name, 1, RTEMS_MINIMUM_STACK_SIZE * 2, RTEMS_DEFAULT_MODES,
    RTEMS_DEFAULT_ATTRIBUTES, &Task_id );
  status = rtems_task_start( Task_id, Test_task, 1 );
	*/
}






