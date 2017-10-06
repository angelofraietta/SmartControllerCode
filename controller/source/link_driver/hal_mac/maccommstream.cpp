//## begin module%3D6C59C40334.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D6C59C40334.cm

//## begin module%3D6C59C40334.cp preserve=no
//	Angelo Fraietta
//## end module%3D6C59C40334.cp

//## Module: MacCommStream%3D6C59C40334; Package body
//## Subsystem: link_driver::hal_mac%3AEF6A5C035B
//	The Mac implementation of the CommStream
//## Source file: c:\develop\Winsmartcontroller\controller\source\link_driver\hal_mac\maccommstream.cpp

//## begin module%3D6C59C40334.additionalIncludes preserve=no
//## end module%3D6C59C40334.additionalIncludes

//## begin module%3D6C59C40334.includes preserve=yes
#include "stdafx.h"
#include "commstream.h"
//## end module%3D6C59C40334.includes

// MacCommPort
//#include "maccommport.h"
//## begin module%3D6C59C40334.declarations preserve=no
//## end module%3D6C59C40334.declarations

//## begin module%3D6C59C40334.additionalDeclarations preserve=yes
//## end module%3D6C59C40334.additionalDeclarations


// Class CommStream 





//## Other Operations (implementation)
//## Operation: create%988756712
//	Method used to create the comm port. Implementation will
//	be OS dependant.
CommStream* CommStream::create (const char* name)
{
  //## begin CommStream::create%988756712.body preserve=yes
	return NULL;
  //## end CommStream::create%988756712.body
}

// Additional Declarations
  //## begin CommStream%3AE79D6F0223.declarations preserve=yes
  //## end CommStream%3AE79D6F0223.declarations

//## begin module%3D6C59C40334.epilog preserve=yes
//## end module%3D6C59C40334.epilog
