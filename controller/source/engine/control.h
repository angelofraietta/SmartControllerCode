// this header includes all the headers in the appropriate order
//to create Action Classes

// the following file contains definitions for ConnectorAddress, BaseShell
//InletAddress and OutletAddress classes

// we will define _E_STL here as we cannot do it in Code Warrior 
#ifndef _E_STL
#define _E_STL
#endif

#ifndef _ROSE_ANALYSE

#ifndef _E_STL
//#include <vector>
//#include <string>
//using std::vector;  //re-define the namespaces
#define sm_ptr std
#define sm_str std

#else
#include <stddef.h>
#include "evector.h"
#include "estring.h"

#define sm_ptr sm_str
using sm_str::string;

#endif

#ifdef HAL_MAC
#pragma supress_warnings on
#endif

#endif //#ifndef _ROSE_ANALYSE
#include "typedefs.h"

#include "error_messages.h"
#include "identity.h"
#include "connectormessage.h" // ConnectorAddress class dfn
#include "socket.h"// Socket class dfn
#include "outlet.h" // Outlet class dfn
#include "baseshel.h" // BaseShell class dfn
#include "connect.h" // Connector class dfn
#include "funcdec.h" // global function declarations
#include "smutility.h" // utility functions
//#include "Patch.h"

#ifdef HAL_MAC
#pragma supress_warnings off
#endif

