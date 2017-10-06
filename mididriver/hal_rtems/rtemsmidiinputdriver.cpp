//## begin module%3C5F00CA0018.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C5F00CA0018.cm

//## begin module%3C5F00CA0018.cp preserve=no
//## end module%3C5F00CA0018.cp

//## Module: RtemsMidiInputDriver%3C5F00CA0018; Package body
//## Subsystem: MidiDriver::hal_rtems%3C5F008D0309
//## Source file: D:\develop\SmartController\mididriver\hal_rtems\rtemsmidiinputdriver.cpp

//## begin module%3C5F00CA0018.additionalIncludes preserve=no
//## end module%3C5F00CA0018.additionalIncludes

//## begin module%3C5F00CA0018.includes preserve=yes
#include <stdafx.h>
#include <stddef.h>
#include <rtems.h>
#include "midiinputsync.h"
#include "rtemsmididriver.h"
#include "midiflags.h"

//## end module%3C5F00CA0018.includes

#include "midiinputdriver.h"
#include "analogueinputvalue.h"
#include "mididriver.h"


//## begin module%3C5F00CA0018.declarations preserve=no
//## end module%3C5F00CA0018.declarations

//## begin module%3C5F00CA0018.additionalDeclarations preserve=yes

//#define MODULE_DISPLAY_DEBUG
//## end module%3C5F00CA0018.additionalDeclarations


//## begin RtemsMidiInputDriver%3C606B640173.preface preserve=yes
//## end RtemsMidiInputDriver%3C606B640173.preface

//## Class: RtemsMidiInputDriver%3C606B640173
//## Category: MidiDriver::hal_rtems%3C606B4B0131
//## Subsystem: MidiDriver::hal_rtems%3C5F008D0309
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class RtemsMidiInputDriver : public MidiInputDriver  //## Inherits: <unnamed>%3F525DF60002
{
  //## begin RtemsMidiInputDriver%3C606B640173.initialDeclarations preserve=yes
  //## end RtemsMidiInputDriver%3C606B640173.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: RtemsMidiInputDriver%1012952105
      //	Constructor which defines queue size
      RtemsMidiInputDriver (int queue_size, MidiInputSync* driver);

    //## Destructor (generated)
      ~RtemsMidiInputDriver();


    //## Other Operations (specified)
      //## Operation: open%1012952106
      //	opens device
      bool open (int device_num, 	// The device number required by hardware. This value is
      	// the the device number in the hardware
      int device_id = -1	// Index that the device will be identified as the driver.
      	// -1 signifies that the device_num is used
      );

      //## Operation: close%1012952107
      //	closes device
      bool close ();

      //## Operation: DataReady%1012952108
      //	Function called by ISR when data is ready at input
      bool DataReady (IOData data);

      //## Operation: ReadData%1012952109
      //	Removes and retrieves item from Queue. Rteuns true if
      //	successful. Is abstract so each subclass can protect its
      //	critical sections
      bool ReadData (IOData* item);

    // Additional Public Declarations
      //## begin RtemsMidiInputDriver%3C606B640173.public preserve=yes
      //## end RtemsMidiInputDriver%3C606B640173.public

  protected:
    // Additional Protected Declarations
      //## begin RtemsMidiInputDriver%3C606B640173.protected preserve=yes
      //## end RtemsMidiInputDriver%3C606B640173.protected

  private:
    // Additional Private Declarations
      //## begin RtemsMidiInputDriver%3C606B640173.private preserve=yes
      //## end RtemsMidiInputDriver%3C606B640173.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin RtemsMidiInputDriver%3C606B640173.implementation preserve=yes
      //## end RtemsMidiInputDriver%3C606B640173.implementation

};

//## begin RtemsMidiInputDriver%3C606B640173.postscript preserve=yes
//## end RtemsMidiInputDriver%3C606B640173.postscript

// Class RtemsMidiInputDriver 

// Class MidiInputDriver 




MidiInputDriver::MidiInputDriver (int queue_size, MidiInputSync* driver)
  //## begin MidiInputDriver::MidiInputDriver%1012859309.hasinit preserve=no
      : pThread(driver)
  //## end MidiInputDriver::MidiInputDriver%1012859309.hasinit
  //## begin MidiInputDriver::MidiInputDriver%1012859309.initialization preserve=yes
  ,MidiDriver(queue_size)
  //## end MidiInputDriver::MidiInputDriver%1012859309.initialization
{
  //## begin MidiInputDriver::MidiInputDriver%1012859309.body preserve=yes
  for (int i = 0; i < 16; i++)
  {
    _ana_values[i].in_queue = false;
  }

  //## end MidiInputDriver::MidiInputDriver%1012859309.body
}


MidiInputDriver::~MidiInputDriver()
{
  //## begin MidiInputDriver::~MidiInputDriver%.body preserve=yes
  //## end MidiInputDriver::~MidiInputDriver%.body
}



//## Other Operations (implementation)
void MidiInputDriver::ProcessInputData ()
{
  if (pThread)
   pThread->resume();

  //## begin MidiInputDriver::ProcessInputData%1012451967.body preserve=yes
  //## end MidiInputDriver::ProcessInputData%1012451967.body
}

MidiInputDriver* MidiInputDriver::create (int queue_size, MidiInputSync* driver)
{
  //## begin MidiInputDriver::create%1012864642.body preserve=yes
	MidiInputDriver* pDriver = new RtemsMidiInputDriver(queue_size, driver);

  return pDriver;

  //## end MidiInputDriver::create%1012864642.body
}

void MidiInputDriver::ExtDataInput (IOData data)
{
  //## begin MidiInputDriver::ExtDataInput%1031953702.body preserve=yes
  //## end MidiInputDriver::ExtDataInput%1031953702.body
}

unsigned MidiInputDriver::NumDevices ()
{
  //## begin MidiInputDriver::NumDevices%1049869257.body preserve=yes
  //## end MidiInputDriver::NumDevices%1049869257.body
}

bool MidiInputDriver::GetDeviceName (unsigned index, char* ret_buf, unsigned buf_len)
{
  //## begin MidiInputDriver::GetDeviceName%1049869258.body preserve=yes
  //## end MidiInputDriver::GetDeviceName%1049869258.body
}

AnalogueInputValue& MidiInputDriver::GetAnalogValue (unsigned channel)
{
   return _ana_values[channel];

  //## begin MidiInputDriver::GetAnalogValue%1096433556.body preserve=yes
  //## end MidiInputDriver::GetAnalogValue%1096433556.body
}

// Additional Declarations
  //## begin MidiInputDriver%3C588B9601D9.declarations preserve=yes
  //## end MidiInputDriver%3C588B9601D9.declarations

// Class RtemsMidiInputDriver 

RtemsMidiInputDriver::RtemsMidiInputDriver (int queue_size, MidiInputSync* driver)
  //## begin RtemsMidiInputDriver::RtemsMidiInputDriver%1012952105.hasinit preserve=no
  //## end RtemsMidiInputDriver::RtemsMidiInputDriver%1012952105.hasinit
  //## begin RtemsMidiInputDriver::RtemsMidiInputDriver%1012952105.initialization preserve=yes
  :MidiInputDriver(queue_size, driver)
  //## end RtemsMidiInputDriver::RtemsMidiInputDriver%1012952105.initialization
{
  //## begin RtemsMidiInputDriver::RtemsMidiInputDriver%1012952105.body preserve=yes
  //## end RtemsMidiInputDriver::RtemsMidiInputDriver%1012952105.body
}


RtemsMidiInputDriver::~RtemsMidiInputDriver()
{
  //## begin RtemsMidiInputDriver::~RtemsMidiInputDriver%.body preserve=yes
  //## end RtemsMidiInputDriver::~RtemsMidiInputDriver%.body
}



//## Other Operations (implementation)
bool RtemsMidiInputDriver::open (int device_num, int device_id)
{
  //## begin RtemsMidiInputDriver::open%1012952106.body preserve=yes
	close();
	_device_num = device_num;

	return RtemsMidiDriver::AddInputDevice(device_num, this);
  //## end RtemsMidiInputDriver::open%1012952106.body
}

bool RtemsMidiInputDriver::close ()
{
  //## begin RtemsMidiInputDriver::close%1012952107.body preserve=yes

	return true;
  //## end RtemsMidiInputDriver::close%1012952107.body
}

bool RtemsMidiInputDriver::DataReady (IOData data)
{
  //## begin RtemsMidiInputDriver::DataReady%1012952108.body preserve=yes

	IOData iodata_type = (IOData) ((data & DATA_TYPE_MASK) >> 8);

	// if it is MIDI, process and get out
	if (iodata_type == MIDI_CHAN_1_DATA)
		{
			EnqueData (data);
			return true;
		}

	if (iodata_type == ANALOG_DATA)
    {
      //printf ("Analogue Data \r\n");

      unsigned channel = (data & DATA_PARAMS_MASK) >> 8;
      _ana_values[channel].upper_bits =  data;

      if (!_ana_values[channel].in_queue)
				{
        _ana_values[channel].in_queue = true;			
				EnqueData (data);
				return true;
				}
			
    }
    else if (iodata_type == ANALOG_LOWER_DATA)
    {
      unsigned channel = (data & DATA_PARAMS_MASK) >> 8;
      unsigned value = (data & DATA_VALUE_MASK);
      _ana_values[channel].lower_bits = value;
			//printf ("Lower %d\r\n", value);
    }

	else
    {
			EnqueData (data);
			return true;
    }
	
	return false;
  //## end RtemsMidiInputDriver::DataReady%1012952108.body
}

bool RtemsMidiInputDriver::ReadData (IOData* item)
{
  //## begin RtemsMidiInputDriver::ReadData%1012952109.body preserve=yes
  bool valid;

	//rtems_interrupt_level level;

	//rtems_interrupt_disable (level);

  valid = DequeData(item);

	//rtems_interrupt_enable (level);
  
  return valid;
 
  //## end RtemsMidiInputDriver::ReadData%1012952109.body
}

// Additional Declarations
  //## begin RtemsMidiInputDriver%3C606B640173.declarations preserve=yes
  //## end RtemsMidiInputDriver%3C606B640173.declarations

//## begin module%3C5F00CA0018.epilog preserve=yes
//## end module%3C5F00CA0018.epilog
