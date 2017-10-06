/*******************************************************************************
*	Author: Angelo Fraietta
*	Description: General Purpose Midi controller
*	Processor PIC16F877
*	Specifications:
*		16 Digital input to Midi Output (SPI)
*		16 Analogue input to Midi Output (ADC)
*		Midi input to Midi output merge (UART)
*   Midi input to 16 Analogue ouput (I2C)
*
*******************************************************************************/

#include "16f877.h"
#device adc=8
#fuses HS, WDT, BROWNOUT, PUT, NOLVP, PROTECT

//#define _SIMULATE


// define pins for SPI input reads and output writes
#define SPI_IN_LATCH      PIN_C2
#define SPI_CLOCK         PIN_C3
#define SPI_DATA_OUT      PIN_D1
#define DIGITAL_OUT_LATCH PIN_D2
 

#define DIGITAL_IN_DATA PIN_C4
#define MIDI_CONTROLLER_BUILD

#ifdef _SIMULATE
#define _NO_DELAY
#else
#define _USE_PRINTF
#endif

#define NUM_ANALOGUE_OUT 8
#define NUM_DIGITAL_OUT 16


#use delay(clock=20000000)

#define MIDIOUT_1_PIN PIN_C6
#define MIDIOUT_2_PIN PIN_C5
#define MIDI_IN_PIN PIN_C7

#define WATCHDOG_OVERFLOW_COUNT   255
#define WATCHDOG_NORMAL_COUNT     5000L

#define NUM_ANALOGUE_IN_BANKS 2
#define NUM_ANALOGUE_IN_SUB_BANKS 8
#define NUM_ANALOGUE_IN_CHANS (NUM_ANALOGUE_IN_BANKS * NUM_ANALOGUE_IN_SUB_BANKS)
#define AD_READ_DELAY 20 // num us to delay from setting channel to making read
#define AD_SWITCH_DELAY 1 // num us to wait between switching analog switch to reading
#define NUM_ANALOG_VALID_READS 2 // must be this many identical reads to be a valid input

#define SEVEN_BIT_AD

#ifdef SEVEN_BIT_AD
#define DIG_ON_VAL 0x7f
#else
#define DIG_ON_VAL 0xff
#endif

#byte PORTA = 5
#byte PORTB = 6
#byte PORTC = 7


#use rs232(baud=31250, xmit=MIDIOUT_1_PIN, rcv=MIDI_IN_PIN, ERRORS) 

#USE I2C(master, sda=PIN_B7, scl=PIN_B6)
#include "sysexcommands.h"
#include "midiDrv.h"
#include "cfgram.h"
#include "midicfg.h"
#include "max520.h"
#include "anaout.h"
#include "midiin.h"
#include "sysexout.h"
#include "midiout.h"
#include "spi_read.h"
#include "watchdog.h"
#include "decmidi.h"
#include "procmidi.h"
#include "digout.h"
#include "sysex.h"
#include "anain.h"
#include "digin.h"





// LED timers
int16 watchdog_flash_count = 0; // when becomes zero, changes state of LED
short watchdog_led = 0;
short overflow_val = 0;


void BlinkWatchdog()
{
  if (overflow_val != InOverflow())
    {
    overflow_val = InOverflow();
    watchdog_flash_count = 0;
    }

  if (!watchdog_flash_count)
    {
    watchdog_led = ~watchdog_led;
    SetWatchdogLed (watchdog_led);
    
    if (InOverflow())
      {
      watchdog_flash_count = WATCHDOG_OVERFLOW_COUNT;
      }

    else
      {
      watchdog_flash_count = WATCHDOG_NORMAL_COUNT;
      }

		if (!ClearRxFlag()) // then we are locked inside a merge
			{
				InitialiseMidiStatus();

				InitialiseInQueue();
			}
    }
  else
    {
    watchdog_flash_count--;
    }
}

void GenerateResetConfigData()
{
	// configure analog in first
	str_midiconfig config;
	int i;
  byte outval;

	for (i = 0; i < MAX_INPUT_CHAN; i++)
		{
      restart_wdt();
			ReadAnalogueInConfig (&config, i);
      if (config.config_flag & PRESET_VALUE_FLAG)
      {
        OutputMidi (&config);
      }
		}


	for (i = 0; i < MAX_INPUT_CHAN; i++)
		{
      restart_wdt();
			ReadDigitalInConfig (&config, i);

      if (config.config_flag & PRESET_VALUE_FLAG)
      {
        OutputMidi (&config);
      }
		}

	for (i = 0; i < MAX_ANAOUTPUT_CHAN; i++)
		{
      restart_wdt();
			ReadAnalogueOutConfig (&config, i);

      if (config.config_flag & PRESET_VALUE_FLAG)
      {
          if (DATA_1_VARY_MASK & config.config_flag)
            {
					  outval = config.data_1;  
            }
          else
            {
					  outval = config.data_2;  
            }

          if (INVERT_VALUE_MASK & config.config_flag)
            {
            outval ^= 0x7f; // flip all but msb
            }

          GenerateAnalogueOutput (i, outval << 1); // multiply by 2

      }

		}

	for (i = 0; i < MAX_DIGOUTPUT_CHAN; i++)
		{
      restart_wdt();
			ReadDigitalOutConfig (&config, i);

      if (config.config_flag & PRESET_VALUE_FLAG)
      {

          if (DATA_1_VARY_MASK & config.config_flag)
            {
					  outval = config.data_1;  
            }
          else
            {
					  outval = config.data_2;  
            }
          
          if (INVERT_VALUE_MASK & config.config_flag)
            {
            outval ^= 0x7f; // flip all but msb
            }

            
					GenerateDigitalOutput (i, outval);
      }
		}
}







void ResetController ()
{
  disable_interrupts(GLOBAL);
#ifndef _SIMULATE
  ValidateStoredConfig();
  InitialiseWatchdog();
#endif

#ifdef _USE_OUT_BUFFER
	InitialiseOutQueue();
#endif

	InitialiseAnalogueIn();
	ProcessDigitalInputs(false);			
  InitialiseMidiStatus();

  GenerateResetConfigData();
  InitialiseInQueue();
  enable_interrupts(GLOBAL);

}

main() {
	ResetController ();
   do {
      ProcessAnalogueIn();
	    ProcessDigitalInputs(true);			
			restart_wdt();
      BlinkWatchdog();
      ProcessMidiInputStream(); 
   } while (TRUE);

}



