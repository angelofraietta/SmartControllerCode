#ifndef _SMC_STDAFX_H
#define _SMC_STDAFX_H
/****************************************************************
These are the standard include files dependant upon each system
****************************************************************/
#ifdef _HAL_WINDOWS
#include <windows.h>
#endif

#include <stdlib.h>


#ifndef _E_STL
//#include <vector>
//#include <string>
//using std::vector;  //re-define the namespaces
#define sm_ptr std
#define sm_str std

#else
#include "evector.h"
#include "estring.h"

#define sm_ptr sm_str
using sm_str::string;

#endif
#include <stdio.h>
#include "typedefs.h"
#include "error_messages.h"


#endif
