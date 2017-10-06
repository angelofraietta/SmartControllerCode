/**********************************************************************
Performs the digital output using an SPI write
***********************************************************************/
typedef struct 
{
  byte upper;
  byte lower;
}str_digout;

str_digout current_value; // this is the current state of the digital pins


void GenerateDigitalOutput (int out_num, byte val)
{
  byte* byte_to_write = &current_value.lower;
  

  if (out_num >= 8)
    {
    byte_to_write = &current_value.upper;
    }
  
  // now define the bit num
  out_num %= 8;

	if (val > 63)
		{
			bit_set (*byte_to_write, out_num);
		}
	else
		{
			bit_clear (*byte_to_write, out_num);
		}

	Spi_write_data (&current_value, sizeof(current_value), DIGITAL_OUT_LATCH);
}

void InitialiseDigitalOut()
{
  current_value.upper = 0;
  current_value.lower = 0;
  GenerateDigitalOutput (0, 0);
}
