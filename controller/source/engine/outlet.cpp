#include "stdafx.h"
#include "control.h"
#include "messagecell.h"


OutletContainer::~OutletContainer()
{
  DeleteConnectors();
}

void  OutletContainer::SaveConnectors (FILE* OutFile)
{
  for (unsigned wCon = 0;
       wCon < GetNumConnectors();
       wCon++)
    {
      Connector* pCon = GetConnector(wCon);
      pCon->Save(OutFile);
    }

}

void  OutletContainer::ProduceOutput (const MessageCell& TheMessage)
{
  switch (TheMessage.MsgType)
    {
    case MessageCell::VoidType:
      ProduceOutput();
      break;
    case MessageCell::IntType:
      ProduceOutput(TheMessage.ival);
      break;
    case MessageCell::DoubleType:
      ProduceOutput(TheMessage.dval);
      break;
    case MessageCell::StringType:
      ProduceOutput(TheMessage.sval.c_str());
      break;
    default:
      break;
    };//end case

}


void OutletContainer::ProduceOutput ()
{
  if (_mutex)
    {
      Identity::Error (eOutletThreadLocked, ThisSocketDetails.pBase, (int)ThisSocketDetails.wSocketNumber);
      return;
    }
  
  _mutex = true;
  
  Connector const* pConnector;
  unsigned Size = (unsigned) apConnector.size();
  for(unsigned i = 0; i < Size; i++)
    {
      pConnector = apConnector[i];
      if (pConnector)
				{  // get the inlet details
					const SocketDetails TheInlet = pConnector->InletConnection;
					BaseShell* pInletBase = TheInlet.pBase;
					if (pInletBase)
            {
							const unsigned wSocketNumber = TheInlet.wSocketNumber;
							(pInletBase->VoidInlet)(wSocketNumber); // send to inlet
            }
				}
    }
  
  _mutex = false;
}



void OutletContainer::ProduceOutput (const char* TheString)
{
  if (_mutex)
    {
      Identity::Error (eOutletThreadLocked, ThisSocketDetails.pBase, (int)ThisSocketDetails.wSocketNumber);
      return;
    }
  
  _mutex = true;
  
  Connector const* pConnector;
  unsigned Size = (unsigned) apConnector.size();
  for(unsigned i = 0; i < Size; i++)
    {
      pConnector = apConnector[i];
      if (pConnector)
				{  // get the inlet details
					const SocketDetails TheInlet = pConnector->InletConnection;
					BaseShell* pInletBase = TheInlet.pBase;
					if (pInletBase)
						{
							const unsigned wSocketNumber = TheInlet.wSocketNumber;
							pInletBase->StringInlet(wSocketNumber, TheString); // send to inlet
            }
				}
    }
  
  _mutex = false;
}

void OutletContainer::ProduceOutput (int TheInt)
{
  if (_mutex)
    {
      Identity::Error (eOutletThreadLocked, ThisSocketDetails.pBase, (int)ThisSocketDetails.wSocketNumber);
      return;
    }
  
  _mutex = true;
  
  Connector const* pConnector;
  unsigned Size = (unsigned) apConnector.size();
  for(unsigned i = 0; i < Size; i++)
    {
      pConnector = apConnector[i];
      if (pConnector)
				{  // get the inlet details
					const SocketDetails TheInlet = pConnector->InletConnection;
					BaseShell* pInletBase = TheInlet.pBase;
					if (pInletBase)
            {
							const unsigned wSocketNumber = TheInlet.wSocketNumber;
							(pInletBase->IntInlet)(wSocketNumber, TheInt); // send to inlet
            }
				}
    }
  _mutex = false;
}

void OutletContainer::ProduceOutput (double TheDouble)
{
  if (_mutex)
    {
      Identity::Error (eOutletThreadLocked, ThisSocketDetails.pBase, (int)ThisSocketDetails.wSocketNumber);
      return;
    }
  
  _mutex = true;
  
  Connector const* pConnector;
  unsigned Size = (unsigned) apConnector.size();
  for(unsigned i = 0; i < Size; i++)
    {
      pConnector = apConnector[i];
      if (pConnector)
				{  // get the inlet details
					const SocketDetails TheInlet = pConnector->InletConnection;
					BaseShell* pInletBase = TheInlet.pBase;
					if (pInletBase)
            {
							const unsigned wSocketNumber = TheInlet.wSocketNumber;
							pInletBase->DoubleInlet(wSocketNumber, TheDouble); // send to inlet
            }
				}
    }
  
  _mutex = false;
}

bool OutletContainer::DeleteConnectors()
{
  bool Success = true;
  Connector* pCon;
  int Size = apConnector.size();
  for(int i = Size - 1; i >= 0; i--)
    {
      pCon = apConnector[i];;
      Success = Success && pCon->Disconnect(Connector::ByOutlet);
    }
  return Success;
}





