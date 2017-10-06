 // The superclass shell by which all action classes are derived
#include "stdafx.h"
#include <stdlib.h>

#include "control.h"
#include "patch.h"
#include "ostypes.h"
#include "typelist.h"

const char*const BaseShell::StartBlock = "OBJ"; // Start Of Object Block

BaseShell::  BaseShell (Patch* Parent,
			unsigned NumInlets,
			unsigned NumOutlets,
			const char* Name,
			const char* Comment)
  :Identity(Parent, Name, Comment),
   wNumInlets(NumInlets), wNumOutlets(NumOutlets)
{
  CreateOutlets();
  CreateInletLists();
}

BaseShell::~BaseShell()
{
  //destroy all outlets
  for (unsigned i = 0; i < wNumOutlets; i++)
    {
      OutletContainer* pOutlet = tpOutlet[i];
      delete pOutlet;
    }
  
  for (unsigned i = 0; i < wNumInlets; i++)
    {
      InletContainer* pInlet = tpInletConnections[i];
      delete pInlet;
    }
}

unsigned BaseShell::GetNumObjectTypes()
{
  return TypeList::NumElements;
}

const char* BaseShell::GetObjectType(unsigned index)
{
  return TypeList::GetTypeName(index);
}

bool BaseShell::Connect(ConnectorMessage ConnectionDetails)
{
  // check for inlet or outlet
  if (ConnectionDetails.fToInlet)
    {
      // check for valid Inlet Number
      if (ConnectionDetails.wSocketNumber >= wNumInlets)
				return false;
      // See if Making or deleteing a Connection
      if (ConnectionDetails.fJoin)
      	return tpInletConnections[ConnectionDetails.wSocketNumber]
					->AddConnector (ConnectionDetails.pCon);
      else // must be removing
      	return tpInletConnections[ConnectionDetails.wSocketNumber]->
					RemoveConnector (ConnectionDetails.pCon);
    }
  else // must be outlet
    {
      //check for valid Outlet Number
      if (ConnectionDetails.wSocketNumber >= wNumOutlets)
				return false;
      // See if Making or deleteing a Connection
      if (ConnectionDetails.fJoin)
				return tpOutlet[ConnectionDetails.wSocketNumber]
					->AddConnector(ConnectionDetails.pCon);
      else // must be deleteing
				return tpOutlet[ConnectionDetails.wSocketNumber]
					->RemoveConnector(ConnectionDetails.pCon);
    }
  
}

bool BaseShell::CanConnectInlet(unsigned InletNum, Connector* pCon)
{
  if ((pParent) && (pParent->CanSave()) && InletNum < wNumInlets)
    return !(tpInletConnections[InletNum]->HasConnector(pCon));
  else
    return false;
}

bool BaseShell::CanConnectOutlet(unsigned OutletNum, Connector* pCon)
{
  if ((pParent) && (pParent->CanSave()) && OutletNum < wNumOutlets)
    return !(tpOutlet[OutletNum]->HasConnector(pCon));
  else
    return false;
}


void BaseShell::CreateOutlets()
{
  //create the Outlets
  for(unsigned i = 0; i < wNumOutlets; i++)
    {
      OutletContainer* pOutlet = new OutletContainer(this, i); // create the OutletContainer
      if (pOutlet)
				{
					tpOutlet.push_back(pOutlet);
				}
    }
}

void BaseShell::CreateInletLists()
{
  //create the Inlets
  for(unsigned i = 0; i < wNumInlets; i++)
    {
      
      InletContainer* pInlet = new InletContainer(this); // create the InletContainer
      if (pInlet)
				{
					tpInletConnections.push_back(pInlet);
				}
    }
}

unsigned BaseShell::PatchPosition()const
{
  unsigned position = 0;
  if (pParent)
    {
      position = pParent->FindPosition(this);
    }
  return position;
}


void BaseShell::Save(FILE* outfile)
{

  //save Identity
  fprintf (outfile, "%s %s\r\n", StartBlock, GetType());

  SaveID(outfile);

	for (unsigned i = 0; i < GetNumResetAccess (); i++)
		{
			char buff [128];
      char ref [128];
			if (GetResetAttribute(i, buff, sizeof(buff)))
				{
         if (GetReference() && GetReference()->GetResetAttribute(i, ref, sizeof(ref)))
         {
            // only write if different to Reference
            if (strcmp (buff, ref))
            {
					    fprintf (outfile, "%u %s\r\n", i, buff);
            }
         }
         else
         {
            fprintf (outfile, "%u %s\r\n", i, buff);
         }
				}
		}
	fprintf(outfile, "%s\r\n", EndBlock);

}

void BaseShell::SaveConnectors (FILE* OutFile)const
{
	for (unsigned OutletNum = 0; OutletNum < GetNumOutlets(); OutletNum++)
		{
			tpOutlet[OutletNum]->SaveConnectors(OutFile);
		}
	
}

bool BaseShell::Restore(FILE* infile)
{

	bool complete = false;
	Readline (infile, RestoreInputBuffer, RestoreInputBufferSize);
	// read all the different types of commands that it could be
  do
  {
  	char* cursor = RestoreInputBuffer;

		cursor = Tokenize (&cursor);
  	if (!strcmp (cursor, StartIdBlock))
    {
    	RestoreID(infile);
    }
    else if (SMUtility::IsInt(cursor))
    {
      unsigned attribute_num = atoi (cursor);

    	// move past this to the object type;
      char* attribute_val =  cursor + strlen (cursor) + 1;
      SetResetAttribute (attribute_num, attribute_val);
    }
    else if  (!strcmp (cursor, EndBlock))
    {
    	complete = true;
    }
    else
    {
    	// just read the line
    }

    if (!complete)
    {
      Readline (infile, RestoreInputBuffer, RestoreInputBufferSize);
    }

  } while (!complete);

  // restore attributes
  return true;
}

unsigned BaseShell::FindOutletConnectorIndex(unsigned OutletNum,
																						 const Connector* pCon)const
{
  if(!(OutletNum < GetNumOutlets()) || !(tpOutlet[OutletNum]->HasConnector(pCon)))
    {
			Error (eInvalidIndex, this, (int)OutletNum);
			return 0;
		}
  
  return tpOutlet[OutletNum]->FindIndex(pCon);
}

unsigned BaseShell::FindInletConnectorIndex(unsigned SocketNum,
                                            const Connector* pCon)const
{
  if(!(SocketNum < GetNumInlets()) || !(tpInletConnections[SocketNum]->HasConnector(pCon)))
		{
			Error (eInvalidIndex, this, (int)SocketNum);
			return 0;
		}
  
  return tpInletConnections[SocketNum]->FindIndex(pCon);
}

void BaseShell::RemoveInlet()
{
  //delete last InletContainer
  delete tpInletConnections[GetNumInlets() -1];
#ifndef _BORLAND_CONTAINERS
  tpInletConnections.pop_back();
#else
  tpInletConnections.Detach(wNumInlets -1)
#endif   
    //change number in BaseShell
    wNumInlets--;
}

void BaseShell::RemoveOutlet()
{
  //delete last OutletContainer
  delete tpOutlet[wNumOutlets - 1];
#ifndef _BORLAND_CONTAINERS
  tpOutlet.pop_back();
#else
  tpOutlet.Detach(wNumOutlets -1)
#endif   
    //change number in BaseShell
    wNumOutlets--;
}
void BaseShell::AddOutlet()
{
  //create new OutletContainer
  OutletContainer* pOutletContainer = new OutletContainer(this, GetNumOutlets());
#ifndef _BORLAND_CONTAINERS
  tpOutlet.push_back(pOutletContainer);
#else
  tpOutlet.Add(pOutletContainer);
#endif
  
  //Increment number in BaseShell
  wNumOutlets++;
}

void BaseShell::AddInlet()
{
  //create new InletContainer
  InletContainer* pInletContainer = new InletContainer(this,	GetNumInlets());
#ifndef _BORLAND_CONTAINERS
  tpInletConnections.push_back(pInletContainer);
#else
  tpInletConnections.Add(pInletContainer)
#endif
    //Increment number in BaseShell
    wNumInlets++;
}


unsigned BaseShell::GetNumInletConnectors(unsigned InletNum)const
{
  if (InletNum < GetNumInlets())
    return tpInletConnections[InletNum]->GetNumConnectors();
  else
    return 0;
}

unsigned BaseShell::GetNumOutletConnectors(unsigned OutletNum)const
{
  if(OutletNum <  GetNumOutlets())
    return tpOutlet[OutletNum]->GetNumConnectors();
  else
    return 0;
}

Connector* BaseShell::GetInletConnector(unsigned InletNum, unsigned ConnectorNum)
{
  if (InletNum < GetNumInlets())
    return tpInletConnections[InletNum]->GetConnector(ConnectorNum);
  else
    return NULL;
}

Connector* BaseShell::GetOutletConnector(unsigned OutletNum, unsigned ConnectorNum)
{
  if(OutletNum <  GetNumOutlets())
    return tpOutlet[OutletNum]->GetConnector(ConnectorNum);
  else
    return NULL;
}

void BaseShell::SetModified(bool Modified)
{
  IsModified = Modified;
  if (IsModified && pParent)
    pParent->SetModified(Modified);
}

bool BaseShell::CanSave()const
{
  return ((!pParent) || pParent->CanSave());
}

void BaseShell::SwapOutletConnector(unsigned OutletNumber, unsigned Index1, unsigned Index2)
{
  if(OutletNumber < GetNumOutlets())
    {
      tpOutlet[OutletNumber]->SwapConnector(Index1, Index2);
    }
}

int BaseShell::DoubleToInt (double d)
{
  int i;
  
  if (d < 0)
    {
      d -= 0.5;
    }
  
  else
    {
      d += 0.5;
    }
  
  if (d >= MAXINT)
    {
      i = MAXINT;
    }
  
  else if (d <= (-MAXINT))
    {
      i = (-MAXINT) + 1;
    }
  
  else
    {
      i = (int) d;
    }

  return i;

} // end BaseShell::DoubleToInt


