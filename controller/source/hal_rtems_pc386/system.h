/*  system.h
 *
 *  This include file contains information that is included in every
 *  function in the test set.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.OARcorp.com/rtems/license.html.
 *
 *  $Id: system.h,v 1.13 2003/04/29 00:51:11 angelo Exp $
 */

#include <rtems.h>
#include "midibsp.h"

/* functions */

rtems_task Init(
  rtems_task_argument argument
);

rtems_task Test_task(
  rtems_task_argument argument
);

/* global variables */

/*
 *  Keep the names and IDs in global variables so another task can use them.
 */ 



/* configuration information */

#include <bsp.h> /* for device driver prototypes */
#ifdef RTEMS_BSP_HAS_IDE_DRIVER
#include <libchip/ata.h> /* for ata driver prototype */
#include <libchip/ide_ctrl.h> /* for general ide driver prototype */
#endif
#include <tty_drv.h>
#include <console.h>
#include <clockdrv.h>
#include <timerdrv.h>

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_USE_IMFS_AS_BASE_FILESYSTEM
#define CONFIGURE_HAS_OWN_DEVICE_DRIVER_TABLE


rtems_driver_address_table Device_drivers[] = {
        CONSOLE_DRIVER_TABLE_ENTRY,
        TTY1_DRIVER_TABLE_ENTRY,
        TTY2_DRIVER_TABLE_ENTRY,
				MIDIPORT_1_DRIVER_TABLE_ENTRY,
        CLOCK_DRIVER_TABLE_ENTRY,
#ifdef RTEMS_BSP_HAS_IDE_DRIVER
				/* important: ATA driver must be after ide drivers */

				IDE_CONTROLLER_DRIVER_TABLE_ENTRY,
				ATA_DRIVER_TABLE_ENTRY ,
#endif
        {NULL,NULL,NULL,NULL,NULL,NULL},
};

#include <rtems/bdbuf.h>
rtems_bdbuf_config rtems_bdbuf_configuration[] = {
  {512,128,NULL}
};
int rtems_bdbuf_configuration_size =( sizeof(rtems_bdbuf_configuration)
				     /sizeof(rtems_bdbuf_configuration[0]));

#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 50

#define CONFIGURE_MICROSECONDS_PER_TICK 1000 /* 1 ms */
#define CONFIGURE_MAXIMUM_TASKS             30
#define CONFIGURE_INIT_TASK_STACK_SIZE      (1024 * 8)
#define CONFIGURE_MAXIMUM_SEMAPHORES 20
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES    20


#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_EXTRA_TASK_STACKS (CONFIGURE_MAXIMUM_TASKS*10*RTEMS_MINIMUM_STACK_SIZE)


#include <confdefs.h>


