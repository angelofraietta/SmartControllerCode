//## begin module%3AEF67BA0167.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AEF67BA0167.cm

//## begin module%3AEF67BA0167.cp preserve=no
//	Angelo Fraietta
//## end module%3AEF67BA0167.cp

//## Module: LinkLayer%3AEF67BA0167; Pseudo Package specification
//## Subsystem: link_driver%3D7412070347
//## Source file: D:\develop\Smartcontroller\controller\source\link_driver\linklayer.h

#ifndef linklayer_h
#define linklayer_h 1

//## begin module%3AEF67BA0167.additionalIncludes preserve=no
//## end module%3AEF67BA0167.additionalIncludes

//## begin module%3AEF67BA0167.includes preserve=yes
//## end module%3AEF67BA0167.includes

// NetworkLayer
#include "networklayer.h"

class CommStream;
class LinkProtocol;

//## begin module%3AEF67BA0167.additionalDeclarations preserve=yes
//## end module%3AEF67BA0167.additionalDeclarations


//## begin LinkLayer%3AEF67BA0167.preface preserve=yes
//## end LinkLayer%3AEF67BA0167.preface

//## Class: LinkLayer%3AEF67BA0167
//	The link layer encapsulates the Link Protocol and the
//	Communications Port
//## Category: link_driver%3D7411EB00A8
//## Subsystem: link_driver%3D7412070347
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class LinkLayer : public NetworkLayer  //## Inherits: <unnamed>%4082F6FA02FD
{
  //## begin LinkLayer%3AEF67BA0167.initialDeclarations preserve=yes
  //## end LinkLayer%3AEF67BA0167.initialDeclarations

  public:
    //## Constructors (generated)
      LinkLayer();

    //## Constructors (specified)
      //## Operation: LinkLayer%988756716
      LinkLayer (const char* port_name, 	// the name of the port that is opened
      unsigned char* buf, 	// This is a pre-allocated buffer. If the parameter is
      	// provided, it must remain within scope for the duration
      	// of the class instance. If no buffer is provided, a
      	// Buffer of max_size is created and maintained by this
      	// class
      unsigned max_size	// this is the maximum size that can be transmitted though
      	// this layer
      );

    //## Destructor (generated)
      ~LinkLayer();


    //## Other Operations (specified)
      //## Operation: WriteBuffer%988756717; C++
      virtual bool WriteBuffer (const unsigned char* lpBuf, unsigned long dwToWrite);

      //## Operation: ReadBuffer%988756718; C++
      virtual unsigned long ReadBuffer (unsigned  char* lpBuf, unsigned long dwToRead);

      //## Operation: reset%988756720
      virtual void reset ();

      //## Operation: flush%1030333279
      virtual void flush ();

      //## Operation: WriteRaw%1044915129; C++
      virtual bool WriteRaw (const unsigned char* lpBuf, unsigned long dwToWrite);

      //## Operation: Open%1081798840; C++
      virtual bool Open (const char* port_name, const char* port_settings = NULL);

    // Additional Public Declarations
      //## begin LinkLayer%3AEF67BA0167.public preserve=yes
      //## end LinkLayer%3AEF67BA0167.public

  protected:
    // Additional Protected Declarations
      //## begin LinkLayer%3AEF67BA0167.protected preserve=yes
      //## end LinkLayer%3AEF67BA0167.protected

  private:

    //## Other Operations (specified)
      //## Operation: create%988756719
      static LinkLayer* create (const char* port_name, 	// the name of the port that is opened
      unsigned char* buf = NULL, 	// This is a pre-allocated buffer. If the parameter is
      	// provided, it must remain within scope for the duration
      	// of the class instance. If no buffer is provided, a
      	// Buffer of max_size is created and maintained by this
      	// class
      unsigned max_size = 1024	// this is the maximum size that can be transmitted though
      	// this layer
      );

    // Additional Private Declarations
      //## begin LinkLayer%3AEF67BA0167.private preserve=yes
      //## end LinkLayer%3AEF67BA0167.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _flush%3D6BFF470230
      //	Flag to indicate that a flush is taking place
      //## begin LinkLayer::_flush%3D6BFF470230.attr preserve=no  private: bool {UT} false
      volatile bool  _flush;
      //## end LinkLayer::_flush%3D6BFF470230.attr

      //## Attribute: _tx_buf%3D6BFF870304
      //## begin LinkLayer::_tx_buf%3D6BFF870304.attr preserve=no  private: char [8192] {U} 
      char  _tx_buf[8192];
      //## end LinkLayer::_tx_buf%3D6BFF870304.attr

    // Data Members for Associations

      //## Association: encodes and decodes%3AEF67DF0373
      //## Role: LinkLayer::_encoder%3AEF67E00285
      //## begin LinkLayer::_encoder%3AEF67E00285.role preserve=no  public: LinkProtocol { -> 1RFHN}
      LinkProtocol *_encoder;
      //## end LinkLayer::_encoder%3AEF67E00285.role

      //## Association: reads and writes data%3AEF67FA02DC
      //## Role: LinkLayer::_stream%3AEF67FB00F4
      //## begin LinkLayer::_stream%3AEF67FB00F4.role preserve=no  public: CommStream { -> 1RFHN}
      CommStream *_stream;
      //## end LinkLayer::_stream%3AEF67FB00F4.role

    // Additional Implementation Declarations
      //## begin LinkLayer%3AEF67BA0167.implementation preserve=yes
      //## end LinkLayer%3AEF67BA0167.implementation

};

//## begin LinkLayer%3AEF67BA0167.postscript preserve=yes
//## end LinkLayer%3AEF67BA0167.postscript

// Class LinkLayer 

inline LinkLayer::LinkLayer()
  //## begin LinkLayer::LinkLayer%.hasinit preserve=no
      : _flush(false), _encoder(NULL), _stream(NULL)
  //## end LinkLayer::LinkLayer%.hasinit
  //## begin LinkLayer::LinkLayer%.initialization preserve=yes
  //## end LinkLayer::LinkLayer%.initialization
{
  //## begin LinkLayer::LinkLayer%.body preserve=yes
  //## end LinkLayer::LinkLayer%.body
}


//## begin module%3AEF67BA0167.epilog preserve=yes
//## end module%3AEF67BA0167.epilog


#endif
