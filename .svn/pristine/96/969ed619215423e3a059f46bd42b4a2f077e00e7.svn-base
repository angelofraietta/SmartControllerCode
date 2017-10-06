//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
 
#include "NumberBox.h"
#include "NumberBoxWindowUnit.h"
//#include "Bridge.h"
#include "VCLGLOBFUNC.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TNumberBoxEdit::TNumberBoxEdit(TNumberBoxWindow* Owner)
:TEdit(Owner)
{
   ReadOnly = true;
   Cursor = crArrow;
}

void __fastcall TNumberBoxEdit::OnExit()
{

    //IntMaskEditBox(this);
}

void __fastcall TNumberBoxEdit::MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
      ((TNumberBoxWindow*)Owner)->ChildObjectMouseDown(this, Button, Shift, X, Y);
}

void __fastcall TNumberBoxEdit::MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y)
{
   ((TNumberBoxWindow*)Owner)->ChildObjectMouseUp(this, Button, Shift, X, Y);
}

void TNumberBoxEdit::LoadData()
{
   if(Tag == TNumberBoxWindow::nbwNumber)
      Text = IntToStr(((TNumberBoxWindow*)Owner)->GetNumber());
   else
      {
      //load the Midi Note Name for data
      char Buf[8];
      /*
      NumberToMidi((unsigned)StrToIntDef(NumberStoreGetNumber(
                  ((TNumberBoxWindow*)Owner)->pObject), 128), Buf);
      */                  
      SetTextBuf(Buf);
      }
}

__fastcall TNumberBoxScroll::TNumberBoxScroll(TNumberBoxWindow* Owner)
:TScrollBar(Owner)
{
   LoadData();
}

void TNumberBoxScroll::LoadData()
{
   int CurrentPos = ((TNumberBoxWindow*)Owner)->GetNumber();
   if(Kind == sbHorizontal)
      {
      Max = ((TNumberBoxWindow*)Owner)->GetUpperLimit();
      Min = ((TNumberBoxWindow*)Owner)->GetLowerLimit();
      
      if (CurrentPos <= Min)
        {
        Position = Min;
        return;
        }
      if (CurrentPos >= Max)
        {
        Position = Max;
        return;
        }

      Position = CurrentPos;
      }
   else
      {
      Min = - ((TNumberBoxWindow*)Owner)->GetUpperLimit();
      Max = - ((TNumberBoxWindow*)Owner)->GetLowerLimit();
      if (-CurrentPos <= Min)
        {
        Position = Min;
        return;
        }
      if (-CurrentPos >= Max)
        {
        Position = Max;
        return;
        }


      Position = -CurrentPos;
      }
}
void __fastcall TNumberBoxScroll::MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
   ((TNumberBoxWindow*)Owner)->ChildObjectMouseDown(this, Button, Shift, X, Y);
}


void __fastcall TNumberBoxScroll::MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y)
{
   ((TNumberBoxWindow*)Owner)->ChildObjectMouseUp(this, Button, Shift, X, Y);
}

void __fastcall TNumberBoxScroll::Scroll(TScrollCode ScrollCode, int &ScrollPos)
{
   if(Kind == sbHorizontal)
      ((TNumberBoxWindow*)Owner)->SetNumber (ScrollPos);
   else
      ((TNumberBoxWindow*)Owner)->SetNumber (-ScrollPos);
      
   ((TNumberBoxWindow*)Owner)->Send();
}

__fastcall TNumberBoxWindow::TNumberBoxWindow(TNumberBox* Owner)
    : TWinControl(Owner), ScrollBar1(NULL), NumberEdit(NULL), _nBox(Owner)
{
   Parent = Owner->Parent;
   pObject = Owner->pObject;
   HelpContext = Owner->HelpContext ();
}

__fastcall TNumberBoxWindow::~TNumberBoxWindow()
{
}


void __fastcall TNumberBoxWindow::ChildObjectMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if(Shift.Contains(ssShift))
      {
      ((TNumberBox*)Owner)->MouseDown(Button, Shift, X, Y);
      }
}

void __fastcall TNumberBoxWindow::ChildObjectMouseUp(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
      ((TNumberBox*)Owner)->ChildMouseUp(this, Button, Shift, X, Y);
}


void __fastcall TNumberBoxWindow::MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y)
{
      ((TNumberBox*)Owner)->ChildMouseUp(this, Button, Shift, X, Y);
}


void TNumberBoxWindow::SetDisplayType(int Type)
{
   if(FType == Type)
      return;
   FType = Type;
   
   switch(Type){
      //display no type
      case nbwNone:
         if(NumberEdit)
            {
            delete NumberEdit;
            NumberEdit = NULL;
            }
         if(ScrollBar1)
            {
            delete ScrollBar1;
            ScrollBar1 = NULL;
            }
         break;

      case nbwNumber:
      case nbwMidiNote:
          if(ScrollBar1)
            {
            delete ScrollBar1;
            ScrollBar1 = NULL;
            }
          if(!NumberEdit)
            {
            NumberEdit = new TNumberBoxEdit(this);
            NumberEdit->Parent = this;
            NumberEdit->Align = alClient;
            NumberEdit->HelpContext = ((TNumberBox*) Owner)->HelpContext ();
            }
          NumberEdit->Tag = Type;
          break;

      case nbwVSlider:
      case nbwHSlider:
          if(NumberEdit)
            {
            delete NumberEdit;
            NumberEdit = NULL;
            }
          if(!ScrollBar1)
            {
            ScrollBar1 = new TNumberBoxScroll(this);
            ScrollBar1->Parent = this;

            ScrollBar1->HelpContext = ((TNumberBox*) Owner)->HelpContext ();
            }

          if (Type == nbwVSlider)
            ScrollBar1->Kind = sbVertical;
          else
            ScrollBar1->Kind = sbHorizontal;

          ScrollBar1->Align = alClient;

          break;

      case nbwGuage:
         break;

      default:
         break;
   };

   UpdateDisplay();
}

void TNumberBoxWindow::UpdateDisplay()
{
   if(ScrollBar1)
      ScrollBar1->LoadData();
   if(NumberEdit)
      NumberEdit->LoadData();

}

void TNumberBoxWindow::SetNumber(int new_val)
{
  _nBox->SetNumber(new_val);
}

int TNumberBoxWindow::GetNumber()
{
  return _nBox->GetNumber();
}

int TNumberBoxWindow::GetLowerLimit()
{
  return _nBox->GetLowerLimit();
}

int TNumberBoxWindow::GetUpperLimit()
{
  return _nBox->GetUpperLimit();
}

void TNumberBoxWindow::Send()
{
  _nBox->Send();
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#pragma package(smart_init)
