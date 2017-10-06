//## begin module%3CFC0279023A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CFC0279023A.cm

//## begin module%3CFC0279023A.cp preserve=no
//	Angelo Fraietta
//## end module%3CFC0279023A.cp

//## Module: QuestionTask%3CFC0279023A; Pseudo Package specification
//## Subsystem: engineinterface%3A9C858C00CB
//## Source file: d:\develop\smartcontroller\controller\source\engineinterface\questiontask.h

#ifndef questiontask_h
#define questiontask_h 1

//## begin module%3CFC0279023A.additionalIncludes preserve=no
//## end module%3CFC0279023A.additionalIncludes

//## begin module%3CFC0279023A.includes preserve=yes
//## end module%3CFC0279023A.includes

// ActiveObject
#include "activeobject.h"

class StreamedQuestion;
class Event;

//## begin module%3CFC0279023A.additionalDeclarations preserve=yes
//## end module%3CFC0279023A.additionalDeclarations


//## begin QuestionTask%3CFC0279023A.preface preserve=yes
//## end QuestionTask%3CFC0279023A.preface

//## Class: QuestionTask%3CFC0279023A
//## Category: EngineInterface::Question%3AA7F96B037A
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class QuestionTask : public ActiveObject  //## Inherits: <unnamed>%3CFC02A703A9
{
  //## begin QuestionTask%3CFC0279023A.initialDeclarations preserve=yes
  //## end QuestionTask%3CFC0279023A.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: QuestionTask%1023147565
      QuestionTask (StreamedQuestion* pQuestion);

    //## Destructor (generated)
      ~QuestionTask();


    //## Other Operations (specified)
      //## Operation: run%1023147566
      void run ();

      //## Operation: go%1023147567
      bool go (int timeout);

      //## Operation: flush%1029987707
      virtual void flush ();

      //## Operation: wait%1083901317
      void wait ();

    // Additional Public Declarations
      //## begin QuestionTask%3CFC0279023A.public preserve=yes
      //## end QuestionTask%3CFC0279023A.public

  protected:
    // Additional Protected Declarations
      //## begin QuestionTask%3CFC0279023A.protected preserve=yes
      //## end QuestionTask%3CFC0279023A.protected

  private:
    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: _timeout%409B061800BB
      //	The timeout for the waitchdog
      const unsigned get__timeout () const;
      void set__timeout (unsigned value);

    // Additional Private Declarations
      //## begin QuestionTask%3CFC0279023A.private preserve=yes
      //## end QuestionTask%3CFC0279023A.private

  private: //## implementation
    // Data Members for Class Attributes

      //## begin QuestionTask::_timeout%409B061800BB.attr preserve=no  private: unsigned {U} 2000
      unsigned _timeout;
      //## end QuestionTask::_timeout%409B061800BB.attr

    // Data Members for Associations

      //## Association: EngineInterface::Question::<unnamed>%3CFC081802BC
      //## Role: QuestionTask::_pWaitEvent%3CFC081900AA
      //## begin QuestionTask::_pWaitEvent%3CFC081900AA.role preserve=no  public: Event { -> 1RFHN}
      Event *_pWaitEvent;
      //## end QuestionTask::_pWaitEvent%3CFC081900AA.role

      //## Association: EngineInterface::Question::<unnamed>%3CFC17620241
      //## Role: QuestionTask::_pQuestionEvent%3CFC1763012B
      //## begin QuestionTask::_pQuestionEvent%3CFC1763012B.role preserve=no  public: Event { -> 1RFHN}
      Event *_pQuestionEvent;
      //## end QuestionTask::_pQuestionEvent%3CFC1763012B.role

      //## Association: EngineInterface::Question::<unnamed>%3CFC02EF01CC
      //## Role: QuestionTask::_pQuestion%3CFC02F00047
      //## begin QuestionTask::_pQuestion%3CFC02F00047.role preserve=no  public: StreamedQuestion {1 -> 1RFHGN}
      StreamedQuestion *_pQuestion;
      //## end QuestionTask::_pQuestion%3CFC02F00047.role

    // Additional Implementation Declarations
      //## begin QuestionTask%3CFC0279023A.implementation preserve=yes
      //## end QuestionTask%3CFC0279023A.implementation

};

//## begin QuestionTask%3CFC0279023A.postscript preserve=yes
//## end QuestionTask%3CFC0279023A.postscript

// Class QuestionTask 

//## Get and Set Operations for Class Attributes (inline)

inline const unsigned QuestionTask::get__timeout () const
{
  //## begin QuestionTask::get__timeout%409B061800BB.get preserve=no
  return _timeout;
  //## end QuestionTask::get__timeout%409B061800BB.get
}

inline void QuestionTask::set__timeout (unsigned value)
{
  //## begin QuestionTask::set__timeout%409B061800BB.set preserve=no
  _timeout = value;
  //## end QuestionTask::set__timeout%409B061800BB.set
}

//## begin module%3CFC0279023A.epilog preserve=yes
//## end module%3CFC0279023A.epilog


#endif
