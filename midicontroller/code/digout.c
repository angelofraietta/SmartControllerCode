#include "16f877.h"

#include "../../mididriver/midiflags.h"

#define IOCARD_BUILD

#device adc=8
#fuses HS, WDT, BROWNOUT, PUT, NOLVP , PROTECT

#define _SIMULATE


// define pins for SPI input reads and output writes
#define SPI_IN_LATCH      PIN_C2
#define SPI_CLOCK         PIN_C3

#define SPI_DATA_OUT      PIN_D1
#define DIGITAL_OUT_LATCH PIN_D2
#define DIGITAL_IN_DATA   PIN_C4
#define LCD_CLK           SPI_CLOCK         
#define LCD_DATA          SPI_DATA_OUT
#define LCD_ENABLE        PIN_D0
  
// define PLA Pins
#define PLA_CLK                 PIN_D5
#define SPI_PLA_DATA_OUT        PIN_D4
#define SPI_PLA_DATA_IN         PIN_D6

//#define SPI_PLA_DATA          PIN_D4
#define SPI_PLA_DATA_DIR        PIN_D3

#define CYCLE_COUNT 2

// set the following define to Do a count test
//#define DIAG_COUNT


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

#define WATCHDOG_OVERFLOW_COUNT     255
#define WATCHDOG_NORMAL_COUNT       5000L
#define WATCHDOG_PATCH_LOADED_COUNT 1000L
#define WATCHDOG_EEPROM_COUNT       20
#define NUM_MAX_OVERFLOW_BLINK      10
#define MAX_RESENDS                 2

#define NUM_ANALOGUE_IN_BANKS 2
#define NUM_ANALOGUE_IN_SUB_BANKS 8
#define NUM_ANALOGUE_IN_CHANS (NUM_ANALOGUE_IN_BANKS * NUM_ANALOGUE_IN_SUB_BANKS)
#define AD_READ_DELAY 20 // num us to delay from setting channel to making read
#define AD_SWITCH_DELAY 1 // num us to wait between switching analog switch to reading
#define NUM_ANALOG_VALID_READS 2 // must be this many identical reads to be a valid input

//#define SEVEN_BIT_AD

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
#use fast_io(e)  

#define IO_INTERUPT_OUT_DATA PIN_E1
#define IO_INTERUPT_OUT_MIDI PIN_E2
//#define IO_INTERUPT_OUT_MIDI PIN_E1

typedef struct
{
  byte flags;
  byte data;
} str_PLA_Data;


short resync_required = true;
short patch_loaded = false;

int num_overflow_blinks = 0;
int16 quiet_cycles = 0; // the number of cycles where we have heard nothing

short enable_analogs = true;
short processing_analogs = true; // this defines whethere we are in the analog processing loop

#define MAX_QUIET_CYCLES  5000

void MessageRead()
{
  resync_required = false;
}

#include "cfgram.h"
#include "lcd.h"
#include "watchdog.h"

#include "pla_io.h"
#include "Pla_out.h"
#include "24lc256.h"
#include "extprom.h"
#include "max520.h"
#include "anaout.h"
#include "midiin.h"
#include "spi_read.h"
#include "digout.h"
#include "anain.h"
#include "digin.h"
#include "proc_pla.h"
// LED timers
int16 watchdog_flash_count = 0; // when becomes zero, changes state of LED
short watchdog_led = 0;
short overflow_val = 0;

const byte LCD_INIT_TEXT [] = "Wait ...";

void BlinkWatchdog()
{
  str_PLA_Data pla_data;
 
  if (RequestEEProm() && watchdog_flash_count > WATCHDOG_EEPROM_COUNT)
  {
    watchdog_flash_count = 0;
  }

  if (!watchdog_flash_count)
    {
    watchdog_led = ~watchdog_led;
    SetWatchdogLed (watchdog_led);


    if (InOverflow())
      {
      watchdog_flash_count = WATCHDOG_OVERFLOW_COUNT;
      num_overflow_blinks++;

      if (num_overflow_blinks > NUM_MAX_OVERFLOW_BLINK)
        {
        num_overflow_blinks = 0;
        //ClearInQueueOverflow();
        }
      

      }
    else
      {

      if (!enable_analogs)
        {
        watchdog_flash_count = WATCHDOG_EEPROM_COUNT;
        }
      else
        {
        if (patch_loaded)
          {
          watchdog_flash_count = WATCHDOG_PATCH_LOADED_COUNT;
          }
        else
          {
          watchdog_flash_count = WATCHDOG_NORMAL_COUNT;
          }
        }
      }
    }

  watchdog_flash_count--;

}


void ResetController ()
{
  int i;

  disable_interrupts(GLOBAL);
	//DigoutInitialise();

  lcd_init();

  for (i = 0; i < sizeof(LCD_INIT_TEXT) - 1; i++)
  {
	  lcd_putc(LCD_INIT_TEXT[i]);
    delay_ms (2);
  }

  set_tris_e (0x00);

  output_low(IO_INTERUPT_OUT_DATA); // PREPARE THE iNTERRUPT PIN
  output_low(IO_INTERUPT_OUT_MIDI); // PREPARE THE iNTERRUPT PIN

#ifndef _SIMULATE
  InitialiseWatchdog();
#endif

  InitialisePlaOutQueue();

#ifndef _SIMULATE
	InitialiseAnalogueIn();
#endif

  last_tx_data.flags = DIAG_DIAG_MESSAGE_FLAG;
  last_tx_data.data = DIAG_ETX;

  prev_pla_out.flags = DIAG_DIAG_MESSAGE_FLAG;
  prev_pla_out.data = DIAG_REQUEST_RX_BYTES;

  InitialiseInQueue();
	ProcessDigitalInputs(false);			


  ext_int_edge(L_TO_H);      // init interrupt triggering for positive transition
  enable_interrupts(INT_EXT);// turn on interrupt
  
  InitialisePlaIn();

  InitialiseEEprom();
  enable_interrupts(GLOBAL);

  RequestNumRxBytes();


}


main() {
  int i;

  while (1)
    for (i = 0; i < 16; i++)
    {
      GenerateDigitalOutput (i, 127);
      GenerateDigitalOutput (i, 0);
    }

}



