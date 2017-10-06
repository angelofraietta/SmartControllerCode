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

#define MIDIOUT_1_PIN PIN_C6
#define MIDIOUT_2_PIN PIN_C5
#define MIDI_IN_PIN PIN_C7


#USE FAST_IO(B)
#use delay(clock=20000000)

void WriteOutData (byte out_byte)
{
#use rs232(baud=31250, xmit=MIDIOUT_1_PIN, rcv=MIDI_IN_PIN, ERRORS) 
#ifndef _SIMULATE
	putc (out_byte);
#endif

}


short ReadAnaloguePulse()
{
  int sub_bank;
  short ret = false;

	for (sub_bank = 0; sub_bank < 8; sub_bank++)
		{
			restart_wdt();
      output_bit(PIN_B1, bit_test(sub_bank, 0));
      output_bit(PIN_B2, bit_test(sub_bank, 1));
      output_bit(PIN_B3, bit_test(sub_bank, 2));
    }
  return true;
}

main() {
   int value = 0;
   do {
      WriteOutData (0xB0); // Write Controller Channel 0
      WriteOutData (0x0);  // Write Controller number    
      WriteOutData (value & 0x70); // write controller value clear MSB
      value++;
      delay_ms (1000);
   } while (TRUE);

}



