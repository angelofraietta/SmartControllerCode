//---------------------------------------------------------------------------
#pragma hdrstop

#include "ShellDisplayParam.h"
#include "interfacebridge.h"
#define MAX_SHELL_LEN 1024 //max line of data for a shell
#define DEFAULT_SIZE 50

ShellDisplayParam::ShellDisplayParam(PresentationQuestion* engine): DisplayParam(engine), Tag(NULL),
   Left(DEFAULT_SIZE), Top(DEFAULT_SIZE), Width(DEFAULT_SIZE), Height(DEFAULT_SIZE)
{
}

ofstream& ShellDisplayParam::Save(ofstream& OutFile)
{
   P_PATCH ParentPatch = IdentityQuestion::GetParent(GetCurrentEngine(), pObject);
   unsigned Index = PatchQuestion::FindBaseShellPosition(GetCurrentEngine(), ParentPatch, pObject);
   OutFile<<Index<<DELIM<<Left<<DELIM<<Top<<DELIM<<Width<<DELIM
          <<Height<<DELIM<<Visible<<DELIM<<Tag<<DELIM<<'\n';
   return OutFile;
}

void ShellDisplayParam::Restore(P_PATCH ParentPatch, const char* szCursor)
{
   unsigned Index = (unsigned)atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   Left = atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   Top = atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   Width = atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   Height = atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   Visible =  (bool)atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   Tag =  atoi(szCursor);
   //szCursor = szCursor + strlen(szCursor)+1;

   pObject = PatchQuestion::FindBaseShell(GetCurrentEngine(), ParentPatch, Index);

}

LineDisplayParam::LineDisplayParam(PresentationQuestion* engine) :DisplayParam(engine)
{
}

ofstream& LineDisplayParam::Save(ofstream& OutFile)
{
   P_PATCH ParentPatch = IdentityQuestion::GetParent(GetCurrentEngine(), pCon);

   P_BASESHELL OutletBase = ConnectorQuestion::GetOutletBase(GetCurrentEngine(), pCon);
   unsigned OutletBaseIndex = PatchQuestion::FindBaseShellPosition(GetCurrentEngine(), ParentPatch, OutletBase);
   unsigned OutletNum = ConnectorQuestion::GetOutletNum(GetCurrentEngine(), pCon);
   unsigned OutletIndex = BaseShellQuestion::FindOutletConnectorIndex(GetCurrentEngine(), OutletBase, OutletNum, pCon);
   //only outlet needed to define the connector
/*   P_BASESHELL InletBase = ConnectorGetInletBase(pCon);
   unsigned InletIndex = PatchFindBaseShellPosition(ParentPatch, InletBase);
   unsigned InletNum = ConnectorGetInletNum(pCon);
  */
   //save the constant number of objects
   OutFile<<OutletBaseIndex<<DELIM<<OutletNum<<DELIM<<OutletIndex<<DELIM
    /*     <<InletIndex<<DELIM<<InletNum<<DELIM*/
         <<Visible<<DELIM<<Points.size()<<DELIM;
   //now save points
   for(unsigned i = 0; i < Points.size(); i++)
      {
      OutFile<<Points[i].x<<DELIM
              <<Points[i].y<<DELIM;
      }
   //new line to make easier to read
   OutFile<<'\n';
   return OutFile;

}

void LineDisplayParam::Restore(P_PATCH ParentPatch, const char* szCursor)
{
   unsigned OutletBaseIndex = (unsigned)atoi(szCursor);
   P_BASESHELL pOutletBase = PatchQuestion::FindBaseShell(GetCurrentEngine(), ParentPatch, OutletBaseIndex);

   szCursor = szCursor + strlen(szCursor)+1;
   unsigned OutletNum = (unsigned)atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   unsigned OutletIndex = (unsigned)atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   pCon = BaseShellQuestion::GetOutletConnector(GetCurrentEngine(), pOutletBase, OutletNum, OutletIndex);

/*   unsigned InletIndex = (unsigned)atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;
   unsigned InletNum = (unsigned)atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;
  */
   Visible  = (bool)atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   unsigned Size = (unsigned)atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   for (unsigned i = 0; i < Size; i ++)
      {
      TPoint NextPoint;
      NextPoint.x = atoi(szCursor);
      szCursor = szCursor + strlen(szCursor)+1;
      NextPoint.y = (unsigned)atoi(szCursor);
      szCursor = szCursor + strlen(szCursor)+1;
      Points.push_back(NextPoint);
      }
}


CommentDisplayParam::CommentDisplayParam(PresentationQuestion* engine):DisplayParam(engine), pComment(NULL), Tag(NULL),
   Left(DEFAULT_SIZE), Top(DEFAULT_SIZE), Width(DEFAULT_SIZE), Height(DEFAULT_SIZE)
{
}

ofstream& CommentDisplayParam::Save(ofstream& OutFile)
{
   OutFile<<Left<<DELIM<<Top<<DELIM<<Width<<DELIM
          <<Height<<DELIM<<Visible<<DELIM<<Tag<<DELIM<<CommentText.c_str()<<DELIM<<'\n';
   return OutFile;
}

void CommentDisplayParam::Restore(const char* szCursor)
{
   Left = atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   Top = atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   Width = atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   Height = atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   Visible =  (bool)atoi(szCursor);
   szCursor = szCursor + strlen(szCursor)+1;

   Tag =  atoi(szCursor);

   szCursor = szCursor + strlen(szCursor)+1;
   CommentText = AnsiString(szCursor);
   //szCursor = szCursor + strlen(szCursor)+1;

}

//---------------------------------------------------------------------------
#pragma package(smart_init)
