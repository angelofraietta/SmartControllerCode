//## begin module%3AE7AEB8023A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AE7AEB8023A.cm

//## begin module%3AE7AEB8023A.cp preserve=no
//	Angelo Fraietta
//## end module%3AE7AEB8023A.cp

//## Module: RingQueue%3AE7AEB8023A; Pseudo Package specification
//## Source file: c:\develop\linkdriver\ringqueue.h

#ifndef ringqueue_h
#define ringqueue_h 1

//## begin module%3AE7AEB8023A.additionalIncludes preserve=no
//## end module%3AE7AEB8023A.additionalIncludes

//## begin module%3AE7AEB8023A.includes preserve=yes
//## end module%3AE7AEB8023A.includes

//## begin module%3AE7AEB8023A.additionalDeclarations preserve=yes
//## end module%3AE7AEB8023A.additionalDeclarations


//## begin RingQueue%3AE7AEB8023A.preface preserve=yes
//## end RingQueue%3AE7AEB8023A.preface

//## Class: RingQueue%3AE7AEB8023A
//	Implementation of a ring queue
//## Category: <Top Level>
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class RingQueue 
{
  //## begin RingQueue%3AE7AEB8023A.initialDeclarations preserve=yes
  //## end RingQueue%3AE7AEB8023A.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: RingQueue%988323848
      RingQueue (int size);

    //## Destructor (specified)
      //## Operation: ~RingQueue%988323849
      ~RingQueue ();


    //## Other Operations (specified)
      //## Operation: size%988323850
      int size () const;

      //## Operation: push%988323851
      bool push (BYTE element);

      //## Operation: front%988323852
      BYTE front () const;

      //## Operation: back%988323853
      BYTE back () const;

      //## Operation: pop%988323854
      void pop ();

      //## Operation: full%988323855
      bool full () const;

      //## Operation: empty%988323856
      bool empty () const;

      //## Operation: reset%988323857
      void reset ();

      //## Operation: read%988323858
      int read (BYTE* buf, int buf_size	// size of buffer
      );

      //## Operation: write%988323859
      int write (const BYTE* buf, int buf_size	// size of buffer
      );

    // Additional Public Declarations
      //## begin RingQueue%3AE7AEB8023A.public preserve=yes
      //## end RingQueue%3AE7AEB8023A.public

  protected:
    // Additional Protected Declarations
      //## begin RingQueue%3AE7AEB8023A.protected preserve=yes
      //## end RingQueue%3AE7AEB8023A.protected

  private:
    // Additional Private Declarations
      //## begin RingQueue%3AE7AEB8023A.private preserve=yes
      //## end RingQueue%3AE7AEB8023A.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _size%3AE7AF0500F0
      //## begin RingQueue::_size%3AE7AF0500F0.attr preserve=no  private: int {U} size
      int _size;
      //## end RingQueue::_size%3AE7AF0500F0.attr

      //## Attribute: _buf%3AE7AF6B0364
      //	This is the buffer that has the data in it
      //## begin RingQueue::_buf%3AE7AF6B0364.attr preserve=no  private: BYTE* {U} NULL
      BYTE* _buf;
      //## end RingQueue::_buf%3AE7AF6B0364.attr

      //## Attribute: _head%3AE7AFD4012A
      //## begin RingQueue::_head%3AE7AFD4012A.attr preserve=no  private: int {U} 0
      int _head;
      //## end RingQueue::_head%3AE7AFD4012A.attr

      //## Attribute: _tail%3AE7B011033B
      //## begin RingQueue::_tail%3AE7B011033B.attr preserve=no  private: int {U} 0
      int _tail;
      //## end RingQueue::_tail%3AE7B011033B.attr

      //## Attribute: _empty%3AE89D440368
      //## begin RingQueue::_empty%3AE89D440368.attr preserve=no  private: bool {U} true
      bool _empty;
      //## end RingQueue::_empty%3AE89D440368.attr

    // Additional Implementation Declarations
      //## begin RingQueue%3AE7AEB8023A.implementation preserve=yes
      //## end RingQueue%3AE7AEB8023A.implementation

};

//## begin RingQueue%3AE7AEB8023A.postscript preserve=yes
//## end RingQueue%3AE7AEB8023A.postscript

// Class RingQueue 

//## Operation: RingQueue%988323848
inline RingQueue::RingQueue (int size)
  //## begin RingQueue::RingQueue%988323848.hasinit preserve=no
      : _size(size), _buf(NULL), _head(0), _tail(0), _empty(true)
  //## end RingQueue::RingQueue%988323848.hasinit
  //## begin RingQueue::RingQueue%988323848.initialization preserve=yes
  //## end RingQueue::RingQueue%988323848.initialization
{
  //## begin RingQueue::RingQueue%988323848.body preserve=yes
  //## end RingQueue::RingQueue%988323848.body

  _buf = new BYTE [size];
}


//## Operation: ~RingQueue%988323849
//	destructor
inline RingQueue::~RingQueue ()
{
  //## begin RingQueue::~RingQueue%988323849.body preserve=yes
  //## end RingQueue::~RingQueue%988323849.body

  delete [] _buf;
}



//## Other Operations (inline)
//## Operation: size%988323850
//	returns the number of elements in the queue
inline int RingQueue::size () const
{
  int size ;
  if (full())
     return _size;
  
  if (_head < _tail)
    {
    size = _head + _size - _tail;
    }
  else
    {
    size = _head - _tail;
    }
  
  return size;

  //## begin RingQueue::size%988323850.body preserve=yes
  //## end RingQueue::size%988323850.body
}

//## Operation: push%988323851
//	adds an element to the queue
inline bool RingQueue::push (BYTE element)
{
    bool ret = false;
  
    if (!full())
    {
      _empty = false;
      _buf[_tail] = element;
      _tail++;
      _tail = _tail % _size;
      ret = true;
    }
  
    return ret;

  //## begin RingQueue::push%988323851.body preserve=yes
  //## end RingQueue::push%988323851.body
}

//## Operation: front%988323852
//	returns but does not remove item at front of queue
inline BYTE RingQueue::front () const
{
  return _buf [_head];

  //## begin RingQueue::front%988323852.body preserve=yes
  //## end RingQueue::front%988323852.body
}

//## Operation: back%988323853
//	returns but does not remove item at back of queue
inline BYTE RingQueue::back () const
{
  return _buf [_tail];

  //## begin RingQueue::back%988323853.body preserve=yes
  //## end RingQueue::back%988323853.body
}

//## Operation: pop%988323854
//	removes element from the front
inline void RingQueue::pop ()
{
      if (!empty())
      {
        _head++;
        _head = _head % _size;
        if (_head == _tail)
        {
          _empty = true;
        }
      }

  //## begin RingQueue::pop%988323854.body preserve=yes
  //## end RingQueue::pop%988323854.body
}

//## Operation: full%988323855
//	returns true if queue is full
inline bool RingQueue::full () const
{
  return (!_empty) && (_head == _tail);

  //## begin RingQueue::full%988323855.body preserve=yes
  //## end RingQueue::full%988323855.body
}

//## Operation: empty%988323856
//	returns true if queue is empty
inline bool RingQueue::empty () const
{
  return _empty;

  //## begin RingQueue::empty%988323856.body preserve=yes
  //## end RingQueue::empty%988323856.body
}

//## Operation: reset%988323857
//	initialises the queue
inline void RingQueue::reset ()
{
  _head = 0;
  _tail = 0;
  _empty = true;

  //## begin RingQueue::reset%988323857.body preserve=yes
  //## end RingQueue::reset%988323857.body
}

//## begin module%3AE7AEB8023A.epilog preserve=yes
//## end module%3AE7AEB8023A.epilog


#endif
