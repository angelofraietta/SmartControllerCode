//---------------------------------------------------------------------------
#ifndef TCommentH
#define TCommentH

class TViewForm; //forward declaration

class TComment: public TLabel
{
public:
  __fastcall TComment(const char* Text, TViewForm* Owner);
  const TViewForm* GetParent()const {return pParent;}
  const AnsiString GetComment(){return Text;}
  static void KillObject(TComment* Victim);
  TPoint GetPosition()const;
protected:
  void __fastcall MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall DoStartDrag(TDragObject* &DragObject);
  void __fastcall DoEndDrag(TObject *Source, int X, int Y);
  void __fastcall DragOver(TObject *Source, int X, int Y, TDragState State, bool &Accept);

      
  static bool GetNewComment(char* buff);
  TViewForm* pParent;
};
//---------------------------------------------------------------------------
#endif
 