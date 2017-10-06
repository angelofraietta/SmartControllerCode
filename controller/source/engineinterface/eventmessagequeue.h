//## begin module%3A88576B004F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A88576B004F.cm

//## begin module%3A88576B004F.cp preserve=no
//	Angelo Fraietta
//## end module%3A88576B004F.cp

//## Module: EventMessageQueue%3A88576B004F; Pseudo Package specification
//## Subsystem: engineinterface%3A9C858C00CB
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\eventmessagequeue.h

#ifndef eventmessagequeue_h
#define eventmessagequeue_h 1

//## begin module%3A88576B004F.additionalIncludes preserve=no
//## end module%3A88576B004F.additionalIncludes

//## begin module%3A88576B004F.includes preserve=yes
//## end module%3A88576B004F.includes


class Identity;

//## begin module%3A88576B004F.additionalDeclarations preserve=yes
//## end module%3A88576B004F.additionalDeclarations


//## begin EventMessageQueue%3A88576B004F.preface preserve=yes
//## end EventMessageQueue%3A88576B004F.preface

//## Class: EventMessageQueue%3A88576B004F; Class Utility
//	Interfaces messages that are required to go to some sort
//	of Display Window. Handles interface for Display,
//	Trigger, and Error messages.
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class EventMessageQueue 
{
  //## begin EventMessageQueue%3A88576B004F.initialDeclarations preserve=yes
  //## end EventMessageQueue%3A88576B004F.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: DisplayVoid%982014805
      static void DisplayVoid (const Identity* sender	// This ios the Trigger that sent the object
      );

      //## Operation: DisplayInt%982019132
      static void DisplayInt (const Identity* sender, 	// This ios the Trigger that sent the object
      int message	// The message to be displayed.
      );

      //## Operation: DisplayDouble%982019133
      static void DisplayDouble (const Identity* sender, 	// This ios the Trigger that sent the object
      double message	// The message to be displayed.
      );

      //## Operation: DisplayString%982019134
      static void DisplayString (const Identity* sender, 	// This ios the Trigger that sent the object
      const char* message	// The message to be displayed.
      );

      //## Operation: Trigger%982019135
      static void Trigger (const Identity* sender	// This ios the Trigger that sent the object
      );

      //## Operation: VoidError%982019136
      static void VoidError (error_message_type error_type, const Identity *sender	// The Object that is sending the Error Message
      );

      //## Operation: IntError%982019137
      static void IntError (error_message_type error_type, const Identity *sender, 	// The Object that is sending the Error Message
      int param	// Parameter Value that causes the error.
      );

      //## Operation: DoubleError%982019138
      static void DoubleError (error_message_type error_type, const Identity *sender, 	// The Object that is sending the Error Message
      double param	// Parameter Value that causes the error.
      );

      //## Operation: StringError%982019139
      static void StringError (error_message_type error_type, const Identity *sender, 	// The Object that is sending the Error Message
      const char* param	// Parameter Value that causes the error.
      );

    // Additional Public Declarations
      //## begin EventMessageQueue%3A88576B004F.public preserve=yes
      //## end EventMessageQueue%3A88576B004F.public

  protected:
    // Additional Protected Declarations
      //## begin EventMessageQueue%3A88576B004F.protected preserve=yes
      //## end EventMessageQueue%3A88576B004F.protected

  private:
    // Additional Private Declarations
      //## begin EventMessageQueue%3A88576B004F.private preserve=yes
      //## end EventMessageQueue%3A88576B004F.private

  private: //## implementation
    // Data Members for Associations

      //## Association: hal_include::<unnamed>%3A8877D400D2
      //## Role: EventMessageQueue::sender%3A8877D40399
      //## begin EventMessageQueue::sender%3A8877D40399.role preserve=no  public: Identity { -> RFHN}
      //## end EventMessageQueue::sender%3A8877D40399.role

    // Additional Implementation Declarations
      //## begin EventMessageQueue%3A88576B004F.implementation preserve=yes
      //## end EventMessageQueue%3A88576B004F.implementation

};

//## begin EventMessageQueue%3A88576B004F.postscript preserve=yes
//## end EventMessageQueue%3A88576B004F.postscript

// Class Utility EventMessageQueue 

//## begin module%3A88576B004F.epilog preserve=yes
//## end module%3A88576B004F.epilog


#endif
