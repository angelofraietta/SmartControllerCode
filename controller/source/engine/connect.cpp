 #include "stdafx.h"
#include <stdlib.h>
#include "control.h"
#include "patch.h"
#include "typenames.h"        


//#define SHOW_LOAD_DEBUG

const char*const Connector::szType = CONNECTOR_TYPE;

const char*const Connector::StartBlock = "CON"; // Start Of Object Block

Connector::	Connector():Identity (NULL, "",""){}

Connector::Connector(Patch* ParentList,
		     SocketDetails pOutletAddress,
		     SocketDetails pInletAddress,
                     const char* Name,
                     const char* Comment)
  :Identity (ParentList, Name, Comment),
   
   InletConnection(pInletAddress),
   OutletConnection(pOutletAddress)
{
  ConnectToOutlet();
  ConnectToInlet();
}


bool Connector::operator==(const Connector& Con)const
{
  if (this == &Con)
    return 1;
  return ((Con.InletConnection == (*this).InletConnection)
	  && (Con.OutletConnection == (*this).OutletConnection));
}



bool Connector::Disconnect(int Disconnector)
{
  // this function is called by an InletContainer, Outlet, or pParent
  // The Connector then disconnects from the the two that did not call the
  // function.  The Connector then destroys itself
  
  bool Successful ;
  switch (Disconnector){
    
  case ByInlet:	Successful  = DisconnectFromOutlet()&&
		  DisconnectFromParent();
  break;
  
  case ByOutlet: Successful  = DisconnectFromInlet()&&
		   DisconnectFromParent();
  break;
  case ByParent: Successful  = DisconnectFromInlet() &&
									 DisconnectFromOutlet();
  break;
  
  default:	break;
    
  }; //end case
  
  
  if (Successful )
    delete this;
  
  return Successful;
}

inline bool Connector::DisconnectFromParent()
{
  return pParent->Detach(this, Patch::ByConnector);
}

bool Connector::DisconnectFromInlet ()
{
  if (!!InletConnection) // there is a shell
    {
      // create the message
      ConnectorMessage TheMessage;
      TheMessage.pCon = this;
      TheMessage.fJoin = false;
      TheMessage.fToInlet = true;
      TheMessage.wSocketNumber = InletConnection.wSocketNumber;
      
      int Success = InletConnection.pBase->Connect(TheMessage);
      // send message to inlet
      
      InletConnection.pBase = NULL; // invalidate InletConnection
      if (!Success)
        {
          Error(eInternalError, this);
        }
      return Success;
    }
  else
    return false;
}


bool Connector::DisconnectFromOutlet()
{
  
  if (!!OutletConnection) // there is a valid connection
    {
      ConnectorMessage TheMessage;
      TheMessage.pCon = this;
      TheMessage.fJoin = false;
      TheMessage.fToInlet = false;
      TheMessage.wSocketNumber = OutletConnection.wSocketNumber;
      int Success = (OutletConnection.pBase->Connect)(TheMessage);
      
      OutletConnection.pBase = NULL; // invalidate the address
      if (!Success)
        Error(eInternalError, this);
      
      return Success;
    }
  else
    return 0;
  
}


bool Connector::ConnectToInlet()
{
  bool Success;
  ConnectorMessage TheMessage;
  TheMessage.pCon = this;
  TheMessage.fJoin = true;
  TheMessage.fToInlet = true;
  TheMessage.wSocketNumber = InletConnection.wSocketNumber;
  Success = InletConnection.pBase->Connect(TheMessage);
  if (!Success)
    {
      InletConnection.pBase = NULL; // invalidate InletConnection
      Error(eInternalError, this);
    }
  else
    {
    }
  
  
  return Success;
  
}


bool Connector::ConnectToInlet (SocketDetails TheInlet)// points to where to send address
{
  if (!!InletConnection) // must already be connected
    DisconnectFromInlet();// disconnect
  
  if(!!TheInlet)
    {
      // Assigne the new inlet connection details
      InletConnection = TheInlet;
      bool Success = ConnectToInlet();
      return Success;
    }
  else
    return false;
}

bool Connector::ConnectToOutlet()
{
  bool Success;
  ConnectorMessage TheMessage;
  TheMessage.pCon = this;
  TheMessage.fJoin = true;
  TheMessage.fToInlet = false;
  TheMessage.wSocketNumber = OutletConnection.wSocketNumber;
  
  
  Success = OutletConnection.pBase->Connect(TheMessage);
  if (!Success)
    {
      Error(eInternalError, this);
      OutletConnection.pBase = NULL; // invalidate base
    }

  return Success;
}

bool Connector::ConnectToOutlet (SocketDetails TheOutlet )// points to where to sene address
{
  if (!!OutletConnection) // must already be connected
    DisconnectFromOutlet();
  
  if (!!TheOutlet)
    {
      bool Success;
      //Assign the New Outlet details
      OutletConnection = TheOutlet;
      Success = ConnectToOutlet();
      return Success;
    }
  else
    return false;
}


void Connector::Save(FILE* outfile)
{
  fprintf (outfile, "%s\r\n", StartBlock);

  SaveID(outfile);

  fprintf(outfile, "%u %u %u %u\r\n", OutletConnection.pBase->PatchPosition(),
          OutletConnection.wSocketNumber,
          InletConnection.pBase->PatchPosition(),
          InletConnection.wSocketNumber);

  fprintf(outfile, "%s\r\n", EndBlock);
  
}


void Connector::SetModified(bool Modified)
{
  IsModified = Modified;
  if (IsModified && pParent)
    pParent->SetModified(Modified);
}

bool Connector::CanSave()const
{
  return pParent->CanSave();
}


bool Connector::Restore(FILE* infile, Patch* parent)
{

	bool ret = false;
	bool complete = false;

#ifdef SHOW_LOAD_DEBUG
	cout<<"Connector Read Input Buffer"<<endl;
#endif

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
    	// Get each of the values
      unsigned outlet_base_index, outlet_num, inlet_base_index, inlet_num;
      outlet_base_index = atoi (cursor);

      cursor = cursor + strlen (cursor) + 1;
      cursor =  Tokenize (&cursor);
      outlet_num = atoi (cursor);

      cursor = cursor + strlen (cursor) +1;
      cursor =  Tokenize (&cursor);
      inlet_base_index = atoi (cursor);

			cursor = cursor + strlen (cursor) +1;
      cursor =  Tokenize (&cursor);
      inlet_num = atoi (cursor);

#ifdef SHOW_LOAD_DEBUG
			cout<<"Connector Indexes"<<outlet_base_index<< " " <<outlet_num << " "
					<<inlet_base_index<<" "<<inlet_num <<endl;
#endif

      BaseShell* pInletShell = parent->FindObject(outlet_base_index);
      BaseShell* pOutletShell = parent->FindObject(inlet_base_index);

			if ((pInletShell) && (pOutletShell))
				{
					SetOutletBase (pInletShell);
					SetOutletNum(outlet_num);
					
					SetInletBase (pOutletShell);
					SetInletNum(inlet_num);
					
					SetParent(parent);
#ifdef SHOW_LOAD_DEBUG
					cout<<"Making Connections"<<endl;
#endif

					ret = ConnectToInlet() &&  ConnectToOutlet();
				}
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
  return ret;
}

