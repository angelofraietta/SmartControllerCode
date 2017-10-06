//---------------------------------------------------------------------------
#ifndef NumberBoxWindowUnitH
#define NumberBoxWindowUnitH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include "typedefs.h"
class TNumberBox;
class TNumberBoxWindow;

class TNumberBoxEdit:public TEdit
{
public:
   __fastcall TNumberBoxEdit(TNumberBoxWindow* Owner);
   void LoadData();
protected:
   void __fastcall MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall OnExit();
};


class TNumberBoxScroll:public TScrollBar
{
public:
   __fastcall TNumberBoxScroll(TNumberBoxWindow* Owner);
   void LoadData();
protected:
   void __fastcall MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall Scroll(TScrollCode ScrollCode, int &ScrollPos);
};


//---------------------------------------------------------------------------
class TNumberBoxWindow : public TWinControl
{
friend class TNumberBoxScroll;
friend class TNumberBoxEdit;
private:
  TNumberBox* _nBox;
protected:
   P_BASESHELL pObject;
public:
  int GetNumber();
  int GetLowerLimit();
  int GetUpperLimit();
  void SetNumber(int new_val);
  void Send();
//define the types of displays
enum {nbwNone, nbwNumber, nbwMidiNote, nbwVSlider, nbwHSlider, nbwGuage};

    __fastcall TNumberBoxWindow(TNumberBox* Owner);
    __fastcall ~TNumberBoxWindow();

    int FType;
    TNumberBoxEdit* NumberEdit;
    TNumberBoxScroll* ScrollBar1;
    void __fastcall ChildObjectMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall ChildObjectMouseUp(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y);

    void SetDisplayType(int Type);
    void UpdateDisplay();
};
//---------------------------------------------------------------------------
#endif

