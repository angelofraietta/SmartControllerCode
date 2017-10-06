//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GraphicLine.h"
#include <math>
#include <algorithm>
#include "CommonFunctions.h"


#pragma package(smart_init)

#define POINT_SIZE 2 //size of displayed points in pixels
#define MARK "X"//use to mark drag point
#define HANDLE_WIDTH 2
#define BOUND_SIZE 10 //the boundary around control draw area

bool ScanLine(TPoint, TPoint, TPoint,unsigned);

double GetDistance(TPoint, TPoint);

bool ComparePoint(const TPoint&, const TPoint&, unsigned);
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TGraphicLine *)
{
    new TGraphicLine(NULL);
}
bool TGraphicLine::fRemovePoint = false;
//---------------------------------------------------------------------------
__fastcall TGraphicLine::TGraphicLine(TComponent* Owner)
    : TGraphicControl(Owner), fDisplayPoints(false), pDragPoint(NULL),fDragPoint(false),
    LineColor(clBlack), pDragEnd(NULL)
{
    FBrush = new TBrush();
    FBrush->OnChange = StyleChanged;
    FPen = new TPen();
    FPen->OnChange = StyleChanged;
    ParentStartPoint.x = 100; ParentStartPoint.y = 100;
    ParentEndPoint.x = 100; ParentEndPoint.y = 100;
}

__fastcall TGraphicLine::~TGraphicLine()
{
    delete FBrush;
    delete FPen;
}


void __fastcall TGraphicLine::StyleChanged (TObject* Sender)
{
    Invalidate();
}

void __fastcall TGraphicLine::SetPen (TPen* Value)
{
    FPen->Assign(Value);
}

void __fastcall TGraphicLine::SetBrush (TBrush* Value)
{
    FBrush->Assign(Value);
}

void TGraphicLine::AdjustLineArea()
{
    Align = alNone;

    TRect DrawArea;
    TPoint Cursor;

    Cursor.x = ParentStartPoint.x; Cursor.y = ParentStartPoint.y;
//    Cursor = AlignPoint(StartPoint, this);
    DrawArea.Top =  Cursor.y;
    DrawArea.Bottom = Cursor.y;
    DrawArea.Left = Cursor.x;
    DrawArea.Right = Cursor.x;
    for(unsigned i = 0; i < LinePoints.size(); i++)
        {
        Cursor.x += LinePoints[i].x;
        Cursor.y += LinePoints[i].y;
        GetControlPointPos(i);
        if(Cursor.x <= DrawArea.Left)
            DrawArea.Left = Cursor.x;
        if(Cursor.x >= DrawArea.Right)
            DrawArea.Right = Cursor.x;

        if(Cursor.y <= DrawArea.Top)
            DrawArea.Top = Cursor.y;
        if(Cursor.y >= DrawArea.Bottom)
            DrawArea.Bottom = Cursor.y;
        }
        //now bottom
    Cursor.x = ParentEndPoint.x; Cursor.y = ParentEndPoint.y;
//    Cursor = AlignPoint(EndPoint, this);
    if(Cursor.x <= DrawArea.Left)
        DrawArea.Left = Cursor.x;
    if(Cursor.x >= DrawArea.Right)
        DrawArea.Right = Cursor.x;

    if(Cursor.y <= DrawArea.Top)
        DrawArea.Top = Cursor.y;
    if(Cursor.y >= DrawArea.Bottom)
        DrawArea.Bottom = Cursor.y;


    Left = DrawArea.Left - BOUND_SIZE;
    Width = DrawArea.Right - DrawArea.Left + BOUND_SIZE * 2;
    Top = DrawArea.Top - BOUND_SIZE;
    Height = DrawArea.Bottom - DrawArea.Top + BOUND_SIZE * 2;

    StartPoint.x = ParentStartPoint.x - Left;
    StartPoint.y = ParentStartPoint.y - Top;

    EndPoint.x = ParentEndPoint.x - Left;
    EndPoint.y = ParentEndPoint.y - Top;

    Left = Left -((TScrollingWinControl*)Parent)->HorzScrollBar->Position;
    Top = Top -((TScrollingWinControl*)Parent)->VertScrollBar->Position;



}

void __fastcall TGraphicLine::Paint()
{
    std::vector<TPoint> OldPoints;//will store these lines
    Canvas->Pen = FPen;
    Canvas->Pen->Color = LineColor;
    if(fDisplayPoints)
        Canvas->Pen->Width = HANDLE_WIDTH;
    TPoint Cursor = StartPoint;
//    Cursor = AlignPoint(Cursor, this);
    Canvas->MoveTo(Cursor.x, Cursor.y);
    OldPoints.push_back(StartPoint);
    for(unsigned i = 0; i < LinePoints.size(); i++)
        {
        Cursor.x += LinePoints[i].x;
        Cursor.y += LinePoints[i].y;
        Canvas->LineTo(Cursor.x, Cursor.y);//draw to next
        OldPoints.push_back(LinePoints[i]);          //and store position

        if(fDisplayPoints && i <  LinePoints.size())    //display handles
            {
            int PenWidth = Canvas->Pen->Width;
            Canvas->Pen->Width = POINT_SIZE;//make thicker
            Canvas->Rectangle(Cursor.x - POINT_SIZE,
                              Cursor.y - POINT_SIZE,
                              Cursor.x + POINT_SIZE,
                              Cursor.y + POINT_SIZE);
            Canvas->Pen->Width = PenWidth; //return to normal
            }

        Canvas->MoveTo(Cursor.x , Cursor.y);
        }
    Cursor = EndPoint;
  //  Cursor = AlignPoint(Cursor, this);
    Canvas->LineTo(Cursor.x, Cursor.y);
    OldPoints.push_back(EndPoint);          //and store position

    PrevLinePoints = OldPoints;
}

void __fastcall TGraphicLine::DragPaint()
{
    if(!Visible)
        return;
    //first paint over old lines
    Canvas->Pen->Mode = pmNotXor;
    if(fDisplayPoints)
        Canvas->Pen->Width = HANDLE_WIDTH;
    TPoint Cursor;
    for(unsigned i = 1; i < PrevLinePoints.size(); i++)
        {
        Canvas->MoveTo(Cursor.x,Cursor.y);

        Canvas->LineTo(Cursor.x, Cursor.y);//draw to next

        if(fDisplayPoints && i <  PrevLinePoints.size() -1)    //display handles
            {
            int PenWidth = Canvas->Pen->Width;
            Canvas->Pen->Width = POINT_SIZE;//make thicker
            Canvas->Rectangle(Cursor.x - POINT_SIZE,
                              Cursor.y - POINT_SIZE,
                              Cursor.x + POINT_SIZE,
                              Cursor.y + POINT_SIZE);
            Canvas->Pen->Width = PenWidth; //return to normal
            }
        }
    //now draw new lines
    AdjustLineArea();
    std::vector<TPoint> OldPoints;//will store these lines
    Cursor = StartPoint;
    Canvas->MoveTo(Cursor.x, Cursor.y);
    OldPoints.push_back(StartPoint);
    for(unsigned i = 0; i < LinePoints.size(); i++)
        {
        Cursor.x += LinePoints[i].x;
        Cursor.y += LinePoints[i].y;

        Canvas->LineTo(Cursor.x, Cursor.y);//draw to next
        OldPoints.push_back(LinePoints[i]);          //and store position

        if(fDisplayPoints && i <  LinePoints.size())    //display handles
            {
            int PenWidth = Canvas->Pen->Width;
            Canvas->Pen->Width = POINT_SIZE;//make thicker
            Canvas->Rectangle(Cursor.x - POINT_SIZE,
                              Cursor.y - POINT_SIZE,
                              Cursor.x + POINT_SIZE,
                              Cursor.y + POINT_SIZE);
            Canvas->Pen->Width = PenWidth; //return to normal
            }
        Canvas->MoveTo(Cursor.x , Cursor.y);
        }
    Cursor = EndPoint;
    Canvas->LineTo(Cursor.x, Cursor.y);
    OldPoints.push_back(EndPoint);          //and store position

    PrevLinePoints = OldPoints;
    Canvas->Pen->Mode = pmCopy;
}


TPoint* __fastcall TGraphicLine::AddPoint(TPoint Position, unsigned Tol)
{
    //find where to position the point
    bool Found = false;
    TPoint StartScan = StartPoint;
    TPoint EndScan = StartScan;
    for (unsigned i = 0; i < LinePoints.size()&&!Found; i++)
        {
        EndScan.x += LinePoints[i].x;
        EndScan.y += LinePoints[i].y;
        Found = ScanLine(StartScan, EndScan, Position,Tol);
        if(Found)
            {
            tpDragStart = StartScan;
            tpDragEnd = EndScan;
            pDragEnd = & LinePoints[i];
            //convert to relative position
            TPoint tpDiff;
            tpDiff.x = Position.x - StartScan.x;
            tpDiff.y = Position.y - StartScan.y;
            //store the position
            tpDragRef.x = Position.x;
            tpDragRef.y = Position.y;


            Position.x -= StartScan.x;
            Position.y -= StartScan.y;

            //subtract the amount added to point
            LinePoints[i].x -= tpDiff.x;
            LinePoints[i].y -= tpDiff.y;

            LinePoints.insert(&LinePoints[i],Position);//insert here
            pDragPoint = &LinePoints[i];  //and set drag point
            fDragPoint = true;
            }
        else
            StartScan = EndScan;
        }
    if(!Found)// Place at end
        {
        //store the position
        tpDragRef.x = Position.x;
        tpDragRef.y = Position.y;

        Position.x -= StartScan.x;
        Position.y -= StartScan.y;

        LinePoints.push_back(Position);
        pDragPoint = &LinePoints[LinePoints.size() - 1];
        tpDragStart = StartScan;
        tpDragEnd = EndPoint;
        pDragEnd = NULL;
        }
    return pDragPoint;
}

void __fastcall TGraphicLine::RemovePoint(TPoint ThePoint)
{
    bool Found = false;
    for(unsigned i = 0; i < LinePoints.size() && !Found; i++)
        if(ThePoint.x == LinePoints[i].x &&
            ThePoint.y == LinePoints[i].y)
            {
            Found = true;
            if(&LinePoints[i] == pDragPoint)
                fDragPoint = NULL;
            //adjust relative position of next Point
            if(LinePoints.size() >= i)
                {
                LinePoints[i+1].x += LinePoints[i].x;
                LinePoints[i+1].y += LinePoints[i].y;                
                }
            LinePoints.erase(&LinePoints[i]);
            }
}

bool __fastcall TGraphicLine::DragPoint(TPoint Position)
{
    if (!fDragPoint)
        return false;

    if(ComparePoint(*pDragPoint,StartPoint, 5) || ComparePoint(*pDragPoint, EndPoint, 5))
        {
        RemovePoint(*pDragPoint);
        fDragPoint = false;
        Invalidate();
        return false;
        }

    //adjust position to original
    pDragPoint->x = Position.x - tpDragRef.x;
    pDragPoint->y = Position.y - tpDragRef.y;

    DragPaint();
    return true;
}
void __fastcall TGraphicLine::MarkDragPoint()
{
    if(!fDragPoint)
        return;
    //mark the spot first
   // Canvas->TextOut(pDragPoint->x, pDragPoint->y, MARK);
}

void __fastcall TGraphicLine::DisplayHandles(bool ShowHandle)
{
    if(fDisplayPoints == ShowHandle)
        return;
    fDisplayPoints = ShowHandle;
    if(Visible)
        Invalidate();
}


bool __fastcall TGraphicLine::ScanPoint(const TPoint& TestPoint, unsigned ScanThreshold)
{
    //scan from start through points
    TPoint StartScan = StartPoint;
    TPoint EndScan = StartScan;
    bool Found = false;
    //iterate through each point
    for (unsigned i = 0; i < LinePoints.size() && !Found; i++)
        {
        EndScan.x += LinePoints[i].x;
        EndScan.y += LinePoints[i].y;
        Found = ScanLine(StartScan, EndScan, TestPoint, ScanThreshold);
        StartScan = EndScan;//set start at next point
        }
    if (!Found)//test aginst last point
        Found = ScanLine(StartScan, EndPoint, TestPoint, ScanThreshold);
    return Found;

}

TPoint* __fastcall TGraphicLine::GetPoint(TPoint& TestPoint, unsigned Tol)
{
    //see whether the test point is a Point in the series of lines
    //returns pointer to the point if in list, otherwise returns NULL
    bool Found = ComparePoint(StartPoint, TestPoint, Tol);
    if(Found)
        return &StartPoint;
    for(unsigned i = 0; i < LinePoints.size(); i++)
        {
        TPoint Cursor = GetControlPointPos(i);
        Found = ComparePoint(TestPoint, Cursor, Tol);
        if(Found)
            return &LinePoints[i];
        }
    Found = ComparePoint(EndPoint, TestPoint, Tol);
    if(Found)
        return &EndPoint;
    else
        return NULL;
}

TPoint TGraphicLine::GetControlPointPos(unsigned Index)
{
 // Get the Control positon of LinePoints Relative to StartPoint
 TPoint Cursor = StartPoint;
 for (unsigned i = 0; i <= Index; i++)
    {
    Cursor.x += LinePoints[i].x;
    Cursor.y += LinePoints[i].y;
    }
 return Cursor;
}

void TGraphicLine::CompleteDrag()
{
//    int X_Diff = tpDragPoint.x - tpDragRef.x;
//    int Y_Diff = tpDragPoint.y - tpDragRef.y;
//    pDragPoint->x += X_Diff;
//    pDragPoint->y += Y_Diff;
    pDragPoint->x = tpDragPoint.x - tpDragStart.x;
    pDragPoint->y = tpDragPoint.y - tpDragStart.y;    
    if(wDragIndex < LinePoints.size()-1)
        {
        LinePoints[wDragIndex +1].x = tpDragEnd.x - tpDragPoint.x;
        LinePoints[wDragIndex +1].y = tpDragEnd.y - tpDragPoint.y;
        }
    AdjustLineArea();
    Invalidate();
}
//******************************************************************************
double GetDistance (TPoint Start, TPoint End)
{
    //calculate start to end
    return  sqrt( (Start.x - End.x) * (Start.x - End.x) +
                                  (Start.y - End.y)*(Start.y - End.y));
}
//**************************************************************************
bool ComparePoint(const TPoint& A, const TPoint& B, unsigned Tol)
{
    return (unsigned)abs(A.x - B.x) <= Tol && (unsigned)abs(A.y - B.y)<= Tol;
}


//*****************************************************************


bool ScanLine(TPoint Start, TPoint End, TPoint Test,unsigned Tolerance)
{
    bool Possible;
    //check that the  x direction is right
    if(Start.x <= End.x)
       Possible = (Test.x  >= Start.x   && Test.x <= End.x);
    else //start x must be >
        Possible = (Test.x <= Start.x && Test.x >= End.x );
    if (!Possible)
        return false;

    if(Start.y <= End.y)
       Possible = (Test.y >= Start.y  && Test.y <= End.y);
    else //start y must be >
        Possible = (Test.y <= Start.y  && Test.y >= End.y);
    if (!Possible)
        return false;

    //distance(Start To End) == distance(Start to Test) + distance (Test to End)
    double Total, First, Second, Difference;
    Total = GetDistance(Start, End);
    First = GetDistance(Start, Test);
    Second = GetDistance(Test, End);
    Difference = abs(Total - First - Second);

    return (unsigned)Difference <= Tolerance;

}


//---------------------------------------------------------------------------
namespace Graphicline
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TGraphicLine)};
        RegisterComponents("Samples", classes, 0);
    }
}

//---------------------------------------------------------------------------


