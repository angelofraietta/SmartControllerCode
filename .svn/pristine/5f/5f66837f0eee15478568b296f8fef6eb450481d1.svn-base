#include "stdafx.h"

#include "deltatime.h"

unsigned WriteVarLen(register unsigned long value, BYTE* Buff)
{
  //returns the number of bytes written
  DWORD* dwBuff = (DWORD*)Buff;
  unsigned wCursor = 0;
  
  register unsigned long buffer;
  buffer = value & 0x7F;
  while ( (value >>= 7) )
    {
      buffer <<= 8;
      buffer |= ((value & 0x7F) | 0x80);
    }
  
  while (1)
    {
      dwBuff[wCursor++] = buffer;
      if (buffer & 0x80)
	buffer >>= 8;
      else
	break;
    }
  return wCursor + 4;
  
}


DWORD ReadVarLen(BYTE* StartBuff, unsigned* pNumBytesRead)
{
  unsigned wCursor = 0;
  register DWORD value = 0;
  register BYTE c;
  
  do{
    
    c = StartBuff[wCursor];
    value = (value <<7) | (c & 0x7F);
    wCursor++;
  }while (c & 0x80);
  
  *pNumBytesRead = wCursor;
  return(value);
}



