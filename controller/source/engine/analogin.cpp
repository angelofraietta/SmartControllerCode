//AnalogIn function defs
#include "stdafx.h"

#include "iodata.h"
#include "control.h"
#include "analogin.h"
#include "typenames.h"
#include "ostypes.h"

#define NUM_INLETS 1
#define NUM_OUTLETS 2

#define CHANNEL_OUTLET 0
#define VALUE_OUTLET 1

// this is the 

//static variables
// this is for 8 bit resolution. When the Resolution is increased, this will have to increase also
#define MAX_ANA_VAL 1023

AnalogIn** AnalogIn::ObjectsList = NULL;
unsigned AnalogIn::ListSize = 0;


const unsigned AnalogIn::NumAccess = AnalogIn::eMaxAttribute;
const unsigned AnalogIn::NumResetAccess = AnalogIn::eMaxResetAttribute;

// create the default
static AnalogIn* reference = new AnalogIn (NULL);

const BaseShell* AnalogIn::GetReference() const
{
	return reference;
}


inline bool AnalogIn::DoScale()const
{
  return fLowerScale != 0 ||
   fUpperScale != MAX_ANA_VAL;
}

void AnalogIn::CalculateRange ()
{
  fRange = ((fUpperScale - fLowerScale)) / (MAX_ANA_VAL);
  iRange = ((iUpperScale - iLowerScale) + 1);
  printf ("Range = %f %i\r\n", fRange, iRange);
}

void AnalogIn::AddObject(AnalogIn* NewObject)
{
  AnalogIn** NewList = new AnalogIn* [ListSize + 1];
  //copy list over
  for(unsigned i = 0; i < ListSize; i++)
    NewList[i] = ObjectsList[i];
  //add new one
  NewList[ListSize] = NewObject;
  ListSize++;
  delete[] ObjectsList;
  ObjectsList = NewList;
}

const char*const AnalogIn::szType = ANALOGUE_IN_TYPE;

const AnalogIn::pIntFunc  AnalogIn::tpIntFunc [NUM_INLETS] = {
  &AnalogIn::SetChannel
};

void AnalogIn::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}


const char*const AnalogIn::szaInletDetails[NUM_INLETS] = {
  "Channel"
};

const char* AnalogIn::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}


const char*const AnalogIn::szaOutletDetails[NUM_OUTLETS] = {
	"Output Channel",
  "Output Value"
};

const char* AnalogIn::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}



AnalogIn::AnalogIn(Patch* Parent, const char* Name ,
		     const char* Comment, unsigned Channel,
         float lower_scale,
         float upper_scale,
         unsigned lower_threshold,
         unsigned upper_threshold)
  :BaseShell (Parent, NUM_INLETS,
	      NUM_OUTLETS, Name, Comment),
  cResetChannel(Channel), filtered (false), fLowerScale (lower_scale), iLowerScale((int)lower_scale),
    fUpperScale (upper_scale), iUpperScale((int)upper_scale),
   iLowerThreshold (lower_threshold), iUpperThreshold (upper_threshold), enable_float(false)
{
  if (this != reference)
  {
    AddObject(this);
  }
   
  Reset();
}

AnalogIn::~AnalogIn()
{
  AnalogIn** NewList = NULL;
  if(ListSize >1)
    NewList = new AnalogIn*[ListSize -1];
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




BaseShell* AnalogIn::Create(Patch* Parent)
{
  return new AnalogIn(Parent);
}



void AnalogIn::ProcessInput(unsigned channel, unsigned value)
{
  for (unsigned i = 0; i < ListSize; i++)
	{
  	ObjectsList[i]->OutputValue(channel, value);
  }

}






void AnalogIn::OutputIntValue(unsigned channel, unsigned value)
{
  if ((!filtered) || (channel + 1 == cChannel))
  {
    if (!DoScale())
    {
      if (value >= iLowerThreshold && value <= iUpperThreshold)
      {
		    if (cValue != value)
        {
          cValue = value;
          tpOutlet[CHANNEL_OUTLET]->ProduceOutput((int)channel + 1);
          tpOutlet[VALUE_OUTLET]->ProduceOutput((int)value);
        }
      }
    }
    else
    {
        if (iRange)
        {
          int new_val = (value * iRange);
          //printf ("New Value %d\r\n", new_val);

          new_val = (new_val / (MAX_ANA_VAL + 1)) + iLowerScale;
          //printf ("New Value %f\r\n",new_val);
          if (new_val >= iLowerThreshold && new_val <= iUpperThreshold)
          {
            //printf ("New Value %f acepted\r\n",new_val);
            if (cValue !=  new_val)
            {
              cValue = new_val;
              tpOutlet[CHANNEL_OUTLET]->ProduceOutput((int)channel + 1);
              tpOutlet[VALUE_OUTLET]->ProduceOutput(cValue);
            }
          }
        }

    }
  }

}

void AnalogIn::OutputFloatValue(unsigned channel, unsigned value)
{
  //printf ("AnalogIn::OutputValue %u\r\n", value);
  //produce the outputs
  if ((!filtered) || (channel + 1 == cChannel))
  {
    if (!DoScale())
    {
      if (value >= iLowerThreshold && value <= iUpperThreshold)
      {
		    if (cValue != value)
        {
          cValue = value;
          tpOutlet[CHANNEL_OUTLET]->ProduceOutput((int)channel + 1);
          tpOutlet[VALUE_OUTLET]->ProduceOutput((int)value);
        }
      }
    }
    else
    {
        if (fRange != 0)
        {
          float new_val = (fRange * value) + fLowerScale;
          //printf ("New Value %f\r\n",new_val);
          if (new_val >= iLowerThreshold && new_val <= iUpperThreshold)
          {
            //printf ("New Value %f acepted\r\n",new_val);
            if (fValue !=  new_val)
            {
              fValue = new_val;
              tpOutlet[CHANNEL_OUTLET]->ProduceOutput((int)channel + 1);
              tpOutlet[VALUE_OUTLET]->ProduceOutput(fValue);
            }
          }
        }

    }
  }

} //OutputFloatValue

void AnalogIn::OutputValue(unsigned channel, unsigned value)
{
  if (enable_float)
  {
    OutputFloatValue(channel, value);
  }
  else
  {
    OutputIntValue(channel, value);
  }

}


const AnalogIn::str_access AnalogIn::aAccess[NumAccess] =
{
  {"Channel", &AnalogIn::Channel, &AnalogIn::Channel},
  {"Input Value", &AnalogIn::Value, NULL}
};


const char* AnalogIn::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool AnalogIn::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool AnalogIn::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}


const AnalogIn::str_access AnalogIn::aResetAccess[NumResetAccess] =
{
	{"Reset Channel", &AnalogIn::ResetChannel, &AnalogIn::ResetChannel},
  {"Filter Input", &AnalogIn::Filter, &AnalogIn::Filter},
  {"LowerScale", &AnalogIn::LowerScale, &AnalogIn::LowerScale},
  {"UpperScale", &AnalogIn::UpperScale, &AnalogIn::UpperScale},
  {"LowerThreshold", &AnalogIn::LowerThreshold, &AnalogIn::LowerThreshold},
  {"UpperThreshold", &AnalogIn::UpperThreshold, &AnalogIn::UpperThreshold},
  {"EnableFloat", &AnalogIn::EnableFloat, &AnalogIn::EnableFloat}
};


const char* AnalogIn::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool AnalogIn::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool AnalogIn::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool AnalogIn::Channel (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetChannel(), ret, ret_size);
}

bool AnalogIn::ResetChannel (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetChannel(), ret, ret_size);
}

bool AnalogIn::Filter (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (filtered? 1:0, ret, ret_size);
}

bool AnalogIn::EnableFloat (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (enable_float? 1:0, ret, ret_size);
}

bool AnalogIn::LowerScale(char* ret, unsigned ret_size) const
{
  bool ret_val;

  if (enable_float)
  {
    ret_val = SMUtility::FltToStr (fLowerScale, ret, ret_size);
  }

  else
  {
	  ret_val = SMUtility::IntToStr (iLowerScale, ret, ret_size);
  }

  return ret_val;
}

bool AnalogIn::UpperScale(char* ret, unsigned ret_size) const
{
  bool ret_val;

  if (enable_float)
  {
    ret_val = SMUtility::FltToStr (fUpperScale, ret, ret_size);
  }
  else
  {
	  ret_val = SMUtility::IntToStr (iUpperScale, ret, ret_size);
  }
  return ret_val;
}

bool AnalogIn::LowerThreshold(char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (iLowerThreshold, ret, ret_size);
}

bool AnalogIn::UpperThreshold(char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (iUpperThreshold, ret, ret_size);
}

bool AnalogIn::Value (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetValue(), ret, ret_size);
}

bool AnalogIn::Channel (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetChannel(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool AnalogIn::ResetChannel (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetChannel(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool AnalogIn::Filter (const char* new_val)
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

bool AnalogIn::EnableFloat (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			enable_float = (SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}


bool AnalogIn::LowerScale(const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			fLowerScale = atof(new_val);
      iLowerScale = SMUtility::StrToInt(new_val);
      CalculateRange();
			ret = true;
		}
	return ret;
}

bool AnalogIn::UpperScale(const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			fUpperScale = atof(new_val);
      iUpperScale = SMUtility::StrToInt(new_val);      
      CalculateRange();
			ret = true;
		}
	return ret;
}

bool AnalogIn::LowerThreshold(const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			iLowerThreshold = SMUtility::StrToInt(new_val);

			ret = true;
		}
	return ret;
}

bool AnalogIn::UpperThreshold(const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsFloat(new_val))
		{
			iUpperThreshold = SMUtility::StrToInt(new_val);
			ret = true;
		}
	return ret;
}
