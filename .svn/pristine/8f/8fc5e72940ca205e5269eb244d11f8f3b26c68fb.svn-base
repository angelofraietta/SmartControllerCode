/**************************************************************
 * Author: Angelo Fraietta
 * Description: Midi output interface
 *************************************************************/

#define PLA_OUT_QUEUE_SIZE  4

// forward declarations
void ProcessPlaInputStream();
short PlaOutFree();

typedef struct
{
  str_PLA_Data queue_data [PLA_OUT_QUEUE_SIZE];
  int  head :2; // the size is important as we just make the value 
  int  tail :2; // cycle from 0x0 to QUEUE_SIZE by incrementing
  int overflow :1;
  int empty :1;

} str_pla_queue;  


str_pla_queue pla_out_queue;


#inline 
short PlaOutQueueEmpty()
{
  return pla_out_queue.empty;
} // end PlaOutQueueEmpty

#inline 
short PlaOutQueueFull()
{
	return (!pla_out_queue.empty && pla_out_queue.tail == pla_out_queue.head);
} // end PlaOutQueueFull

#inline
void InitialisePlaOutQueue()
{
  pla_out_queue.tail = 0; 
  pla_out_queue.head = 0;
  pla_out_queue.overflow = false;
  pla_out_queue.empty = true;

} // end InitialiseOutQueue

#inline
void AddPlaQueue (byte flags, byte data)
{
	pla_out_queue.queue_data [pla_out_queue.tail].flags = flags;
	pla_out_queue.queue_data [pla_out_queue.tail].data = data;

	pla_out_queue.tail++;

	pla_out_queue.empty = false;
}  // end AddPlaQueue

#inline 
void GetPlaQueue ()
{
  pla_out_data.flags = pla_out_queue.queue_data [pla_out_queue.head].flags; 
  pla_out_data.data = pla_out_queue.queue_data [pla_out_queue.head].data; 

  pla_out_queue.head++;

  if (pla_out_queue.tail == pla_out_queue.head)
    {
      pla_out_queue.empty = true;
    }
} // end GetPlaQueue


#inline
short OutputPla (int flags, int value)
{
	short ret = false;

	if  (!PlaOutQueueFull ())
		{
			AddPlaQueue (flags, value);
			ProcessPlaInputStream();
			ret = true;
		}

	return ret;
}


#inline
short OutputAnalog (int channel, int value)
{
  int flags = 0;

  flags = (ANALOG_DATA | channel);

  return OutputPla (flags, value);
}

#inline
short OutputDigital (int channel, int value)
{
  int flags = 0;
  flags = (DIGITAL_DATA | channel);
  return OutputPla (flags, value);

}























