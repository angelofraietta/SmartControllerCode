#ifndef GLOBALS_H
#define GLOBALS_H

//static variables           
class ErrorUnitType;//forward dec
extern ErrorUnitType* gErrorUnit;

class TableListType;
class TablePoints;
extern TableListType* gOpenTables;

class TableListType
{
 public:
  sm_ptr::vector <TablePoints*> OpenTables;
};
#endif

