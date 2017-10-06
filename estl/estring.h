
#ifndef C_STRING_H
#define C_STRING_H

#ifndef _ROSE_ANALYSE
#include <string.h>
#endif

#ifndef _NO_NAMESPACES
namespace sm_str {
#endif
                       
class string
{
 public:
  string (const char* s = NULL);
  string (const string& s);
  ~string(){delete [] s_val;}
  const char* c_str ()const {return s_val;}
  bool operator == (const string& right)const;
  bool operator < (const string& right)const;
	string& operator = (const string& right);
	void purge(){delete []s_val; s_val = NULL;}
	unsigned length()const;
 private:
  char* s_val;
};


#ifdef _DO_OFSTREAM
inline ostream& operator << (ostream& outstream, const string& s)
{
  outstream<<s.c_str();
  return outstream;
}
#endif

inline string::string(const char* s):s_val (NULL)
{
  if (s)
    {
      s_val = new char [strlen (s)+1];
      strcpy (s_val, s);
    }
}


inline string::string(const string& s):s_val (NULL)
{
  if (s.s_val)
    {
      s_val = new char [strlen (s.s_val)+1];
      strcpy (s_val, s.s_val);
    }
}


inline string& string::operator = (const string& s)
{
	
  if (s.s_val)
    {
			delete [] s_val;
      s_val = new char [strlen (s.s_val)+1];
			if (s_val)
				{
					strcpy (s_val, s.s_val);
				}
    }
	return *this;
}

inline bool string::operator == (const string& right)const
{
  bool ret = false;

  if (right.s_val && s_val)
    {
      ret = !strcmp(right.s_val, s_val);
    } 
  return ret;
}

inline bool string::operator < (const string& right)const
{
  bool ret = false;

  if (right.s_val && s_val)
    {
      ret = strcmp(right.s_val, s_val) < 0;
    } 
  return ret;
}

inline unsigned  string::length()const
{
	unsigned ret = 0;

	if (s_val)
		{
			ret = strlen (s_val);
		}
	return ret;
}

#ifndef _NO_NAMESPACES
} // namespace sm_str
#endif

#endif








