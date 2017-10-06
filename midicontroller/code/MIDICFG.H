/****************************************************************************
* MidiCfg.h
* Contains the configuration data for the Midi configuration for each input 
* and output channel
*
* Configuration is stored as 64 element arrays
* 
* 256 bytes available due to PIC limitations. 
* Therefore, a max of 64 configuration types
*
* module shared between patch editor and PIC code
****************************************************************************/
#ifndef _MIDICFG_H
#define _MIDICFG_H

      

const byte ANA_OUT_CONTROLLER [] = {1, 2, 4, 7};

#define ANALOG_IN_CONFIG_INDEX  0
#define DIGITAL_IN_CONFIG_INDEX 16
#define ANALOGUE_OUT_CONFIG_INDEX 32
#define DIGITAL_OUT_CONFIG_INDEX  40

#define NOTEOFF_MASK 0x80
#define NOTEON_MASK 0x90
#define POLYPRESS_MASK 0xA0
#define CONTROLLER_MASK 0xB0
#define PROGCHANGE_MASK 0xC0
#define CHANPRESS_MASK 0xD0
#define PITCHBEND_MASK 0xE0

// define index for configuraion within eeprom
#define MAX_INPUT_CHAN 16
#define MAX_ANAOUTPUT_CHAN 8
#define MAX_DIGOUTPUT_CHAN 16
#define MIDI_CONFIG_START_ADDRESS 32

#define VALID_CONFIG_ADDRESS 0x0
#define DEVICE_ID_ADDRESS 0x01
#define MIDI_MERGE_ADDRESS 0x02


#define DEFAULT_ANA_IN_CONT 12
#define DEFAULT_DIG_IN_CONT 64
#define DEFAULT_DIG_OUT_CONT 80

// define bitmasks for config flags
#define DATA_1_VARY_MASK    0x01 // this means data 1 is the byte containg the variable value
#define INVERT_VALUE_MASK   0x02 // this means the variable value is inverted
#define MUTE_CONFIG_MASK    0x04 // no output generated for this configuration
#define MIDI_OUTPUT2_MASK   0x08 // Output generated on Midi output 2 insetad of 1
#define PRESET_VALUE_FLAG   0x10 // Value will be sent upon reset


/* define a structure for a midi config. max 4 bytes */
typedef unsigned char BYTE;

typedef struct
{
  BYTE status_chan;
  BYTE data_1;
  BYTE data_2;
  BYTE config_flag;
} str_midiconfig;


#ifdef _PATCH_EDITOR
  byte ReadConfigByte (int index);
  void WriteConfigByte (int index, byte value);
  void ReadMidiConfig (str_midiconfig* ret_config, byte index);
  void WriteMidiConfig (str_midiconfig* config, byte index);
  void ReadAnalogueInConfig(str_midiconfig* ret_config, int index);
  void ReadDigitalInConfig(str_midiconfig* ret_config, int index);
  void ReadAnalogueOutConfig(str_midiconfig* ret_config, int index);
  void ReadDigitalOutConfig(str_midiconfig* ret_config, int index);
#endif

#ifndef _NO_CODE
#pragma inline
short DoMidiMerge()
{
  return (ReadConfigByte(MIDI_MERGE_ADDRESS));
}

// note that index must be less than 64
void ReadMidiConfig (str_midiconfig* ret_config, byte index)
{
  byte i;
  byte* ret_ptr;
	byte start_memory_index; // the index within the RAM configuration array

  ret_ptr = (byte*)ret_config;
	start_memory_index = (byte)((index * sizeof (str_midiconfig))
		+ MIDI_CONFIG_START_ADDRESS);

  for (i = 0; i < sizeof (str_midiconfig); i++)
  {
    ret_ptr [i] = (byte)ReadConfigByte ((byte) (start_memory_index + i));
  }
} // end void ReadMidiConfig (str_midiconfig* ret_config, int index) 


// note that index must be less than 64
void WriteMidiConfig (str_midiconfig* config, byte index)
{
  byte i;
  byte* ptr;
	byte start_memory_index; // the index within the RAM configuration array

  ptr = (byte*)config;
  
	start_memory_index = (byte) ((index * sizeof (str_midiconfig))
		+ MIDI_CONFIG_START_ADDRESS);
  
	for (i = 0; i < sizeof (str_midiconfig); i++)
  {
    WriteConfigByte ((byte) (start_memory_index + i), ptr [i]);
  }
} // end void WriteMidiConfig (str_midiconfig* config, int index) 


#pragma inline
void ReadAnalogueInConfig(str_midiconfig* ret_config, int index)
{
	ReadMidiConfig (ret_config, (byte) (ANALOG_IN_CONFIG_INDEX + index));
}


# pragma inline
void ReadDigitalInConfig(str_midiconfig* ret_config, int index) 
{
	ReadMidiConfig (ret_config, (byte) (DIGITAL_IN_CONFIG_INDEX + index));
} // end void ReadDigitalInConfig(str_midiconfig* ret_config, int index) 


#pragma inline
void ReadAnalogueOutConfig(str_midiconfig* ret_config, int index) 
{
	ReadMidiConfig (ret_config, (byte) (ANALOGUE_OUT_CONFIG_INDEX + index));
} // end void ReadAnalogueOutConfig(str_midiconfig* ret_config, int index) 


#pragma inline 
void ReadDigitalOutConfig(str_midiconfig* ret_config, int index) 
{
	ReadMidiConfig (ret_config, (byte) (DIGITAL_OUT_CONFIG_INDEX + index));
} // end void ReadDigitalOutConfig(str_midiconfig* ret_config, int index) 

void GetDefaultAnalogueIn(str_midiconfig* ret_config, int index) 
{
  ret_config->status_chan = CONTROLLER_MASK | 0x00; // controller on channel 1 
  ret_config->data_1 = (byte) (DEFAULT_ANA_IN_CONT + index);
	ret_config->data_2 = 0; 
  ret_config->config_flag = 0;
} // end void GetDefaultAnalogueIn(str_midiconfig* ret_config, int index) 

void GetDefaultDigitalIn(str_midiconfig* ret_config, int index) 
{
  ret_config->status_chan = CONTROLLER_MASK | 0x00; // controller on channel 1 
  ret_config->data_1 = (byte) (DEFAULT_DIG_IN_CONT + index);
	ret_config->data_2 = 0;
  ret_config->config_flag = 0;
} // end void GetDefaultDigitalIn(str_midiconfig* ret_config, int index) 

void GetDefaultDigitalOut(str_midiconfig* ret_config, int index) 
{
  ret_config->status_chan = CONTROLLER_MASK | 0x00; // controller on channel 1 
  ret_config->data_1 = (byte) (DEFAULT_DIG_OUT_CONT + index);
	ret_config->data_2 = 0;
  ret_config->config_flag = 0;
} // end void GetDefaultDigitalOut(str_midiconfig* ret_config, int index) 

void GetDefaultAnalogueOut(str_midiconfig* ret_config, int index) 
{
	ret_config->status_chan = (byte) (CONTROLLER_MASK | (index / sizeof(ANA_OUT_CONTROLLER))); 
	ret_config->data_1 = ANA_OUT_CONTROLLER [index % sizeof(ANA_OUT_CONTROLLER)];
	ret_config->data_2 = 0;
  ret_config->config_flag = 0;
} // end void GetDefaultAnalogueOut(str_midiconfig* ret_config, int index) 

// gets the default for all types and writes it to eeprom
void ResetConfiguration()
{
	// configure analog in first
	str_midiconfig config;
	int i;

	for (i = 0; i < MAX_INPUT_CHAN; i++)
		{
			GetDefaultAnalogueIn (&config, i);

			WriteMidiConfig (&config, (byte) (i + ANALOG_IN_CONFIG_INDEX));
		}


	for (i = 0; i < MAX_INPUT_CHAN; i++)
		{
			GetDefaultDigitalIn (&config, i);

			WriteMidiConfig (&config, (byte) (i + DIGITAL_IN_CONFIG_INDEX));
		}

	for (i = 0; i < MAX_ANAOUTPUT_CHAN; i++)
		{
			GetDefaultAnalogueOut (&config, i);

			WriteMidiConfig (&config, (byte) (i + ANALOGUE_OUT_CONFIG_INDEX));
		}

	for (i = 0; i < MAX_DIGOUTPUT_CHAN; i++)
		{
			GetDefaultDigitalOut (&config, i);

			WriteMidiConfig (&config, (byte) (i + DIGITAL_OUT_CONFIG_INDEX));
		}

	WriteConfigByte (VALID_CONFIG_ADDRESS, 0x00);
} // end void ResetConfiguration()

// tests whether the config bit is valid (i.e between 0x80 and 0xEf)
short ValidConfig ()
{
	return (!ReadConfigByte (VALID_CONFIG_ADDRESS));
}// end short ValidConfig ()

int ReadDeviceId()
{
  int ret;
	ret = ReadConfigByte(DEVICE_ID_ADDRESS);
  return ret;
} // end ReadDeviceId 

// tests first config msg. If invalid, rewrites lot
void ValidateStoredConfig ()
{
	if (!ValidConfig ())
		{
			ResetConfiguration();
		}

} // end ValidateStoredConfig



// returns the number of bytes that need to be transmitted for this midi config
int NumTxBytes (str_midiconfig* config)
{
	int status_nibble;

	status_nibble = config->status_chan & 0xF0; // first nibble

	switch (status_nibble)
		{
		case NOTEOFF_MASK:
		case NOTEON_MASK: 
		case POLYPRESS_MASK:
		case CONTROLLER_MASK:
		case PITCHBEND_MASK:
			return 3;

		case PROGCHANGE_MASK:
		case CHANPRESS_MASK:
			return 2;
		default:
			return 0;
		}

} // end int NumTxBytes (str_midiconfig* config)

#endif /*_NO_CODE*/

#endif
