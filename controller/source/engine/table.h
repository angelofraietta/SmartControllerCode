#ifndef TABLE_H
#define TABLE_H

#include "tablepoints.h"
#include "estring.h"


class Table: public BaseShell
{
  friend class TypeList;
 public:
  enum {eIndex, eValue, eSize, eLowestValue, eHighestValue, eSave, eMaxAttribute};
	enum {eTableName, eMaxResetAttribute};

  enum {eReplaceMode, eInsertMode, eAppendMode};
  
  Table(Patch* pParent , const char* Name = "", const char* Comment = "",
	const char* TableName = "");
  ~Table();
  
  static BaseShell* Create(Patch* pParent = NULL);

  const char* GetInletName(unsigned)const;
  const char* GetOutletName(unsigned)const;
  const char* GetType()const {return szType;}
  
  void VoidInlet (unsigned);
  void StringInlet(unsigned, const char*);
  void IntInlet(unsigned, int);
  void DoubleInlet(unsigned, double);

  void Reset(){}
  bool SaveTable();

  bool SetIndex(unsigned index);
  unsigned GetIndex ()const {return CurrentIndex;}

  void SetCurrentValue (int new_value);
  int GetValue(unsigned Index)const;
  
  int GetSize()const;

  float GetHighestValue()const;
  float GetLowestValue()const;
  void SetPoint(unsigned Index, int Value, bool Insert = false);
  
  void SetPoint(unsigned Index, const char* Value, bool Insert = false);
  void SetPoint(unsigned Index, double Value, bool Insert = false);
  void RemovePoint(unsigned Index);
  void SetSize(int NewSize);

	void DoDefaultAction();  
  //operations on table
  void SendIndex(){SendIndex ( GetIndex() );}

  void SendIndex(int);
  void Insert(int);
  void SetMode(int);
  void ChangeTable(const char*);
  
  static unsigned GetNumTables();
  static bool GetTableName(unsigned Index, char* buf, unsigned buf_len);
  bool GetTableModified()const {return ThisTable->GetModified();}
	const BaseShell* GetReference() const;

 protected:
  void IndexInlet(int);
  void ValueInlet(int);
  void ValueInlet(double);
  void ValueInlet(const char*);
  void ValueInlet();
  
  void ControlInlet(const char*);
  
  TablePoints*  ThisTable;

  int iCurrentMode;
  bool DoInsert()const {return iCurrentMode == eInsertMode;}
  bool DoAppend()const {return iCurrentMode == eAppendMode;}
  
  unsigned CurrentIndex;
  
  static const char*const szaInletDetails[];
  static const char*const szaOutletDetails[];
  static const char*const szType;


  // typedefs for inlet functions
  typedef void(Table::*pVoidFunc)();
  typedef void(Table::*pStringFunc)( const char*);
  typedef void(Table::*pIntFunc)( int);
  typedef void(Table::*pDoubleFunc)( double);
  
  static const pVoidFunc tpVoidFunc[];
  static const pStringFunc tpStringFunc[];
  static const pIntFunc tpIntFunc[];
  static const pDoubleFunc tpDoubleFunc[];

  
  // access functions
	static const unsigned NumAccess;
	typedef bool (Table::*pGetFunc)(char* ret, unsigned ret_size) const;
	typedef bool (Table::*pSetFunc)(const char* new_value);
	typedef struct
	{
		const char* access_name;
		pGetFunc get_func;
		pSetFunc set_func;
	} str_access;

  static const str_access aAccess[];

  unsigned GetNumAccess ()const {return NumAccess;}
  const char* GetAccessName (unsigned index)const;
  
  bool SetAttribute (unsigned index, const char* value);
  bool GetAttribute (unsigned index, char* ret_value, unsigned buf_size)const;

	static const unsigned NumResetAccess;
  static const str_access aResetAccess[];
  unsigned GetNumResetAccess ()const {return NumResetAccess;}
  const char* GetResetAccessName (unsigned index)const;

  bool SetResetAttribute (unsigned index, const char* value);
  bool GetResetAttribute (unsigned index, char* ret_value, unsigned buf_size) const;

  bool Index (char* ret, unsigned ret_size) const;
  bool CurrentValue (char* ret, unsigned ret_size) const;
  bool Size (char* ret, unsigned ret_size) const;
  bool LowestValue (char* ret, unsigned ret_size) const;
  bool HighestValue (char* ret, unsigned ret_size) const;
  bool TableName (char* ret, unsigned ret_size) const;
  bool SaveTable (char* ret, unsigned ret_size) const;

  bool Index (const char* new_val);
  bool CurrentValue (const char* new_val);
  bool Size (const char* new_val);

  bool TableName (const char* new_val);
  bool SaveTable (const char* new_val);

};


#endif





