//## begin module%3AEF8F170294.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AEF8F170294.cm

//## begin module%3AEF8F170294.cp preserve=no
//	Angelo Fraietta
//## end module%3AEF8F170294.cp

//## Module: ControlFilter%3AEF8F170294; Package specification
//## Subsystem: <Top Level>
//## Source file: c:\develop\linkdriver\controlfilter.h

#ifndef controlfilter_h
#define controlfilter_h 1

//## begin module%3AEF8F170294.additionalIncludes preserve=no
//## end module%3AEF8F170294.additionalIncludes

//## begin module%3AEF8F170294.includes preserve=yes
//## end module%3AEF8F170294.includes

//## begin module%3AEF8F170294.declarations preserve=no
//## end module%3AEF8F170294.declarations

//## begin module%3AEF8F170294.additionalDeclarations preserve=yes
//## end module%3AEF8F170294.additionalDeclarations


//## begin ControlFilter%3AE8B5040049.preface preserve=yes
//## end ControlFilter%3AE8B5040049.preface

//## Class: ControlFilter%3AE8B5040049
//	Encodes and Decodes control characters
//## Category: link%3AEF580F01BA
//## Subsystem: <Top Level>
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class ControlFilter 
{
  //## begin ControlFilter%3AE8B5040049.initialDeclarations preserve=yes
  //## end ControlFilter%3AE8B5040049.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ControlFilter%988323860
      ControlFilter (const BYTE* control_chars, 	// The control characters that require encoding
      unsigned buf_size, 	// the size of control_chars
      BYTE dle_char = 0x10, 	// The DLE character to place before encoded char
      BYTE offset = 0x20	// the DLE offset
      );


    //## Other Operations (specified)
      //## Operation: Encode%988323861
      BYTE Encode (BYTE* c	// the Byte to be encoded
      ) const;

      //## Operation: Decode%988323862
      bool Decode (BYTE* c, 	// the char to be decoded
      bool* running_dle	// the running dle status
      ) const;

      //## Operation: Valid%988323863
      bool Valid () const;

    // Additional Public Declarations
      //## begin ControlFilter%3AE8B5040049.public preserve=yes
      //## end ControlFilter%3AE8B5040049.public

  protected:
    // Additional Protected Declarations
      //## begin ControlFilter%3AE8B5040049.protected preserve=yes
      //## end ControlFilter%3AE8B5040049.protected

  private:
    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: _dle_offset%3AE8B76F0248
      //	The offset to add to the control chars
      const BYTE get__dle_offset () const;
      void set__dle_offset (BYTE value);

      //## Attribute: _dle_char%3AE8B8740149
      const BYTE get__dle_char () const;
      void set__dle_char (BYTE value);

    // Additional Private Declarations
      //## begin ControlFilter%3AE8B5040049.private preserve=yes
      //## end ControlFilter%3AE8B5040049.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _control_chars%3AE8B6E20368
      //	this contains the list of BYTES that are control
      //	characters, and thus require encoding
      //## begin ControlFilter::_control_chars%3AE8B6E20368.attr preserve=no  private: const BYTE*const {U} control_chars
      const BYTE*const _control_chars;
      //## end ControlFilter::_control_chars%3AE8B6E20368.attr

      //## Attribute: _buf_size%3AE8B72D0153
      //	The size of the _control_chars buffer
      //## begin ControlFilter::_buf_size%3AE8B72D0153.attr preserve=no  private: unsigned {U} buf_size
      unsigned _buf_size;
      //## end ControlFilter::_buf_size%3AE8B72D0153.attr

      //## begin ControlFilter::_dle_offset%3AE8B76F0248.attr preserve=no  private: BYTE {U} offset
      BYTE _dle_offset;
      //## end ControlFilter::_dle_offset%3AE8B76F0248.attr

      //## begin ControlFilter::_dle_char%3AE8B8740149.attr preserve=no  private: BYTE {U} dle_char
      BYTE _dle_char;
      //## end ControlFilter::_dle_char%3AE8B8740149.attr

    // Additional Implementation Declarations
      //## begin ControlFilter%3AE8B5040049.implementation preserve=yes
      //## end ControlFilter%3AE8B5040049.implementation

};

//## begin ControlFilter%3AE8B5040049.postscript preserve=yes
//## end ControlFilter%3AE8B5040049.postscript

// Class ControlFilter 

//## Operation: ControlFilter%988323860
//	Constructor that initialises the BYTE buffer containing
//	the control chars, the size of the buffer, and the DLE
//	offset
inline ControlFilter::ControlFilter (const BYTE* control_chars, unsigned buf_size, BYTE dle_char, BYTE offset)
  //## begin ControlFilter::ControlFilter%988323860.hasinit preserve=no
      : _control_chars(control_chars), _buf_size(buf_size), _dle_offset(offset), _dle_char(dle_char)
  //## end ControlFilter::ControlFilter%988323860.hasinit
  //## begin ControlFilter::ControlFilter%988323860.initialization preserve=yes
  //## end ControlFilter::ControlFilter%988323860.initialization
{
  //## begin ControlFilter::ControlFilter%988323860.body preserve=yes
  //## end ControlFilter::ControlFilter%988323860.body
}



//## Other Operations (inline)
//## Operation: Encode%988323861
//	encodes the inputed character and returns the DLE
//	required. If no DLE is required, 0x00 is returned,
//	otherwise the DLE char
inline BYTE ControlFilter::Encode (BYTE* c) const
{
    for (unsigned i = 0; i < _buf_size; i++)
      {
        if (*c == _control_chars[i]) // then requires Byte stuffing
        {
          *c += _dle_offset;
          return _dle_char;
        }
      }
  
    if (*c == _dle_char)
    {
      *c += _dle_offset;
      return _dle_char;
    }
    return 0x00;

  //## begin ControlFilter::Encode%988323861.body preserve=yes
  //## end ControlFilter::Encode%988323861.body
}

//## Operation: Decode%988323862
//	Decodes the character and returns true if a valid char.
//	The running DLE status is also modified
inline bool ControlFilter::Decode (BYTE* c, bool* running_dle) const
{
    bool valid;
    if (*running_dle)           // the previous char was a DLE char
      {                         //  This char is an encoded in band char
      *c -= _dle_offset;          // convert this one - subtract offset
      *running_dle = false;     //  clear running dle
      valid =  true;            // *c is a valid char
      }
  
    else
      {                          // is this the DLE char?
      if (*c == _dle_char)       // The char following this one
        {                        // will need converting
        *running_dle = true;     // set flag
        valid = false;           // this is an invalid cha
        }
  
      else
        {
        if (Encode(c))            // this is a DLE char that
          {                       // requires filtering out
          *running_dle = false;   // this is an out of band char
          valid = false;
          }
  
        else
          {
          valid = true;           // this is an un-encoded in band char
          }
  
        }
  
      }
  
    return valid;

  //## begin ControlFilter::Decode%988323862.body preserve=yes
  //## end ControlFilter::Decode%988323862.body
}

//## Operation: Valid%988323863
//	Returns true if the parameters of the constructor are
//	valid. This means that adding a DLE offset will not
//	create a DLE char
inline bool ControlFilter::Valid () const
{
    for (unsigned i = 0; i < _buf_size; i++)
      {
        BYTE c = (BYTE) (_control_chars[i] + _dle_offset);
        if (Encode (&c)) // then converted value is a dle char and as such is invalid
        {
          return false;
        }
      }
  
    return true;


  //## begin ControlFilter::Valid%988323863.body preserve=yes
  //## end ControlFilter::Valid%988323863.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const BYTE ControlFilter::get__dle_offset () const
{
  //## begin ControlFilter::get__dle_offset%3AE8B76F0248.get preserve=no
  return _dle_offset;
  //## end ControlFilter::get__dle_offset%3AE8B76F0248.get
}

inline void ControlFilter::set__dle_offset (BYTE value)
{
  //## begin ControlFilter::set__dle_offset%3AE8B76F0248.set preserve=no
  _dle_offset = value;
  //## end ControlFilter::set__dle_offset%3AE8B76F0248.set
}

inline const BYTE ControlFilter::get__dle_char () const
{
  //## begin ControlFilter::get__dle_char%3AE8B8740149.get preserve=no
  return _dle_char;
  //## end ControlFilter::get__dle_char%3AE8B8740149.get
}

inline void ControlFilter::set__dle_char (BYTE value)
{
  //## begin ControlFilter::set__dle_char%3AE8B8740149.set preserve=no
  _dle_char = value;
  //## end ControlFilter::set__dle_char%3AE8B8740149.set
}

//## begin module%3AEF8F170294.epilog preserve=yes
//## end module%3AEF8F170294.epilog


#endif
