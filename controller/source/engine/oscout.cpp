//MessageStore function dfns

#include "stdafx.h"
#include "control.h"
#include "oscout.h"
#include "typenames.h"
#include <string.h>
#include <stdio.h>
#include "htmsocket.h"

#define NUM_INLETS 3
#define NUM_OUTLETS 0


static bool InitSockets();

const char*const OscOut::szType = OSC_OUT_TYPE;

const unsigned OscOut::NumAccess = OscOut::eMaxAttribute;
const unsigned OscOut::NumResetAccess = OscOut::eMaxResetAttribute;

static bool sockets_initialised = false;

// create the default
static OscOut *reference = new OscOut (NULL);

const BaseShell* OscOut::GetReference() const
{
	return reference;
}

const char*const OscOut::szaInletDetails[NUM_INLETS] = {
  "UDP Target",
  "OSC Address",
  "OSC Argument"
};



const char* OscOut::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}

const char* OscOut::GetOutletName(unsigned OutletNumber)const
{
  UNREFERENCED_PARAMETER(OutletNumber);
  return NULL;
}


OscOut::OscOut (Patch* Parent, const char* Name,
			    const char* Comment)
  : BaseShell (Parent, NUM_INLETS,NUM_OUTLETS,
	       Name, Comment), _resetDesintationAddress(""), _reset_osc_address(""), _reset_on_send(1), _send_on_message (true)

{
  if (!sockets_initialised)
  {
    sockets_initialised = InitSockets();
  }
  OSC_initBuffer(&_OSCBuf, sizeof(_osc_buf_memory), _osc_buf_memory);
  Reset();
}



const OscOut::pVoidFunc  OscOut::tpVoidFunc [] = {
	&OscOut::SendOSC,
	NULL,
  &OscOut::AddMessage
};

const OscOut::pStringFunc  OscOut::tpStringFunc [] = {
	&OscOut::ControlStringInlet,
	&OscOut::SetOscAddress,
  &OscOut::AddMessage
};

const OscOut::pIntFunc  OscOut::tpIntFunc [] = {
	&OscOut::SetDestPort,
	NULL,
  &OscOut::AddMessage
};

const OscOut::pDoubleFunc  OscOut::tpDoubleFunc [] = {
	NULL,
	NULL,
  &OscOut::AddMessage
};

BaseShell* OscOut::Create(Patch* Parent)
{
	return new OscOut (Parent);
};

void OscOut::VoidInlet(unsigned InletNumber)
{
	if ((InletNumber < GetNumInlets()) && (tpVoidFunc[InletNumber]))
   	(this->*tpVoidFunc[InletNumber])();
}

void OscOut::StringInlet(unsigned InletNumber, const char* s)
{
	if ((InletNumber < GetNumInlets())&&(tpStringFunc[InletNumber]))
   	(this->*tpStringFunc[InletNumber])(s);
}

void OscOut::IntInlet(unsigned InletNumber, int i)
{
	if ((InletNumber < GetNumInlets()) && (tpIntFunc[InletNumber]))
   	(this->*tpIntFunc[InletNumber])(i);
}

void OscOut::DoubleInlet(unsigned InletNumber, double d)
  {
    if ((InletNumber < GetNumInlets()) &&(tpDoubleFunc[InletNumber]))
    {
   	  (this->*tpDoubleFunc[InletNumber])(d);
    }
  else
    {
      IntInlet (InletNumber, DoubleToInt(d));
    }
  }


void OscOut::Send ()
{
  if (_htmsocket)
  {
    SendHTMSocket(_htmsocket, OSC_packetSize(&_OSCBuf), OSC_getPacket(&_OSCBuf));
    if (_reset_on_send)
    {
      OSC_resetBuffer (&_OSCBuf);
      OSC_writeAddress (&_OSCBuf, _osc_address.c_str());
    }
  }
  else
  {
    printf ("Cannot OSC\r\n");
  }
};

void OscOut::ControlStringInlet(const char* s)
{
  // first see if it is one of our control messages
	if (!strcmp (s, "send")) // the two are ==
   	{Send(); return;}

   if (!strcmp (s, "reset"))
   	{Reset(); return;}

   if (!strcmp (s, "open"))
   	{OpenHtmSocket(); return;}

   if (!strcmp (s, "close"))
   	{CloseHtmSocket(); return;}

    // if not, then store address
   SetDestAddress(s);
}




// the get functions return true if the message type matches the ret parameter

bool OscOut::GetDestinationAddress(char* buf, unsigned buf_len)const
{
	bool ret = false;
	if (strlen (_destinationAddress.c_str()) < buf_len)
		{
			strcpy (buf, _destinationAddress.c_str());
			ret = true;
		}
	return ret;
}

bool OscOut::SetDestinationAddress (const char* new_value)
{
  bool ret = false;

  if (new_value)
  {
    _destinationAddress = string(new_value);

    if (!SetHTMDest (_htmsocket, new_value))
    {
      printf ("Unable to set destination\r\n");
    }
    ret = true;
  }
  return ret;
}

bool OscOut::GetOSCAddress(char* buf, unsigned buf_len)const
{
	bool ret = false;
	if (strlen (_osc_address.c_str()) < buf_len)
		{
			strcpy (buf, _osc_address.c_str());
			ret = true;
		}
	return ret;
}

bool OscOut::SetOSCAddress (const char* new_value)
{
  bool ret = false;

  if (new_value)
  {
    _osc_address = string(new_value);
    OSC_resetBuffer (&_OSCBuf);
    OSC_writeAddress (&_OSCBuf, new_value);
    ret = true;
  }
  return ret;
}

bool OscOut::GetResetOSCAddress(char* buf, unsigned buf_len)const
{
	bool ret = false;
	if (strlen (_reset_osc_address.c_str()) < buf_len)
		{
			strcpy (buf, _reset_osc_address.c_str());
			ret = true;
		}
	return ret;
}

bool OscOut::SetResetOSCAddress (const char* new_value)
{
  bool ret = false;

  if (new_value)
  {
    printf ("Set Reset OSC Address %s\r\n", new_value);
    _reset_osc_address = string(new_value);
    ret = true;
  }
  return ret;
}

bool OscOut::GetResetDestinationAddress(char* buf, unsigned buf_len)const
{
	bool ret = false;
	if (strlen (_resetDesintationAddress.c_str()) < buf_len)
		{
			strcpy (buf, _resetDesintationAddress.c_str());
			ret = true;
		}
	return ret;
}

bool OscOut::SetResetDestinationAddress (const char* new_value)
{
  bool ret = false;

  if (new_value)
  {
    _resetDesintationAddress = string(new_value);
    ret = true;
  }
  return ret;
}

bool OscOut::GetPort (char* buff, unsigned buff_len) const
{
  return SMUtility::IntToStr (_port, buff, buff_len);
}

bool OscOut::SetPort (const char* new_value)
{
	bool ret = false;
	if (SMUtility::IsInt(new_value))
		{
			SetDestPort (SMUtility::StrToInt(new_value));
			ret = true;
		}

	return ret;
}

bool OscOut::GetResetPort (char* buff, unsigned buff_len) const
{
  return SMUtility::IntToStr (_reset_port, buff, buff_len);
}


bool OscOut::SetResetPort (const char* new_value)
{
	bool ret = false;
	if (SMUtility::IsInt(new_value))
		{
			_reset_port = SMUtility::StrToInt(new_value);
			ret = true;
		}

	return ret;
}

bool OscOut::GetPortOpen (char* buff, unsigned buff_len) const
{
  int is_open = 0;
  if (_htmsocket)
  {
    is_open = 1;
  }

  return SMUtility::IntToStr (is_open, buff, buff_len);
}

bool OscOut::SetPortOpen (const char* new_value)
{
	bool ret = false;
	if (SMUtility::IsInt(new_value))
		{
      bool open = (SMUtility::StrToInt(new_value));

      if (open)
      {
        ret = OpenHtmSocket();
      }
      else
      {
        CloseHtmSocket();
        ret = true;
      }

		}

	return ret;
}

bool OscOut::GetResetOnSend (char* buff, unsigned buff_len) const
{
  return SMUtility::IntToStr (_reset_on_send, buff, buff_len);
}

bool OscOut::GetSendOnMessage (char* buff, unsigned buff_len) const
{
  return SMUtility::IntToStr (_send_on_message?1: 0, buff, buff_len);
}

bool OscOut::SetResetOnSend (const char* new_value)
{
	bool ret = false;
	if (SMUtility::IsInt(new_value))
		{
			_reset_on_send = SMUtility::StrToInt(new_value);
			ret = true;
		}

	return ret;
}

bool OscOut::SetSendOnMessage (const char* new_value)
{
	bool ret = false;
	if (SMUtility::IsInt(new_value))
		{
			_send_on_message = (SMUtility::StrToInt(new_value));
			ret = true;
		}

	return ret;
}

const OscOut::str_access OscOut::aAccess[NumAccess] =
{
  {"UDP Address", &OscOut::GetDestinationAddress, &OscOut::SetDestinationAddress},
  {"UDP Port", &OscOut::GetPort, &OscOut::SetPort},
  {"OSC Address", &OscOut::GetOSCAddress, &OscOut::SetOSCAddress},
  {"Port Open", &OscOut::GetPortOpen, &OscOut::SetPortOpen}

};


const char* OscOut::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool OscOut::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
			(this->*aAccess [index].set_func) (value);
       ret = true;
    }

  return ret;
}

bool OscOut::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}


const OscOut::str_access OscOut::aResetAccess[NumResetAccess] =
{
  {"Reset UDP Address", &OscOut::GetResetDestinationAddress, &OscOut::SetResetDestinationAddress},
  {"Reset UDP Port", &OscOut::GetResetPort, &OscOut::SetResetPort},
  {"Reset OSC Address", &OscOut::GetResetOSCAddress, &OscOut::SetResetOSCAddress},
  {"Reset Sent Message", &OscOut::GetResetOnSend, &OscOut::SetResetOnSend},
  {"Send Each Argument", &OscOut::GetSendOnMessage, &OscOut::SetSendOnMessage}

};

const char* OscOut::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool OscOut::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      (this->*aResetAccess [index].set_func) (value);
			ret = true;
    }

  return ret;
}

bool OscOut::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool OscOut::GetDefaultAttribute (char* buf, unsigned buf_len)const
{
	return GetOSCAddress (buf, buf_len);
}



void OscOut::SetOscAddress (const char* s)
{
  SetOSCAddress (s); // call bool version -- note case
}


void OscOut::AddMessage ()
{
  if (_send_on_message)
    Send();
}

void OscOut::AddMessage (int i)
{
  OSC_writeIntArg(&_OSCBuf, i);
  if (_send_on_message)
    Send();

}

void OscOut::AddMessage (double d)
{
  OSC_writeFloatArg(&_OSCBuf, d);
  if (_send_on_message)
    Send();

}

void OscOut::AddMessage (const char* s)
{
  OSC_writeStringArg(&_OSCBuf, s);
  if (_send_on_message)
    Send();

}

void OscOut::SetDestPort (int i)
{
  if (i != _port || !_htmsocket)
  {
    _port = i;
    OpenHtmSocket();
    printf ("Set Port %i\r\n", i);
  }
}

void OscOut::Reset()
{
  SetDestinationAddress (_resetDesintationAddress.c_str());
  SetDestPort(_reset_port);

  SetOSCAddress (_reset_osc_address.c_str());
}

bool OscOut::OpenHtmSocket()
{
  CloseHtmSocket();
  _htmsocket = OpenHTMSocket(_destinationAddress.c_str(), _port);

  return (_htmsocket);
}

void OscOut::CloseHtmSocket()
{
  if (_htmsocket)
    CloseHTMSocket(_htmsocket);

  _htmsocket = NULL;
}

bool InitSockets(){
#ifdef WIN32
  printf ("Init Sockets\r\n");
  WORD wVersionRequested;
  WSADATA wsaData;

  wVersionRequested = MAKEWORD( 2, 2 );

  WSAStartup( wVersionRequested, &wsaData );
#endif
  return true;
}
