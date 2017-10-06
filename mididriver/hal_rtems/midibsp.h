#ifndef MIDI_BSP_H
#define MIDI_BSP_H

#ifdef __cplusplus
extern "C" {
#endif

extern	rtems_device_driver
	midiport0_initialize(rtems_device_major_number major,
											 rtems_device_minor_number minor,
											 void                      *arg);

extern rtems_device_driver
midiport0_open(rtems_device_major_number major,
                rtems_device_minor_number minor,
							 void                      *arg);
	
#define MIDIPORT_1_DRIVER_TABLE_ENTRY  { midiport0_initialize, NULL, NULL, NULL, NULL, NULL}

#ifdef __cplusplus
}	//extern "C" {
#endif



#endif
