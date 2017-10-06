//---------------------------------------------------------------------------
#ifndef GraphicBoxFollowH
#define GraphicBoxFollowH
#include "GraphicShape.h"
#include <vector>
#define BOX_FOLLOWER_HEIGHT 5
#define BOX_FOLLOWER_WIDTH  10

class TGraphicControlBox; //forard dec
class TLineFollow;
class TGraphicBoxFollow:public TGraphicShape
{
public:
    __fastcall TGraphicBoxFollow(TGraphicControlBox* pLeader,
                                 unsigned Number, bool IsTop );
    __fastcall ~TGraphicBoxFollow();

    void __fastcall Follow(bool Finished);
    void Position(TPoint NewPosition);
    void __fastcall AddFollower(TLineFollow* Follower);
    void __fastcall RemoveFollower(TLineFollow* Follower);    
    void __fastcall NotifyFollowers(bool ); //notify follwers that an event is happening

    TPoint Position()const {return FPosition;}

protected:
    void __fastcall DragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept);
    virtual void __fastcall ProcessDragOver(TObject *Source, int X, int Y,
                            TDragState State, bool &Accept){Accept = false;}
    TGraphicControlBox* Leader;//the object this follows
    TPoint FPosition;            //the position on the Leader
    std::vector<TLineFollow*> Followers;
    const unsigned wFollowerNum; //the number that this is
    const bool fIsTop;

};

//---------------------------------------------------------------------------
#endif
