//## begin module%3CF2B905003C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CF2B905003C.cm

//## begin module%3CF2B905003C.cp preserve=no
//	Angelo Fraietta
//## end module%3CF2B905003C.cp

//## Module: SysexFileQuestion%3CF2B905003C; Pseudo Package body
//## Subsystem: engineinterface%3A9C858C00CB
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\sysexfilequestion.cpp

//## begin module%3CF2B905003C.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3CF2B905003C.additionalIncludes

//## begin module%3CF2B905003C.includes preserve=yes
#include "mididrv.h"
#include "linkprotocol.h"
//## end module%3CF2B905003C.includes

// SysexFileQuestion
#include "sysexfilequestion.h"
//## begin module%3CF2B905003C.additionalDeclarations preserve=yes
//## end module%3CF2B905003C.additionalDeclarations


// Class SysexFileQuestion 



SysexFileQuestion::SysexFileQuestion()
  //## begin SysexFileQuestion::SysexFileQuestion%.hasinit preserve=no
      : _fp(NULL)
  //## end SysexFileQuestion::SysexFileQuestion%.hasinit
  //## begin SysexFileQuestion::SysexFileQuestion%.initialization preserve=yes
  //## end SysexFileQuestion::SysexFileQuestion%.initialization
{
  //## begin SysexFileQuestion::SysexFileQuestion%.body preserve=yes
  //## end SysexFileQuestion::SysexFileQuestion%.body
}


SysexFileQuestion::~SysexFileQuestion()
{
  //## begin SysexFileQuestion::~SysexFileQuestion%.body preserve=yes
  close();
  //## end SysexFileQuestion::~SysexFileQuestion%.body
}



//## Other Operations (implementation)
//## Operation: AskQuestion%1022540280
//	The single function with which all querries to the
//	Engine are sent and responded to from. The parameters
//	are passed in and out as a series of Null terminated
//	strings. The function returns true ff the reply was
//	successful.
bool SysexFileQuestion::AskQuestion (const BYTE* question, unsigned q_size, BYTE* ret_answer, unsigned r_size, unsigned timeout)
{
  //## begin SysexFileQuestion::AskQuestion%1022540280.body preserve=yes

  if (_fp)
  {
    BYTE sysex_header [] = {0xF0, 0x7D, 0x01};
    BYTE sysex_tail = 0xf7;
    unsigned link_size = _encoder.EncodeBufferSize(question, q_size);
    BYTE* link_tx = new BYTE [link_size];

    _encoder.EncodeData(question, q_size, link_tx);

    // first write the sysyex header
    fwrite (&sysex_header[0], sizeof(sysex_header), 1, _fp);

    // write the link data
    for(unsigned i = 0; i < link_size; i++)
    {
      BYTE link_byte =  link_tx[i];
      BYTE dle = EncodeMidiByte(&link_byte);

      if (dle)
      {
        fwrite (&dle, 1, 1, _fp);
      }

      fwrite (&link_byte, 1, 1, _fp);
    }
    delete [] link_tx;

    // now write end sysex
    fwrite (&sysex_tail, 1, 1, _fp);
  }
  return false;
  //## end SysexFileQuestion::AskQuestion%1022540280.body
}

//## Operation: open%1022540281
//	Opens the lower layer device
bool SysexFileQuestion::open (const char* file_name)
{
  //## begin SysexFileQuestion::open%1022540281.body preserve=yes
  close();
  _fp = fopen(file_name, "w+b");
  return (_fp);
  //## end SysexFileQuestion::open%1022540281.body
}

//## Operation: close%1022540282
//	Closes the open file
void SysexFileQuestion::close ()
{
  if (_fp)
    fclose(_fp);
  
  _fp = NULL;


  //## begin SysexFileQuestion::close%1022540282.body preserve=yes
  //## end SysexFileQuestion::close%1022540282.body
}

// Additional Declarations
  //## begin SysexFileQuestion%3CF2B905003C.declarations preserve=yes
  //## end SysexFileQuestion%3CF2B905003C.declarations

//## begin module%3CF2B905003C.epilog preserve=yes
//## end module%3CF2B905003C.epilog
