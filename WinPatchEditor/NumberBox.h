//---------------------------------------------------------------------------
#ifndef NumberBoxH
#define NumberBoxH
#include "ObjectBox.h"
class TNumberBoxWindow;

class TNumberBox:public TObjectBox
{
friend class TNumberBoxWindow;
public:
   enum {nbNone, nbNumber, nbNoteName, nbVSlider, nbHSlider, nbGuage};
   __fastcall TNumberBox(TBaseShellHook* Owner, TViewForm* pParent);
   __fastcall ~TNumberBox();
   void DisplayControl(bool Display = true);
   void ChangeType(int DisplayType);
   static TObjectBox* Create(TBaseShellHook* Owner, TViewForm* pParent);

   //over-ridden base methods
    bool HasControls()const {return true;}
    void UpdateDisplay();
    void DisplayControl();
    bool ControlDisplayed()const {return (pWindowDisplay);}
    int GetNumber();
    int GetUpperLimit();
    int GetLowerLimit();
    void SetNumber(int new_val);

    TPopupMenu* BoxDisplayMenu;    

protected:
   TNumberBoxWindow* pWindowDisplay;//a display for this type
   bool fIsDragging;

   void __fastcall MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall ChildMouseUp(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall DoStartDrag(TDragObject *&DragObject);
   void __fastcall DoEndDrag(TObject *Source, int X, int Y);
};
//---------------------------------------------------------------------------
#endif
