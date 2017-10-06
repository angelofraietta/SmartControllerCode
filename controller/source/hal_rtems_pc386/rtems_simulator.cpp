//## begin module%3ACB9FA701C8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ACB9FA701C8.cm

//## begin module%3ACB9FA701C8.cp preserve=no
//	Angelo Fraietta
//## end module%3ACB9FA701C8.cp

//## Module: rtems_simulator%3ACB9FA701C8; Package body
//	Connection to simulator library for RTEMS
//## Subsystem: hal_rtems%3A80A5EB020D
//	This includes modules that are specific to RTEMS for the
//	SmartController.   These modules are linked with the
//	engine package..
//## Source file: c:\develop\SmartController\controller\source\hal_rtems_pc386\rtems_simulator.cpp

//## begin module%3ACB9FA701C8.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3ACB9FA701C8.additionalIncludes

//## begin module%3ACB9FA701C8.includes preserve=yes
//## end module%3ACB9FA701C8.includes

// SimulatorInterface
#include "simulatorinterface.h"
// SessionInterface
#include "sessioninterface.h"
//## begin module%3ACB9FA701C8.declarations preserve=no
//## end module%3ACB9FA701C8.declarations

//## begin module%3ACB9FA701C8.additionalDeclarations preserve=yes
extern "C" bool SimulatorGetAnswer (const BYTE* question, BYTE* ret_answer)
{
	return SimulatorAnswer::GetAnswer (question, ret_answer);
}

//## end module%3ACB9FA701C8.additionalDeclarations


//## begin module%3ACB9FA701C8.epilog preserve=yes
//## end module%3ACB9FA701C8.epilog
