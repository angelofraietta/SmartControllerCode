
#include "16f877.h"
#device adc=8
#fuses HS, WDT, BROWNOUT, NOPUT, NOLVP

// define pins for SPI input reads and output writes
#use delay (clock=10000000)

#define SPI_IN_LATCH      PIN_C2
#define SPI_CLOCK         PIN_C3
#define SPI_DATA_OUT      PIN_D1
#define DIGITAL_OUT_LATCH PIN_D2
 

#define DIGITAL_IN_DATA PIN_C4
#include "spi_read.h"



int x = 0;

main ()
{
  while (1 )
    {
    Spi_write_data (&x, 1, DIGITAL_OUT_LATCH);
    x++;
    delay_ms (1);
    }
  
    
}

