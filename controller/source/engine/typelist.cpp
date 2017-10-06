#include "stdafx.h"
#include <string.h>

#include "iodata.h"
#include "control.h"
#include "typenames.h"
#include "ostypes.h"
#include "midi.h"
#include "counter.h"
#include "messagestore.h"
#include "messagefilter.h"
#include "display.h"
#include "patch.h"
#include "stdmidiout.h"
#include "metro.h"
#include "switch.h"
#include "calculate.h"
#include "flipflop.h"
#include "delay.h"
#include "trigger.h"
#include "selector.h"
#include "toggle.h"
#include "stdmidiin.h"
#include "table.h"
#include "number.h"
#include "randomgen.h"
#include "sequencer.h"
#include "analogin.h"
#include "digitalin.h"
#include "analogout.h"
#include "digitalout.h"
#include "oscout.h"
#include "oscin.h"
#include "typelist.h"

TypeListElement::TypeListElement(const char* Name,
                                 pfnCreate Create)
  :TypeName(Name), pCreate(Create)
{
}


const TypeListElement TypeList::TypeElements [] =
{
  TypeListElement(PATCH_FILE_ID, Patch::CreatePatchFile),
  TypeListElement(Patch::szType, Patch::Create),
  TypeListElement(AnalogIn::szType, AnalogIn::Create),
  TypeListElement(AnalogOut::szType, AnalogOut::Create),
  TypeListElement(DigitalIn::szType, DigitalIn::Create),
  TypeListElement(DigitalOut::szType, DigitalOut::Create),
  TypeListElement(Counter::szType, Counter::Create),
  TypeListElement(Calculate::szType, Calculate::Create),
  TypeListElement(MessageStore::szType, MessageStore::Create),
  TypeListElement(MessageFilter::szType, MessageFilter::Create),  
  TypeListElement(SwitchInlets::szType, SwitchInlets::Create),
  TypeListElement(SwitchOutlets::szType, SwitchOutlets::Create),
  TypeListElement(StdMidiOut::szType, StdMidiOut::Create),
  TypeListElement(StdMidiIn::szType, StdMidiIn::Create),
  TypeListElement(Display::szType, Display::Create),
  TypeListElement(Metro::szType, Metro::Create),
  TypeListElement(Delay::szType, Delay::Create),
  TypeListElement(FlipFlop::szType, FlipFlop::Create),
  TypeListElement(Trigger::szType, Trigger::Create),
  TypeListElement(Selector::szType, Selector::Create),
  TypeListElement(Toggle::szType, Toggle::Create),
  TypeListElement(PatchOutletPort::szType, Patch::AddOutletPort),
  TypeListElement(PatchInletPort::szType, Patch::AddInletPort),
  TypeListElement(Table::szType, Table::Create),
  TypeListElement(NumberStore::szType, NumberStore::Create),
  TypeListElement(RandomGen::szType, RandomGen::Create),
  TypeListElement(Sequencer::szType, Sequencer::Create),
  TypeListElement(OscOut::szType, OscOut::Create),
  TypeListElement(OSCIn::szType, OSCIn::Create),    
  TypeListElement(NULL, NULL)

};


BaseShell* TypeList::Create(const char* szType , Patch* Parent)
{
  unsigned i = 0;
  BaseShell* ret = NULL;

  if (szType)
    {  
      do
      {
        if (!strcmp (TypeElements [i].TypeName, szType)) // The Same
          {
            ret = TypeElements[i].pCreate (Parent);
          /*
            if (ret)
              {
              printf ("Created %s \r\n", szType);
              }
            */
          }
        i++;
      }
      while (!ret && TypeElements [i].TypeName);
    }

  return ret;
};





const unsigned TypeList::NumElements = sizeof (TypeElements) / sizeof (TypeListElement) -1;

const char* TypeList::GetTypeName (unsigned Index)
{
  const char* ret = 0;

  if (Index < NumElements)
  {
    ret = TypeElements[Index].TypeName;
  }
  return ret;
}

bool TypeList::GetTypeName (unsigned Index, char* ret_val, unsigned buff_len)
{
  bool ret = false;

  if (Index < NumElements)
    {
      const char* type_name = TypeElements[Index].TypeName;
      if (type_name && buff_len > strlen(type_name))
	{
	  strcpy (ret_val, type_name);
	  ret = true;
	}
    }
  return ret;
}










