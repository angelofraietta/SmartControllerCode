//## begin module%3ACAAF0D00EE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ACAAF0D00EE.cm

//## begin module%3ACAAF0D00EE.cp preserve=no
//	Angelo Fraietta
//## end module%3ACAAF0D00EE.cp

//## Module: SessionAnswer%3ACAAF0D00EE; Package body
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: d:\develop\smartcontroller\controller\source\engineinterface\sessionanswer.cpp

//## begin module%3ACAAF0D00EE.additionalIncludes preserve=no
#include "stdafx.h"
#include "smutility.h"
//## end module%3ACAAF0D00EE.additionalIncludes

//## begin module%3ACAAF0D00EE.includes preserve=yes
#include <stdio.h>
#include <stddef.h>
#include "networklayer.h"
//## end module%3ACAAF0D00EE.includes

// SessionInterface
#include "sessioninterface.h"
// PresentationAnswer
#include "presentationanswer.h"

class NetworkLayer;

//## begin module%3ACAAF0D00EE.declarations preserve=no
//#define SHOW_DEBUG
//## end module%3ACAAF0D00EE.declarations

//## begin module%3ACAAF0D00EE.additionalDeclarations preserve=yes
//## end module%3ACAAF0D00EE.additionalDeclarations


// Class Utility SimulatorAnswer 

//## begin SimulatorAnswer::<the_SimulatorQuestion>%3AC272FD00B1.role preserve=no  public: SimulatorQuestion { -> RFH}
//## end SimulatorAnswer::<the_SimulatorQuestion>%3AC272FD00B1.role

//## begin SimulatorAnswer::_presentation%3AEE4E4E015C.role preserve=no  public: PresentationAnswer { -> 1VFHN}
PresentationAnswer SimulatorAnswer::_presentation;
//## end SimulatorAnswer::_presentation%3AEE4E4E015C.role


//## Other Operations (implementation)
//## Operation: GetAnswer%985819692
//	The single function with which all querries to the
//	Engine are sent and responded to from. The parameters
//	are passed in and out as a series of Null terminated
//	strings
bool SimulatorAnswer::GetAnswer (const BYTE* question, BYTE* ret_answer)
{
  //## begin SimulatorAnswer::GetAnswer%985819692.body preserve=yes
	const BYTE* cursor = question;
	unsigned ret_bytes = SMUtility::BufToInt(&cursor);

	return _presentation.GetAnswer (cursor, ret_answer, ret_bytes);

  //## end SimulatorAnswer::GetAnswer%985819692.body
}

// Additional Declarations
  //## begin SimulatorAnswer%3AC01654026F.declarations preserve=yes
  //## end SimulatorAnswer%3AC01654026F.declarations

// Class StreamedAnswer 





StreamedAnswer::StreamedAnswer()
  //## begin StreamedAnswer::StreamedAnswer%.hasinit preserve=no
      : _buf(NULL), _buf_size(0), _lower_layer(NULL)
  //## end StreamedAnswer::StreamedAnswer%.hasinit
  //## begin StreamedAnswer::StreamedAnswer%.initialization preserve=yes
  //## end StreamedAnswer::StreamedAnswer%.initialization
{
  //## begin StreamedAnswer::StreamedAnswer%.body preserve=yes
  //## end StreamedAnswer::StreamedAnswer%.body
}


StreamedAnswer::~StreamedAnswer()
{
  //## begin StreamedAnswer::~StreamedAnswer%.body preserve=yes
  if (_lower_layer)
  {
    delete  _lower_layer;
  }

  delete []_buf;
  //## end StreamedAnswer::~StreamedAnswer%.body
}



//## Other Operations (implementation)
//## Operation: GetQuestion%985819700
//	The single function with which all querries to the
//	Engine are sent and responded to from. Returns the
//	number of bytes in the question
unsigned StreamedAnswer::GetQuestion (const BYTE** question)
{
  //## begin StreamedAnswer::GetQuestion%985819700.body preserve=yes
  
	_lower_layer->ReadBuffer (_buf,  _buf_size);

#ifdef SHOW_DEBUG
	printf ("Streamed Answer ReadBuffer\r\n");
#endif

  const BYTE* cursor = _buf;
	unsigned ret_bytes = SMUtility::BufToInt(&cursor);

  // now assign the pointer to question
  *question = cursor;
  return ret_bytes;
  //## end StreamedAnswer::GetQuestion%985819700.body
}

//## Operation: open%985819701
//	Opens the lower layer device
bool StreamedAnswer::open (const char* name, DWORD port_speed, unsigned buf_size)
{
  //## begin StreamedAnswer::open%985819701.body preserve=yes
  _buf = new BYTE [buf_size];
  _buf_size = buf_size;
  
  _lower_layer = NetworkLayer::create(name, port_speed, _buf, buf_size);
  return (_lower_layer);
  //## end StreamedAnswer::open%985819701.body
}

//## Operation: SendAnswer%992232178
unsigned StreamedAnswer::SendAnswer (const BYTE* answer, unsigned answer_size)
{
  //## begin StreamedAnswer::SendAnswer%992232178.body preserve=yes
  return _lower_layer->WriteBuffer (answer, answer_size);
  //## end StreamedAnswer::SendAnswer%992232178.body
}

//## Operation: close%992232179
void StreamedAnswer::close ()
{
  //## begin StreamedAnswer::close%992232179.body preserve=yes
  //## end StreamedAnswer::close%992232179.body
}

//## Operation: SendRaw%1044915131
//	Send Raw Data to Comm port
unsigned StreamedAnswer::SendRaw (const BYTE* answer, unsigned answer_size)
{
  //## begin StreamedAnswer::SendRaw%1044915131.body preserve=yes
  return _lower_layer->WriteRaw (answer, answer_size);
  //## end StreamedAnswer::SendRaw%1044915131.body
}

// Additional Declarations
  //## begin StreamedAnswer%3AC0172700EC.declarations preserve=yes
  //## end StreamedAnswer%3AC0172700EC.declarations

//## begin module%3ACAAF0D00EE.epilog preserve=yes
//## end module%3ACAAF0D00EE.epilog
