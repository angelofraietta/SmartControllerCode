// global functions
#include "stdafx.h"

#include <stdlib.h>
#include "funcdec.h"


bool Atoi(int* Output, const char* Input)
{
  bool Valid = TestValidInt(Input);
  if (Valid)
    *Output = atoi(Input);
  else
    *Output = 0;
  
  return Valid;
  
  
}


bool TestValidInt (const char* InBuf)
  //return true if input number can be converted to an int value
{
  unsigned Invalid = false;
  int i = 0;
  char c;
  
  //find sign bit
  for (c = InBuf [i]; c == ' '; i++)
    ;//keep going
  // check for sign bit
  if ( (c == '-')||(c == '+'))
    i++; //set index past sign
  
  c = InBuf[i];
  if(c == '\0')
    Invalid = true;
  while ( (!Invalid) && (c!='\0'))
    {
      if (c < '0' || c > '9')
      	{
	  Invalid = true;
	  break;
	}
      c = InBuf[++i];
    }; //end while
  return (!Invalid);
};





