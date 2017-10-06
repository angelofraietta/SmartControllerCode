//## begin module%3B25425E0119.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B25425E0119.cm

//## begin module%3B25425E0119.cp preserve=no
//	Angelo Fraietta
//## end module%3B25425E0119.cp

//## Module: AnswerTask%3B25425E0119; Package specification
//	This is a platform dependent interface for the AnswerTask
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\answertask.h

#ifndef answertask_h
#define answertask_h 1

//## begin module%3B25425E0119.additionalIncludes preserve=no
//## end module%3B25425E0119.additionalIncludes

//## begin module%3B25425E0119.includes preserve=yes
//## end module%3B25425E0119.includes

// ActiveObject
#include "activeobject.h"

class PresentationAnswer;
class ActiveThread;
class AnswerTask;
class StreamedAnswer;

//## begin module%3B25425E0119.declarations preserve=no
//## end module%3B25425E0119.declarations

//## begin module%3B25425E0119.additionalDeclarations preserve=yes
class DiagTask; // forward declaration;
//## end module%3B25425E0119.additionalDeclarations


//## begin AnswerTask%3AEF323701FF.preface preserve=yes
//## end AnswerTask%3AEF323701FF.preface

//## Class: AnswerTask%3AEF323701FF
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AnswerTask 
{
  //## begin AnswerTask%3AEF323701FF.initialDeclarations preserve=yes
	friend class DiagTask;
  //## end AnswerTask%3AEF323701FF.initialDeclarations

  public:
    //## Constructors (generated)
      AnswerTask();

    //## Destructor (generated)
      ~AnswerTask();


    //## Other Operations (specified)
      //## Operation: startTask%992232180
      bool startTask (const char* name, 	// the name of the stream to open
      DWORD port_speed	// The speed at which to open the port
      );

      //## Operation: stopTask%992232181
      bool stopTask ();

      //## Operation: processQuestion%992473059
      void processQuestion ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: _default_task%3E48260E01E9
      static const AnswerTask* get__default_task ();
      static void SetDefault (AnswerTask* value);

    // Additional Public Declarations
      //## begin AnswerTask%3AEF323701FF.public preserve=yes
      //## end AnswerTask%3AEF323701FF.public

  protected:
    // Additional Protected Declarations
      //## begin AnswerTask%3AEF323701FF.protected preserve=yes
      //## end AnswerTask%3AEF323701FF.protected

  private:

    //## Other Operations (specified)
      //## Operation: WriteRawData%1044915130
      static void WriteRawData (const char* buf, unsigned long buf_len);

    // Additional Private Declarations
      //## begin AnswerTask%3AEF323701FF.private preserve=yes
      //## end AnswerTask%3AEF323701FF.private

  private: //## implementation
    // Data Members for Class Attributes

      //## begin AnswerTask::_default_task%3E48260E01E9.attr preserve=no  public: static AnswerTask* {U} NULL
      static AnswerTask* _default_task;
      //## end AnswerTask::_default_task%3E48260E01E9.attr

    // Data Members for Associations

      //## Association: hal_include::<unnamed>%3B2543F50197
      //## Role: AnswerTask::_pThread%3B2543F601E8
      //## begin AnswerTask::_pThread%3B2543F601E8.role preserve=no  public: ActiveThread { -> 0..1RFHN}
      ActiveThread *_pThread;
      //## end AnswerTask::_pThread%3B2543F601E8.role

      //## Association: EngineInterface::to engine%3AEF3786011D
      //## Role: AnswerTask::_presentation%3AEF378700EC
      //## begin AnswerTask::_presentation%3AEF378700EC.role preserve=no  public: PresentationAnswer { -> 1RFHN}
      PresentationAnswer *_presentation;
      //## end AnswerTask::_presentation%3AEF378700EC.role

      //## Association: EngineInterface::to patch editor%3AEF37E000AE
      //## Role: AnswerTask::_stream%3AEF37E100EC
      //## begin AnswerTask::_stream%3AEF37E100EC.role preserve=no  public: StreamedAnswer { -> 1RFHN}
      StreamedAnswer *_stream;
      //## end AnswerTask::_stream%3AEF37E100EC.role

    // Additional Implementation Declarations
      //## begin AnswerTask%3AEF323701FF.implementation preserve=yes
      //## end AnswerTask%3AEF323701FF.implementation

    friend class ActiveThread;
};

//## begin AnswerTask%3AEF323701FF.postscript preserve=yes
extern "C" void DisplayDiags(const char* message);
//## end AnswerTask%3AEF323701FF.postscript

//## begin ActiveThread%3B25439B01E7.preface preserve=yes
//## end ActiveThread%3B25439B01E7.preface

//## Class: ActiveThread%3B25439B01E7
//	This is the platform dependent thread or task that
//	actually runs.  It is defined within the package body of
//	the AnswerTask
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class ActiveThread : public ActiveObject  //## Inherits: <unnamed>%3B4A3B7F02B2
{
  //## begin ActiveThread%3B25439B01E7.initialDeclarations preserve=yes
  //## end ActiveThread%3B25439B01E7.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ActiveThread%992298027
      ActiveThread (AnswerTask* pTask);

    //## Destructor (generated)
      ~ActiveThread();


    //## Other Operations (specified)
      //## Operation: run%992298026
      void run ();

    // Additional Public Declarations
      //## begin ActiveThread%3B25439B01E7.public preserve=yes
      //## end ActiveThread%3B25439B01E7.public

  protected:
    // Additional Protected Declarations
      //## begin ActiveThread%3B25439B01E7.protected preserve=yes
      //## end ActiveThread%3B25439B01E7.protected

  private:
    // Additional Private Declarations
      //## begin ActiveThread%3B25439B01E7.private preserve=yes
      //## end ActiveThread%3B25439B01E7.private

  private: //## implementation
    // Data Members for Associations

      //## Association: hal_include::<unnamed>%3B2543F50197
      //## Role: ActiveThread::_pTask%3B2543F601D4
      //## begin ActiveThread::_pTask%3B2543F601D4.role preserve=no  public: AnswerTask {0..1 -> RFHGN}
      AnswerTask *_pTask;
      //## end ActiveThread::_pTask%3B2543F601D4.role

    // Additional Implementation Declarations
      //## begin ActiveThread%3B25439B01E7.implementation preserve=yes
      //## end ActiveThread%3B25439B01E7.implementation

    friend class AnswerTask;
};

//## begin ActiveThread%3B25439B01E7.postscript preserve=yes
//## end ActiveThread%3B25439B01E7.postscript

// Class AnswerTask 

//## Get and Set Operations for Class Attributes (inline)

inline const AnswerTask* AnswerTask::get__default_task ()
{
  //## begin AnswerTask::get__default_task%3E48260E01E9.get preserve=no
  return _default_task;
  //## end AnswerTask::get__default_task%3E48260E01E9.get
}

inline void AnswerTask::SetDefault (AnswerTask* value)
{
  //## begin AnswerTask::SetDefault%3E48260E01E9.set preserve=no
  _default_task = value;
  //## end AnswerTask::SetDefault%3E48260E01E9.set
}

// Class ActiveThread 

//## begin module%3B25425E0119.epilog preserve=yes
//## end module%3B25425E0119.epilog


#endif
