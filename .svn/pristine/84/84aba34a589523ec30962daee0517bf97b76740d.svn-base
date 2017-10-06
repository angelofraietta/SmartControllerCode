//---------------------------------------------------------------------------
#ifndef GraphicShapeH
#define GraphicShapeH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#define MIN_SHAPE_HEIGHT 20
#define MIN_SHAPE_WIDTH 20 
enum TGraphicControlType {gctRectangle, gctCircle};
//---------------------------------------------------------------------------
class TGraphicShape : public TGraphicControl
{
private:
    TGraphicControlType FShape;
    void __fastcall SetShape(TGraphicControlType Value);
    void __fastcall SetPen(TPen* Value);
    void __fastcall SetBrush(TBrush* Value);
    TPen* FPen;
    TBrush* FBrush;
protected:
    virtual void __fastcall Paint();
public:
    __fastcall TGraphicShape(TComponent* Owner);
    __fastcall ~TGraphicShape();
    void __fastcall StyleChanged(TObject* Owner);
__published:
    __property Height;
    __property Width;
    __property TBrush* Brush = {read=FBrush, write=SetBrush, nodefault};
    __property TPen* Pen = {read=FPen, write=SetPen, nodefault};
    __property TGraphicControlType Shape = {read=FShape, write=SetShape, nodefault};
    __property DragCursor;
    __property DragMode;
    __property OnDragDrop;
    __property OnDragOver;
    __property OnStartDrag;
    __property OnEndDrag;
    __property OnMouseDown;
    __property OnMouseMove;
    __property OnMouseUp;
};
//---------------------------------------------------------------------------
#endif
