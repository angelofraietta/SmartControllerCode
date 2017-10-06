//## begin module%3CB613C5000E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CB613C5000E.cm

//## begin module%3CB613C5000E.cp preserve=no
//	Angelo Fraietta
//## end module%3CB613C5000E.cp

//## Module: EngineDataInput%3CB613C5000E; Pseudo Package body
//## Subsystem: engine%39F51CB901B8
//## Source file: D:\develop\smartcontroller\controller\source\engine\enginedatainput.cpp

//## begin module%3CB613C5000E.additionalIncludes preserve=no
//## end module%3CB613C5000E.additionalIncludes

//## begin module%3CB613C5000E.includes preserve=yes
#include "iodata.h"
#include "control.h"
#include "stdmidiin.h"
#include "typenames.h"
#include "ostypes.h"
#include "midiflags.h"
#include "midiutilities.h"
#include "analogin.h"
#include "digitalin.h"
#include "midioutputdriver.h"
#include <stdio.h>
//## end module%3CB613C5000E.includes

// scheduler
#include "scheduler.h"
// SysexDriver
#include "sysexdriver.h"
// EngineDataInput
#include "enginedatainput.h"
// NVRAMStore
#include "nvramstore.h"
//## begin module%3CB613C5000E.additionalDeclarations preserve=yes
using hal_include::Scheduler;

#define LOCK_WAIT_TIME 50000
//#define SHOW_ALL_RX
//#define SHOW_MIDI_RX
//#define SHOW_SYSEX_DEBUG

extern "C" void DisplayDiags(const char* message);
//## end module%3CB613C5000E.additionalDeclarations


// Class EngineDataInput 





//## Operation: EngineDataInput%1018564229
//	Constructor with Queue Size
EngineDataInput::EngineDataInput (unsigned queue_size)
  //## begin EngineDataInput::EngineDataInput%1018564229.hasinit preserve=no
      : _in_sysex(false), _midi_bytes_remaining(0), _sysexDriver(new SysexDriver)
  //## end EngineDataInput::EngineDataInput%1018564229.hasinit
  //## begin EngineDataInput::EngineDataInput%1018564229.initialization preserve=yes
  ,MidiInputSync(queue_size)
  //## end EngineDataInput::EngineDataInput%1018564229.initialization
{
  //## begin EngineDataInput::EngineDataInput%1018564229.body preserve=yes
  //## end EngineDataInput::EngineDataInput%1018564229.body
}


EngineDataInput::~EngineDataInput()
{
  //## begin EngineDataInput::~EngineDataInput%.body preserve=yes
  delete _sysexDriver;
  //## end EngineDataInput::~EngineDataInput%.body
}



//## Other Operations (implementation)
//## Operation: processMidiInput%1018564230
//	Function that process the Input Data
void EngineDataInput::processMidiInput ()
{
  IOData iodata;
  
    bool data_valid = ReadData(&iodata);
  
    while (data_valid)
    {


  //## begin EngineDataInput::processMidiInput%1018564230.body preserve=yes
     processData (iodata);
  //## end EngineDataInput::processMidiInput%1018564230.body

    data_valid = ReadData(&iodata);
    }
}

//## Operation: processMidiByte%1018564231
//	Returns true if we have to output the Current Midi
//	Message
bool EngineDataInput::processMidiByte (unsigned char data)
{
  //## begin EngineDataInput::processMidiByte%1018564231.body preserve=yes

  bool ret = false;
	IOData out_data;
  
  // test for status
  if (data & 0x80)
  {
    _current_message.status = data;


    switch (data & 0xff) // we have to add the 0xff because we have to have an int
    {
    	case SYSEX_START_STATUS:
      	_in_sysex = true;
        _midi_bytes_remaining = -1;

#ifdef SHOW_SYSEX_DEBUG
				cout<<"Resetting SysexDriver"<<endl;
#endif
				_sysexDriver->Reset();

				// disable other Analogue In
        //out_data = EEPROM_START * 0x100;
        //MidiOutputDriver::TransmitIoData (out_data);

      	break;

      case SYSEX_END_STATUS:
      	_midi_bytes_remaining = 0;
				//out_data = EEPROM_END * 0x100;
				//MidiOutputDriver::TransmitIoData (out_data);

      	break;

      default:
      	_midi_bytes_remaining = MidiUtilities::num_bytes(data) - 1;
    }
  }
  else // not a status byte
  {
  	int data_byte_num;

    if (!_in_sysex)
    {
    	if (!_midi_bytes_remaining) // then we are using running status
      {
      	data_byte_num = 1;
        _midi_bytes_remaining = MidiUtilities::num_bytes(_current_message.status) - 1;
      }
      else
      {
      	data_byte_num = MidiUtilities::num_bytes(_current_message.status) - _midi_bytes_remaining;
      }

     	switch (data_byte_num)
      {
      	case 1:
        	_current_message.data1 = data;
          break;
        case 2:
        	_current_message.data2 = data;
          break;

        default:
        	break;
        }

    }
    else // in sysex
    {
    	_sysexDriver->ProcessByte(char(data & 0xff));
    }

    _midi_bytes_remaining--;
  }


  // we are ready to transmit
  if(!_midi_bytes_remaining)
  {
  	if (_in_sysex)
    {
    	_in_sysex = false;
    }
    else
    {
    	ret = true;
		} // end !sysex
  }

  return ret;                      
  //## end EngineDataInput::processMidiByte%1018564231.body
}

//## Operation: AddAnalogueVal%1096227731
//	Add an Analogue Value to the Input Queue
//## Postconditions:
//	Causes the Inpute Event to Be fired
void EngineDataInput::AddAnalogueVal (unsigned channel, unsigned value)
{
  //## begin EngineDataInput::AddAnalogueVal%1096227731.body preserve=yes
  if (GetInputDriver ())                   
  {

    IOData upper_data = ANALOG_DATA_16;
    IOData lower_data = ANALOG_LOWER_DATA_16;
    IOData chan = (IOData)((channel << 8) & DATA_PARAMS_MASK);

    upper_data |=  chan;
    lower_data |=  chan;

    upper_data |=  (IOData)((value >>2) & DATA_VALUE_MASK);
    lower_data |=  (IOData)(value & 0x03); // only last two bytes

    // order is important
    GetInputDriver ()->ExtDataInput (lower_data);
    GetInputDriver ()->ExtDataInput (upper_data);
    //printf ("Ana In %04X %04X\r\n", upper_data, lower_data);
		processMidiInput();

  }

  //## end EngineDataInput::AddAnalogueVal%1096227731.body
}

//## Operation: AddDigitalVal%1096227732
//	Add a Digital Value to the Input Queue
//## Postconditions:
//	Causes the Inpute Event to Be fired
void EngineDataInput::AddDigitalVal (unsigned channel, bool value)
{
  //## begin EngineDataInput::AddDigitalVal%1096227732.body preserve=yes
  IOData data = DIGITAL_DATA << 8;
  IOData chan = (IOData) ((channel << 8) & DATA_PARAMS_MASK);
  data |=  chan;
  data |=  (IOData) (value & DATA_VALUE_MASK);
  processData (data);
  //## end EngineDataInput::AddDigitalVal%1096227732.body
}

//## Operation: processData%1096227734
//	Processes the data received from Queue
void EngineDataInput::processData (IOData iodata)
{
  //## begin EngineDataInput::processData%1096227734.body preserve=yes
	bool success = false;

			IOData iodata_type = (IOData) ((iodata & DATA_TYPE_MASK) >> 8);

      //printf ("processData %04X \r\n",  iodata);
			switch (iodata_type)
				{
				case  MIDI_CHAN_1_DATA:
#ifdef SHOW_MIDI_RX
					char buf [9];

					sprintf (buf, "%04X", iodata);

					cout<<"Received Midi"<<buf<<endl;
#endif // Show all Midi


					if (processMidiByte ((BYTE)iodata))
						{
							if (Scheduler::LockEngine(LOCK_WAIT_TIME))
								{
									StdMidiIn::ProcessMidi(GetDeviceNum(), &_current_message);
									Scheduler::UnlockEngine();
									success = true;
								}
						}
					break;

				case ANALOG_DATA:
					{
            unsigned channel = (iodata & DATA_PARAMS_MASK) >> 8;
            AnalogueInputValue& ana_ref = GetAnalogValue (channel);

						if (Scheduler::LockEngine(LOCK_WAIT_TIME))
							{
								ana_ref.in_queue = false;
                unsigned value = ana_ref.getAnaVal();

                //printf ("Anaval %u, \r\n", value);
								AnalogIn::ProcessInput(channel, value);
								Scheduler::UnlockEngine();
								success = true;
							}

					}
					break;

				case DIGITAL_DATA:
					{
						if (Scheduler::LockEngine(LOCK_WAIT_TIME))
							{
								unsigned channel = (iodata & DATA_PARAMS_MASK) >> 8;
								unsigned value = (iodata & DATA_VALUE_MASK);


								DigitalIn::ProcessInput(channel, value);
								Scheduler::UnlockEngine();
								success = true;
							}

					}
					break;

				case  EEPROM_DATA:
          NVRAMStore::ReceiveData (iodata);
					success = true;
				default:
      	break;
      }

#ifdef SHOW_ALL_RX
			char buf [9];

			sprintf (buf, "%04X", iodata);

			cout<<"Received "<<buf<<endl;
#endif // Show all Send
  
			if (!success)
				{
					DisplayDiags("Failed to Lock Engine");
				}
  //## end EngineDataInput::processData%1096227734.body
}

// Additional Declarations
  //## begin EngineDataInput%3CB613C5000E.declarations preserve=yes
  //## end EngineDataInput%3CB613C5000E.declarations

//## begin module%3CB613C5000E.epilog preserve=yes
//## end module%3CB613C5000E.epilog
