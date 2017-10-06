//## begin module%4082F624037A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4082F624037A.cm

//## begin module%4082F624037A.cp preserve=no
//	Angelo Fraietta
//## end module%4082F624037A.cp

//## Module: NetworkLayer%4082F624037A; Pseudo Package body
//## Subsystem: link_driver%3D7412070347
//## Source file: D:\develop\Smartcontroller\controller\source\link_driver\networklayer.cpp

//## begin module%4082F624037A.additionalIncludes preserve=no
//## end module%4082F624037A.additionalIncludes

//## begin module%4082F624037A.includes preserve=yes
#include <stddef.h>
#include "linklayer.h"

//## end module%4082F624037A.includes

// NetworkLayer
#include "networklayer.h"
// UDPPort
#include "udpport.h"
//## begin module%4082F624037A.additionalDeclarations preserve=yes
//## end module%4082F624037A.additionalDeclarations


// Class NetworkLayer 

//## begin NetworkLayer::UDP_PORT_NAME%407AF25700AB.attr preserve=no  public: static const char* {V} "UDP"
const char* NetworkLayer::UDP_PORT_NAME = "UDP";
//## end NetworkLayer::UDP_PORT_NAME%407AF25700AB.attr


//## Other Operations (implementation)
//## Operation: create%1082317736
//	Interface for creating a link layer
NetworkLayer* NetworkLayer::create (const char* port_name, unsigned long port_param, unsigned char* buf, unsigned max_size)
{
  //## begin NetworkLayer::create%1082317736.body preserve=yes
  NetworkLayer* ret = NULL;

  //strip first part of name off

  if (strcmp(port_name, UDP_PORT_NAME))
  {
	  ret = new LinkLayer (port_name, buf, max_size);
  }
  else
  {
    UDPPort* port = new UDPPort();
    if (port)
    {
      if (port->OpenPort(port_param))
      {
        ret = port;
      }
    }



  }

  return ret;
  //## end NetworkLayer::create%1082317736.body
}

// Additional Declarations
  //## begin NetworkLayer%4082F624037A.declarations preserve=yes
  //## end NetworkLayer%4082F624037A.declarations

//## begin module%4082F624037A.epilog preserve=yes
//## end module%4082F624037A.epilog
