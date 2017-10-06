/******************************************************
* Author: A. Fraietta
* Description: Tests the Midi Input queue functions
* define TEST_QUEUEwhen testing queues on simulator
******************************************************/

#include "16f877.h"
#fuses HS, WDT, BROWNOUT, NOPUT, NOLVP
#use delay (clock = 10000000)

#define TEST_QUEUE

#include "midicfg.h"
#include "midiin.h"
#include "watchdog.h"
#include "decmidi.h"
#include "procmidi.h"


byte midi_in_char = 0;
int logic_error = false;
int success;

#ifdef TEST_QUEUE
main()
{
  int x;
  int queue_start; // this is the number that the queue head starts at when pushing into queue
  int y;
  
  InitialiseMidiInQueue();

  for (queue_start = 0; queue_start < MIDI_IN_QUEUE_SIZE; queue_start++)
  {
    // fill queue to max
    midi_in_char = 0;
    for (x = 0; x < MIDI_IN_QUEUE_SIZE; x++)
      {
      ProcessMidiIn (midi_in_char++);
      
      if (MidiQueueEmpty() || MidiInOverflow ())
        {
        // we have an error in our logic somewhere or there is some midi coming in from somewhere else
        logic_error = true;
        }
      
      }
  
     // one more should cause an overflow
     ProcessMidiIn (midi_in_char++);
  
      if (!MidiInOverflow ())
        {
        // we have an error in our logic somewhere or there is some midi coming in from somewhere else
        logic_error = true;
        }
  
      // now pull the lot off the queue
      midi_in_char = 0;
      while (!MidiQueueEmpty())
        {
          x = GetMidiInChar();
          if (x != midi_in_char)
            {
            // we have an error in our logic somewhere or there is some midi coming in from somewhere else
            logic_error = true;
            }
          
          midi_in_char++;
        }
  
      // now increment the start of the queue    
      InitialiseMidiInQueue();
      for (y = 0; y < queue_start; y++)
        {
        ProcessMidiIn (0);
        GetMidiInChar();
        }  
      }
  
    while (1)
      success = !logic_error; // set breakpoint here
    
      

}
    
#else // testing on hardware

main ()
{
  byte midi_char;

  InitialiseWatchdog ();
  InitialiseMidiInQueue();
  enable_interrupts(GLOBAL);
  while (1)
    {
    while (!MidiQueueEmpty())
      {
      // flash led for each non zero char
      midi_char = GetMidiInChar();
      if (midi_char)
        {
        FlashWatchdog (100);
        if (midi_char == 0xb1) // midi controller on channel 2
          {
          InitialiseMidiInQueue();
          }
        }
      restart_wdt();
      }  // end while queue not empty    
    
    if (MidiInOverflow ())
      {
      FlashWatchdog (200);
      
      }
    restart_wdt();
    } // end while 1
} // end main
  

#endif
