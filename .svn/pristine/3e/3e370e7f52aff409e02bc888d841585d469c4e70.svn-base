//## begin module%3C5F014002FC.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C5F014002FC.cm

//## begin module%3C5F014002FC.cp preserve=no
//## end module%3C5F014002FC.cp

//## Module: WindowsMidiOutputDriver%3C5F014002FC; Package body
//## Subsystem: MidiDriver::hal_windows%3C5F00760139
//## Source file: C:\develop\WinSmartController\mididriver\hal_windows\windowsmidioutputdriver.cpp

//## begin module%3C5F014002FC.additionalIncludes preserve=no
#include <windows.h>
#include <mmsystem.h>
//## end module%3C5F014002FC.additionalIncludes

//## begin module%3C5F014002FC.includes preserve=yes
#include <windows.h>
#include "midiflags.h"
#include <stdio.h>

//## end module%3C5F014002FC.includes

#include "midioutputdriver.h"
#include "midiinputdriver.h"
#include "filedriver.h"
#include "mididriver.h"
#include "midiutilities.h"
//## begin module%3C5F014002FC.declarations preserve=no
//## end module%3C5F014002FC.declarations

//## begin module%3C5F014002FC.additionalDeclarations preserve=yes
// forward declaration
void SetSimDigitalOutput (unsigned channel, bool value);
void SetSimAnalogueOutput (unsigned channel, unsigned value);

void CALLBACK WindowsMidiOutProc(

    HMIDIOUT hmo,
    UINT wMsg,
    DWORD dwInstance,
    DWORD dwParam1,	
    DWORD dwParam2	
   );
//## end module%3C5F014002FC.additionalDeclarations


//## begin WindowsMidiOutputDriver%3C5F1ED00074.preface preserve=yes
//## end WindowsMidiOutputDriver%3C5F1ED00074.preface

//## Class: WindowsMidiOutputDriver%3C5F1ED00074
//## Category: MidiDriver::hal_windows%3C5F1EB6009E
//## Subsystem: MidiDriver::hal_windows%3C5F00760139
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class WindowsMidiOutputDriver : public MidiOutputDriver  //## Inherits: <unnamed>%3C5F1EDC0248
{
  //## begin WindowsMidiOutputDriver%3C5F1ED00074.initialDeclarations preserve=yes
  //## end WindowsMidiOutputDriver%3C5F1ED00074.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: WindowsMidiOutputDriver%1012864641
      //	Constructor which defines queue size
      WindowsMidiOutputDriver (int queue_size);

    //## Destructor (generated)
      ~WindowsMidiOutputDriver();


    //## Other Operations (specified)
      //## Operation: open%1012864646
      //	opens device
      bool open (int device_num, 	// The device number required by hardware. This value is
      	// the the device number in the hardware
      int device_id = -1	// Index that the device will be identified as the driver.
      	// -1 signifies that the device_num is used
      );

      //## Operation: close%1012864647
      //	closes device
      bool close ();

      //## Operation: TransmitMidiByte%1012864648
      //	Transmits Midi Byte to an output
      void TransmitMidiByte (unsigned char data, 	// The Midi byte to transmit
      int output_num = 0	// The Midi Output to go to
      );

      //## Operation: TransmitCV%1012864649
      //	Transmits a variable cv to output
      void TransmitCV (unsigned char data_val, int output_num);

      //## Operation: TransmitDigital%1012864650
      //	transmits digital CV outputs
      void TransmitDigital (unsigned char data_val, int output_num);

    // Additional Public Declarations
      //## begin WindowsMidiOutputDriver%3C5F1ED00074.public preserve=yes
      //## end WindowsMidiOutputDriver%3C5F1ED00074.public

  protected:
    // Additional Protected Declarations
      //## begin WindowsMidiOutputDriver%3C5F1ED00074.protected preserve=yes
      //## end WindowsMidiOutputDriver%3C5F1ED00074.protected

  private:

    //## Other Operations (specified)
      //## Operation: TransmitSysex%1013465078
      bool TransmitSysex ();

    // Data Members for Class Attributes

      //## Attribute: _hmout%3C5F23580112
      //## begin WindowsMidiOutputDriver::_hmout%3C5F23580112.attr preserve=no  private: HMIDIOUT {UA} 0
      HMIDIOUT _hmout;
      //## end WindowsMidiOutputDriver::_hmout%3C5F23580112.attr

      //## Attribute: _num_bytes%3C5F2D3B0270
      //	The number of bytes transmitted in this Midi Message
      //## begin WindowsMidiOutputDriver::_num_bytes%3C5F2D3B0270.attr preserve=no  private: int {UA} 0
      int _num_bytes;
      //## end WindowsMidiOutputDriver::_num_bytes%3C5F2D3B0270.attr

      //## Attribute: _running_status%3C5F3DD9037B
      //## begin WindowsMidiOutputDriver::_running_status%3C5F3DD9037B.attr preserve=no  private: char {UA} 0
      char _running_status;
      //## end WindowsMidiOutputDriver::_running_status%3C5F3DD9037B.attr

      //## Attribute: _in_sysex%3C683F230233
      //	Flag to determine whether the current buffer is in a
      //	sysex message state
      //## begin WindowsMidiOutputDriver::_in_sysex%3C683F230233.attr preserve=no  private: bool {UA} false
      bool _in_sysex;
      //## end WindowsMidiOutputDriver::_in_sysex%3C683F230233.attr

      //## Attribute: _sysex_buf%3C683FBF011F
      //## begin WindowsMidiOutputDriver::_sysex_buf%3C683FBF011F.attr preserve=no  private: unsigned char* {UA} 
      unsigned char* _sysex_buf;
      //## end WindowsMidiOutputDriver::_sysex_buf%3C683FBF011F.attr

      //## Attribute: _sysex_hdr%3C684888015F
      //## begin WindowsMidiOutputDriver::_sysex_hdr%3C684888015F.attr preserve=no  private: MIDIHDR* {UA} (MIDIHDR*)(GlobalLock (GlobalAlloc (GHND, sizeof (MIDIHDR))))
      MIDIHDR* _sysex_hdr;
      //## end WindowsMidiOutputDriver::_sysex_hdr%3C684888015F.attr

    // Additional Private Declarations
      //## begin WindowsMidiOutputDriver%3C5F1ED00074.private preserve=yes
      //## end WindowsMidiOutputDriver%3C5F1ED00074.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin WindowsMidiOutputDriver%3C5F1ED00074.implementation preserve=yes
      //## end WindowsMidiOutputDriver%3C5F1ED00074.implementation

};

//## begin WindowsMidiOutputDriver%3C5F1ED00074.postscript preserve=yes
//## end WindowsMidiOutputDriver%3C5F1ED00074.postscript

// Class WindowsMidiOutputDriver 

// Class MidiOutputDriver 


//## begin MidiOutputDriver::_max_devices%3CB2310200A6.attr preserve=no  protected: static int {VA} 6
int MidiOutputDriver::_max_devices = 6;
//## end MidiOutputDriver::_max_devices%3CB2310200A6.attr


//## begin MidiOutputDriver::_devices%3CB22B7F01B6.role preserve=no  protected: static MidiOutputDriver { -> 0..nUHAN}
MidiOutputDriver*  MidiOutputDriver::_devices[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
//## end MidiOutputDriver::_devices%3CB22B7F01B6.role


MidiOutputDriver::MidiOutputDriver (int queue_size)
  //## begin MidiOutputDriver::MidiOutputDriver%1012859302.hasinit preserve=no
      : _tx_ready(false)
  //## end MidiOutputDriver::MidiOutputDriver%1012859302.hasinit
  //## begin MidiOutputDriver::MidiOutputDriver%1012859302.initialization preserve=yes
  , MidiDriver(queue_size)
  //## end MidiOutputDriver::MidiOutputDriver%1012859302.initialization
{
  //## begin MidiOutputDriver::MidiOutputDriver%1012859302.body preserve=yes
  //## end MidiOutputDriver::MidiOutputDriver%1012859302.body
}


MidiOutputDriver::~MidiOutputDriver()
{
  //## begin MidiOutputDriver::~MidiOutputDriver%.body preserve=yes
  //## end MidiOutputDriver::~MidiOutputDriver%.body
}



//## Other Operations (implementation)
bool MidiOutputDriver::TxDataReady (IOData* io_data)
{
  //## begin MidiOutputDriver::TxDataReady%1012859306.body preserve=yes
  return true;
  //## end MidiOutputDriver::TxDataReady%1012859306.body
}

MidiOutputDriver* MidiOutputDriver::create (int queue_size)
{
  //## begin MidiOutputDriver::create%1012864640.body preserve=yes
  return new WindowsMidiOutputDriver(queue_size);
  //## end MidiOutputDriver::create%1012864640.body
}

void MidiOutputDriver::TransmitMidiData (const MidiData& midi_data, int output_num)
{
  //## begin MidiOutputDriver::TransmitMidiData%1013488868.body preserve=yes
  //## end MidiOutputDriver::TransmitMidiData%1013488868.body

  int tx_bytes =  MidiUtilities::num_bytes((char) midi_data.status);
    
  TransmitMidiByte (midi_data.status,output_num);
    
  if (tx_bytes > 1)
    {
      TransmitMidiByte (midi_data.data1, output_num);
    }
    
  if (tx_bytes > 2)
    {
      TransmitMidiByte (midi_data.data2, output_num);
     }
}

void MidiOutputDriver::TransmitMidiMessageByte (unsigned char data, int output_num, unsigned device)
{
  //## begin MidiOutputDriver::TransmitMidiMessageByte%1018308378.body preserve=yes
  MidiOutputDriver* p_device = _devices[device];

  if (p_device)
  {
  	p_device->TransmitMidiByte(data, output_num);
  }

  //## end MidiOutputDriver::TransmitMidiMessageByte%1018308378.body
}

void MidiOutputDriver::TransmitControlVoltage (unsigned char data_val, int output_num, unsigned device)
{
  //## begin MidiOutputDriver::TransmitControlVoltage%1018308379.body preserve=yes
  MidiOutputDriver* p_device = _devices[device];

  if (p_device)
  {
  	p_device->TransmitCV(data_val, output_num);
  }
  //## end MidiOutputDriver::TransmitControlVoltage%1018308379.body
}

void MidiOutputDriver::TransmitDigitalVoltage (unsigned char data_val, int output_num, unsigned device)
{
  //## begin MidiOutputDriver::TransmitDigitalVoltage%1018308380.body preserve=yes
  MidiOutputDriver* p_device = _devices[device];
  if (p_device)
  {
  	p_device->TransmitDigital(data_val, output_num);
  }

  //## end MidiOutputDriver::TransmitDigitalVoltage%1018308380.body
}

void MidiOutputDriver::TransmitMidiDataMessage (const MidiData& midi_data, int output_num, unsigned device)
{
  //## begin MidiOutputDriver::TransmitMidiDataMessage%1018308381.body preserve=yes
#ifdef _HAL_WINDOWS
	device = output_num;
#endif

  MidiOutputDriver* p_device = _devices[device];

  if (p_device)
  {
  	p_device->TransmitMidiData(midi_data, output_num);
  }

  //## end MidiOutputDriver::TransmitMidiDataMessage%1018308381.body
}

void MidiOutputDriver::TransmitIoData (IOData io_data, int output_num, unsigned device)
{
  //## begin MidiOutputDriver::TransmitIoData%1031946742.body preserve=yes
  IOData data_flags = (IOData )((io_data & 0xff00) >>8);
  IOData data = io_data & (IOData) 0xFF;
  char c;

  unsigned i;
      /*
  switch (data_flags)
  {
    case EEPROM_INIT_ADDRESS:
      FileDriver::InitPosition ();
      break;

    case EEPROM_END_WRITE:
      FileDriver::Flush ();
      break;

    case EEPROM_DATA:
      FileDriver::WriteByte (data, 0);
      break;

    case INT_EEPROM_DATA:
      FileDriver::WriteByte (data, 1);
      break;


    case EEPROM_START_WRITE:
      MidiInputDriver::ExtDataInput (EEPROM_WRITE_READY << 8);
      break;

    case EEPROM_BLOCK_READ:
      for (i = 0; i < EEPROM_READ_PAGE_SIZE; i++)
      {
        FileDriver::ReadByte (&c, 0);
        data = c & 0xff;
        data_flags = EEPROM_DATA * 0x100;
        MidiInputDriver::ExtDataInput (data_flags | data);

      }
      data_flags = EEPROM_END_READ * 0x100;
      MidiInputDriver::ExtDataInput (data_flags);
      break;

    case INT_EEPROM_READ:
      for (i = 0; i < EEPROM_INT_PAGE_SIZE; i++)
      {
        if (FileDriver::ReadByte (&c, 1))
        {
          data = c & 0xff;
          data_flags = INT_EEPROM_DATA * 0x100;
          MidiInputDriver::ExtDataInput (data_flags | data);
        }
      }
      data_flags = EEPROM_END_READ * 0x100;
      MidiInputDriver::ExtDataInput (data_flags);
      break;

    default:
      break;

    }
        */
  //## end MidiOutputDriver::TransmitIoData%1031946742.body
}

unsigned MidiOutputDriver::NumDevices ()
{
  //## begin MidiOutputDriver::NumDevices%1018316747.body preserve=yes
  return  midiOutGetNumDevs();
  //## end MidiOutputDriver::NumDevices%1018316747.body
}

bool MidiOutputDriver::GetDeviceName (unsigned index, char* ret_buf, unsigned buf_len)
{
  //## begin MidiOutputDriver::GetDeviceName%1049869260.body preserve=yes
  bool ret = false;
	MIDIOUTCAPS Caps;

	if(midiOutGetDevCaps(index, (LPMIDIOUTCAPS) &Caps, sizeof(Caps)) !=
			MMSYSERR_BADDEVICEID)
  {
		strncpy(ret_buf, (LPSTR)Caps.szPname, buf_len);
    // make sure last char is null
    ret_buf [buf_len -1] = 0;
	  ret = true;
  }
  return ret;
  //## end MidiOutputDriver::GetDeviceName%1049869260.body
}

// Additional Declarations
  //## begin MidiOutputDriver%3C5E05CA01BF.declarations preserve=yes
  //## end MidiOutputDriver%3C5E05CA01BF.declarations

// Class WindowsMidiOutputDriver 







WindowsMidiOutputDriver::WindowsMidiOutputDriver (int queue_size)
  //## begin WindowsMidiOutputDriver::WindowsMidiOutputDriver%1012864641.hasinit preserve=no
      : _hmout(0), _num_bytes(0), _running_status(0), _in_sysex(false), _sysex_hdr((MIDIHDR*)(GlobalLock (GlobalAlloc (GHND, sizeof (MIDIHDR)))))
  //## end WindowsMidiOutputDriver::WindowsMidiOutputDriver%1012864641.hasinit
  //## begin WindowsMidiOutputDriver::WindowsMidiOutputDriver%1012864641.initialization preserve=yes
  ,MidiOutputDriver (queue_size)
  //## end WindowsMidiOutputDriver::WindowsMidiOutputDriver%1012864641.initialization
{
  //## begin WindowsMidiOutputDriver::WindowsMidiOutputDriver%1012864641.body preserve=yes
    _sysex_buf = (unsigned char*) GlobalLock(GlobalAlloc(GHND, queue_size));
  //## end WindowsMidiOutputDriver::WindowsMidiOutputDriver%1012864641.body
}


WindowsMidiOutputDriver::~WindowsMidiOutputDriver()
{
  //## begin WindowsMidiOutputDriver::~WindowsMidiOutputDriver%.body preserve=yes
  close();
  GlobalFree (_sysex_buf);
  GlobalFree(_sysex_hdr);
  //## end WindowsMidiOutputDriver::~WindowsMidiOutputDriver%.body
}



//## Other Operations (implementation)
bool WindowsMidiOutputDriver::open (int device_num, int device_id)
{
  //## begin WindowsMidiOutputDriver::open%1012864646.body preserve=yes
  bool ret = false;

  close();

  if (device_num < _max_devices)
  {
  	ret = (midiOutOpen(&_hmout, device_num, NULL, (DWORD)this, CALLBACK_NULL) ==
  		MMSYSERR_NOERROR);

    if (ret)
    	{
      if (device_id == -1 || device_id >= _max_devices)
      	{
      	_devices[device_num] = this;
        }
      else
      	{
        _devices[device_id] = this;
        }
      }
    }

    return ret;
  //## end WindowsMidiOutputDriver::open%1012864646.body
}

bool WindowsMidiOutputDriver::close ()
{
  //## begin WindowsMidiOutputDriver::close%1012864647.body preserve=yes
  if (_hmout)
  {
  	midiOutClose(_hmout);
  	_hmout = 0;
  }

  return true;
  //## end WindowsMidiOutputDriver::close%1012864647.body
}

void WindowsMidiOutputDriver::TransmitMidiByte (unsigned char data, int output_num)
{
  //## begin WindowsMidiOutputDriver::TransmitMidiByte%1012864648.body preserve=yes
  IOData iodata = data;
	EnqueData(iodata);

  // test for status
  if (data & 0x80)
  {
    switch (data & 0xff) // we have to add the 0xff because we have to have an int
    {
      case SYSEX_START_STATUS:
        _in_sysex = true;
        _num_bytes = -1;
        break;

      case SYSEX_END_STATUS:
        _num_bytes = 0;
        break;

      default:
        _num_bytes = MidiUtilities::num_bytes(data) - 1;
    }
  }
  else
  {
    _num_bytes--;
  }


  // we are ready to transmit
  if(!_num_bytes)
  {
    if (_in_sysex)
    {
      TransmitSysex();
      _in_sysex = false;
    }
    else
    {
      if (DequeData(&iodata))
      {
        // write the status byte
        int tx_bytes =  MidiUtilities::num_bytes((char) (iodata & 0xff));
        DWORD short_msg = iodata & 0xff;
        // now write remaining bytes
        for (int i = 1; i <= tx_bytes; i++)
        {
          if (DequeData(&iodata))
          {
            DWORD byte_mask = iodata & 0xff;
            // now shift data to left one byte for every position
            for (int j = 0; j < i; j++)
            {
              byte_mask <<=8;
            } // for (unsigned j = 0; j < i; j++)

           short_msg |=  byte_mask;
          }  // if (DequeData(&iodata))
        } // for (unsigned i = 1; i <= tx_bytes; i++)

        if (midiOutShortMsg (_hmout, short_msg) != MMSYSERR_NOERROR)
          {
          MessageBox (0, "Unable to Tx byte", "MidiOut",  MB_OK);
          }
      } //dequedata
    } // end !sysex
  }

  //## end WindowsMidiOutputDriver::TransmitMidiByte%1012864648.body
}

void WindowsMidiOutputDriver::TransmitCV (unsigned char data_val, int output_num)
{
  //## begin WindowsMidiOutputDriver::TransmitCV%1012864649.body preserve=yes
  SetSimAnalogueOutput (output_num, data_val);
  //## end WindowsMidiOutputDriver::TransmitCV%1012864649.body
}

void WindowsMidiOutputDriver::TransmitDigital (unsigned char data_val, int output_num)
{
  //## begin WindowsMidiOutputDriver::TransmitDigital%1012864650.body preserve=yes
  SetSimDigitalOutput (output_num, data_val);
  //## end WindowsMidiOutputDriver::TransmitDigital%1012864650.body
}

bool WindowsMidiOutputDriver::TransmitSysex ()
{
  //## begin WindowsMidiOutputDriver::TransmitSysex%1013465078.body preserve=yes
  IOData iodata;
  unsigned num_bytes = 0;
  int reason;
  bool ret = false;

  reason = midiOutPrepareHeader (_hmout, _sysex_hdr, sizeof (MIDIHDR));

  while (DequeData(&iodata))
  {
  	_sysex_buf[num_bytes] = (unsigned char)(iodata & 0xff);
  	num_bytes++;
  }


  _sysex_hdr->lpData = (char*)_sysex_buf;
  _sysex_hdr->dwBufferLength =  num_bytes;

  reason = midiOutPrepareHeader (_hmout, _sysex_hdr, sizeof (MIDIHDR));
  if (reason ==  MMSYSERR_NOERROR)
    {
    midiOutLongMsg (_hmout, _sysex_hdr,  sizeof (MIDIHDR));
    ret = true;
    }

  return ret;
  //## end WindowsMidiOutputDriver::TransmitSysex%1013465078.body
}

// Additional Declarations
  //## begin WindowsMidiOutputDriver%3C5F1ED00074.declarations preserve=yes

// function only required for SYSex data
void CALLBACK WindowsMidiOutProc(

    HMIDIOUT hmo,	
    UINT wMsg,	
    DWORD dwInstance,
    DWORD dwParam1,	
    DWORD dwParam2	
   )
{
/*
  WindowsMidiOutputDriver* pDriver = (WindowsMidiOutputDriver*)dwInstance;

  if (dwInstance)
  {
    pDriver->TxDataReady();
  }
  */
}
  //## end WindowsMidiOutputDriver%3C5F1ED00074.declarations
//## begin module%3C5F014002FC.epilog preserve=yes
//## end module%3C5F014002FC.epilog
