//switch function dfns
#include "stdafx.h"

#include "control.h"
#include "switch.h"
#include "typenames.h"
#include <stdio.h>



#define SWITCH_OUTLETS_NUM_INLETS  2

#define SWITCH_INLETS_NUM_OUTLETS  1

const unsigned Switch::NumAccess = Switch::eMaxAttribute;
const unsigned Switch::NumResetAccess = Switch::eMaxResetAttribute;


void Switch::SetResetSwitchPos (int i)
{
  if(iResetSwitchPosition == (unsigned)i)
    return;

 iResetSwitchPosition = (unsigned) i;
  SetModified(true);
}

const char*const Switch::szInletZeroName = "Set Position";

const Switch::str_access Switch::aAccess[NumAccess] =
{
  {"SwitchPosition", &Switch::SwitchPosition, &Switch::SwitchPosition}
};


void Switch::DoDefaultAction()
{
	iSwitchPosition++;
	if (iSwitchPosition > GetNumContacts()+1)
		{
			iSwitchPosition = 0;
		}
}

const char* Switch::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool Switch::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;
  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool Switch::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}


const Switch::str_access Switch::aResetAccess[NumResetAccess] =
{
  {"NumberOfContacts", &Switch::NumberOfContacts, &Switch::NumberOfContacts},
  {"ResetSwitchPosition", &Switch::ResetSwitchPosition, &Switch::ResetSwitchPosition}
};


const char* Switch::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool Switch::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool Switch::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}


bool Switch::SwitchPosition (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetSwitchPos (), ret, ret_size);
}

bool Switch::NumberOfContacts (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetNumContacts (), ret, ret_size);
}

bool Switch::ResetSwitchPosition (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetResetSwitchPos (), ret, ret_size);
}


bool Switch::SwitchPosition (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetSwitchPos(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Switch::NumberOfContacts (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetNumContacts(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}

bool Switch::ResetSwitchPosition (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetResetSwitchPos(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}


//---------------------------------------------------------------------------//



//define Inlets

const char*const SwitchInlets::szInletName = "Switch Pole ";
const char*const SwitchInlets::szOutletName = "Output Contact ";
const char*const SwitchInlets::szType = SWITCH_INLETS_TYPE;

// create the default
static SwitchInlets *SwitchInlets_reference ;//= new SwitchInlets (NULL);

const BaseShell* SwitchInlets::GetReference() const
{
	return SwitchInlets_reference;
}


const char* SwitchInlets::GetInletName(unsigned InletNumber)const
{
  if (InletNumber == 0)
    return szInletZeroName;
  
  return szInletName;
}

const char* SwitchInlets::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szOutletName;
  else
    return NULL;
}


SwitchInlets::SwitchInlets(Patch* Parent,
													 unsigned NumContacts,
													 const char* Name,
													 const char* Comment,
													 unsigned SwitchPosition) // initial position
  :Switch(Parent, (NumContacts + 1), SWITCH_INLETS_NUM_OUTLETS,
					Name,Comment, SwitchPosition)
{}


BaseShell* SwitchInlets::Create(Patch* Parent)
{
  return new SwitchInlets(Parent,1);
}


void  SwitchInlets::VoidInlet(unsigned InletNumber)
{  
	if ((InletNumber != 0 ) && (InletNumber < GetNumInlets()))
		PassMessage(InletNumber);
}


void  SwitchInlets::IntInlet(unsigned InletNumber, int i)
{
  if (!(InletNumber < GetNumInlets()))
    return;

  if (InletNumber == 0)
    SetSwitchPos(i);
  else
    PassMessage(InletNumber, i);
  
}

void  SwitchInlets::StringInlet(unsigned InletNumber, const char* s)
{ 
  if (!(InletNumber < GetNumInlets()))
    return;
  if (InletNumber == 0)
    {
      if(!strcmp(s, "reset"))
       	Reset();
    }
  else
    PassMessage(InletNumber, s);
}

void  SwitchInlets::DoubleInlet(unsigned InletNumber, double d)
{
  if ((InletNumber != 0 ) && (InletNumber < GetNumInlets()))
    {
      PassMessage(InletNumber, d);
    }
  
  else
    {
      IntInlet (InletNumber, DoubleToInt(d));
    }
  
}

void  SwitchInlets::PassMessage(unsigned InletNumber)
{
  if (iSwitchPosition - 1 == (unsigned)InletNumber)
    tpOutlet[0]->ProduceOutput();
}

void  SwitchInlets::PassMessage(unsigned InletNumber, const char* s)
{
  if (iSwitchPosition - 1 == (unsigned) InletNumber)
    tpOutlet[0]->ProduceOutput(s);
}


void  SwitchInlets::PassMessage(unsigned InletNumber, int i)
{
  if (iSwitchPosition - 1 == (unsigned)InletNumber)
    tpOutlet[0]->ProduceOutput(i);
}

void  SwitchInlets::PassMessage(unsigned InletNumber, double d)
{
  if (iSwitchPosition - 1 == (unsigned)InletNumber)
    tpOutlet[0]->ProduceOutput(d);
}

bool SwitchInlets::GetDefaultAttribute (char* ret_value, unsigned buff_len)const
{
	bool ret = SwitchPosition(ret_value, buff_len);

	if (iSwitchPosition <= 1 || iSwitchPosition > GetNumContacts()+1)
    {
      int buf_cursor = strlen (ret_value);
			strncpy (ret_value + buf_cursor, " - N/C", buff_len -1 - buf_cursor);
      ret_value[buff_len] = 0;
		}

	return ret;
}


void SwitchInlets::SetNumContacts(int iNewNumContacts)
{
  if (iNewNumContacts > MAX_UINT8 || iNewNumContacts < 0)
    {
      printf ("Invalid Number Contacts :%u\r\n", iNewNumContacts);
      return;
    }
	
  unsigned NewNumContacts = (unsigned) iNewNumContacts;
  unsigned NumContacts = (unsigned)GetNumContacts();
  
  if (NewNumContacts == NumContacts)
    return;
  //remove
  if (NewNumContacts < NumContacts)
    {
      if (NewNumContacts < 1)
				{
					Error(eInvalidSwitchContacts, this, iNewNumContacts);
					NewNumContacts = 1;
				}
      
      for (unsigned i = NumContacts; i > NewNumContacts; i--)
				RemoveInlet();

      SetModified(true);
      return;
    }
  //must be greater
  for (unsigned i = NumContacts; i < NewNumContacts; i++)
    AddInlet();
  
  SetModified(true);
  
}


int SwitchInlets::GetNumContacts()const
{
  return GetNumInlets() - 1;
}
//*********************************************************************
//SwitchOutletsfunctions
const char*const SwitchOutlets::szInletName = "Input Contact ";
const char*const SwitchOutlets::szOutletName = "Output Pole ";
const char*const SwitchOutlets::szType = SWITCH_OUTLETS_TYPE;

// create the default
static SwitchOutlets *SwitchOutlets_reference = new SwitchOutlets (NULL);

const BaseShell* SwitchOutlets::GetReference() const
{
	return SwitchOutlets_reference;
}

const char* SwitchOutlets::GetInletName(unsigned InletNumber)const
{
  if (InletNumber == 0)
    {
      return szInletZeroName;
    }
  
  return szInletName;
}

const char* SwitchOutlets::GetOutletName(unsigned OutletNumber)const
{
  UNREFERENCED_PARAMETER (OutletNumber);
  return szOutletName;
}


SwitchOutlets::SwitchOutlets(Patch* Parent,
														 unsigned NumContacts,
														 const char* Name,
														 const char* Comment,
														 unsigned SwitchPosition) // initial position
  :Switch(Parent, SWITCH_OUTLETS_NUM_INLETS,
					NumContacts, Name,Comment, SwitchPosition)
{}


BaseShell* SwitchOutlets::Create(Patch* Parent)
{
  return new SwitchOutlets(Parent,1);
}


void SwitchOutlets::VoidInlet (unsigned InletNumber)
{
  if ((InletNumber < GetNumInlets())
      && (InletNumber > 0)
      && (iSwitchPosition > 0)
      && (iSwitchPosition  <= (unsigned)GetNumOutlets()))
    tpOutlet[iSwitchPosition -1]->ProduceOutput();
}

void SwitchOutlets::IntInlet (unsigned InletNumber, int i)
{
  if (InletNumber == 0)
    SetSwitchPos(i);
  else
    if ((InletNumber < GetNumInlets())
				&&(iSwitchPosition > 0)
				&& (iSwitchPosition <= (unsigned)GetNumOutlets()))
      tpOutlet[iSwitchPosition -1]->ProduceOutput(i);
}

void SwitchOutlets::StringInlet (unsigned InletNumber, const char* s)
{
  if (!(InletNumber < GetNumInlets()))
    return;
  if (InletNumber == 0)
    {
      if(!strcmp(s, "reset"))
        {
					Reset();
        }
      
      return;
    }
  
  if ((InletNumber < GetNumInlets())
      && (InletNumber > 0)
      && (iSwitchPosition > 0)
      && (iSwitchPosition  <= (unsigned)GetNumOutlets()))
    {
      tpOutlet[iSwitchPosition -1]->ProduceOutput(s);
    }
  
}


void SwitchOutlets::DoubleInlet (unsigned InletNumber, double d)
{
  if ((InletNumber < GetNumInlets())
      &&(InletNumber != 0)
      &&(iSwitchPosition > 0)
      &&(iSwitchPosition <= (unsigned)GetNumOutlets()))
    {
      tpOutlet[iSwitchPosition -1]->ProduceOutput(d);
    }
  
  else
    {
      IntInlet (InletNumber, DoubleToInt(d));
    }
}

bool SwitchOutlets::GetDefaultAttribute (char* ret_value, unsigned buff_len)const
{
	bool ret = SwitchPosition(ret_value, buff_len);

	if (iSwitchPosition <= 0 || iSwitchPosition > GetNumContacts())
		{
      int buf_cursor = strlen (ret_value);
			strncpy (ret_value + buf_cursor, " - N/C", buff_len -1 - buf_cursor);
      ret_value[buff_len] = 0;

    }
  return ret;
}

void SwitchOutlets::SetNumContacts(int iNewNumContacts)
{
  if (iNewNumContacts > MAX_UINT8 || iNewNumContacts < 0)
    {
      Error (eInvalidSwitchContacts, this, iNewNumContacts);
      return;
    }
	
  unsigned NewNumContacts = (unsigned) iNewNumContacts;
	
  unsigned NumContacts = (unsigned) GetNumContacts();
  
  if (NewNumContacts == NumContacts)
    return;
  //remove
  if (NewNumContacts < NumContacts)
    {
      if (NewNumContacts < 1)
				{
					Error(eInvalidSwitchContacts, this, iNewNumContacts);
					NewNumContacts = 1;
				}
      
      for (unsigned i = NumContacts; i > NewNumContacts; i--)
				RemoveOutlet();
      return;
    }
  //must be greater
  for (unsigned i = NumContacts; i < NewNumContacts; i++)
    AddOutlet();
}

int SwitchOutlets::GetNumContacts()const
{
  return GetNumOutlets();
}



