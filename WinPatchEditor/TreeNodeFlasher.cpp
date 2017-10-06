//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TreeNodeFlasher.h"
#include "PatchUnit.h"
#include "IdentityHook.h"
#include "typenames.h"
#define FLASH_ID 7 //the number in the ImageList

TTreeNodeFlasher::TTreeNodeFlasher(TTreeNode* pNode, TTreeView* pNodeDisplay, unsigned NumFlashes, unsigned Rate)
    :TThread(true), isFlashing(false),wNumFlashes(NumFlashes)
    ,wRate(Rate)
{
    Priority = tpLowest;
    FreeOnTerminate = true;
    Resume();
    NodeDisplay = pNodeDisplay;
    Node = pNode;
    if (!(pNode->Data))
        Terminate();

    typedef TObject* pTObject; //typedef allows access of data
      	//get data
   	TObject* pObject = pTObject(Node->Data);
    if(dynamic_cast<TBaseShellHook*> (pObject))
        iImage = ((TBaseShellHook*)pObject)->StateIndex;


}

void TTreeNodeFlasher::SetRate(unsigned Rate)
{
    wRate = Rate;
}

void TTreeNodeFlasher::SetNumFlashes(unsigned NumFlashes)
{
    wNumFlashes = NumFlashes;
}

void __fastcall TTreeNodeFlasher::Execute()
{
    if (Terminated)
        return;
    for (unsigned x = 0; x < wNumFlashes; x++)
        {
        Node->StateIndex = FLASH_ID;
        NodeDisplay->Invalidate();
        Sleep(wRate/2);
        Node->StateIndex = iImage;
        NodeDisplay->Invalidate();
        Sleep(wRate/2);
        }
    Terminate();
}


//---------------------------------------------------------------------------
#pragma package(smart_init)

