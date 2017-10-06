#include <windows.h>
#include <stdafx.h>
#include "midioutputdriver.h"
#include "midiinputdriver.h"
#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include "midiinputsync.h"


#include "equeue.h"

sm_str::e_static_queue <unsigned char> rxq (120);

#define BIG_SYSEX_BUF_SIZE 1024

const char SysexBuf[] = {0xf0, 0x7d, 0x01, 0x01, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x03,  0xF7};
char big_sysexBuf [BIG_SYSEX_BUF_SIZE];
const char* sysex_filename = "test.dat";

void InitBigSysexBuf()
{
	big_sysexBuf [0] = 0xf0;

  for(unsigned i = 1; i < BIG_SYSEX_BUF_SIZE - 1; i++)
  {
   	big_sysexBuf [i] = 0;
  }

  big_sysexBuf [BIG_SYSEX_BUF_SIZE -1] =  0xF7;

}

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
  	cout<<(unsigned)(iodata & 0xff)<<endl;
    //rxq.push((unsigned char) iodata & 0xff);

    data_valid = ReadData(&iodata);
  }


}

void main()
{
   MidiOutputDriver* pDriver = MidiOutputDriver::create (1024);
   MidiInDriver* pMidiIn = new MidiInDriver (1024);

   InitBigSysexBuf();

   if (!pMidiIn->open(0))
   {
   	 cout<<"Unable to open Midi In"<<endl;
   }

   pMidiIn->start();
		//cout<< "Press x to exit"<<endl;

    if (pDriver->open(1))
    {

    	for (unsigned j = 0; j < 25; j++)
      	{
        FILE* fp;

        fp = fopen (sysex_filename, "r+b");

        if (fp)
        {
        	BYTE read_buf [256];

        	unsigned bytes_read = fread (read_buf, 1, 256, fp);

          while (bytes_read)
          {
						for (unsigned i = 0; i < bytes_read; i++)
            {
            	BYTE b = read_buf[i];
							pDriver->TransmitMidiMessageByte (b ,0, 1);
              cout <<"TX "<<bytes_read<<endl;
            }

          	bytes_read = fread (read_buf, 1, 256, fp);
          }

        	fclose (fp);
        }
        /*
        for(unsigned i = 0; i < sizeof (SysexBuf); i++)
          {
          pDriver->TransmitMidiMessageByte (SysexBuf[i] ,0, 1);
          }
        */
        cout<<"Tx Midi. Press a key to tx"<<endl;
        getch();

				}

		}
/*
    cout<<"press any key to write continuous Sysex"<<endl;
    getch();

    cout<<"Writing Continuous Sysex"<<endl;
    while (1)
    for (unsigned i = 0; i < BIG_SYSEX_BUF_SIZE; i++)
    {
    	pDriver->TransmitMidiMessageByte(big_sysexBuf[i], 0, 1);
    }
    */
    cout<<"press any key to finish"<<endl;
    Sleep (1000);
    getch();
    delete pDriver;
    delete pMidiIn;

    while (!rxq.empty())
    {
    	cout<<(int)rxq.top()<<endl;
      rxq.pop();
    }
		getch();

}