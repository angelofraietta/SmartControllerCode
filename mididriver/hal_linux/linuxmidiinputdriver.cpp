//## begin module%3D6AB50500C8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D6AB50500C8.cm

//## begin module%3D6AB50500C8.cp preserve=no
//## end module%3D6AB50500C8.cp

//## Module: LinuxMidiInputDriver%3D6AB50500C8; Package body
//	Mac version of Midi Input Driver
//## Subsystem: MidiDriver::hal_mac%3D6AB4D80041
//## Source file: D:\develop\SmartController\mididriver\hal_mac\linuxMidiInputDriver.cpp

//## begin module%3D6AB50500C8.additionalIncludes preserve=no
//## end module%3D6AB50500C8.additionalIncludes

//## begin module%3D6AB50500C8.includes preserve=yes
#include <stddef.h>
#include "midiinputsync.h"
#include <pthread.h>
#include "midiflags.h"
//## end module%3D6AB50500C8.includes

#include "midiinputdriver.h"
#include "analogueinputvalue.h"
#include "mididriver.h"


//## begin module%3D6AB50500C8.declarations preserve=no
//## end module%3D6AB50500C8.declarations

//## begin module%3D6AB50500C8.additionalDeclarations preserve=yes

static MidiInputDriver* def_midi_in = 0; // this pointer is for File IO only
//## end module%3D6AB50500C8.additionalDeclarations


//## begin LinuxMidiInputDriver%3D6AB8CF027C.preface preserve=yes
//## end LinuxMidiInputDriver%3D6AB8CF027C.preface

//## Class: LinuxMidiInputDriver%3D6AB8CF027C
//## Category: MidiDriver::hal_mac%3D6AB53A007E
//## Subsystem: MidiDriver::hal_mac%3D6AB4D80041
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class LinuxMidiInputDriver : public MidiInputDriver  //## Inherits: <unnamed>%3D6AB8DC03D9
{
  //## begin LinuxMidiInputDriver%3D6AB8CF027C.initialDeclarations preserve=yes
  //## end LinuxMidiInputDriver%3D6AB8CF027C.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: LinuxMidiInputDriver%1030404441
      LinuxMidiInputDriver (int queue_size, MidiInputSync* driver);

    //## Destructor (generated)
      ~LinuxMidiInputDriver();


    //## Other Operations (specified)
      //## Operation: open%1030414456
      //	opens device
      bool open (int device_num, 	// The device number required by hardware. This value is
      	// the the device number in the hardware
      int device_id = -1	// Index that the device will be identified as the driver.
      	// -1 signifies that the device_num is used
      );

      //## Operation: close%1030414457
      //	closes device
      bool close ();

      //## Operation: DataReady%1030414458
      //	Function called by ISR when data is ready at input
      bool DataReady (IOData data);

      //## Operation: ReadData%1030414459
      //	Removes and retrieves item from Queue. Rteuns true if
      //	successful. Is abstract so each subclass can protect its
      //	critical sections
      bool ReadData (IOData* item);

      //## Operation: PostProcesData%1030414460
      //	Function for processing data within context of thread.
      //	Overloaded for specific hal implimenttaion
      virtual void PostProcesData ();

    // Additional Public Declarations
      //## begin LinuxMidiInputDriver%3D6AB8CF027C.public preserve=yes
      //## end LinuxMidiInputDriver%3D6AB8CF027C.public

  protected:
    // Additional Protected Declarations
      //## begin LinuxMidiInputDriver%3D6AB8CF027C.protected preserve=yes
      //## end LinuxMidiInputDriver%3D6AB8CF027C.protected

  private:
    // Additional Private Declarations
      //## begin LinuxMidiInputDriver%3D6AB8CF027C.private preserve=yes
  pthread_mutex_t count_mutex;
      //## end LinuxMidiInputDriver%3D6AB8CF027C.private
  private: //## implementation
    // Additional Implementation Declarations
      //## begin LinuxMidiInputDriver%3D6AB8CF027C.implementation preserve=yes
      //## end LinuxMidiInputDriver%3D6AB8CF027C.implementation

};

//## begin LinuxMidiInputDriver%3D6AB8CF027C.postscript preserve=yes
//## end LinuxMidiInputDriver%3D6AB8CF027C.postscript

// Class LinuxMidiInputDriver

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
	MidiInputDriver* pDriver = new LinuxMidiInputDriver (queue_size, driver);
  if (!def_midi_in)
  {
    def_midi_in = pDriver;
  }

  return pDriver;
  //## end MidiInputDriver::create%1012864642.body
}

void MidiInputDriver::ExtDataInput (IOData data)
{
  //## begin MidiInputDriver::ExtDataInput%1031953702.body preserve=yes
  if (def_midi_in)
  {
    IOData iodata_type = (IOData) ((data & DATA_TYPE_MASK));

    if (iodata_type == ANALOG_DATA_16)
    {
      //printf ("Analogue Data \r\n");
      unsigned channel = (data & DATA_PARAMS_MASK) >> 8;
      def_midi_in->_ana_values[channel].upper_bits =  data;

      if (!def_midi_in->_ana_values[channel].in_queue)
      {
        def_midi_in->_ana_values[channel].in_queue = true;
        def_midi_in->DataReady(data);
      }

    }
    else if (iodata_type == ANALOG_LOWER_DATA_16)
    {
      unsigned channel = (data & DATA_PARAMS_MASK) >> 8;
      //unsigned value = (data & DATA_VALUE_MASK);// we will let the getAnaVal stript the iodata type
      def_midi_in->_ana_values[channel].lower_bits = data;
    }
    else
    {
      def_midi_in->DataReady(data);
      def_midi_in->ProcessInputData();
    }
  }

  //## end MidiInputDriver::ExtDataInput%1031953702.body
}

unsigned MidiInputDriver::NumDevices ()
{
  //## begin MidiInputDriver::NumDevices%1049869257.body preserve=yes
	return 0;
  //## end MidiInputDriver::NumDevices%1049869257.body
}

bool MidiInputDriver::GetDeviceName (unsigned index, char* ret_buf, unsigned buf_len)
{
  //## begin MidiInputDriver::GetDeviceName%1049869258.body preserve=yes
	bool ret = false;
	return ret;

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

// Class LinuxMidiInputDriver

LinuxMidiInputDriver::LinuxMidiInputDriver (int queue_size, MidiInputSync* driver)
  //## begin LinuxMidiInputDriver::LinuxMidiInputDriver%1030404441.hasinit preserve=no
  //## end LinuxMidiInputDriver::LinuxMidiInputDriver%1030404441.hasinit
  //## begin LinuxMidiInputDriver::LinuxMidiInputDriver%1030404441.initialization preserve=yes
  :MidiInputDriver (queue_size, driver)
  //## end LinuxMidiInputDriver::LinuxMidiInputDriver%1030404441.initialization
{
  //## begin LinuxMidiInputDriver::LinuxMidiInputDriver%1030404441.body preserve=yes
  pthread_mutex_init(&count_mutex, NULL);
  //## end LinuxMidiInputDriver::LinuxMidiInputDriver%1030404441.body
}


LinuxMidiInputDriver::~LinuxMidiInputDriver()
{
  //## begin LinuxMidiInputDriver::~LinuxMidiInputDriver%.body preserve=yes
  pthread_mutex_destroy(&count_mutex);
  //## end LinuxMidiInputDriver::~LinuxMidiInputDriver%.body
}



//## Other Operations (implementation)
bool LinuxMidiInputDriver::open (int device_num, int device_id)
{
  //## begin LinuxMidiInputDriver::open%1030414456.body preserve=yes
  bool ret = false;

	_device_num = device_num;
  // create client and ports

  return ret;
  //## end LinuxMidiInputDriver::open%1030414456.body
}

bool LinuxMidiInputDriver::close ()
{
  //## begin LinuxMidiInputDriver::close%1030414457.body preserve=yes
  return true;
  //## end LinuxMidiInputDriver::close%1030414457.body
}

bool LinuxMidiInputDriver::DataReady (IOData data)
{
  //## begin LinuxMidiInputDriver::DataReady%1030414458.body preserve=yes
  pthread_mutex_lock(&count_mutex);
  EnqueData (data);
  pthread_mutex_unlock(&count_mutex);
	return true;
  //## end LinuxMidiInputDriver::DataReady%1030414458.body
}

bool LinuxMidiInputDriver::ReadData (IOData* item)
{
  //## begin LinuxMidiInputDriver::ReadData%1030414459.body preserve=yes
  bool valid;

  pthread_mutex_lock(&count_mutex);

  valid = DequeData(item);

  pthread_mutex_unlock(&count_mutex);


  return valid;

  //## end LinuxMidiInputDriver::ReadData%1030414459.body
}

void LinuxMidiInputDriver::PostProcesData ()
{
  //## begin LinuxMidiInputDriver::PostProcesData%1030414460.body preserve=yes
  //## end LinuxMidiInputDriver::PostProcesData%1030414460.body
}

//## begin module%3D6AB50500C8.epilog preserve=yes
//## end module%3D6AB50500C8.epilog
