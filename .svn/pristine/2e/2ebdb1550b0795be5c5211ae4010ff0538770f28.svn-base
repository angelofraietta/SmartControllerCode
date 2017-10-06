#include "stdafx.h"
#include "control.h"
#include <stdio.h>
#include <stdlib.h>
#include "smutility.h"

#include "messagecell.h"


MemoryCache MessageCell::_mem_manager;

void* MessageCell::operator new (size_t size)
{
  return _mem_manager.allocate(size);

}

void MessageCell::operator delete (void* mem)
{
  _mem_manager.free(mem);

}

bool MessageCell::Store(int Val)
{
	ClearString ();
  MsgType = IntType;
  ival = Val;
  return true;
}


bool MessageCell::Store(double Val)
{
	ClearString ();
  MsgType = DoubleType;
  dval = Val;
  return true;
}


bool MessageCell::Store(const char* Val)
{
	if (strlen (Val))
		{
			if (SMUtility::IsInt(Val))
				{
					Store (atoi(Val));
				}
			else if (SMUtility::IsFloat (Val))
				{
          printf ("Is Float %s\r\n", Val);
					Store (atof(Val));
				}
			else
				{
					sval = Val;
          MsgType = StringType;
				}
		}
	else
		{
			Store ();
		}
	return true;
}

MessageCell& MessageCell::operator=(const MessageCell& M)
{
  MsgType = M.MsgType;
  switch (MsgType){
  case VoidType: break;

  case IntType: ival = M.ival;
    break;

  case DoubleType: dval = M.dval;
    break;

  case StringType: sval = M.sval.c_str();
    break;
  default: break;
  };
  return *this;
}

MessageCell operator+(const MessageCell &left, const MessageCell &right)
{
  MessageCell ret;
  
  if (left.isNumeric() && right.isNumeric())
  {
    if (left.MsgType == MessageCell::DoubleType || right.MsgType == MessageCell::DoubleType)
    {
      ret.Store(left.dval + right.dval);
    }
    else
    {
      ret.Store(left.ival + right.ival);
    }
  }
  
  return ret;
}

void MessageCell::ClearString ()
{
	if (MsgType == StringType)
		{
			sval.purge();
		}
}

bool MessageCell::GetMessage  (char* buff, unsigned buff_len) const
{
  
	bool ret = false;
	switch (MsgType)
		{
		case VoidType: 
			buff[0] = '\0';
			ret = true;
			break;
			
		case IntType: 
		 ret = SMUtility::IntToStr (ival, buff, buff_len);
		 break;
		 
		case DoubleType: 
			ret = SMUtility::FltToStr (dval, buff, buff_len);
		 break;
		 
	 case StringType:
		 if (strlen (sval.c_str()) < buff_len)
			 { 
				 strncpy (buff, sval.c_str(), buff_len -1);
				 ret = true;
			 }
		 break;
		default: break;
		};
	return ret;
}
