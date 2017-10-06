//## begin module%3AEF6C4A012B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AEF6C4A012B.cm

//## begin module%3AEF6C4A012B.cp preserve=no
//	Angelo Fraietta
//## end module%3AEF6C4A012B.cp

//## Module: WindowsCommPort%3AEF6C4A012B; Package body
//	Windows Implementation of Comm Port
//## Subsystem: hal_windows%3AEF69F502F9
//	The windows implementation of the CommStream
//## Source file: c:\develop\linkdriver\hal_windows\windowscommport.cpp

//## begin module%3AEF6C4A012B.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3AEF6C4A012B.additionalIncludes

//## begin module%3AEF6C4A012B.includes preserve=yes
//## end module%3AEF6C4A012B.includes

// WindowsCommPort
#include "windowscommport.h"
//## begin module%3AEF6C4A012B.declarations preserve=no
//## end module%3AEF6C4A012B.declarations

//## begin module%3AEF6C4A012B.additionalDeclarations preserve=yes
#include <windows.h>
//## end module%3AEF6C4A012B.additionalDeclarations


// Class WindowsCommPort 


//## Operation: WindowsCommPort%988756721
//	constructor with a port name
WindowsCommPort::WindowsCommPort (const char* name)
  //## begin WindowsCommPort::WindowsCommPort%988756721.hasinit preserve=no
      : _handle(NULL)
  //## end WindowsCommPort::WindowsCommPort%988756721.hasinit
  //## begin WindowsCommPort::WindowsCommPort%988756721.initialization preserve=yes
  //## end WindowsCommPort::WindowsCommPort%988756721.initialization
{
  //## begin WindowsCommPort::WindowsCommPort%988756721.body preserve=yes
	if (name)
		{
			Open(name);
		}
  //## end WindowsCommPort::WindowsCommPort%988756721.body
}


WindowsCommPort::~WindowsCommPort()
{
  //## begin WindowsCommPort::~WindowsCommPort%.body preserve=yes
	if (IsOpen())
		{
		Close ();
		}

  //## end WindowsCommPort::~WindowsCommPort%.body
}



//## Other Operations (implementation)
//## Operation: GetTimeouts%-1144797312; C++
//	Gets the Comm Timeouts
bool WindowsCommPort::GetTimeouts (COMMTIMEOUTS& cto)
{
  //## begin WindowsCommPort::GetTimeouts%-1144797312.body preserve=yes
	return (::GetCommTimeouts (_handle, &cto));
  //## end WindowsCommPort::GetTimeouts%-1144797312.body
}

//## Operation: SetTimeouts%-1924942881; C++
//	Sets the Comm Timeouts
bool WindowsCommPort::SetTimeouts (COMMTIMEOUTS& cto)
{
  //## begin WindowsCommPort::SetTimeouts%-1924942881.body preserve=yes
	return (::GetCommTimeouts (_handle, &cto));
  //## end WindowsCommPort::SetTimeouts%-1924942881.body
}

//## Operation: SetDcb%1436041025; C++
//	Sets the DCB
bool WindowsCommPort::SetDcb (DCB& dcb)
{
  //## begin WindowsCommPort::SetDcb%1436041025.body preserve=yes
  if (dcb.Parity == NOPARITY)
    {
    dcb.fParity = 0;
    }
  else
    {
    dcb.fParity = 1;
    }

	return (::SetCommState (_handle, &dcb));

  //## end WindowsCommPort::SetDcb%1436041025.body
}

//## Operation: GetDcb%-1736609045; C++
//	Gets the DCB
bool WindowsCommPort::GetDcb (DCB* dcb)
{
  //## begin WindowsCommPort::GetDcb%-1736609045.body preserve=yes
  if (dcb->Parity == NOPARITY)
    {
    dcb->fParity = 0;
    }
  else
    {
    dcb->fParity = 1;
    }

	return (::SetCommState (_handle, dcb));
  //## end WindowsCommPort::GetDcb%-1736609045.body
}

//## Operation: Open%988245413; C++
//	Opens the Comm port
bool WindowsCommPort::Open (const char* port_name, const char* port_settings)
{
  //## begin WindowsCommPort::Open%988245413.body preserve=yes

  if (IsOpen())
  {
    Close();
  }
  
	DCB dcb;	       /* address of device-control block	*/
	bool result = true;
	const char default_channel_settings[] = "baud=9600 parity=N data=8 stop=1";
  const char* channelSettings = default_channel_settings;

	COMMTIMEOUTS commTimeouts = {MAXDWORD, 0, 0, 0, 0};

	if (port_settings)
		{
			channelSettings = port_settings;
		}

	_handle = ::CreateFile (port_name,
													GENERIC_READ | GENERIC_WRITE,
													0,
													0,
													OPEN_EXISTING,
													FILE_FLAG_OVERLAPPED,
													0);
	
	if (_handle == INVALID_HANDLE_VALUE)
		{
      result = false;
      _handle = NULL;
		}

	if (result)
		result = (::SetupComm (_handle, 1000, 1000));

	if (result)
		{
			::FillMemory (&dcb, sizeof (dcb), 0);
			dcb.DCBlength = sizeof (dcb);
			result = ::BuildCommDCB (channelSettings, &dcb);
		}

	dcb.fBinary = TRUE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fNull = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	dcb.fErrorChar = FALSE;
	dcb.fDsrSensitivity = FALSE;
	dcb.fRtsControl = RTS_CONTROL_ENABLE;			// default to raise RTS
	dcb.fDtrControl = DTR_CONTROL_ENABLE;     // raise DTR and leave ON
	
	if (result)
		result = ::SetCommState (_handle, &dcb);

	if (result)
		result = ::SetCommTimeouts (_handle, &commTimeouts);
	
	if (result)
		{
			_isOpen = true;
			_portName = port_name;
		}
	
	return (result);

  //## end WindowsCommPort::Open%988245413.body
}

//## Operation: Close%988245414; C++
//	Closes the Comm Port
void WindowsCommPort::Close ()
{
  //## begin WindowsCommPort::Close%988245414.body preserve=yes
 	if (IsOpen())
		{
    FlushBuffer();
		::CloseHandle (_handle);

		_isOpen = false;
		}

  //## end WindowsCommPort::Close%988245414.body
}

//## Operation: WriteBuffer%988245416; C++
//	Writes a buffer of Bytes to an open Port
bool WindowsCommPort::WriteBuffer (const BYTE* lpBuf, DWORD dwToWrite)
{
  //## begin WindowsCommPort::WriteBuffer%988245416.body preserve=yes
   OVERLAPPED osWrite = {0};
   DWORD dwWritten;
   BOOL  fRes = false;

	if (IsOpen())
		{
		// Create this write operation's OVERLAPPED structure hEvent.
		osWrite.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);

		if (osWrite.hEvent)
			{
			// Issue write
			if (!WriteFile (_handle, lpBuf, dwToWrite, &dwWritten, &osWrite))
				{
				if (GetLastError() != ERROR_IO_PENDING)
					{ 
					// WriteFile failed, but it isn't delayed. Report error.
					fRes = false;
					}
				else		// Write is pending.
					{
					if (WaitForSingleObject (osWrite.hEvent, INFINITE) == WAIT_OBJECT_0)
						{
						if (!GetOverlappedResult (_handle, &osWrite, &dwWritten, FALSE))
							fRes = false;
						else
							{
							if (dwWritten != dwToWrite)
								{
								// The write operation timed out. I now need to 
								// decide if I want to abort or retry. If I retry, 
								// I need to send only the bytes that weren't sent. 
								// If I want to abort, I would just set fRes to 
								// FALSE and return.
								fRes = FALSE;
								}
							else		// Write operation completed successfully.
								fRes = TRUE;
							}
						}	
					else            
						// An error has occurred in WaitForSingleObject. This usually 
						// indicates a problem with the overlapped event handle.
						fRes = FALSE;
					}
				}

			else		// WriteFile completed immediately, ret: TRUE
				{
				if (dwWritten != dwToWrite)
					{
					 // The write operation timed out. I now need to 
					 // decide if I want to abort or retry. If I retry, 
					 // I need to send only the bytes that weren't sent. 
					 // If I want to abort, then I would just set fRes to 
					 // FALSE and return.
					fRes = false;
					}
				else
					 fRes = true;
				}

			CloseHandle (osWrite.hEvent);
			}		// Error creating overlapped event handle.
		}			// if com port not open

	return fRes;

  //## end WindowsCommPort::WriteBuffer%988245416.body
}

//## Operation: GetDcdStatus%988245417; C++
//	returns the Data Carriaer Detect status at the port
bool WindowsCommPort::GetDcdStatus ()
{
  //## begin WindowsCommPort::GetDcdStatus%988245417.body preserve=yes
	bool ret = false;
	DWORD dwModemStatus;

	if (_isOpen)
		{
		if (GetCommModemStatus (_handle, &dwModemStatus))
			{
			if (MS_RLSD_ON & dwModemStatus)
				ret = true;
			}
		}

	return ret;

  //## end WindowsCommPort::GetDcdStatus%988245417.body
}

//## Operation: GetCtsStatus%988245418; C++
//	returns the Clear To Send status at the port
bool WindowsCommPort::GetCtsStatus ()
{
  //## begin WindowsCommPort::GetCtsStatus%988245418.body preserve=yes
	bool ret = false;
	DWORD dwModemStatus;

	if (_isOpen)
		{
		if (GetCommModemStatus (_handle, &dwModemStatus))
			{
			if (MS_CTS_ON & dwModemStatus)
				ret = true;
			}
		}

	return ret;

  //## end WindowsCommPort::GetCtsStatus%988245418.body
}

//## Operation: GetDsrStatus%988245419; C++
//	returns the Data Set Ready status at the port
bool WindowsCommPort::GetDsrStatus ()
{
  //## begin WindowsCommPort::GetDsrStatus%988245419.body preserve=yes
	bool ret = false;
	DWORD dwModemStatus;

	if (_isOpen)
		{
		if (GetCommModemStatus (_handle, &dwModemStatus))
			{
			if (MS_DSR_ON & dwModemStatus)
				ret = true;
			}
		}

	return ret;

  //## end WindowsCommPort::GetDsrStatus%988245419.body
}

//## Operation: GetRingStatus%988245420; C++
//	returns the Ring Detect status at the port
bool WindowsCommPort::GetRingStatus ()
{
  //## begin WindowsCommPort::GetRingStatus%988245420.body preserve=yes
	bool ret = false;
	DWORD dwModemStatus;

	if (_isOpen)
		{
		if (GetCommModemStatus (_handle, &dwModemStatus))
			{
			if (MS_RING_ON & dwModemStatus)
				ret = true;
			}
		}

	return ret;

  //## end WindowsCommPort::GetRingStatus%988245420.body
}

//## Operation: SetDtrStatus%988245421
//	Sets the DTR status at the port
void WindowsCommPort::SetDtrStatus (bool status)
{
  //## begin WindowsCommPort::SetDtrStatus%988245421.body preserve=yes
	if (IsOpen())
		{
			DCB dcb;
			GetDcb (&dcb);

			if (status)
				{
					dcb.fDtrControl = DTR_CONTROL_ENABLE;
				}
			else
				{
					dcb.fDtrControl = DTR_CONTROL_DISABLE;
				}
			SetDcb (dcb);
		}

  //## end WindowsCommPort::SetDtrStatus%988245421.body
}

//## Operation: SetRtsStatus%988245422
//	Sets the RTS status at the port
void WindowsCommPort::SetRtsStatus (bool status)
{
  //## begin WindowsCommPort::SetRtsStatus%988245422.body preserve=yes
	if (IsOpen())
		{
			DCB dcb;
			GetDcb (&dcb);

			if (status)
				{
					dcb.fRtsControl = RTS_CONTROL_ENABLE;
				}
			else
				{
					dcb.fRtsControl = RTS_CONTROL_DISABLE;
				}
			SetDcb (dcb);
		}

  //## end WindowsCommPort::SetRtsStatus%988245422.body
}

//## Operation: ReadBuffer%988245423; C++
//	Reads a buffer of Bytes from a port
DWORD WindowsCommPort::ReadBuffer (BYTE* lpBuf, DWORD dwToRead, DWORD total_timeout, DWORD inter_char_timeout)
{
  //## begin WindowsCommPort::ReadBuffer%988245423.body preserve=yes
	COMMTIMEOUTS new_cto, old_cto;
	ULONG bytes_read = 0L;

	if (IsOpen())
		{
		if (GetTimeouts (old_cto))
			{
			memcpy (&new_cto, &old_cto, sizeof (COMMTIMEOUTS));

			new_cto.ReadIntervalTimeout = inter_char_timeout;
			new_cto.ReadTotalTimeoutMultiplier = 1L;
			new_cto.ReadTotalTimeoutConstant = total_timeout;
			
			SetTimeouts (new_cto);

			bytes_read = read (lpBuf, dwToRead);

			SetTimeouts (old_cto);		// restore previous timeouts
			}
		}
	
	return (bytes_read);

  //## end WindowsCommPort::ReadBuffer%988245423.body
}

//## Operation: FlushBuffer%988245424; C++
//	Flushes the input read buffer of comm port
DWORD WindowsCommPort::FlushBuffer ()
{
  //## begin WindowsCommPort::FlushBuffer%988245424.body preserve=yes
	COMSTAT status;
	DWORD errors, bytes_read = 0L;
	char buffer [1000];

	if (IsOpen ())
		{
		if (ClearCommError (_handle, &errors, &status))	// get bytes in queue
			{
			if (status.cbInQue > 0)
				{
				if (status.cbInQue > sizeof (buffer))
					status.cbInQue = sizeof (buffer);

				ReadFile (_handle, buffer, status.cbInQue, &bytes_read, NULL);
				}											// read the bytes in queue
			}	
		}
	return ((USHORT) bytes_read);

  //## end WindowsCommPort::FlushBuffer%988245424.body
}

//## Operation: CharsInBuffer%988245425; C++
//	returns the number of characters in the buffer
DWORD WindowsCommPort::CharsInBuffer ()
{
  //## begin WindowsCommPort::CharsInBuffer%988245425.body preserve=yes
	COMSTAT status;
	DWORD errors, bytes_read = 0L;

	if (IsOpen ())
		{
		if (ClearCommError (_handle, &errors, &status))	// get bytes in queue
			{
			bytes_read = status.cbInQue;
			}	
		}
	return ((USHORT) bytes_read);

  //## end WindowsCommPort::CharsInBuffer%988245425.body
}

//## Operation: read%988245426; C++
DWORD WindowsCommPort::read (BYTE* lpBuf, DWORD dwToRead)
{
  //## begin WindowsCommPort::read%988245426.body preserve=yes
   OVERLAPPED osReader = {0};
   ULONG bytes_read = 0L;

	if (IsOpen ())
		{
		// Create this write operation's OVERLAPPED structure hEvent.
		osReader.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);

		if (osReader.hEvent != NULL)
			{
			// Issue write
			if (!ReadFile (_handle, lpBuf, dwToRead, &bytes_read, &osReader))
				{
				if (GetLastError() != ERROR_IO_PENDING)
					{ 
					// ReadFile failed, but it isn't delayed. Report error.
					bytes_read = 0L;
					}
				else		// Read is pending.
					{
					if (WaitForSingleObject (osReader.hEvent, INFINITE) == WAIT_OBJECT_0)
						{
						if (!GetOverlappedResult (_handle, &osReader, &bytes_read, FALSE))
							bytes_read = 0L;
						}	
					else            
						// An error has occurred in WaitForSingleObject. This usually 
						// indicates a problem with the overlapped event handle.
						bytes_read = 0L;
					}
				}

			CloseHandle (osReader.hEvent);
			}		// Error creating overlapped event handle.
		}			// if com port not open

	return (bytes_read);

  //## end WindowsCommPort::read%988245426.body
}

// Additional Declarations
  //## begin WindowsCommPort%3AE75EB7024E.declarations preserve=yes
  //## end WindowsCommPort%3AE75EB7024E.declarations

//## begin module%3AEF6C4A012B.epilog preserve=yes
//## end module%3AEF6C4A012B.epilog
