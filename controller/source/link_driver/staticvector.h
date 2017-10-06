//## begin module%3AEF52B100E2.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AEF52B100E2.cm

//## begin module%3AEF52B100E2.cp preserve=no
//	Angelo Fraietta
//## end module%3AEF52B100E2.cp

//## Module: StaticVector%3AEF52B100E2; Package specification
//## Subsystem: <Top Level>
//## Source file: c:\develop\linkdriver\staticvector.h

#ifndef staticvector_h
#define staticvector_h 1

//## begin module%3AEF52B100E2.additionalIncludes preserve=no
//## end module%3AEF52B100E2.additionalIncludes

//## begin module%3AEF52B100E2.includes preserve=yes
//## end module%3AEF52B100E2.includes

//## begin module%3AEF52B100E2.declarations preserve=no
//## end module%3AEF52B100E2.declarations

//## begin module%3AEF52B100E2.additionalDeclarations preserve=yes
//## end module%3AEF52B100E2.additionalDeclarations


//## begin StaticVector%3AEF40770377.preface preserve=yes
//## end StaticVector%3AEF40770377.preface

//## Class: StaticVector%3AEF40770377
//	This class holds a constant pointer to a pre-allocated
//	array, using it as a vector. There is no overwrapping
//	allowed and the vecor does not get bigger than it's
//	maximum size. The class is passed a BYTE* which must
//	always be in scope during the existance of this class
//## Category: link%3AEF580F01BA
//## Subsystem: <Top Level>
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class StaticVector 
{
  //## begin StaticVector%3AEF40770377.initialDeclarations preserve=yes
  //## end StaticVector%3AEF40770377.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: StaticVector%988756706
      StaticVector (BYTE*& buf, 	// The pointer to the buffer. Must always be in scope
      unsigned buf_size	// The size of the buffer
      );


    //## Other Operations (specified)
      //## Operation: size%988756707
      unsigned size () const;

      //## Operation: reset%988756708
      void reset ();

      //## Operation: data%988756709
      BYTE* data ();

      //## Operation: push%988756710
      bool push (BYTE element);

      //## Operation: full%988756711
      bool full () const;

    // Additional Public Declarations
      //## begin StaticVector%3AEF40770377.public preserve=yes
      //## end StaticVector%3AEF40770377.public

  protected:
    // Additional Protected Declarations
      //## begin StaticVector%3AEF40770377.protected preserve=yes
      //## end StaticVector%3AEF40770377.protected

  private:
    // Additional Private Declarations
      //## begin StaticVector%3AEF40770377.private preserve=yes
      //## end StaticVector%3AEF40770377.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _buf%3AEF42F0035A
      //	This is a refernce to the pointer to the buffer. It must
      //	always be in scope while this class is active.
      //## begin StaticVector::_buf%3AEF42F0035A.attr preserve=no  private: BYTE*& {U} buf
      BYTE*& _buf;
      //## end StaticVector::_buf%3AEF42F0035A.attr

      //## Attribute: _max_size%3AEF43F50098
      //## begin StaticVector::_max_size%3AEF43F50098.attr preserve=no  private: unsigned {U} buf_size
      unsigned _max_size;
      //## end StaticVector::_max_size%3AEF43F50098.attr

      //## Attribute: _size%3AEF4425025A
      //	The size of the vector
      //## begin StaticVector::_size%3AEF4425025A.attr preserve=no  private: unsigned {U} 0
      volatile unsigned _size;
      //## end StaticVector::_size%3AEF4425025A.attr

    // Additional Implementation Declarations
      //## begin StaticVector%3AEF40770377.implementation preserve=yes
      //## end StaticVector%3AEF40770377.implementation

};

//## begin StaticVector%3AEF40770377.postscript preserve=yes
//## end StaticVector%3AEF40770377.postscript

// Class StaticVector 

//## Operation: StaticVector%988756706
//	Constructor that contains the pointer to the data and
//	the maximum size of the data
//## Preconditions:
//	buf must remain a valid pointer for the duration of the
//	class
inline StaticVector::StaticVector (BYTE*& buf, unsigned buf_size)
  //## begin StaticVector::StaticVector%988756706.hasinit preserve=no
      : _buf(buf), _max_size(buf_size), _size(0)
  //## end StaticVector::StaticVector%988756706.hasinit
  //## begin StaticVector::StaticVector%988756706.initialization preserve=yes
  //## end StaticVector::StaticVector%988756706.initialization
{
  //## begin StaticVector::StaticVector%988756706.body preserve=yes
  //## end StaticVector::StaticVector%988756706.body
}



//## Other Operations (inline)
//## Operation: size%988756707
//	returns the size of the data written to this vector
inline unsigned StaticVector::size () const
{
  return _size;

  //## begin StaticVector::size%988756707.body preserve=yes
  //## end StaticVector::size%988756707.body
}

//## Operation: reset%988756708
//	resets the size to zero
inline void StaticVector::reset ()
{
  _size = 0;

  //## begin StaticVector::reset%988756708.body preserve=yes
  //## end StaticVector::reset%988756708.body
}

//## Operation: data%988756709
//	returns the pinter to the buf data
inline BYTE* StaticVector::data ()
{
  return _buf;

  //## begin StaticVector::data%988756709.body preserve=yes
  //## end StaticVector::data%988756709.body
}

//## Operation: push%988756710
//	adds an element to the vector
inline bool StaticVector::push (BYTE element)
{
    bool ret = false;
  
    if (!full())
    {
      _buf[_size] = element;
      _size++;
      ret = true;
    }
  
    return ret;

  //## begin StaticVector::push%988756710.body preserve=yes
  //## end StaticVector::push%988756710.body
}

//## Operation: full%988756711
//	returns true if is full
inline bool StaticVector::full () const
{
  return (_size >= _max_size);

  //## begin StaticVector::full%988756711.body preserve=yes
  //## end StaticVector::full%988756711.body
}

//## begin module%3AEF52B100E2.epilog preserve=yes
//## end module%3AEF52B100E2.epilog


#endif
