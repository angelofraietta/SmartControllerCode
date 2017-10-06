//---------------------------------------------------------------------------
#include "stdafx.h"
#include "control.h"
#include "patchports.h"
#include "patch.h"
#include "typenames.h"
#include <stdio.h>

#define NUM_INLETPORT_INLETS  0
#define NUM_INLETPORT_OUTLETS  1


#define NUM_OUTLETPORT_INLETS  1
#define NUM_OUTLETPORT_OUTLETS  0

const char*const PatchInletPort::szType = INLETPORT_TYPE;
const unsigned PatchInletPort::NumAccess = 1;


PatchInletPort::PatchInletPort(Patch* ParentPatch,
                               const char* Name,
                               const char* Comment, unsigned InletNumber)
  :BaseShell(ParentPatch, NUM_INLETPORT_INLETS,
	     NUM_INLETPORT_OUTLETS, Name,Comment), wInletNumber(InletNumber)
{
}

PatchInletPort::~PatchInletPort()
{
  RemoveFromPatch();
}

PatchInletPort* PatchInletPort::Create(Patch* Parent)
{
  unsigned InletNumber = Parent->GetNumInlets();
  char buffer[80];
  sprintf(buffer, "Inlet %d", InletNumber + 1);
  return new PatchInletPort(Parent,buffer,  "", InletNumber);
}


void PatchInletPort::RemoveFromPatch()
{
  if(pParent)
    pParent->RemoveInlet(this);
}


void PatchInletPort::Input()
{
  tpOutlet[0]->ProduceOutput();
}

void PatchInletPort::Input(int i)
{
  tpOutlet[0]->ProduceOutput(i);
}

void PatchInletPort::Input(double d)
{
  tpOutlet[0]->ProduceOutput(d);
}
void PatchInletPort::Input(const char* s)
{
  tpOutlet[0]->ProduceOutput(s);
}

const char* PatchInletPort::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return "Patch Inlet";
  else
    return NULL;
}



const PatchInletPort::str_access PatchInletPort::aAccess[NumAccess] =
{

  {"InletNumber", &PatchInletPort::InletNumber, NULL}
  
};


const char* PatchInletPort::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool PatchInletPort::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}

bool PatchInletPort::InletNumber (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetInletNumber (), ret, ret_size);
}

//**********************************************************************
// PatchOutletPort function defs

const char*const PatchOutletPort::szType = OUTLETPORT_TYPE;
const unsigned PatchOutletPort::NumAccess = 1;


PatchOutletPort::PatchOutletPort(Patch* ParentPatch,
				 const char* Name,
				 const char* Comment,
				 unsigned OutletNum)
  :BaseShell(ParentPatch, NUM_OUTLETPORT_INLETS,
	     NUM_OUTLETPORT_OUTLETS,Name,Comment),
  OutletNumber(OutletNum){}

PatchOutletPort::~PatchOutletPort()
{
  RemoveFromPatch();
}

PatchOutletPort* PatchOutletPort::Create(Patch* Parent)
{
  unsigned OutletNum = Parent->GetNumOutlets();
  char buffer[80];
  sprintf(buffer, "Outlet %d", OutletNum + 1);
  
  return new PatchOutletPort(Parent, buffer, "", OutletNum);
}

void PatchOutletPort::RemoveFromPatch()
{
  if(pParent)
    pParent->RemoveOutlet(this);
}


void PatchOutletPort::VoidInlet(unsigned InletNumber)
{
  if (InletNumber < GetNumInlets())
    
    pParent->ProduceOutput(OutletNumber);
}
void PatchOutletPort::IntInlet(unsigned InletNumber, int i)
{
  if (InletNumber < GetNumInlets())
    
    pParent->ProduceOutput(OutletNumber, i);
}

void PatchOutletPort::DoubleInlet(unsigned InletNumber, double d)
{
  if (InletNumber < GetNumInlets())
    
    pParent->ProduceOutput(OutletNumber, d);
}

void PatchOutletPort::StringInlet(unsigned InletNumber, const char* s)
{
  if (InletNumber < GetNumInlets())
    
    pParent->ProduceOutput(OutletNumber, s);
}

const char* PatchOutletPort::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return "Patch Output";
  else
    return NULL;
}




const PatchOutletPort::str_access PatchOutletPort::aAccess[NumAccess] =
{

  {"OutletNumber", &PatchOutletPort::GetOutletNumber, NULL}
  
};


const char* PatchOutletPort::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool PatchOutletPort::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}

bool PatchOutletPort::GetOutletNumber (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetOutletNumber (), ret, ret_size);
}

//---------------------------------------------------------------------------



