//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "GraphicLineFollow.h"
#include "GraphicBoxUnit.h"
#include "GraphicBoxFollow.h"
#include "Cursorsunit.h"
#include "CommonFunctions.h"
#include "DragLine.h"
#define DRAG_THRESHOLD 3 //the number of pixels to befin a drag

#define TOL 10 //a tolerance for mouse position

TLineFollow* TLineFollow::pFocusedControl = NULL;


__fastcall TLineFollow::TLineFollow(TComponent* Owner, TForm* pParent)
    :TGraphicLine(Owner),pStartLeader(NULL),pEndLeader(NULL),
    fIsOver(false)
{
 Parent = pParent;
 SendToBack();
 Visible = true;
 DragCursor = (TCursor)crPlace;

}

__fastcall TLineFollow::~TLineFollow()
{
    if (pFocusedControl == this)
        pFocusedControl = NULL;
    if(pStartLeader)
        pStartLeader->RemoveFollower(this);
    if(pEndLeader)
        pEndLeader->RemoveFollower(this);
}

void __fastcall TLineFollow::RemoveLeader(TGraphicBoxFollow* Leader)
{
    if(Leader == pStartLeader)
        pStartLeader = NULL;
    if(Leader == pEndLeader)
        pEndLeader = NULL;
}
void __fastcall TLineFollow::Follow(bool Finished)
{
     if(pFocusedControl == this)
        {
        DisplayHandles(false);
        pFocusedControl = NULL;
        }
     if(pStartLeader)
        {
        ParentStartPoint = pStartLeader->Position();
        ParentStartPoint.x += pStartLeader->Width/2;
        ParentStartPoint.y += pStartLeader->Height/2;

        }
    if(pEndLeader)
        {
        ParentEndPoint = pEndLeader->Position();
        ParentEndPoint.x += pEndLeader->Width/2;
        ParentEndPoint.y += pEndLeader->Height/2;

        }
    AdjustLineArea();
    //check offset from previous and adjust first and last Points
    /*
    if(PrevLinePoints.size() > 3 && LinePoints.size() > 1 && Visible)
      {
      //find offset for leader
      int Offset;

      Offset = StartPoint.x - PrevLinePoints[0].x;
      LinePoints[0].x = LinePoints[0].x + Offset;
      Offset = StartPoint.y - PrevLinePoints[0].y;
      LinePoints[0].y = LinePoints[0].y + Offset;

      //find offset for end
      Offset = EndPoint.x - (PrevLinePoints.end()-1)->x;
      (LinePoints.end()-1)->x = (LinePoints.end()-1)->x + Offset;
      Offset = EndPoint.y - (PrevLinePoints.end()-1) ->y;
      (LinePoints.end()-1) ->y = (LinePoints.end()-1)->y + Offset;

    }
*/
    if(Finished && Visible)
        {
        AdjustLineArea();
        Invalidate();
        }
    else
        DragPaint();


}

void __fastcall TLineFollow::MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
        ProcessSelect(Button, Shift, X, Y);
}

void __fastcall TLineFollow::ProcessSelect(TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(fIsOver && pFocusedControl == this)
        {
        TPoint Pos;
        Pos.x = X;
        Pos.y = Y;
        //Pos = Parent->ScreenToClient(ClientToScreen(Pos));
        TPoint* SelectedPoint = GetPoint(Pos, TOL);
        DisplayHandles(true);
        if(SelectedPoint)
            {
            if(fRemovePoint)
                {
                RemovePoint(*SelectedPoint);
                SelectedPoint = NULL;
                Invalidate();
                }
            else
                {
                pDragPoint = SelectedPoint;
                fDragPoint = true;
                }
            }
        else
            {
            if(!fRemovePoint)
                {
                pDragPoint = AddPoint(Pos, TOL);
                fDragPoint = false;
                }
            }
        tpDragRef = Pos;
        
        if(!fRemovePoint && pDragPoint != &StartPoint && pDragPoint != &EndPoint)
            BeginDrag(false, DRAG_THRESHOLD);

        return;
        }
     if(!fIsOver)
        {
        if(pFocusedControl == this)//remove focus from it
            {
            DisplayHandles(false);
            pFocusedControl = NULL;
            return;
            }
        else
            {
            if(pFocusedControl)
                pFocusedControl->BringToFront();
            }
        }
     else //fIsOver
        {
        if(pFocusedControl)
            pFocusedControl->DisplayHandles(false);
        pFocusedControl = this;
        DisplayHandles(true);
        }
}

void __fastcall TLineFollow::DoStartDrag(TDragObject *&DragObject)
{
    DragCursor = (TCursor)crPlace;
    TDragLine* pDragObject = new TDragLine(this);
    pDragObject->pDragPoint = pDragPoint;
    tpDragRef = *pDragPoint;
    //get index of pDragPoint;
    unsigned i;
    unsigned Size =  LinePoints.size();
    for(i = 0; i <  Size && pDragPoint != &LinePoints[i]; i++)
         ;
    //get start
    if (i == 0)
        tpDragStart = StartPoint;
    else
        tpDragStart = GetControlPointPos(i-1);
    //get end
    if (i == Size -1)
        tpDragEnd = EndPoint;
    else
        {
        tpDragEnd = GetControlPointPos(i+1);
        pDragEnd = &LinePoints[i+1];
        }
    wDragIndex = i;
    
    pDragObject->tpDragPoint = Parent->ScreenToClient(ClientToScreen(tpDragRef));
    pDragObject->tpStartPoint = Parent->ScreenToClient(ClientToScreen(tpDragStart));
    pDragObject->tpEndPoint = Parent->ScreenToClient(ClientToScreen(tpDragEnd));

//    pDragObject->tpStartPoint = ParentStartPoint;
//    pDragObject->tpEndPoint = ParentEndPoint;
    DragObject = pDragObject;
}

void __fastcall TLineFollow::DragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
    //TPoint ParentPos;
    //ParentPos.x = X; ParentPos.y = Y;
    //ParentPos = Parent->ScreenToClient(ClientToScreen(ParentPos));
    GraphicDragOver(Source, X, Y, State, Accept);
}

void __fastcall TLineFollow::GraphicDragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
    TGraphicControlBox* pControl = dynamic_cast<TGraphicControlBox*> (Source);
    if(pControl)
        {
        Accept = true;
        TPoint Pos; Pos.x = X; Pos.y = Y;
        Pos = pControl->ScreenToClient(ClientToScreen(Pos));
        pControl ->ProcessDrag(Pos.x, Pos.y);
        //remove any focus from focused control
        if(pFocusedControl)
            {
            pFocusedControl->DisplayHandles(false);
            pFocusedControl = NULL;
            }
    }
    if(dynamic_cast<TLineFollow*>(Source))
        {
         Accept = true;
         TPoint Pos;//the new position
         Pos.x = X;
         Pos.y = Y;
         Pos = ((TLineFollow*)Source)->ScreenToClient(ClientToScreen(Pos));
         //check if Point has been swollowed by Leader
         if(!((TLineFollow*)Source)->DragPoint(Pos))
            DragCursor = crDefault;
         return;
        }
     if(dynamic_cast<TDragLine*>(Source))
        {
        Accept = true;

        TPoint Pos; Pos.x = X; Pos.y = Y;
        Pos = Parent->ScreenToClient(ClientToScreen(Pos));  
        ((TDragLine*)Source)->DoDrag(Pos);
        }
}
void __fastcall TLineFollow::StartLeader(TGraphicBoxFollow* Leader)
{
    pStartLeader = Leader;
    ParentStartPoint = pStartLeader->Position();
    ParentStartPoint.x += pStartLeader->Width/2;
    ParentStartPoint.y += pStartLeader->Height/2;

    AdjustLineArea();
    Invalidate();
}
void __fastcall TLineFollow::EndLeader(TGraphicBoxFollow* Leader)
{
    pEndLeader = Leader;
    ParentEndPoint = pEndLeader->Position();
    ParentEndPoint.x += pEndLeader->Width/2;
    ParentEndPoint.y += pEndLeader->Height/2;
    AdjustLineArea();
    Invalidate();
}

void __fastcall TLineFollow::MouseMove(TShiftState Shift, int X, int Y)
{
    fIsOver = false;
    bool IsColoured = false;
    //int PixelColor; //I hate American spelling
    for (int i = - TOL / 2; i < TOL/2 && !IsColoured; i++)
        {
        for(int j = -TOL /2; j < TOL/2 && !IsColoured; j++)
            {
            if(Canvas->Pixels[X+i][Y+j] != ((TForm*)Parent)->Color)
                {

                IsColoured = true;
                //PixelColor = Canvas->Pixels[X+i][Y+j];
                }
            }
         }
    TPoint Pos; Pos.x = X; Pos.y = Y;
    //Pos = Parent->ScreenToClient(ClientToScreen(Pos));
    fIsOver = IsColoured && ScanPoint(Pos, 5);
                         ;//
    if(fIsOver)
        {
        if(pFocusedControl == this)
            //display a cursor for dragging
            {
            if(fRemovePoint)
                Cursor = (TCursor)crErase;
            else
                Cursor = (TCursor)crPlace;

            DisplayMouseMove (true);
            }
        else
            {
            Cursor = crHandPoint;
            DisplayMouseMove (false);
            }

        }
    else
        {
        Cursor = crDefault;
        SendToBack();
        DisplayMouseMove (false);
        }
}

void __fastcall TLineFollow::DoEndDrag(TObject *Source, int X, int Y)
{
    SendToBack();
    Invalidate();
   // Screen->Cursors[crNoDrop] = Screen->Cursors[crNormalNoDrop];
}

bool TLineFollow::IsOverAndAtFront(int X, int Y) //returns true if over and at front
  {
  fIsOver = false;
  bool IsColoured = false;
  //int PixelColor; //I hate American spelling
  for (int i = - TOL / 2; i < TOL/2 && !IsColoured; i++)
    {
    for(int j = -TOL /2; j < TOL/2 && !IsColoured; j++)
      {
      if(Canvas->Pixels[X+i][Y+j] != ((TForm*)Parent)->Color)
        {
        IsColoured = true;
        //PixelColor = Canvas->Pixels[X+i][Y+j];
        }

      }//end for

    }//end for

  TPoint Pos; Pos.x = X; Pos.y = Y;
  //Pos = Parent->ScreenToClient(ClientToScreen(Pos));
  fIsOver = IsColoured && ScanPoint(Pos, 5);
                         ;//
  if(fIsOver)
    {
    if(pFocusedControl == this)
      {
      DisplayHandles(true);
      return true;
      }

    else
      {
      BringToFront();
      DisplayHandles(true);
      pFocusedControl = this;
      Invalidate();
      }

    }

  else  //is not over
    {
    SendToBack();
    DisplayHandles(false);
    Invalidate();
    }

  return false;
  }
//---------------------------------------------------------------------------
#pragma package(smart_init)
