//---------------------------------------------------------------------------
#ifndef GraphicBoxUnitH
#define GraphicBoxUnitH
#include "GraphicShape.h"
#include <vector>

class TGraphicBoxFollow; //follow this

//---------------------------------------------------------------------------
class TGraphicControlBox:public TGraphicShape{
public:
    __fastcall TGraphicControlBox(TComponent* Owner);
    TGraphicBoxFollow* AddFollower(bool IsTop);
    void AddFollower(TGraphicBoxFollow* Follower, bool IsTop);
    void __fastcall RemoveFollower(bool IsTop);
    void __fastcall ShowObject(bool ShowObject);

    void AdjustMinWidth();//if adding or removing followers
    TGraphicBoxFollow* GetFollower(unsigned FollowerNum, bool IsTop);

    void __fastcall NotifyFollowers(bool Finished); //notify follwers that an event is happening
    TPoint __fastcall GetOffset(unsigned FollowerNum, bool IsTop)const;
    TPoint GetPosition()const;
    void __fastcall ProcessDrag(int X, int Y);
    static void AllowResize (bool f) {m_allow_resize = f;}
    static bool AllowResize (){return m_allow_resize;}
protected:
    void __fastcall MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall MouseMove(TShiftState Shift, int X, int Y);
//    void __fastcall DoStartDrag(TDragObject *&DragObject);
    void __fastcall DragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept);
    void __fastcall DoEndDrag(TObject *Source, int X, int Y);

    std::vector<TGraphicBoxFollow*> TopFollowers, BottomFollowers;
    unsigned wMinWidth, wMinHeight;
    bool fResize; //if the object is resizing

    static bool m_allow_resize;
    };
#endif
