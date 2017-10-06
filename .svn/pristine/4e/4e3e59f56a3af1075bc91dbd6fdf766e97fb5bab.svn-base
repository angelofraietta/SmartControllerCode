//## begin module%3C5F01310106.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C5F01310106.cm

//## begin module%3C5F01310106.cp preserve=no
//## end module%3C5F01310106.cp

//## Module: RtemsMidiOutputDriver%3C5F01310106; Package body
//## Subsystem: MidiDriver::hal_rtems%3C5F008D0309
//## Source file: C:\develop\WinSmartController\mididriver\hal_rtems\rtemsmidioutputdriver.cpp

//## begin module%3C5F01310106.additionalIncludes preserve=no
//## end module%3C5F01310106.additionalIncludes

//## begin module%3C5F01310106.includes preserve=yes
#include <stddef.h>
#include <rtems.h>
#include "rtemsmididriver.h"
#include "midiflags.h"
#include "filedriver.h"
//## end module%3C5F01310106.includes

#include "midioutputdriver.h"
#include "midiinputdriver.h"
#include "filedriver.h"
#include "mididriver.h"
#include "midiutilities.h"
//## begin module%3C5F01310106.declarations preserve=no
//## end module%3C5F01310106.declarations

//## begin module%3C5F01310106.additionalDeclarations preserve=yes
//## end module%3C5F01310106.additionalDeclarations


//## begin RtemsMidiOutputDriver%3C606BDA01EB.preface preserve=yes
//## end RtemsMidiOutputDriver%3C606BDA01EB.preface

//## Class: RtemsMidiOutputDriver%3C606BDA01EB
//## Category: MidiDriver::hal_rtems%3C606B4B0131
//## Subsystem: MidiDriver::hal_rtems%3C5F008D0309
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class RtemsMidiOutputDriver : public MidiOutputDriver  //## Inherits: <unnamed>%3C606BE60239
{
  //## begin RtemsMidiOutputDriver%3C606BDA01EB.initialDeclarations preserve=yes
  //## end RtemsMidiOutputDriver%3C606BDA01EB.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: RtemsMidiOutputDriver%1012952099
      //	Constructor which defines queue size
      RtemsMidiOutputDriver (int queue_size);

    //## Destructor (generated)
      ~RtemsMidiOutputDriver();


    //## Other Operations (specified)
      //## Operation: open%1012952100
      //	opens device
      bool open (int device_num, 	// The device number required by hardware. This value is
      	// the the device number in the hardware
      int device_id = -1	// Index that the device will be identified as the driver.
      	// -1 signifies that the device_num is used
      );

      //## Operation: close%1012952101
      //	closes device
      bool close ();

      //## Operation: TransmitMidiByte%1012952102
      //	Transmits Midi Byte to an output
      void TransmitMidiByte (unsigned char data, 	// The Midi byte to transmit
      int output_num = 0	// The Midi Output to go to
      );

      //## Operation: TransmitCV%1012952103
      //	Transmits a variable cv to output
      void TransmitCV (unsigned char data_val, int output_num);

      //## Operation: TransmitDigital%1012952104
      //	transmits digital CV outputs
      void TransmitDigital (unsigned char data_val, int output_num);

      //## Operation: TransmitIO%1031946741
      //	transmits direct to IO
      void TransmitIO (IOData data_val, int output_num);

    // Additional Public Declarations
      //## begin RtemsMidiOutputDriver%3C606BDA01EB.public preserve=yes
      //## end RtemsMidiOutputDriver%3C606BDA01EB.public

  protected:
    // Additional Protected Declarations
      //## begin RtemsMidiOutputDriver%3C606BDA01EB.protected preserve=yes
      //## end RtemsMidiOutputDriver%3C606BDA01EB.protected

  private:

    //## Other Operations (specified)
      //## Operation: TransmitData%1012952110
      //	Transmits directly to the output
      void TransmitData (IOData data);

    // Additional Private Declarations
      //## begin RtemsMidiOutputDriver%3C606BDA01EB.private preserve=yes
      //## end RtemsMidiOutputDriver%3C606BDA01EB.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin RtemsMidiOutputDriver%3C606BDA01EB.implementation preserve=yes
      //## end RtemsMidiOutputDriver%3C606BDA01EB.implementation

};

//## begin RtemsMidiOutputDriver%3C606BDA01EB.postscript preserve=yes
//## end RtemsMidiOutputDriver%3C606BDA01EB.postscript

// Class RtemsMidiOutputDriver 

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
	// this function is only called in the context of an ISR

	// need to write the next bit of data if available to calling function
	_tx_ready = false;
	return DequeData (io_data);
  //## end MidiOutputDriver::TxDataReady%1012859306.body
}

MidiOutputDriver* MidiOutputDriver::create (int queue_size)
{
  //## begin MidiOutputDriver::create%1012864640.body preserve=yes
	return new RtemsMidiOutputDriver(queue_size);
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
	unsigned midi_device = device / 2; // each device has two devices

  MidiOutputDriver* p_device = _devices[midi_device];

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
	RtemsMidiOutputDriver* p_device = (RtemsMidiOutputDriver*)_devices[device];
	if (p_device)
		{
			p_device->TransmitIO(io_data, output_num);
		}
	
    //## end MidiOutputDriver::TransmitIoData%1031946742.body
}

unsigned MidiOutputDriver::NumDevices ()
{
  //## begin MidiOutputDriver::NumDevices%1018316747.body preserve=yes
	return 6; // this number will do for now
  //## end MidiOutputDriver::NumDevices%1018316747.body
}

bool MidiOutputDriver::GetDeviceName (unsigned index, char* ret_buf, unsigned buf_len)
{
  //## begin MidiOutputDriver::GetDeviceName%1049869260.body preserve=yes
  //## end MidiOutputDriver::GetDeviceName%1049869260.body
}

// Additional Declarations
  //## begin MidiOutputDriver%3C5E05CA01BF.declarations preserve=yes
  //## end MidiOutputDriver%3C5E05CA01BF.declarations

// Class RtemsMidiOutputDriver 

RtemsMidiOutputDriver::RtemsMidiOutputDriver (int queue_size)
  //## begin RtemsMidiOutputDriver::RtemsMidiOutputDriver%1012952099.hasinit preserve=no
  //## end RtemsMidiOutputDriver::RtemsMidiOutputDriver%1012952099.hasinit
  //## begin RtemsMidiOutputDriver::RtemsMidiOutputDriver%1012952099.initialization preserve=yes
  :MidiOutputDriver (queue_size)
  //## end RtemsMidiOutputDriver::RtemsMidiOutputDriver%1012952099.initialization
{
  //## begin RtemsMidiOutputDriver::RtemsMidiOutputDriver%1012952099.body preserve=yes
  //## end RtemsMidiOutputDriver::RtemsMidiOutputDriver%1012952099.body
}


RtemsMidiOutputDriver::~RtemsMidiOutputDriver()
{
  //## begin RtemsMidiOutputDriver::~RtemsMidiOutputDriver%.body preserve=yes
	close();
  //## end RtemsMidiOutputDriver::~RtemsMidiOutputDriver%.body
}



//## Other Operations (implementation)
bool RtemsMidiOutputDriver::open (int device_num, int device_id)
{
  //## begin RtemsMidiOutputDriver::open%1012952100.body preserve=yes
	bool success;

	_device_num = device_num;
	success = RtemsMidiDriver::AddOutputDevice(device_num, this);

	_tx_ready = (true);

	_devices [device_num] = this;

	return success;
  //## end RtemsMidiOutputDriver::open%1012952100.body
}

bool RtemsMidiOutputDriver::close ()
{
  //## begin RtemsMidiOutputDriver::close%1012952101.body preserve=yes
	return true;
  //## end RtemsMidiOutputDriver::close%1012952101.body
}

void RtemsMidiOutputDriver::TransmitMidiByte (unsigned char data, int output_num)
{
  //## begin RtemsMidiOutputDriver::TransmitMidiByte%1012952102.body preserve=yes
	// do some encoding with flags
	IOData iodata = MIDI_CHAN_1_DATA;

	// store the Flags
	if (output_num)
		{
			iodata = MIDI_CHAN_2_DATA;
		}

	// shift the flags to MSB
	iodata <<=8;

	// now store the data value
	iodata |= data;

	TransmitData(iodata);


  //## end RtemsMidiOutputDriver::TransmitMidiByte%1012952102.body
}

void RtemsMidiOutputDriver::TransmitCV (unsigned char data_val, int output_num)
{
  //## begin RtemsMidiOutputDriver::TransmitCV%1012952103.body preserve=yes
	// do some encoding with flags
	IOData iodata = 0;


	// store the Flags and channel
	iodata = output_num | ANALOG_DATA;

	// shift the data to MSB

	iodata <<=8;

	// now store the data value
	iodata |= data_val;

	TransmitData(iodata);

  //## end RtemsMidiOutputDriver::TransmitCV%1012952103.body
}

void RtemsMidiOutputDriver::TransmitDigital (unsigned char data_val, int output_num)
{
  //## begin RtemsMidiOutputDriver::TransmitDigital%1012952104.body preserve=yes
	// do some encoding with flags
	IOData iodata = 0;


	// store the Flags and channel
	iodata = output_num | DIGITAL_DATA;

	// shift the data to MSB

	iodata <<=8;

	// now store the data value
	iodata |= data_val;

	TransmitData(iodata);

  //## end RtemsMidiOutputDriver::TransmitDigital%1012952104.body
}

void RtemsMidiOutputDriver::TransmitData (IOData data)
{
  //## begin RtemsMidiOutputDriver::TransmitData%1012952110.body preserve=yes
	rtems_interrupt_level level;

	bool successful_transmit = true;
	const unsigned max_retries = 3;

	unsigned num_retries;
	// disable interrupts
	EnqueData(data);

	do
		{
			if (_tx_ready)
				{
					rtems_task_wake_after(1);

					rtems_interrupt_disable (level);
					if (_tx_ready) // check again as it is volaitile
						{
							successful_transmit = RtemsMidiDriver::WriteOutputReady(_device_num);
						}
					else
						{
							successful_transmit = true;
						}

					rtems_interrupt_enable (level);

					if (successful_transmit)
						{
							_tx_ready = false;
						}
				}
			else
				{
					successful_transmit = true; // if Tx Was not ready, we will leave
				}
			num_retries++;
		}
	while(!successful_transmit&& num_retries < max_retries);



  //## end RtemsMidiOutputDriver::TransmitData%1012952110.body
}

void RtemsMidiOutputDriver::TransmitIO (IOData data_val, int output_num)
{
  TransmitData (data_val);

  //## begin RtemsMidiOutputDriver::TransmitIO%1031946741.body preserve=yes
  //## end RtemsMidiOutputDriver::TransmitIO%1031946741.body
}

// Additional Declarations
  //## begin RtemsMidiOutputDriver%3C606BDA01EB.declarations preserve=yes
  //## end RtemsMidiOutputDriver%3C606BDA01EB.declarations

//## begin module%3C5F01310106.epilog preserve=yes
//## end module%3C5F01310106.epilog
