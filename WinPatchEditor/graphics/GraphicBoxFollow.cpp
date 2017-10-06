//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GraphicBoxFollow.h"
#include "GraphicBoxUnit.h"
#include "GraphicLineFollow.h"

__fastcall TGraphicBoxFollow::TGraphicBoxFollow(TGraphicControlBox* Owner,
                                                unsigned Number, bool IsTop)
    :TGraphicShape(Owner), Leader(Owner), wFollowerNum(Number), fIsTop(IsTop)
{
    Height = BOX_FOLLOWER_HEIGHT;
    Width = BOX_FOLLOWER_WIDTH;
    Pen->Width = 10;
    Visible = true;
    Cursor = crHandPoint;
}

__fastcall TGraphicBoxFollow::~TGraphicBoxFollow()
{
    for(unsigned i = 0; i < Followers.size(); i++)
        Followers[i]->RemoveLeader(this);
}


void TGraphicBoxFollow::Position(TPoint NewPos)
{
    FPosition = NewPos;
    Follow(true);
}

void __fastcall TGraphicBoxFollow::Follow(bool Finished)
{
    FPosition = ((TGraphicControlBox*)Owner)
                ->GetOffset(wFollowerNum, fIsTop);
    Left = FPosition.x;
    Top = FPosition.y;
    FPosition.x = FPosition.x + ((TScrollingWinControl*)Parent)->HorzScrollBar->Position;
    FPosition.y = FPosition.y + ((TScrollingWinControl*)Parent)->VertScrollBar->Position;    
    Invalidate();

    NotifyFollowers(Finished);
}

void __fastcall  TGraphicBoxFollow::NotifyFollowers(bool Finished)
{
//notifies all followers that they must update their information
    for(unsigned i = 0; i < Followers.size(); i++)
        Followers[i]->Follow(Finished);
}

void __fastcall TGraphicBoxFollow::AddFollower(TLineFollow* Follower)
{
    Followers.push_back(Follower);
}

void __fastcall TGraphicBoxFollow::RemoveFollower(TLineFollow* Follower)
{
    bool Found = false;
    for (unsigned i = 0; i < Followers.size() && !Found; i++)
         if (Follower == Followers[i])
            {
            Followers.erase(&Followers[i]);
            Found = true;
            }

}
void __fastcall TGraphicBoxFollow::DragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
    TGraphicControlBox* pControl = dynamic_cast<TGraphicControlBox*> (Source);
    if(pControl)
        {
        TPoint Pos; Pos.x = X; Pos.y = Y;
        Pos = pControl->ScreenToClient(ClientToScreen(Pos));
        pControl ->ProcessDrag(Pos.x, Pos.y);
        Accept = true;
        return;
    }
    //pass to a virtual processing to descendent
    ProcessDragOver(Source, X,  Y, State, Accept);
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
