/***************************************************
Module for decoding Incoming sysex messages
 note that all messages must have a MSB of 0
**************************************************/

#define MAX_MIDIDCONTROLLER_PARAMS 4

#ifndef MIDI_CONTROLLER_BUILD
typedef int int32;

#define MAX_PARAMS 256
void ProcessAcknowledge();
#else
#define MAX_PARAMS MAX_MIDIDCONTROLLER_PARAMS
#endif



#ifndef MIDI_CONTROLLER_BUILD
void ProcessreadConfigMsg();
#endif

typedef struct
{
	int command_type; // the command type of this message
	int config_index; // the start index
	int32 byte_num; // the byte number of the byte coming in
	int config_data_size; // the current index for config bytes
	byte config_data [MAX_PARAMS];

} STR_SYSEX_MSG;
	
STR_SYSEX_MSG current_sysex_msg;



#pragma inline
void SetFactoryDefault()
{
  byte i;
  
  for (i = 0; i < 0xff; i++)
    {
#ifdef MIDI_CONTROLLER_BUILD
    restart_wdt();
#endif
    WriteConfigByte (i, 0xff);
    }
#ifdef MIDI_CONTROLLER_BUILD
  while (1); // wait till we watchdog
#endif
}

#pragma inline
void ProcessReadConfigMsg()
{
	byte i; // must be byte so will cycle around 0xff
#ifdef MIDI_CONTROLLER_BUILD
	// now write the config
  WriteSysexHeader();

	WriteSysexOutData (WRITE_CONGFIG_BYTE);
#endif

	i = (byte) current_sysex_msg.config_index;

#ifdef MIDI_CONTROLLER_BUILD
  WriteSysexOutData (current_sysex_msg.config_index);
	WriteSysexOutData (ReadConfigByte (i));
#endif


  do
	  {
      i++; 
#ifdef MIDI_CONTROLLER_BUILD
			restart_wdt();
			WriteSysexOutData (ReadConfigByte (i));
#endif
		} while (i != current_sysex_msg.config_data[0]); // end index

#ifdef MIDI_CONTROLLER_BUILD    
	WriteOutData (SYSEX_END);
#endif
}// end ProcessReadConfigMsg

#pragma inline
void ProcessWriteConfigMsg()
{
	int i;

#ifdef MIDI_CONTROLLER_BUILD
	disable_interrupts (GLOBAL);
#endif

	for (i = 0; i < current_sysex_msg.config_data_size; i++)
		{
#ifdef MIDI_CONTROLLER_BUILD
      restart_wdt();
#endif
			WriteConfigByte (i + current_sysex_msg.config_index, 
											 current_sysex_msg.config_data[i]);
		}
#ifdef MIDI_CONTROLLER_BUILD
	enable_interrupts (GLOBAL);

  WriteSysexHeader();

	WriteSysexOutData (WRITE_ACKNOWLEDGE);

	WriteOutData (SYSEX_END);

#endif //#ifdef MIDI_CONTROLLER_BUILD

} // end  ProcessWriteConfigMsg()


void ResetSysex()
{
	current_sysex_msg.byte_num = 0;
	current_sysex_msg.config_index = 0;
	current_sysex_msg.config_data_size = 0;
}

short DecodeSysexByte (byte byte_val)
{
	short ret;
	current_sysex_msg.byte_num++;

 	switch (current_sysex_msg.byte_num)
		{
		case SYSEX_ID_NUM:
			ret = (byte_val == SYSEX_ID);
			break;

		case SYSEX_EQUIPMENT_NUM:
			ret = (byte_val == EQUIPMENT_TYPE);
			break; 

		case SYSEX_DEVICE_NUM:
			ret = (byte_val == ReadDeviceId() || byte_val == ANY_DEVICE_ID_NUM);
			break;

		case SYSEX_COMMAND_NUM:
			current_sysex_msg.command_type = byte_val;
      ret = true;
			break;

		case SYSEX_CONGIG_INDEX_NUM:
			current_sysex_msg.config_index = byte_val;
      current_sysex_msg.config_data_size = 0;
			ret = true;
			break;

		default:
			if (current_sysex_msg.config_data_size < MAX_PARAMS)
				{
					current_sysex_msg.config_data [current_sysex_msg.config_data_size] 
						= byte_val;
					ret = true;
				}
			else
				{
					ret = false;
				}

			current_sysex_msg.config_data_size++;

		} // end case


	return ret;
} // end DecodeSysexByte

void ExecuteSysexMessage()
{
	switch (current_sysex_msg.command_type)
		{ 
		case WRITE_CONGFIG_BYTE:
			ProcessWriteConfigMsg();
			break;
			
		case READ_CONFIG_BYTE:
			
			ProcessReadConfigMsg();
			break;

		case FACTORY_DEFAULT: // we will never return
			SetFactoryDefault();
			break;

#ifndef MIDI_CONTROLLER_BUILD      
    case WRITE_ACKNOWLEDGE:
      ProcessAcknowledge();
      break;
#endif
		default:
      break;
		}
} // end ExecuteSysexMessage()



