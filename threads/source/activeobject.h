//## begin module%3B25578F0192.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B25578F0192.cm

//## begin module%3B25578F0192.cp preserve=no
//	Angelo Fraietta
//## end module%3B25578F0192.cp

//## Module: ActiveObject%3B25578F0192; Pseudo Package specification
//## Subsystem: <Top Level>
//## Source file: c:\develop\multithreads\source\activeobject.h

#ifndef activeobject_h
#define activeobject_h 1

//## begin module%3B25578F0192.additionalIncludes preserve=no
//## end module%3B25578F0192.additionalIncludes

//## begin module%3B25578F0192.includes preserve=yes
//## end module%3B25578F0192.includes


class MultiThread;

//## begin module%3B25578F0192.additionalDeclarations preserve=yes
//## end module%3B25578F0192.additionalDeclarations


//## begin ActiveObject%3B25578F0192.preface preserve=yes
//## end ActiveObject%3B25578F0192.preface

//## Class: ActiveObject%3B25578F0192
//## Category: MultiThread%3B2568A6002B
//## Subsystem: <Top Level>
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class ActiveObject 
{
  //## begin ActiveObject%3B25578F0192.initialDeclarations preserve=yes
  //## end ActiveObject%3B25578F0192.initialDeclarations

  public:
    //## Constructors (generated)
      ActiveObject();

    //## Destructor (generated)
      virtual ~ActiveObject();


    //## Other Operations (specified)
      //## Operation: initialise%992298018
      virtual void initialise ();

      //## Operation: run%992298019
      virtual void run () = 0;

      //## Operation: flush%992298020
      virtual void flush ();

      //## Operation: start%992298021
      void start ();

      //## Operation: kill%992298025
      void kill ();

    // Additional Public Declarations
      //## begin ActiveObject%3B25578F0192.public preserve=yes
      //## end ActiveObject%3B25578F0192.public

  protected:
    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: _terminate%3B2559A4036F
      //	Becomes thru when we have to exit the thread
      const bool Terminated () const;

    // Additional Protected Declarations
      //## begin ActiveObject%3B25578F0192.protected preserve=yes
      //## end ActiveObject%3B25578F0192.protected

  private:
    // Additional Private Declarations
      //## begin ActiveObject%3B25578F0192.private preserve=yes
      //## end ActiveObject%3B25578F0192.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _started%3B2558F0019A
      //## begin ActiveObject::_started%3B2558F0019A.attr preserve=no  private: bool {UT} false
      volatile bool  _started;
      //## end ActiveObject::_started%3B2558F0019A.attr

      //## begin ActiveObject::_terminate%3B2559A4036F.attr preserve=no  protected: bool {UT} false
      volatile bool  _terminate;
      //## end ActiveObject::_terminate%3B2559A4036F.attr

    // Data Members for Associations

      //## Association: <unnamed>%3B255975026D
      //## Role: ActiveObject::_pThread%3B2559760052
      //## begin ActiveObject::_pThread%3B2559760052.role preserve=no  public: MultiThread {1 -> 1RFHN}
      MultiThread *_pThread;
      //## end ActiveObject::_pThread%3B2559760052.role

    // Additional Implementation Declarations
      //## begin ActiveObject%3B25578F0192.implementation preserve=yes
      //## end ActiveObject%3B25578F0192.implementation

};

//## begin ActiveObject%3B25578F0192.postscript preserve=yes
//## end ActiveObject%3B25578F0192.postscript

// Class ActiveObject 


//## Other Operations (inline)
//## Operation: flush%992298020
//	Abstract function that tells superclass to stop what it
//	is doing and return.
inline void ActiveObject::flush ()
{
  //## begin ActiveObject::flush%992298020.body preserve=yes
  //## end ActiveObject::flush%992298020.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const bool ActiveObject::Terminated () const
{
  //## begin ActiveObject::Terminated%3B2559A4036F.get preserve=no
  return _terminate;
  //## end ActiveObject::Terminated%3B2559A4036F.get
}

//## begin module%3B25578F0192.epilog preserve=yes
//## end module%3B25578F0192.epilog


#endif
