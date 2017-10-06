//## begin module%4082F624037A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4082F624037A.cm

//## begin module%4082F624037A.cp preserve=no
//	Angelo Fraietta
//## end module%4082F624037A.cp

//## Module: NetworkLayer%4082F624037A; Pseudo Package specification
//## Subsystem: link_driver%3D7412070347
//## Source file: D:\develop\Smartcontroller\controller\source\link_driver\networklayer.h

#ifndef networklayer_h
#define networklayer_h 1

//## begin module%4082F624037A.additionalIncludes preserve=no
//## end module%4082F624037A.additionalIncludes

//## begin module%4082F624037A.includes preserve=yes
//## end module%4082F624037A.includes


class LinkLayer;
class UDPPort;

//## begin module%4082F624037A.additionalDeclarations preserve=yes
//## end module%4082F624037A.additionalDeclarations


//## begin NetworkLayer%4082F624037A.preface preserve=yes
//## end NetworkLayer%4082F624037A.preface

//## Class: NetworkLayer%4082F624037A
//## Category: link_driver%3D7411EB00A8
//## Subsystem: link_driver%3D7412070347
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4082FB9E0196;LinkLayer { -> F}
//## Uses: <unnamed>%4082FBA00222;UDPPort { -> F}

class NetworkLayer 
{
  //## begin NetworkLayer%4082F624037A.initialDeclarations preserve=yes
  //## end NetworkLayer%4082F624037A.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: WriteBuffer%1082317734; C++
      virtual bool WriteBuffer (const unsigned char* lpBuf, unsigned long dwToWrite) = 0;

      //## Operation: ReadBuffer%1082317735; C++
      virtual unsigned long ReadBuffer (unsigned  char* lpBuf, unsigned long dwToRead) = 0;

      //## Operation: create%1082317736
      static NetworkLayer* create (const char* port_name, 	// the name of the port that is opened
      unsigned long port_param, unsigned char* buf = NULL, 	// This is a pre-allocated buffer. If the parameter is
      	// provided, it must remain within scope for the duration
      	// of the class instance. If no buffer is provided, a
      	// Buffer of max_size is created and maintained by this
      	// class
      unsigned max_size = 1024	// this is the maximum size that can be transmitted though
      	// this layer
      );

      //## Operation: reset%1082317737
      virtual void reset ();

      //## Operation: flush%1082317738
      virtual void flush ();

      //## Operation: WriteRaw%1082317739; C++
      virtual bool WriteRaw (const unsigned char* lpBuf, unsigned long dwToWrite);

      //## Operation: Open%1082317740; C++
      virtual bool Open (const char* port_name, const char* port_settings = NULL) = 0;

      //## Operation: SetTo%1082317741
      virtual bool SetTo (const char* to_address);

      //## Operation: GetFrom%1082317742
      virtual bool GetFrom (char* ret_buf, unsigned buf_size);

    // Data Members for Class Attributes

      //## Attribute: UDP_PORT_NAME%407AF25700AB
      //## begin NetworkLayer::UDP_PORT_NAME%407AF25700AB.attr preserve=no  public: static const char* {V} "UDP"
      static const char* UDP_PORT_NAME;
      //## end NetworkLayer::UDP_PORT_NAME%407AF25700AB.attr

    // Additional Public Declarations
      //## begin NetworkLayer%4082F624037A.public preserve=yes
      //## end NetworkLayer%4082F624037A.public

  protected:
    // Additional Protected Declarations
      //## begin NetworkLayer%4082F624037A.protected preserve=yes
      //## end NetworkLayer%4082F624037A.protected

  private:
    // Additional Private Declarations
      //## begin NetworkLayer%4082F624037A.private preserve=yes
      //## end NetworkLayer%4082F624037A.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin NetworkLayer%4082F624037A.implementation preserve=yes
      //## end NetworkLayer%4082F624037A.implementation

};

//## begin NetworkLayer%4082F624037A.postscript preserve=yes
//## end NetworkLayer%4082F624037A.postscript

// Class NetworkLayer 


//## Other Operations (inline)
//## Operation: reset%1082317737
inline void NetworkLayer::reset ()
{
  //## begin NetworkLayer::reset%1082317737.body preserve=yes
  //## end NetworkLayer::reset%1082317737.body
}

//## Operation: flush%1082317738
//	Flushes the input buffer
inline void NetworkLayer::flush ()
{
  //## begin NetworkLayer::flush%1082317738.body preserve=yes
  //## end NetworkLayer::flush%1082317738.body
}

//## Operation: WriteRaw%1082317739; C++
//	Writes a Raw buffer of Bytes to an open Port
inline bool NetworkLayer::WriteRaw (const unsigned char* lpBuf, unsigned long dwToWrite)
{
  return false;

  //## begin NetworkLayer::WriteRaw%1082317739.body preserve=yes
  //## end NetworkLayer::WriteRaw%1082317739.body
}

//## Operation: SetTo%1082317741
//	Sets the To address
inline bool NetworkLayer::SetTo (const char* to_address)
{
  return false;

  //## begin NetworkLayer::SetTo%1082317741.body preserve=yes
  //## end NetworkLayer::SetTo%1082317741.body
}

//## Operation: GetFrom%1082317742
//	Returns the From Address
inline bool NetworkLayer::GetFrom (char* ret_buf, unsigned buf_size)
{
  return false;

  //## begin NetworkLayer::GetFrom%1082317742.body preserve=yes
  //## end NetworkLayer::GetFrom%1082317742.body
}

//## begin module%4082F624037A.epilog preserve=yes
//## end module%4082F624037A.epilog


#endif
