#include "16f877.h"


#fuses HS, WDT, BROWNOUT, NOPUT, NOLVP

#use delay(clock=10000000)

#include "cfgram.h"
#include "midicfg.h"
#include "watchdog.h"

main()
{
  int eprom_val;
  byte i;
  str_midiconfig config;

  initialiseWatchdog();
  enable_interrupts (GLOBAL);
  
  //ResetConfiguration();
  while (1)
    {
    restart_wdt();

    if (!eeprom_busy)
      {
      FlashWatchdog (250);
      }

     WriteConfigByte (i, i++);
     i = ReadConfigByte(i);
     i++; 
    }
}
    

