//## begin module%3AC3CE0C0201.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AC3CE0C0201.cm

//## begin module%3AC3CE0C0201.cp preserve=no
//	Angelo Fraietta
//## end module%3AC3CE0C0201.cp

//## Module: SessionQuestion%3AC3CE0C0201; Package body
//	Implementation of presentation question and answer
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: d:\develop\smartcontroller\controller\source\engineinterface\sessionquestion.cpp

//## begin module%3AC3CE0C0201.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3AC3CE0C0201.additionalIncludes

//## begin module%3AC3CE0C0201.includes preserve=yes
#include "sysexfilequestion.h"
#include "questiontask.h"
#include "networklayer.h"
//## end module%3AC3CE0C0201.includes

// SimulatorInterface
#include "simulatorinterface.h"
// SessionInterface
#include "sessioninterface.h"

class SMUtility;

//## begin module%3AC3CE0C0201.declarations preserve=no
//## end module%3AC3CE0C0201.declarations

//## begin module%3AC3CE0C0201.additionalDeclarations preserve=yes
//## end module%3AC3CE0C0201.additionalDeclarations


// Class SessionQuestion 

//## begin SessionQuestion::simulator_name%3AC3EAF30387.attr preserve=no  public: static const char*const {V} "simulator"
const char*const SessionQuestion::simulator_name = "simulator";
//## end SessionQuestion::simulator_name%3AC3EAF30387.attr



//## Other Operations (implementation)
//## Operation: create%985819688
SessionQuestion* SessionQuestion::create (const char* name, DWORD port_speed)
{
  //## begin SessionQuestion::create%985819688.body preserve=yes
	SessionQuestion* question;

	if (!strcmp (simulator_name, name))
		{
			question = new SimulatorQuestion();
			((SimulatorQuestion*)question)->initialise();

		}
	else
		{
			question = new StreamedQuestion();
			if (!((StreamedQuestion*)question)->open (name, port_speed))  
				{
					delete question;
					question = NULL;
				}
		}

	return question;

  //## end SessionQuestion::create%985819688.body
}

//## Operation: destroy%985819711
void SessionQuestion::destroy (SessionQuestion* pLayer)
{
  //## begin SessionQuestion::destroy%985819711.body preserve=yes
	delete pLayer;
  //## end SessionQuestion::destroy%985819711.body
}

//## Operation: createfile%1022540283
SessionQuestion* SessionQuestion::createfile (const char* file_name)
{
  //## begin SessionQuestion::createfile%1022540283.body preserve=yes
  SysexFileQuestion* new_session = new SysexFileQuestion;

  if (!new_session->open(file_name))
  {
    delete new_session;
  }

  return new_session;

  //## end SessionQuestion::createfile%1022540283.body
}

// Additional Declarations
  //## begin SessionQuestion%3AA8170C00F6.declarations preserve=yes
  //## end SessionQuestion%3AA8170C00F6.declarations

// Class SimulatorQuestion 



//## Other Operations (implementation)
//## Operation: initialise%985819710
//	opens the
bool SimulatorQuestion::initialise ()
{
  //## begin SimulatorQuestion::initialise%985819710.body preserve=yes
  return true;
  //## end SimulatorQuestion::initialise%985819710.body
}

//## Operation: AskQuestion%985819712
//	The single function with which all querries to the
//	Engine are sent and responded to from. The parameters
//	are passed in and out as a series of Null terminated
//	strings. The function returns true ff the reply was
//	successful.
bool SimulatorQuestion::AskQuestion (const BYTE* question, unsigned q_size, BYTE* ret_answer, unsigned r_size, unsigned timeout)
{
  //## begin SimulatorQuestion::AskQuestion%985819712.body preserve=yes
	return SimulatorGetAnswer (question, ret_answer);
  //## end SimulatorQuestion::AskQuestion%985819712.body
}

// Additional Declarations
  //## begin SimulatorQuestion%3AC0144D0183.declarations preserve=yes
  //## end SimulatorQuestion%3AC0144D0183.declarations

// Class StreamedQuestion 






StreamedQuestion::StreamedQuestion()
  //## begin StreamedQuestion::StreamedQuestion%.hasinit preserve=no
      : _bytes_read(0), _pThread(new QuestionTask(this)), _lower_layer(NULL)
  //## end StreamedQuestion::StreamedQuestion%.hasinit
  //## begin StreamedQuestion::StreamedQuestion%.initialization preserve=yes
  //## end StreamedQuestion::StreamedQuestion%.initialization
{
  //## begin StreamedQuestion::StreamedQuestion%.body preserve=yes
  //## end StreamedQuestion::StreamedQuestion%.body
}


StreamedQuestion::~StreamedQuestion()
{
  //## begin StreamedQuestion::~StreamedQuestion%.body preserve=yes
  _pThread->kill();
  if (_lower_layer)
  {
    delete  _lower_layer;
  }

  delete _pThread;
  //## end StreamedQuestion::~StreamedQuestion%.body
}



//## Other Operations (implementation)
//## Operation: open%985819699
//	Opens the lower layer device
bool StreamedQuestion::open (const char* dev_name, DWORD port_speed)
{
  //## begin StreamedQuestion::open%985819699.body preserve=yes
  _lower_layer = NetworkLayer::create(dev_name, port_speed);
  _pThread->start();
  return (_lower_layer);
  //## end StreamedQuestion::open%985819699.body
}

//## Operation: AskQuestion%985819713
//	The single function with which all querries to the
//	Engine are sent and responded to from. The parameters
//	are passed in and out as a series of Null terminated
//	strings. The function returns true ff the reply was
//	successful.
bool StreamedQuestion::AskQuestion (const BYTE* question, unsigned q_size, BYTE* ret_answer, unsigned r_size, unsigned timeout)
{
  //## begin StreamedQuestion::AskQuestion%985819713.body preserve=yes
  bool ret = false;

  _return_result = false;

  _bytes_read = r_size;
  _answer_buf = ret_answer;

  if (_lower_layer)
  {
    _lower_layer->reset();
    if (_lower_layer->WriteBuffer (question, q_size))
    {
      // start the waucth dog
      _pThread->go(timeout);
      ret = GetAnswer();
      _pThread->wait();
      // let dog know we have finished
    }
    else
    {
      printf ("Unable to Write To Lower Layer\r\n");
    }
  }
  return ret;
  //## end StreamedQuestion::AskQuestion%985819713.body
}

//## Operation: GetAnswer%1023147568
bool StreamedQuestion::GetAnswer ()
{
  //## begin StreamedQuestion::GetAnswer%1023147568.body preserve=yes
  unsigned bytes_to_read = _bytes_read;
  _return_result = false;
  unsigned char read_buf [4096];

  _bytes_read = _lower_layer->ReadBuffer (read_buf,  sizeof(read_buf));

  memcpy(_answer_buf,read_buf, bytes_to_read);

  //_bytes_read = _lower_layer->ReadBuffer (_answer_buf,  bytes_to_read);
  _return_result = bytes_to_read >= _bytes_read;

  return _return_result;
  //## end StreamedQuestion::GetAnswer%1023147568.body
}

//## Operation: SetInterfaceAddress%1082670127
//	Sets the Interface address of network Layer
bool StreamedQuestion::SetInterfaceAddress (const char* address)
{
  //## begin StreamedQuestion::SetInterfaceAddress%1082670127.body preserve=yes
  return _lower_layer->SetTo(address);
  //## end StreamedQuestion::SetInterfaceAddress%1082670127.body
}

//## Operation: Flush%1083901316
void StreamedQuestion::Flush ()
{
  //## begin StreamedQuestion::Flush%1083901316.body preserve=yes
  if (_lower_layer)
  {
    _lower_layer->flush();
  }
  //## end StreamedQuestion::Flush%1083901316.body
}

// Additional Declarations
  //## begin StreamedQuestion%3AC015A10069.declarations preserve=yes
  //## end StreamedQuestion%3AC015A10069.declarations

//## begin module%3AC3CE0C0201.epilog preserve=yes
//## end module%3AC3CE0C0201.epilog
