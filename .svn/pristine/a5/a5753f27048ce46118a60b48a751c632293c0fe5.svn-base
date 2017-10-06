#include "stdafx.h"
#include "control.h"

#include "typenames.h"
#include "messagefilter.h"
#include "eventmessagequeue.h"

#define NUM_INLETS  1
#define NUM_OUTLETS  3

#define TICK_OUTLET 0
#define NUMBER_OUTLET 1
#define STRING_OUTLET 2

const char*const MessageFilter::szInletDetails = "Input Message";
const char*const MessageFilter::szType = MESSAGEFILTER_TYPE;


// create the default
static MessageFilter *reference = new MessageFilter (NULL);

const BaseShell* MessageFilter::GetReference() const
{
	return reference;
}


MessageFilter::MessageFilter(Patch* Parent, const char* Name, const char* Comment)
    :BaseShell(Parent, NUM_INLETS, //NumInlets
		  NUM_OUTLETS, // NumOutlets
		  Name,	Comment)
{
}

const char*const MessageFilter::szaOutletDetails[NUM_OUTLETS] = {
  "Tick Out",
  "Number Out",
  "String Out"
};

const char* MessageFilter::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szInletDetails;
  else
    return NULL;
}

const char* MessageFilter::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}


BaseShell* MessageFilter::Create(Patch* Parent)
{  // get Name
  return new MessageFilter(Parent);
}

MessageFilter::~MessageFilter()
{
}


void MessageFilter::VoidInlet(unsigned InletNumber)
{
  tpOutlet[TICK_OUTLET]->ProduceOutput();  
  UNREFERENCED_PARAMETER (InletNumber);
}

void MessageFilter::IntInlet(unsigned InletNumber, int i)
{
  tpOutlet[NUMBER_OUTLET]->ProduceOutput(i);  
  UNREFERENCED_PARAMETER (InletNumber);
}

void MessageFilter::DoubleInlet(unsigned InletNumber, double d)
{
  tpOutlet[NUMBER_OUTLET]->ProduceOutput(d);  
  UNREFERENCED_PARAMETER (InletNumber);
}

void MessageFilter::StringInlet(unsigned InletNumber, const char* s)
{
	tpOutlet[STRING_OUTLET]->ProduceOutput(s);  
  UNREFERENCED_PARAMETER (InletNumber);
}




