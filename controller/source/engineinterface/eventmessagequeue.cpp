//## begin module%3A88576B004F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A88576B004F.cm

//## begin module%3A88576B004F.cp preserve=no
//	Angelo Fraietta
//## end module%3A88576B004F.cp

//## Module: EventMessageQueue%3A88576B004F; Pseudo Package body
//## Subsystem: engineinterface%3A9C858C00CB
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\eventmessagequeue.cpp

//## begin module%3A88576B004F.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3A88576B004F.additionalIncludes

//## begin module%3A88576B004F.includes preserve=yes
#include "control.h"
//## end module%3A88576B004F.includes

// identity
#include "identity.h"
// EventMessageQueue
#include "eventmessagequeue.h"
//## begin module%3A88576B004F.additionalDeclarations preserve=yes
//## end module%3A88576B004F.additionalDeclarations


// Class Utility EventMessageQueue 

//## begin EventMessageQueue::Sender%3A885A7D02E5.role preserve=no  public: Display {1 -> 0..nRFH}
//## end EventMessageQueue::Sender%3A885A7D02E5.role

//## begin EventMessageQueue::Sender%3A886FEE019D.role preserve=no  public: Trigger { -> RFH}
//## end EventMessageQueue::Sender%3A886FEE019D.role

//## begin EventMessageQueue::sender%3A8877D40399.role preserve=no  public: Identity { -> RFHN}
//## end EventMessageQueue::sender%3A8877D40399.role


//## Other Operations (implementation)
//## Operation: DisplayVoid%982014805
//	Sends a void message for a display Object
void EventMessageQueue::DisplayVoid (const Identity* sender)
{
  //## begin EventMessageQueue::DisplayVoid%982014805.body preserve=yes
  //## end EventMessageQueue::DisplayVoid%982014805.body
}

//## Operation: DisplayInt%982019132
//	Sends an int message for a display Object
void EventMessageQueue::DisplayInt (const Identity* sender, int message)
{
  //## begin EventMessageQueue::DisplayInt%982019132.body preserve=yes
  //## end EventMessageQueue::DisplayInt%982019132.body
}

//## Operation: DisplayDouble%982019133
//	Sends a double message for a display Object
void EventMessageQueue::DisplayDouble (const Identity* sender, double message)
{
  //## begin EventMessageQueue::DisplayDouble%982019133.body preserve=yes
  //## end EventMessageQueue::DisplayDouble%982019133.body
}

//## Operation: DisplayString%982019134
//	Sends a const char* message for a display Object.
//## Postconditions:
//	This class will make a copy of the string message and
//	send it when it has time, thus allowing the Display
//	object to continue on its way.
void EventMessageQueue::DisplayString (const Identity* sender, const char* message)
{
  //## begin EventMessageQueue::DisplayString%982019134.body preserve=yes
  //## end EventMessageQueue::DisplayString%982019134.body
}

//## Operation: Trigger%982019135
//	Sends a Trigger message for display to a window.
void EventMessageQueue::Trigger (const Identity* sender)
{
  //## begin EventMessageQueue::Trigger%982019135.body preserve=yes
  //## end EventMessageQueue::Trigger%982019135.body
}

//## Operation: VoidError%982019136
//	Displays Error messages that have no Parameters causing
//	the error
void EventMessageQueue::VoidError (error_message_type error_type, const Identity *sender)
{
  //## begin EventMessageQueue::VoidError%982019136.body preserve=yes
  //## end EventMessageQueue::VoidError%982019136.body
}

//## Operation: IntError%982019137
//	Displays Error messages that have an integer as the
//	parameter causing the error.
void EventMessageQueue::IntError (error_message_type error_type, const Identity *sender, int param)
{
  //## begin EventMessageQueue::IntError%982019137.body preserve=yes
  //## end EventMessageQueue::IntError%982019137.body
}

//## Operation: DoubleError%982019138
//	Displays Error messages that have a double as the
//	parameter causing the error.
void EventMessageQueue::DoubleError (error_message_type error_type, const Identity *sender, double param)
{
  //## begin EventMessageQueue::DoubleError%982019138.body preserve=yes
  //## end EventMessageQueue::DoubleError%982019138.body
}

//## Operation: StringError%982019139
//	Displays Error messages that have a stringas the
//	parameter causing the error.
//## Postconditions:
//	This class will make a copy of the string message and
//	send it when it has time, thus allowing the object to
//	continue on its way.
void EventMessageQueue::StringError (error_message_type error_type, const Identity *sender, const char* param)
{
  //## begin EventMessageQueue::StringError%982019139.body preserve=yes
  //## end EventMessageQueue::StringError%982019139.body
}

// Additional Declarations
  //## begin EventMessageQueue%3A88576B004F.declarations preserve=yes
  //## end EventMessageQueue%3A88576B004F.declarations

//## begin module%3A88576B004F.epilog preserve=yes
//## end module%3A88576B004F.epilog
