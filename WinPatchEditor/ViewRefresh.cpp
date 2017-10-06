//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ViewRefresh.h"
#include "ViewFormUnit.h"
#include "interfacebridge.h"

#define UPDATE_RATE 1000
#define SIMULATOR_UPDATE_RATE 100

TViewRefresh::TViewRefresh(TViewForm* pForm)
    :TThread(false), EditForm(pForm)
{
    Priority = tpIdle;
    FreeOnTerminate = true;
}

void __fastcall TViewRefresh::PerformUpdate(void)
{
    if (!Terminated)
        EditForm->UpdateForm();
}

//---------------------------------------------------------------------------
void __fastcall TViewRefresh::Execute()
{
typedef void __fastcall (__closure *TThreadMethod)(void);
    while (!Terminated)
        {
      DWORD update_rate = UPDATE_RATE;
      if (EditForm->GetCurrentEngine() == GetSimulator())
      {
        update_rate = SIMULATOR_UPDATE_RATE;
      }

        Synchronize(PerformUpdate);
        Sleep(update_rate);
        }
}


//---------------------------------------------------------------------------
#pragma package(smart_init)
 