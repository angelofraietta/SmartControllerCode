//## begin module%3AE8AB5503DE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AE8AB5503DE.cm

//## begin module%3AE8AB5503DE.cp preserve=no
//	Angelo Fraietta
//## end module%3AE8AB5503DE.cp

//## Module: LinkProtocol%3AE8AB5503DE; Package specification
//	Contains specifications for the link protocol
//## Subsystem: link_driver%3D7412070347
//## Source file: c:\develop\Winsmartcontroller\controller\source\link_driver\linkprotocol.h

#ifndef linkprotocol_h
#define linkprotocol_h 1

//## begin module%3AE8AB5503DE.additionalIncludes preserve=no
//## end module%3AE8AB5503DE.additionalIncludes

//## begin module%3AE8AB5503DE.includes preserve=yes
//## end module%3AE8AB5503DE.includes

// StaticVector
#include "staticvector.h"
// ControlFilter
#include "controlfilter.h"
//## begin module%3AE8AB5503DE.declarations preserve=no
//## end module%3AE8AB5503DE.declarations

//## begin module%3AE8AB5503DE.additionalDeclarations preserve=yes
//## end module%3AE8AB5503DE.additionalDeclarations


//## begin DecodeMessageType%3AE7A6B80073.preface preserve=yes
//## end DecodeMessageType%3AE7A6B80073.preface

//## Class: DecodeMessageType%3AE7A6B80073
//	The Decode Message is a return value after attempting to
//	perform a decode
//## Category: link_driver::link%3AEF580F01BA
//## Subsystem: link_driver%3D7412070347
//## Persistence: Transient
//## Cardinality/Multiplicity: n

typedef enum{DECODE_SUCCESS, DECODE_INCOMPLETE, BUFFER_FULL} DecodeMessageType;

//## begin DecodeMessageType%3AE7A6B80073.postscript preserve=yes
//## end DecodeMessageType%3AE7A6B80073.postscript

//## begin LinkProtocol%3AE7A56003C1.preface preserve=yes
//## end LinkProtocol%3AE7A56003C1.preface

//## Class: LinkProtocol%3AE7A56003C1
//## Category: link_driver::link%3AEF580F01BA
//## Subsystem: link_driver%3D7412070347
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: returns%3AE8ABA503D9;DecodeMessageType { -> }

class LinkProtocol 
{
  //## begin LinkProtocol%3AE7A56003C1.initialDeclarations preserve=yes
  //## end LinkProtocol%3AE7A56003C1.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: LinkProtocol%988323866
      LinkProtocol (BYTE* buf = NULL, 	// This is a pre-allocated buffer. If the parameter is
      	// provided, it must remain within scope for the duration
      	// of the class instance. If no buffer is provided, a
      	// Buffer of max_size is created and maintained by this
      	// class
      unsigned max_size = 8192	// this is the maximum size that can be transmitted though
      	// this layer
      );

    //## Destructor (generated)
      ~LinkProtocol();


    //## Other Operations (specified)
      //## Operation: EncodeData%988245429
      unsigned EncodeData (const BYTE* source, 	// this is the unenecoded data
      unsigned source_size, 	// size of the source buffer
      BYTE* target	// The target buffer where the encoded data will go
      );

      //## Operation: DecodeData%988245430
      DecodeMessageType DecodeData (const BYTE* source, 	// this is the unenecoded data
      unsigned source_size	// size of the source buffer
      );

      //## Operation: EncodeBufferSize%988323864
      unsigned EncodeBufferSize (const BYTE* source, 	// this is the unenecoded data
      unsigned source_size	// size of the source buffer
      ) const;

      //## Operation: reset%988323867
      void reset ();

      //## Operation: create%988756713
      static LinkProtocol* create (BYTE* buf = NULL, 	// This is a pre-allocated buffer. If the parameter is
      	// provided, it must remain within scope for the duration
      	// of the class instance. If no buffer is provided, a
      	// Buffer of max_size is created and maintained by this
      	// class
      unsigned max_size = 1024	// this is the maximum size that can be transmitted though
      	// this layer
      );

      //## Operation: decode_size%988756722
      unsigned decode_size () const;

      //## Operation: decode_data%988756723
      const BYTE* decode_data ();

    // Additional Public Declarations
      //## begin LinkProtocol%3AE7A56003C1.public preserve=yes
      //## end LinkProtocol%3AE7A56003C1.public

  protected:
    // Additional Protected Declarations
      //## begin LinkProtocol%3AE7A56003C1.protected preserve=yes
      //## end LinkProtocol%3AE7A56003C1.protected

  private:
    // Additional Private Declarations
      //## begin LinkProtocol%3AE7A56003C1.private preserve=yes
      //## end LinkProtocol%3AE7A56003C1.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _running_dle%3AE8FCCD004E
      //	The state of the running dle char. required for decoding
      //## begin LinkProtocol::_running_dle%3AE8FCCD004E.attr preserve=no  private: bool {U} false
      bool _running_dle;
      //## end LinkProtocol::_running_dle%3AE8FCCD004E.attr

      //## Attribute: _start_found%3AE8FEA0028B
      //	Becomes true when start has already been found
      //## begin LinkProtocol::_start_found%3AE8FEA0028B.attr preserve=no  private: bool {U} false
      bool _start_found;
      //## end LinkProtocol::_start_found%3AE8FEA0028B.attr


      //## Attribute: _frame_chars%3AE8CEDC002F
      //	This is the characters that defines the frame
      //## begin LinkProtocol::_frame_chars%3AE8CEDC002F.attr preserve=no  private: static BYTE[] {U} {_stx, _etx}
      static BYTE _frame_chars[];
      //## end LinkProtocol::_frame_chars%3AE8CEDC002F.attr

      //## Attribute: _stx%3AE8D51F028D
      //	This is the frame start byte
      //## begin LinkProtocol::_stx%3AE8D51F028D.attr preserve=no  private: static BYTE {U} 0x01
      static BYTE _stx;
      //## end LinkProtocol::_stx%3AE8D51F028D.attr

      //## Attribute: _etx%3AE8FAE20201
      //## begin LinkProtocol::_etx%3AE8FAE20201.attr preserve=no  private: static BYTE {U} 0x03
      static BYTE _etx;
      //## end LinkProtocol::_etx%3AE8FAE20201.attr

      //## Attribute: _max_size%3AE8D7670214
      //	The maximum size the protocaol can support
      //## begin LinkProtocol::_max_size%3AE8D7670214.attr preserve=no  private: unsigned {U} max_size
      unsigned _max_size;
      //## end LinkProtocol::_max_size%3AE8D7670214.attr

      //## Attribute: _buf%3AEF47FE026A
      //	This is the buffer of the link protocol
      //## begin LinkProtocol::_buf%3AEF47FE026A.attr preserve=no  private: BYTE* {U} buf
      BYTE* _buf;
      //## end LinkProtocol::_buf%3AEF47FE026A.attr

      //## Attribute: _alloc_buf%3AEF49A500EC
      //	This is the data that has been allocated by this class,
      //	and as such must be deleted when the class goes out of
      //	scope
      //## begin LinkProtocol::_alloc_buf%3AEF49A500EC.attr preserve=no  private: BYTE* {U} NULL
      BYTE* _alloc_buf;
      //## end LinkProtocol::_alloc_buf%3AEF49A500EC.attr

    // Data Members for Associations

      //## Association: encoder%3AE8D28C01DB
      //## Role: LinkProtocol::_filter%3AE8D28C03DA
      //## begin LinkProtocol::_filter%3AE8D28C03DA.role preserve=no  private: ControlFilter { -> 1VHN}
      ControlFilter _filter;
      //## end LinkProtocol::_filter%3AE8D28C03DA.role

      //## Association: its queue%3AEF45E803D5
      //## Role: LinkProtocol::_rxq%3AEF45EB0003
      //## begin LinkProtocol::_rxq%3AEF45EB0003.role preserve=no  public: StaticVector { -> 1VHN}
      StaticVector _rxq;
      //## end LinkProtocol::_rxq%3AEF45EB0003.role

    // Additional Implementation Declarations
      //## begin LinkProtocol%3AE7A56003C1.implementation preserve=yes
      //## end LinkProtocol%3AE7A56003C1.implementation

};

//## begin LinkProtocol%3AE7A56003C1.postscript preserve=yes
//## end LinkProtocol%3AE7A56003C1.postscript

// Class LinkProtocol 

//## begin module%3AE8AB5503DE.epilog preserve=yes
//## end module%3AE8AB5503DE.epilog


#endif
