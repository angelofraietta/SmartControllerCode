//---------------------------------------------------------------------------
#ifndef FormRefreshH
#define FormRefreshH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
class TBaseShellEditForm;//forward dec


class TFormRefresh :public TThread
{
public:
    TFormRefresh(TBaseShellEditForm*);
    void __fastcall Execute();
    void __fastcall PerformUpdate();
private:
    TBaseShellEditForm* EditForm;

};

//---------------------------------------------------------------------------
#endif
