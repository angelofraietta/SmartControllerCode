//## begin module%3AE8ABD100D9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AE8ABD100D9.cm

//## begin module%3AE8ABD100D9.cp preserve=no
//	Angelo Fraietta
//## end module%3AE8ABD100D9.cp

//## Module: LinkProtocol%3AE8ABD100D9; Package body
//## Subsystem: link_driver%3D7412070347
//## Source file: c:\develop\Winsmartcontroller\controller\source\link_driver\linkprotocol.cpp

//## begin module%3AE8ABD100D9.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3AE8ABD100D9.additionalIncludes

//## begin module%3AE8ABD100D9.includes preserve=yes
#include <stddef.h>
//## end module%3AE8ABD100D9.includes

// LinkProtocol
#include "linkprotocol.h"
//## begin module%3AE8ABD100D9.declarations preserve=no
//## end module%3AE8ABD100D9.declarations

//## begin module%3AE8ABD100D9.additionalDeclarations preserve=yes
//## end module%3AE8ABD100D9.additionalDeclarations


// Class LinkProtocol 





//## begin LinkProtocol::_frame_chars%3AE8CEDC002F.attr preserve=no  private: static BYTE[] {U} {_stx, _etx}
BYTE LinkProtocol::_frame_chars[] = {_stx, _etx};
//## end LinkProtocol::_frame_chars%3AE8CEDC002F.attr

//## begin LinkProtocol::_stx%3AE8D51F028D.attr preserve=no  private: static BYTE {U} 0x01
BYTE LinkProtocol::_stx = 0x01;
//## end LinkProtocol::_stx%3AE8D51F028D.attr

//## begin LinkProtocol::_etx%3AE8FAE20201.attr preserve=no  private: static BYTE {U} 0x03
BYTE LinkProtocol::_etx = 0x03;
//## end LinkProtocol::_etx%3AE8FAE20201.attr







//## Operation: LinkProtocol%988323866
//	Constructor
LinkProtocol::LinkProtocol (BYTE* buf, unsigned max_size)
  //## begin LinkProtocol::LinkProtocol%988323866.hasinit preserve=no
      : _running_dle(false), _start_found(false),  _max_size(max_size), _buf(buf), _alloc_buf(NULL), _filter(_frame_chars, sizeof(_frame_chars)), _rxq(_buf, _max_size)
  //## end LinkProtocol::LinkProtocol%988323866.hasinit
  //## begin LinkProtocol::LinkProtocol%988323866.initialization preserve=yes
  //## end LinkProtocol::LinkProtocol%988323866.initialization
{
  //## begin LinkProtocol::LinkProtocol%988323866.body preserve=yes
	if (!_buf)
		{
			_alloc_buf = new BYTE [_max_size];
			_buf = _alloc_buf;
		}
  //## end LinkProtocol::LinkProtocol%988323866.body
}


LinkProtocol::~LinkProtocol()
{
  //## begin LinkProtocol::~LinkProtocol%.body preserve=yes
	delete [] _alloc_buf;
  //## end LinkProtocol::~LinkProtocol%.body
}



//## Other Operations (implementation)
//## Operation: EncodeData%988245429
//	Encodes data and prepares it for transmission
//## Preconditions:
//	target will be large enough to contain the data. This is
//	ensured by calling EncodeBufferSize before calling this
//	function
unsigned LinkProtocol::EncodeData (const BYTE* source, unsigned source_size, BYTE* target)
{
  //## begin LinkProtocol::EncodeData%988245429.body preserve=yes
  unsigned ret = 1; // we start at the char after _stx
  target[0] = _stx;

  for (unsigned i = 0; i < source_size; i++)
    {
      BYTE tmp = source [i];
      BYTE dle_char = _filter.Encode(&tmp);
      if (dle_char)
        {
          target [ret] = dle_char;
          ret++;
        }
      target [ret] = tmp;
      ret++;
    }
  target[ret] = _etx;
  ret++;
  return ret;

  //## end LinkProtocol::EncodeData%988245429.body
}

//## Operation: DecodeData%988245430
//	Decodes the data inputted as a source. If the data is
//	incomplete, the values are stored until valid. If
//	success is returned, the decoded Bytes are written into
//	tarrget
DecodeMessageType LinkProtocol::DecodeData (const BYTE* source, unsigned source_size)
{
  //## begin LinkProtocol::DecodeData%988245430.body preserve=yes
  DecodeMessageType  ret = DECODE_INCOMPLETE;
  unsigned s_index = 0; // the source buffer index

  if (source [0] == _stx)
  {
    reset();
  }
  
  if (!_start_found) // we will have to wait for _stx
    {
      while (!_start_found && s_index < source_size)
        {
          if (source [s_index] == _stx)
            {
              reset();
              _start_found = true;
              _running_dle = false;
            }
          s_index++; // we always have to go past the _stx
        }

    }

  // either _start found is true or we are past the max index

  while (s_index < source_size)
    {
      if (source[s_index] == _etx)
        {
          _start_found = false;
          ret = DECODE_SUCCESS;
          //reset();
        }
      else
        {
          BYTE tmp = source [s_index];
          if (_filter.Decode(&tmp, &_running_dle)) // then is a valid char
            {
              _rxq.push(tmp);
            }
        }
      s_index++;
    }
  return ret;
  //## end LinkProtocol::DecodeData%988245430.body
}

//## Operation: EncodeBufferSize%988323864
//	Returns the size of the buffer required to encode
//	requested data
unsigned LinkProtocol::EncodeBufferSize (const BYTE* source, unsigned source_size) const
{
  //## begin LinkProtocol::EncodeBufferSize%988323864.body preserve=yes
	unsigned ret = 2; // we need to add _stx and _etx
	for (unsigned i = 0; i < source_size; i++)
		{
			BYTE tmp = source [i];
			if (_filter.Encode(&tmp))
				{
					ret++;
				}
			ret++;
		}
	return ret;
  //## end LinkProtocol::EncodeBufferSize%988323864.body
}

//## Operation: reset%988323867
void LinkProtocol::reset ()
{
  //## begin LinkProtocol::reset%988323867.body preserve=yes
  _rxq.reset();
  _start_found = false;
  _running_dle = false;
  //## end LinkProtocol::reset%988323867.body
}

//## Operation: create%988756713
LinkProtocol* LinkProtocol::create (BYTE* buf, unsigned max_size)
{
  //## begin LinkProtocol::create%988756713.body preserve=yes
  return new LinkProtocol (buf, max_size);
  //## end LinkProtocol::create%988756713.body
}

//## Operation: decode_size%988756722
//	returns the size of the decoded data
unsigned LinkProtocol::decode_size () const
{
  return _rxq.size();

  //## begin LinkProtocol::decode_size%988756722.body preserve=yes
  //## end LinkProtocol::decode_size%988756722.body
}

//## Operation: decode_data%988756723
//	returns a pointer to the decode data
const BYTE* LinkProtocol::decode_data ()
{
  return _rxq.data();

  //## begin LinkProtocol::decode_data%988756723.body preserve=yes
  //## end LinkProtocol::decode_data%988756723.body
}

// Additional Declarations
  //## begin LinkProtocol%3AE7A56003C1.declarations preserve=yes
  //## end LinkProtocol%3AE7A56003C1.declarations

//## begin module%3AE8ABD100D9.epilog preserve=yes
//## end module%3AE8ABD100D9.epilog
