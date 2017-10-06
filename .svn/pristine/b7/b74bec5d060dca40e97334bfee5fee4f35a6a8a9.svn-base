/*
  Driver file to test Midi input and output
 */

#include <iostream.h>
#include "midioutputdriver.h"
#include "midiinputdriver.h"
#include "midiinputsync.h"
#include <CoreFoundation/CFRunLoop.h>

void SetSimDigitalOutput (unsigned channel, bool value){}
void SetSimAnalogueOutput (unsigned channel, unsigned value){}

class MidiInDriver:public MidiInputSync
{
	public:
  	MidiInDriver (int queue_size) : MidiInputSync (queue_size){}
    ~MidiInDriver() {Purge(); kill();}
    void processMidiInput();

};

void MidiInDriver::processMidiInput()
{
  IOData iodata;

  bool data_valid = ReadData(&iodata);

  while (data_valid)
  {
    //cout<<(unsigned)(iodata & 0xff)<<endl;
    //rxq.push((unsigned char) iodata & 0xff);
    MidiOutputDriver::TransmitMidiMessageByte ((unsigned char) iodata, 0);
    data_valid = ReadData(&iodata);
  }


}
 
int main()
{
  char c;

  MidiOutputDriver* pOutputDriver = MidiOutputDriver::create (1024);
  MidiInDriver* pMidiIn = new MidiInDriver (1024);
  
  if (!pMidiIn->open(0))
    {
      cout<<"Unable to open Midi In"<<endl;
    }
  
  pMidiIn->start();
  
  if (pOutputDriver->open(0))
    {
      cout<<"Midi Output opened"<<endl;
    }
  else
    {
      cout <<"Unable to open Midi Out"<<endl;
    }

  cout<<"Press <ctrl> c to exit"<<endl;  
  CFRunLoopRun();  
	
  return 0;
}
