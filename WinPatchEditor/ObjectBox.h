//---------------------------------------------------------------------------
#ifndef ObjectBoxH
#define ObjectBoxH
#include "GraphicBoxUnit.h"
#include "IdentityHook.h"
#include "ShellDisplayParam.h"

class TViewForm;
class TObjectSocket;
class PresentationQuestion;

class TObjectBox :public TGraphicControlBox
{
friend class TViewForm;
friend class TObjectSocket;
public:
enum {dtObjectBox, dtView};//DragTypes
enum {OutletFollow, InletFollow};
    __fastcall TObjectBox(TBaseShellHook* Owner, TViewForm* pParent);
    __fastcall ~TObjectBox();

    void __fastcall Detach(); //from View form
    P_BASESHELL GetObject()const {return pObject;}
    TBaseShellHook* GetHook();
    TPatchForm* GetPatchForm();
    TViewForm* GetViewForm() {return pParentForm;}
    bool NormallyVisible;
    void PlaceObject(int X, int Y);
    //virtual functions that can be over-ridden
    //for ObjectBox descendants
    virtual bool HasControls()const {return false;}
    virtual bool ControlDisplayed()const {return false;}
    virtual void UpdateDisplay();
    virtual void DisplayControl(bool Display = true){};
    unsigned DragType; //used to define what type ofDrag Operation
    inline int HelpContext () const {return m_help_context;}

    PresentationQuestion* GetCurrentEngine ();

    void Send();
protected:

    P_BASESHELL pObject;
    TViewForm* pParentForm;
    ShellDisplayParam DisplayParams; // this is Form independent
    void __fastcall MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall DoStartDrag(TDragObject *&DragObject);
    void __fastcall DoEndDrag(TObject *Source, int X, int Y);
    TPopupMenu* ObjectPopup;
    int m_help_context;
};

//---------------------------------------------------------------------------
#endif
