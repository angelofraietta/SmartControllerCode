//## begin module%40FEFD010122.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40FEFD010122.cm

//## begin module%40FEFD010122.cp preserve=no
//	Angelo Fraietta
//## end module%40FEFD010122.cp

//## Module: OSCInput%40FEFD010122; Pseudo Package body
//## Subsystem: engine%39F51CB901B8
//## Source file: D:\develop\smartcontroller\controller\source\engine\oscinput.cpp

//## begin module%40FEFD010122.additionalIncludes preserve=no
//## end module%40FEFD010122.additionalIncludes

//## begin module%40FEFD010122.includes preserve=yes
#include "iodata.h"
#include "control.h"
#include <stdio.h>
//## end module%40FEFD010122.includes

// scheduler
#include "scheduler.h"
// OSCInput
#include "oscinput.h"
// OSCArg
#include "oscarg.h"
// OSCIn
#include "oscin.h"
// Event
#include "event.h"
// UDPPort
#include "udpport.h"
//## begin module%40FEFD010122.additionalDeclarations preserve=yes
#define STRING_ALIGN_PAD 4
#define SMALLEST_POSITIVE_FLOAT 0.000001f
using hal_include::Scheduler;
#define LOCK_WAIT_TIME 10000

#define MAX_OSC_IN_INPUTS 10

OSCInput* _OscInList[MAX_OSC_IN_INPUTS];
//## end module%40FEFD010122.additionalDeclarations


// Class OSCInput 






//## begin OSCInput::_list_size%41008BD601C5.attr preserve=no  private: static unsigned {U} 0
unsigned OSCInput::_list_size = 0;
//## end OSCInput::_list_size%41008BD601C5.attr




OSCInput::OSCInput()
  //## begin OSCInput::OSCInput%.hasinit preserve=no
      : _is_open(false), _port_num(0), _purging(false), _num_args(0), _in_port(new UDPPort()), pEvent(Event::create()), _args(new OSCArg[100])
  //## end OSCInput::OSCInput%.hasinit
  //## begin OSCInput::OSCInput%.initialization preserve=yes
  //## end OSCInput::OSCInput%.initialization
{
  //## begin OSCInput::OSCInput%.body preserve=yes
  //## end OSCInput::OSCInput%.body
}


OSCInput::~OSCInput()
{
  //## begin OSCInput::~OSCInput%.body preserve=yes
  _purging = true;
  close();
  pEvent->Release ();
  delete _in_port;
  delete pEvent;
  delete []_args;
  //## end OSCInput::~OSCInput%.body
}



//## Other Operations (implementation)
//## Operation: run%1090452875
//	The actual function of the task
void OSCInput::run ()
{
  //## begin OSCInput::run%1090452875.body preserve=yes
  while (!Terminated() && !_purging)
  {
    if (_is_open)
    {
      unsigned long bytes_read = _in_port->ReadBuffer(_in_buf, sizeof(_in_buf));
      char from [256];
      if (_in_port->GetFrom (from, sizeof(from)))
      {
        ParseOSCPacket((char*) _in_buf, bytes_read, from);

      }
    }
    else
    {
      pEvent->Wait();
    }
  }
  //## end OSCInput::run%1090452875.body
}

//## Operation: open%1090452876
//	Open The UDP Port
bool OSCInput::open (int port_num)
{
  //## begin OSCInput::open%1090452876.body preserve=yes
  close();
  _is_open = _in_port->OpenPort(port_num);
  _port_num = port_num;
  pEvent->Release ();
  return _is_open;
  //## end OSCInput::open%1090452876.body
}

//## Operation: close%1090452877
void OSCInput::close ()
{
  //## begin OSCInput::close%1090452877.body preserve=yes
  _is_open = false;
  _in_port->Close();
  //## end OSCInput::close%1090452877.body
}

//## Operation: ParseOSCPacket%1090452878
//	Parse The OSC Packet
bool OSCInput::ParseOSCPacket (char*  buf, unsigned buf_len, const char* client_address)
{
  //## begin OSCInput::ParseOSCPacket%1090452878.body preserve=yes
  bool ret = true;

	int size, messageLen, i;
	char *messageName;
	char *args;
	
	if ((buf_len%4) != 0) {
		printf("SynthControl packet size (%d) not a multiple of 4 bytes: dropping",
						 buf_len);
		return false;
	}
	
	if ((buf_len >= 8) && (strncmp(buf, "#bundle", 8) == 0)) {
		printf ("Bundle Message\r\n");
		/* This is a bundle message. */
		
		if (buf_len < 16) {
			printf("Bundle message too small (%d bytes) for time tag", buf_len);
			return false;
		}
		
		/* Print the time tag */
		printf("[ %lx%08lx\n", ntohl(*((unsigned long *)(buf+8))),
					 ntohl(*((unsigned long *)(buf+12))));
		/* Note: if we wanted to actually use the time tag as a little-endian
			 64-bit int, we'd have to word-swap the two 32-bit halves of it */
		
		i = 16; /* Skip "#group\0" and time tag */
		while(i<buf_len) {
	    size = ntohl(*((int *) (buf + i)));
	    if ((size % 4) != 0) {
				printf("Bad size count %d in bundle (not a multiple of 4)", size);
				return false;
	    }
	    if ((size + i + 4) > buf_len) {
				printf("Bad size count %d in bundle (only %d bytes left in entire bundle)",
								 size, buf_len-i-4);
				return false;
	    }

	    /* Recursively handle element of bundle */
	    ret &= ParseOSCPacket(buf+i+4, size, client_address);
	    i += 4 + size;
		}
		if (i != buf_len) {
	    printf("This can't happen");
		}
		printf("]\buf_len");
	} else {
		/* This is not a bundle message */
		messageName = buf;

		args = DataAfterAlignedString(messageName, buf+buf_len);
		/* We have Just Moved the pointer */
		if (args == 0) {
	    printf("Bad message name string: \nDropping entire message.\n");
	    return false;
		}
		messageLen = args-messageName;	   /* This is the length of the Address */

    if (Scheduler::LockEngine(LOCK_WAIT_TIME))
    {
      if (OSCIn::AcceptOSCMessage(_port_num, messageName))
      {
        // parse the complete message and send it
        SendOSCMessage(messageName, args, buf_len-messageLen, client_address);
      }
      Scheduler::UnlockEngine();
    }
	}


  return ret;
  //## end OSCInput::ParseOSCPacket%1090452878.body
}

//## Operation: DataAfterAlignedString%1090452879
//	The argument is a block of data beginning with a
//	string.  The string has (presumably) been padded with
//	extra null characters so that the overall length is a
//	multiple of STRING_ALIGN_PAD bytes.  Return a pointer to
//	the next byte after the null byte(s).  The boundary
//	argument points to the character after the last valid
//	character in the buffer---if the string hasn't ended by
//	there, something's wrong.
//	If the data looks wrong, return 0, and set htm_error_
//	string
char* OSCInput::DataAfterAlignedString (char* string, char* boundary)
{
  //## begin OSCInput::DataAfterAlignedString%1090452879.body preserve=yes
	int i;
	
	if ((boundary - string) %4 != 0) {
		fprintf(stderr, "Internal error: DataAfterAlignedString: bad boundary\n");
		return 0;
	}
	
	for (i = 0; string[i] != '\0'; i++) {
		if (string + i >= boundary) {
	    printf("DataAfterAlignedString: Unreasonably long string");
	    return 0;
		}
	}

	/* Now string[i] is the first null character */
	i++;

	for (; (i % STRING_ALIGN_PAD) != 0; i++) {
		if (string + i >= boundary) {
	    printf("DataAfterAlignedString: Unreasonably long string");
	    return 0;
		}
		if (string[i] != '\0') {
	    printf("DataAfterAlignedString: Incorrectly padded string.");
	    return 0;
		}
	}
	
	return string+i;
  
  //## end OSCInput::DataAfterAlignedString%1090452879.body
}

//## Operation: SendOSCMessage%1090452880
//	Send the Message
bool OSCInput::SendOSCMessage (const char* osc_address, char* arg_data, int arg_data_length, const char* client_address)
{
  //## begin OSCInput::SendOSCMessage%1090452880.body preserve=yes
  _num_args = 0;

	//printf("%s ", osc_address);

	if (arg_data_length != 0) {
		if (arg_data[0] == ',') {
	    if (arg_data[1] != ',') {
				/* This message begins with a type-tag string */
				ObtainTypeTaggedArgs(arg_data, arg_data_length);
	    } else {
				/* Double comma means an escaped real comma, not a type string */
				ObtainHeuristicallyTypeGuessedArgs(arg_data, arg_data_length, true);
	    }
		} else {
	    ObtainHeuristicallyTypeGuessedArgs(arg_data, arg_data_length, false);
		}
	}

  OSCIn::ProcessInput (_port_num, osc_address, client_address, _num_args, _args); 
  return _num_args;
  
  //## end OSCInput::SendOSCMessage%1090452880.body
}

//## Operation: ObtainTypeTaggedArgs%1090452881
//	Returns The number of arguments
unsigned OSCInput::ObtainTypeTaggedArgs (void* arg_data_buf, unsigned buf_len)
{
  //## begin OSCInput::ObtainTypeTaggedArgs%1090452881.body preserve=yes
	char *typeTags, *thisType;
	char *p;
  int i;
  
	typeTags = (char*) arg_data_buf;

	if (!IsNiceString(typeTags, typeTags + buf_len)) {
		/* No null-termination, so maybe it wasn't a type tag
			 string after all */
		return ObtainHeuristicallyTypeGuessedArgs(arg_data_buf, buf_len, false);
	}

	p = DataAfterAlignedString(typeTags, typeTags + buf_len);


	for (thisType = typeTags + 1; *thisType != 0; ++thisType) {
		switch (*thisType) {
		case 'i': case 'r': case 'm': case 'c':
	    //printf("%d ", ntohl(*((int *) p)));
      i = ntohl(*((int *) p));
      _args [_num_args].SetVal(i);
      _num_args++;
	    p += 4;
	    break;

		case 'f': {
			i = ntohl(*((int *) p));
			float *floatp = ((float *) (&i));
			//printf("%f ", *floatp);
      _args [_num_args].SetVal(*floatp);
      _num_args++;
			p += 4;
		}
		break;

		case 'h': case 't':
	    //printf("[A 64-bit int] ");
      _args [_num_args].ClearVal();
      _num_args++;
	    p += 8;
	    break;

		case 'd':
	    //printf("[A 64-bit float] ");
      _args [_num_args].ClearVal();
      _num_args++;
	    p += 8;
	    break;

		case 's': case 'S':
	    if (!IsNiceString(p, typeTags + buf_len)) {
				printf("Type tag said this arg is a string but it's not!\n");
        _num_args = 0;
				return 0;
	    } else {
				//printf("\"%s\" ", p);
        _args [_num_args].SetVal(p);
        _num_args++;
				p = DataAfterAlignedString(p, typeTags + buf_len);
	    }
	    break;

		case 'T':
      //printf("[True] ");
      _args [_num_args].SetVal((int)1);
      _num_args++;

      break;
		case 'F':
      //printf("[False] ");
      _args [_num_args].SetVal((int)0);
      _num_args++;

      break;
		case 'N':
      //printf("[Nil]");
      _args [_num_args].SetVal();
      _num_args++;
      break;

		case 'I':
      _args [_num_args].ClearVal();
      _num_args++;
      printf("[Infinitum]"); break;

		default:
	    printf("[Unrecognized type tag %c]", *thisType);
      _num_args = 0;
	    return 0;
		}
	}

  return _num_args;
  //## end OSCInput::ObtainTypeTaggedArgs%1090452881.body
}

//## Operation: ObtainHeuristicallyTypeGuessedArgs%1090452882
//	Returns The number of arguments
unsigned OSCInput::ObtainHeuristicallyTypeGuessedArgs (void* arg_data_buf, unsigned buf_len, bool skipComma)
{
  //## begin OSCInput::ObtainHeuristicallyTypeGuessedArgs%1090452882.body preserve=yes
	int i, thisi;
	float thisf;
	int *ints;
	char *chars;
	char *string, *nextString;

	/* Go through the arguments 32 bits at a time */
	ints = (int*) arg_data_buf;
	chars = (char*) arg_data_buf;

	for (i = 0; i< buf_len /4; ) {
		string = &chars[i*4];
		thisi = ntohl(ints[i]);
		/* Reinterpret the (potentially byte-reversed) thisi as a float */
		thisf = *(((float *) (&thisi)));

		if  (thisi >= -1000 && thisi <= 1000000) {
	    //printf("%d ", thisi);
      _args [_num_args].SetVal(thisi);
      _num_args++;
	    i++;
		} else if (thisf >= -1000.f && thisf <= 1000000.f &&
							 (thisf <=0.0f || thisf >= SMALLEST_POSITIVE_FLOAT)) {
	    //printf("%f ",  thisf);
      _args [_num_args].SetVal(thisf);
      _num_args++;
	    i++;
		} else if (IsNiceString(string, chars + buf_len)) {
	    nextString = DataAfterAlignedString(string, chars + buf_len);
	    //printf("\"%s\" ", (i == 0 && skipComma) ? string +1 : string);
			//num_args++;
      _args [_num_args].SetVal((i == 0 && skipComma) ? string +1 : string);
      _num_args++;

	    i += (nextString-string) / 4;
		} else {
	    //printf("0x%x ", ints[i]);
      _args [_num_args].ClearVal();
      _num_args++;
	    i++;
		}
	}
  return _num_args;
  //## end OSCInput::ObtainHeuristicallyTypeGuessedArgs%1090452882.body
}

//## Operation: IsNiceString%1090452883
//	Arguments same as DataAfterAlignedString().  Is the
//	given "string" really a string?  I.e., is it a sequence
//	of isprint() characters terminated with 1-4 null
//	characters to align on a 4-byte boundary?
bool OSCInput::IsNiceString (char* string, char* boundary)
{
  //## begin OSCInput::IsNiceString%1090452883.body preserve=yes
  int i;

	if ((boundary - string) %4 != 0) {
		fprintf(stderr, "Internal error: IsNiceString: bad boundary\n");
		return false;
	}

	for (i = 0; string[i] != '\0'; i++) {
		if (!isprint(string[i])) return FALSE;
		if (string + i >= boundary) return FALSE;
	}

	/* If we made it this far, it's a null-terminated sequence of printing characters
		 in the given boundary.  Now we just make sure it's null padded... */

	/* Now string[i] is the first null character */
	i++;
	for (; (i % STRING_ALIGN_PAD) != 0; i++) {
		if (string[i] != '\0') return FALSE;
	}

	return true;

  //## end OSCInput::IsNiceString%1090452883.body
}

//## Operation: create%1090554363
//	Search For existing Input Drivers that Are Open. If not
//	already open, creates a new port and returns true. If
//	exists, returns true
bool OSCInput::create (int port)
{
  //## begin OSCInput::create%1090554363.body preserve=yes
  if (!port) return false;
  
  bool found = false;

  for (unsigned i = 0; i < _list_size && !found; i++)
  {
    found = _OscInList[i]->_port_num == port;
  }

  if (!found)
  {
    if (_list_size < MAX_OSC_IN_INPUTS)
    {
      OSCInput* pDriver = new OSCInput ();

      if (pDriver)
      {
        bool success = pDriver->open (port);
        if (success)
        {
          pDriver->start();
          _OscInList[_list_size] = pDriver;
          _list_size++;
          found = true;
        }
        else
        {
          printf ("Unable to Open UDP Port % u for OSC In\r\n", port);
          delete pDriver;
        }
      } // if(pDriver)
    }
    else
    {
      printf ("Unable to open more than %u ports for OSC Input\r\n", MAX_OSC_IN_INPUTS);
    }
  } // (!found && _list_size < MAX_OSC_IN_INPUTS)

  return found;
  //## end OSCInput::create%1090554363.body
}

//## Operation: closeall%1090554364
void OSCInput::closeall ()
{
  //## begin OSCInput::closeall%1090554364.body preserve=yes
  for (unsigned i = 0; i < _list_size; i++)
  {
    delete _OscInList[i];
  }

  _list_size = 0;

  //## end OSCInput::closeall%1090554364.body
}

// Additional Declarations
  //## begin OSCInput%40FEFD010122.declarations preserve=yes
  //## end OSCInput%40FEFD010122.declarations

//## begin module%40FEFD010122.epilog preserve=yes
//## end module%40FEFD010122.epilog
