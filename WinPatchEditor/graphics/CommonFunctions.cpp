//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CommonFunctions.h"

TPoint AlignPoint(TPoint Ref, TControl* ControlRef)
{
    TForm* Surface =(TForm*)(ControlRef->Parent);
    Ref = ControlRef->ScreenToClient(Surface->ClientToScreen(Ref));
    
    Ref.x += Surface->HorzScrollBar->Position;
    Ref.y += Surface->VertScrollBar->Position;
    return Ref;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
