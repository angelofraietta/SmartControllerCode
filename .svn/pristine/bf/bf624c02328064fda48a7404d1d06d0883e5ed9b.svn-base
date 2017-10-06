//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DragLine.h"
#include "GraphicLineFollow.h"
#include "CursorsUnit.h"

#define GRID_SIZE 5 //the gradation for drawing lines
#define IMAGE_STYLE psSolid//psDash

__fastcall TDragLine::TDragLine  (TLineFollow* pLine)
    :pDragLine(pLine), wNumPaints(NULL)
{
    ParentForm = (TForm*)(pLine->Parent);
}

TCursor __fastcall TDragLine::GetDragCursor(bool Accepted, int X, int Y)
{
    if(Accepted)
        return (TCursor)crPlace;
    else
        return crNoDrop;
}

void TDragLine::DoDrag(TPoint DragPoint)
{
    if(wNumPaints)
    {    //remove line
        ParentForm->Canvas->Pen->Mode = pmNotXor;
        ParentForm->Canvas->Pen->Style = IMAGE_STYLE;
        ParentForm->Canvas->MoveTo(tpStartPoint.x, tpStartPoint.y);
        ParentForm->Canvas->LineTo(tpDragPoint.x, tpDragPoint.y);
        ParentForm->Canvas->MoveTo(tpDragPoint.x, tpDragPoint.y);
        ParentForm->Canvas->LineTo(tpEndPoint.x, tpEndPoint.y);
     }
     wNumPaints++;
    //round DragPoint to within grid
    int X_Diff = tpStartPoint.x % GRID_SIZE;
    int Y_Diff = tpStartPoint.y % GRID_SIZE;

    DragPoint.x -= DragPoint.x % GRID_SIZE - X_Diff;
    DragPoint.y -= DragPoint.y % GRID_SIZE - Y_Diff;

    tpDragPoint = DragPoint;

    //draw new line
    ParentForm->Canvas->MoveTo(tpStartPoint.x, tpStartPoint.y);
    ParentForm->Canvas->LineTo(tpDragPoint.x, tpDragPoint.y);
    ParentForm->Canvas->MoveTo(tpDragPoint.x, tpDragPoint.y);
    ParentForm->Canvas->LineTo(tpEndPoint.x, tpEndPoint.y);
    ParentForm->Canvas->Pen->Mode = pmCopy ;

    //tell the pLine the new position
    //pDragLine->tpDragPoint = pDragLine->ScreenToClient(ParentForm->ClientToScreen(tpDragPoint));
}

void __fastcall TDragLine::Finished(TObject* Target, int X, int Y, bool Accepted)
{
    if(Accepted)
        {
        pDragLine->tpDragPoint = pDragLine->ScreenToClient(ParentForm->ClientToScreen(tpDragPoint));
        pDragLine->tpDragEnd = pDragLine->ScreenToClient(ParentForm->ClientToScreen(tpEndPoint));
        pDragLine->CompleteDrag();
        }
    else
        if(!pDragLine->fDragPoint)
            pDragLine->RemovePoint(pDragLine->tpDragRef);
            
    ParentForm->Invalidate();
    pDragLine->fDragPoint = false;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
