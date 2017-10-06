//## begin module%3C5A067C0099.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C5A067C0099.cm

//## begin module%3C5A067C0099.cp preserve=no
//	Angelo Fraietta
//## end module%3C5A067C0099.cp

//## Module: RtemsEvent%3C5A067C0099; Package body
//## Subsystem: hal_rtems%3B255F2C0271
//## Source file: c:\develop\multithreads\source\hal_rtems\rtemsevent.cpp

//## begin module%3C5A067C0099.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3C5A067C0099.additionalIncludes

//## begin module%3C5A067C0099.includes preserve=yes
#include <rtems.h>

//## end module%3C5A067C0099.includes

// Event
#include "event.h"
//## begin module%3C5A067C0099.declarations preserve=no
//## end module%3C5A067C0099.declarations

//## begin module%3C5A067C0099.additionalDeclarations preserve=yes
#define RTEMS_EVENT_EVENT_FLAG RTEMS_EVENT_0

//#define CONSOLE_DEBUG

//## end module%3C5A067C0099.additionalDeclarations


//## begin RtemsEvent%3C58CD2A01B0.preface preserve=yes
//## end RtemsEvent%3C58CD2A01B0.preface

//## Class: RtemsEvent%3C58CD2A01B0
//## Category: MultiThread::hal_rtems%3B4A2D6C0207
//## Subsystem: hal_rtems%3B255F2C0271
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class RtemsEvent : public Event  //## Inherits: <unnamed>%3C58CD3501B6
{
  //## begin RtemsEvent%3C58CD2A01B0.initialDeclarations preserve=yes
  //## end RtemsEvent%3C58CD2A01B0.initialDeclarations

  public:
    //## Constructors (generated)
      RtemsEvent();

    //## Destructor (generated)
      ~RtemsEvent();


    //## Other Operations (specified)
      //## Operation: Wait%1012532982
      bool Wait (int timeout = -1);

      //## Operation: Release%1012532983
      void Release ();

    // Additional Public Declarations
      //## begin RtemsEvent%3C58CD2A01B0.public preserve=yes
      //## end RtemsEvent%3C58CD2A01B0.public

  protected:
    // Additional Protected Declarations
      //## begin RtemsEvent%3C58CD2A01B0.protected preserve=yes
      //## end RtemsEvent%3C58CD2A01B0.protected

  private:
    // Additional Private Declarations
      //## begin RtemsEvent%3C58CD2A01B0.private preserve=yes
      //## end RtemsEvent%3C58CD2A01B0.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _task_id%3C5A061702F6
      //## begin RtemsEvent::_task_id%3C5A061702F6.attr preserve=no  private: rtems_id {U} 
      rtems_id _task_id;
      //## end RtemsEvent::_task_id%3C5A061702F6.attr

      //## Attribute: _initialised%3C5A154F02B2
      //## begin RtemsEvent::_initialised%3C5A154F02B2.attr preserve=no  private: bool {UT} false
      volatile bool  _initialised;
      //## end RtemsEvent::_initialised%3C5A154F02B2.attr

    // Additional Implementation Declarations
      //## begin RtemsEvent%3C58CD2A01B0.implementation preserve=yes
      //## end RtemsEvent%3C58CD2A01B0.implementation

};

//## begin RtemsEvent%3C58CD2A01B0.postscript preserve=yes
//## end RtemsEvent%3C58CD2A01B0.postscript

// Class RtemsEvent 

inline RtemsEvent::RtemsEvent()
  //## begin RtemsEvent::RtemsEvent%.hasinit preserve=no
      : _initialised(false)
  //## end RtemsEvent::RtemsEvent%.hasinit
  //## begin RtemsEvent::RtemsEvent%.initialization preserve=yes
  //## end RtemsEvent::RtemsEvent%.initialization
{
  //## begin RtemsEvent::RtemsEvent%.body preserve=yes
#ifdef CONSOLE_DEBUG
	printf("RtemsEvent\r\n");
#endif

  //## end RtemsEvent::RtemsEvent%.body
}


inline RtemsEvent::~RtemsEvent()
{
  //## begin RtemsEvent::~RtemsEvent%.body preserve=yes
	Release();
  //## end RtemsEvent::~RtemsEvent%.body
}


// Class Event 


//## Other Operations (implementation)
//## Operation: create%1012532984
//	Static create function that returns the sub class,
//	depending upon the component
Event* Event::create ()
{
  //## begin Event::create%1012532984.body preserve=yes
#ifdef CONSOLE_DEBUG
	printf("Event::Create\r\n");
#endif

	return new RtemsEvent;
  //## end Event::create%1012532984.body
}

// Additional Declarations
  //## begin Event%3C58CD02004A.declarations preserve=yes
  //## end Event%3C58CD02004A.declarations

// Class RtemsEvent 




//## Other Operations (implementation)
//## Operation: Wait%1012532982
bool RtemsEvent::Wait (int timeout)
{
  //## begin RtemsEvent::Wait%1012532982.body preserve=yes

	bool ret;

	rtems_event_set dummy;

	if (!_initialised)
		{
			rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &_task_id );
			_initialised = true;
		}

#ifdef CONSOLE_DEBUG
	printf("wait\r\n"):
#endif

	if (timeout == -1)
		{
			ret = (rtems_event_receive (RTEMS_EVENT_EVENT_FLAG, RTEMS_WAIT, 
																	RTEMS_NO_TIMEOUT, &dummy) == RTEMS_SUCCESSFUL);
		 }
	else
		{
			ret = (rtems_event_receive (RTEMS_EVENT_EVENT_FLAG, RTEMS_WAIT, 
																	timeout, &dummy) == RTEMS_SUCCESSFUL);
		}

#ifdef CONSOLE_DEBUG
	printf("release\r\n");
#endif
	return ret;

  //## end RtemsEvent::Wait%1012532982.body
}

//## Operation: Release%1012532983
void RtemsEvent::Release ()
{
  //## begin RtemsEvent::Release%1012532983.body preserve=yes
	
	if (_initialised)
		{
#ifdef CONSOLE_DEBUG
			printf("send\r\n");
#endif
			rtems_event_send (_task_id, RTEMS_EVENT_EVENT_FLAG);
		}
  //## end RtemsEvent::Release%1012532983.body
}

// Additional Declarations
  //## begin RtemsEvent%3C58CD2A01B0.declarations preserve=yes
  //## end RtemsEvent%3C58CD2A01B0.declarations

//## begin module%3C5A067C0099.epilog preserve=yes
//## end module%3C5A067C0099.epilog
