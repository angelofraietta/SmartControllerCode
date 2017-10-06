//DigitalIn function defs
#include "stdafx.h"

#include "iodata.h"
#include "control.h"
#include "digitalin.h"
#include "typenames.h"
#include "ostypes.h"

#define NUM_INLETS 1
#define NUM_OUTLETS 2

#define VALUE_OUTLET 1
#define CHANNEL_OUTLET 0

//static variables

DigitalIn** DigitalIn::ObjectsList = NULL;
unsigned DigitalIn::ListSize = 0;

const unsigned DigitalIn::NumAccess = DigitalIn::eMaxAttribute;
const unsigned DigitalIn::NumResetAccess = DigitalIn::eMaxResetAttribute;


// create the default
static DigitalIn *reference = new DigitalIn (NULL);

const BaseShell* DigitalIn::GetReference() const
{
	return reference;
}

const DigitalIn::pIntFunc  DigitalIn::tpIntFunc [NUM_INLETS] = {
  &DigitalIn::SetChannel
};

void DigitalIn::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}


const char*const DigitalIn::szaInletDetails[NUM_INLETS] = {
  "Channel"
};

const char* DigitalIn::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else                                                     
    return NULL;
}

void DigitalIn::AddObject(DigitalIn* NewObject)
{
  DigitalIn** NewList = new DigitalIn* [ListSize + 1];
  //copy list over
  for(unsigned i = 0; i < ListSize; i++)
    NewList[i] = ObjectsList[i];
  //add new one
  NewList[ListSize] = NewObject;
  ListSize++;
  delete[] ObjectsList;
  ObjectsList = NewList;
}

const char*const DigitalIn::szType = DIGITAL_IN_TYPE;

const char*const DigitalIn::szaOutletDetails[NUM_OUTLETS] = {
	"Output Channel",
  "Output Value"
};

const char* DigitalIn::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}



DigitalIn::DigitalIn(Patch* Parent, const char* Name ,
		     const char* Comment, unsigned Channel)
  :BaseShell (Parent, NUM_INLETS,
	      NUM_OUTLETS, Name, Comment),
  cResetChannel(Channel), filtered (false), mOffMessage (0), mOnMessage (1)
{
  AddObject(this);
  Reset();
}

DigitalIn::~DigitalIn()
{
  DigitalIn** NewList = NULL;
  if(ListSize >1)
    NewList = new DigitalIn*[ListSize -1];
  bool Found = false;
  unsigned i;
  for (i = 0; i < ListSize && !Found; i++)
    if(ObjectsList[i] == this)
      Found = true;
    else
      {   //copy element back
			NewList[i] = ObjectsList[i];
      }
  ListSize--;
  //now copy remaining elements
  for(unsigned j = i-1; j < ListSize; j++)
    NewList[j] = ObjectsList[j+1];

  delete[] ObjectsList;
  ObjectsList = NewList;


}




BaseShell* DigitalIn::Create(Patch* Parent)
{
  return new DigitalIn(Parent);
}



void DigitalIn::ProcessInput(unsigned channel, unsigned value)
{
  for (unsigned i = 0; i < ListSize; i++)
	{
  	ObjectsList[i]->OutputValue(channel, value);
  }

}






void DigitalIn::OutputValue(unsigned channel, unsigned value)
{

  //produce the outputs
  if ((!filtered) || (channel + 1 == cChannel))
  {
		cValue = value;
    tpOutlet[CHANNEL_OUTLET]->ProduceOutput((int)channel + 1);

    if (value)
      tpOutlet[VALUE_OUTLET]->ProduceOutput(mOnMessage);
    else
      tpOutlet[VALUE_OUTLET]->ProduceOutput(mOffMessage);

  }



}


const DigitalIn::str_access DigitalIn::aAccess[NumAccess] =
{
  {"Channel", &DigitalIn::Channel, &DigitalIn::Channel},
  {"Input Value", &DigitalIn::Value, NULL}
};


const char* DigitalIn::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool DigitalIn::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool DigitalIn::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}


const DigitalIn::str_access DigitalIn::aResetAccess[NumResetAccess] =
{
	{"Reset Channel", &DigitalIn::ResetChannel, &DigitalIn::ResetChannel},
  {"Filter Input", &DigitalIn::Filter, &DigitalIn::Filter},
  {"Off Message", &DigitalIn::OffMessage, &DigitalIn::OffMessage},
  {"On Message", &DigitalIn::OnMessage, &DigitalIn::OnMessage}

};


const char* DigitalIn::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool DigitalIn::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool DigitalIn::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool DigitalIn::Channel (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetChannel(), ret, ret_size);
}

bool DigitalIn::Filter (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (filtered? 1:0, ret, ret_size);
}

bool DigitalIn::ResetChannel (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetChannel(), ret, ret_size);
}

bool DigitalIn::Value (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetValue(), ret, ret_size);
}

bool DigitalIn::OnMessage (char* ret, unsigned ret_size) const
{
	return mOnMessage.GetMessage(ret, ret_size);
}

bool DigitalIn::OffMessage (char* ret, unsigned ret_size) const
{
	return mOffMessage.GetMessage(ret, ret_size);
}

bool DigitalIn::Channel (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetChannel(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool DigitalIn::Filter (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			filtered = (SMUtility::StrToInt(new_val));
      if (filtered && !cResetChannel)
      {
        cResetChannel = 1;
      }
			ret = true;
		}
	return ret;
}

bool DigitalIn::ResetChannel (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetChannel(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool DigitalIn::OnMessage (const char* new_val)
{
  mOnMessage.Store(new_val);
	return true;
}

bool DigitalIn::OffMessage (const char* new_val)
{
  mOffMessage.Store(new_val);
	return true;
}
