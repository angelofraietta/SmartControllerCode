#include "16f877.h"
#fuses HS, WDT, BROWNOUT, NOPUT, NOLVP

#use delay(clock=10000000)


#include "watchdog.h"


#USE I2C(master, sda=PIN_B7, scl=PIN_B6)

//#define CONTROL_BYTE 0x50
//#define COMMAND_BYTE 0xAF // both pots
//#include "ds1803.h"
#include "max520.h"

byte i = 0;

main ()
{
  int j;
	initialiseWatchdog();
	while (1)
		{
      for (j = 0; j < 4; j++)
        {
        WriteAnalogueOutput (j, i);
        }
      i++;
    
			restart_wdt();
			FlashWatchdog (1);
		}

}
