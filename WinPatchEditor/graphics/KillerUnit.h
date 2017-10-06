//---------------------------------------------------------------------------
#ifndef KillerUnitH
#define KillerUnitH
class TKiller:public TDragObject
  {
  public:
    __fastcall TKiller(TObject* Creator);
    void __fastcall Finished(TObject* Target, int X, int Y, bool Accepted);
    virtual TCursor __fastcall GetDragCursor(bool Accepted, int X, int Y);
  protected:
    TObject* Instigator;

  };

class TKillerObject:public TControl
  {
  __property OnStartDrag;
  public:
     __fastcall TKillerObject(TComponent* Owner);
  void __fastcall DoStartDrag(TDragObject* &DragObject);
  };
//---------------------------------------------------------------------------
#endif
 