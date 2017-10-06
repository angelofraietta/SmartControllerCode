#include "stdafx.h"
#include "control.h"

#include "typenames.h"
#include "trigger.h"
#include "eventmessagequeue.h"

const char*const Trigger::szInletDetails = "Input";
const char*const Trigger::szOutletDetails = "Trigger Output";
const char*const Trigger::szType = TRIGGER_TYPE;


// create the default
static Trigger *reference = new Trigger (NULL);

const BaseShell* Trigger::GetReference() const
{
	return reference;
}


const char* Trigger::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szInletDetails;
  else
    return NULL;
}

const char* Trigger::GetOutletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumOutlets())
    return szOutletDetails;
  else
    return NULL;
}


BaseShell* Trigger::Create(Patch* Parent)
{  // get Name
  return new Trigger(Parent);
}

Trigger::~Trigger()
{
}


void Trigger::EnableDisplay (bool add)
{
	if (add)
		{
			display_messages++;
		}
	else
		{
			if (display_messages)
				display_messages--;
		}
}

void Trigger::VoidInlet(unsigned InletNumber)
{
  Send();
  UNREFERENCED_PARAMETER (InletNumber);
}

void Trigger::IntInlet(unsigned InletNumber, int i)
{
  Send();
  UNREFERENCED_PARAMETER (InletNumber);
  UNREFERENCED_PARAMETER (i);
}

void Trigger::DoubleInlet(unsigned InletNumber, double d)
{
  Send();
  UNREFERENCED_PARAMETER (InletNumber);
  UNREFERENCED_PARAMETER (d);
}

void Trigger::StringInlet(unsigned InletNumber, const char* s)
{
  Send();
  UNREFERENCED_PARAMETER (InletNumber);
  UNREFERENCED_PARAMETER (s);
}


void Trigger::Send()
{
  tpOutlet[0]->ProduceOutput();
  if(display_messages)
    {
			EventMessageQueue::Trigger (this);
    }
}




