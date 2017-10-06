//---------------------------------------------------------------------------
#ifndef ToggleBoxH
#define ToggleBoxH

#include "ObjectBox.h"
class TToggleBox:public TObjectBox
{
public:
   __fastcall TToggleBox(TBaseShellHook* Owner, TViewForm* pParent);
   __fastcall ~TToggleBox();
   static TObjectBox* Create(TBaseShellHook* Owner, TViewForm* pParent);
   void __fastcall MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
   void UpdateDisplay();
protected:
   void __fastcall Paint();
   bool PrevState;
   bool GetState ();
};

//---------------------------------------------------------------------------
#endif
 