//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "KillerUnit.h"
#include "CursorsUnit.h"
#include "IdentityHook.h"
#include "ObjectBox.h"
#include "ConnectorLine.h"
#include "TComment.h"

__fastcall TKiller::TKiller(TObject* Creator)
  :TDragObject(), Instigator(Creator)
  {
  }

void __fastcall TKiller::Finished(TObject* Target, int X, int Y, bool Accepted)
  {
  if(!Accepted) return;

  if(dynamic_cast<TObjectBox*>(Target))
    {
    TBaseShellHook* Victim = ((TObjectBox*)Target)->GetHook();
    Victim->KillObject(Victim);
    return;
    }

  if(dynamic_cast<TConnectorLine*>(Target))
    {
    TConnectorHook* Victim = ((TConnectorLine*)Target)->GetHook();
    Victim->KillObject(Victim);
    return;
    }
  if(dynamic_cast<TComment*>(Target))
    {
    TComment* Victim = (TComment*)Target;
    Victim->KillObject(Victim);
    return;
    }
  }

TCursor __fastcall TKiller::GetDragCursor(bool Accepted, int X, int Y)
  {
  if(Accepted)
    {
    return (TCursor)crRedScull;
    }

  else
    {
    return (TCursor)crScull;
    }
  }

__fastcall TKillerObject::TKillerObject(TComponent* Owner)
  :TControl(Owner)
  {
  }


void __fastcall TKillerObject::DoStartDrag(TDragObject *&DragObject)
  {
  DragObject = new TKiller(Owner);
  }
//---------------------------------------------------------------------------
#pragma package(smart_init)
