/******************************************************************************
Module for processing Digital Inputs
******************************************************************************/
// digital Read variables
int16 prev_digital_val;
int16 current_digital_val;


short ProcessDigitalInputs(int produce_output)
{
  short ret = false;
	int bit_num;
	int byte_num;
	byte *cur_val = &current_digital_val;
	byte *prev_val = &prev_digital_val;

	current_digital_val = 0;

	Spi_read_data (&current_digital_val, sizeof(current_digital_val), DIGITAL_IN_DATA);

	if (current_digital_val != prev_digital_val)
		{
			if (produce_output)
				{
          // iterate through each byte
					for (byte_num = 0; byte_num < sizeof(current_digital_val); byte_num++)
						{
							// iterate through each bit
							for (bit_num = 0; bit_num < 8; bit_num++)
								{
#ifdef IOCARD_BUILD
                if (MessageWaiting())
                  {
                    ProcessPlaInputStream(); 
                    ret = true;
                  }
#endif
									if (Bit_test (cur_val[byte_num], bit_num) 
											!= bit_test(prev_val[byte_num], bit_num))
										{
											// we use this fancy calculation because of the endian of an int16
											// we want the first byte to be the high order byte
                      // also, a one will produce a zero ouitput
											if (OutputDigital ((sizeof(current_digital_val)-1 - byte_num) * 8 + bit_num, 
																				 (!Bit_test (cur_val[byte_num], bit_num)) * DIG_ON_VAL))
												{
													if (Bit_test (cur_val[byte_num], bit_num) )
														{
															Bit_set(prev_val[byte_num], bit_num);
														}
													else
														{
															Bit_clear(prev_val[byte_num], bit_num);
														}
                          ret = true;
												}
										}
								}
						}
				}
			
		}

  return ret;
}
