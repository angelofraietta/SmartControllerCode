//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FormRefresh.h"
#include "BaseShellsUnit.h"
#define UPDATE_RATE 100

TFormRefresh::TFormRefresh(TBaseShellEditForm* pForm)
    :TThread(false), EditForm(pForm)
{
    Priority = tpIdle;
    FreeOnTerminate = true;
}

void __fastcall TFormRefresh::PerformUpdate(void)
{
    if (!(Terminated) && EditForm->AllowUpdate())
        EditForm->UpdateForm();
}

//---------------------------------------------------------------------------
void __fastcall TFormRefresh::Execute()
{
typedef void __fastcall (__closure *TThreadMethod)(void);
    while (!Terminated)
        {
        Synchronize(PerformUpdate);
        Sleep(UPDATE_RATE);
        }
}


#pragma package(smart_init)
