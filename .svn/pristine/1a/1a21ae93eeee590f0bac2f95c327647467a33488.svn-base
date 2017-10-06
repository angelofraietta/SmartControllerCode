#ifndef IDENTITY_H
#define IDENTITY_H

#ifndef _ROSE_ANALYSE
#include <stdio.h>
#endif
// An Identity class that BaseShell and Connector Classes are derived from
// This allows one superclass to give Name, DeviceType, and Commecnt data
class Patch; // forward declaration;

class Identity{
 public:
  Identity (Patch* parent, const char* Name, const char* Comment );
  virtual ~Identity();
  const char* GetName ()const {return szName;}
  const char* GetComment ()const {return szComment;}
  virtual const char* GetType()const = 0;


  int GetModified()const {return IsModified?1:0;}
  virtual void SetModified(bool Modified) {IsModified = Modified;}

	// define functions for objects to call on error
	static void Error (error_message_type error_message, const Identity* sender);
	static void Error (error_message_type error_message, const Identity* sender, int param);
	static void Error (error_message_type error_message, const Identity* sender, double param);
	static void Error (error_message_type error_message, const Identity* sender, const char* param);

  virtual void Save(FILE*) = 0;

  //extract stored ID data
  bool RestoreID(FILE* infile);


  Patch* GetParent(){return pParent;}
  void SetParent(Patch* Parent) {pParent = Parent;}

	virtual bool GetDefaultAttribute (char* buf, unsigned buf_len)const;
	virtual bool SetDefaultAttribute (const char* new_value) {return false;}
	virtual bool CanSave()const {return true;}
  bool SetName (const char*);
  bool SetComment (const char*);

	virtual bool GetName (char* buf, unsigned buf_len)const;
	bool GetComment (char* buf, unsigned buf_len)const;
	bool GetIdType  (char* buf, unsigned buf_len)const;

  static const char *StartIdBlock;
  static const char *EndBlock;

  static const unsigned RestoreInputBufferSize;
  static char RestoreInputBuffer[];
  static char* Tokenize (char** cursor);
  static bool Readline (FILE* infile, char* buf, unsigned buf_len);

 protected:
  Patch* pParent; // 
  bool IsModified;
  char* szName, *szComment; // details about this object
  void SaveID(FILE*);
 private:

};

#endif




