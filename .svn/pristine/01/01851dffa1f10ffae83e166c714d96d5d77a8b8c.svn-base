#include <rtems.h>
#include "activeobject.h"
#include "event.h"
#include "midiinputdriver.h"
#include "midioutputdriver.h"
#include "midiinputsync.h"
#include "rtemsmididriver.h"
#include "midiflags.h"

#include <stdio.h>
//#include <string>

#define TOGGLE_OUTPUT 0x30FF // when we receive a digital on on channel 0, we will toggle oure generate
#define TOGGLE_SPEED 0x31FF //  When We receive a Digital on on Channle 1, we will go flat out

#define FAST_SLEEP 1
#define SLOW_SLEEP 1000

#define SHOW_ALL


#ifdef SHOW_ALL
#define NUM_PAGES_TO_READ 8
#else
#define NUM_PAGES_TO_READ 1024
#endif

void Sleep (unsigned long sleep_time)
{
	rtems_task_wake_after(sleep_time); 
}
 



volatile bool produce_outputs = false;
volatile bool fast_speed = false;
volatile bool read_ready = true;
volatile bool write_ready = false;

volatile char tx_buf [NUM_PAGES_TO_READ * EEPROM_WRITE_PAGE_SIZE];
volatile char rx_buf [NUM_PAGES_TO_READ * EEPROM_WRITE_PAGE_SIZE];
volatile unsigned read_data_index;

void WaitForWrite()
{
	while (!write_ready)
		{
			//			cout<<"WaitForWrite"<<endl;
			Sleep(FAST_SLEEP);
			if (!write_ready)
				{
					IOData out_data;
					out_data = EEPROM_START_WRITE *  0x100;
					MidiOutputDriver::TransmitIoData (out_data);
				}
		}

	//cout<<"ExitWaitForWrite"<<endl;

}


bool CompareData(unsigned num_to_test)
{
	bool ret = true;

	for (unsigned i = 0; i < num_to_test && ret; i++)
		{
			ret &= tx_buf[i] == rx_buf [i];
			if (!ret)
				{
					if (i)
						{
							//cout<<"Byte "<< i-1 << ":"<<(int) tx_buf[i-1]<< " read " << (int)rx_buf[i-1]<<endl;
						}
					//cout<<"Byte "<< i << ":"<<(int) tx_buf[i]<< " read " << (int)rx_buf[i]<<endl;
				}
		}

	return ret;
}

void WaitForRead()
{
	//cout<<"WaitForRead"<<endl;
	
	while (!read_ready)
		{
			if (!read_ready)
				{
					Sleep(FAST_SLEEP);
				}
		}
	
	//cout<<"ExitWaitForRead"<<endl;
}

class MidiInDriver:public MidiInputSync
{
	public:
  	MidiInDriver (int queue_size) : MidiInputSync (queue_size), last_byte(0), num_bytes(0){}
    ~MidiInDriver() {Purge(); kill();}
    void processMidiInput();
private:
	char last_byte;
	unsigned num_bytes;

};


void MidiInDriver::processMidiInput()
{
	IOData iodata;


	bool data_valid = ReadData(&iodata);


  while (data_valid)
  {
		char buf [8];
		short data_val = (iodata & 0x7Fff);
		short flags = (iodata & 0x7F00);
		flags >>= 8;


#ifdef SHOW_ALL
		num_bytes++;		
		sprintf (buf, "%04X", data_val);
		
		//cout<<"Input Rx "<<buf<< " Byte num "<< num_bytes<<endl;
#endif

			switch (flags)
				{
				case EEPROM_WRITE_READY:
					write_ready = true;
					break;
			
				case EEPROM_END_READ:
					read_ready = true;
					break;

				case INT_EEPROM_DATA:
				case EEPROM_DATA:
					if (read_data_index < sizeof(rx_buf))
						{
							rx_buf [read_data_index] = (char) data_val;
							read_data_index++;
						}
					break;
				default:
					{
#ifndef SHOW_ALL
						num_bytes++;		
						sprintf (buf, "%04X", data_val);
						
						//cout<<"Input Rx "<<buf<< " Byte num "<< num_bytes<<endl;
#endif			
					}

					break;
				}

    data_valid = ReadData(&iodata);

  }


}

class TestThread:public ActiveObject
{
  public:
  TestThread (): _purge(false), pEvent(Event::create()){}
  ~TestThread (){Purge(); Sleep (100); kill(); delete pEvent;}
  void Go(){pEvent->Release();}
  void Purge();
  private:
  void run ();
  Event* pEvent;
  volatile bool _purge;

};


void TestThread::run()
{
	//cout<<"Thread::Run"<<endl;
  while (!Terminated() && !_purge)
  {
		//cout<<"Wait"<<endl;
		pEvent->Wait();

  	if (!_purge)
    {
	    //cout<<"TestThread:run"<<endl;
    }
  }
}

void TestThread::Purge()
{
	_purge = true;
	//cout<<"TestThread->Purge"<<endl;
  Go();
}

void WriteDataToEEprom (bool ascending)
{
	IOData out_data;
	unsigned char c;

	bool restart = true;
	unsigned tx_buff_index = 0;

	if (ascending)
		{
			c = 0x00;
		}
	else
		{
			c = 0xff;
		}
	
	// set address to zero
	out_data = EEPROM_INIT_ADDRESS * 0x100;
	MidiOutputDriver::TransmitIoData (out_data);

	// we will write NUM_PAGES_TO_READ pages
	while (tx_buff_index < NUM_PAGES_TO_READ * EEPROM_WRITE_PAGE_SIZE)
		{

			if  (restart)
				{
					write_ready = false;
					// request a write to memory
					out_data = EEPROM_START_WRITE *  0x100;
					MidiOutputDriver::TransmitIoData (out_data);
			
					// Wait for a response that we are allowed to write
					WaitForWrite(); // this loops
					restart = false;
				}
	
			out_data = EEPROM_DATA *  0x100;
			MidiOutputDriver::TransmitIoData ((out_data & 0xff00) | (c & 0xFF) );
			
			// store the value we sent
			tx_buf [tx_buff_index] = c;
			
			if (ascending)
				{
					c++;
				}
			else
				{
					c--;
					c = 'a';//(char) rand();
				}

			// we have not incremented yet so we will do it here
			tx_buff_index++;

			restart = (!(tx_buff_index % EEPROM_WRITE_PAGE_SIZE)) || (!(tx_buff_index % 93)); // 93 is any number really We jsut want to flush
			if (restart)
				{
					// complete the write
					out_data = EEPROM_END_WRITE *  0x100;
					MidiOutputDriver::TransmitIoData (out_data);
				}
		} 
			

} // end WriteDataToEEprom (bool ascending)


void ReadData()
{
	IOData out_data;

	read_data_index = 0;

	// reset eeprom
	out_data = EEPROM_INIT_ADDRESS * 0x100;
	MidiOutputDriver::TransmitIoData (out_data);

	// set to read block of data
	out_data = EEPROM_BLOCK_READ *  0x100;
	
	while (read_data_index < NUM_PAGES_TO_READ * EEPROM_WRITE_PAGE_SIZE)
		{
			read_ready = false;
			//cout <<"Read block of data"<<endl;
			MidiOutputDriver::TransmitIoData (out_data);

			WaitForRead(); //loops
		}

	// reset eeprom
	out_data = EEPROM_INIT_ADDRESS * 0x100;
	MidiOutputDriver::TransmitIoData (out_data);

} // end void ReadData()


bool PerformTest (bool ascending)
{
	IOData out_data;

	// get exclusive access
	out_data = EEPROM_START * 0x100;
	MidiOutputDriver::TransmitIoData (out_data);

	WriteDataToEEprom (ascending);
	ReadData();

	out_data = EEPROM_END * 0x100;
	MidiOutputDriver::TransmitIoData (out_data);

	return CompareData(NUM_PAGES_TO_READ * EEPROM_WRITE_PAGE_SIZE);
} // end PerformTest


bool TestIntEEprom()
{
	IOData out_data;

	// reset eeprom
	out_data = EEPROM_INIT_ADDRESS * 0x100;
	MidiOutputDriver::TransmitIoData (out_data);

	for (unsigned i = 0; i < EEPROM_INT_PAGE_SIZE; i++)
		{
			char c = 'a';//(char) rand();
			tx_buf [i] = c;
			out_data = INT_EEPROM_DATA *  0x100;
			MidiOutputDriver::TransmitIoData ((out_data & 0xff00) | (c & 0xFF) );
		}

	// now read them back
	read_data_index = 0;

	// reset address
	out_data = EEPROM_INIT_ADDRESS * 0x100;
	MidiOutputDriver::TransmitIoData (out_data);

	// request data
	out_data = INT_EEPROM_READ * 0x100;
	MidiOutputDriver::TransmitIoData (out_data);

	while (read_data_index < EEPROM_INT_PAGE_SIZE)
		{
			Sleep(FAST_SLEEP);
		}

	return CompareData (EEPROM_INT_PAGE_SIZE);
} // TestIntEEprom()


extern "C" void mainline ()
{
	IOData out_data;

	//std::string message;

   MidiInDriver* pMidiIn = new MidiInDriver (0x00010000);

   if (!pMidiIn->open(0))
   {
   	 //cout<<"Unable to open Midi In"<<endl;
   }

   pMidiIn->start();

	 MidiOutputDriver* outdriver = MidiOutputDriver::create (10240);

	 if (!outdriver)
		 {
			 //			 cout<<"Unable to create Midi Output Driver"<<endl;
		 }
	 else
		 {
			 if (!outdriver->open (0))
				 {
					 //					 cout<<"unable to open output device"<<endl;
				 }
			 else
				 {
					 //					 cout<<"Successful output device opened"<<endl;
				 }


			 bool dig_val = false;

			 // reset eeprom
			 out_data = EEPROM_INIT_ADDRESS * 0x100;
			 MidiOutputDriver::TransmitIoData (out_data);

			 //			 cout<<"Ascending"<<endl;
			 
			 if (PerformTest (true))
				 {
					 //					 cout<<"Ascending passed"<<endl;
					 if (PerformTest (false))
						 {
							 //message = "Passed";
							 //							 cout<<"Descending Passed"<<endl;
						 }
					 else
						 {
							 //message = "Failed";
							 //							 cout<<"Descending failed"<<endl;
						 }
				 }
			 else
				 {
					 //					 cout<<"Ascending failed"<<endl;
					 //message = "Failed";
				 }

			 int num_tested = read_data_index;

			 while (1)
				 {
					 //					 cout<<"Enter Loop"<<endl;
					 //					 cout<<message<< " after "<<num_tested<<" bytes"<<endl;

					 //					 cout<<"Internal EEPROM ";
					 /*
					 if (TestIntEEprom())
						 {
							// cout<<"Passed"<<endl;
						 }
					 else
						 {
							 //cout<<"Failed"<<endl;
						 }
					 */
					 unsigned char outval = 0;
					 unsigned sleep_period;

					 if(fast_speed)
						 {
							 sleep_period = FAST_SLEEP;
						 }
					 else
						 {
							 sleep_period = SLOW_SLEEP;
						 }

					 if (dig_val)
						 {
							 outval = 0xff;
						 }

					 dig_val = !dig_val;
					 /*
					 if (produce_outputs)
						 {
							 outdriver->TransmitDigitalVoltage(outval, 0);
							 outdriver->TransmitMidiMessageByte(0x90, 0);
							 outdriver->TransmitMidiMessageByte(0x3C, 0);
							 outdriver->TransmitMidiMessageByte(0x7F, 0);
						 }
					 */
					 rtems_task_wake_after (sleep_period);
				 }
		 }
}











