#ifndef TYPELIST_H
#define TYPELIST_H

//forward declaration
class BaseShell;
class Patch;

class TypeListElement{
  // a grouping of a class object static functions and variables
  // required for Creating and restoring class object
 public:
  typedef BaseShell* (*pfnCreate)(Patch*);
  
  TypeListElement(const char* Type, pfnCreate pCreate);
  const char* TypeName;
  pfnCreate pCreate;
};


class TypeList{
// provides an array listing of available object types
  // a parallel array of pointers to create these objects
  // and a map to restore class objects
  
 public:
  //find the name of the type at the index
  static bool GetTypeName (unsigned Index, char* ret_val, unsigned buff_len);

  // returns pointer to created object
  static BaseShell* Create (const char* Type, Patch*);

  static const unsigned NumElements;
  static const char* GetTypeName (unsigned index);
  
 protected:
  static const TypeListElement TypeElements [];

};



#endif









