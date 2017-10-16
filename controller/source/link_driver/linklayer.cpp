//## begin module%3AEF67BA0167.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AEF67BA0167.cm

//## begin module%3AEF67BA0167.cp preserve=no
//	Angelo Fraietta
//## end module%3AEF67BA0167.cp

//## Module: LinkLayer%3AEF67BA0167; Pseudo Package body
//## Subsystem: link_driver%3D7412070347
//## Source file: D:\develop\Smartcontroller\controller\source\link_driver\linklayer.cpp

//## begin module%3AEF67BA0167.additionalIncludes preserve=no
//## end module%3AEF67BA0167.additionalIncludes

//## begin module%3AEF67BA0167.includes preserve=yes
#ifdef BUILDER
#include "stdafx.h"
#else
#include "estring.h"
using sm_str::string;
#endif

#include <stddef.h>
#include "typedefs.h"
#include "udpport.h"
// LinkProtocol
#include "linkprotocol.h"
// CommStream
#include "commstream.h"


//## end module%3AEF67BA0167.includes

// LinkLayer
#include "linklayer.h"
//## begin module%3AEF67BA0167.additionalDeclarations preserve=yes
//#define SHOW_DEBUG
//#define _DEBUG_LAYER
//## end module%3AEF67BA0167.additionalDeclarations


// Class LinkLayer 





//## Operation: LinkLayer%988756716
LinkLayer::LinkLayer (const char* port_name, unsigned char* buf, unsigned max_size)
  //## begin LinkLayer::LinkLayer%988756716.hasinit preserve=no
      : _flush(false), _encoder(NULL), _stream(NULL)
  //## end LinkLayer::LinkLayer%988756716.hasinit
  //## begin LinkLayer::LinkLayer%988756716.initialization preserve=yes
  //## end LinkLayer::LinkLayer%988756716.initialization
{
  //## begin LinkLayer::LinkLayer%988756716.body preserve=yes
	_encoder = LinkProtocol::create(buf, max_size);
  _stream = CommStream::create (port_name);

  //## end LinkLayer::LinkLayer%988756716.body
}


LinkLayer::~LinkLayer()
{
  //## begin LinkLayer::~LinkLayer%.body preserve=yes
  if (_stream)
  {
    _stream->Close();
  }

  delete _encoder;
  delete _stream;
  //## end LinkLayer::~LinkLayer%.body
}



//## Other Operations (implementation)
//## Operation: WriteBuffer%988756717; C++
//	Writes a buffer of Bytes to an open Port
bool LinkLayer::WriteBuffer (const unsigned char* lpBuf, unsigned long dwToWrite)
{
  //## begin LinkLayer::WriteBuffer%988756717.body preserve=yes

	const unsigned num_tx_bytes  = _encoder->EncodeBufferSize(lpBuf, dwToWrite);
	_encoder->EncodeData (lpBuf, dwToWrite, (BYTE*)_tx_buf);

#ifdef _DEBUG_LAYER
	cout<<"write "<<num_tx_bytes<<" bytes"<<endl;
#endif

	bool success =_stream->WriteBuffer ((const BYTE*) _tx_buf, num_tx_bytes);
#ifdef _DEBUG_LAYER
	cout<<"complete writeBufer"<<endl;
#endif

	return success;

  //## end LinkLayer::WriteBuffer%988756717.body
}

//## Operation: ReadBuffer%988756718; C++
//	Reads a buffer of Bytes from a port
unsigned long LinkLayer::ReadBuffer (unsigned  char* lpBuf, unsigned long dwToRead)
{
  //## begin LinkLayer::ReadBuffer%988756718.body preserve=yes
  bool found = false;
  _encoder->reset();
  DWORD bytes_read = 0;

  if (_stream->IsOpen())
  {
#ifdef SHOW_DEBUG
		cout<< "Link wait"<<endl;
#endif

    do
    {
      BYTE c; // this is the char we will read
      if (_stream->ReadBuffer(&c, 1) == 1) // read one char
      {
          unsigned result = _encoder->DecodeData (&c, 1);
          if (result == DECODE_SUCCESS)
            {
              found = true;
#ifdef SHOW_DEBUG
							cout<< "Link found"<<endl;
#endif

            }

      }
#ifdef SHOW_DEBUG
			else
				{
					cout<< "Byte not read"<<endl;
				}
#endif

    } while (!found && !_flush);

    if (found)
    {
      bytes_read = _encoder->decode_size();
      if (bytes_read <= dwToRead)
      {
        memcpy (lpBuf, _encoder->decode_data(), bytes_read);
      }
      else
      {
        bytes_read = 0;
      }
    }
  }

  return bytes_read;
  
  
  //## end LinkLayer::ReadBuffer%988756718.body
}

//## Operation: create%988756719
//	Interface for creating a link layer
LinkLayer* LinkLayer::create (const char* port_name, unsigned char* buf, unsigned max_size)
{
  //## begin LinkLayer::create%988756719.body preserve=yes


  return new LinkLayer (port_name, buf, max_size);
  //## end LinkLayer::create%988756719.body
}

//## Operation: reset%988756720
void LinkLayer::reset ()
{
  //## begin LinkLayer::reset%988756720.body preserve=yes
  _flush = false;
  //## end LinkLayer::reset%988756720.body
}

//## Operation: flush%1030333279
//	Flushes the input buffer
void LinkLayer::flush ()
{
  //## begin LinkLayer::flush%1030333279.body preserve=yes
  _flush = true;

  if (_stream)
  {
    _stream->FlushBuffer();
  }

  //## end LinkLayer::flush%1030333279.body
}

//## Operation: WriteRaw%1044915129; C++
//	Writes a Raw buffer of Bytes to an open Port
bool LinkLayer::WriteRaw (const unsigned char* lpBuf, unsigned long dwToWrite)
{
  //## begin LinkLayer::WriteRaw%1044915129.body preserve=yes
	bool success =_stream->WriteBuffer ((const BYTE*) lpBuf, dwToWrite);

	return success;
  //## end LinkLayer::WriteRaw%1044915129.body
}

//## Operation: Open%1081798840; C++
//	Opens the Comm port
bool LinkLayer::Open (const char* port_name, const char* port_settings)
{
  //## begin LinkLayer::Open%1081798840.body preserve=yes
  return false;
  //## end LinkLayer::Open%1081798840.body
}

// Additional Declarations
  //## begin LinkLayer%3AEF67BA0167.declarations preserve=yes
  //## end LinkLayer%3AEF67BA0167.declarations

//## begin module%3AEF67BA0167.epilog preserve=yes
//## end module%3AEF67BA0167.epilog
