#ifndef TABLEPOINTS_H
#define TABLEPOINTS_H

#ifndef _ROSE_ANALYSE

#include "messagecell.h"

#ifdef _E_STL
typedef sm_str::vector<MessageCell> message_vec;
#else
#include <vector>
typedef std::vector<MessageCell> message_vec;
#endif

#endif

#include "estring.h"   

#ifndef _ROSE_ANALYSE
//using std::vector;
#endif

//The actual table elements
class TablePoints{
 public:
  TablePoints(const char* FileName);
  string Name;
  message_vec ValueTable;
  bool Save();
  bool Save(const char*);
  unsigned NumTables;//the number of tables that reference this
  bool GetModified()const {return Modified;}
  void SetModified(){Modified = true;}
  void Reload();
  double GetHighestValue()const;
  double GetLowestValue()const;
  
  
 private:
  bool Modified;
};

#endif
