//## begin module%3B43FDC2039D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B43FDC2039D.cm

//## begin module%3B43FDC2039D.cp preserve=no
//	Angelo Fraietta
//## end module%3B43FDC2039D.cp

//## Module: RtemsCommPort%3B43FDC2039D; Pseudo Package body
//## Subsystem: hal_rtems%3AEF6A0103BE
//## Source file: c:\develop\linkdriver\hal_rtems\rtemscommport.cpp

//## begin module%3B43FDC2039D.additionalIncludes preserve=no
#include "stdafx.h"
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <rtems.h>

//## end module%3B43FDC2039D.additionalIncludes

//## begin module%3B43FDC2039D.includes preserve=yes
//## end module%3B43FDC2039D.includes

// RtemsCommPort
#include "rtemscommport.h"
//## begin module%3B43FDC2039D.additionalDeclarations preserve=yes
//#define _DEBUG_LAYER


//## end module%3B43FDC2039D.additionalDeclarations


// Class RtemsCommPort 


RtemsCommPort::RtemsCommPort()
  //## begin RtemsCommPort::RtemsCommPort%.hasinit preserve=no
      : _file(-1)
  //## end RtemsCommPort::RtemsCommPort%.hasinit
  //## begin RtemsCommPort::RtemsCommPort%.initialization preserve=yes
  //## end RtemsCommPort::RtemsCommPort%.initialization
{
  //## begin RtemsCommPort::RtemsCommPort%.body preserve=yes
  //## end RtemsCommPort::RtemsCommPort%.body
}


RtemsCommPort::~RtemsCommPort()
{
  //## begin RtemsCommPort::~RtemsCommPort%.body preserve=yes
	Close();
  //## end RtemsCommPort::~RtemsCommPort%.body
}



//## Other Operations (implementation)
//## Operation: Open%994311832; C++
//	Opens the Comm port
bool RtemsCommPort::Open (const char* port_name, const char* port_settings)
{
  //## begin RtemsCommPort::Open%994311832.body preserve=yes
	bool ret = false;
	struct termios ts; // define a termios structure to modify in order to set the terminal parameters

	Close();
	_file = open (port_name, O_RDWR);

	if (_file >= 0)
		{
			ret = true;
			// let us set the terminal up
			tcgetattr(_file, &ts);
			ts.c_lflag &= ~(ICANON | ISIG | ECHO | ECHOE |ECHOK | ECHONL | ECHOPRT);
			ts.c_cc[VMIN] = 1;
			ts.c_cc[VTIME] = 0;
			ts.c_oflag &= ~OPOST;
			ts.c_iflag &= ~ICRNL;
			ts.c_iflag &= ~BRKINT;
			ts.c_iflag |= IGNBRK;
			ts.c_iflag &= ~CRTSCTS;
			ts.c_iflag &= ~(IXON | IXOFF | IXANY);

			tcsetattr(_file, TCSANOW, &ts);

			_isOpen = true;
			WriteBuffer ((const BYTE*)port_name, strlen (port_name)+1);
		}
	
	return ret;

  //## end RtemsCommPort::Open%994311832.body
}

//## Operation: Close%994311833; C++
//	Closes the Comm Port
void RtemsCommPort::Close ()
{
  //## begin RtemsCommPort::Close%994311833.body preserve=yes
	close(_file);
	_file = -1;
	_isOpen = false;
  //## end RtemsCommPort::Close%994311833.body
}

//## Operation: WriteBuffer%994311834; C++
//	Writes a buffer of Bytes to an open Port
bool RtemsCommPort::WriteBuffer (const BYTE* lpBuf, DWORD dwToWrite)
{
  //## begin RtemsCommPort::WriteBuffer%994311834.body preserve=yes
	bool ret = false;
	if(IsOpen())
		{
#ifdef _DEBUG_LAYER
			cout<<"write "<<dwToWrite<<" bytes"<<endl;
#endif

			ret = write  (_file, lpBuf, dwToWrite) == (long)dwToWrite;
#ifdef _DEBUG_LAYER
			cout<<"wrote "<<dwToWrite<<" bytes"<<endl;
#endif

		}

	
	return ret;
  //## end RtemsCommPort::WriteBuffer%994311834.body
}

//## Operation: GetDcdStatus%994311835; C++
//	returns the Data Carrier Detect status at the port
bool RtemsCommPort::GetDcdStatus ()
{
  //## begin RtemsCommPort::GetDcdStatus%994311835.body preserve=yes
	bool ret = false;

	return ret;
  //## end RtemsCommPort::GetDcdStatus%994311835.body
}

//## Operation: GetCtsStatus%994311836; C++
//	returns the Clear To Send status at the port
bool RtemsCommPort::GetCtsStatus ()
{
  //## begin RtemsCommPort::GetCtsStatus%994311836.body preserve=yes
	bool ret = false;

	return ret;
  //## end RtemsCommPort::GetCtsStatus%994311836.body
}

//## Operation: GetDsrStatus%994311837; C++
//	returns the Data Set Ready status at the port
bool RtemsCommPort::GetDsrStatus ()
{
  //## begin RtemsCommPort::GetDsrStatus%994311837.body preserve=yes
	bool ret = false;

	return ret;
  //## end RtemsCommPort::GetDsrStatus%994311837.body
}

//## Operation: GetRingStatus%994311838; C++
//	returns the Ring Detect status at the port
bool RtemsCommPort::GetRingStatus ()
{
  //## begin RtemsCommPort::GetRingStatus%994311838.body preserve=yes
	bool ret = false;

	return ret;
  //## end RtemsCommPort::GetRingStatus%994311838.body
}

//## Operation: SetDtrStatus%994311839
//	Sets the DTR status at the port
void RtemsCommPort::SetDtrStatus (bool status)
{
  //## begin RtemsCommPort::SetDtrStatus%994311839.body preserve=yes
  //## end RtemsCommPort::SetDtrStatus%994311839.body
}

//## Operation: SetRtsStatus%994311840
//	Sets the RTS status at the port
void RtemsCommPort::SetRtsStatus (bool status)
{
  //## begin RtemsCommPort::SetRtsStatus%994311840.body preserve=yes
  //## end RtemsCommPort::SetRtsStatus%994311840.body
}

//## Operation: ReadBuffer%994311841; C++
//	Reads a buffer of Bytes from a port
DWORD RtemsCommPort::ReadBuffer (BYTE* lpBuf, DWORD dwToRead, DWORD total_timeout, DWORD inter_char_timeout)
{
  //## begin RtemsCommPort::ReadBuffer%994311841.body preserve=yes
	int ret =  read (lpBuf, dwToRead);

	return ret;
  //## end RtemsCommPort::ReadBuffer%994311841.body
}

//## Operation: FlushBuffer%994311842; C++
//	Flushes the input read buffer of comm port
DWORD RtemsCommPort::FlushBuffer ()
{
  //## begin RtemsCommPort::FlushBuffer%994311842.body preserve=yes
	DWORD ret = 0;

	return ret;
  //## end RtemsCommPort::FlushBuffer%994311842.body
}

//## Operation: CharsInBuffer%994311843; C++
//	returns the number of characters in the buffer
DWORD RtemsCommPort::CharsInBuffer ()
{
  //## begin RtemsCommPort::CharsInBuffer%994311843.body preserve=yes
	DWORD ret = 0;

	return ret;
  //## end RtemsCommPort::CharsInBuffer%994311843.body
}

//## Operation: read%994311844; C++
DWORD RtemsCommPort::read (BYTE* lpBuf, DWORD dwToRead)
{
  //## begin RtemsCommPort::read%994311844.body preserve=yes
	DWORD ret =  ::read (_file, lpBuf, dwToRead);

	return ret;
  //## end RtemsCommPort::read%994311844.body
}

// Additional Declarations
  //## begin RtemsCommPort%3B43FDC2039D.declarations preserve=yes
  //## end RtemsCommPort%3B43FDC2039D.declarations

//## begin module%3B43FDC2039D.epilog preserve=yes
//## end module%3B43FDC2039D.epilog
