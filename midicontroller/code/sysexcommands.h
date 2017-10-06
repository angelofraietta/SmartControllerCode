#ifndef _SYSEXCAMMANDS_H
#define _SYSEXCAMMANDS_H

#define BASIC_MIDI_CONTROLLER 0x00
#define SMART_CONTROLLER      0x01

// define SYSEX ID education/ research
#define SYSEX_ID 0x7D
#define EQUIPMENT_TYPE BASIC_MIDI_CONTROLLER
#define ANY_DEVICE_ID_NUM 0xff // any device will respond


// define the numbers of the bytes within a sysyex message
#define SYSEX_ID_NUM 1
#define SYSEX_EQUIPMENT_NUM 2
#define SYSEX_DEVICE_NUM 3
#define SYSEX_COMMAND_NUM 4
#define SYSEX_CONGIG_INDEX_NUM 5


// define COMMANDS
#define READ_CONFIG_BYTE 0
#define WRITE_CONGFIG_BYTE 1
#define FACTORY_DEFAULT 2
#define WRITE_ACKNOWLEDGE 3


#define SYSEX_BEGIN 0xF0
#define SYSEX_END 0xF7
#define SYSTEM_RESET 0xFF
#define SYSTEM_QUARTER_FRAME 0xF1
#define SYSTEM_SONG_POS 0xF2
#define SYSTEM_SONG_SELECT 0xF3


#define STATUS_BYTE_MASK 0x80 
#define SYSTEM_MSG_VAL 0xF0
#define STATUS_NIBBLE_MASK 0xF0

#endif



