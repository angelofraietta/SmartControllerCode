/**************************************************************
 * Author: Angelo Fraietta
 * Description: Midi output interface
 *************************************************************/

// forward declarations
void ProcessMidiInputStream();
short MidiOutFree();
void SetLastStatusChan(byte);

#inline
void OutputMidi (str_midiconfig* midi_msg)
{
	int num_bytes;
	byte* msg_ptr;
	int i;
  short midi_out_2;

  midi_out_2 = midi_msg->config_flag & MIDI_OUTPUT2_MASK;
  
  
	num_bytes = NumTxBytes (midi_msg);
	msg_ptr = (byte*) midi_msg;

	// make sure that there is no merge happening
	while (!MidiOutFree())
		{
			ProcessMidiInputStream();
		}

	// store the last status that we are sending
	SetLastStatusChan (msg_ptr[0]);

	for (i = 0; i < num_bytes; i++)
		{
      if (midi_out_2)
      {
			  WriteOutData2 (msg_ptr [i]); 
      }

      else
      {
			  WriteOutData (msg_ptr [i]); 
      }
		}

	
}
#inline
short OutputAnalog (int channel, int value)
{
  int num_bytes;
  
	str_midiconfig midi_msg;

	ReadAnalogueInConfig (&midi_msg, channel);

  if (!(MUTE_CONFIG_MASK  & midi_msg.config_flag))
    {
    num_bytes = NumTxBytes (&midi_msg);

		if (INVERT_VALUE_MASK & midi_msg.config_flag)
			{
				value ^= 0x7f; // flip all but msb
			}
		
		switch (num_bytes)
			{
			case 3:
				if (DATA_1_VARY_MASK & midi_msg.config_flag)
					{
						midi_msg.data_1 = value;
					}
				else
					{
						midi_msg.data_2 = value;
					}
				break;
				
			case 2:
				midi_msg.data_1 = value;
				break;
				
			default:
			}
		
		OutputMidi (&midi_msg);
		}
  return true;
}

#inline
short OutputDigital (int channel, int value)
{
  int num_bytes;
	str_midiconfig midi_msg;

	ReadDigitalInConfig (&midi_msg, channel);

  if (!(MUTE_CONFIG_MASK  & midi_msg.config_flag))
    {
    num_bytes = NumTxBytes (&midi_msg);

		if (INVERT_VALUE_MASK & midi_msg.config_flag)
			{
				value ^= 0x7f; // flip all but msb
			}
		
		switch (num_bytes)
			{
			case 3:
				if (DATA_1_VARY_MASK & midi_msg.config_flag)
					{
						midi_msg.data_1 = value;
					}
				else
					{
						midi_msg.data_2 = value;
					}
				
				break;
				
			case 2:
				midi_msg.data_1 = value;
				break;
				
			default:
			}
		
		
		OutputMidi (&midi_msg);
		}
  return true;
}























