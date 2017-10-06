/**************************************************************
 * Module for processing Midi input on PIC
 * Contains running status, and determines how many bytes left to 
 * read in an input midi message
 *
 * dependant upon midicfg.h, decmidi.h
 *************************************************************/


// forward declaration
void ResetController ();
short DecodeSysexByte (byte byte_val);
void ResetSysex();
void ExecuteSysexMessage();

typedef struct
{
	str_midiconfig current_msg;
	byte in_sysex :1;
	byte bytes_left :2; // the number of bytes remaining in this message
	byte our_sysex :1; // this could be our sysex
	byte byte_num:4 ;   // the byte number within current message
	byte last_status_chan;
	byte control_char; // for sysex commands
} str_midistatus;

str_midistatus midi_status;

void InitialiseMidiStatus()
{
	midi_status.current_msg.status_chan = 0;
	midi_status.in_sysex = 0;
	midi_status.bytes_left = 0;
	midi_status.byte_num = 0;
	midi_status.last_status_chan = 0; // the last status sent by us
}

void SetLastStatusChan (byte status_chan)
{
	midi_status.last_status_chan = status_chan;
}

#ifdef MIDI_CONTROLLER_BUILD
// returns true if the merge is currently free
short MidiOutFree()
{
	return (!DoMidiMerge()) || (InQueueEmpty () 
          && !midi_status.bytes_left 
          && !midi_status.in_sysex);
}

#endif

#pragma  inline
void ProcessSystemMessage ( byte midi_byte)
{
	switch (midi_byte)
		{
		case SYSEX_BEGIN:
			midi_status.in_sysex = 1;
			midi_status.our_sysex = 1;
			midi_status.current_msg.status_chan = 0;
			midi_status.byte_num = 0;
			midi_status.last_status_chan = 0;
			midi_status.control_char = 0x00;
			ResetSysex();
			break;

		case SYSTEM_QUARTER_FRAME:
			midi_status.byte_num = 0;
			midi_status.bytes_left = 1;
			break;

		case SYSTEM_SONG_POS:
			midi_status.byte_num = 0;
			midi_status.bytes_left = 2;
			break;

		case SYSTEM_SONG_SELECT:
			midi_status.byte_num = 0;
			midi_status.bytes_left = 1;
			break;

		case SYSEX_END:
			if (midi_status.our_sysex) 
				{
					ExecuteSysexMessage();
				}
			midi_status.in_sysex = 0;
			midi_status.our_sysex = 0;
			midi_status.current_msg.status_chan = 0;
			midi_status.byte_num = 0;
			midi_status.last_status_chan = 0;
			
      break;

		case SYSTEM_RESET:
			//reset_cpu();
#ifdef MIDI_CONTROLLER_BUILD
			while (1); // wait for watchdog
#endif
			break;
		default:
      break;
			// just ignore
		}
} // end void ProcessSystemMessage ( byte midi_byte)

#ifdef MIDI_CONTROLLER_BUILD
// ensures that complete midi word is transmitted 
void ProcessMidiInputStream()
{
	byte midi_byte;
	byte status_nibble;
	byte* msg_ptr;
  short valid_byte;
	
	while (!InQueueEmpty())
		{
			restart_wdt();
			midi_byte = GetInChar();

			if (midi_byte & STATUS_BYTE_MASK) // then this is a status byte
				{
          if (DoMidiMerge())
  					{
							WriteOutData (midi_byte);
						}

					status_nibble = midi_byte & STATUS_NIBBLE_MASK;

					if (status_nibble == SYSTEM_MSG_VAL) // then this is system message
            {
							ProcessSystemMessage (midi_byte);
            }
          else
						{
							midi_status.in_sysex = 0; // clear in sysex flag
							midi_status.current_msg.status_chan = midi_byte;

							midi_status.bytes_left = NumTxBytes (&(midi_status.current_msg)) -1;
							// store the last status that we have transmitted
							midi_status.last_status_chan = midi_byte;
					
							midi_status.byte_num = 0;		
						}
					
				}
			else // not a status byte
				{
					midi_status.byte_num++;

					if (midi_status.in_sysex)
						{
							// we need to write data out
              if (DoMidiMerge())
								{
									WriteOutData (midi_byte);
								}

							if (midi_status.our_sysex)
								{
                if (DecodeMidiByte (&midi_status.control_char, &midi_byte))
  								{
                  midi_status.our_sysex = DecodeSysexByte (midi_byte);	
                  }
								}
						}
					else // not in sysex
						{
              valid_byte = 1;

							if (!midi_status.bytes_left)// must be using running status
								{
									valid_byte = (NumTxBytes (&(midi_status.current_msg)));
    
                  if (valid_byte)
                    {
											midi_status.bytes_left = NumTxBytes (&(midi_status.current_msg)) -1;

											if (midi_status.last_status_chan 
													!= midi_status.current_msg.status_chan)
												{
                          if (DoMidiMerge())
														{
															WriteOutData (midi_status.current_msg.status_chan);
														}

													midi_status.last_status_chan = midi_status.current_msg.status_chan;
												}

											midi_status.byte_num = 1;
                    }
								}
							
              if (valid_byte)
								{
                if (DoMidiMerge())
									{
										WriteOutData (midi_byte);
									}

									// store current byte 
									msg_ptr = (byte*)(&midi_status.current_msg);
									msg_ptr [midi_status.byte_num] = midi_byte;
							
									midi_status.bytes_left--;
							
									// if no bytes to tx, we need to decode to see if we need to produce some sort of o/p
									if (!midi_status.bytes_left)
										{
											DecodeMidiMessage (&midi_status.current_msg);
										}
								}
						}
				}
		}
}

#endif 
