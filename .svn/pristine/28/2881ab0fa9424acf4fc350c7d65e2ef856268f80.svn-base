#include "stdafx.h"
  
#include "control.h"
#include "typenames.h"
#include "eventmessagequeue.h"
#include "display.h"
#include "presentationanswer.h"
// AnswerTask
#include "answertask.h"


const char*const Display::szInletDetails = "Input";
const char*const Display::szType = DISPLAY_TYPE;


// create the default
static Display *reference = new Display (NULL);

const BaseShell* Display::GetReference() const
{
	return reference;
}


const char* Display::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szInletDetails;
  else
    return NULL;
}

Display::Display(Patch* Parent, const char* Name, const char* Comment)
  :BaseShell (Parent, 1,0,Name,Comment)
{
}

Display::~Display()
{
}

BaseShell* Display::Create(Patch* Parent)
{
  return new Display(Parent);
}


void Display::VoidInlet(unsigned InletNumber)
{
	char message [255];

	sprintf (message, "%s\r\n", GetName());
	DisplayDiags (message);
  UNREFERENCED_PARAMETER (InletNumber);
}



void Display::IntInlet(unsigned InletNumber, int i)
{
	char message [255];

	sprintf (message, "%s %d\r\n", GetName(), i);
	DisplayDiags (message);

  UNREFERENCED_PARAMETER (InletNumber);
}

void Display::DoubleInlet(unsigned InletNumber, double d)
{
	char message [255];

	sprintf (message, "%s %f\r\n", GetName(), d);
	DisplayDiags (message);

  UNREFERENCED_PARAMETER (InletNumber);
}

void Display::StringInlet(unsigned InletNumber, const char* s)
{
	char message [255];

	sprintf (message, "%s %s\r\n", GetName(), s);

	DisplayDiags (message);

  UNREFERENCED_PARAMETER (InletNumber);
}



