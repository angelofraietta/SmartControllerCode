//---------------------------------------------------------------------------
#ifndef DragLineH
#define DragLineH
class TLineFollow; //forward dec

class TDragLine: public TDragObject
{
public:
    __fastcall TDragLine(TLineFollow* pLine);
    TLineFollow *const pDragLine;
    TPoint* pDragPoint; //of pDragLine
    TForm* ParentForm;
    unsigned wNumPaints;
    TPoint tpStartPoint, tpEndPoint, tpDragPoint; //relative to form
    TCursor __fastcall GetDragCursor(bool Accepted, int X, int Y);
    void DoDrag(TPoint DragPoint);
    void __fastcall Finished(TObject* Target, int X, int Y, bool Accepted);

};
//---------------------------------------------------------------------------
#endif
 