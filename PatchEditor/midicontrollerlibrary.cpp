#include <stdio.h>
#include <memory.h>




#include "configmsg.h"
#include "sysexcommands.h"
#include "midicfg.h"
#include "procmidi.h"
#include "sysexWriter.h"
#include "midioutputdriver.h"


#include "mididrv.h"
#include "equeue.h"
using sm_str::e_static_queue;

#include "MidiInputUnit.h"

#define SETTINGS_FILENAME  "Settings.ini"


#include "sysex.h"

#define CONFIG_SIZE 256

byte config_data [CONFIG_SIZE];

byte reference_data [CONFIG_SIZE]; // this is a reference which we will use to see if our config has changed

const byte WriteCfgHeader [] = {SYSEX_ID, BASIC_MIDI_CONTROLLER, ANY_DEVICE_ID_NUM, WRITE_CONGFIG_BYTE};
const byte FactoryDefaultCfgHeader [] = {SYSEX_ID, BASIC_MIDI_CONTROLLER, ANY_DEVICE_ID_NUM, FACTORY_DEFAULT};
const byte ReadCfgHeader [] = {SYSEX_ID, BASIC_MIDI_CONTROLLER, ANY_DEVICE_ID_NUM, READ_CONFIG_BYTE};

SysexWriter* aMidiOut;
MidiInDriver* pMidiIn;
MidiOutputDriver* midi_out;

volatile bool in_sysex; // flag determining whether we are in a sysex
volatile unsigned byte_num;

volatile unsigned bytes_written;

volatile bool cancel_write;
unsigned out_device_num, in_device_num;

void ProcessMidiByte (unsigned char midi_data);

MidiData rx_midi_message;
e_static_queue <MidiData> midi_in_messages (CONFIG_SIZE);


bool   GetMidiData(MidiData* data)
{
  bool ret = !midi_in_messages.empty();
  if (ret)
  {
    data->status = midi_in_messages.top().status;
    data->data1 = midi_in_messages.top().data1;
    data->data2 = midi_in_messages.top().data2;
    midi_in_messages.pop();
  }
  return (ret);
}

void SetReferenceData()
{
  memcpy (reference_data, config_data, CONFIG_SIZE);
}

 bool ConfigChanged()
{
  return memcmp(reference_data, config_data, CONFIG_SIZE);
}

unsigned GetBytesWritten()
{
  return  bytes_written;
}

void WriteConfigByte(int index, byte value)
{
  if (index < CONFIG_SIZE)
  {
    config_data[index] = value;
  }
}


byte ReadConfigByte (int index)
{
  byte ret = 0x00;

  if (index < CONFIG_SIZE)
  {
    ret = config_data[index];
  }

  return ret;

}


void InitialisePatchEditor ()
{
  pMidiIn  = new MidiInDriver (ProcessMidiByte, 1024);
  midi_out  = MidiOutputDriver::create (1024);
  aMidiOut = new SysexWriter;
  in_sysex = false;

  SetFactoryDefault();
  ValidateStoredConfig();
  SetReferenceData();
  pMidiIn->start();
}

void DeInitialisePatchEditor()
{
    pMidiIn->close();
    delete pMidiIn;
    delete aMidiOut;

    if (midi_out)
      {
      delete midi_out;
      midi_out = NULL;
      }

}


bool WriteConfigChannelData (const STR_CONFIG &config_msg)
{
  byte configMessage [sizeof(WriteCfgHeader) + sizeof(STR_CONFIG)];
  memcpy (configMessage, WriteCfgHeader, sizeof(WriteCfgHeader));
  memcpy (configMessage + sizeof(WriteCfgHeader), &config_msg, sizeof (config_msg));

  aMidiOut->WriteSysexData (out_device_num, configMessage, sizeof(WriteCfgHeader) + sizeof(STR_CONFIG));
  return true;
}

bool SendFactoryDefault()
{
  SetFactoryDefault();
  SetReferenceData();
  ValidateStoredConfig();
  aMidiOut->WriteSysexData (out_device_num, FactoryDefaultCfgHeader, sizeof(FactoryDefaultCfgHeader));
  return true;
}

bool SendMidiData(const MidiData& data)
{
  midi_out->TransmitMidiData(data);
  return true;
}

 bool SetOutputDevice(unsigned dev_num)
{
  out_device_num = dev_num;
  return midi_out->open(dev_num);
}

 bool SetIntputDevice(unsigned dev_num)
{
  bool ret = pMidiIn->open (dev_num);
  pMidiIn->start();
  return ret;
}

 bool SendReadConfig()
{
  printf ("Request Config Data\r\n");
  byte read_params [2];
  byte configMessage [sizeof(ReadCfgHeader) + sizeof(read_params)];

  read_params[0] = 0; // start at index 0
  read_params[1] = 255; // end index

  memcpy (configMessage, ReadCfgHeader, sizeof(ReadCfgHeader));
  memcpy (configMessage + sizeof(ReadCfgHeader), read_params, sizeof (read_params));

  aMidiOut->WriteSysexData (out_device_num, configMessage, sizeof(configMessage));
  return true;
}

 bool WriteNextConfigByte()
{
  bool ret = false;

  if (!cancel_write && bytes_written < CONFIG_SIZE)
    {

      byte configMessage [sizeof(WriteCfgHeader) + sizeof(STR_CONFIG)];
      STR_CONFIG config_msg;


      //SendStatus->Position = bytes_written;
      config_msg.index = (byte)(bytes_written);
      config_msg.status = ReadConfigByte (bytes_written++);
      config_msg.data1 =  ReadConfigByte (bytes_written++);
      config_msg.data2 = ReadConfigByte (bytes_written++);
      config_msg.data3 = ReadConfigByte (bytes_written++);


      memcpy (configMessage, WriteCfgHeader, sizeof(WriteCfgHeader));
      memcpy (configMessage + sizeof(WriteCfgHeader), &config_msg, sizeof (config_msg));

      aMidiOut->WriteSysexData (out_device_num, configMessage, sizeof(WriteCfgHeader) + sizeof(STR_CONFIG));
      printf ("Wrote %d bytes\r\n", bytes_written);
      ret = true;
    }

    return ret;
}

void ProcessMidiByte (unsigned char midi_data)
{
  if (midi_data & STATUS_BYTE_MASK) // this is a status byte
  {
    byte_num = 0;

    byte status_nibble = (byte) (midi_data & STATUS_NIBBLE_MASK);

    if (status_nibble == SYSTEM_MSG_VAL) // then this is system message
      {
        ProcessSystemMessage (midi_data);
        ValidateStoredConfig();
        //UpdateConfig();
      }
    else
      {
        midi_status.in_sysex = 0; // clear in sysex flag
        midi_status.current_msg.status_chan = midi_data;

        midi_status.bytes_left = (byte) (MidiUtilities::num_bytes (midi_data) -1);
        // store the last status that we have transmitted
        midi_status.last_status_chan = midi_data;

        midi_status.byte_num = 0;
        printf ("\r\nMidi In %u ", midi_data);
        rx_midi_message.status = midi_data;
      }

  }
  else
  {
    if (midi_status.in_sysex)
      {

        if (midi_status.our_sysex)
          {
          if (DecodeMidiByte (&midi_status.control_char, &midi_data))
            {
            midi_status.our_sysex = DecodeSysexByte (midi_data);
            }
          }
      }
    else
    {
      byte_num++;
      switch (byte_num)
      {
        case 0:
          printf ("\r\nMidi In %u ", midi_data);
          rx_midi_message.status = midi_data;
          midi_status.bytes_left = (byte) (MidiUtilities::num_bytes (midi_data) -1);
          break;
        case 1:
          printf ("%u ", midi_data);
          rx_midi_message.data1 = midi_data;
          midi_status.bytes_left--;
          break;

        case 2:
          printf ("%u ", midi_data);
          rx_midi_message.data2 = midi_data;
          midi_status.bytes_left--;
          break;
      } // end switch

      if (!midi_status.bytes_left)
      {
        printf ("Message Complete\r\n");
        if (!midi_in_messages.push(rx_midi_message))
        {
          printf ("Overflow\r\n");
        }

      }
    }
  }

}

bool LoadConfig (const char* filename)
{
  bool ret = false;

  FILE* infile = fopen(filename, "r+b");

  if (infile)
  {
    ret = (fread(config_data, 1, CONFIG_SIZE, infile));

    fclose(infile);

  }
  return ret;

}

 bool SaveConfig (const char* filename)
{
  bool ret = false;

  FILE* outfile = fopen(filename, "w+b");

  if (outfile)
  {
    ret = (fwrite(config_data, 1, CONFIG_SIZE, outfile));

    fclose(outfile);
  }

  return ret;
}

bool CancelWrite()
{
  cancel_write = true;
  bytes_written = 0;
  return true;
}

void ProcessAcknowledge()
{
  WriteNextConfigByte();
}

unsigned GetNumMidiInDevices()
{
  return MidiInputDriver::NumDevices ();
}

unsigned GetNumMidiOutDevices()
{
  return MidiOutputDriver::NumDevices ();
}

bool GetMidiInputName (unsigned device_index, char* ret_buf, unsigned buf_len)
{
  return MidiInputDriver::GetDeviceName (device_index, ret_buf, buf_len);
}

bool GetMidiOutputName (unsigned device_index, char* ret_buf, unsigned buf_len)
{
  return MidiOutputDriver::GetDeviceName (device_index, ret_buf, buf_len);
}

void SendConfig()
{
  cancel_write = false;
  bytes_written = 0;
  WriteNextConfigByte();
}
