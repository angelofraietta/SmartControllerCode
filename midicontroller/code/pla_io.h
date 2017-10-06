#ifndef PLA_IO_H
#define PLA_IO_H


#define WRITE_TRIS_VAL 0xE0
#define READ_TRIS_VAL  0xd0 

void MessageRead(); //forward declaration of function

#define PLA_DATA_SIZE 2 // 2 bytes in a PLA transfer
#define VALID_DATA_VALUE 0 // bit that defines whether a read has a valid value

short tx_ready = true;
short message_received = false;
short awaiting_response = false;
short message_lost = false;
short midi_tx = false; // defines whether we send a mid or data irq

str_PLA_Data pla_out_data, pla_in_data, prev_pla_out;

#inline
void SavePlaMessage() // saves the Pla message in case we need to re-send it
{
  // store the old value
  prev_pla_out.flags = pla_out_data.flags;
  prev_pla_out.data = pla_out_data.data;
}

#inline
void WritePlaFlags()
{
  if (bit_test (pla_out_data.flags, 7)) 
    {
      output_bit (SPI_PLA_DATA_OUT, 1);
    }
  else
    {
      output_bit (SPI_PLA_DATA_OUT, 0);
    }

  // now clock register
  output_high (PLA_CLK);
  
  output_low (PLA_CLK);
} // end WritePlaFlags

#inline
void WritePlaData()
{
	if (bit_test (pla_out_data.data, 7)) 
    {
      output_bit (SPI_PLA_DATA_OUT, 1);
    }
	else
		{
			output_bit (SPI_PLA_DATA_OUT, 0);
    }
	

	
	// now clock register
	output_high (PLA_CLK);
	
	output_low (PLA_CLK);
} // end WritePlaData

#inline 
void ReadPlaFlags()
{
	// read the input
	if (input (SPI_PLA_DATA_IN))
		{
			pla_in_data.flags |= 0x01;
		}
	
	// now clock register
	output_high (PLA_CLK);
	
	output_low (PLA_CLK);
					
} // end ReadPlaFlags;

#inline 
void ReadPlaData()
{
	if (input (SPI_PLA_DATA_IN))
		{
			pla_in_data.data |= 0x01;
		}
	
	// now clock register
	output_high (PLA_CLK);
	
	output_low (PLA_CLK);
					
} // end ReadPlaData

#inline
short PlaTxReady()
{
  return tx_ready;
}

#inline MessageWaiting()
{
  return message_received;
}

#int_ext
ProcessInterrupt()
{
  output_low(IO_INTERUPT_OUT_DATA); // by removing this we may just prevent the PC from reading an interrupt we just sent
  output_low(IO_INTERUPT_OUT_MIDI); // by removing this we may just prevent the PC from reading an interrupt we just sent
  message_received = true;
  tx_ready = true;
  message_lost = false;

}


/********************************************************************
 writes 16 bit word to pla
*********************************************************************/


#inline
void Pla_write_data ()
{
#use fast_io(d)
  // prepare Direction
  set_tris_d (WRITE_TRIS_VAL);

  output_low (PLA_CLK);
  output_high(SPI_PLA_DATA_DIR);

  // set the MSB to a one so we can stop the shifting in the pla
  bit_set (pla_out_data.flags, 7);

  WritePlaFlags();
  pla_out_data.flags<<=1;
  WritePlaFlags();
  pla_out_data.flags<<=1;
  WritePlaFlags();
  pla_out_data.flags<<=1;
  WritePlaFlags();
  pla_out_data.flags<<=1;
  WritePlaFlags();
  pla_out_data.flags<<=1;
  WritePlaFlags();
  pla_out_data.flags<<=1;
  WritePlaFlags();
  pla_out_data.flags<<=1;
  WritePlaFlags();



  // now write the data byte
  WritePlaData();
  pla_out_data.data<<=1;
  WritePlaData();
  pla_out_data.data<<=1;
  WritePlaData();
  pla_out_data.data<<=1;
  WritePlaData();
  pla_out_data.data<<=1;
  WritePlaData();
  pla_out_data.data<<=1;
  WritePlaData();
  pla_out_data.data<<=1;
  WritePlaData();
  pla_out_data.data<<=1;
  WritePlaData();
  
  
  set_tris_d (READ_TRIS_VAL);
}

/*************************************************************************
Reads 16 bit word plus test bit from PLA. Returns true if test bit is valid
ret_data contains returned data
*************************************************************************/

#inline
void Pla_read_data ()
{
	int byte_num;
	int bit_num;
	short data_val;
#use fast_io(d)

  message_received = false; // clear flag as there is no longer a message available
	// prepare clock

  set_tris_d (READ_TRIS_VAL);

	output_low (SPI_CLOCK);
	pla_in_data.flags = 0;
	pla_in_data.data = 0;

  // prepare for read
	output_low(SPI_PLA_DATA_DIR);

	ReadPlaFlags();	
	pla_in_data.flags <<= 1; 
	ReadPlaFlags();	
	pla_in_data.flags <<= 1; 
	ReadPlaFlags();	
	pla_in_data.flags <<= 1; 
	ReadPlaFlags();	
	pla_in_data.flags <<= 1; 
	ReadPlaFlags();	
	pla_in_data.flags <<= 1; 
	ReadPlaFlags();	
	pla_in_data.flags <<= 1; 
	ReadPlaFlags();	
	pla_in_data.flags <<= 1; 
	ReadPlaFlags();	


	ReadPlaData();
	pla_in_data.data <<= 1; 
	ReadPlaData();
	pla_in_data.data <<= 1; 
	ReadPlaData();
	pla_in_data.data <<= 1; 
	ReadPlaData();
	pla_in_data.data <<= 1; 
	ReadPlaData();
	pla_in_data.data <<= 1; 
	ReadPlaData();
	pla_in_data.data <<= 1; 
	ReadPlaData();
	pla_in_data.data <<= 1; 
	ReadPlaData();


  // make PLA Data Dir Write
  output_high(SPI_PLA_DATA_DIR);

}



void Pla_Send_data () //(int* out_data)
{
#use fast_io(e)  
#use fast_io(d)  
  
  tx_ready = false; // set flag that we are no longer ready to Transmit
  message_lost = false;


  output_low(IO_INTERUPT_OUT_DATA);
  output_low(IO_INTERUPT_OUT_MIDI);
  
  Pla_write_data();

  awaiting_response = true;  


  //enable_interrupts(GLOBAL);

  if (midi_tx)
    output_high(IO_INTERUPT_OUT_MIDI);
  else  
    output_high(IO_INTERUPT_OUT_DATA);

}


void InitialisePlaIn()
{
  message_received = false; // clear flag as there is no longer a message available
	output_low (SPI_CLOCK);

  Pla_read_data ();

  output_low(IO_INTERUPT_OUT_DATA); // PREPARE THE iNTERRUPT PIN
  output_low(IO_INTERUPT_OUT_MIDI); // PREPARE THE iNTERRUPT PIN

}

#endif




