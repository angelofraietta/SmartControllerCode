//## begin module%3AEF6E8C0104.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AEF6E8C0104.cm

//## begin module%3AEF6E8C0104.cp preserve=no
//	Angelo Fraietta
//## end module%3AEF6E8C0104.cp

//## Module: WindowsCommStream%3AEF6E8C0104; Package body
//	Windows implementation of CommStream.  Platform
//	dependant component is made so the appropriate subclass
//	can be created, depending upon platform
//## Subsystem: link_driver::hal_windows%3AEF69F502F9
//	The windows implementation of the CommStream
//## Source file: c:\develop\Winsmartcontroller\controller\source\link_driver\hal_windows\windowscommstream.cpp

//## begin module%3AEF6E8C0104.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3AEF6E8C0104.additionalIncludes

//## begin module%3AEF6E8C0104.includes preserve=yes
//## end module%3AEF6E8C0104.includes

// WindowsMidiPort
#include "windowsmidiport.h"
// WindowsCommPort
#include "windowscommport.h"
// CommStream
#include "commstream.h"
//## begin module%3AEF6E8C0104.declarations preserve=no
//## end module%3AEF6E8C0104.declarations

//## begin module%3AEF6E8C0104.additionalDeclarations preserve=yes
//## end module%3AEF6E8C0104.additionalDeclarations


// Class CommStream 





//## Other Operations (implementation)
//## Operation: create%988756712
//	Method used to create the comm port. Implementation will
//	be OS dependant.
CommStream* CommStream::create (const char* name)
{
  //## begin CommStream::create%988756712.body preserve=yes
	// we will just make a comm port for now
	return new WindowsCommPort (name);
  //## end CommStream::create%988756712.body
}

// Additional Declarations
  //## begin CommStream%3AE79D6F0223.declarations preserve=yes
  //## end CommStream%3AE79D6F0223.declarations

//## begin module%3AEF6E8C0104.epilog preserve=yes
//## end module%3AEF6E8C0104.epilog
