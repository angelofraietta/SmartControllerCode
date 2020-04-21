//## begin module%3D6AB5580013.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D6AB5580013.cm

//## begin module%3D6AB5580013.cp preserve=no
//## end module%3D6AB5580013.cp

//## Module: LinuxMidiOutputDriver%3D6AB5580013; Package body
//	Mac version of Midi OutputDriver
//## Subsystem: MidiDriver::hal_mac%3D6AB4D80041
//## Source file: D:\develop\SmartController\mididriver\hal_mac\linuxMidiOutputDriver.cpp

//## begin module%3D6AB5580013.additionalIncludes preserve=no
//## end module%3D6AB5580013.additionalIncludes

//## begin module%3D6AB5580013.includes preserve=yes
#include <stddef.h>
#include "iodata.h"
#include "midiflags.h"
//## end module%3D6AB5580013.includes

#include "midioutputdriver.h"
#include "midiinputdriver.h"
#include "filedriver.h"
#include "mididriver.h"
#include "midiutilities.h"
//## begin module%3D6AB5580013.declarations preserve=no
//## end module%3D6AB5580013.declarations

//## begin module%3D6AB5580013.additionalDeclarations preserve=yes


//UInt8 midiChannelInUse = 0; //we're using midi channel 1...

void SetSimDigitalOutput (unsigned channel, bool value);
void SetSimAnalogueOutput (unsigned channel, unsigned value);


//## end module%3D6AB5580013.additionalDeclarations


//## begin LinuxMidiOutputDriver%3D6AB8F6030E.preface preserve=yes
//## end LinuxMidiOutputDriver%3D6AB8F6030E.preface

//## Class: LinuxMidiOutputDriver%3D6AB8F6030E
//## Category: MidiDriver::hal_mac%3D6AB53A007E
//## Subsystem: MidiDriver::hal_mac%3D6AB4D80041
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class LinuxMidiOutputDriver : public MidiOutputDriver  //## Inherits: <unnamed>%3D6AB904021E
{
  //## begin LinuxMidiOutputDriver%3D6AB8F6030E.initialDeclarations preserve=yes
  //## end LinuxMidiOutputDriver%3D6AB8F6030E.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: LinuxMidiOutputDriver%1030404440
      LinuxMidiOutputDriver (int queue_size);

    //## Destructor (generated)
      ~LinuxMidiOutputDriver();


    //## Other Operations (specified)
      //## Operation: open%1030414461
      //	opens device
      bool open (int device_num, 	// The device number required by hardware. This value is
      	// the the device number in the hardware
      int device_id = -1	// Index that the device will be identified as the driver.
      	// -1 signifies that the device_num is used
      );

      //## Operation: close%1030414462
      //	closes device
      bool close ();

      //## Operation: TransmitMidiByte%1030414463
      //	Transmits Midi Byte to an output
      void TransmitMidiByte (unsigned char data, 	// The Midi byte to transmit
      int output_num = 0	// The Midi Output to go to
      );

      //## Operation: TransmitCV%1030414464
      //	Transmits a variable cv to output
      void TransmitCV (unsigned char data_val, int output_num);

      //## Operation: TransmitDigital%1030414465
      //	transmits digital CV outputs
      void TransmitDigital (unsigned char data_val, int output_num);

      //## Operation: TransmitSoftSynthMidiByte%1120506345
      //	Transmits Midi Byte to an output
      void TransmitSoftSynthMidiByte (unsigned char data, 	// The Midi byte to transmit
	    int output_num = 0	// The Midi Output to go to
     );
      
    // Additional Public Declarations
      //## begin LinuxMidiOutputDriver%3D6AB8F6030E.public preserve=yes
      // we will overload
      void TransmitMidiData (const MidiData& midi_data, int output_num = 0	// The Midi Output to go to
      );
      //## end LinuxMidiOutputDriver%3D6AB8F6030E.public

  protected:
    // Additional Protected Declarations
      //## begin LinuxMidiOutputDriver%3D6AB8F6030E.protected preserve=yes
      
      void TransmitSoftSynthMidiMesssage(const MidiData& midi_data);
      //## end LinuxMidiOutputDriver%3D6AB8F6030E.protected

  private:

    //## Other Operations (specified)
      //## Operation: TransmitSysex%1030414466
      bool TransmitSysex ();

      //## Operation: OpenSoftSynth%1120506346
      bool OpenSoftSynth ();

      //## Operation: CloseSoftSynth%1120506347
      bool CloseSoftSynth ();

    // Data Members for Class Attributes

      //## Attribute: _useSoftSynth%42C994980399
      //## begin LinuxMidiOutputDriver::_useSoftSynth%42C994980399.attr preserve=no  private: bool {UA} false
      bool _useSoftSynth;
      //## end LinuxMidiOutputDriver::_useSoftSynth%42C994980399.attr

      //## Attribute: _num_bytes%42C99C0A007D
      //	The number of bytes transmitted in this Midi Message
      //## begin LinuxMidiOutputDriver::_num_bytes%42C99C0A007D.attr preserve=no  private: int {UA} 0
      int _num_bytes;
      //## end LinuxMidiOutputDriver::_num_bytes%42C99C0A007D.attr

      //## Attribute: _running_status%42C99C0A009C
      //## begin LinuxMidiOutputDriver::_running_status%42C99C0A009C.attr preserve=no  private: char {UA} 0
      char _running_status;
      //## end LinuxMidiOutputDriver::_running_status%42C99C0A009C.attr

      //## Attribute: _in_sysex%42C99C0A00BB
      //	Flag to determine whether the current buffer is in a
      //	sysex message state
      //## begin LinuxMidiOutputDriver::_in_sysex%42C99C0A00BB.attr preserve=no  private: bool {UA} false
      bool _in_sysex;
      //## end LinuxMidiOutputDriver::_in_sysex%42C99C0A00BB.attr

      //## Attribute: _qtNoteAllocator%42C9A3D002CE
      //## begin LinuxMidiOutputDriver::_qtNoteAllocator%42C9A3D002CE.attr preserve=no  private: static NoteAllocator {UA} NULL
  //      static NoteAllocator _qtNoteAllocator;
      //## end LinuxMidiOutputDriver::_qtNoteAllocator%42C9A3D002CE.attr

    // Additional Private Declarations
      //## begin LinuxMidiOutputDriver%3D6AB8F6030E.private preserve=yes
      //## end LinuxMidiOutputDriver%3D6AB8F6030E.private
  private: //## implementation
    // Additional Implementation Declarations
      //## begin LinuxMidiOutputDriver%3D6AB8F6030E.implementation preserve=yes
      //## end LinuxMidiOutputDriver%3D6AB8F6030E.implementation

};

//## begin LinuxMidiOutputDriver%3D6AB8F6030E.postscript preserve=yes
//## end LinuxMidiOutputDriver%3D6AB8F6030E.postscript

// Class LinuxMidiOutputDriver 

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
  return false;
  //## end MidiOutputDriver::TxDataReady%1012859306.body
}

MidiOutputDriver* MidiOutputDriver::create (int queue_size)
{
  //## begin MidiOutputDriver::create%1012864640.body preserve=yes
  return new LinuxMidiOutputDriver (queue_size);
  //## end MidiOutputDriver::create%1012864640.body
}

// we are just going to overload this
void MidiOutputDriver::TransmitMidiData (const MidiData& midi_data, int output_num)
{
    printf ("MidiOutputDriver::TransmitMidiData base\r\n");
} 


void MidiOutputDriver::TransmitMidiMessageByte (unsigned char data, int output_num, unsigned device)
{
  //## begin MidiOutputDriver::TransmitMidiMessageByte%1018308378.body preserve=yes
    //printf ("MidiOutputDriver::TransmitMidiMessageByte %d %u \n", output_num, device);
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

	SetSimAnalogueOutput (output_num, data_val);

  //## end MidiOutputDriver::TransmitControlVoltage%1018308379.body
}

void MidiOutputDriver::TransmitDigitalVoltage (unsigned char data_val, int output_num, unsigned device)
{
  //## begin MidiOutputDriver::TransmitDigitalVoltage%1018308380.body preserve=yes

	SetSimDigitalOutput (output_num, data_val);

  //## end MidiOutputDriver::TransmitDigitalVoltage%1018308380.body
}

void MidiOutputDriver::TransmitMidiDataMessage (const MidiData& midi_data, int output_num, unsigned device)
{
  //## begin MidiOutputDriver::TransmitMidiDataMessage%1018308381.body preserve=yes
    printf ("MidiOutputDriver::TransmitMidiDataMessage\r\n");
  device = output_num;

  MidiOutputDriver* p_device = _devices[device];

  if (p_device)
  {

    p_device->TransmitMidiData(midi_data, output_num);

  }
  else
  {
      printf("No pDevice\r\n");
  }

  //## end MidiOutputDriver::TransmitMidiDataMessage%1018308381.body
}


void MidiOutputDriver::TransmitIoData (IOData io_data, int output_num, unsigned device)
{
  //## begin MidiOutputDriver::TransmitIoData%1031946742.body preserve=yes
  //## end MidiOutputDriver::TransmitIoData%1031946742.body
}

unsigned MidiOutputDriver::NumDevices ()
{
  //## begin MidiOutputDriver::NumDevices%1018316747.body preserve=yes
	return 0;
  //## end MidiOutputDriver::NumDevices%1018316747.body
}

bool MidiOutputDriver::GetDeviceName (unsigned index, char* ret_buf, unsigned buf_len)
{
  //## begin MidiOutputDriver::GetDeviceName%1049869260.body preserve=yes
	bool ret = false;


	return ret;
  //## end MidiOutputDriver::GetDeviceName%1049869260.body
}

// Additional Declarations
  //## begin MidiOutputDriver%3C5E05CA01BF.declarations preserve=yes
  //## end MidiOutputDriver%3C5E05CA01BF.declarations

// Class LinuxMidiOutputDriver 





//## begin LinuxMidiOutputDriver::_qtNoteAllocator%42C9A3D002CE.attr preserve=no  private: static NoteAllocator {UA} NULL
//NoteAllocator LinuxMidiOutputDriver::_qtNoteAllocator = NULL;
//## end LinuxMidiOutputDriver::_qtNoteAllocator%42C9A3D002CE.attr

LinuxMidiOutputDriver::LinuxMidiOutputDriver (int queue_size)
  //## begin LinuxMidiOutputDriver::LinuxMidiOutputDriver%1030404440.hasinit preserve=no
      : _useSoftSynth(false), _num_bytes(0), _running_status(0), _in_sysex(false)
  //## end LinuxMidiOutputDriver::LinuxMidiOutputDriver%1030404440.hasinit
  //## begin LinuxMidiOutputDriver::LinuxMidiOutputDriver%1030404440.initialization preserve=yes
  ,MidiOutputDriver (queue_size)
  //## end LinuxMidiOutputDriver::LinuxMidiOutputDriver%1030404440.initialization
{
  //## begin LinuxMidiOutputDriver::LinuxMidiOutputDriver%1030404440.body preserve=yes
  //## end LinuxMidiOutputDriver::LinuxMidiOutputDriver%1030404440.body
}


LinuxMidiOutputDriver::~LinuxMidiOutputDriver()
{
  //## begin LinuxMidiOutputDriver::~LinuxMidiOutputDriver%.body preserve=yes
  //## end LinuxMidiOutputDriver::~LinuxMidiOutputDriver%.body
}



//## Other Operations (implementation)
bool LinuxMidiOutputDriver::open (int device_num, int device_id)
{
  //## begin LinuxMidiOutputDriver::open%1030414461.body preserve=yes
  bool ret = false;

  return ret;
  //## end LinuxMidiOutputDriver::open%1030414461.body
}

bool LinuxMidiOutputDriver::close ()
{
  //## begin LinuxMidiOutputDriver::close%1030414462.body preserve=yes
    bool ret = true;
    return ret;
  //## end LinuxMidiOutputDriver::close%1030414462.body
}

void LinuxMidiOutputDriver::TransmitMidiByte (unsigned char data, int output_num)
{
  //## begin LinuxMidiOutputDriver::TransmitMidiByte%1030414463.body preserve=yes
  //## end LinuxMidiOutputDriver::TransmitMidiByte%1030414463.body
}

void LinuxMidiOutputDriver::TransmitCV (unsigned char data_val, int output_num)
{
  //## begin LinuxMidiOutputDriver::TransmitCV%1030414464.body preserve=yes
  //## end LinuxMidiOutputDriver::TransmitCV%1030414464.body
}

void LinuxMidiOutputDriver::TransmitDigital (unsigned char data_val, int output_num)
{
  //## begin LinuxMidiOutputDriver::TransmitDigital%1030414465.body preserve=yes
  //## end LinuxMidiOutputDriver::TransmitDigital%1030414465.body
}

bool LinuxMidiOutputDriver::TransmitSysex ()
{
  //## begin LinuxMidiOutputDriver::TransmitSysex%1030414466.body preserve=yes
    return false;
  //## end LinuxMidiOutputDriver::TransmitSysex%1030414466.body
}

void LinuxMidiOutputDriver::TransmitSoftSynthMidiByte (unsigned char data, int output_num)
{
  //## begin LinuxMidiOutputDriver::TransmitSoftSynthMidiByte%1120506345.body preserve=yes
  
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
          /*
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

        //if (midiOutShortMsg (_hmout, short_msg) != MMSYSERR_NOERROR)
        //  {
        //  MessageBox (0, "Unable to Tx byte", "MidiOut",  MB_OK);
        //  }
           * */
      } //dequedata
    } // end !sysex
  }
  
  //## end LinuxMidiOutputDriver::TransmitSoftSynthMidiByte%1120506345.body
}

bool LinuxMidiOutputDriver::OpenSoftSynth ()
{
  //## begin LinuxMidiOutputDriver::OpenSoftSynth%1120506346.body preserve=yes
    return false;

  //## end LinuxMidiOutputDriver::OpenSoftSynth%1120506346.body
}

bool LinuxMidiOutputDriver::CloseSoftSynth ()
{
  //## begin LinuxMidiOutputDriver::CloseSoftSynth%1120506347.body preserve=yes
    bool ret = false;
  return ret;
  //## end LinuxMidiOutputDriver::CloseSoftSynth%1120506347.body
}

void LinuxMidiOutputDriver::TransmitSoftSynthMidiMesssage(const MidiData& midi_data)
{
    printf("Midi Message 0x%1x %d %d \r\n", midi_data.status, midi_data.data1, midi_data.data2);
    //MusicDeviceMIDIEvent(_synthUnit, midi_data.status, midi_data.data1, midi_data.data2, 0);
}

void LinuxMidiOutputDriver::TransmitMidiData (const MidiData& midi_data, int output_num)
{
    printf("LinuxMidiOutputDriver::TransmitMidiData Mod\r\n");
    if (_useSoftSynth)
    {
        printf("LinuxMidiOutputDriver::TransmitSoftSynthMidiMesssage\r\n");
        TransmitSoftSynthMidiMesssage(midi_data);
    }
    else
    {
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
}

// Additional Declarations
  //## begin LinuxMidiOutputDriver%3D6AB8F6030E.declarations preserve=yes
  //## end LinuxMidiOutputDriver%3D6AB8F6030E.declarations

//## begin module%3D6AB5580013.epilog preserve=yes
//## end module%3D6AB5580013.epilog
