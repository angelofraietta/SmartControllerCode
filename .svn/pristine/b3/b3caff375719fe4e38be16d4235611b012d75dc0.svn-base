/*************************************************************
Module contains Flags used for using 16 bit word as bitmask

Tx and RX are respective to the Smart Controller CPU device
The Midi IO board, therefore would treat it's tx as RX
*************************************************************/

#define TX_DATA_MASK    0x8000
#define DATA_TYPE_MASK   0x7000
#define DATA_PARAMS_MASK 0x0F00
#define DATA_VALUE_MASK  0x00FF

// define the diagnostic messages

#define DIAG_DIAG_MESSAGE_FLAG 0xFF

#define DIAG_INVALID_RX_DATA 0xFFFF //this means this message is bad
#define DIAG_MESSAGE_MASK 0xFF00 // we are checking the first byte
#define DIAG_RE_TRANSMIT_LAST_MESSAGE 0xFF00 // We are requesting the last message be re-sent
#define DIAG_ETX 0xFF01 // This is the End of our transmission. Pic Requires a response
#define DIAG_ECHO 0xFF02 // Same Data is returned. Initiated by PIC
#define DIAG_RESET 0xFF03 // Reset. Sent by 386 upon device driver startup
#define DIAG_ASYNC_MESSAGE_READY 0xFF04 // 386 has a message ready, transmitted asynchronously from 386.
#define DIAG_SYNC_MESSAGE_READY 0xFF05 // 386 has a message ready, transmitted within context of ISR from 386.  
#define DIAG_RECEIVE_RESPONSE  0xFF06 // 386 has received PICS message but has no data. Response still required
#define DIAG_REQUEST_RX_BYTES  0xFF07 // requesting the number of Data bytes received be returned
#define DIAG_REQUEST_TX_BYTES  0xFF08 // requesting the number of Data bytes transmitted be returned
#define DIAG_NO_DATA           0xFF0A // this means that the 386 last sent a DIAG_ETX
// Synchronisation returns have the number as the last nibble. Value is therefore 0 to F
#define DIAG_RETURN_RX_BYTES   0xFFE0
#define DIAG_RETURN_TX_BYTES   0xFFD0
#define DIAG_TEST_RETURN_BYTES_MASK 0xFFF0 // AND with Diag message to determine whether it is a synch mask
#define DIAG_RETURN_BYTES_MASK 0x0001 // AND with Message to read the number of bytes. Only test 1 and zero

#define SYSEX_START_STATUS 0xF0
#define SYSEX_END_STATUS 	 0xF7
	
/*************************************************
16 bit Message Consists of following Bits

T  DDD CCCC DATABYTE

T = Transmit Data - 1 bit
DDD = Data Types - 3 bits (listed below). Up to a maximum of 7
CCCC = Channel - 4 bits (16 channels)
DATABYTE = Message Data Value - 8 bits

Note that DDDCCCC that equals 7F is a diag message
**************************************************/
#define TX_DATA_FLAG      0x80

// define four Data Types. Last three bits of first byte. Remaining are Type specific
// the define with 16 are the values shifted left one byte
#define MIDI_CHAN_1_DATA     0x00
#define MIDI_CHAN_1_DATA_16  0x00

#define MIDI_CHAN_2_DATA     0x10 // also used for Lower 2 bits of Analogue Data
#define MIDI_CHAN_2_DATA_16  0x1000 // also used for Lower 2 bits of Analogue Data

#define ANALOG_DATA          0x20 // upper 8 bits
#define ANALOG_DATA_16       0x2000 // upper 8 bits

#define ANALOG_LOWER_DATA    0x10 // lower 2 bits - input to 386 only
#define ANALOG_LOWER_DATA_16  0x1000 // lower 2 bits - input to 386 only

#define DIGITAL_DATA         0x30
#define DIGITAL_DATA_16      0x3000

#define EEPROM_WRITE_PAGE_SIZE 64 // the maximum we are allowed to write at one time
#define EEPROM_READ_PAGE_SIZE  128 // the number of bytes we will receive from the IO card
#define EEPROM_INT_PAGE_SIZE   256

// define EEPROM flags 
#define EEPROM_DATA          0x40 
#define EEPROM_INIT_ADDRESS  0x41 // sent by 386
#define EEPROM_START_WRITE   0x42 // sent by 386
#define EEPROM_END_WRITE     0x43 // completes the page write
#define EEPROM_WRITE_READY   0x44 // sent by PIC
#define EEPROM_END_READ      0x45 // sent by PIC
#define EEPROM_BLOCK_READ    0x46 // sent by 386

// define masks to Disable and enable IO
#define EEPROM_START         0x47 // get exclusive access to IO
#define EEPROM_END           0x48 // remove exclusive access to IO
#define EEPROM_REBOOT        0x4B // reboot if we have exclusive access to IO

// define Masks for the internal rom
#define INT_EEPROM_DATA      0x49
#define INT_EEPROM_READ      0x4A

// define flags for IO infortmation
#define IO_FLAGS             0x50
#define IO_WATCHDOG_TYPE     IO_FLAGS // the data will Determine the behaviour of the Watchdog led
// now define the types of Watchdog
#define IO_NO_PATCH          0x00
#define IO_PATCH_LOADED      0x01
#define IO_ERROR             0x02

// note that we must reserve 0x60 flags with data 0x00 for TX_NO_DATA
#define TX_NO_DATA        0x6000 // Value increments num tx on Pic but not on 386




