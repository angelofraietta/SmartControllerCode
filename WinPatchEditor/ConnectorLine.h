//---------------------------------------------------------------------------
#ifndef ConnectorLineH
#define ConnectorLineH

#include "GraphicLineFollow.h"
#include "TypeDefs.h"
#include "interfacetypes.h"
//---------------------------------------------------------------------------


class TViewForm;
class TConnectorHook;
class PresentationQuestion;
class TPatchForm;

class TConnectorLine :public TLineFollow
{
friend class TViewForm;
public:
    __fastcall TConnectorLine(TConnectorHook* Owner, TViewForm* pParent);
    __fastcall ~TConnectorLine();
    void AutoArrange();
    P_CONNECTOR GetObject()const {return pObject;}
    TConnectorHook* GetHook();
    void Detach();
    const std::vector<TPoint>*const GetPoints()const;
    void StorePoints(const std::vector<TPoint>*const NewPoints);
    bool NormallyVisible;
    virtual void DisplayMouseMove (bool);
protected:
    P_CONNECTOR pObject;
    TViewForm* pParentForm;
    void __fastcall MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall DoStartDrag(TDragObject *&DragObject);
    void __fastcall DragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept);
    void __fastcall DragDrop(TObject *Source, int X, int Y);
    TPopupMenu* ConnectorPopup;
   PresentationQuestion* GetCurrentEngine ();
   TPatchForm* GetPatchForm();
};

#endif
