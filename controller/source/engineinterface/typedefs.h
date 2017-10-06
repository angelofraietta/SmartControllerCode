//## begin module%3A9DA7B60388.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A9DA7B60388.cm

//## begin module%3A9DA7B60388.cp preserve=no
//	Angelo Fraietta
//## end module%3A9DA7B60388.cp

//## Module: typedefs%3A9DA7B60388; Package specification
//	Contains the common typedefs used by the engine and the
//	Patch Interface
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\typedefs.h

#ifndef typedefs_h
#define typedefs_h 1

//## begin module%3A9DA7B60388.additionalIncludes preserve=no
//## end module%3A9DA7B60388.additionalIncludes

//## begin module%3A9DA7B60388.includes preserve=yes
//## end module%3A9DA7B60388.includes

//## begin module%3A9DA7B60388.declarations preserve=no
//## end module%3A9DA7B60388.declarations

//## begin module%3A9DA7B60388.additionalDeclarations preserve=yes

//define the maximum LPSTR lengths add 1 for null char
#define MAX_NAME_LEN 32
#define MAX_COMMENT_LEN 63
#define MAX_MESSAGE_LEN 31
#define MAX_ERROR_LEN           

/* define limits */
#define MAX_INT8      ((signed char)0x7F)
#define MIN_INT8      ((signed char)0x80)
#define MAX_UINT8     ((unsigned char)0xFF)
#define MAX_INT16     ((short)0x7FFF)
#define MIN_INT16     ((short)0x8000)
#define MAX_UINT16    ((unsigned short)0xFFFFU
#define MAX_INT32     0x7FFFFFFFL
#define MIN_INT32     0x80000000L
#define MAX_UINT32    0xFFFFFFFFUL

/* define the message Set and Get Types */
#define MESSAGE_TYPE_NONE       ((UINT8) 0)
#define MESSAGE_TYPE_INT        ((UINT8) 1)
#define MESSAGE_TYPE_FLOAT      ((UINT8) 2)
#define MESSAGE_TYPE_STRING     ((UINT8) 3)
#define MESSAGE_TYPE_UNSIGNED   ((UINT8) 4)

#define DELIM '\0'

#ifndef NO_TYPEDEFS

#ifndef UNREFERENCED_PARAMETER
  #define UNREFERENCED_PARAMETER(P) (P)=(P);
#endif

typedef unsigned long DWORD;
typedef char* LPSTR;
typedef unsigned long UINT32;
typedef unsigned short UINT16;
typedef short INT16;
typedef long  INT32;
typedef signed char INT8;
typedef unsigned char UINT8;
typedef unsigned char UCHAR;
typedef unsigned char BYTE;

#ifdef _NO_BOOL
/* The Rose analyzer still cannot handle bool */
typedef unsigned char bool;
#define true  ((bool) 1)
#define false ((bool) 0)
#endif
#endif

//## end module%3A9DA7B60388.additionalDeclarations


//## begin module%3A9DA7B60388.epilog preserve=yes
//## end module%3A9DA7B60388.epilog


#endif
