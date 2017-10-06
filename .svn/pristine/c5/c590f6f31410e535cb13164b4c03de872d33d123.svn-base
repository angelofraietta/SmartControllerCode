//---------------------------------------------------------------------------
#ifndef ShellDisplayParamH
#define ShellDisplayParamH
#include <vcl>
#include <vector>
#include <fstream.h>
#include "Typedefs.h"
#include "interfacetypes.h"

#define SHELL_PARAM "ShellDisplayParameter"
#define LINE_PARAM "LineDisplayParameter"
class TComment;
class PresentationQuestion;

class DisplayParam
{
  public:
    DisplayParam (PresentationQuestion* engine): _engine (engine){}
    PresentationQuestion* GetCurrentEngine () {return _engine;}
  private:
    PresentationQuestion* _engine;
};

class ShellDisplayParam: public DisplayParam
{
public:
    ShellDisplayParam(PresentationQuestion* engine);
    unsigned Left, Top, Width, Height;
    unsigned Tag;//extra value if required by derived types
    bool Visible;
    P_BASESHELL pObject;

    ofstream& Save(ofstream& OutFile);
    void Restore(P_PATCH ParentPatch, const char* szCursor);
};

class LineDisplayParam : public DisplayParam
{
public:
    LineDisplayParam(PresentationQuestion* engine);
    std::vector <TPoint> Points;
    bool Visible;
    P_CONNECTOR pCon;

    //these parameters only used when streaming
    unsigned InletBaseIndex, OutletBaseIndex;
    unsigned InletNum, OutletNum;
    ofstream& Save(ofstream& OutFile);
    void Restore(P_PATCH ParentPatch, const char* szCursor);
};

class CommentDisplayParam: public DisplayParam
{
public:
    CommentDisplayParam(PresentationQuestion* engine);
    unsigned Left, Top, Width, Height;
    unsigned Tag;//extra value if required by derived types
    bool Visible;
    AnsiString CommentText;

    ofstream& Save(ofstream& OutFile);
    void Restore(const char* szCursor);
    TComment* pComment;
};
//---------------------------------------------------------------------------
#endif
