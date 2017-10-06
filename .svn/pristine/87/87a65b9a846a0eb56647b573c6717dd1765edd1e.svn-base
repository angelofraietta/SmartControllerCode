//---------------------------------------------------------------------------
#include "midioutputdriver.h"
#include "SysexWriter.h"
#include "mididrv.h"


SysexWriter::SysexWriter ()
{}

SysexWriter::~SysexWriter()
{
}

bool SysexWriter::WriteSysexData (unsigned midi_device, const byte* buf, unsigned buflen)
{
  bool ret = false;
	int sysex_size;
  int sysex_buf_index;


  //sysex_size = CalculateMidiTxBufferSize ((byte*)buf, buflen) + 2;// add start and stop

  sysex_buf_index = 0;
  _sysexbuf [sysex_buf_index] = 0xf0;

  MidiOutputDriver::TransmitMidiMessageByte (0xf0, 0, midi_device);

  sysex_buf_index++;

  for (unsigned i = 0; i < buflen; i++)
  	{
    byte tx_byte = buf [i];
    byte control_char = EncodeMidiByte (&tx_byte);

    if (control_char)
    	{
      MidiOutputDriver::TransmitMidiMessageByte (control_char, 0, midi_device);
      }

    MidiOutputDriver::TransmitMidiMessageByte (tx_byte, 0, midi_device);
    }

  MidiOutputDriver::TransmitMidiMessageByte(0xf7, 0, midi_device);

  return ret;
}   // end WriteSysexData

//---------------------------------------------------------------------------
#pragma package(smart_init)
