/*******************************************************************************
*	Author: Angelo Fraietta
*	Description: General SPI Read function
*	Processor N/A
* Inputs: 
*    data_size: size of the data structure receiving the data
*    data_pin: the I/O pin that receives the data*     
* Outputs:
*           ret_data: pointer to structure to receive data 
*
* Global
*    SPI_IN_LATCH: the I/O pin that latches input registers
*    SPI_CLOCK: the I/O pin that clocks the device shift registers


*	Description:
* 
*		The registers are latched. 
*   [iterate]
*   The state of the Input is read and shifted left
*   When 8 bits are read and shifted, the value is stored into ret_data


* Notes: asuumes the I/O pins are configured if not using standard I/O
* Assumes a Low latch and a Low to High clock
*******************************************************************************/
#inline
void Spi_read_data (int* ret_data, 
											int data_size, 
											int data_pin)
{
	int byte_num;
	int bit_num;
	byte in_val;
	short data_val;

	// prepare clock
	output_low (SPI_CLOCK);

  // latch the data
  switch (data_pin)
  {
    case DIGITAL_IN_DATA:
	
	    output_low (SPI_IN_LATCH);
	    output_high (SPI_IN_LATCH);
      break;

    default:
      break;
  }

	
	for (byte_num = 0; byte_num < data_size; byte_num++)
		{
			in_val = 0;

			for (bit_num = 0; bit_num < 8; bit_num++)
				{
					in_val <<= 1; // first shift is a dummy. Only seven are really shifted

					// read the input
					switch (data_pin)
						{
							case DIGITAL_IN_DATA:
								data_val = input (DIGITAL_IN_DATA);
								break;
              
						}

					if (data_val)
						{
							in_val |= 0x0001;
						}

					// now clock register
					output_high (SPI_CLOCK);
					output_low (SPI_CLOCK);
				}

			// now store that byte in ret_data
			ret_data [byte_num] = in_val;
		}
}


/*******************************************************************************
*	Author: Angelo Fraietta
*	Description: General SPI Write function
*	Processor N/A
* Inputs: 
*    out_data: structure containing the data to be written
*    data_size: size of the data structure receiving the data
*    latch_pin: the I/O pin that receives the data*     
* Outputs:
*           Data written to the outputs after being latched
*
* Global
*    SPI_CLOCK: the I/O pin that clocks the device shift registers
*    SPI_DATA_OUT: the data I/O pin that receives the output data

*	Description:
* 
*		The registers are latched. 
*   [iterate]
*   The state of the Output is written and shifted left
*   When 8 bits are read and shifted, the value is stored into ret_data


* Notes: asuumes the I/O pins are configured if not using standard I/O
* Assumes a Low latch and a Low to High clock
*******************************************************************************/
#inline
void Spi_write_data (int* out_data, 
											int data_size, 
											int latch_pin)
{
	int byte_num;
	int bit_num;
	byte out_val;
	short data_val;
  
	// prepare clock
	output_low (SPI_CLOCK);

	for (byte_num = 0; byte_num < data_size; byte_num++)
		{
			out_val = out_data [byte_num];
 

			for (bit_num = 0; bit_num < 8; bit_num++)
				{
					// write the high bit
          output_bit (SPI_DATA_OUT, out_val & 0x80);
          out_val<<=1;

					// now clock register
					output_high (SPI_CLOCK);
					output_low (SPI_CLOCK);
				}


		}

	// latch the data
  switch (latch_pin)
  {
    case DIGITAL_OUT_LATCH:
	    output_low (DIGITAL_OUT_LATCH);
	    output_high (DIGITAL_OUT_LATCH);
      break;

  }
}



