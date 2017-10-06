//---------------------------------------------------------------------------
#ifndef GraphicLineH
#define GraphicLineH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <vector>


class LinePointPriority{
    public:
        bool operator()(const TPoint& a, const TPoint& b)
            {return a.x > b.x && a.y > b.y;}
};

class LinePointEquals{
    public:
        bool operator()(const TPoint& a, const TPoint& b)
            {return a.x == b.x && a.y == b.y;}
};

class TDragLine; //forawrd dec
//---------------------------------------------------------------------------
class PACKAGE TGraphicLine : public TGraphicControl
{
friend class TDragLine;
private:
    bool fDisplayPoints;
protected:
    TPen* FPen;
    TBrush* FBrush;
    void __fastcall SetPen(TPen* Value);
    void __fastcall SetBrush(TBrush* Value);
    virtual void __fastcall Paint();
    std::vector<TPoint> LinePoints, PrevLinePoints;
    TPoint* pDragPoint, *pDragEnd;
    TPoint tpDragRef, tpDragStart, tpDragEnd, tpDragPoint; 
    bool fDragPoint;
    unsigned wDragIndex;

    TPoint StartPoint, EndPoint;//these must have a fixed address. Position relative to control
    TPoint ParentStartPoint, ParentEndPoint; //absolute draw start positions from leaders
    bool __fastcall ScanPoint(const TPoint& Test, unsigned Thresh); //detrmines whethe the point is on this line

    TPoint* __fastcall GetPoint(TPoint& Test, unsigned Thresh); //detrmines whethe the point is on this line
    TPoint GetControlPointPos(unsigned Index); //of LinePoints
    void AdjustLineArea();
    void CompleteDrag();
public:
    static bool fRemovePoint; //selecting with flag set removes point
    __fastcall TGraphicLine(TComponent* Owner);
    __fastcall ~TGraphicLine();
    void __fastcall StyleChanged(TObject* Owner);
    TPoint* __fastcall AddPoint(TPoint Position, unsigned Thresh);
    void __fastcall RemovePoint(TPoint Value);
    TColor LineColor;
    virtual bool __fastcall DragPoint(TPoint);
    void __fastcall DragPaint();
    void __fastcall DisplayHandles(bool);
    void __fastcall MarkDragPoint();

__published:
    __property Width;
    __property TBrush* Brush = {read=FBrush, write=SetBrush, nodefault};
    __property TPen* Pen = {read=FPen, write=SetPen, nodefault};
    __property DragCursor;
    __property DragMode;
    __property OnDragOver;
    __property OnStartDrag;
    __property OnEndDrag;
    __property OnMouseDown;
    __property OnMouseMove;
    __property OnMouseUp;
};
//---------------------------------------------------------------------------
#endif
