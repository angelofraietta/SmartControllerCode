//## begin module%3CF1B0700221.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CF1B0700221.cm

//## begin module%3CF1B0700221.cp preserve=no
//	Angelo Fraietta
//## end module%3CF1B0700221.cp

//## Module: SysexDriver%3CF1B0700221; Pseudo Package body
//## Subsystem: engine%39F51CB901B8
//## Source file: c:\develop\Winsmartcontroller\controller\source\engine\sysexdriver.cpp

//## begin module%3CF1B0700221.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3CF1B0700221.additionalIncludes

//## begin module%3CF1B0700221.includes preserve=yes
#include <stddef.h>
#include "typedefs.h"
#include "mididrv.h"
#include "smutility.h"
//## end module%3CF1B0700221.includes

// SysexDriver
#include "sysexdriver.h"
// LinkProtocol
#include "linkprotocol.h"
//## begin module%3CF1B0700221.additionalDeclarations preserve=yes
//#define SHOW_DEBUG

//## end module%3CF1B0700221.additionalDeclarations


// Class SysexDriver 



//## begin SysexDriver::_sysex_header%3CF1B8AA019D.attr preserve=no  private: static char[] {U} {0x7D, 0x01}
char SysexDriver::_sysex_header[] = {0x7D, 0x01};
//## end SysexDriver::_sysex_header%3CF1B8AA019D.attr






SysexDriver::SysexDriver()
  //## begin SysexDriver::SysexDriver%.hasinit preserve=no
      : _dle(0), _byte_num(0), _our_sysex(true), _link_layer(new LinkProtocol (_rx_buf, sizeof(_rx_buf)))
  //## end SysexDriver::SysexDriver%.hasinit
  //## begin SysexDriver::SysexDriver%.initialization preserve=yes
  //## end SysexDriver::SysexDriver%.initialization
{
  //## begin SysexDriver::SysexDriver%.body preserve=yes
  //## end SysexDriver::SysexDriver%.body
}



//## Other Operations (implementation)
//## Operation: Reset%1022473326
//	Clears DLE
void SysexDriver::Reset ()
{
  //## begin SysexDriver::Reset%1022473326.body preserve=yes
  _dle = 0;
  _byte_num = 0;
  _our_sysex = true;
  _link_layer->reset();
  //## end SysexDriver::Reset%1022473326.body
}

//## Operation: ProcessByte%1022473327
void SysexDriver::ProcessByte (char data)
{
  //## begin SysexDriver::ProcessByte%1022473327.body preserve=yes

	if (_byte_num < sizeof(_sysex_header))
  {
  	_our_sysex &= (data == _sysex_header[_byte_num]);
	}
  
  if (_our_sysex)
  {

  	if (_byte_num >= sizeof(_sysex_header))
    {
   	ProcessOurSysex(data);
    }

  }
  else
  {
#ifdef SHOW_DEBUG
		cout <<"Sysex Driver->Process other Sysex"<<endl;
#endif

		ProcessOtherSysex(data);
  }

  _byte_num++;
  //## end SysexDriver::ProcessByte%1022473327.body
}

//## Operation: ProcessOurSysex%1022473328
void SysexDriver::ProcessOurSysex (char data)
{
  //## begin SysexDriver::ProcessOurSysex%1022473328.body preserve=yes
  BYTE c = (BYTE)data; // make a BYTE for the compiler

  if (DecodeMidiByte(&_dle, &c))
  {
#ifdef SHOW_DEBUG
		cout <<"Sysex Driver->Byte decoded"<<endl;
#endif

    if (_link_layer->DecodeData (&c, 1) == DECODE_SUCCESS)
      {
				BYTE buf[256];
#ifdef SHOW_DEBUG
				cout <<"Sysex Driver->Link Driver Success"<<endl;
#endif

			const BYTE* cursor = _link_layer->decode_data();
			unsigned ret_bytes = SMUtility::BufToInt(&cursor);

      unsigned bytes_to_write =  _controller.GetAnswer(cursor, buf, ret_bytes);
      }
  }
  //## end SysexDriver::ProcessOurSysex%1022473328.body
}

//## Operation: ProcessOtherSysex%1022473329
void SysexDriver::ProcessOtherSysex (char data)
{
  //## begin SysexDriver::ProcessOtherSysex%1022473329.body preserve=yes
  UNREFERENCED_PARAMETER(data);
  //## end SysexDriver::ProcessOtherSysex%1022473329.body
}

// Additional Declarations
  //## begin SysexDriver%3CF1B0700221.declarations preserve=yes
  //## end SysexDriver%3CF1B0700221.declarations

//## begin module%3CF1B0700221.epilog preserve=yes
//## end module%3CF1B0700221.epilog
