//---------------------------------------------------------------------------
#ifndef PerformanceViewH
#define PerformanceViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ToolWin.hpp>
#include <vector>
#include "TypeDefs.h"
#include "ShellDisplayParam.h"
#include <fstream>

class TObjectBox;
class TConnectorLine;
class TViewForm;
class TBaseShellHook;
class PresentationQuestion;

class TPerformanceView :public TComponent
{
friend class TViewForm;
public:
    __fastcall TPerformanceView(TBaseShellHook* Owner);
    bool __fastcall CanAdd (P_BASESHELL);
    bool __fastcall AddObject(P_BASESHELL);
    bool __fastcall AddConnector(P_CONNECTOR);
    void RemoveObject(P_BASESHELL);
    void RemoveConnector(P_CONNECTOR);
    void RemoveComment(TComment*);
    void __fastcall Display();

    void Add (const ShellDisplayParam& NewObject);
    void Add (const LineDisplayParam& NewConnector);
    void Add (const CommentDisplayParam& NewComment);

    void SetViewNode(TTreeNode* Node){pViewNode = Node;}
    TTreeNode* GetNode() {return pViewNode;}
    void SetViewForm(TViewForm* F) {pViewForm = F;}
    void ClearView();
    TPatchForm* GetPatchForm();
    const String& GetViewName()const {return ViewName;}
    void SetViewName(const String& Name);
    //ofstream& Save(ofstream& OutFile);
    //ifstream& Restore(ifstream& InFile, int FileType);
    void SaveView();
    TViewForm* GetViewForm() {return pViewForm;}
    TTreeNode* GetViewNode() {return pViewNode;}
    int StateIndex; //the index in the tree view
    static const char* szStartViewId;
    static const char* szStartConId;
    static const char* szStartCommentId;
    static const char* szEndViewId;
    PresentationQuestion* GetCurrentEngine ();
    void DeInitialise() {initialised = false;}
protected:
    std::vector<ShellDisplayParam> ObjectsList;
    std::vector<LineDisplayParam> ConnectorsList;
    std::vector<CommentDisplayParam> CommentList;
    TViewForm* pViewForm;
    TTreeNode* pViewNode;
    String ViewName;
    bool initialised;
};

#endif
