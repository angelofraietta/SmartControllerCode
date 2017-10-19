//AnalogIn function defs
#include "stdafx.h"

#include "iodata.h"
#include "control.h"
#include "oscin.h"
#include "typenames.h"
#include "ostypes.h"
#include "oscarg.h"
#include "oscinput.h"

#define NUM_INLETS 2
#define NUM_OUTLETS 6

enum {PORT_OUTLET, CLIENT_OUTLET, OSC_ADDRESS_OUTLET, NUM_ARGS_OUTLET, ARG_NUMBER_OUTLET, ARGS_OUTLET};


//static variables

OSCIn** OSCIn::ObjectsList = NULL;
unsigned OSCIn::ListSize = 0;


const unsigned OSCIn::NumAccess = OSCIn::eMaxAttribute;
const unsigned OSCIn::NumResetAccess = OSCIn::eMaxResetAttribute;

// create the default
static OSCIn* reference = new OSCIn (NULL);

const BaseShell* OSCIn::GetReference() const
{
	return reference;
}


void OSCIn::AddObject(OSCIn* NewObject)
{
  if (NewObject != reference)
  {
    OSCIn** NewList = new OSCIn* [ListSize + 1];
    //copy list over
    for(unsigned i = 0; i < ListSize; i++)
      NewList[i] = ObjectsList[i];
    //add new one
    NewList[ListSize] = NewObject;
    ListSize++;
    delete[] ObjectsList;
    ObjectsList = NewList;
  }
}

const char*const OSCIn::szType = OSC_IN_TYPE;

const OSCIn::pIntFunc  OSCIn::tpIntFunc [NUM_INLETS] = {
  NULL,
  &OSCIn::SetPort
};

const OSCIn::pStringFunc  OSCIn::tpStringFunc [] = {
	&OSCIn::SetOscAddress,
  NULL
};

void OSCIn::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}

void OSCIn::StringInlet(unsigned InletNumber, const char* s)
{
	if ((InletNumber < GetNumInlets())&&(tpStringFunc[InletNumber]))
   	(this->*tpStringFunc[InletNumber])(s);
}

const char*const OSCIn::szaInletDetails[NUM_INLETS] = {
  "OSC Address",
  "UDP Port"
};

const char* OSCIn::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}


const char*const OSCIn::szaOutletDetails[NUM_OUTLETS] = {
	"UDP Port",
  "Client Address",
  "OSC Address",
  "Num Arguments",
  "Argument Number",
  "OSC Arguments"
};

const char* OSCIn::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}



OSCIn::OSCIn(Patch* Parent, const char* Name ,
		     const char* Comment, unsigned Channel, const char* osc_address)
  :BaseShell (Parent, NUM_INLETS,
	      NUM_OUTLETS, Name, Comment),
  _reset_port(Channel), _reset_osc_address_space (osc_address)
{
  if (Parent)
  {
    AddObject(this);
  }
  Reset();
}

OSCIn::~OSCIn()
{
  OSCIn** NewList = NULL;
  if(ListSize >1)
    NewList = new OSCIn*[ListSize -1];
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




BaseShell* OSCIn::Create(Patch* Parent)
{
  return new OSCIn(Parent);
}



void OSCIn::ProcessInput(int port, const char* osc_address, const char* client_address, unsigned num_args, OSCArg* args)
{
  for (unsigned i = 0; i < ListSize; i++)
	{
    if (ObjectsList[i]->ObjectAcceptOSCMessage(port, osc_address))
    {
  	  ObjectsList[i]->GenerateOutput(port, osc_address, client_address, num_args, args);
    }
  }

}

void OSCIn::GenerateOutput(int port, const char* osc_address, const char* client_address, unsigned num_args, OSCArg* args)
{
  tpOutlet[PORT_OUTLET]->ProduceOutput(port);
  tpOutlet[CLIENT_OUTLET]->ProduceOutput(client_address);
  tpOutlet[OSC_ADDRESS_OUTLET]->ProduceOutput(osc_address);
  tpOutlet[NUM_ARGS_OUTLET]->ProduceOutput((int)num_args);

  for (unsigned i = 0; i < num_args; i++)
  {
    tpOutlet[ARG_NUMBER_OUTLET]->ProduceOutput((int)i+1);

    OSCArg& arg = args[i];

    switch (arg._arg_type)
    {
      case OSCArg::eTick:
        tpOutlet[ARGS_OUTLET]->ProduceOutput();
        break;

      case OSCArg::eInt:
        tpOutlet[ARGS_OUTLET]->ProduceOutput(arg.i);
        break;

      case OSCArg::eFloat:
        tpOutlet[ARGS_OUTLET]->ProduceOutput(arg.f);
        break;

      case OSCArg::eString:
        tpOutlet[ARGS_OUTLET]->ProduceOutput(arg.s);
        break;

      case OSCArg::eUndefined:
        tpOutlet[ARGS_OUTLET]->ProduceOutput("?");
        break;


    }
  }
}

bool OSCIn::ObjectAcceptOSCMessage (int port, const char* osc_address)
{
  bool accept = false;
    // first test the port Number - 0 or the port number are acceptable
    if (GetPort() == 0 || GetPort() == port)
    {
      const char* local_address = _osc_address_space.c_str();

      // test for matching address
      if ((!strcmp (local_address, "*")) || (!strcmp(local_address, osc_address)))
      {
        accept = true;
      }
    }

  return accept;
}

bool OSCIn::AcceptOSCMessage (int port, const char* osc_address)
{
  bool accept = false;

  for (unsigned i = 0; i < ListSize && ! accept; i++)
  {
    // first test the port Number - 0 or the port number are acceptable
    accept = ObjectsList[i]->ObjectAcceptOSCMessage(port, osc_address);
  }


  return accept;
}



const OSCIn::str_access OSCIn::aAccess[NumAccess] =
{
  {"UDP Port", &OSCIn::Port, &OSCIn::Port},
  {"OSC Address", &OSCIn::OSCAddress, &OSCIn::OSCAddress}
};


const char* OSCIn::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool OSCIn::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool OSCIn::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}


const OSCIn::str_access OSCIn::aResetAccess[NumResetAccess] =
{
  {"UDP Port", &OSCIn::ResetPort, &OSCIn::ResetPort},
  {"OSC Address", &OSCIn::ResetOSCAddress, &OSCIn::ResetOSCAddress}
};


const char* OSCIn::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool OSCIn::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool OSCIn::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool OSCIn::Port (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetPort(), ret, ret_size);
}

bool OSCIn::ResetPort (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetPort(), ret, ret_size);
}

bool OSCIn::OSCAddress (char* buf, unsigned buf_len) const
{
	bool ret = false;
	if (strlen (_osc_address_space.c_str()) < buf_len)
		{
			strcpy (buf, _osc_address_space.c_str());
			ret = true;
		}
	return ret;
}

bool OSCIn::ResetOSCAddress (char* buf, unsigned buf_len) const
{
	bool ret = false;
	if (strlen (_reset_osc_address_space.c_str()) < buf_len)
		{
			strcpy (buf, _reset_osc_address_space.c_str());
			ret = true;
		}
	return ret;
}

bool OSCIn::Port (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetPort(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool OSCIn::ResetPort (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetPort(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}


bool OSCIn::OSCAddress (const char* new_val)
{
  bool ret = false;

  if (new_val)
  {
    _osc_address_space = string(new_val);
    ret = true;
  }
  return ret;
}

bool OSCIn::ResetOSCAddress (const char* new_val)
{
  bool ret = false;

  if (new_val)
  {
    _reset_osc_address_space = string(new_val);
    ret = true;
  }
  return ret;
}

void OSCIn::SetPort(int port)
{
  // we will allow a port of zero
  if (OSCInput::create(port) || (!port))
  {
    _port = port;
  }
}

bool OSCIn::GetDefaultAttribute (char* ret_value, unsigned buff_len)const
{
  // return the operator and the right val;

  //first get the operator
  bool ret = Port(ret_value, buff_len);

  
  // first put the
  if (ret)
  {
    unsigned new_start = strlen(ret_value);
    buff_len -= new_start;

    if (buff_len > 2)
    {
       ret_value [new_start] = ':'; // place a Char IN
       ret = OSCAddress ( ret_value + new_start + 1, buff_len -1);
    }


  }

  return ret;
}
