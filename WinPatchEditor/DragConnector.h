//---------------------------------------------------------------------------
#ifndef DragConnectorH
#define DragConnectorH
#include "Typedefs.h"
#include "interfacetypes.h"

class TBaseShellEditForm;
class TObjectSocket;
class PresentationQuestion;

class TDragConnector:public TDragObject
{
public:
    __fastcall TDragConnector(P_CONNECTOR Con, bool ConnectToInlet, PresentationQuestion* engine, TBaseShellEditForm* Creator = NULL);
    __fastcall TDragConnector(P_CONNECTOR Con, bool ConnectToInlet, PresentationQuestion* engine, TObjectSocket* Creator);
    void __fastcall Finished(TObject* Target, int X, int Y, bool Accepted);
    virtual TCursor __fastcall GetDragCursor(bool Accepted, int X, int Y);

    bool CanConnectInlet(P_BASESHELL, unsigned); //can connect to the parameters
    bool CanConnectOutlet(P_BASESHELL, unsigned); //can connect to the parameters
    bool MakeConnection();
    void SetOutlet(P_BASESHELL, unsigned); // sets the OutletConnection
    void SetInlet(P_BASESHELL, unsigned); //ditto for inlet
    bool ValidConnection;
    const bool fConnectingToInlet; // used for dragging
    P_CONNECTOR pCon;
    TBaseShellEditForm* CreatorEditForm;// if created by the edit form
    TObjectSocket* ConnectFromSocket;
    PresentationQuestion* GetCurrentEngine () {return  _current_engine;}
private:
  PresentationQuestion* _current_engine;

};
//---------------------------------------------------------------------------
#endif
