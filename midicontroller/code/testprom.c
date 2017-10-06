#include "16f877.h"


#fuses HS, WDT, BROWNOUT, NOPUT, NOLVP

#use delay(clock=20000000)
#USE I2C(master, sda=PIN_B7, scl=PIN_B6)

//#define _SIMULATE

#define WATCHDOG_OVERFLOW_COUNT   255
#define WATCHDOG_NORMAL_COUNT     5000L

#include "watchdog.h"
#include "24lc256.h"
#include "cfgram.h"

short finished = false;
int16 watchdog_flash_count = 0; // when becomes zero, changes state of LED
short watchdog_led = 0;

struct TSettings{
   char *date_fmt[2];
   char *dist_fmt[2];
   char *alm_set[2];
};



void BlinkWatchdog()
{

  if (!watchdog_flash_count)
    {
    watchdog_led = ~watchdog_led;
    SetWatchdogLed (watchdog_led);


    if (finished)
      {
      watchdog_flash_count = WATCHDOG_OVERFLOW_COUNT;
      }
    else
      {
      watchdog_flash_count = WATCHDOG_NORMAL_COUNT;
      }
    }

  watchdog_flash_count--;

}

main()
{
  int i, add_number;
  int32 num_eeprom_bytes = 0;
  short eeprom_written = false;
  i=0;
  add_number = 1;
  
  ResetEEprom();

  initialiseWatchdog();
  enable_interrupts (GLOBAL);
  
  while (1)
    {
    restart_wdt();
    BlinkWatchdog ();

    if (!finished && num_eeprom_bytes < 0x00008080)
      {
      if (WriteEEProm (i ^ 0xff))
        {
        num_eeprom_bytes++;
        i += add_number; 
        }
      }
     else
      {
      finished = true;
      ResetEEprom();
    
      }
    
    } // end while
}
    

