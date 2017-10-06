#include "16f877.h"
#device adc=8
#fuses HS, WDT, BROWNOUT, NOPUT, NOLVP
#define WATCHDOG_PIN	PIN_C0

//#define _SIMULATE


// define pins ofr Digital input reads
#define DIGITAL_IN_LATCH PIN_C2
#define DIGITAL_IN_CLOCK PIN_C3

#define DIGITAL_IN_DATA PIN_C4


#ifdef _SIMULATE
#define _NO_DELAY
#else
#define _USE_PRINTF
#endif



#include "midiout.h"
#include "watchdog.h"

int controller = 0;
int val = 10;
int channel = 0;

main ()
{
  InitialiseWatchdog();

  while (1)
    {

    OutputController(channel, controller, val);
    controller++;
		if (controller == 127)
			{
				controller = 0;
			}


    val++;

		if (val == 127)
			{
				val = 0;
			}

    channel++;

    if (channel == 16)
      {
      channel = 0;
      }

    restart_wdt();
#ifndef _SIMULATE
    delay_ms (100);

#endif
  }
}

