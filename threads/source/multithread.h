//## begin module%3B25606D033B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B25606D033B.cm

//## begin module%3B25606D033B.cp preserve=no
//	Angelo Fraietta
//## end module%3B25606D033B.cp

//## Module: MultiThread%3B25606D033B; Package specification
//## Subsystem: <Top Level>
//## Source file: c:\develop\multithreads\source\multithread.h

#ifndef multithread_h
#define multithread_h 1

//## begin module%3B25606D033B.additionalIncludes preserve=no
//## end module%3B25606D033B.additionalIncludes

//## begin module%3B25606D033B.includes preserve=yes
//## end module%3B25606D033B.includes


class MacThread;
class WindowsThread;
class RtemsThread;
class ActiveObject;

//## begin module%3B25606D033B.declarations preserve=no
//## end module%3B25606D033B.declarations

//## begin module%3B25606D033B.additionalDeclarations preserve=yes
//## end module%3B25606D033B.additionalDeclarations


//## begin MultiThread%3B255966033E.preface preserve=yes
//## end MultiThread%3B255966033E.preface

//## Class: MultiThread%3B255966033E; Abstract
//	A different specification and implementation is required
//	for each platform.
//## Category: MultiThread%3B2568A6002B
//## Subsystem: <Top Level>
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3B4A2B9A0225;RtemsThread { -> F}
//## Uses: <unnamed>%3B4A2B9D008F;WindowsThread { -> F}
//## Uses: <unnamed>%3D47199C0132;MacThread { -> F}

class MultiThread 
{
  //## begin MultiThread%3B255966033E.initialDeclarations preserve=yes
  //## end MultiThread%3B255966033E.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: MultiThread%992298022
      MultiThread (ActiveObject* pActive);

    //## Destructor (generated)
      virtual ~MultiThread();


    //## Other Operations (specified)
      //## Operation: resume%992298023
      virtual void resume () = 0;

      //## Operation: wait%992298024
      virtual void wait (unsigned long period	// The period we are going to wait
      ) = 0;

      //## Operation: create%994716922
      static MultiThread* create (ActiveObject* pActive);

    // Additional Public Declarations
      //## begin MultiThread%3B255966033E.public preserve=yes
      //## end MultiThread%3B255966033E.public

  protected:
    // Data Members for Associations

      //## Association: <unnamed>%3B255975026D
      //## Role: MultiThread::_pActive%3B255976005C
      //## begin MultiThread::_pActive%3B255976005C.role preserve=no  public: ActiveObject {1 -> 1RFHN}
      ActiveObject *_pActive;
      //## end MultiThread::_pActive%3B255976005C.role

    // Additional Protected Declarations
      //## begin MultiThread%3B255966033E.protected preserve=yes
      //## end MultiThread%3B255966033E.protected

  private:
    // Additional Private Declarations
      //## begin MultiThread%3B255966033E.private preserve=yes
      //## end MultiThread%3B255966033E.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin MultiThread%3B255966033E.implementation preserve=yes
      //## end MultiThread%3B255966033E.implementation

};

//## begin MultiThread%3B255966033E.postscript preserve=yes
//## end MultiThread%3B255966033E.postscript

// Class MultiThread 

//## Operation: MultiThread%992298022
//	Constructor with parameter that points to ActiveObject
inline MultiThread::MultiThread (ActiveObject* pActive)
  //## begin MultiThread::MultiThread%992298022.hasinit preserve=no
      : _pActive(pActive)
  //## end MultiThread::MultiThread%992298022.hasinit
  //## begin MultiThread::MultiThread%992298022.initialization preserve=yes
  //## end MultiThread::MultiThread%992298022.initialization
{
  //## begin MultiThread::MultiThread%992298022.body preserve=yes
  //## end MultiThread::MultiThread%992298022.body
}


inline MultiThread::~MultiThread()
{
  //## begin MultiThread::~MultiThread%.body preserve=yes
  //## end MultiThread::~MultiThread%.body
}


//## begin module%3B25606D033B.epilog preserve=yes
//## end module%3B25606D033B.epilog


#endif
