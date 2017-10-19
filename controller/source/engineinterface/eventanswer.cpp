//## begin module%3ACAAF8D012E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ACAAF8D012E.cm

//## begin module%3ACAAF8D012E.cp preserve=no
//	Angelo Fraietta
//## end module%3ACAAF8D012E.cp

//## Module: EventAnswer%3ACAAF8D012E; Package body
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\eventanswer.cpp

//## begin module%3ACAAF8D012E.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3ACAAF8D012E.additionalIncludes

//## begin module%3ACAAF8D012E.includes preserve=yes
//## end module%3ACAAF8D012E.includes

// EventAnswer
#include "eventanswer.h"
//## begin module%3ACAAF8D012E.declarations preserve=no
//## end module%3ACAAF8D012E.declarations

//## begin module%3ACAAF8D012E.additionalDeclarations preserve=yes
//## end module%3ACAAF8D012E.additionalDeclarations


// Class EventAnswer 


EventAnswer::EventAnswer()
  //## begin EventAnswer::EventAnswer%.hasinit preserve=no
  //## end EventAnswer::EventAnswer%.hasinit
  //## begin EventAnswer::EventAnswer%.initialization preserve=yes
  //## end EventAnswer::EventAnswer%.initialization
{
  //## begin EventAnswer::EventAnswer%.body preserve=yes
  //## end EventAnswer::EventAnswer%.body
}

EventAnswer::EventAnswer(const EventAnswer &right)
  //## begin EventAnswer::EventAnswer%copy.hasinit preserve=no
  //## end EventAnswer::EventAnswer%copy.hasinit
  //## begin EventAnswer::EventAnswer%copy.initialization preserve=yes
  //## end EventAnswer::EventAnswer%copy.initialization
{
  //## begin EventAnswer::EventAnswer%copy.body preserve=yes
  //## end EventAnswer::EventAnswer%copy.body
}


EventAnswer::~EventAnswer()
{
  //## begin EventAnswer::~EventAnswer%.body preserve=yes
  //## end EventAnswer::~EventAnswer%.body
}


const EventAnswer & EventAnswer::operator=(const EventAnswer &right)
{
  //## begin EventAnswer::operator=%.body preserve=yes
    return *this;
  //## end EventAnswer::operator=%.body
}


int EventAnswer::operator==(const EventAnswer &right) const
{
  //## begin EventAnswer::operator==%.body preserve=yes
    return 0;
  //## end EventAnswer::operator==%.body
}

int EventAnswer::operator!=(const EventAnswer &right) const
{
  //## begin EventAnswer::operator!=%.body preserve=yes
    return 0;
  //## end EventAnswer::operator!=%.body
}



//## Other Operations (implementation)
//## Operation: eventReady%985819702
//	returns true if there is an event ready
bool EventAnswer::eventReady ()
{
  //## begin EventAnswer::eventReady%985819702.body preserve=yes
    return false;
  //## end EventAnswer::eventReady%985819702.body
}

//## Operation: GetEvent%985819708
//	Gets the next event that is ready
unsigned EventAnswer::GetEvent (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin EventAnswer::GetEvent%985819708.body preserve=yes
    return 0;
  //## end EventAnswer::GetEvent%985819708.body
}

// Additional Declarations
  //## begin EventAnswer%3AA808F802AC.declarations preserve=yes
  //## end EventAnswer%3AA808F802AC.declarations

//## begin module%3ACAAF8D012E.epilog preserve=yes
//## end module%3ACAAF8D012E.epilog
