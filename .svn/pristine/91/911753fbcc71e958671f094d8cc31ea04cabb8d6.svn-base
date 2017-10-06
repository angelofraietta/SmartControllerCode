//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "VariableSizeBox.h"
#include "ObjectSocket.h"

__fastcall TVariableSizeBox::TVariableSizeBox(TBaseShellHook* Owner, TViewForm* pParent)
   :TObjectBox(Owner, pParent)
   {
   }

__fastcall TVariableSizeBox::~TVariableSizeBox()
{
}

TObjectBox* TVariableSizeBox::Create(TBaseShellHook* Owner, TViewForm* pParent)
{
   return new TVariableSizeBox(Owner, pParent);
}

void TVariableSizeBox::UpdateDisplay()
{                         
    TObjectBox::UpdateDisplay();
   if(BaseShellQuestion::GetNumInlets(GetCurrentEngine(), pObject) != TopFollowers.size()
   || BaseShellQuestion::GetNumOutlets(GetCurrentEngine(), pObject) != BottomFollowers.size())
      {//adjust the number of inlets and outlets

      //first inlets
      unsigned CurrentNumInlets =TopFollowers.size();
      if(BaseShellQuestion::GetNumInlets(GetCurrentEngine(), pObject) < TopFollowers.size())
         {//remove inlets
         for (unsigned i = BaseShellQuestion::GetNumInlets(GetCurrentEngine(), pObject); i < CurrentNumInlets; i++)
            RemoveFollower(InletFollow);
         }
      else //add inlets
         for (unsigned i = CurrentNumInlets ; i < BaseShellQuestion::GetNumInlets(GetCurrentEngine(), pObject) ; i++)
           {
           TObjectSocket* InletDisplay = new TObjectSocket(this, i, InletFollow);
           AddFollower(InletDisplay, InletFollow);
           InletDisplay->pObject = pObject; //give same base
           InletDisplay->Hint = InletDisplay->GetSocketDetails();
           InletDisplay->ShowHint = true;
           }

         //do same for outlets
      unsigned CurrentNumOutlets = BottomFollowers.size();
      if(BaseShellQuestion::GetNumOutlets(GetCurrentEngine(), pObject) < BottomFollowers.size())
         {
         for (unsigned i = BaseShellQuestion::GetNumOutlets(GetCurrentEngine(), pObject); i < CurrentNumOutlets; i++)
            RemoveFollower(OutletFollow);
         }
      else
         for (unsigned i = CurrentNumOutlets ; i < BaseShellQuestion::GetNumOutlets(GetCurrentEngine(), pObject) ; i++)
           {
           TObjectSocket* OutletDisplay = new TObjectSocket(this, i, OutletFollow);
           AddFollower(OutletDisplay, OutletFollow);
           OutletDisplay->pObject = pObject; //give same base
           OutletDisplay->Hint = OutletDisplay->GetSocketDetails();
           OutletDisplay->ShowHint = true;
           }
      AdjustMinWidth();
      }

}

//---------------------------------------------------------------------------

#pragma package(smart_init)
