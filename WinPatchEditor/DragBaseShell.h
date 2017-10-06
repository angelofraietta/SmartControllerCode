//---------------------------------------------------------------------------
#ifndef DragBaseShellH
#define DragBaseShellH
#include "TypeDefs.h"
#include "IdentityHook.h"
class TDragBaseShell:public TDragObject
{
public:
   __fastcall TDragBaseShell(TBaseShellHook* pHook, P_PATCH pParent)
      :pObject(pHook), pPatch(pParent){}
   TBaseShellHook* pObject;
   const P_PATCH pPatch;
};
//---------------------------------------------------------------------------
#endif
