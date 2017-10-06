//---------------------------------------------------------------------------
#ifndef GraphicLineFollowH
#define GraphicLineFollowH

#include "GraphicLine.h"
class TGraphicBoxFollow;

class TLineFollow:public TGraphicLine
{
public:
    __fastcall TLineFollow(TComponent* Owner, TForm* Parent);
    __fastcall ~TLineFollow();


   void  __fastcall Follow(bool);
   void __fastcall StartLeader(TGraphicBoxFollow*);
   void __fastcall EndLeader(TGraphicBoxFollow*);
   void __fastcall MouseMove(TShiftState Shift, int X, int Y);
   void __fastcall DoEndDrag(TObject *Source, int X, int Y);
   void __fastcall RemoveLeader(TGraphicBoxFollow*);
   bool IsOverAndAtFront(int X, int Y);
protected:
    void __fastcall MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall ProcessSelect(TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall DoStartDrag(TDragObject *&DragObject);
    void __fastcall DragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept);
    void __fastcall GraphicDragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept);
    virtual void DisplayMouseMove (bool f) {}    
    TGraphicBoxFollow* pStartLeader, *pEndLeader;//start and fininsh ponts of line
    bool fIsOver;
    static TLineFollow* pFocusedControl;//  Points to the control that has focus
};
//---------------------------------------------------------------------------
#endif
