//## begin module%3B45242B03A3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B45242B03A3.cm

//## begin module%3B45242B03A3.cp preserve=no
//	Angelo Fraietta
//## end module%3B45242B03A3.cp

//## Module: RtemsCommStream%3B45242B03A3; Package body
//	Implementation of CommStream for Rtems
//## Subsystem: link_driver::hal_rtems%3AEF6A0103BE
//	The pc386 implementation of the CommStream
//## Source file: c:\develop\Winsmartcontroller\controller\source\link_driver\hal_rtems\rtemscommstream.cpp

//## begin module%3B45242B03A3.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3B45242B03A3.additionalIncludes

//## begin module%3B45242B03A3.includes preserve=yes
#include "rtemscommport.h"
//## end module%3B45242B03A3.includes

// CommStream
#include "commstream.h"
//## begin module%3B45242B03A3.declarations preserve=no
//## end module%3B45242B03A3.declarations

//## begin module%3B45242B03A3.additionalDeclarations preserve=yes
//## end module%3B45242B03A3.additionalDeclarations


// Class CommStream 





//## Other Operations (implementation)
//## Operation: create%988756712
//	Method used to create the comm port. Implementation will
//	be OS dependant.
CommStream* CommStream::create (const char* name)
{
  //## begin CommStream::create%988756712.body preserve=yes
	CommStream* ret = NULL;

	return ret;

  //## end CommStream::create%988756712.body
}

// Additional Declarations
  //## begin CommStream%3AE79D6F0223.declarations preserve=yes
  //## end CommStream%3AE79D6F0223.declarations

//## begin module%3B45242B03A3.epilog preserve=yes
//## end module%3B45242B03A3.epilog
