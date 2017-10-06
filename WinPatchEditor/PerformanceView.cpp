//---------------------------------------------------------------------------
#include <vcl.h>
#include <map>
#include "IdentityHook.h"
#pragma hdrstop

#include "PerformanceView.h"
#include "viewquestion.h"
#include "ViewFormUnit.h"

const char* TPerformanceView::szStartViewId  = "<VIEW>";
const char* TPerformanceView::szStartConId    = "<CON>";
const char* TPerformanceView::szStartCommentId = "<COM>";
const char* TPerformanceView::szEndViewId      = "<ENDVIEW>";

//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TPerformanceView::TPerformanceView(TBaseShellHook* Owner)
:TComponent(Owner), pViewNode(NULL), pViewForm(NULL), initialised(false)
{
}

void __fastcall TPerformanceView::Display()
{
  TCursor last_cursor = Screen->Cursor;
  Screen->Cursor = crHourGlass;
  if (!initialised)
  {
    // then we have to load the parameters from the engine
    P_PATCH dwpPatch = (P_PATCH) (((TBaseShellHook*)Owner)->GetHook());
    unsigned view_num = pViewNode->Index;
    unsigned num_objects =  ViewQuestion::GetNumViewObjects(GetCurrentEngine(), dwpPatch, view_num);

    for (unsigned i = 0; i <  num_objects; i++)
    {
      // load each object parameter
      ShellDisplayParam NewObject(GetCurrentEngine());
      if (ViewQuestion::GetViewObjectDisplayParams(GetCurrentEngine(), dwpPatch, view_num, i,
        &NewObject.pObject, &NewObject.Top, &NewObject.Left, &NewObject.Height, &NewObject.Width, &NewObject.Tag))
        {
          Add(NewObject);
        }


    }
    initialised = true;
  }

    if(!pViewForm)
      {
      pViewForm = new TViewForm(this, (P_PATCH)(((TBaseShellHook*)Owner)->GetHook()));
      pViewForm->FormStyle = fsMDIChild;
      }
    pViewForm->Caption = String("Performance View: " + ViewName);
    pViewForm->LoadView();
    pViewForm->Show();
    pViewForm->Top = GetPatchForm()->Top;
    pViewForm->Height = GetPatchForm()->Height;
    pViewForm->Left = GetPatchForm()->Left + GetPatchForm()->Width;

  Screen->Cursor = last_cursor;
}

void TPerformanceView::SaveView()
{
  if (initialised)
  {
   if(pViewForm)
   {
      pViewForm->StoreView();
   }

    // then we have to load the parameters from the engine
    P_PATCH dwpPatch = (P_PATCH) (((TBaseShellHook*)Owner)->GetHook());

    unsigned view_num = pViewNode->Index;

    ViewQuestion::ClearView(GetCurrentEngine(), dwpPatch, view_num);

    for (unsigned i = 0; i <  ObjectsList.size(); i++)
    {
      // load each object parameter
      ShellDisplayParam& DisplayObject = ObjectsList[i];
      ViewQuestion::AddViewObject(GetCurrentEngine(),
            dwpPatch, view_num,
            DisplayObject.pObject, DisplayObject.Top,
            DisplayObject.Left, DisplayObject.Height,
            DisplayObject.Width, DisplayObject.Tag);


    }
  }



}

void TPerformanceView::ClearView()
{
    ObjectsList.erase(ObjectsList.begin(), ObjectsList.end());
    ConnectorsList.erase(ConnectorsList.begin(), ConnectorsList.end());
    CommentList.erase(CommentList.begin(), CommentList.end());
}

void TPerformanceView::Add (const ShellDisplayParam& NewObject)
{
    ObjectsList.push_back(NewObject);
}

void TPerformanceView::Add (const CommentDisplayParam& NewComment)
{
    CommentList.push_back(NewComment);
}

void TPerformanceView::Add (const LineDisplayParam& NewConnector)
{
    ConnectorsList.push_back(NewConnector);
}

TPatchForm* TPerformanceView::GetPatchForm()
{
    return ((TBaseShellHook*)Owner)->GetPatchForm();
}

void TPerformanceView::SetViewName(const String& Name)
{
    ViewName = Name;
    const char* view_name = ViewName.c_str();
    if(pViewForm)
        pViewForm->Caption = String("Performance View: " + ViewName);

    P_PATCH dwpPatch = (P_PATCH) (((TBaseShellHook*)Owner)->GetHook());
    ViewQuestion::SetViewName(GetCurrentEngine(), dwpPatch, pViewNode->Index, view_name);
}

#if 0
ofstream& TPerformanceView::Save(ofstream& OutFile)
{
  unsigned size;
   //save open form
   if(pViewForm)
      pViewForm->StoreView();

   OutFile<<szStartViewId<<endl;
   OutFile<<ViewName.c_str()<<endl;

   //OutFile<<START_OBJECT_ID<<endl;
   size = ObjectsList.size();
   for(unsigned i = 0; i < size; i++)
      ObjectsList[i].Save(OutFile);

   size = ConnectorsList.size();

   if (size)
   {
     OutFile<<szStartConId<<endl;
     for(unsigned i = 0; i < size; i++)
        ConnectorsList[i].Save(OutFile);
   }

   size = CommentList.size();
   if (size)
   {
     OutFile<<szStartCommentId<<endl;
     for(unsigned i = 0; i < size; i++)
        CommentList[i].Save(OutFile);
   }

   OutFile<<szEndViewId<<endl;

   return OutFile;
}

ifstream& TPerformanceView::Restore(ifstream& InFile, int FileType)
{
   char Buf [MAX_NAME_LEN +1];
   if(InFile.getline(Buf, MAX_NAME_LEN).eof())
      return InFile;

   ViewName = String(Buf);


   P_PATCH pPatch = ((TBaseShellHook*)Owner)->GetHook();

   //get the number of Shell Params
   if(InFile.getline(Buf, MAX_NAME_LEN).eof())
      return InFile;

 /*  if (FileType <= 3)
   {
     unsigned NumObjects = (unsigned)atoi(Buf);

     for (unsigned i = 0; i < NumObjects; i++)
        {
        if(InFile.getline(Buf, MAX_NAME_LEN).eof())
          return InFile;

        ShellDisplayParam NewObject (GetCurrentEngine());
        NewObject.Restore(pPatch, Buf);
        ObjectsList.push_back(NewObject);
        }
     //get Line details
     if(InFile.getline(Buf, MAX_NAME_LEN).eof())
        return InFile;

     NumObjects = (unsigned)atoi(Buf);

     for (unsigned i = 0; i < NumObjects; i++)
        {
         if(InFile.getline(Buf, MAX_NAME_LEN).eof())
            return InFile;
        LineDisplayParam NewObject(GetCurrentEngine());
        NewObject.Restore(pPatch, Buf);
        ConnectorsList.push_back(NewObject);
        }

     if(FileType <= 2)
        {
        return InFile;
        }

     if(InFile.getline(Buf, MAX_NAME_LEN).eof())
        return InFile;

     NumObjects = (unsigned)atoi(Buf);
     for (unsigned i = 0; i < NumObjects; i++)
        {
         if(InFile.getline(Buf, MAX_NAME_LEN).eof())
            return InFile;
        CommentDisplayParam NewObject(GetCurrentEngine());
        NewObject.Restore(Buf);
        CommentList.push_back(NewObject);
        }
     } // end type <=2
   else
   */ {
    // test for Connector Start, comment start or end view. If !, read object
    while (strcmp (Buf, szStartConId)
    && strcmp (Buf, szStartCommentId)
    && strcmp (Buf, szEndViewId)) // ! the same
    {
      ShellDisplayParam NewObject(GetCurrentEngine());
      NewObject.Restore(pPatch, Buf);
      ObjectsList.push_back(NewObject);

      if(InFile.getline(Buf, MAX_NAME_LEN).eof())
        return InFile;
    }// end while ! szStartConId

    if (!strcmp (Buf, szStartConId))
    {
      // read  Connectors
      if(InFile.getline(Buf, MAX_NAME_LEN).eof())
        return InFile;
      // test for comment start or end view.
      while (strcmp (Buf, szStartCommentId)
      && strcmp (Buf, szEndViewId)) // ! the same
      {
      //Read Connectors
        LineDisplayParam NewObject(GetCurrentEngine());
        NewObject.Restore(pPatch, Buf);
        ConnectorsList.push_back(NewObject);

        if(InFile.getline(Buf, MAX_NAME_LEN).eof())
          return InFile;
      } //end while ! szStartCommentId
    } // we are now past connectors

    if (!strcmp (Buf, szStartCommentId))
    {
      // Read Comments
      if(InFile.getline(Buf, MAX_NAME_LEN).eof())
        return InFile;
      while (strcmp (Buf, szEndViewId)) // ! the same
      {
        CommentDisplayParam NewObject(GetCurrentEngine());
        NewObject.Restore(Buf);
        CommentList.push_back(NewObject);

        if(InFile.getline(Buf, MAX_NAME_LEN).eof())
          return InFile;
      } // end while !szEndViewId
    }
   }
   return InFile;
}
#endif

void TPerformanceView::RemoveObject(P_BASESHELL pObject)
{
   bool Found = false;
   for (unsigned i = 0; i < ObjectsList.size() && !Found; i++)
      {
      if(ObjectsList[i].pObject == pObject)
         {
         Found = true;
         ObjectsList.erase(&ObjectsList[i]);
         }
      }
}

void TPerformanceView::RemoveConnector(P_CONNECTOR pCon)
{
   bool Found = false;
   for (unsigned i = 0; i < ConnectorsList.size() && !Found; i++)
      {
      if(pCon == ConnectorsList[i].pCon)
         {
         Found = true;
         ConnectorsList.erase(&ConnectorsList[i]);
         }
      }
}

void TPerformanceView::RemoveComment(TComment* pComment)
{
   bool Found = false;
   for (unsigned i = 0; i < CommentList.size() && !Found; i++)
      {
      if(pComment == CommentList[i].pComment)
         {
         Found = true;
         CommentList.erase(&CommentList[i]);
         }
      }
}

bool __fastcall TPerformanceView::CanAdd (P_BASESHELL pObject)
{
   if(pViewForm)
      return (pViewForm->pPatch == IdentityQuestion::GetParent(GetCurrentEngine(), pObject)
            && !pViewForm->ObjectMap.count(pObject));
   else
      {
      bool Found = false;
      for (unsigned i = 0; i < ObjectsList.size() && !Found; i++)
         {
         if(pObject == ObjectsList[i].pObject)
            Found = true;
         }

      return IdentityQuestion::GetParent(GetCurrentEngine(), pObject)== ((TBaseShellHook*)Owner)->GetHook()
            && !Found;
      }
}

bool __fastcall TPerformanceView::AddObject(P_BASESHELL pObject)
{
   if(pViewForm)
      {
      TBaseShellHook* pObjectHook = GetPatchForm()->GetBaseShellHook(pObject);
      return (pViewForm->AddObject(pObjectHook));
      }
   else
      {
      ShellDisplayParam NewObject(GetCurrentEngine());
      NewObject.pObject = pObject;
      ObjectsList.push_back(NewObject);
      return true;
      }
}

PresentationQuestion* TPerformanceView::GetCurrentEngine ()
{
  return GetPatchForm()->GetCurrentEngine ();
}
