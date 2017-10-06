/**********************************************************************
 * decodes midi message and produces an output if we are configured to
 *
 *dependant uponf midicfg.h,  
 *********************************************************************/

void GenerateAnalogueOutput (int out_num, byte val);
void GenerateDigitalOutput (int out_num, byte val);


#inline
short MatchingConfig (str_midiconfig* test, str_midiconfig* reference)
{
  short ret;
  byte match_only_status;

  ret = !(MUTE_CONFIG_MASK  & reference->config_flag);

  
  ret = ret && (test->status_chan == reference->status_chan);
  
  match_only_status = DATA_1_VARY_MASK & reference->config_flag;
  
  if (!match_only_status)
    {
    ret = ret	&& (test->data_1 == reference->data_1);
    }

  return ret;
}

// test all analogs and digitals for a match
void DecodeMidiMessage (str_midiconfig* test_msg)
{
	str_midiconfig config;
	int i;
  byte outval;

  outval = test_msg->data_2;
 
	for (i = 0; i < NUM_ANALOGUE_OUT; i++)
		{
#ifndef _SIMULATE
			ReadAnalogueOutConfig (&config, i);
#else
      GetDefaultAnalogueOut (&config, i);
#endif
			if (MatchingConfig (test_msg, &config))
				{
          if (DATA_1_VARY_MASK & config.config_flag)
            {
					  outval = test_msg->data_1;  
            }

          if (INVERT_VALUE_MASK & config.config_flag)
            {
            outval ^= 0x7f; // flip all but msb
            }

          GenerateAnalogueOutput (i, outval << 1); // multiply by 2
             
				}
		}

	for (i = 0; i < NUM_DIGITAL_OUT; i++)
		{
#ifndef _SIMULATE
			ReadDigitalOutConfig (&config, i);
#else
      GetDefaultDigitalOut (&config, i);
#endif		
	if ( MatchingConfig (test_msg, &config))
				{
          if (DATA_1_VARY_MASK & config.config_flag)
            {
					  outval = test_msg->data_1;  
            }
          
          if (INVERT_VALUE_MASK & config.config_flag)
            {
            outval ^= 0x7f; // flip all but msb
            }

            
					GenerateDigitalOutput (i, outval);
				}
		}

}
