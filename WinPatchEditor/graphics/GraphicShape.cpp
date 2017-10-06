//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GraphicShape.h"
#pragma package(smart_init)
#define TEXT_BORDER 2
#define DEFAULT_SHAPE_WIDTH 50
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TGraphicShape *)
{
    new TGraphicShape(NULL);
}
//---------------------------------------------------------------------------
__fastcall TGraphicShape::TGraphicShape(TComponent* Owner)
    : TGraphicControl(Owner)
{
    Height = MIN_SHAPE_HEIGHT;
    Width = DEFAULT_SHAPE_WIDTH;
    FBrush = new TBrush();
    FBrush->OnChange = StyleChanged;
    FPen = new TPen();
    FPen->OnChange = StyleChanged;

}

__fastcall TGraphicShape::~TGraphicShape()
{
    delete FBrush;
    delete FPen;
}

void __fastcall TGraphicShape::SetShape (TGraphicControlType Value)
{
    if(FShape != Value)
        {
        FShape = Value;
        Invalidate();
        }
}

void __fastcall TGraphicShape::StyleChanged (TObject* Sender)
{
    Invalidate();
}

void __fastcall TGraphicShape::SetPen (TPen* Value)
{
    FPen->Assign(Value);
}

void __fastcall TGraphicShape::SetBrush (TBrush* Value)
{
    FBrush->Assign(Value);
}

void __fastcall TGraphicShape::Paint()
{
    int X,Y,W,H;
    Canvas->Pen = FPen;
    Canvas->Brush = FBrush;
    W=Width;
    H=Height;
    X=Y=0;


    switch(FShape)
    {
        case gctRectangle:
            Canvas->Rectangle(X,Y,X+W,Y+H);
            Canvas->TextOut(TEXT_BORDER, TEXT_BORDER , Text);
            break;
        case gctCircle:
            Canvas->Ellipse(X,Y,X+W, Y+H);
            break;
        default:
            break;
    }

}
//---------------------------------------------------------------------------
namespace Graphicshape
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TGraphicShape)};
        RegisterComponents("Samples", classes, 0);
    }
}
//---------------------------------------------------------------------------
 