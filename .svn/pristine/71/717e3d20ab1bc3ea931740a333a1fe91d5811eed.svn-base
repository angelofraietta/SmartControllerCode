//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TComment.h"
#include "ViewFormUnit.h"
#include "CommentFormUnit.h"
#include <killerUnit.h>
__fastcall TComment::TComment(const char* Comment, TViewForm* Owner)
  :TLabel(Owner), pParent(Owner)
  {
  Parent = Owner;
  SetTextBuf((char*)Comment);
  Top = 100;
  Left = 100;
  Height = 15;
  Width = 100;
  Visible = false;

  }

void __fastcall TComment::MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
  {
  pParent->SetActiveComment(this); //let parent know this is the active comment

  if(Shift.Contains(ssDouble))
    {
    CommentDialog->Comment->Text = Text;
    CommentDialog->ShowModal();
    Text = CommentDialog->Comment->Text;
    }

  else
    {
    BeginDrag(false, 10);
    }
  }
void __fastcall TComment::DoEndDrag(TObject *Source, int X, int Y)
  {
  Enabled = true;
  }
void __fastcall TComment::DoStartDrag(TDragObject* &DragObject)
  {
  Enabled = false;
  }

bool TComment::GetNewComment(char* buff)
  {
  strcpy(buff, "New Comment");
  return true;
  }

void __fastcall TComment::DragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept)
  {
  if(IsDragObject(Source)
  && dynamic_cast<TKiller*> ((TDragObject*)Source))//see if is a drag object
    {
    Accept = true;
    return;
    }

  Accept = false;
  }

void TComment::KillObject(TComment* Victim)
  {
  Victim->pParent->RemoveComment(Victim);
  delete Victim;
  }

TPoint TComment::GetPosition()const
{
    TPoint Position;

    Position.x = Left + ((TScrollingWinControl*)Parent)->HorzScrollBar->Position;
    Position.y = Top + ((TScrollingWinControl*)Parent)->VertScrollBar->Position;
    return Position;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
