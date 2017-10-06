//## begin module%3AAD7D850277.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AAD7D850277.cm

//## begin module%3AAD7D850277.cp preserve=no
//	Angelo Fraietta
//## end module%3AAD7D850277.cp

//## Module: SMUtility%3AAD7D850277; Pseudo Package body
//## Subsystem: engineinterface%3A9C858C00CB
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\smutility.cpp

//## begin module%3AAD7D850277.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3AAD7D850277.additionalIncludes

//## begin module%3AAD7D850277.includes preserve=yes
#include "typedefs.h"
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <stdio.h>
//## end module%3AAD7D850277.includes

// SMUtility
#include "smutility.h"
//## begin module%3AAD7D850277.additionalDeclarations preserve=yes
//## end module%3AAD7D850277.additionalDeclarations


// Class Utility SMUtility 


//## Other Operations (implementation)
//## Operation: IsInt%984448565
//	Returns true if the input buffer is an integer type
bool SMUtility::IsInt (const char* buf)
{
  //## begin SMUtility::IsInt%984448565.body preserve=yes
  const INT8 len = (INT8)strlen (buf);
  bool valid_int = false;
  
  INT8 i = 0;
  
  // eat whitespace
  while (buf [i] == ' ' && i < len)
    {
      i++;
    }
  
  // test for sign
  if ((buf [i] == '-') || (buf [i] == '+'))
    {
      i++;
    }
  
  while (i < len)
    {
      if ((buf [i] >= '0') && (buf [i] <= '9'))
				{
					valid_int = true;
					i++;
				}
      
      else
				{
					valid_int = false;
					break;
				}
      
    } // end while
  
  // test for over range
  
  if (valid_int)
    {
      double float_val = atof (buf);
      static const int max_int = MAX_INT32;
      static const int min_int = MIN_INT32;
      
      valid_int = ((float_val <= max_int) && (float_val >= min_int));
    }
  
  return valid_int; 
	
  //## end SMUtility::IsInt%984448565.body
}

//## Operation: IsUint%984448566
//	Returns true if the input buffer is anunsigned  integer
//	type
bool SMUtility::IsUint (const char* buf)
{
  //## begin SMUtility::IsUint%984448566.body preserve=yes
  const INT8 len = (INT8)strlen (buf);
  bool valid_int = false;
  
  INT8 i = 0;
  
  // eat whitespace
  while (buf [i] == ' ' && i < len)
    {
      i++;
    }
  
  // test for sign
  if (buf [i] == '-')  // this is not a uint
    {
      return false;
    }
  
  if(buf [i] == '+')
    {
      i++;
    }
  
  while (i < len)
    {
      if ((buf [i] >= '0') && (buf [i] <= '9'))
				{
					valid_int = true;
					i++;
				}
      
      else
				{
					valid_int = false;
					break;
				}
      
    } // end while
  
  // test for over range
  
  if (valid_int)
    {
      double float_val = atof (buf);

      valid_int = (float_val <= MAX_UINT32);
    }

  return valid_int;

  //## end SMUtility::IsUint%984448566.body
}

//## Operation: IsFloat%984448567
//	Returns true if the input buffer is a floatr type
bool SMUtility::IsFloat (const char* buf)
{
  //## begin SMUtility::IsFloat%984448567.body preserve=yes
  bool valid_float = false;

  const INT8 len = (INT8)strlen (buf);
  INT8 i = 0;
  bool found_point = false;

  // eat whitespace
  while (buf [i] == ' ' && i < len)
    {
      i++;
    }

  // test for sign
  if ((buf [i] == '-') || (buf [i] == '+'))
    {
      i++;
    }

  while (i < len)
    {
      if ((buf [i] >= '0') && (buf [i] <= '9'))
        {
          valid_float = true;
          i++;
        }

      else
        {
          switch (buf [i])
            {
            case '.': // is the decimal point
              if (found_point)
                {
                  return false; // we already have a decimal point
                }

              else
                {
                  found_point = true;
                  i++;
                }

              break;

            case 'e':
            case 'E':
              return IsInt (buf + i + 1); // test the exponent

            default:
              return false;

            } // end switch

        }

    } // end while

  return valid_float;

  //## end SMUtility::IsFloat%984448567.body
}

//## Operation: StrToFlt%984519165
//	Converts a char* buffer to a float.
double SMUtility::StrToFlt (const char* buf)
{
  return atof(buf);

  //## begin SMUtility::StrToFlt%984519165.body preserve=yes
  //## end SMUtility::StrToFlt%984519165.body
}

//## Operation: StrToInt%984519166
//	Converts a char* buffer to an integer
int SMUtility::StrToInt (const char* buf)
{
  return atoi(buf);

  //## begin SMUtility::StrToInt%984519166.body preserve=yes
  //## end SMUtility::StrToInt%984519166.body
}

//## Operation: FltToStr%984519167
//	converts a float to a string, placing the string value
//	into buf. Returns true if there is enough space in buf
bool SMUtility::FltToStr (double val, char* buf, unsigned buf_len)
{
  //## begin SMUtility::FltToStr%984519167.body preserve=yes
  bool ret = false;

  char stat_buf [128]; // this is the largest
  sprintf (stat_buf, "%f", val);

  if (strlen (stat_buf) < buf_len)
  {
    strcpy (buf, (const char*)stat_buf);
    ret = true;
  }

  return ret;
  //## end SMUtility::FltToStr%984519167.body
}

//## Operation: IntToStr%984519168
//	converts an integer to a string, placing the string
//	value into buf. Returns true if there is enough space in
//	buf
bool SMUtility::IntToStr (int val, char* buf, unsigned buf_len)
{
  //## begin SMUtility::IntToStr%984519168.body preserve=yes
  bool ret = false;

  char stat_buf [128]; // this is the largest
  sprintf (stat_buf, "%d", val);

  if (strlen (stat_buf) < buf_len)
  {
    strcpy (buf, (const char*)stat_buf);
    ret = true;
  }

  return ret;
  //## end SMUtility::IntToStr%984519168.body
}

//## Operation: StrToStr%985649597
//	copies a string into a char buffer, placing the string
//	value into buf. Returns true if there is enough space in
//	buf
bool SMUtility::StrToStr (const char* val, char* buf, unsigned buf_len)
{
  //## begin SMUtility::StrToStr%985649597.body preserve=yes
{
	bool ret = false;
	if (strlen (val) < buf_len)
		{
			strcpy (buf, val);
			ret = true;
		}
	return ret;
}

  //## end SMUtility::StrToStr%985649597.body
}

//## Operation: IntToBuf%985746357
//	Converts an integer to a Big endian  2 character buf. If
//	the value of the integer is greater than 16 bits, a
//	rounding error will occur. Returns pointer to one after
//	bytes written
BYTE* SMUtility::IntToBuf (short val, BYTE* buf)
{
  //## begin SMUtility::IntToBuf%985746357.body preserve=yes
	for (unsigned i = 0; i < sizeof (val); i++)
		{
			buf [i] = (BYTE) (val & 0x0FF);
			val >>= 8;
		}
	return buf + sizeof (val);
  //## end SMUtility::IntToBuf%985746357.body
}

//## Operation: BufToInt%985746358
//	Converts two bytes in Big endian to a 16 bit integer.
//## Postconditions:
//	in_val points to next parameter. i.e. is incremented by
//	two.
short SMUtility::BufToInt (const BYTE** in_val)
{
  //## begin SMUtility::BufToInt%985746358.body preserve=yes
	short ret = 0;
  const BYTE* cursor = *in_val;
	for (unsigned i = 0; i < sizeof(short); i++)
		{
      short byte_val = *cursor;
      for (unsigned weight = 0; weight < i; weight ++)
        {
          byte_val = (short) (byte_val * 0x100);
        }
        
			ret += byte_val;
			cursor++;
		}
  *in_val = cursor;
	return ret;
  //## end SMUtility::BufToInt%985746358.body
}

//## Operation: BufToStr%985746361
//	returns null terminated const char* and increments cursor
//## Preconditions:
//	in_val must point to a Null terminated string
//## Postconditions:
//	in_val points to next parameter. i.e. is incremented by
//	strlen + 1
const char* SMUtility::BufToStr (const BYTE** in_val)
{
  //## begin SMUtility::BufToStr%985746361.body preserve=yes
	const char* ret = (const char*)in_val;

	*in_val += strlen (ret) + 1;

	return ret;

  //## end SMUtility::BufToStr%985746361.body
}

//## Operation: StrToBuf%985819704
//	Copies a string + null terminatorr into a Byte buffer.
//	Returns pointer to one after bytes written
BYTE* SMUtility::StrToBuf (const char* val, BYTE* buf)
{
  //## begin SMUtility::StrToBuf%985819704.body preserve=yes
	const unsigned bytes_to_copy = strlen (val) +1;
  memcpy (buf, val, bytes_to_copy);

	return buf + bytes_to_copy;
  //## end SMUtility::StrToBuf%985819704.body
}

//## Operation: TargetFuncToBuf%986415468
//	Fills input BYTE* cursor with Big Endian BYTE. Returns
//	pointer to one after last BYTE.
BYTE* SMUtility::TargetFuncToBuf (unsigned target_func, BYTE* buf)
{
  //## begin SMUtility::TargetFuncToBuf%986415468.body preserve=yes
  //## end SMUtility::TargetFuncToBuf%986415468.body

    *buf = (BYTE)target_func;
    buf++;
    return buf;

}

//## Operation: BufToTargetFunc%986415469
//	Converts buffer to IdentityInterface target function
//	index
//## Postconditions:
//	buf points to one after last BYTE value
unsigned SMUtility::BufToTargetFunc (const BYTE** buf)
{
    const BYTE* b_val = *buf; 
    BYTE val = *b_val;
    b_val++;
    *buf = b_val;
    return val;


  //## begin SMUtility::BufToTargetFunc%986415469.body preserve=yes
  //## end SMUtility::BufToTargetFunc%986415469.body
}

//## Operation: TargetClassToBuf%986415471
//	Fills input BYTE* cursor with Big Endian BYTE. Returns
//	pointer to one after last BYTE.
BYTE* SMUtility::TargetClassToBuf (unsigned target_class, BYTE* buf)
{
    *buf = (BYTE)target_class;
    buf++;
    return buf;


  //## begin SMUtility::TargetClassToBuf%986415471.body preserve=yes
  //## end SMUtility::TargetClassToBuf%986415471.body
}

//## Operation: BufToTargetClass%986415472
//	Converts buffer to TargetClassIndex
//## Postconditions:
//	buf points to one after last BYTE value
unsigned SMUtility::BufToTargetClass (const BYTE** buf)
{
    const BYTE* b_val = *buf; 
    BYTE val = *b_val;
    b_val++;
    *buf = b_val;
    return val;


  //## begin SMUtility::BufToTargetClass%986415472.body preserve=yes
  //## end SMUtility::BufToTargetClass%986415472.body
}

//## Operation: DwordToBuf%1020130706
//	Stores 4 Byte DWORD into a buf
BYTE* SMUtility::DwordToBuf (DWORD val, BYTE* buf)
{
  //## begin SMUtility::DwordToBuf%1020130706.body preserve=yes
  BYTE* cursor = buf;
  // store lowest byte and shift right
  for (unsigned i = 0; i < sizeof (val); i++)
  {
    *cursor = (char)val;
    val /= 256;
    cursor++;
  }

  return cursor;
  //## end SMUtility::DwordToBuf%1020130706.body
}

//## Operation: BufToDword%1020130707
//	Converts 4 bytes into a DWORD without swapping endian
//## Postconditions:
//	in_val points to next parameter. i.e. is incremented by
//	4.
DWORD SMUtility::BufToDword (const BYTE** in_val)
{
  //## begin SMUtility::BufToDword%1020130707.body preserve=yes
  DWORD ret = 0;

  const BYTE* cursor = *in_val;

  for (unsigned i = sizeof (ret) - 1;  i > 0; i--)
  {
    ret += cursor [i];
    ret *= 256;
    (*in_val)++;       // move the buffer along
  }

  ret += cursor [0];
		(*in_val)++;

  return ret;

  //## end SMUtility::BufToDword%1020130707.body
}

// Additional Declarations
  //## begin SMUtility%3AAD7D850277.declarations preserve=yes
  //## end SMUtility%3AAD7D850277.declarations

//## begin module%3AAD7D850277.epilog preserve=yes
//## end module%3AAD7D850277.epilog
