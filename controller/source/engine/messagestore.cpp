//MessageStore function dfns

#include "stdafx.h"
#include "control.h"
#include "messagestore.h"
#include "typenames.h"
#include <string.h>
#include <stdio.h>

#define NUM_INLETS 2
#define NUM_OUTLETS 1



const char*const MessageStore::szType = MESSAGESTORE_TYPE;

const unsigned MessageStore::NumAccess = MessageStore::eMaxAttribute;
const unsigned MessageStore::NumResetAccess = MessageStore::eMaxResetAttribute;


// create the default
static MessageStore *reference = new MessageStore (NULL);

const BaseShell* MessageStore::GetReference() const
{
	return reference;
}

const char*const MessageStore::szaInletDetails[NUM_INLETS] = {
  "Send Message",
  "Store Message"
};

const char*const MessageStore::szaOutletDetails[NUM_OUTLETS] = {
  "Message Output"
};

const char* MessageStore::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}

const char* MessageStore::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}


MessageStore::MessageStore (Patch* Parent, const char* Name,
			    const char* Comment)
  : BaseShell (Parent, NUM_INLETS,NUM_OUTLETS,
	       Name, Comment), ResetMessage()
  
{
  Reset();
}

MessageStore::MessageStore (Patch* Parent, const char* Name,
			    const char* Comment, int i)
  : BaseShell (Parent, NUM_INLETS,NUM_OUTLETS,
	       Name, Comment), ResetMessage(i)
  
{
  Reset();
}

MessageStore::MessageStore (Patch* Parent, const char* Name,
			    const char* Comment, double d)
  : BaseShell (Parent, NUM_INLETS,NUM_OUTLETS,
	       Name, Comment), ResetMessage(d)
  
{
  Reset();
}

MessageStore::MessageStore (Patch* Parent, const char* Name,
			    const char* Comment, const char* s)
  : BaseShell (Parent, NUM_INLETS,NUM_OUTLETS,
      				 Name, Comment), ResetMessage(s)

{
   Reset();
}

const MessageStore::pVoidFunc  MessageStore::tpVoidFunc [] = {
	&MessageStore::Send,
	&MessageStore::Store
};

const MessageStore::pStringFunc  MessageStore::tpStringFunc [] = {
	&MessageStore::Send,
	&MessageStore::Store
};

const MessageStore::pIntFunc  MessageStore::tpIntFunc [] = {
	NULL,
	&MessageStore::Store
};

const MessageStore::pDoubleFunc  MessageStore::tpDoubleFunc [] = {
	NULL,
	&MessageStore::Store
};

BaseShell* MessageStore::Create(Patch* Parent)
{
	return new MessageStore (Parent);
};

void MessageStore::VoidInlet(unsigned InletNumber)
{
	if ((InletNumber < GetNumInlets()) && (tpVoidFunc[InletNumber]))
   	(this->*tpVoidFunc[InletNumber])();
}

void MessageStore::StringInlet(unsigned InletNumber, const char* s)
{
	if ((InletNumber < GetNumInlets())&&(tpStringFunc[InletNumber]))
   	(this->*tpStringFunc[InletNumber])(s);
}

void MessageStore::IntInlet(unsigned InletNumber, int i)
{
	if ((InletNumber < GetNumInlets()) && (tpIntFunc[InletNumber]))
   	(this->*tpIntFunc[InletNumber])(i);
}

void MessageStore::DoubleInlet(unsigned InletNumber, double d)
  {
    if ((InletNumber < GetNumInlets()) &&(tpDoubleFunc[InletNumber]))
      {
   	(this->*tpDoubleFunc[InletNumber])(d);
      }
  else
    {
      IntInlet (InletNumber, DoubleToInt(d));
    }
  }


void MessageStore::Send ()
{
   switch (StoredMessage.MsgType){
      case MessageCell::VoidType:
         tpOutlet[0]->ProduceOutput();
         break;
      case MessageCell::IntType:
         tpOutlet[0]->ProduceOutput(StoredMessage.ival);
         break;
      case MessageCell::DoubleType:
         tpOutlet[0]->ProduceOutput(StoredMessage.dval);
         break;
      case MessageCell::StringType:
         	tpOutlet[0]->ProduceOutput(StoredMessage.sval.c_str());
            break;
      default:
         break;
   };//end case
};

void MessageStore::Send(const char* s)
{
	if (!strcmp (s, "send")) // the two are ==
   	{Send(); return;}

   if (!strcmp (s, "reset"))
   	{Reset(); return;}
}




// the get functions return true if the message type matches the ret parameter

bool MessageStore::GetMessage (char* buff, unsigned buff_len) const
{
	return StoredMessage.GetMessage(buff, buff_len);
}

bool MessageStore::GetResetMessage (char* buff, unsigned buff_len)const
{
	return ResetMessage.GetMessage(buff, buff_len);
}

const MessageStore::str_access MessageStore::aAccess[NumAccess] =
{

  {"Message", &MessageStore::GetMessage, &MessageStore::Store}  
};


const char* MessageStore::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool MessageStore::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
			(this->*aAccess [index].set_func) (value);
       ret = true;
    }

  return ret;
}

bool MessageStore::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}


const MessageStore::str_access MessageStore::aResetAccess[NumResetAccess] =
{

  {"ResetMessage", &MessageStore::GetResetMessage, &MessageStore::StoreReset}
  
};

const char* MessageStore::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool MessageStore::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      (this->*aResetAccess [index].set_func) (value);
			ret = true;
    }

  return ret;
}

bool MessageStore::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool MessageStore::GetDefaultAttribute (char* buf, unsigned buf_len)const
{
	return GetMessage (buf, buf_len);
}



bool MessageStore::SetDefaultAttribute (const char* new_value)
{
	Store (new_value);
	return true;
}




