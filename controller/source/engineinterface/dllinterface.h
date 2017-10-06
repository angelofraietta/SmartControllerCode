#ifndef DLL_INTERFACE_BRIDGE_H
#define  DLL_INTERFACE_BRIDGE_H

#ifdef __cplusplus
extern "C" {            // Assume C declarations for C++
#endif

/*********************************************************************
Common Interface functions
**********************************************************************/
// Conversion of MIDI
 void   NumberToMidi(unsigned NumVal, LPSTR Buf);
 bool   MidiToNumber(LPSTR szNoteName, int* Result);

//Error Interface
   /* bool   GetErrorMessage(LPSTR Buf);
    void   SetErrorWindow(SC_QID hWnd);
    bool   GetErrorMessage32(LPSTR Buf);
    void   SetErrorWindow32(SC_QID hWnd);
     */
//all remaining functions assume the first argument is a valid
//if it is a pointer represenatation

/****************************************************************
Connector class access functions
****************************************************************/
//test if full connection exists
    bool   ConnectorIsValid(P_CONNECTOR dwpCon);

//find out about Connector
    P_BASESHELL   ConnectorGetInletBase(P_CONNECTOR dwpCon);
    unsigned   ConnectorGetInletNum(P_CONNECTOR dwpCon);
    P_BASESHELL   ConnectorGetOutletBase(P_CONNECTOR dwpCon);
    unsigned   ConnectorGetOutletNum(P_CONNECTOR dwpCon);

//find position in Outlet
    unsigned   ConnectorGetOutletIndex(P_CONNECTOR dwpCon);

    P_PATCH   ConnectorGetParent(P_CONNECTOR dwpCon);

//use for testing acceptability of connector
//does not actually connect to the BaseShell
    void   ConnectorSetInletBase(P_CONNECTOR dwpCon, P_BASESHELL dwpShell);
    void   ConnectorSetInletNum(P_CONNECTOR dwpCon, unsigned wSocketNum);
    void   ConnectorSetOutletBase(P_CONNECTOR dwpCon, P_BASESHELL dwpShell);
    void   ConnectorSetOutletNum(P_CONNECTOR dwpCon, unsigned wSocketNum);

//complete connection.
    bool   ConnectorMakeConnection(P_CONNECTOR dwpCon);
    void   ConnectorSetParent(P_CONNECTOR dwpCon, P_PATCH dwpParent);

    P_CONNECTOR   ConnectorCreate();
    void   ConnectorDelete(P_CONNECTOR dwpCon);

    bool   ConnectorCanSave(P_CONNECTOR dwpCon);

/**********************************************************************************
*   Patch Class access functions
**********************************************************************************/
//assumes dwpShell exists in this patch
    void   PatchDetachBaseShell(P_PATCH dwpPatch, P_BASESHELL dwpShell);
    unsigned   PatchFindBaseShellPosition(P_PATCH dwpPatch, P_BASESHELL dwpShell);

    void   PatchAddBaseShell(P_PATCH dwpPatch, P_BASESHELL dwpShell);

    unsigned   PatchNumberBaseShells(P_PATCH dwpPatch);
//assumes a valid index
    P_BASESHELL   PatchFindBaseShell(P_PATCH dwpPatch, unsigned Index);

//causes Connector to become deleted from memory
    void   PatchDetachConnector(P_PATCH dwpPatch, P_CONNECTOR dwpCon);

//call after completeing a connection
    void   PatchAddConnector(P_PATCH dwpPatch, P_CONNECTOR dwpCon);

    unsigned   PatchNumberConnectors(P_PATCH dwpPatch);
//assumes a valid index
    P_CONNECTOR   PatchFindConnector(P_PATCH dwpPatch, unsigned Index);

//call after deleting any BaseShells to see if any Connectors were also deleted
    P_CONNECTOR   PatchGetDeadConnector(P_PATCH dwpPatch);

//same as BaseShellCreate for Patch Inlets and Outlets
    P_BASESHELL   PatchAddInlet(P_PATCH dwpPatch);
    P_BASESHELL   PatchAddOutlet(P_PATCH dwpPatch);
    P_PATCH   PatchMakeNew(LPSTR Name);

//streaming
    void   PatchSetFileName(P_PATCH dwpPatch, LPSTR FileName);
    P_PATCH   PatchLoadPatchFile(LPSTR FileName, P_PATCH dwpParent);
    void   PatchGetFileName(P_PATCH dwpPatch, LPSTR FileName);
    bool   PatchSave(P_PATCH dwpPatch, LPSTR FileName);
    void   PatchDelete(P_PATCH dwpPatch);
    void   PatchSetNumViews(P_PATCH dwpPatch, unsigned NumViews);
    unsigned   PatchGetNumViews(P_PATCH dwpPatch);

//alter the ordering of inlets and outlets
    void   PatchSwapOutlets(P_PATCH dwpPatch, unsigned Outlet1, unsigned Outlet2);
    void   PatchSwapInlets(P_PATCH dwpPatch, unsigned Inlet1, unsigned Inlet2);

    P_BASESHELL   PatchGetInlet(P_PATCH dwpPatch, unsigned SocketNum);
    P_BASESHELL   PatchGetOutlet(P_PATCH dwpPatch, unsigned SocketNum);

    unsigned   PatchOutletGetOutletNumber(P_BASESHELL dwpPort);
    unsigned   PatchInletGetInletNumber(P_BASESHELL dwpPort);


#ifdef __cplusplus
}            // end C declarations for C++
#endif

#endif
