/*************************************************************
* Author: Angelo Fraietta
* Description Process the reception of Input and output using a 
* sixteen byte queue
* Dependancy : calls ProcessMidiIn
*************************************************************/
#byte PIR1 = 0x0C
#byte TXREG = 0x19

// define a  volatile flag that becomes true when a char is received
// and is reset by external program
short input_unlocked; 
                   

#define QUEUE_SIZE  32

typedef struct
{
  byte queue_data [QUEUE_SIZE];

  int  head :5; // the size is important as we just make the value 
  int dummy :3;
  int  tail :5; // cycle from 0x0 to QUEUE_SIZE by incrementing
  int overflow :1;
  int empty :1;

} str_data_queue;  

str_data_queue in_queue;


// return true if flag was set when we cleared it
#inline 
short ClearRxFlag()
{
	short ret;

	ret = input_unlocked;
	input_unlocked = 0;
	return ret;
}

#inline 
short InQueueEmpty()
{
  return in_queue.empty;
}


#ifdef _USE_OUT_BUFFER
#inline 
short OutQueueEmpty()
{
  return out_queue.empty;
}
#endif

#inline 
short InOverflow()
{
  return in_queue.overflow;
}

#inline 
short InQueueFull()
{
	return (!in_queue.empty && in_queue.tail == in_queue.head);
}


#ifdef _USE_OUT_BUFFER
#inline 
short OutQueueFull()
{
	return (!out_queue.empty && out_queue.tail == out_queue.head);
}
#endif

#inline
void InitialiseQueue(str_data_queue& q)
{
  q.tail = 0; 
  q.head = 0;
  q.overflow = false;
  q.empty = true;

}


void InitialiseInQueue()
{
  disable_interrupts (INT_RDA); // disable any Midi in 
	InitialiseQueue (in_queue);
	input_unlocked = true;
  enable_interrupts (INT_RDA); // disable any Midi in  
}



// function called when adding function. Called by interrupt by input
#inline
void AddQueue (byte new_byte, str_data_queue& q)
{
	q.queue_data [q.tail] = new_byte;
	q.tail++;

	q.empty = false;

}  

#inline 
byte GetQueue (str_data_queue& q)
{
  byte ret;
  ret = q.queue_data [q.head]; 
  q.head++;

  if (q.tail == q.head)
    {
      q.empty = true;
    }
	return ret;
}

#inline
void ClearInQueueOverflow()
{
  in_queue.overflow = false;
}

#inline
void AddInQueue (byte new_byte)
{
	AddQueue (new_byte, in_queue);
}

#int_rda
DataReceived()
{
  int midi_char;
  midi_char = getc();
  if (InQueueFull())
		{
			in_queue.overflow = true;
		}
  else
    {	
    in_queue.queue_data [in_queue.tail] = midi_char;
	  in_queue.tail++;
    }


	in_queue.empty = false;

}


#inline 
void WriteOutData (byte out_byte)
{
#use rs232(baud=31250, xmit=MIDIOUT_1_PIN, rcv=MIDI_IN_PIN, ERRORS) 
#ifndef _SIMULATE
	putc (out_byte);
#endif

}

#inline
byte GetInChar()
{
  byte ret;
  
  disable_interrupts (INT_RDA); // disable any Midi in 

  ret = GetQueue (in_queue);
  
  enable_interrupts (INT_RDA); // re-enable Midi in 

  input_unlocked = true; // set flag

  return ret;
}





#inline 
void WriteOutData2 (byte out_byte)
{
#use rs232(baud=31250, xmit=MIDIOUT_2_PIN, rcv=MIDI_IN_PIN, ERRORS) 
  // we have to disable the interrupts here otherwise the data will become corrupted because it has no uart
  disable_interrupts(GLOBAL);
#ifndef _SIMULATE
	putc (out_byte);
#endif
  enable_interrupts(GLOBAL);
}


