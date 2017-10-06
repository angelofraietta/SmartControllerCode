#ifndef MSGSTORE_H
#define MSGSTORE_H
 
#include "estring.h"
#include "memorycache.h"

//	make a StoredMessage type
class MessageCell
{
 public:
  enum {VoidType, StringType, IntType, DoubleType};
                                    
  static void* operator new (size_t);
  static void operator delete (void*);

  MessageCell ():MsgType(VoidType) {}
  MessageCell (int i):ival(i), MsgType(IntType){}
  MessageCell (double d):dval(d),MsgType(DoubleType){}
  MessageCell (const char* s):MsgType(StringType), sval (s){}
  
  bool isNumeric()const {return MsgType == IntType || MsgType == DoubleType;}
  
  int MsgType;
  union
  {
    int ival;  // is int
    double dval; // is double
  };
  string sval;// is string
  MessageCell& operator=(const MessageCell&);

  friend MessageCell operator+(const MessageCell &left, const MessageCell &right);

  bool Store() {ClearString ();MsgType = VoidType; return true;}
  bool Store(int);
  bool Store(const char*);
  bool Store(double);

	bool GetMessage  (char* buff, unsigned buff_len) const;
 private:
	void ClearString ();
  static MemoryCache _mem_manager;
};

#endif

