//## begin module%3C5A067C0099.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C5A067C0099.cm

//## begin module%3C5A067C0099.cp preserve=no
//	Angelo Fraietta
//## end module%3C5A067C0099.cp

//## Module: RtemsEvent%3C5A067C0099; Package specification
//## Subsystem: hal_rtems%3B255F2C0271
//## Source file: c:\develop\multithreads\source\hal_rtems\rtemsevent.h

#ifndef rtemsevent_h
#define rtemsevent_h 1

//## begin module%3C5A067C0099.additionalIncludes preserve=no

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
      void Wait ();

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
    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: _waiting%3C5A154F02B2
      const bool get__waiting () const;
      void set__waiting (bool value);

    // Additional Private Declarations
      //## begin RtemsEvent%3C58CD2A01B0.private preserve=yes
      //## end RtemsEvent%3C58CD2A01B0.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _task_id%3C5A061702F6
      //## begin RtemsEvent::_task_id%3C5A061702F6.attr preserve=no  private: rtems_id {U} 
      rtems_id _task_id;
      //## end RtemsEvent::_task_id%3C5A061702F6.attr

      //## begin RtemsEvent::_waiting%3C5A154F02B2.attr preserve=no  private: bool {UT} false
      volatile bool  _waiting;
      //## end RtemsEvent::_waiting%3C5A154F02B2.attr

    // Additional Implementation Declarations
      //## begin RtemsEvent%3C58CD2A01B0.implementation preserve=yes
      //## end RtemsEvent%3C58CD2A01B0.implementation

};

//## begin RtemsEvent%3C58CD2A01B0.postscript preserve=yes
//## end RtemsEvent%3C58CD2A01B0.postscript

// Class RtemsEvent 

inline RtemsEvent::RtemsEvent()
  //## begin RtemsEvent::RtemsEvent%.hasinit preserve=no
      : _waiting(false)
  //## end RtemsEvent::RtemsEvent%.hasinit
  //## begin RtemsEvent::RtemsEvent%.initialization preserve=yes
  //## end RtemsEvent::RtemsEvent%.initialization
{
  //## begin RtemsEvent::RtemsEvent%.body preserve=yes
  //## end RtemsEvent::RtemsEvent%.body
}


inline RtemsEvent::~RtemsEvent()
{
  //## begin RtemsEvent::~RtemsEvent%.body preserve=yes
	Release();
  //## end RtemsEvent::~RtemsEvent%.body
}



//## Other Operations (inline)
//## Operation: Wait%1012532982
inline void RtemsEvent::Wait ()
{
  //## begin RtemsEvent::Wait%1012532982.body preserve=yes
	rtems_event_set dummy;

	rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &_task_id );
	_waiting = true;

#ifdef CONSOLE_DEBUG
	cout<<"wait"<<endl;
#endif

	rtems_event_receive (RTEMS_EVENT_EVENT_FLAG, RTEMS_WAIT, 
											 RTEMS_NO_TIMEOUT, &dummy);
#ifdef CONSOLE_DEBUG
	cout<<"release"<<endl;
#endif

	_waiting = false;
  //## end RtemsEvent::Wait%1012532982.body
}

//## Operation: Release%1012532983
inline void RtemsEvent::Release ()
{
  //## begin RtemsEvent::Release%1012532983.body preserve=yes
	if (_waiting)
		{
#ifdef CONSOLE_DEBUG
			cout<<"send"<<endl;
#endif
			rtems_event_send (_task_id, RTEMS_EVENT_EVENT_FLAG);
		}
  //## end RtemsEvent::Release%1012532983.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const bool RtemsEvent::get__waiting () const
{
  //## begin RtemsEvent::get__waiting%3C5A154F02B2.get preserve=no
  return _waiting;
  //## end RtemsEvent::get__waiting%3C5A154F02B2.get
}

inline void RtemsEvent::set__waiting (bool value)
{
  //## begin RtemsEvent::set__waiting%3C5A154F02B2.set preserve=no
  _waiting = value;
  //## end RtemsEvent::set__waiting%3C5A154F02B2.set
}

//## begin module%3C5A067C0099.epilog preserve=yes
//## end module%3C5A067C0099.epilog


#endif
