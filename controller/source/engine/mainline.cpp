#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include "ostypes.h"
#include "midi.h"
#include "interfacebridge.h"
#include "control.h"
#include "calculate.h"
#include "typenames.h"
#include "typelist.h"
#include "timer.h"
#include "scheduler.h"
#include "answertask.h"

#define BUFF_LEN 80

void DisplayObjectTypes()
{
#ifndef _HAL_WINDOWS 
  char buff [80];
  for (unsigned i = 0; i < TypeList::NumElements; i++)
    {
      if (TypeList::GetTypeName(i, buff, sizeof(buff)))
        {
          printf ("%s\n", buff);
        }
    } 
#endif
}


void maintask ()
{
#ifndef _NO_STREAM
  char name [BUFF_LEN];
  bool exit = false;


	AnswerTask* pTask = new AnswerTask;
	pTask->startTask ("/dev/ttys1", 0);
//	PresentationQuestion *question = GetCurrentEngine ();

//  P_PATCH pPatch = PatchQuestion::MakeNew (question, "new Patch");
/*  P_BASESHELL pMetro = BaseShellQuestion::Create (question, "Metro", pPatch);
  PatchQuestion::AddBaseShell (question, pPatch, pMetro);
  P_BASESHELL pDisplay = BaseShellCreate ("Display", pPatch);
  PatchAddBaseShell (pPatch, pDisplay);
  P_CONNECTOR pCon = ConnectorCreate();
  ConnectorSetInletBase( pCon,  pDisplay);
  ConnectorSetInletNum( pCon,  0);
  ConnectorSetOutletBase( pCon,  pMetro);
  ConnectorSetOutletNum( pCon,  0);

  if (ConnectorMakeConnection(pCon))
    {
      ConnectorSetParent (pCon, pPatch);
    }

  P_BASESHELL pToggle = BaseShellCreate ("Toggle", pPatch);
  PatchAddBaseShell (pPatch, pToggle);
  pCon = ConnectorCreate();
  ConnectorSetInletBase( pCon,  pMetro);
  ConnectorSetInletNum( pCon,  0);
  ConnectorSetOutletBase( pCon,  pToggle);
  ConnectorSetOutletNum( pCon,  0);

  if (ConnectorMakeConnection(pCon))
    {
      ConnectorSetParent (pCon, pPatch);
    }

  BaseShellReset (pToggle);
  BaseShellSend(pToggle);

  DisplayObjectTypes();

  scanf ("%s",name);

  switch (name[0])
    {
    case 'x':
    case 'X':
      exit = true;
      break;
    default:
      break;
    }
*/
/*
  while (!exit)
    {
      P_BASESHELL pBase =  (BaseShellQuestion::Create(question, name, pPatch));

      if (1)
        {
					char buf [BUFF_LEN];
          PatchQuestion::AddBaseShell (question, pPatch, pBase);
          IdentityQuestion::GetType (question, pBase, buf, BUFF_LEN);
          cout <<"Type"<<buf<<endl;

					bool modified = IdentityQuestion::GetModified (question, pBase);
					cout <<"Modified:"<<modified<<endl;

					// test name
          IdentityQuestion::GetName (question, pBase, buf, BUFF_LEN);
          cout <<"Name"<<buf<<endl;

					IdentityQuestion::SetName (question, pBase,  "new name");
          IdentityQuestion::GetName (question, pBase, buf, BUFF_LEN);
          cout <<"Name"<<buf<<endl;

					// test comment
          IdentityQuestion::GetComment (question, pBase, buf, BUFF_LEN);
          cout <<"Comment"<<buf<<endl;

					IdentityQuestion::SetComment (question, pBase,  "new comment");
          IdentityQuestion::GetComment (question, pBase, buf, BUFF_LEN);
          cout <<"Comment"<<buf<<endl;

					modified = IdentityQuestion::GetModified (question, pBase);
					cout <<"Modified:"<<modified<<endl;

					// test Default Attribute
          IdentityQuestion::GetDefaultAttribute (question, pBase, buf, BUFF_LEN);
          cout <<"Default: "<<buf<<endl;


					unsigned NumAttributes = BaseShellQuestion::GetNumAttributes (question, pBase);
					for (unsigned i = 0; i < NumAttributes; i++)
						{
							BaseShellQuestion::GetAttributeName (question, pBase, i, buf, BUFF_LEN);
							cout <<buf<<": ";
							//IdentityQuestion::SetAttribute (question, pBase, i, "new value");
							BaseShellQuestion::GetAttribute (question, pBase, i, buf, BUFF_LEN);
							cout <<buf<<endl;
						}

				}

			cout <<"Press a key and enter to continue..."<<endl;
      scanf ("%s",name);

			DisplayObjectTypes();
      cout <<"enter an object type (type x to exit) > "<<endl;
      scanf ("%s",name);

      switch (name[0])
        {
        case 'x':
        case 'X':
          exit = true;
          break;
        default:
          break;
        }

    }


	PatchQuestion::Destroy (question, pPatch);
  */
#endif
}







