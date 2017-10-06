//## begin module%3B494B2701A2.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B494B2701A2.cm

//## begin module%3B494B2701A2.cp preserve=no
//	Angelo Fraietta
//## end module%3B494B2701A2.cp

//## Module: RtemsActiveObject%3B494B2701A2; Package body
//## Subsystem: hal_rtems%3A80A5EB020D
//## Source file: c:\develop\SmartController\controller\source\hal_rtems_pc386\rtemsactiveobject.cpp

//## begin module%3B494B2701A2.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3B494B2701A2.additionalIncludes

//## begin module%3B494B2701A2.includes preserve=yes
//## end module%3B494B2701A2.includes

// TaskThreads
#include "taskthreads.h"
//## begin module%3B494B2701A2.declarations preserve=no
//## end module%3B494B2701A2.declarations

//## begin module%3B494B2701A2.additionalDeclarations preserve=yes
//## end module%3B494B2701A2.additionalDeclarations


//## begin RtemsThread%3B4956A20101.preface preserve=yes
//## end RtemsThread%3B4956A20101.preface

//## Class: RtemsThread%3B4956A20101
//## Category: MultiThread%3B25695D031D
//## Subsystem: hal_rtems%3A80A5EB020D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class RtemsThread : public Thread  //## Inherits: <unnamed>%3B4956B60377
{
  //## begin RtemsThread%3B4956A20101.initialDeclarations preserve=yes
  //## end RtemsThread%3B4956A20101.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: RtemsThread%994657920
      RtemsThread (ActiveObject* pActive);

    //## Destructor (generated)
      ~RtemsThread();


    //## Other Operations (specified)
      //## Operation: resume%994657921
      void resume ();

      //## Operation: wait%994657922
      void wait (unsigned long period	// The period we are going to wait
      );

    // Additional Public Declarations
      //## begin RtemsThread%3B4956A20101.public preserve=yes
      //## end RtemsThread%3B4956A20101.public

  protected:
    // Additional Protected Declarations
      //## begin RtemsThread%3B4956A20101.protected preserve=yes
      //## end RtemsThread%3B4956A20101.protected

  private:
    // Additional Private Declarations
      //## begin RtemsThread%3B4956A20101.private preserve=yes
      //## end RtemsThread%3B4956A20101.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin RtemsThread%3B4956A20101.implementation preserve=yes
      //## end RtemsThread%3B4956A20101.implementation

};

//## begin RtemsThread%3B4956A20101.postscript preserve=yes
//## end RtemsThread%3B4956A20101.postscript

// Class RtemsThread 

// Class RtemsThread 

//## Operation: RtemsThread%994657920
//	Constructor with parameter that points to ActiveObject
RtemsThread::RtemsThread (ActiveObject* pActive)
  //## begin RtemsThread::RtemsThread%994657920.hasinit preserve=no
  //## end RtemsThread::RtemsThread%994657920.hasinit
  //## begin RtemsThread::RtemsThread%994657920.initialization preserve=yes
	:Thread(pActive)
  //## end RtemsThread::RtemsThread%994657920.initialization
{
  //## begin RtemsThread::RtemsThread%994657920.body preserve=yes
  //## end RtemsThread::RtemsThread%994657920.body
}


RtemsThread::~RtemsThread()
{
  //## begin RtemsThread::~RtemsThread%.body preserve=yes
  //## end RtemsThread::~RtemsThread%.body
}



//## Other Operations (implementation)
//## Operation: resume%994657921
void RtemsThread::resume ()
{
  //## begin RtemsThread::resume%994657921.body preserve=yes
  //## end RtemsThread::resume%994657921.body
}

//## Operation: wait%994657922
//	Waits for the thread to finish
void RtemsThread::wait (unsigned long period)
{
  //## begin RtemsThread::wait%994657922.body preserve=yes
  //## end RtemsThread::wait%994657922.body
}

// Additional Declarations
  //## begin RtemsThread%3B4956A20101.declarations preserve=yes
  //## end RtemsThread%3B4956A20101.declarations

//## begin module%3B494B2701A2.epilog preserve=yes
//## end module%3B494B2701A2.epilog
