//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DragConnector.h"
#include "interfacebridge.h"
#include "CursorsUnit.h"
#include "BaseShellsUnit.h"
#include "ObjectSocket.h"

__fastcall TDragConnector::TDragConnector(P_CONNECTOR Con, bool ConnectToInlet,
            PresentationQuestion* engine, TBaseShellEditForm* Creator)
        :TDragObject(), fConnectingToInlet(ConnectToInlet), ValidConnection(false),
        pCon(Con), CreatorEditForm(Creator), ConnectFromSocket(NULL), _current_engine(engine)
{

}

__fastcall TDragConnector::TDragConnector(P_CONNECTOR Con, bool ConnectToInlet,
            PresentationQuestion* engine, TObjectSocket* Creator)
        :TDragObject(), fConnectingToInlet(ConnectToInlet), ValidConnection(false),
        pCon(Con), CreatorEditForm(NULL), ConnectFromSocket(Creator), _current_engine(engine)
{

}
void __fastcall TDragConnector::Finished(TObject* Target, int X, int Y, bool Accepted)
{
    //a connection was not made
    if(!Accepted)
        ConnectorQuestion::Delete(GetCurrentEngine(), pCon);
    if(CreatorEditForm)
        CreatorEditForm->HideConnectionImages();
}

bool TDragConnector::CanConnectInlet(P_BASESHELL pTestBase, unsigned InletNum)
{
    //Inlet and outlet must share same Parent
    //get inlet base parent
    P_BASESHELL pOutletBase = ConnectorQuestion::GetOutletBase(GetCurrentEngine(), pCon);
    if(!pOutletBase || !pTestBase)
        return false; //must have a base

    P_PATCH OutletParent = IdentityQuestion::GetParent(GetCurrentEngine(), pOutletBase);

    if  (*OutletParent  != *IdentityQuestion::GetParent(GetCurrentEngine(), pTestBase)
        || !OutletParent)
        return false;

	//set the internals
	ConnectorQuestion::SetInletBase(GetCurrentEngine(), pCon, pTestBase);
    ConnectorQuestion::SetInletNum(GetCurrentEngine(), pCon, InletNum);

    //see if connection is possible
	bool CanConnect = BaseShellQuestion::CanConnectInlet(GetCurrentEngine(), pTestBase,InletNum, pCon );

    if(CanConnect)
        return true;
    else
        {
    	ConnectorQuestion::SetInletBase(GetCurrentEngine(), pCon, (DWORD)0);
        return false;
        }
}


TCursor __fastcall TDragConnector::GetDragCursor(bool Accepted, int X, int Y)
{
    if(Accepted)
        {
        if (fConnectingToInlet)
            return (TCursor)crConnectDown;
        else
            return (TCursor)crConnectUp;
        }
    else
        {
        if(fConnectingToInlet)
            return (TCursor)crHoldPlugDown;
        else
            return (TCursor)crHoldPlugUp;
        }
}
bool TDragConnector::CanConnectOutlet(P_BASESHELL pTestBase, unsigned OutletNum)
{
    //Inlet and outlet must share same Parent
    //get inlet base parent
    P_BASESHELL pInletBase = ConnectorQuestion::GetInletBase(GetCurrentEngine(), pCon);
    if(!pInletBase || !pTestBase)
        return false; //must have a base

    P_PATCH InletParent = IdentityQuestion::GetParent(GetCurrentEngine(), pInletBase);

    if  (*InletParent  != *IdentityQuestion::GetParent(GetCurrentEngine(), pTestBase)
        || !InletParent)
        return false;

	//set the internals
	ConnectorQuestion::SetOutletBase(GetCurrentEngine(), pCon, pTestBase);
    ConnectorQuestion::SetOutletNum(GetCurrentEngine(), pCon, OutletNum);

    //see if connection is possible
	bool CanConnect = BaseShellQuestion::CanConnectOutlet(GetCurrentEngine(), pTestBase,OutletNum, pCon );

    if(CanConnect)
        return true;
    else
        {
    	ConnectorQuestion::SetOutletBase(GetCurrentEngine(), pCon, (DWORD)0);
        return false;
        }

}

void TDragConnector::SetOutlet(P_BASESHELL pBase, unsigned OutletNum)
{
    if (ValidConnection)
        return;
	//set internals
	ConnectorQuestion::SetOutletBase(GetCurrentEngine(), pCon, pBase);
    ConnectorQuestion::SetOutletNum(GetCurrentEngine(), pCon, OutletNum);
}


void TDragConnector::SetInlet(P_BASESHELL pBase, unsigned InletNum)
{
    if(ValidConnection)
        return;
	//set internals
	ConnectorQuestion::SetInletBase(GetCurrentEngine(), pCon, pBase);
    ConnectorQuestion::SetInletNum(GetCurrentEngine(), pCon, InletNum);
}

bool TDragConnector::MakeConnection()
{
    //make the connection
   ValidConnection = ConnectorQuestion::MakeConnection(GetCurrentEngine(), pCon);
    //set the parent
    P_PATCH pParent = IdentityQuestion::GetParent(GetCurrentEngine(), ConnectorQuestion::GetOutletBase(GetCurrentEngine(), pCon));
    IdentityQuestion::SetParent(GetCurrentEngine(), pCon, pParent);
    //Add to ConnectorList in Patch
    PatchQuestion::AddConnector(GetCurrentEngine(), pParent,pCon);
    return ValidConnection;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
