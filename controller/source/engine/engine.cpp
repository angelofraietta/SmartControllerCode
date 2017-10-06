//Main for Algoritmic composer engine
#include "stdafx.h"
#include "control.h"
#include "globals.h"
#include "estring.h"
#include "smerror.h"

unsigned wNumInstances = 0;
ErrorUnitType* gErrorUnit;

bool IncreaseInstances()
{
  if(!wNumInstances)
    {
      gErrorUnit = new ErrorUnitType;
      gOpenTables = new TableListType;
    }
  wNumInstances++;
  return true;
}

bool DecreaseInstances()
{
  wNumInstances--;
  if(!wNumInstances)
    {
      delete gErrorUnit;
      delete gOpenTables;
    }
  return true;
}


