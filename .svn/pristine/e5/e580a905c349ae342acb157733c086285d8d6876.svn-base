#include "stdafx.h"
#include "control.h"
#include "table.h"
#include "typenames.h"
#include "globals.h"

#define NUM_INLETS 2
#define NUM_OUTLETS 2


TableListType* gOpenTables = new TableListType;

const char*const Table::szType = TABLE_TYPE;
const unsigned Table::NumAccess = Table::eMaxAttribute;
const unsigned Table::NumResetAccess = Table::eMaxResetAttribute;

// define some control messages
static const char*const TABLE_CLEAR = "clear";
static const char*const TABLE_APPEND = "append";
static const char*const TABLE_INSERT = "insert";
static const char*const TABLE_REPLACE = "replace";

// create the default
static Table *reference = new Table (NULL);

const BaseShell* Table::GetReference() const
{
	return reference;
}

const char*const Table::szaInletDetails[NUM_INLETS] = {
  "Index",
  "Value"
};

const char*const Table::szaOutletDetails[NUM_OUTLETS] = {
  "Value",
  "End of Table"
};

const char* Table::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
    return szaInletDetails[InletNumber];
  else
    return NULL;
}

const char* Table::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return szaOutletDetails[OutletNumber];
  else
    return NULL;
}


const Table::pIntFunc  Table::tpIntFunc [NUM_INLETS] = {
  &Table::IndexInlet,
  &Table::ValueInlet
};

const Table::pVoidFunc  Table::tpVoidFunc [NUM_INLETS] = {
  &Table::SendIndex,
  &Table::ValueInlet
};

const Table::pStringFunc  Table::tpStringFunc [NUM_INLETS] = {
  &Table::ControlInlet,
  &Table::ValueInlet
};

const Table::pDoubleFunc  Table::tpDoubleFunc [NUM_INLETS] = {
  NULL,
  &Table::ValueInlet
};

Table::Table(Patch* pParent ,
	     const char* Name, const char* Comment,
	     const char* TableName)
  :BaseShell (pParent, NUM_INLETS,
              NUM_OUTLETS, Name, Comment), iCurrentMode(eReplaceMode)
{
  //see if table exists
  string ThisTableName(TableName);

  bool Found = false;
  for (unsigned i = 0; i < gOpenTables->OpenTables.size() && !Found; i++)
    {
      TablePoints* TestTable = gOpenTables->OpenTables[i];
      if (ThisTableName == TestTable->Name)
				{
					Found = true;
					ThisTable = TestTable; //the pointer values
				}
    }

  if(!Found) //create a new one
    {
      ThisTable = new TablePoints(ThisTableName.c_str());
      gOpenTables->OpenTables.push_back(ThisTable); //add to list of open tables
    }

  ThisTable->NumTables++;//let the table know how many are using it

}

Table::~Table()
{
  ThisTable->NumTables--;
  if(!ThisTable->NumTables) //delete the table
    {
      TablePoints** iter;

      bool Found = false;
      
      for (unsigned i = 0; i < gOpenTables->OpenTables.size() &&!Found; i++)
        {
          iter = &gOpenTables->OpenTables[i];
          if(*iter == ThisTable)
            {
              Found = true;
              gOpenTables->OpenTables.erase(iter);
              delete ThisTable;
              ThisTable = NULL;
            }
        }
    }
}


BaseShell* Table::Create(Patch* pParent)
{
  return new Table(pParent);
}

void Table::IntInlet(unsigned InletNumber, int i)
{
  if ((InletNumber < GetNumInlets())&& (tpIntFunc[InletNumber]))
    (this->*tpIntFunc[InletNumber])(i);
}

void Table::VoidInlet(unsigned InletNumber)
{
  if ((InletNumber < GetNumInlets())&& (tpVoidFunc[InletNumber]))
    (this->*tpVoidFunc[InletNumber])();
}

void Table::DoubleInlet(unsigned InletNumber, double d)
{
  if ((InletNumber < GetNumInlets()) &&(tpDoubleFunc[InletNumber]))
  {
    (this->*tpDoubleFunc[InletNumber])(d);
  }
else
  {
    IntInlet (InletNumber, DoubleToInt(d));
  }
}


void Table::StringInlet(unsigned InletNumber, const char* s)
{
	if ((InletNumber < GetNumInlets())&&(tpStringFunc[InletNumber]))
   	(this->*tpStringFunc[InletNumber])(s);
}

bool Table::SaveTable()
{
  return ThisTable->Save();
}

void Table::DoDefaultAction()
{
	if (GetIndex () >= GetSize())
		{
			CurrentIndex = 0;
		}
	SendIndex();

}

int Table::GetSize()const
{
  return ThisTable->ValueTable.size();
}

int Table::GetValue(unsigned Index)const
{
	int ret = 0;

  if (Index && Index <= ThisTable->ValueTable.size())
  {
  	MessageCell next = ThisTable->ValueTable[Index -1];

    if (next.MsgType == MessageCell::IntType)
    {
      ret = next.ival;
		}
  }

  return ret;
}

void Table::SetPoint(unsigned Index, int Value, bool Insert)
{
  if (Index)
    {
      Index -= 1;
      if (Index > ThisTable->ValueTable.size())
				return;
      //see if adding to last
      if(Index == ThisTable->ValueTable.size())
				Insert = true;
      
      if(Insert)
				ThisTable->ValueTable.insert(&ThisTable->ValueTable[Index], Value);
      else
				ThisTable->ValueTable[Index] = Value;
      
      ThisTable->SetModified();
    }
}

void Table::RemovePoint(unsigned Index)
{
  if (Index && Index <= ThisTable->ValueTable.size())
    {
      ThisTable->ValueTable.erase(&ThisTable->ValueTable[Index]);
      
      ThisTable->SetModified();
    }
}

void Table::SetSize(int iNewSize)
{
  if (iNewSize < 1)
    {
      Error (eInvalidTableSize, this, iNewSize);
      return;
    }
  
  UINT16 NewSize = (UINT16) iNewSize;
	
  if(ThisTable->ValueTable.size() == NewSize)
    return;
  
  if (ThisTable->ValueTable.size() > NewSize)
    {
      ThisTable->ValueTable.erase(ThisTable->ValueTable.begin()+ NewSize,
																	ThisTable->ValueTable.end());
    }
  else
    {
      for(unsigned i = ThisTable->ValueTable.size(); i < NewSize; i++)
				{
					ThisTable->ValueTable.push_back(0);
				}
      ThisTable->SetModified();
    }
}


//operations on table
void Table::SendIndex(int Index)
{
  if((!Index) || ((unsigned)Index > ThisTable->ValueTable.size()))
    return;
  
  MessageCell StoredMessage = ThisTable->ValueTable[(unsigned)Index - 1];

   switch (StoredMessage.MsgType){
      case MessageCell::VoidType:
         tpOutlet[0]->ProduceOutput();
         break;
      case MessageCell::IntType:
         tpOutlet[0]->ProduceOutput(StoredMessage.ival);
         break;
      case MessageCell::DoubleType:
         tpOutlet[0]->ProduceOutput(StoredMessage.dval);
         break;
      case MessageCell::StringType:
         	tpOutlet[0]->ProduceOutput(StoredMessage.sval.c_str());
            break;
      default:
         break;
   };//end case

  SetIndex (Index);
}

void Table::Insert(int Value)
{
  //inserts at current index.
  ThisTable->ValueTable.insert(&ThisTable->ValueTable[CurrentIndex -1], Value);
}


void Table::ChangeTable(const char* NewName)
{
  string NewTableName(NewName);
  if(ThisTable->Name == NewTableName)
    return;
  
  //remove from this table
  ThisTable->NumTables--;
  if(!ThisTable->NumTables) //delete the table
    {
      bool Found = false;
      for(unsigned i = 0; !Found && i < gOpenTables->OpenTables.size(); i++)
				{
					if(gOpenTables->OpenTables[i] == ThisTable)
            {
							Found = true;
							delete ThisTable;
							gOpenTables->OpenTables.erase(&(gOpenTables->OpenTables[i]));
            }
				}
      //      iter = std::find(gOpenTables-<OpenTables.begin(), gOpenTables->OpenTables.end(), ThisTable);
      //      delete (*iter);
      //      gOpenTables->OpenTables.erase(iter);
    }
  
  //now add to new table
  bool Found = false;
  for (unsigned i = 0; i < gOpenTables->OpenTables.size() && !Found; i++)
    {
      TablePoints* TestTable = gOpenTables->OpenTables[i];
      if (NewTableName == TestTable->Name)
				{
					Found = true;
					ThisTable = TestTable; //the pointer values
				}
      
    }
  
  if(!Found) //create a new one
    ThisTable = new TablePoints(NewTableName.c_str());
  
  ThisTable->NumTables++;//let the table know how many are using it
}


unsigned Table::GetNumTables()
{
  return gOpenTables->OpenTables.size();
}

bool Table::GetTableName(unsigned Index, char* buf, unsigned buf_len)
{
	bool ret = false;

  if (gOpenTables->OpenTables.size() > Index)
		{
			strncpy (buf, gOpenTables->OpenTables[Index]->Name.c_str(), buf_len - 1);
			buf[buf_len -1] = '\0';
			ret = true;
		}

	return ret;
}

bool Table::SetIndex(unsigned index)
{
  if(index > ThisTable->ValueTable.size())
  {
    index = ThisTable->ValueTable.size();
  }

  CurrentIndex = index;
  return true;
}


void Table::SetCurrentValue (int new_value)
{
  // the real index is 1 minus the CurrentIndex
  if (!CurrentIndex) CurrentIndex = 1;
  
  unsigned table_index = CurrentIndex - 1;

   if(table_index > ThisTable->ValueTable.size())
    {
     table_index = ThisTable->ValueTable.size();
    }

  //see if at end
  if(table_index == ThisTable->ValueTable.size())
    {
    ThisTable->ValueTable.push_back(new_value);
    }

  else
    {
      ThisTable->ValueTable[table_index] = new_value; //replace value
    }

  ThisTable->SetModified();
}


void Table::IndexInlet(int Index)
{
  if (Index <= 0)
    {
      Error (eInvalidTableSize, this, Index);
      return;
    }

  CurrentIndex = (unsigned)Index;

  Index -= 1;

  unsigned TableSize =  ThisTable->ValueTable.size();
  if((unsigned)Index >= TableSize)
    {
      tpOutlet[1]->ProduceOutput();//output off end of table
      Error(eTableExceeded, this);
      return;
    }
  //see if at end of table
  if((unsigned)Index == TableSize - 1)
    tpOutlet[1]->ProduceOutput(1);//output end of table

  MessageCell Value = ThisTable->ValueTable[(unsigned)Index];
  tpOutlet[0]->ProduceOutput(Value);

}

void Table::ValueInlet(int Value)
{
	MessageCell new_value;

  if (!CurrentIndex) CurrentIndex = 1;

  unsigned table_index = CurrentIndex -1;

  //see if at end
  if(table_index == ThisTable->ValueTable.size() || DoAppend())
  {
    new_value.Store(Value);

    ThisTable->ValueTable.push_back(new_value);
  }
  else
    {
      //see if in insert mode
      if(DoInsert())
      {
        new_value.Store(Value);

				ThisTable->ValueTable.insert(&ThisTable->ValueTable[table_index], new_value);
      }
      else if(table_index > ThisTable->ValueTable.size())
      {
        Error(eInvalidTableIndex, this, (int) CurrentIndex);
        return;
      }      
      else
      {
				ThisTable->ValueTable[table_index].Store (Value); //replace value
      }
    }
  ThisTable->SetModified();
}

void Table::ControlInlet(const char* value)
{
  //printf ("Table Control %s\r\n", value);
  if (strcmp(value, TABLE_CLEAR) == 0)
  {
    ThisTable->ValueTable.clear();
  }
  else if (strcmp(value, TABLE_APPEND)== 0)
  {
    iCurrentMode = eAppendMode;
    //printf ("Table append Mode\r\n");
  }  
  else if (strcmp(value, TABLE_INSERT)== 0)
  {
    iCurrentMode = eInsertMode;
    //printf ("Table insert Mode\r\n");
  }    
  else if (strcmp(value, TABLE_REPLACE)== 0)
  {
    iCurrentMode = eReplaceMode;
  }   
}

void Table::ValueInlet(const char* Value)
{
  if (!CurrentIndex) CurrentIndex = 1;

  unsigned table_index = CurrentIndex -1;

  //see if at end
  if(table_index == ThisTable->ValueTable.size() || DoAppend())
  {
		MessageCell new_value;
    new_value.Store(Value);

    ThisTable->ValueTable.push_back(new_value);
  }
  else
    {
      //see if in insert mode
      if(DoInsert())
      {
      	MessageCell new_value;
        new_value.Store(Value);

				ThisTable->ValueTable.insert(&ThisTable->ValueTable[table_index], new_value);
      }
      else if(table_index > ThisTable->ValueTable.size())
      {
        Error(eInvalidTableIndex, this, (int) CurrentIndex);
        return;
      }
      else
      {
				ThisTable->ValueTable[table_index].Store (Value); //replace value
      }
    }
  ThisTable->SetModified();
}

void Table::ValueInlet()
{
  if (!CurrentIndex) CurrentIndex = 1;

  unsigned table_index = CurrentIndex -1;

  //see if at end
  if(table_index == ThisTable->ValueTable.size() || DoAppend())
  {
		MessageCell new_value;
    new_value.Store();

    ThisTable->ValueTable.push_back(new_value);
  }
  else
    {
      //see if in insert mode
      if(DoInsert())
      {
      	MessageCell new_value;
        new_value.Store();

				ThisTable->ValueTable.insert(&ThisTable->ValueTable[table_index], new_value);
      }
      else if(table_index > ThisTable->ValueTable.size())
      {
        Error(eInvalidTableIndex, this, (int) CurrentIndex);
        return;
      }      
      else
      {
				ThisTable->ValueTable[table_index].Store (); //replace value
      }
    }
  ThisTable->SetModified();
}


void Table::ValueInlet(double Value)
{
  if (!CurrentIndex) CurrentIndex = 1;

  unsigned table_index = CurrentIndex -1;

  //see if at end
  if(table_index == ThisTable->ValueTable.size() || DoAppend())
  {
		MessageCell new_value;
    new_value.Store(Value);

    ThisTable->ValueTable.push_back(new_value);
  }
  else
    {
      //see if in insert mode
      if(DoInsert())
      {
      	MessageCell new_value;
        new_value.Store(Value);

				ThisTable->ValueTable.insert(&ThisTable->ValueTable[table_index], new_value);
      }
      else if(table_index > ThisTable->ValueTable.size())
      {
        Error(eInvalidTableIndex, this, (int) CurrentIndex);
        return;
      }
      else
      {
				ThisTable->ValueTable[table_index].Store (Value); //replace value
      }
    }
  ThisTable->SetModified();
}


float Table::GetHighestValue()const
{
  return ThisTable->GetHighestValue();
}

float Table::GetLowestValue()const
{
  return ThisTable->GetLowestValue();
}


const Table::str_access Table::aAccess[NumAccess] =
{
  {"Index", &Table::Index, &Table::Index},
  {"Value", &Table::CurrentValue, &Table::CurrentValue},
  {"Size", &Table::Size, &Table::Size},
  {"LowestValue", &Table::LowestValue, NULL},
  {"HighestValue", &Table::HighestValue, NULL},
  {"SaveStatus", &Table::SaveTable, &Table::SaveTable},

};



const char* Table::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool Table::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool Table::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;


  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

 
  return ret;
}

const Table::str_access Table::aResetAccess[NumResetAccess] =
{
  {"TableName", &Table::TableName, &Table::TableName}
  
};


const char* Table::GetResetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumResetAccess)
    {
      ret = aResetAccess[index].access_name;
    }
  return ret;
}

bool Table::SetResetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].set_func)
    {
      ret = (this->*aResetAccess [index].set_func) (value);
    }

  return ret;
}

bool Table::GetResetAttribute (unsigned index, char* ret_value, unsigned ret_size)const
{
  bool ret = false;

  if (index < NumResetAccess && aResetAccess [index].get_func)
    {
      ret = (this->*aResetAccess [index].get_func) (ret_value, ret_size);
		}

  return ret;
}

bool Table::Index (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetIndex(), ret, ret_size);
}

bool Table::CurrentValue (char* ret, unsigned ret_size) const
{
  if (GetIndex()  <= GetSize() && GetSize() > 0)
  {
  	MessageCell &val = ThisTable->ValueTable[GetIndex()];

	  return val.GetMessage(ret, ret_size);
  }
  else
  {
    return SMUtility::StrToStr("NIL", ret, ret_size);
  }
}

bool Table::Size (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (GetSize(), ret, ret_size);
}

bool Table::LowestValue (char* ret, unsigned ret_size) const
{
	return SMUtility::FltToStr (GetLowestValue(), ret, ret_size);
}

bool Table::HighestValue (char* ret, unsigned ret_size) const
{
	return SMUtility::FltToStr (GetHighestValue(), ret, ret_size);
}


bool Table::TableName (char* ret, unsigned ret_size) const
{
	bool success = false;

  if (ThisTable)
		{
			success = SMUtility::StrToStr(ThisTable->Name.c_str(), ret, ret_size);
		}

	return success;
}

bool Table::SaveTable (char* ret, unsigned ret_size) const
{
	bool success = false;

  if (ThisTable)
		{
      if (ThisTable->GetModified())
      {
			  success = SMUtility::StrToStr("Needs Saving", ret, ret_size);
      }
      else
      {
			  success = SMUtility::StrToStr("No Save Required", ret, ret_size);
      }

		}

	return success;
}

bool Table::Index (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			ret = SetIndex(SMUtility::StrToInt(new_val));
		}
	return ret;
}

bool Table::CurrentValue (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetCurrentValue (SMUtility::StrToInt(new_val));
      ret = true;
		}
	return ret;
}

bool Table::Size (const char* new_val)
{
	bool ret = false;
	if (SMUtility::IsInt(new_val))
		{
			SetSize(SMUtility::StrToInt(new_val));
			ret = true;
		}
	return ret;
}


bool Table::TableName (const char* new_val)
{
	ChangeTable(new_val);
	return true;
}

bool Table::SaveTable (const char* new_val)
{
	UNREFERENCED_PARAMETER (new_val);
	return SaveTable();

}


