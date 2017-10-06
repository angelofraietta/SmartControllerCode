//## begin module%3D6C167A0348.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D6C167A0348.cm

//## begin module%3D6C167A0348.cp preserve=no
//	Angelo Fraietta
//## end module%3D6C167A0348.cp

//## Module: MacSimulator%3D6C167A0348; Package body
//## Subsystem: hal_mac%3A80A6B0022E
//	This contains the implementation for the Macintosh
//	specific build.  These are used for the engine simulator
//	that will have to run within the Patch Editor.  These
//	modules are linked with the engine package.
//## Source file: c:\develop\WinSmartController\controller\source\hal_mac\macsimulator.cpp

//## begin module%3D6C167A0348.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3D6C167A0348.additionalIncludes

//## begin module%3D6C167A0348.includes preserve=yes
#include <stddef.h>
#include "iodata.h"
#include "scheduler.h"
#include "answertask.h"
#include "midioutputdriver.h"
#include "enginedatainput.h"
#include "control.h"
#include "patch.h"
#include "fileanswer.h"
#include "oscinput.h"
#include <vector>
#include <iostream>

#ifndef _HAL_WINDOWS
#include <unistd.h>
using std::cout;
using std::endl;

#endif


//## end module%3D6C167A0348.includes

// SimulatorInterface
#include "simulatorinterface.h"
// SessionInterface
#include "sessioninterface.h"
//## begin module%3D6C167A0348.declarations preserve=no
//## end module%3D6C167A0348.declarations

//## begin module%3D6C167A0348.additionalDeclarations preserve=yes
#define NUM_OUTPUTS 16

void maintask ();

extern "C" bool StartDiagTask();

std::vector<EngineDataInput*> MidiInDevs;
std::vector<MidiOutputDriver*> MidiOutDevs;
EngineDataInput* SimInput = NULL;

class Outputs {
  public:
    Outputs ()
    {
      for (unsigned i = 0; i < NUM_OUTPUTS; i++)
        {
          dig_outputs [i] = false;
          ana_outputs [i] = 0;
        }

    }

  bool dig_outputs [NUM_OUTPUTS];
  unsigned ana_outputs [NUM_OUTPUTS];
};

static Outputs outputs;

// define exported functions

extern "C"
{
void  OpenCommPorts ();
bool OpenMidiOutputDevice (unsigned device_num, unsigned device_index);
void  CloseMidiOutputDevices ();
void  SetDefaultDirectory (const char* dir_name);
bool  OpenMidiInputDevice (unsigned device_num, unsigned device_index);
void  CloseMidiInputDevices ();
bool  SimulatorGetAnswer (const BYTE* question, BYTE* ret_answer);
void  InitialiseEngine();
void  DeinitialiseEngine();
void  DeleteAllPatches();

void  AddAnalogueValue (unsigned channel, unsigned value);
void  AddDigitalValue(unsigned channel, unsigned value);
unsigned GetAnalogueValue (unsigned channel);
bool GetDigitalValue(unsigned channel);

}


//## end module%3D6C167A0348.additionalDeclarations


//## begin module%3D6C167A0348.epilog preserve=yes
#pragma export on

extern "C" void Restart(){}
extern "C" int fsync(int){return 0;}

static unsigned num_tx_blocks = 0;

extern "C"	const char* GetNVRAMFilename() {return 0;}
extern "C"	void SyncNVRAM(){}
extern "C" void  OpenCommPorts ()
{
  AnswerTask* answer_task_1 = new AnswerTask;
  answer_task_1->startTask ("COM2", 0);
/*
  AnswerTask* answer_task_2 = new AnswerTask;
  answer_task_2->startTask ("COM1", 0);
  */
}

extern "C"   unsigned GetNumMidiInDevices()
{
  return MidiInputDriver::NumDevices ();
}

extern "C"   unsigned GetNumMidiOutDevices()
{
  return MidiOutputDriver::NumDevices ();
}

extern "C"   bool GetMidiInputName (unsigned device_index, char* ret_buf, unsigned buf_len)
{
  return MidiInputDriver::GetDeviceName (device_index, ret_buf, buf_len);
}

extern "C"   bool GetMidiOutputName (unsigned device_index, char* ret_buf, unsigned buf_len)
{
  return MidiOutputDriver::GetDeviceName (device_index, ret_buf, buf_len);
}

extern "C"   unsigned long OpenSysexSendFile (const char* sysex_filename)
{
	num_tx_blocks = 0;
  return (unsigned long) fopen (sysex_filename, "r+b");
}

extern "C"   bool TransmitSysexData (unsigned long file_key, unsigned device_index, unsigned num_bytes)
{
	num_tx_blocks++;
  bool ret = false;
  if (device_index < MidiOutDevs.size ())
  {
    MidiOutputDriver* pDriver = MidiOutDevs [device_index];

    if (pDriver)
    {
      FILE* fp = (FILE*)file_key;

      if (fp)
      {
        ret = true;
        for (unsigned i = 0; i < num_bytes && ret; i++)
        {
          char c;
          ret = fread (&c, 1, 1, fp);
          if (ret)
          {
            pDriver->TransmitMidiMessageByte (c ,0, device_index);
          }
        }
        cout<<"Tx Block "<<num_tx_blocks<<endl;

      }
    }
  }
  return ret;
}

extern "C"   bool CloseSysexData (unsigned long file_key)
{
  bool ret = false;
  FILE* fp = (FILE*)file_key;

  if (fp)
  {
    fclose (fp);
    ret = true;
  }

  return ret;
}

extern "C" bool OpenMidiOutputDevice (unsigned device_num, unsigned device_index)
{
	bool ret = false;

  if (device_num < MidiOutputDriver::NumDevices ())
  {
  	MidiOutputDriver* pDriver = MidiOutputDriver::create (1024);

    if (pDriver)
    	{
      pDriver->open (device_num, device_index);
      MidiOutDevs.push_back(pDriver);
      ret = true;
      }
    else
    	{
      	printf("Unable to open device\r\n");
      	}


  }

  return ret;
}

extern "C" void  CloseMidiOutputDevices ()
{
	unsigned num_devs = MidiOutDevs.size();

	for (unsigned i = 0; i < num_devs; i++)
  {
  	delete MidiOutDevs[i];
    MidiOutDevs[i] = NULL;
  }

  MidiOutDevs.erase(MidiOutDevs.begin(), MidiOutDevs.end());
}

void CloseOSCPorts()
{
  OSCInput::closeall ();
}

extern "C" void  SetDefaultDirectory (const char* dir_name)
{
  FileAnswer::SetDefaultDirectory (dir_name);
	printf ("Set Default Directory %s\r\n", dir_name);
}

extern "C" bool GetDefaultDirectory (char* buf, unsigned buf_size)
{
  bool ret = false;
  const char* dir = FileAnswer::GetDefaultDirName();

  if (dir)
  {
    strncpy (buf, dir, buf_size);
    buf [buf_size -1] = 0; // make sure last is NULL;
    ret = true;
  }
  else
  {
    *buf = 0;
  }


  return ret;
}

extern "C" bool  OpenMidiInputDevice (unsigned device_num, unsigned device_index)
{
	bool ret = false;

	EngineDataInput* pMidiIn = new EngineDataInput (1024 * 8);

   	if (!pMidiIn->open(device_num, device_index))
   	{
   	 	printf("Unable to open Midi In");
   	 	delete pMidiIn;
   	}
    else
    {
			pMidiIn->start();
			printf ("Opened Midi In\r\n");

			MidiInDevs.push_back(pMidiIn);
      if (!SimInput) SimInput = pMidiIn;
			ret = true;
		}

  return ret;
}

extern "C" void  CloseMidiInputDevices ()
{
	unsigned num_devs = MidiInDevs.size();

	for (unsigned i = 0; i < num_devs; i++)
  {
	 	delete MidiInDevs[i];
  	MidiInDevs[i] = NULL;
  }

  MidiInDevs.erase(MidiInDevs.begin(), MidiInDevs.end());

  CloseOSCPorts();
}


extern "C" bool  SimulatorGetAnswer (const BYTE* question, BYTE* ret_answer)
{
	return SimulatorAnswer::GetAnswer (question, ret_answer);
}
 
extern "C" bool SimulatorInitialise()
{
  bool ret = StartDiagTask();

	return ret && hal_include::Scheduler::initialise ();
}


extern "C" void  InitialiseEngine()
{
	
  if (hal_include::Scheduler::initialise ())
		{
			printf("Successful InitialiseEngine\r\n");
		}
	else
		{
			printf("Unable to InitialiseEngine\r\n");
		}

  SetDefaultDirectory ("");

}

extern "C" bool SimulatorDeinitialise()
{
	return hal_include::Scheduler::deinitialise ();
}


extern "C" unsigned long GetSchedulerTime()
{
  return hal_include::Scheduler::getTime();
}

// deletes all Patches When Dll is being detached
extern "C" void  DeleteAllPatches()
{
		unsigned num_patches = Patch::NumPatches();

    if (num_patches)
    {
      for (unsigned i = num_patches; i != 0; i--)
      {
        Patch* pPatch = Patch::GetPatch (i -1);
        delete pPatch;
      }
		}
}

extern "C" void SaveFileToIde (const char* source_file, const char* target_file, unsigned long CRC) {}

extern "C" void  AddAnalogueValue (unsigned channel, unsigned value)
{
  if (!SimInput)
  {
    SimInput = new EngineDataInput (1024 * 8);
  }
  if (SimInput)
  {
    SimInput->AddAnalogueVal(channel, value);
  }

}

extern "C" void  AddDigitalValue(unsigned channel, unsigned value)
{
  if (!SimInput)
  {
    SimInput = new EngineDataInput (1024 * 8);
  }

  //printf ("Add Digital Sim %u %u\r\n", channel, value);
  if (SimInput)
  {
    SimInput->AddDigitalVal(channel, value);
  }

}

extern "C" unsigned GetAnalogueValue (unsigned channel)
{
  unsigned ret = 0;
  if (channel < NUM_OUTPUTS)
    ret = outputs.ana_outputs [channel];

  //printf ("Read Analogue Out %u %u\r\n", channel, ret);
  return ret;
}

extern "C" bool GetDigitalValue(unsigned channel)
{
  bool ret = false;
  if (channel < NUM_OUTPUTS)
    ret = outputs.dig_outputs [channel];

//   printf ("ReadDigital Out %u %u\r\n", channel, ret);
  return ret;
}

#pragma export off

void SetSimDigitalOutput (unsigned channel, bool value)
{
    if (channel < NUM_OUTPUTS)
      outputs.dig_outputs [channel] = value;

    //printf ("Write Digital Out %u %u\r\n", channel, value);
}

void SetSimAnalogueOutput (unsigned channel, unsigned value)
{
    if (channel < NUM_OUTPUTS)
      outputs.ana_outputs [channel] = value;

    //printf ("Write Analogue Out %u %u\r\n", channel, value);
}

//## end module%3D6C167A0348.epilog
