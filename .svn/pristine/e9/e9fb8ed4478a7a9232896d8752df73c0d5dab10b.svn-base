//## begin module%3A91CCA701C9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A91CCA701C9.cm

//## begin module%3A91CCA701C9.cp preserve=no
//	Angelo Fraietta
//## end module%3A91CCA701C9.cp

//## Module: ScheduledObject%3A91CCA701C9; 
//## Subsystem: hal_include%3A80CC250114
//## Source file: c:\develop\SmartController\source\hal_include\scheduledobject.h

//## begin module%3A91CCA701C9.additionalIncludes preserve=no
//## end module%3A91CCA701C9.additionalIncludes

//## begin module%3A91CCA701C9.includes preserve=yes
//## end module%3A91CCA701C9.includes

// timer
#include "timer.h"

namespace hal_include {
  class ScheduledObject;

} // namespace hal_include

//## begin module%3A91CCA701C9.declarations preserve=no
//## end module%3A91CCA701C9.declarations

//## begin module%3A91CCA701C9.additionalDeclarations preserve=yes
//## end module%3A91CCA701C9.additionalDeclarations


namespace hal_include {
  //## begin hal_include%3A80CAE10028.initialDeclarations preserve=yes
  //## end hal_include%3A80CAE10028.initialDeclarations

  //## begin hal_include::ScheduledObject%3A909E770117.preface preserve=yes
  //## end hal_include::ScheduledObject%3A909E770117.preface

  //## Class: ScheduledObject%3A909E770117
  //	Contains Details of Scheduled Item, and whether the Item
  //	is Valid
  //## Category: hal_include%3A80CAE10028
  //## Subsystem: hal_include%3A80CC250114
  //## Persistence: Transient
  //## Cardinality/Multiplicity: n

  class ScheduledObject 
  {
    //## begin hal_include::ScheduledObject%3A909E770117.initialDeclarations preserve=yes
    //## end hal_include::ScheduledObject%3A909E770117.initialDeclarations

    public:
      //## Constructors (specified)
        //## Operation: ScheduledObject%982622339
        ScheduledObject (const TimerQueueItem& TimerObject	// Contains All the details about object that needs to be
        	// called back
        );


      //## Other Operations (specified)
        //## Operation: CallbackTime%982638341
        DWORD CallbackTime () const;

        //## Operation: Param%982638346
        void* Param () const;

        //## Operation: Timer%982638347
        TimerObject* Timer ();

      // Additional Public Declarations
        //## begin hal_include::ScheduledObject%3A909E770117.public preserve=yes
        //## end hal_include::ScheduledObject%3A909E770117.public

    protected:
      // Additional Protected Declarations
        //## begin hal_include::ScheduledObject%3A909E770117.protected preserve=yes
        //## end hal_include::ScheduledObject%3A909E770117.protected

    private:
      // Additional Private Declarations
        //## begin hal_include::ScheduledObject%3A909E770117.private preserve=yes
        //## end hal_include::ScheduledObject%3A909E770117.private

    private: //## implementation
      // Data Members for Class Attributes

        //## Attribute: valid%3A909F040296
        //## begin hal_include::ScheduledObject::valid%3A909F040296.attr preserve=no  private: bool {UT} true
        volatile bool  valid;
        //## end hal_include::ScheduledObject::valid%3A909F040296.attr

      // Data Members for Associations

        //## Association: hal_include::<unnamed>%3A909EC6005C
        //## Role: ScheduledObject::_timer%3A909EC901E7
        //## begin hal_include::ScheduledObject::_timer%3A909EC901E7.role preserve=no  public: TimerQueueItem { -> 1VHN}
        TimerQueueItem _timer;
        //## end hal_include::ScheduledObject::_timer%3A909EC901E7.role

      // Additional Implementation Declarations
        //## begin hal_include::ScheduledObject%3A909E770117.implementation preserve=yes
        //## end hal_include::ScheduledObject%3A909E770117.implementation

    //## begin hal_include::ScheduledObject%3A909E770117.friends preserve=no
      friend class Scheduler;
    //## end hal_include::ScheduledObject%3A909E770117.friends
  };

  //## begin hal_include::ScheduledObject%3A909E770117.postscript preserve=yes
  //## end hal_include::ScheduledObject%3A909E770117.postscript

  //## begin hal_include::ScheduledObjectPriority%3A91DD400060.preface preserve=yes
  //## end hal_include::ScheduledObjectPriority%3A91DD400060.preface

  //## Class: ScheduledObjectPriority%3A91DD400060
  //	class uses operator to determine which ScheduledObject
  //	has the higher priority
  //
  //	Greater time has less priority
  //## Category: hal_include%3A80CAE10028
  //## Subsystem: hal_include%3A80CC250114
  //## Persistence: Transient
  //## Cardinality/Multiplicity: n

  class ScheduledObjectPriority 
  {
    //## begin hal_include::ScheduledObjectPriority%3A91DD400060.initialDeclarations preserve=yes
    //## end hal_include::ScheduledObjectPriority%3A91DD400060.initialDeclarations

    public:

      //## Other Operations (specified)
        //## Operation: operator()%982638342
        bool operator () (const ScheduledObject* x, const ScheduledObject* y);

      // Additional Public Declarations
        //## begin hal_include::ScheduledObjectPriority%3A91DD400060.public preserve=yes
        //## end hal_include::ScheduledObjectPriority%3A91DD400060.public

    protected:
      // Additional Protected Declarations
        //## begin hal_include::ScheduledObjectPriority%3A91DD400060.protected preserve=yes
        //## end hal_include::ScheduledObjectPriority%3A91DD400060.protected

    private:
      // Additional Private Declarations
        //## begin hal_include::ScheduledObjectPriority%3A91DD400060.private preserve=yes
        //## end hal_include::ScheduledObjectPriority%3A91DD400060.private

    private: //## implementation
      // Data Members for Associations

        //## Association: hal_include::<unnamed>%3A91DD7F02EC
        //## Role: ScheduledObjectPriority::<the_ScheduledObject>%3A91DD81038F
        //## begin hal_include::ScheduledObjectPriority::<the_ScheduledObject>%3A91DD81038F.role preserve=no  public: hal_include::ScheduledObject { -> 2RFHN}
        //## end hal_include::ScheduledObjectPriority::<the_ScheduledObject>%3A91DD81038F.role

      // Additional Implementation Declarations
        //## begin hal_include::ScheduledObjectPriority%3A91DD400060.implementation preserve=yes
        //## end hal_include::ScheduledObjectPriority%3A91DD400060.implementation

  };

  //## begin hal_include::ScheduledObjectPriority%3A91DD400060.postscript preserve=yes
  //## end hal_include::ScheduledObjectPriority%3A91DD400060.postscript

  // Class hal_include::ScheduledObject 

  //## Operation: ScheduledObject%982622339
  //	Constructor
  inline ScheduledObject::ScheduledObject (const TimerQueueItem& TimerObject)
    //## begin hal_include::ScheduledObject::ScheduledObject%982622339.hasinit preserve=no
        : valid(true), _timer(TimerObject)
    //## end hal_include::ScheduledObject::ScheduledObject%982622339.hasinit
    //## begin hal_include::ScheduledObject::ScheduledObject%982622339.initialization preserve=yes
    //## end hal_include::ScheduledObject::ScheduledObject%982622339.initialization
  {
    //## begin hal_include::ScheduledObject::ScheduledObject%982622339.body preserve=yes
    //## end hal_include::ScheduledObject::ScheduledObject%982622339.body
  }



  //## Other Operations (inline)
  //## Operation: CallbackTime%982638341
  //	Returns the Callback Time of this ScheduledObject
  inline DWORD ScheduledObject::CallbackTime () const
  {
    return _timer.CallbackTime;

    //## begin hal_include::ScheduledObject::CallbackTime%982638341.body preserve=yes
    //## end hal_include::ScheduledObject::CallbackTime%982638341.body
  }

  //## Operation: Param%982638346
  //	Returns the Param of this ScheduledObject
  inline void* ScheduledObject::Param () const
  {
    return _timer.pParam;

    //## begin hal_include::ScheduledObject::Param%982638346.body preserve=yes
    //## end hal_include::ScheduledObject::Param%982638346.body
  }

  //## Operation: Timer%982638347
  //	Returns the Timerof this ScheduledObject
  inline TimerObject* ScheduledObject::Timer ()
  {
    return _timer.pTimer;

    //## begin hal_include::ScheduledObject::Timer%982638347.body preserve=yes
    //## end hal_include::ScheduledObject::Timer%982638347.body
  }

  // Class hal_include::ScheduledObjectPriority 


  //## Other Operations (inline)
  //## Operation: operator()%982638342
  //	The Greater Time has less priority
  inline bool ScheduledObjectPriority::operator () (const ScheduledObject* x, const ScheduledObject* y)
  {
    return x->CallbackTime () > y->CallbackTime();

    //## begin hal_include::ScheduledObjectPriority::operator()%982638342.body preserve=yes
    //## end hal_include::ScheduledObjectPriority::operator()%982638342.body
  }

  // Class hal_include::ScheduledObject 





  // Additional Declarations
    //## begin hal_include::ScheduledObject%3A909E770117.declarations preserve=yes
    //## end hal_include::ScheduledObject%3A909E770117.declarations

  // Class hal_include::ScheduledObjectPriority 


  // Additional Declarations
    //## begin hal_include::ScheduledObjectPriority%3A91DD400060.declarations preserve=yes
    //## end hal_include::ScheduledObjectPriority%3A91DD400060.declarations

} // namespace hal_include

//## begin module%3A91CCA701C9.epilog preserve=yes
//## end module%3A91CCA701C9.epilog
