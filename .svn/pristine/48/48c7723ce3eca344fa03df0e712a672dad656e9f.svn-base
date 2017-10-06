//## begin module%3A92E11B0106.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A92E11B0106.cm

//## begin module%3A92E11B0106.cp preserve=no
//	Angelo Fraietta
//## end module%3A92E11B0106.cp

//## Module: scheduler%3A92E11B0106; Package specification
//	scheduler header file
//## Subsystem: hal_include%3A80CC250114
//## Source file: d:\develop\SmartController\controller\source\hal_include\scheduler.h

#ifndef scheduler_h
#define scheduler_h 1

//## begin module%3A92E11B0106.additionalIncludes preserve=no
//## end module%3A92E11B0106.additionalIncludes

//## begin module%3A92E11B0106.includes preserve=yes
namespace hal_include {class ScheduledObjectPriority;}
//## end module%3A92E11B0106.includes

// memorycache
#include "memorycache.h"
// timer
#include "timer.h"
// equeue
#include "equeue.h"

namespace hal_include {
  typedef sm_str::priority_queue< ScheduledObjectPriority > ScheduledObjectQueue;
  class ScheduledObjectPriority;
  class ScheduledObject;
  class Scheduler;

} // namespace hal_include

//## begin module%3A92E11B0106.declarations preserve=no
//## end module%3A92E11B0106.declarations

//## begin module%3A92E11B0106.additionalDeclarations preserve=yes
//## end module%3A92E11B0106.additionalDeclarations


namespace hal_include {
  //## begin hal_include%3A80CAE10028.initialDeclarations preserve=yes
  //## end hal_include%3A80CAE10028.initialDeclarations

  //## begin hal_include::Scheduler%3A80BBBF0082.preface preserve=yes
  //## end hal_include::Scheduler%3A80BBBF0082.preface

  //## Class: Scheduler%3A80BBBF0082; Class Utility
  //	This is the scheduler unit that is used for calling
  //	timer objects when they are due. The Scheduler is
  //	implemented as a utility class as there is only one
  //	scheduler, and as such, the operations will all be
  //	static.  The Header can be used by all HAL layers with
  //	the implementation and coupling with the particular OS
  //	can be implemented within each hal component source
  //## Category: hal_include%3A80CAE10028
  //## Subsystem: hal_include%3A80CC250114
  //## Persistence: Transient
  //## Cardinality/Multiplicity: n

  //## Uses: <unnamed>%3A909FA700E2;friend ScheduledObject { -> F}
  //## Uses: <unnamed>%3A92F55902FC;ScheduledObjectQueue { -> F}

  class Scheduler 
  {
    //## begin hal_include::Scheduler%3A80BBBF0082.initialDeclarations preserve=yes
    //## end hal_include::Scheduler%3A80BBBF0082.initialDeclarations

    public:

      //## Other Operations (specified)
        //## Operation: SetTimeEvent%981519022
        static ScheduledObject* SetTimeEvent (const TimerQueueItem& item	// This is the Item that has the details to call back
        );

        //## Operation: KillTimeEvent%981519023
        static void KillTimeEvent (ScheduledObject* item	// This is the Item that has the details to call back
        );

        //## Operation: initialise%981603322
        static bool initialise ();

        //## Operation: deinitialise%981603323
        static bool deinitialise ();

        //## Operation: getTime%981603750
        static DWORD getTime ();

        //## Operation: processCallback%982638343
        static DWORD processCallback ();

        //## Operation: pause%982638344
        static void pause ();

        //## Operation: resume%982638345
        static void resume ();

        //## Operation: purge%982879201
        static void purge ();

        //## Operation: LockEngine%1018482872
        static bool LockEngine (unsigned wait_period = 0);

        //## Operation: UnlockEngine%1018482873
        static bool UnlockEngine ();

      // Additional Public Declarations
        //## begin hal_include::Scheduler%3A80BBBF0082.public preserve=yes
        //## end hal_include::Scheduler%3A80BBBF0082.public

    protected:
      // Additional Protected Declarations
        //## begin hal_include::Scheduler%3A80BBBF0082.protected preserve=yes
        //## end hal_include::Scheduler%3A80BBBF0082.protected

    private:

      //## Other Operations (specified)
        //## Operation: lock%982879202
        static bool lock (unsigned period = 0	// The amount of time in seconds to wait for the lock. If
        	// the lock is not obtained within this period, the
        	// function will return false;
        );

        //## Operation: unlock%982879203
        static bool unlock ();

      // Additional Private Declarations
        //## begin hal_include::Scheduler%3A80BBBF0082.private preserve=yes
        //## end hal_include::Scheduler%3A80BBBF0082.private

    private: //## implementation
      // Data Members for Class Attributes

        //## Attribute: initialised%3A9452E30298
        //	This flag is used to determine if the Scheduler has been
        //	initialised, and as such is used to prevent
        //	re-initialisation.
        //## begin hal_include::Scheduler::initialised%3A9452E30298.attr preserve=no  private: static bool {UT} false
        static volatile bool  initialised;
        //## end hal_include::Scheduler::initialised%3A9452E30298.attr

        //## Attribute: dwOffset%3A91E2CD00DB
        //	This is the offset that is stored for resuming. When the
        //	Scheduler resumes, this offset is added to the times
        //	scheduled for callback.
        //## begin hal_include::Scheduler::dwOffset%3A91E2CD00DB.attr preserve=no  private: static DWORD {UT} 0
        static volatile DWORD  dwOffset;
        //## end hal_include::Scheduler::dwOffset%3A91E2CD00DB.attr

        //## Attribute: dwPauseTime%3A9452F5004F
        //	The Pause time is used to record when the pause command
        //	was executed. After resume, the pause time is subtracted
        //	from the time resumed to obtain the offset.
        //## begin hal_include::Scheduler::dwPauseTime%3A9452F5004F.attr preserve=no  private: static DWORD {UT} 0
        static volatile DWORD  dwPauseTime;
        //## end hal_include::Scheduler::dwPauseTime%3A9452F5004F.attr

        //## Attribute: lock_wait_time%3A95CF7E0253
        //	The period to wait for a lock
        //## begin hal_include::Scheduler::lock_wait_time%3A95CF7E0253.attr preserve=no  private: static unsigned {U} 10
        static unsigned lock_wait_time;
        //## end hal_include::Scheduler::lock_wait_time%3A95CF7E0253.attr

      // Data Members for Associations

        //## Association: hal_include::<unnamed>%3A92EB380177
        //## Role: Scheduler::<the_ScheduledObjectPriority>%3A92EB3A02B0
        //## begin hal_include::Scheduler::<the_ScheduledObjectPriority>%3A92EB3A02B0.role preserve=no  public: hal_include::ScheduledObjectPriority { -> RFHN}
        //## end hal_include::Scheduler::<the_ScheduledObjectPriority>%3A92EB3A02B0.role

        //## Association: hal_include::<unnamed>%3A92FF6F01AA
        //## Role: Scheduler::ScheduledItems%3A92FF700133
        //## begin hal_include::Scheduler::ScheduledItems%3A92FF700133.role preserve=no  public: hal_include::ScheduledObjectQueue { -> 1VFHN}
        static ScheduledObjectQueue ScheduledItems;
        //## end hal_include::Scheduler::ScheduledItems%3A92FF700133.role

      // Additional Implementation Declarations
        //## begin hal_include::Scheduler%3A80BBBF0082.implementation preserve=yes
        friend class ScheduledObject;
        //## end hal_include::Scheduler%3A80BBBF0082.implementation
  };

  //## begin hal_include::Scheduler%3A80BBBF0082.postscript preserve=yes
  //## end hal_include::Scheduler%3A80BBBF0082.postscript

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
      //## Constructors (specified)
        //## Operation: ScheduledObjectPriority%982704555
        ScheduledObjectPriority (ScheduledObject* pScheduler);

      //## Dereference Operation (generated)
        ScheduledObject* operator*() const;


      //## Other Operations (specified)
        //## Operation: operator >%982638342
        bool operator > (const ScheduledObjectPriority& right);

        //## Operation: CallbackTime%982704557
        DWORD CallbackTime () const;

        //## Operation: Param%982704558
        void* Param () const;

        //## Operation: Timer%982704559
        TimerObject* Timer ();

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
        //## Role: ScheduledObjectPriority::_scheduler%3A91DD81038F
        //## begin hal_include::ScheduledObjectPriority::_scheduler%3A91DD81038F.role preserve=no  public: hal_include::ScheduledObject { -> 1RFHN}
        ScheduledObject *_scheduler;
        //## end hal_include::ScheduledObjectPriority::_scheduler%3A91DD81038F.role

        //## Association: hal_include::<unnamed>%3A92EB380177
        //## Role: ScheduledObjectPriority::<the_Scheduler>%3A92EB3A02BA
        //## begin hal_include::ScheduledObjectPriority::<the_Scheduler>%3A92EB3A02BA.role preserve=no  public: hal_include::Scheduler { -> RFHN}
        //## end hal_include::ScheduledObjectPriority::<the_Scheduler>%3A92EB3A02BA.role

      // Additional Implementation Declarations
        //## begin hal_include::ScheduledObjectPriority%3A91DD400060.implementation preserve=yes
        //## end hal_include::ScheduledObjectPriority%3A91DD400060.implementation

      friend class Scheduler;
  };

  //## begin hal_include::ScheduledObjectPriority%3A91DD400060.postscript preserve=yes
  //## end hal_include::ScheduledObjectPriority%3A91DD400060.postscript

  //## begin hal_include::ScheduledObject%3A909E770117.preface preserve=yes
  //## end hal_include::ScheduledObject%3A909E770117.preface

  //## Class: ScheduledObject%3A909E770117
  //	Contains Details of Scheduled Item, and whether the Item
  //	is Valid
  //## Category: hal_include%3A80CAE10028
  //## Subsystem: hal_include%3A80CC250114
  //## Persistence: Transient
  //## Cardinality/Multiplicity: n

  //## Uses: <unnamed>%3A9313B100A3;ScheduledObjectPriority { -> F}
  //## Uses: <unnamed>%3CCE1AA301FE;MemoryCache { -> }

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

      //## Storage Management Operations (specified)
        //## Operation: operator new%1020137284
        static void* operator new (size_t size);

        //## Operation: operator delete%1020137285
        static void operator delete (void* mem);


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

        //## Association: hal_include::<unnamed>%3A91DD7F02EC
        //## Role: ScheduledObject::<the_ScheduledObjectPriority>%3A91DD810399
        //## begin hal_include::ScheduledObject::<the_ScheduledObjectPriority>%3A91DD810399.role preserve=no  public: hal_include::ScheduledObjectPriority {1 -> RHN}
        //## end hal_include::ScheduledObject::<the_ScheduledObjectPriority>%3A91DD810399.role

        //## Association: engine::<unnamed>%3CCE19A60309
        //## Role: ScheduledObject::_mem_manager%3CCE19A8006D
        //## begin hal_include::ScheduledObject::_mem_manager%3CCE19A8006D.role preserve=no  public: static MemoryCache { -> 1RHN}
        static MemoryCache _mem_manager;
        //## end hal_include::ScheduledObject::_mem_manager%3CCE19A8006D.role

      // Additional Implementation Declarations
        //## begin hal_include::ScheduledObject%3A909E770117.implementation preserve=yes
        //## end hal_include::ScheduledObject%3A909E770117.implementation

    //## begin hal_include::ScheduledObject%3A909E770117.friends preserve=no
      friend class Scheduler;
    //## end hal_include::ScheduledObject%3A909E770117.friends
  };

  //## begin hal_include::ScheduledObject%3A909E770117.postscript preserve=yes
  //## end hal_include::ScheduledObject%3A909E770117.postscript

  //## begin hal_include::ScheduledObjectQueue%3A92F50600B7.preface preserve=yes
  //## end hal_include::ScheduledObjectQueue%3A92F50600B7.preface

  //## Class: ScheduledObjectQueue%3A92F50600B7; Instantiated Class
  //	This is the priority Queue of Items
  //## Category: hal_include%3A80CAE10028
  //## Subsystem: hal_include%3A80CC250114
  //## Persistence: Persistent
  //## Cardinality/Multiplicity: 1..1

  //## Uses: <unnamed>%3A9302D80123;ScheduledObjectPriority { -> }

  typedef sm_str::priority_queue< ScheduledObjectPriority > ScheduledObjectQueue;

  //## begin hal_include::ScheduledObjectQueue%3A92F50600B7.postscript preserve=yes
  //## end hal_include::ScheduledObjectQueue%3A92F50600B7.postscript

  // Class Utility hal_include::Scheduler 

  // Class hal_include::ScheduledObjectPriority 

  //## Operation: ScheduledObjectPriority%982704555
  //	Required constructor
  inline ScheduledObjectPriority::ScheduledObjectPriority (ScheduledObject* pScheduler)
    //## begin hal_include::ScheduledObjectPriority::ScheduledObjectPriority%982704555.hasinit preserve=no
        : _scheduler(pScheduler)
    //## end hal_include::ScheduledObjectPriority::ScheduledObjectPriority%982704555.hasinit
  {
  }


  inline ScheduledObject* ScheduledObjectPriority::operator*() const
  {
    //## begin hal_include::ScheduledObjectPriority::operator*%.body preserve=yes
					return _scheduler;
    //## end hal_include::ScheduledObjectPriority::operator*%.body
  }



  //## Other Operations (inline)
  //## Operation: operator >%982638342
  //	The Greater Time has less priority
  inline bool ScheduledObjectPriority::operator > (const ScheduledObjectPriority& right)
  {
    return _scheduler->CallbackTime () < right._scheduler->CallbackTime();

  }

  //## Operation: CallbackTime%982704557
  //	Returns the Callback Time of this ScheduledObject
  inline DWORD ScheduledObjectPriority::CallbackTime () const
  {
    return _scheduler->CallbackTime ();

  }

  //## Operation: Param%982704558
  //	Returns the Param of this ScheduledObject
  inline void* ScheduledObjectPriority::Param () const
  {
    return _scheduler->Param ();

  }

  //## Operation: Timer%982704559
  //	Returns the Timerof this ScheduledObject
  inline TimerObject* ScheduledObjectPriority::Timer ()
  {
    return _scheduler->Timer ();

  }

  // Class hal_include::ScheduledObject 

  //## Operation: ScheduledObject%982622339
  //	Constructor
  inline ScheduledObject::ScheduledObject (const TimerQueueItem& TimerObject)
    //## begin hal_include::ScheduledObject::ScheduledObject%982622339.hasinit preserve=no
        : valid(true), _timer(TimerObject)
    //## end hal_include::ScheduledObject::ScheduledObject%982622339.hasinit
  {
  }



  //## Other Operations (inline)
  //## Operation: CallbackTime%982638341
  //	Returns the Callback Time of this ScheduledObject
  inline DWORD ScheduledObject::CallbackTime () const
  {
    return _timer.CallbackTime;

  }

  //## Operation: Param%982638346
  //	Returns the Param of this ScheduledObject
  inline void* ScheduledObject::Param () const
  {
    return _timer.pParam;

  }

  //## Operation: Timer%982638347
  //	Returns the Timerof this ScheduledObject
  inline TimerObject* ScheduledObject::Timer ()
  {
    return _timer.pTimer;

  }

} // namespace hal_include

//## begin module%3A92E11B0106.epilog preserve=yes
//## end module%3A92E11B0106.epilog


#endif
