//---------------------------------------------------------------------------
#ifndef ObjectSocketH
#define ObjectSocketH
#include "GraphicBoxFollow.h"
#include "ObjectBox.h"
class TPatchForm;
class TViewForm;
class PresentationQuestion;

class TObjectSocket:public TGraphicBoxFollow
{
friend class TObjectBox;
friend class TViewForm;
public:
    __fastcall TObjectSocket(TObjectBox* Owner, unsigned SocketNum, bool IsInlet);
    TPatchForm* GetPatchForm();
    String GetSocketDetails();
    P_BASESHELL pObject;
    PresentationQuestion* GetCurrentEngine ();
protected:
    bool fIsInlet;
    unsigned wSocketNumber;
    void __fastcall DragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept);
    void __fastcall DoStartDrag(TDragObject *&DragObject);
    void __fastcall DragDrop(TObject *Source, int X, int Y);
    void __fastcall MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y);    
    void ShowConnectors(bool ShowObjects);
    TViewForm* pParentForm;
    TPopupMenu* SocketPopup;    
};
//---------------------------------------------------------------------------
#endif
 