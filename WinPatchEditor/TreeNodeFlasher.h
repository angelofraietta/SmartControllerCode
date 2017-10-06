//---------------------------------------------------------------------------
#ifndef TreeNodeFlasherH
#define TreeNodeFlasherH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ToolWin.hpp>


class TTreeNodeFlasher :public TThread
{
public:
    TTreeNodeFlasher(TTreeNode*, TTreeView*, unsigned NumFlashes = 3, unsigned Rate = 500);
    void SetNumFlashes(unsigned);
    void SetRate(unsigned);
    void __fastcall Execute();
private:
    bool isFlashing; //is currently flashing
    int iImage;      // the normal StateIndex
    unsigned wNumFlashes, wCurrentFlash, wRate;
    TTreeNode* Node;
    TTreeView* NodeDisplay;
};


//---------------------------------------------------------------------------
#endif
