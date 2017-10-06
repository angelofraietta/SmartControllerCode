//## begin module%3C6083590227.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C6083590227.cm

//## begin module%3C6083590227.cp preserve=no
//## end module%3C6083590227.cp

//## Module: RtemsMidiDriver%3C6083590227; Package body
//## Subsystem: MidiDriver::hal_rtems%3C5F008D0309
//## Source file: c:\develop\MidicontrollerPatchEditor\mididriver\hal_rtems\rtemsmididriver.cpp

//## begin module%3C6083590227.additionalIncludes preserve=no
//## end module%3C6083590227.additionalIncludes

//## begin module%3C6083590227.includes preserve=yes

#include <stddef.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <bsp.h>
#include <irq.h>
#include <rtems/libio.h>
extern "C" {
#include <uart.h>
}
#include <libcpu/cpuModel.h>


#include "midibsp.h"
#include "midiflags.h"

//## end module%3C6083590227.includes

#include "rtemsmididriver.h"
#include "midioutputdriver.h"
#include "midiinputdriver.h"


//## begin module%3C6083590227.declarations preserve=no
//## end module%3C6083590227.declarations

//## begin module%3C6083590227.additionalDeclarations preserve=yes

// define the irq addresses
#define BSP_IRQ_DATA_PORT0_IRQ ((rtems_irq_symbolic_name)10) 
#define BSP_IRQ_DATA_PORT1_IRQ ((rtems_irq_symbolic_name)12)
#define BSP_IRQ_DATA_PORT2_IRQ ((rtems_irq_symbolic_name)5)

#define BSP_IRQ_MIDI_PORT0_IRQ ((rtems_irq_symbolic_name)11) 
#define BSP_IRQ_MIDI_PORT1_IRQ ((rtems_irq_symbolic_name)9)
#define BSP_IRQ_MIDI_PORT2_IRQ ((rtems_irq_symbolic_name)15)

// define that our Midi Task will have event set as the Scheduler was freezing
//#define FORCE_POLL

//define MEMORY IO adresses
#define BSP_IO_BASE_PORT0 0x0230
#define BSP_IO_BASE_PORT1 0x0248
#define BSP_IO_BASE_PORT2 0x0250

/* Internal routines */
static void isr_on(const rtems_irq_connect_data *);
static void isr_off(const rtems_irq_connect_data *);
static int  isr_is_on(const rtems_irq_connect_data *);

// define the IO Addresses of the drivers
typedef struct
{
	short io_address;
	rtems_irq_symbolic_name irq;
	const char* name;
} str_midi_io_board;

// define data values to be stored for each driver
typedef struct
{
	IOData last_tx_message;
	unsigned num_rx_data_bytes;
	unsigned num_tx_data_bytes;
} str_driver_stats;

// define the IO board irq and address
str_midi_io_board BSP_COMM_PORT_ADDRESS [MAX_MIDI_DEVICES] = 
{
	{BSP_IO_BASE_PORT0, BSP_IRQ_DATA_PORT0_IRQ, "/dev/midi1"}, 
	{BSP_IO_BASE_PORT1,  BSP_IRQ_DATA_PORT1_IRQ, "/dev/midi2"},
	{BSP_IO_BASE_PORT2,  BSP_IRQ_DATA_PORT2_IRQ, "/dev/midi3"}
};

// define the connect data for the DATA port
rtems_irq_connect_data port_irq_connect_data [MAX_MIDI_DEVICES] = 
{
 
  {BSP_IRQ_DATA_PORT0_IRQ, RtemsMidiDriver::interrupt1, isr_on, isr_off, isr_is_on},
  {BSP_IRQ_DATA_PORT1_IRQ, RtemsMidiDriver::interrupt2, isr_on, isr_off, isr_is_on},
  {BSP_IRQ_DATA_PORT2_IRQ, RtemsMidiDriver::interrupt3, isr_on, isr_off, isr_is_on}
};

// define the connect data for the MIDI port
rtems_irq_connect_data port_irq_connect_midi [MAX_MIDI_DEVICES] = 
{
 
  {BSP_IRQ_MIDI_PORT0_IRQ, RtemsMidiDriver::midiinterrupt1, isr_on, isr_off, isr_is_on},
  {BSP_IRQ_MIDI_PORT1_IRQ, RtemsMidiDriver::midiinterrupt2, isr_on, isr_off, isr_is_on},
  {BSP_IRQ_MIDI_PORT2_IRQ, RtemsMidiDriver::midiinterrupt3, isr_on, isr_off, isr_is_on}
};

static str_driver_stats io_values [MAX_MIDI_DEVICES];

//#define MODULE_DISPLAY_DEBUG
//#define TEST_SEQUENCE

//#define SHOW_ALL_SEND
//#define SHOW_DIAG
//#define SHOW_RX_DATA

#ifdef TEST_SEQUENCE
unsigned short last_byte = 0;
unsigned byte_num = 0;
#endif

//## end module%3C6083590227.additionalDeclarations


// Class Utility RtemsMidiDriver 

//## begin RtemsMidiDriver::pMidiOut%3C607E74003B.role preserve=no  public: MidiOutputDriver { -> 0..nUFHN}
MidiOutputDriver*  RtemsMidiDriver::pMidiOut[MAX_MIDI_DEVICES];
//## end RtemsMidiDriver::pMidiOut%3C607E74003B.role

//## begin RtemsMidiDriver::pMidiIn%3C607E48025F.role preserve=no  public: MidiInputDriver { -> 0..nUFHN}
MidiInputDriver*  RtemsMidiDriver::pMidiIn[MAX_MIDI_DEVICES];
//## end RtemsMidiDriver::pMidiIn%3C607E48025F.role
 

//## Other Operations (implementation)
short RtemsMidiDriver::AddInputDevice (int device_num, MidiInputDriver* pDriver)
{
  //## begin RtemsMidiDriver::AddInputDevice%1012952111.body preserve=yes
#ifdef	MODULE_DISPLAY_DEBUG
	printf("RtemsMidiDriver::AddInputDevice %u", device_num);
#endif

	short ret = 0;
	rtems_interrupt_level level;
	// disable interrupts
	rtems_interrupt_disable (level);

	if (device_num < MAX_MIDI_DEVICES)
		{
			pMidiIn[device_num] = pDriver;
			ret = BSP_COMM_PORT_ADDRESS[device_num].io_address;
		}

	rtems_interrupt_enable (level);
	return ret;
  //## end RtemsMidiDriver::AddInputDevice%1012952111.body
}

short RtemsMidiDriver::AddOutputDevice (int device_num, MidiOutputDriver* pDriver)
{
  //## begin RtemsMidiDriver::AddOutputDevice%1012952112.body preserve=yes
	short ret = 0;
	rtems_interrupt_level level;
	// disable interrupts
	rtems_interrupt_disable (level);

	if (device_num < MAX_MIDI_DEVICES)
		{
			pMidiOut[device_num] = pDriver;
			ret = true;

		}
	rtems_interrupt_enable (level);
	return ret;

  //## end RtemsMidiDriver::AddOutputDevice%1012952112.body
}

bool RtemsMidiDriver::initialize (int device_number)
{
  //## begin RtemsMidiDriver::initialize%1012952113.body preserve=yes

  rtems_status_code status;
	const char* port_name = BSP_COMM_PORT_ADDRESS[device_number].name;

	for (unsigned i = 0; i  < MAX_MIDI_DEVICES; i++)
		{
			pMidiOut[i] = NULL;
			pMidiIn [i] = NULL;
		}

	outport_word (BSP_COMM_PORT_ADDRESS[device_number].io_address, DIAG_RESET);
	io_values[device_number].last_tx_message = TX_NO_DATA;
	io_values[device_number].num_rx_data_bytes = 0;
	io_values[device_number].num_tx_data_bytes = 0;


  if( !BSP_install_rtems_irq_handler( &(port_irq_connect_data[device_number]) ) )
  {
    printk("Error installing %s data interrupt handler!\n", port_name);
    rtems_fatal_error_occurred(status);
  }

  if( !BSP_install_rtems_irq_handler( &(port_irq_connect_midi[device_number]) ) )
  {
    printk("Error installing %s midi interrupt handler!\n", port_name);
    rtems_fatal_error_occurred(status);
  }



	io_values[device_number].num_rx_data_bytes = 0;
	io_values[device_number].num_tx_data_bytes = 0;

	return true;

  //## end RtemsMidiDriver::initialize%1012952113.body
}

inline void RtemsMidiDriver::interrupt (int dev_num)
{
  //## begin RtemsMidiDriver::interrupt%1012952114.body preserve=yes

#ifdef TEST_SEQUENCE
	unsigned short this_byte;
#endif

#ifdef	MODULE_DISPLAY_DEBUG
	char buf [8];
#endif

	short io_address = BSP_COMM_PORT_ADDRESS[dev_num].io_address;
	IOData io_in_data;
	IOData io_out_data = 0;

	inport_word (io_address, io_in_data);

	
	if (TX_DATA_MASK & io_in_data) // then we can proceed. Otherwise get out quickly
		{
			bool do_tx = true;

			// see if this is a diag message
			if ((io_in_data & DIAG_MESSAGE_MASK) == DIAG_MESSAGE_MASK)
				{
					if(pMidiOut[dev_num])
						{
							pMidiOut[dev_num]->SetTxReady(false);
						}

					switch (io_in_data)
						{
						case DIAG_INVALID_RX_DATA: // we got a bad message. Ask for it again
							do_tx = false;
#ifdef	SHOW_DIAG
							printf("Invalid Rx\r\n");
#endif 
							break; // case DIAG_INVALID_RX_DATA:


							
						case DIAG_ETX:
							if (pMidiOut[dev_num])
								{
									// now check the Transmit
									if (!pMidiOut[dev_num]->TxDataReady (&io_out_data))
										{
											// let the output driver know that we will be ready for a tx after this
											pMidiOut[dev_num]->SetTxReady(true);
											io_out_data = DIAG_ETX;
											
											// remove the reset number setting
											io_values[dev_num].last_tx_message = TX_NO_DATA;
											//io_values[dev_num].last_tx_message = DIAG_NO_DATA;
											//io_values[dev_num].num_tx_data_bytes = 0;
										}
									else
										{
											// there was data to tx so we will increment the number

											io_values[dev_num].num_tx_data_bytes++;
											// save this message in case we have to re-transmit it
											io_values[dev_num].last_tx_message = io_out_data;			
										}
									
								}
							else // no output device
								{
									io_out_data = DIAG_ETX;
									io_values[dev_num].last_tx_message = TX_NO_DATA;

									//io_values[dev_num].last_tx_message = DIAG_NO_DATA;
									//io_values[dev_num].num_tx_data_bytes = 0;
								}

							
							break; // case DIAG_ETX:

						case DIAG_REQUEST_RX_BYTES:
							io_out_data = DIAG_RETURN_RX_BYTES;
							io_out_data |= (io_values[dev_num].num_rx_data_bytes & DIAG_RETURN_BYTES_MASK);
#ifdef FORCE_POLL
							if (pMidiIn[dev_num])
							  {
							    pMidiIn[dev_num]->ProcessInputData ();
							  }
#endif

#ifdef	SHOW_DIAG
							printf ("Request num rx data. Received %u", (unsigned int)(io_values[dev_num].num_rx_data_bytes));
#endif 

							break;

						case DIAG_RE_TRANSMIT_LAST_MESSAGE: // the pic has lost sync
							io_out_data = io_values[dev_num].last_tx_message;
							/*
								removed during re-synchronisation of tx data 28 Feb 2003
							if ((io_out_data == DIAG_ETX) && (pMidiOut[dev_num]))
								{
									pMidiOut[dev_num]->SetTxReady(true);
								}
							*/
#ifdef TEST_SEQUENCE
							last_byte = io_in_data;
#endif // TEST_SEQUENCE
							
#ifdef  SHOW_DIAG
											printf("Retransmit %u\r\n", io_out_data);
#endif 
							
							break; // case DIAG_RE_TRANSMIT_LAST_MESSAGE:


						case DIAG_REQUEST_TX_BYTES:
							io_out_data = DIAG_RETURN_TX_BYTES;
							io_out_data |= (io_values[dev_num].num_tx_data_bytes & DIAG_RETURN_BYTES_MASK);
#ifdef	SHOW_DIAG
							printf("Request num tx data. Transmitted %u\r\n",(unsigned int)(io_values[dev_num].num_tx_data_bytes));
#endif 

							break;
							
						default:
							do_tx = false;
							
#ifdef	SHOW_DIAG
											printf ("Unknown Diag Message. Re-transmit %u\r\n", io_out_data);
#endif 
							
							
						} // end case

				}
			else // we have some receive data
				{ 
					io_values[dev_num].num_rx_data_bytes++;


#ifdef SHOW_RX_DATA
					char read_buf [8];
					sprintf (read_buf, "%04X", io_in_data);
					cout<<"Read "<<read_buf<<endl;
					
#endif 

					
#ifdef TEST_SEQUENCE
					// we are writing a sequence from 0x00 to 0xff
					byte_num++;
					this_byte = io_in_data;
					
					last_byte++;
					
					// compare the bytes except for first two bits
					if  ((this_byte & 0x7FFF) != (last_byte & 0x7FFF))
						{
							cout<<"Bytes missing. Byte Num "<<byte_num<<endl;
							
#ifdef	MODULE_DISPLAY_DEBUG
							sprintf (buf, "%04X", io_in_data);
							cout<<"Read "<<buf<<endl;
							sprintf (buf, "%04X", last_byte);
							cout<<"Expected "<<buf<<endl;
#endif   //MODULE_DISPLAY_DEBUG
							
						} //if  ((this_byte & 0x7FFF) != (last_byte & 0x7FFF))
					
					last_byte = this_byte;
					
#ifdef	MODULE_DISPLAY_DEBUG
					io_out_data = io_in_data +1;
#endif // MODULE_DISPLAY_DEBUG
					
			
					if (byte_num == 0xffff)
						{
							cout<<"Received "<< byte_num<< " Bytes"<<endl;
							byte_num = 0;
						}
					
#else // not TEST_SEQUENCE

#ifdef	MODULE_DISPLAY_DEBUG
					sprintf (buf, "%04X", io_in_data);
					cout<<"Read "<<buf<<endl;
					io_out_data = io_in_data +1;
#endif // MODULE_DISPLAY_DEBUG
					
					
#endif // TEST_SEQUENCE
					// we are out of all the debug stuff now
					
					
					if (pMidiIn[dev_num])
						{
							// we only need to do a process if the driver was empty
							bool process_required = pMidiIn[dev_num]->isEmpty(); //|| pMidiIn[dev_num]->IsLooping();
							
							process_required = process_required && pMidiIn[dev_num]->DataReady (io_in_data);
							
							if (process_required)
								{
									pMidiIn[dev_num]->ProcessInputData ();
								}
						}//if (pMidiIn[dev_num])	
					
					// now check the Transmit
					if (!(pMidiOut[dev_num] && pMidiOut[dev_num]->TxDataReady (&io_out_data)))
						{
							// Let the Pic know we have no more data but require a response
							io_out_data = DIAG_RECEIVE_RESPONSE;
						}
					else
						{
							// we are sending data so we will increment the count
							io_values[dev_num].num_tx_data_bytes++;
							// save this message in case we have to re-transmit it
							io_values[dev_num].last_tx_message = io_out_data;			
						}

				} // end received data
			

			if (do_tx)
				{
					outport_word (io_address, io_out_data);
					
#ifdef SHOW_ALL_SEND
					char buf [9];
					
					sprintf (buf, "%04X", io_out_data);
			
					cout<<"send "<<buf<<endl;
#endif // Show all Send
				}
		}
  //## end RtemsMidiDriver::interrupt%1012952114.body
}

void RtemsMidiDriver::interrupt1 ()
{
  //## begin RtemsMidiDriver::interrupt1%1012952117.body preserve=yes
	interrupt (0);
  //## end RtemsMidiDriver::interrupt1%1012952117.body
}

void RtemsMidiDriver::interrupt2 ()
{
  //## begin RtemsMidiDriver::interrupt2%1012952118.body preserve=yes
	interrupt (1);
  //## end RtemsMidiDriver::interrupt2%1012952118.body
}

void RtemsMidiDriver::interrupt3 ()
{
  //## begin RtemsMidiDriver::interrupt3%1012952119.body preserve=yes
	interrupt (2);
  //## end RtemsMidiDriver::interrupt3%1012952119.body
}

bool RtemsMidiDriver::WriteOutputReady (int device_num)
{
  //## begin RtemsMidiDriver::WriteOutputReady%1013139105.body preserve=yes
	bool ret = false;

	// this message is called in the context of a task
	short io_address = BSP_COMM_PORT_ADDRESS[device_num].io_address;
	IOData io_in_data;

	inport_word (io_address, io_in_data);

	if (TX_DATA_MASK & io_in_data) // then we can proceed. Otherwise get out quickly
		{
			outport_word (io_address, DIAG_ASYNC_MESSAGE_READY);
			
			// we write the Sync message because this is the value that represents this event if called within an ISR
			pMidiOut[device_num]->SetTxReady(false);

			ret = true;

#ifdef SHOW_ALL_SEND
			char buf [9];
			
			sprintf (buf, "%04X", DIAG_MESSAGE_READY);
	
			cout<<"WriteOutput send "<<buf<<endl;
#endif
		}
	return ret;

  //## end RtemsMidiDriver::WriteOutputReady%1013139105.body
}

bool RtemsMidiDriver::OutputPlaStatus (int device_num)
{
  //## begin RtemsMidiDriver::OutputPlaStatus%1018482874.body preserve=yes

	IOData io_in_data;
	short io_address = BSP_COMM_PORT_ADDRESS[device_num].io_address;

	inport_word (io_address, io_in_data);

	return (TX_DATA_MASK & io_in_data);

  //## end RtemsMidiDriver::OutputPlaStatus%1018482874.body
}

inline void RtemsMidiDriver::midiinterrupt (int dev_num)
{
  //## begin RtemsMidiDriver::midiinterrupt%1024352805.body preserve=yes

	short io_address = BSP_COMM_PORT_ADDRESS[dev_num].io_address;
	unsigned char io_in_data;
	IOData io_out_data = DIAG_RE_TRANSMIT_LAST_MESSAGE;

	inport_byte (io_address, io_in_data);
	
	// all messages must be Midi. 0xff will not be accepted and must be passed through other interrupt
	if (io_in_data != 0xFF)
		{
			if(pMidiOut[dev_num])
				{
					pMidiOut[dev_num]->SetTxReady(false);
				}

			// we have a receive byte
			io_values[dev_num].num_rx_data_bytes++;

#ifdef SHOW_RX_DATA
			char read_buf [8];
			sprintf (read_buf, "%02X", io_in_data);
			cout<<"Midi Interrupt Read "<<read_buf<<endl;
			
#endif 
			if (pMidiIn[dev_num])
				{
					// we only need to do a process if the driver was empty
					bool process_required = pMidiIn[dev_num]->isEmpty(); //|| pMidiIn[dev_num]->IsLooping();
					
					pMidiIn[dev_num]->DataReady (io_in_data | MIDI_CHAN_1_DATA); // thgis must be a midi message
							
					if (process_required)
						{
							pMidiIn[dev_num]->ProcessInputData ();
						}
				}//if (pMidiIn[dev_num])	
			
			// we will not check for tx data
			io_out_data = DIAG_RECEIVE_RESPONSE;

			outport_word (io_address, io_out_data);
			
#ifdef SHOW_ALL_SEND
			char buf [9];
			
			sprintf (buf, "%04X", io_out_data);
			
			cout<<"send "<<buf<<endl;
#endif // Show all Send
			
		} // end received data
			
	

  //## end RtemsMidiDriver::midiinterrupt%1024352805.body
}

void RtemsMidiDriver::midiinterrupt1 ()
{
  //## begin RtemsMidiDriver::midiinterrupt1%1024352806.body preserve=yes
	midiinterrupt (0);
  //## end RtemsMidiDriver::midiinterrupt1%1024352806.body
}

void RtemsMidiDriver::midiinterrupt2 ()
{
  //## begin RtemsMidiDriver::midiinterrupt2%1024352807.body preserve=yes
	midiinterrupt (1);
  //## end RtemsMidiDriver::midiinterrupt2%1024352807.body
}

void RtemsMidiDriver::midiinterrupt3 ()
{
  //## begin RtemsMidiDriver::midiinterrupt3%1024352808.body preserve=yes
	midiinterrupt (2);
  //## end RtemsMidiDriver::midiinterrupt3%1024352808.body
}

// Additional Declarations
  //## begin RtemsMidiDriver%3C607DDD03E0.declarations preserve=yes

extern "C"
rtems_device_driver
midiport0_open(rtems_device_major_number major,
                rtems_device_minor_number minor,
                void                      *arg)
{
	printf ("MidiPort1 open");
  return RTEMS_SUCCESSFUL;
}



static void
isr_on(const rtems_irq_connect_data *unused)
{
  return;
}
						   
static void
isr_off(const rtems_irq_connect_data *unused)
{
  return;
}

static int
isr_is_on(const rtems_irq_connect_data *irq)
{
	printf ("isr_is_on");
  return 1;
}

extern "C"
rtems_device_driver
midiport0_initialize(rtems_device_major_number major,
                   rtems_device_minor_number minor,
                   void                      *arg)
{
  rtems_status_code status;
	const int device_num = 0;
	const char* port_name = BSP_COMM_PORT_ADDRESS[device_num].name;

	RtemsMidiDriver::initialize (device_num);

  /*
   * Register the device
   */

  status = rtems_io_register_name ((char*)port_name, major, 0);

  if (status != RTEMS_SUCCESSFUL)
  {
      printk("Error registering %s device!\n", port_name);
      rtems_fatal_error_occurred (status);
  }
  printk("Device: %s initialized.\n", port_name);
  return RTEMS_SUCCESSFUL;
} /* port 1 initialize */

extern "C"
rtems_device_driver
midiport1_initialize(rtems_device_major_number major,
                   rtems_device_minor_number minor,
                   void                      *arg)
{
  rtems_status_code status;
	const int device_num = 1;

	const char* port_name = BSP_COMM_PORT_ADDRESS[device_num].name;
	RtemsMidiDriver::initialize (device_num);

  /*
   * Register the device
   */
  status = rtems_io_register_name ((char*)port_name, major, 0);
  if (status != RTEMS_SUCCESSFUL)
  {
      printk("Error registering %s device!\n", port_name);
      rtems_fatal_error_occurred (status);
  }
  printk("Device: %s initialized.\n", port_name);
  return RTEMS_SUCCESSFUL;

} /* port 2 initialize */


extern "C"
rtems_device_driver
midiport2_initialize(rtems_device_major_number major,
                   rtems_device_minor_number minor,
                   void                      *arg)
{
  rtems_status_code status;
	const int device_num = 2;

	const char* port_name = BSP_COMM_PORT_ADDRESS[device_num].name;

	RtemsMidiDriver::initialize (device_num);

  /*
   * Register the device
   */

  status = rtems_io_register_name ((char*)port_name, major, 0);
  if (status != RTEMS_SUCCESSFUL)
  {
      printk("Error registering %s device!\n", port_name);
      rtems_fatal_error_occurred (status);
  }
  printk("Device: %s initialized.\n", port_name);
  return RTEMS_SUCCESSFUL;

} /* port 3 initialize */



  //## end RtemsMidiDriver%3C607DDD03E0.declarations
//## begin module%3C6083590227.epilog preserve=yes
//## end module%3C6083590227.epilog

