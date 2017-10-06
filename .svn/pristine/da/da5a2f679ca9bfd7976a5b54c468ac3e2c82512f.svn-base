//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GraphicBoxUnit.h"
#include "GraphicBoxFollow.h"
#include "Cursorsunit.h"
#define RESIZE_BORDER 10 //how far from the border to resize
#define DRAG_THRESHOLD 3 //the number of pixels to befin a drag

bool TGraphicControlBox::m_allow_resize = false;

__fastcall TGraphicControlBox::TGraphicControlBox(TComponent* Owner)
    :TGraphicShape(Owner)
{
    wMinHeight = MIN_SHAPE_HEIGHT;
    wMinWidth = MIN_SHAPE_WIDTH;
    DragCursor = (TCursor)crHandMove;

}
void __fastcall TGraphicControlBox::MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (Button == mbLeft
   || Button == mbRight && Shift.Contains(ssCtrl))
      BeginDrag(false, DRAG_THRESHOLD);
}

void __fastcall TGraphicControlBox::MouseMove(TShiftState Shift, int X, int Y)
{
    //if on perimeter do a resize
    if ((m_allow_resize) && (X >= Width - RESIZE_BORDER) && (Y >= Height - RESIZE_BORDER))
        {
        fResize = true;
        Cursor = crSizeNWSE;
        return;
        }
    //must not be resizing
    Cursor = crDefault;
    fResize = false;
}

void __fastcall TGraphicControlBox::ProcessDrag(int X, int Y)
{
    if(fResize)
        {
        DragCursor = crSizeNWSE;
        if(X >= (int)wMinWidth)  Width = X;
        if(Y >= (int)wMinHeight) Height = Y;
        }
    else //is being dragged across screen
        {
        DragCursor = (TCursor)crHandMove;
        //calculate how far the cursor is off center and adjust
        //this control's position
        int XDiff = Width/2 - X;
        int YDiff = Height/2 - Y;
        //X and Y must become centre
        Left = Left - XDiff ;
        Top = Top - YDiff;
        }
    NotifyFollowers(false);
}
/*
does not work with builder 4
void __fastcall TGraphicControlBox::DoStartDrag(TDragObject *&DragObject)
{
      DragObject = new TDragControlObject(this);
}
   */
void __fastcall TGraphicControlBox::DragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
    if(Source == this)
        {
        ProcessDrag(X,Y);
        NotifyFollowers(false);
        Accept = true;
        }
}

void __fastcall  TGraphicControlBox::NotifyFollowers(bool Finished)
{
//notifies all followers that they must update their information
    for(unsigned i = 0; i < TopFollowers.size(); i++)
        TopFollowers[i]->Follow(Finished);
    for(unsigned i = 0; i < BottomFollowers.size(); i++)
        BottomFollowers[i]->Follow(Finished);

}

void TGraphicControlBox::AddFollower(TGraphicBoxFollow* Follower, bool IsTop)
{
    if (IsTop)
        {
        Follower->Parent = Parent; //make same paren
        TopFollowers.push_back(Follower);
        //make sure enough room to display followers
        if((int)TopFollowers.size() * BOX_FOLLOWER_WIDTH > Width)
            {
            Width =  (TopFollowers.size()+1) * BOX_FOLLOWER_WIDTH;
            wMinWidth = Width;
            Invalidate();
            }
        }
    else
        {
        Follower->Parent = Parent; //make same parent
        BottomFollowers.push_back(Follower);
        if((int)BottomFollowers.size() * BOX_FOLLOWER_WIDTH > Width)
            {
            Width =  (BottomFollowers.size()+1) * BOX_FOLLOWER_WIDTH;
            wMinWidth = Width;
            Invalidate();
            }

        }
    NotifyFollowers(true);
}

TGraphicBoxFollow* TGraphicControlBox::AddFollower(bool IsTop)
{
    TGraphicBoxFollow* Follower;
    if (IsTop)
        {
        unsigned NumFollowers = TopFollowers.size();
        Follower = new TGraphicBoxFollow(this, NumFollowers, IsTop);
        Follower->Parent = Parent; //make same paren
        TopFollowers.push_back(Follower);
        //make sure enough room to display followers
        if((int)TopFollowers.size() * BOX_FOLLOWER_WIDTH > Width)
            {
            Width =  (TopFollowers.size()+1) * BOX_FOLLOWER_WIDTH;
            wMinWidth = Width;
            Invalidate();
            }
        }
    else
        {
        unsigned NumFollowers = BottomFollowers.size();
        Follower = new TGraphicBoxFollow(this, NumFollowers, IsTop);
        Follower->Parent = Parent; //make same parent
        BottomFollowers.push_back(Follower);
        if((int)BottomFollowers.size() * BOX_FOLLOWER_WIDTH > Width)
            {
            Width =  (BottomFollowers.size()+1) * BOX_FOLLOWER_WIDTH;
            wMinWidth = Width;
            Invalidate();
            }

        }
    NotifyFollowers(true);
    return Follower;
}

void __fastcall TGraphicControlBox::RemoveFollower(bool IsTop)
{
    TGraphicBoxFollow* Follower;
    if(IsTop)
        {
        unsigned NumFollowers =TopFollowers.size();
         if(!NumFollowers)
            return;
         Follower = TopFollowers[NumFollowers - 1];
         delete Follower;
         TopFollowers.erase(&TopFollowers[NumFollowers-1]);
         }
    else //is bottom
        {
        unsigned NumFollowers =BottomFollowers.size();
        if(!NumFollowers)
            return;
        Follower = BottomFollowers[NumFollowers - 1];
        delete Follower;
        BottomFollowers.erase(&BottomFollowers[NumFollowers-1]);
        }
    AdjustMinWidth();
    NotifyFollowers(true);
}

TGraphicBoxFollow* TGraphicControlBox::GetFollower(unsigned FollowerNum, bool IsTop)
{
    if(IsTop)
        {
        if(FollowerNum < TopFollowers.size())
            return TopFollowers[FollowerNum];
        else
            return NULL;
        }
    else
        {
        if(FollowerNum < BottomFollowers.size())
            return BottomFollowers[FollowerNum];
        else
            return NULL;
        }

}

void __fastcall TGraphicControlBox::DoEndDrag(TObject *Source, int X, int Y)
{
    for(unsigned i = 0; i < TopFollowers.size(); i++)
        TopFollowers[i]->Follow(true);
    for(unsigned i = 0; i < BottomFollowers.size(); i++)
        BottomFollowers[i]->Follow(true);

}

TPoint __fastcall TGraphicControlBox::GetOffset(unsigned FollowerNum, bool IsTop)const
{
    TPoint Position;
    //get x boundaries
    const unsigned BoundaryWidth = Width - BOX_FOLLOWER_WIDTH;

    //set the y position
    if(IsTop)
        {
        Position.y = Top - BOX_FOLLOWER_HEIGHT/2;
        //return boundary conditions
        if(!FollowerNum || TopFollowers.size() <= FollowerNum)//the follower is zero
            {
            Position.x = Left;
            return Position;
            }
        //get spacing between followers
        const unsigned Spacing = BoundaryWidth / (TopFollowers.size() -1);
        Position.x = FollowerNum * Spacing + Left;
        }
    else
        {
        Position.y = Top + Height - BOX_FOLLOWER_HEIGHT/2;
        if(!FollowerNum || BottomFollowers.size() <= FollowerNum)//the follower is zero
            {
            Position.x = Left;
            return Position;
            }
        //get spacing between followers
        const unsigned Spacing = BoundaryWidth / (BottomFollowers.size() -1);
        Position.x = FollowerNum * Spacing + Left;
        }
    //set the x
    return Position;
}

void __fastcall TGraphicControlBox::ShowObject(bool ShowObject)
{
    //display or hide the object and its followers
    Visible = ShowObject;

    for(unsigned i = 0; i < TopFollowers.size(); i++)
        TopFollowers[i]->Visible = ShowObject;
    for(unsigned i = 0; i < BottomFollowers.size(); i++)
        BottomFollowers[i]->Visible = ShowObject;
}

void TGraphicControlBox::AdjustMinWidth()
{
   //find Minimum size for top and bottom
   unsigned MinTopWidth = MIN_SHAPE_WIDTH;
   unsigned MinBottomWidth = MIN_SHAPE_WIDTH;
   //make sure enough room to display followers
   if((int)TopFollowers.size() * BOX_FOLLOWER_WIDTH > MIN_SHAPE_WIDTH)
      MinTopWidth =  (TopFollowers.size()+1) * BOX_FOLLOWER_WIDTH;

   if((int)BottomFollowers.size() * BOX_FOLLOWER_WIDTH > MIN_SHAPE_WIDTH)
      MinBottomWidth =  (BottomFollowers.size()+1) * BOX_FOLLOWER_WIDTH;

   //select the largest
   if(MinTopWidth > MinBottomWidth)
      wMinWidth =  MinTopWidth;
   else
      wMinWidth = MinBottomWidth;
}

TPoint TGraphicControlBox::GetPosition()const
{
    TPoint Position;

    Position.x = Left + ((TScrollingWinControl*)Parent)->HorzScrollBar->Position;
    Position.y = Top + ((TScrollingWinControl*)Parent)->VertScrollBar->Position;
    return Position;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
