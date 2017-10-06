//---------------------------------------------------------------------------
#ifndef ViewRefreshH
#define ViewRefreshH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
class TViewForm;//forward dec


class TViewRefresh :public TThread
{
public:
    TViewRefresh(TViewForm*);
    void __fastcall Execute();
    void __fastcall PerformUpdate();
private:
    TViewForm* EditForm;
};

//---------------------------------------------------------------------------
#endif
 