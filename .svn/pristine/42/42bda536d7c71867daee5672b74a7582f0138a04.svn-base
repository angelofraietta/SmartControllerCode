//## begin module%3B2560E002F0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B2560E002F0.cm

//## begin module%3B2560E002F0.cp preserve=no
//	Angelo Fraietta
//## end module%3B2560E002F0.cp

//## Module: WindowsThread%3B2560E002F0; Package body
//	Windows Implementation of ActiveObject and thread
//## Subsystem: hal_windows%3B255F1C012E
//## Source file: c:\develop\multithreads\source\hal_windows\windowsthread.cpp

//## begin module%3B2560E002F0.additionalIncludes preserve=no
#include <windows.h>
//## end module%3B2560E002F0.additionalIncludes

//## begin module%3B2560E002F0.includes preserve=yes
#include "activeobject.h"
//## end module%3B2560E002F0.includes

// MultiThread
#include "multithread.h"

class MacThread;
class WindowsThread;
class RtemsThread;

//## begin module%3B2560E002F0.declarations preserve=no
//## end module%3B2560E002F0.declarations

//## begin module%3B2560E002F0.additionalDeclarations preserve=yes
DWORD WINAPI ThreadEntry (void* pArg);
//## end module%3B2560E002F0.additionalDeclarations


//## begin WindowsThread%3B4A2B5F0022.preface preserve=yes
//## end WindowsThread%3B4A2B5F0022.preface

//## Class: WindowsThread%3B4A2B5F0022
//## Category: MultiThread::hal_windows%3B4A2D4D0375
//## Subsystem: hal_windows%3B255F1C012E
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class WindowsThread : public MultiThread  //## Inherits: <unnamed>%3B4A2B97002C
{
  //## begin WindowsThread%3B4A2B5F0022.initialDeclarations preserve=yes
  //## end WindowsThread%3B4A2B5F0022.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: WindowsThread%994716923
      WindowsThread (ActiveObject* pActive);

    //## Destructor (generated)
      ~WindowsThread();


    //## Other Operations (specified)
      //## Operation: resume%994716924
      void resume ();

      //## Operation: wait%994716925
      void wait (unsigned long period	// The period we are going to wait
      );

    // Additional Public Declarations
      //## begin WindowsThread%3B4A2B5F0022.public preserve=yes
      //## end WindowsThread%3B4A2B5F0022.public

  protected:
    // Additional Protected Declarations
      //## begin WindowsThread%3B4A2B5F0022.protected preserve=yes
      //## end WindowsThread%3B4A2B5F0022.protected

  private:
    // Additional Private Declarations
      //## begin WindowsThread%3B4A2B5F0022.private preserve=yes
      //## end WindowsThread%3B4A2B5F0022.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _handle%3B4A3178001C
      //## begin WindowsThread::_handle%3B4A3178001C.attr preserve=no  private: HANDLE {U} NULL
      HANDLE _handle;
      //## end WindowsThread::_handle%3B4A3178001C.attr

      //## Attribute: _thread_id%3B4A31930061
      //## begin WindowsThread::_thread_id%3B4A31930061.attr preserve=no  private: DWORD {U} 0
      DWORD _thread_id;
      //## end WindowsThread::_thread_id%3B4A31930061.attr

    // Additional Implementation Declarations
      //## begin WindowsThread%3B4A2B5F0022.implementation preserve=yes
      //## end WindowsThread%3B4A2B5F0022.implementation

};

//## begin WindowsThread%3B4A2B5F0022.postscript preserve=yes
//## end WindowsThread%3B4A2B5F0022.postscript

// Class WindowsThread 

// Class MultiThread 



//## Other Operations (implementation)
//## Operation: create%994716922
//	Static create function that returns the sub class,
//	depending upon the component
MultiThread* MultiThread::create (ActiveObject* pActive)
{
  //## begin MultiThread::create%994716922.body preserve=yes
	return new WindowsThread(pActive);
  //## end MultiThread::create%994716922.body
}

// Additional Declarations
  //## begin MultiThread%3B255966033E.declarations preserve=yes
  //## end MultiThread%3B255966033E.declarations

// Class WindowsThread 



//## Operation: WindowsThread%994716923
//	Constructor with parameter that points to ActiveObject
WindowsThread::WindowsThread (ActiveObject* pActive)
  //## begin WindowsThread::WindowsThread%994716923.hasinit preserve=no
      : _handle(NULL), _thread_id(0)
  //## end WindowsThread::WindowsThread%994716923.hasinit
  //## begin WindowsThread::WindowsThread%994716923.initialization preserve=yes
	,MultiThread (pActive)
  //## end WindowsThread::WindowsThread%994716923.initialization
{
  //## begin WindowsThread::WindowsThread%994716923.body preserve=yes
        _handle = CreateThread (
            0, // Security attributes
            0, // Stack size
            ThreadEntry, 
            pActive,
            CREATE_SUSPENDED, 
            &_thread_id);

  //## end WindowsThread::WindowsThread%994716923.body
}


WindowsThread::~WindowsThread()
{
  //## begin WindowsThread::~WindowsThread%.body preserve=yes
  CloseHandle (_handle);
  //## end WindowsThread::~WindowsThread%.body
}



//## Other Operations (implementation)
//## Operation: resume%994716924
void WindowsThread::resume ()
{
  //## begin WindowsThread::resume%994716924.body preserve=yes
  ResumeThread (_handle);
  //## end WindowsThread::resume%994716924.body
}

//## Operation: wait%994716925
//	Waits for the thread to finish
void WindowsThread::wait (unsigned long period)
{
  //## begin WindowsThread::wait%994716925.body preserve=yes
  WaitForSingleObject (_handle, period);
  //## end WindowsThread::wait%994716925.body
}

// Additional Declarations
  //## begin WindowsThread%3B4A2B5F0022.declarations preserve=yes
DWORD WINAPI ThreadEntry (void* pArg)
{
    ActiveObject * pActive = (ActiveObject *) pArg;
    pActive->initialise ();
    pActive->run ();
    return 0;
}

  //## end WindowsThread%3B4A2B5F0022.declarations
//## begin module%3B2560E002F0.epilog preserve=yes
//## end module%3B2560E002F0.epilog
