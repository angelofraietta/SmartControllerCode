/******************************************************
* Author: A. Fraietta
* Description: Tests the Midi Input queue functions
* define TEST_QUEUEwhen testing queues on simulator
******************************************************/

#include "16f877.h"
#fuses HS, WDT, BROWNOUT, NOPUT, NOLVP

#define _SIMULATE
#define TEST_QUEUE
#define NUM_CONFIGS 16


// define pins for SPI input reads and output writes

#define SPI_IN_LATCH      PIN_C2
#define SPI_CLOCK         PIN_C3
#define SPI_DATA_OUT      PIN_D1
#define DIGITAL_OUT_LATCH PIN_D2
 

#define DIGITAL_IN_DATA PIN_C4


#ifdef _SIMULATE
#define _NO_DELAY
#else
#define _USE_PRINTF
#endif

#define NUM_ANALOGUE_OUT 8
#define NUM_DIGITAL_OUT 16
#use delay(clock=10000000)
//#use delay(clock=20000000)
//#use delay(clock=19660800)
#define MIDIOUT_1_PIN PIN_C6
#define MIDIOUT_2_PIN PIN_C5
#define MIDI_IN_PIN PIN_C7

#use rs232(baud=31250, xmit=MIDIOUT_1_PIN, rcv=MIDI_IN_PIN, ERRORS) 

#USE I2C(master, sda=PIN_B7, scl=PIN_B6)

#include "mididrv.h"
#include "cfgram.h"
#include "midicfg.h"
#include "max520.h"
//#include "ds1803.h"
#include "anaout.h"
#include "midiin.h"
#include "midiout.h"
#include "spi_read.h"
#include "watchdog.h"
#include "decmidi.h"
#include "procmidi.h"
#include "digout.h"
#include "sysex.h"


byte midi_in_char = 0;
int logic_error = false;
int success;

//                            SOSX, SYSID MIDI DEVID  CMD   stindex endindex
byte Read_cfg_sysex_msg [] = {0xf0, 0x7D, 0x00, 0x7f, 0x00, 0x00, 0x01, 0x7f,  0xf7};  
byte Write_cfg_sysex_msg [] = {0x7D, 0x00, 0xff, 0x01, 0x03, 0x01, 0x02, 0x03};

#ifdef TEST_QUEUE
main()
{
  int i, j;
  int queue_start; // this is the number that the queue head starts at when pushing into queue
  int midi_bytes;
	str_midiconfig test_msg;
  byte* msg_ptr;
  byte next_char;
  byte control_char;
  

	msg_ptr = (byte*) (&test_msg);

  InitialiseInQueue();
	InitialiseMidiStatus();
  enable_interrupts (GLOBAL);
/*
  AddInQueue (0xf0);

  for (i = 0; i < sizeof (Write_cfg_sysex_msg); i++)
    {
    next_char = Write_cfg_sysex_msg[i];
    
    control_char = EncodeMidiByte(&next_char);

    if (control_char)
      {
      AddInQueue (control_char);
      }
    AddInQueue (next_char);
    }
  AddInQueue (0xf7);

  ProcessMidiInputStream ();
	*/
  for (i = 0; i < NUM_CONFIGS; i++)
		{
			GetDefaultDigitalOut (&test_msg, i);
      test_msg.data_2 = 0x70;	
			midi_bytes = NumTxBytes (&test_msg);

			
			
			for (j = 0; j < midi_bytes; j++)
				{
					AddInQueue (msg_ptr[j]);
				}
			ProcessMidiInputStream ();
		}
}
    
#else // testing on hardware

main ()
{
  byte midi_char;

  InitialiseWatchdog ();
  InitialiseMidiInQueue();
  enable_interrupts(GLOBAL);
  while (1)
    {
    while (!MidiQueueEmpty())
      {
      // flash led for each non zero char
      midi_char = GetMidiInChar();
      if (midi_char)
        {
        FlashWatchdog (100);
        if (midi_char == 0xb1) // midi controller on channel 2
          {
          InitialiseMidiInQueue();
          }
        }
      restart_wdt();
      }  // end while queue not empty    
    
    if (MidiInOverflow ())
      {
      FlashWatchdog (200);
      
      }
    restart_wdt();
    } // end while 1
} // end main
  

#endif
