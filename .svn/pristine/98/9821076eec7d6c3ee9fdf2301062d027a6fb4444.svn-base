//---------------------------------------------------------------------------
#ifndef IdentityHookH
#define IdentityHookH

#include "TypeElementUnit.h"

#include "PatchUnit.h"
#include "interfacebridge.h"

class TPatchForm;
class TConnectorEditForm;
class TBaseShellEditForm;
class PresentationQuestion;

//---------------------------------------------------------------------------

// allows BaseShell class to associate with Builder
class TBaseShellHook:public TComponent
{
friend class TPatchForm;
public:
	TBaseShellHook (TPatchForm* owner, P_BASESHELL Hook);
    __fastcall ~TBaseShellHook();
   	P_BASESHELL GetHook();
    TPatchForm* GetPatchForm();

    //BaseShell access
   	void SetHookName(String);
   	void SetComment(String);
   	const String& GetName();
   	String GetComment();
   	String GetType()const {return m_type;}
    String GetHint();
    void Reset();


   	void DisplayEditForm();
   	void ClearEditForm();
    void SetViewNode(TTreeNode*);
    void Update(); // updates all references to this name
    void DeleteHook();
    TTreeNode* GetNode();
    bool operator< (TBaseShellHook&);
    void Delete();
    int StateIndex; //the index in the tree view

    static bool KillObject(TBaseShellHook* Victim);

    inline int HelpContext () {return m_help_Context;}
    PresentationQuestion* GetCurrentEngine ();
private:
	P_BASESHELL pHook;
  TPatchForm* _owner;
   	TBaseShellEditForm* pEditForm;
    TTreeNode* ViewNode; // points to the node in the owners tree View
    static CreateFormMapType EditFormMap;
    String sHookName;
    void GetHookName();
    int m_help_Context;
    String m_type;
};

//-----------------------------------------------------------------
class TConnectorHook:public TComponent
{

public:

	TConnectorHook (TPatchForm* owner, P_CONNECTOR Hook);
    __fastcall ~TConnectorHook();
   	P_CONNECTOR GetHook();
    bool fConnectingToInlet; // used for dragging

   	void SetHookName(String);
   	void SetComment(String);
   	String GetName();
   	String GetComment();
    String GetHint();

   	void DisplayEditForm();
   	void ClearEditForm();
    void SetViewNode(TTreeNode*);
    void UpdateObject(); // updates all references to this name
    void DeleteHook();
    void DisplayOutlet();
    void DisplayInlet();
    TTreeNode* GetNode();
    bool operator < (TConnectorHook&);

	// used to test possible connections
    bool CanConnectInlet(P_BASESHELL, unsigned); //can connect to the parameters
    bool CanConnectOutlet(P_BASESHELL, unsigned); //can connect to the parameters
    bool MakeConnection();
    void SetOutlet(P_BASESHELL, unsigned); // sets the OutletConnection
    void SetInlet(P_BASESHELL, unsigned); //ditto for inlet
    TPatchForm* GetPatchForm()const;
    void Delete();
    int StateIndex; //the index in the tree view
    static bool KillObject(TConnectorHook* Victim);
    unsigned OutletIndex () ;
    inline int HelpContext () {return m_help_Context;}
    PresentationQuestion* GetCurrentEngine ();
    TPatchForm* GetPatchForm();
private:
    TPatchForm* _owner;
	  P_CONNECTOR pHook;
   	TConnectorEditForm* pEditForm;
    TTreeNode* ViewNode; // points to the node in the owners tree View
    unsigned m_outlet_index;
    bool ValidConnection;
    int m_help_Context;
};


#endif
