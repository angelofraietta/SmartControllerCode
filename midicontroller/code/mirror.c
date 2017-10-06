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

#include "../../mididriver/midiflags.h"

#device adc=8
#fuses HS, WDT, BROWNOUT, PUT, NOLVP, PROTECT

#define SPI_IN_LATCH      PIN_C2
#define SPI_CLOCK         PIN_C3
#define DIGITAL_IN_DATA   PIN_C4

#define SPI_DATA_OUT      PIN_D1
#define DIGITAL_OUT_LATCH PIN_D2

// define PLA Pins
#define PLA_CLK           PIN_D5
#define SPI_PLA_DATA      PIN_D4
#define SPI_PLA_DATA_DIR  PIN_D3


#define MIDI_CONTROLLER_BUILD

#ifdef _SIMULATE
#define _NO_DELAY
#else
#define _USE_PRINTF
#endif


#use delay(clock=20000000)

#define IO_INTERUPT_OUT_PIN1 PIN_E1
#define IO_INTERUPT_OUT_PIN2 PIN_E2
#define IO_INTERUPT_OUT_PIN3 PIN_E0

typedef struct
{
  byte flags;
  byte data;
} str_PLA_Data;

#include "watchdog.h"
#include "pla_io.h"

#define WATCHDOG_OVERFLOW_COUNT   255
#define WATCHDOG_NORMAL_COUNT     65000L


// LED timers
int16 watchdog_flash_count = 0; // when becomes zero, changes state of LED
short watchdog_led = 0;
short overflow_val = 0;

short message_lost = true;




void ExchangeMessages()
{

    if (Pla_fast_read_data())
      {
      if (pla_in_data.flags == DIAG_DIAG_MESSAGE_FLAG)
        {
        switch (pla_in_data.data)
          {
          case DIAG_INVALID_RX_DATA:
            pla_out_data.flags = DIAG_DIAG_MESSAGE_FLAG;
            pla_out_data.data = DIAG_RE_TRANSMIT_LAST_MESSAGE;
            break;

          case DIAG_RESET:
            while (1); //watchdog out
            break;

          case DIAG_ETX:
            pla_out_data.data = 0x01;
            pla_out_data.flags = 0x01; // clear first two bits of flag
            break;

          case DIAG_RE_TRANSMIT_LAST_MESSAGE:
            pla_out_data.flags = prev_pla_out.flags;
            pla_out_data.data = prev_pla_out.data;

          }
              
        }
      else
        {
        pla_out_data.data = pla_in_data.data;  
        pla_out_data.flags = pla_in_data.flags & 0x3F; // clear first two bits of flag
        }

      }
    else
      {
      pla_out_data.flags = DIAG_DIAG_MESSAGE_FLAG;
      pla_out_data.data = (byte) DIAG_RE_TRANSMIT_LAST_MESSAGE;
      }


		//output_low(IO_INTERUPT_OUT_PIN1);

    //Pla_write_data (&pla_data);

		//output_high(IO_INTERUPT_OUT_PIN1);
    Pla_Send_data();
}

void BlinkWatchdog()
{

  if (MessageWaiting())
  {
    ExchangeMessages();
    message_received = false;    
    message_lost = false;
  }



  if (!watchdog_flash_count)
    {
    watchdog_led = ~watchdog_led;
    SetWatchdogLed (watchdog_led);
    
    if (message_lost)
      {

      Pla_fast_read_data ();
		  

      pla_out_data.data = 0x00;
      pla_out_data.flags = 0x00; // clear first two bits of flag

      Pla_Send_data();

      }

    message_lost = true;

    watchdog_flash_count = WATCHDOG_NORMAL_COUNT;
    }

  watchdog_flash_count--;

}


void ResetController ()
{
  disable_interrupts(GLOBAL);
  output_low(IO_INTERUPT_OUT_PIN1); // PREPARE INTERRUPT
#ifndef _SIMULATE
  InitialiseWatchdog();
#endif

#use fast_io(b)
  set_tris_b (0xff);
  InitialisePlaIn();

  ext_int_edge(L_TO_H);      // init interrupt triggering for button press
  enable_interrupts(INT_EXT);// turn on interrupts
  
  enable_interrupts(GLOBAL);

}

main() {
	ResetController ();
  pla_out_data.data    = 0x00;
  pla_out_data.flags = 0x00;

   do {
			restart_wdt();
      BlinkWatchdog();
   } while (TRUE);

}



