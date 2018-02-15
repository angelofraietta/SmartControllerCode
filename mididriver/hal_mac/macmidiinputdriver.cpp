//## begin module%3D6AB50500C8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D6AB50500C8.cm

//## begin module%3D6AB50500C8.cp preserve=no
//## end module%3D6AB50500C8.cp

//## Module: MacMidiInputDriver%3D6AB50500C8; Package body
//	Mac version of Midi Input Driver
//## Subsystem: MidiDriver::hal_mac%3D6AB4D80041
//## Source file: D:\develop\SmartController\mididriver\hal_mac\macmidiinputdriver.cpp

//## begin module%3D6AB50500C8.additionalIncludes preserve=no
//## end module%3D6AB50500C8.additionalIncludes

//## begin module%3D6AB50500C8.includes preserve=yes
#include <stddef.h>
#include "midiinputsync.h"
#include <CoreMIDI/MIDIServices.h>
#include <pthread.h>
#include "midiflags.h"
//## end module%3D6AB50500C8.includes

#include "midiinputdriver.h"
#include "analogueinputvalue.h"
#include "mididriver.h"


//## begin module%3D6AB50500C8.declarations preserve=no
//## end module%3D6AB50500C8.declarations

//## begin module%3D6AB50500C8.additionalDeclarations preserve=yes
static void	MIDIInputReadProc(const MIDIPacketList *pktlist, void *refCon, void *connRefCon);
static MidiInputDriver* def_midi_in = 0; // this pointer is for File IO only
//## end module%3D6AB50500C8.additionalDeclarations


//## begin MacMidiInputDriver%3D6AB8CF027C.preface preserve=yes
//## end MacMidiInputDriver%3D6AB8CF027C.preface

//## Class: MacMidiInputDriver%3D6AB8CF027C
//## Category: MidiDriver::hal_mac%3D6AB53A007E
//## Subsystem: MidiDriver::hal_mac%3D6AB4D80041
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class MacMidiInputDriver : public MidiInputDriver  //## Inherits: <unnamed>%3D6AB8DC03D9
{
  //## begin MacMidiInputDriver%3D6AB8CF027C.initialDeclarations preserve=yes
  //## end MacMidiInputDriver%3D6AB8CF027C.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: MacMidiInputDriver%1030404441
      MacMidiInputDriver (int queue_size, MidiInputSync* driver);

    //## Destructor (generated)
      ~MacMidiInputDriver();


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
      //## begin MacMidiInputDriver%3D6AB8CF027C.public preserve=yes
      //## end MacMidiInputDriver%3D6AB8CF027C.public

  protected:
    // Additional Protected Declarations
      //## begin MacMidiInputDriver%3D6AB8CF027C.protected preserve=yes
      //## end MacMidiInputDriver%3D6AB8CF027C.protected

  private:
    // Additional Private Declarations
      //## begin MacMidiInputDriver%3D6AB8CF027C.private preserve=yes
  MIDIClientRef client;
  MIDIPortRef inPort;
  pthread_mutex_t count_mutex;
      //## end MacMidiInputDriver%3D6AB8CF027C.private
  private: //## implementation
    // Additional Implementation Declarations
      //## begin MacMidiInputDriver%3D6AB8CF027C.implementation preserve=yes
      //## end MacMidiInputDriver%3D6AB8CF027C.implementation

};

//## begin MacMidiInputDriver%3D6AB8CF027C.postscript preserve=yes
//## end MacMidiInputDriver%3D6AB8CF027C.postscript

// Class MacMidiInputDriver 

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
	MidiInputDriver* pDriver = new MacMidiInputDriver (queue_size, driver);
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
	return MIDIGetNumberOfSources();
  //## end MidiInputDriver::NumDevices%1049869257.body
}

bool MidiInputDriver::GetDeviceName (unsigned index, char* ret_buf, unsigned buf_len)
{
  //## begin MidiInputDriver::GetDeviceName%1049869258.body preserve=yes
	bool ret = false;
	MIDIEndpointRef dev = MIDIGetSource(index);

	if (dev != 0) {
		char name[64];
		CFStringRef pname;
		MIDIObjectGetStringProperty(dev, kMIDIPropertyName, &pname);
		CFStringGetCString(pname, name, sizeof(name), 0);
		CFRelease(pname);
		strncpy(ret_buf, name, buf_len);
		ret_buf[buf_len - 1] = 0;
		ret = true;
	}
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

// Class MacMidiInputDriver 

MacMidiInputDriver::MacMidiInputDriver (int queue_size, MidiInputSync* driver)
  //## begin MacMidiInputDriver::MacMidiInputDriver%1030404441.hasinit preserve=no
  //## end MacMidiInputDriver::MacMidiInputDriver%1030404441.hasinit
  //## begin MacMidiInputDriver::MacMidiInputDriver%1030404441.initialization preserve=yes
  :MidiInputDriver (queue_size, driver), client(0), inPort(0)
  //## end MacMidiInputDriver::MacMidiInputDriver%1030404441.initialization
{
  //## begin MacMidiInputDriver::MacMidiInputDriver%1030404441.body preserve=yes
  pthread_mutex_init(&count_mutex, NULL);
  //## end MacMidiInputDriver::MacMidiInputDriver%1030404441.body
}


MacMidiInputDriver::~MacMidiInputDriver()
{
  //## begin MacMidiInputDriver::~MacMidiInputDriver%.body preserve=yes
  pthread_mutex_destroy(&count_mutex);
  //## end MacMidiInputDriver::~MacMidiInputDriver%.body
}



//## Other Operations (implementation)
bool MacMidiInputDriver::open (int device_num, int device_id)
{
  //## begin MacMidiInputDriver::open%1030414456.body preserve=yes
  bool ret = false;

	_device_num = device_num;
  // create client and ports
  MIDIClientCreate(CFSTR("MIDI Echo"), NULL, NULL, &client);
  
  MIDIInputPortCreate(client, CFSTR("Input port"), MIDIInputReadProc, (void*)this, &inPort);
  
  if (device_num <= MIDIGetNumberOfSources())
    {
      MIDIEndpointRef src = MIDIGetSource(device_num);
      MIDIPortConnectSource(inPort, src, this);
      ret = true;
    }

  return ret;
  //## end MacMidiInputDriver::open%1030414456.body
}

bool MacMidiInputDriver::close ()
{
  //## begin MacMidiInputDriver::close%1030414457.body preserve=yes
  return true;
  //## end MacMidiInputDriver::close%1030414457.body
}

bool MacMidiInputDriver::DataReady (IOData data)
{
  //## begin MacMidiInputDriver::DataReady%1030414458.body preserve=yes
  pthread_mutex_lock(&count_mutex);
  EnqueData (data);
  pthread_mutex_unlock(&count_mutex);
	return true;
  //## end MacMidiInputDriver::DataReady%1030414458.body
}

bool MacMidiInputDriver::ReadData (IOData* item)
{
  //## begin MacMidiInputDriver::ReadData%1030414459.body preserve=yes
  bool valid;

  pthread_mutex_lock(&count_mutex);

  valid = DequeData(item);

  pthread_mutex_unlock(&count_mutex);


  return valid;

  //## end MacMidiInputDriver::ReadData%1030414459.body
}

void MacMidiInputDriver::PostProcesData ()
{
  //## begin MacMidiInputDriver::PostProcesData%1030414460.body preserve=yes
  //## end MacMidiInputDriver::PostProcesData%1030414460.body
}

// Additional Declarations
  //## begin MacMidiInputDriver%3D6AB8CF027C.declarations preserve=yes
static void	MIDIInputReadProc(const MIDIPacketList *pktlist, void *refCon, void *connRefCon)
{
  MidiInputDriver* pDriver = (MidiInputDriver*) refCon;
  bool process_required = pDriver->isEmpty();
	
  MIDIPacket *packet = (MIDIPacket *)pktlist->packet;	// remove const (!)
  for (unsigned int j = 0; j < pktlist->numPackets; ++j) 
    {
      for (int i = 0; i < packet->length; ++i) 
				{
					IOData iodata;
					iodata = packet->data[i];
					pDriver->DataReady(iodata);
				}
      
      packet = MIDIPacketNext(packet);
			{
				pDriver->ProcessInputData();
			}
    }
}

  //## end MacMidiInputDriver%3D6AB8CF027C.declarations
//## begin module%3D6AB50500C8.epilog preserve=yes
//## end module%3D6AB50500C8.epilog
