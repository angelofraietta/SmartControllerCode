//## begin module%3C58CFE20305.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C58CFE20305.cm

//## begin module%3C58CFE20305.cp preserve=no
//	Angelo Fraietta
//## end module%3C58CFE20305.cp

//## Module: WindowsEvent%3C58CFE20305; Package specification
//## Subsystem: hal_windows%3B255F1C012E
//## Source file: c:\develop\multithreads\source\hal_windows\windowsevent.h

#ifndef windowsevent_h
#define windowsevent_h 1

//## begin module%3C58CFE20305.additionalIncludes preserve=no
//## end module%3C58CFE20305.additionalIncludes

//## begin module%3C58CFE20305.includes preserve=yes
//## end module%3C58CFE20305.includes

// Event
#include "event.h"
//## begin module%3C58CFE20305.declarations preserve=no
//## end module%3C58CFE20305.declarations

//## begin module%3C58CFE20305.additionalDeclarations preserve=yes
//## end module%3C58CFE20305.additionalDeclarations


//## begin WindowsEvent%3C58CD1700D6.preface preserve=yes
//## end WindowsEvent%3C58CD1700D6.preface

//## Class: WindowsEvent%3C58CD1700D6
//## Category: MultiThread::hal_windows%3B4A2D4D0375
//## Subsystem: hal_windows%3B255F1C012E
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class WindowsEvent : public Event  //## Inherits: <unnamed>%3C58CD230047
{
  //## begin WindowsEvent%3C58CD1700D6.initialDeclarations preserve=yes
  //## end WindowsEvent%3C58CD1700D6.initialDeclarations

  public:
    //## Constructors (generated)
      WindowsEvent();

    //## Destructor (generated)
      ~WindowsEvent();


    //## Other Operations (specified)
      //## Operation: Wait%1012451968
      void Wait ();

      //## Operation: Release%1012451969
      void Release ();

    // Additional Public Declarations
      //## begin WindowsEvent%3C58CD1700D6.public preserve=yes
      //## end WindowsEvent%3C58CD1700D6.public

  protected:
    // Additional Protected Declarations
      //## begin WindowsEvent%3C58CD1700D6.protected preserve=yes
      //## end WindowsEvent%3C58CD1700D6.protected

  private:
    // Additional Private Declarations
      //## begin WindowsEvent%3C58CD1700D6.private preserve=yes
      //## end WindowsEvent%3C58CD1700D6.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _handle%3C58CF7902A0
      //## begin WindowsEvent::_handle%3C58CF7902A0.attr preserve=no  private: HANDLE {U} NULL
      HANDLE _handle;
      //## end WindowsEvent::_handle%3C58CF7902A0.attr

    // Additional Implementation Declarations
      //## begin WindowsEvent%3C58CD1700D6.implementation preserve=yes
      //## end WindowsEvent%3C58CD1700D6.implementation

};

//## begin WindowsEvent%3C58CD1700D6.postscript preserve=yes
//## end WindowsEvent%3C58CD1700D6.postscript

// Class WindowsEvent 

inline WindowsEvent::WindowsEvent()
  //## begin WindowsEvent::WindowsEvent%.hasinit preserve=no
      : _handle(NULL)
  //## end WindowsEvent::WindowsEvent%.hasinit
  //## begin WindowsEvent::WindowsEvent%.initialization preserve=yes
  //## end WindowsEvent::WindowsEvent%.initialization
{
  //## begin WindowsEvent::WindowsEvent%.body preserve=yes
	_handle = CreateEvent (0, FALSE, FALSE, 0);
  //## end WindowsEvent::WindowsEvent%.body
}


inline WindowsEvent::~WindowsEvent()
{
  //## begin WindowsEvent::~WindowsEvent%.body preserve=yes
	CloseHandle (_handle);
  //## end WindowsEvent::~WindowsEvent%.body
}



//## Other Operations (inline)
//## Operation: Wait%1012451968
inline void WindowsEvent::Wait ()
{
  WaitForSingleObject(_handle, INFINITE);

  //## begin WindowsEvent::Wait%1012451968.body preserve=yes
  //## end WindowsEvent::Wait%1012451968.body
}

//## Operation: Release%1012451969
inline void WindowsEvent::Release ()
{
  SetEvent (_handle); 

  //## begin WindowsEvent::Release%1012451969.body preserve=yes
  //## end WindowsEvent::Release%1012451969.body
}

//## begin module%3C58CFE20305.epilog preserve=yes
//## end module%3C58CFE20305.epilog


#endif
