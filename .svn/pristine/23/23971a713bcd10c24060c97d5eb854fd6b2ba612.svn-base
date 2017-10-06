/*********************************************************************
Module defines functions used for Reading Analogue In
*********************************************************************/
int current_analogue_val[NUM_ANALOGUE_IN_CHANS];

#ifdef MIDI_CONTROLLER_BUILD
int16 current_analogue_lsb [NUM_ANALOGUE_IN_BANKS];
#endif

void ReadAnalogueIn(byte produce_output);

// initialise the previous analogue in values
// Sets RA0, RA1 and RA3 as analogue inputs
// Sets the B1 to B3 as Outputs
#USE FAST_IO(B)

#define CLEAR_BANK_MASK 0b11110001 // ANDing Mask will clear bits 1-3
void InitialiseAnalogueIn()
{
	int i;
	setup_adc (ADC_CLOCK_INTERNAL);
	setup_adc_ports (RA0_RA1_ANALOG_RA3_REF);

	set_tris_b (CLEAR_BANK_MASK);

 	for (i = 0; i < NUM_ANALOG_VALID_READS; i++)
 		{
 			current_analogue_val[i] = 0;
 		}

}

// reads the analogue in and produces output if different
short ProcessAnalogueIn()
{
	return ReadAnalogueIn (true);
}


// if produce_output is true, the result will be sent to the output 
// if different from previous value
short ReadAnalogueIn(byte produce_output)
{
  short ret = false;
	int sub_bank;
	int init_b;
	int bank_num;
	int adc_val;
  int adc_val_second_read;
	int channel_num;

	init_b = PORTB;	
	// clear sub_bank bits
	init_b &= CLEAR_BANK_MASK;

	for (sub_bank = 0; sub_bank < NUM_ANALOGUE_IN_SUB_BANKS; sub_bank++)
		{
			restart_wdt();
			// now write the sub_bank address to PORTB bits 1-3
			PORTB = init_b | (sub_bank<<1);

			delay_us (AD_SWITCH_DELAY);

			for (bank_num = 0; bank_num < NUM_ANALOGUE_IN_BANKS; bank_num++)
				{

#ifdef IOCARD_BUILD
          if (MessageWaiting())
          {
						ret = ProcessPlaInputStream(); 
					}

#endif

					channel_num = bank_num * NUM_ANALOGUE_IN_SUB_BANKS + sub_bank;

					set_adc_channel (bank_num);
					delay_us (AD_READ_DELAY);

					// only eight bits of AD required
					adc_val = read_adc();

          // now read channel second time
					set_adc_channel (bank_num);
					delay_us (AD_READ_DELAY);
          adc_val_second_read = read_adc();

#ifdef SEVEN_BIT_AD
					adc_val >>= 1;
          adc_val_second_read >>= 1;
#endif


					// see if this read and last matched

					if (adc_val_second_read == adc_val && current_analogue_val[channel_num] != adc_val )
						{

							if (produce_output)
								{
									if (OutputAnalog (channel_num, adc_val))
										{
											current_analogue_val[channel_num] = adc_val;
                      ret = true;
										}
								}
							else
								{
									current_analogue_val[channel_num] = adc_val;
								}
 						}

				}
		}
  return ret;
}


