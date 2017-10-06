//## begin module%3AAD7D850277.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AAD7D850277.cm

//## begin module%3AAD7D850277.cp preserve=no
//	Angelo Fraietta
//## end module%3AAD7D850277.cp

//## Module: SMUtility%3AAD7D850277; Pseudo Package specification
//## Subsystem: engineinterface%3A9C858C00CB
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\smutility.h

#ifndef smutility_h
#define smutility_h 1

//## begin module%3AAD7D850277.additionalIncludes preserve=no
//## end module%3AAD7D850277.additionalIncludes

//## begin module%3AAD7D850277.includes preserve=yes
//## end module%3AAD7D850277.includes

//## begin module%3AAD7D850277.additionalDeclarations preserve=yes
//## end module%3AAD7D850277.additionalDeclarations


//## begin SMUtility%3AAD7D850277.preface preserve=yes
//## end SMUtility%3AAD7D850277.preface

//## Class: SMUtility%3AAD7D850277; Class Utility
//	Simple Utiilities for use within engine
//## Category: EngineInterface%3A998EE60122
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class SMUtility 
{
  //## begin SMUtility%3AAD7D850277.initialDeclarations preserve=yes
  //## end SMUtility%3AAD7D850277.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: IsInt%984448565
      static bool IsInt (const char* buf	// The buffer that contains the string to be tested
      );

      //## Operation: IsUint%984448566
      static bool IsUint (const char* buf	// The buffer that contains the string to be tested
      );

      //## Operation: IsFloat%984448567
      static bool IsFloat (const char* buf	// The buffer that contains the string to be tested
      );

      //## Operation: StrToFlt%984519165
      static double StrToFlt (const char* buf	// the buffer with the float number
      );

      //## Operation: StrToInt%984519166
      static int StrToInt (const char* buf	// the buffer with the float number
      );

      //## Operation: FltToStr%984519167
      static bool FltToStr (double val, 	// The value to convert
      char* buf, 	// The return buffer
      unsigned buf_len	// The size of buf
      );

      //## Operation: IntToStr%984519168
      static bool IntToStr (int val, 	// The value to convert
      char* buf, 	// The return buffer
      unsigned buf_len	// The size of buf
      );

      //## Operation: StrToStr%985649597
      static bool StrToStr (const char* val, 	// The value to convert
      char* buf, 	// The return buffer
      unsigned buf_len	// The size of buf
      );

      //## Operation: IntToBuf%985746357
      static BYTE* IntToBuf (short val, 	// The 16 bit integer
      BYTE* buf	// two bytes where value will be written
      );

      //## Operation: BufToInt%985746358
      static short BufToInt (const BYTE** in_val	// address of two bytes of big endian data
      );

      //## Operation: BufToStr%985746361
      static const char* BufToStr (const BYTE** in_val	// address of null terminated string
      );

      //## Operation: StrToBuf%985819704
      static BYTE* StrToBuf (const char* val, 	// The 16 bit integer
      BYTE* buf	// two bytes where value will be written
      );

      //## Operation: TargetFuncToBuf%986415468
      static BYTE* TargetFuncToBuf (unsigned target_func, 	// The target function index
      BYTE* buf	// Where the value will be written
      );

      //## Operation: BufToTargetFunc%986415469
      static unsigned BufToTargetFunc (const BYTE** buf	// Pointer to buffer containing value
      );

      //## Operation: TargetFuncBufSize%986415470
      static unsigned TargetFuncBufSize ();

      //## Operation: TargetClassToBuf%986415471
      static BYTE* TargetClassToBuf (unsigned target_class, 	// The target function index
      BYTE* buf	// Where the value will be written
      );

      //## Operation: BufToTargetClass%986415472
      static unsigned BufToTargetClass (const BYTE** buf	// Pointer to buffer containing value
      );

      //## Operation: TargetClassBufSize%986415473
      static unsigned TargetClassBufSize ();

      //## Operation: DwordToBuf%1020130706
      static BYTE* DwordToBuf (DWORD val, 	// The 16 bit integer
      BYTE* buf	// two bytes where value will be written
      );

      //## Operation: BufToDword%1020130707
      static DWORD BufToDword (const BYTE** in_val	// address of two bytes of big endian data
      );

    // Additional Public Declarations
      //## begin SMUtility%3AAD7D850277.public preserve=yes
      //## end SMUtility%3AAD7D850277.public

  protected:
    // Additional Protected Declarations
      //## begin SMUtility%3AAD7D850277.protected preserve=yes
      //## end SMUtility%3AAD7D850277.protected

  private:
    // Additional Private Declarations
      //## begin SMUtility%3AAD7D850277.private preserve=yes
      //## end SMUtility%3AAD7D850277.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin SMUtility%3AAD7D850277.implementation preserve=yes
      //## end SMUtility%3AAD7D850277.implementation

};

//## begin SMUtility%3AAD7D850277.postscript preserve=yes
//## end SMUtility%3AAD7D850277.postscript

// Class Utility SMUtility 


//## Other Operations (inline)
//## Operation: TargetFuncBufSize%986415470
//	returns the size of a required buffer for a target
//	function index
inline unsigned SMUtility::TargetFuncBufSize ()
{
  return (sizeof (BYTE));

  //## begin SMUtility::TargetFuncBufSize%986415470.body preserve=yes
  //## end SMUtility::TargetFuncBufSize%986415470.body
}

//## Operation: TargetClassBufSize%986415473
//	returns the size of a required buffer for a TargetClass
//	index
inline unsigned SMUtility::TargetClassBufSize ()
{
  return (sizeof (BYTE));

  //## begin SMUtility::TargetClassBufSize%986415473.body preserve=yes
  //## end SMUtility::TargetClassBufSize%986415473.body
}

//## begin module%3AAD7D850277.epilog preserve=yes
//## end module%3AAD7D850277.epilog


#endif
