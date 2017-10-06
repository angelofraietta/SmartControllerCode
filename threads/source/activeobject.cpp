//## begin module%3B25578F0192.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B25578F0192.cm

//## begin module%3B25578F0192.cp preserve=no
//	Angelo Fraietta
//## end module%3B25578F0192.cp

//## Module: ActiveObject%3B25578F0192; Pseudo Package body
//## Subsystem: <Top Level>
//## Source file: c:\develop\multithreads\source\activeobject.cpp

//## begin module%3B25578F0192.additionalIncludes preserve=no
//## end module%3B25578F0192.additionalIncludes

//## begin module%3B25578F0192.includes preserve=yes
//## end module%3B25578F0192.includes

// MultiThread
#include "multithread.h"
// ActiveObject
#include "activeobject.h"
//## begin module%3B25578F0192.additionalDeclarations preserve=yes
//## end module%3B25578F0192.additionalDeclarations


// Class ActiveObject 




ActiveObject::ActiveObject()
  //## begin ActiveObject::ActiveObject%.hasinit preserve=no
      : _started(false), _terminate(false), _pThread(MultiThread::create (this))
  //## end ActiveObject::ActiveObject%.hasinit
  //## begin ActiveObject::ActiveObject%.initialization preserve=yes
  //## end ActiveObject::ActiveObject%.initialization
{
  //## begin ActiveObject::ActiveObject%.body preserve=yes
  //## end ActiveObject::ActiveObject%.body
}


ActiveObject::~ActiveObject()
{
  //## begin ActiveObject::~ActiveObject%.body preserve=yes
	delete _pThread;
  //## end ActiveObject::~ActiveObject%.body
}



//## Other Operations (implementation)
//## Operation: initialise%992298018
void ActiveObject::initialise ()
{
  //## begin ActiveObject::initialise%992298018.body preserve=yes
  //## end ActiveObject::initialise%992298018.body
}

//## Operation: start%992298021
//	Starts the thread giong
void ActiveObject::start ()
{
  if (!_started)
  {
    _pThread->resume();
    _started = true;
  }

  //## begin ActiveObject::start%992298021.body preserve=yes
  //## end ActiveObject::start%992298021.body
}

//## Operation: kill%992298025
//	Tells Superclass to finish and kills the thread. We wait
//	2000 for the thread to exit before we return
void ActiveObject::kill ()
{
  _terminate = true;
  flush();
  _pThread->wait(2000);

  //## begin ActiveObject::kill%992298025.body preserve=yes
  //## end ActiveObject::kill%992298025.body
}

// Additional Declarations
  //## begin ActiveObject%3B25578F0192.declarations preserve=yes
  //## end ActiveObject%3B25578F0192.declarations

//## begin module%3B25578F0192.epilog preserve=yes
//## end module%3B25578F0192.epilog
