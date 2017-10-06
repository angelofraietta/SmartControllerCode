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

short success = false;
int16 watchdog_flash_count = 0; // when becomes zero, changes state of LED
short watchdog_led = 0;


void BlinkWatchdog()
{

  if (!watchdog_flash_count)
    {
    watchdog_led = ~watchdog_led;
    SetWatchdogLed (watchdog_led);


    if (success)
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

#ifdef WRITE_EEPROM
main()
{
  int i = 0;
  int32 num_eeprom_bytes = 0;
	
  initialiseWatchdog();
  while (1)
    {
    restart_wdt();
    BlinkWatchdog ();

    if (!success && num_eeprom_bytes < 0x08000)
      {
      if (WriteEEProm (i))
        {
        num_eeprom_bytes++;
        i++; 
        }
      }
     else
      {
      success = true; // cause watchdog LED to blink quickly 
      ResetEEprom();
      }
    
    } // end while
}
#else
main()
{
  int i = 0;
  int32 num_eeprom_bytes = 0;
	int read_byte;
	short fail = false;

  initialiseWatchdog();
  while (1)
    {
    restart_wdt();
    BlinkWatchdog ();

    if (!fail && num_eeprom_bytes < 0x08000)
      {
      if (ReadEEProm (&read_byte))
        {
					if (read_byte != i)
						{
							fail = true;
						}
					
					num_eeprom_bytes++;
					i++; 
        }
			else
				{
					fail = true;
				}
      }
		else
      {
      success = !fail; // cause watchdog LED to blink quickly 
      ResetEEprom();
      }
    
    } // end while
}
#endif    




