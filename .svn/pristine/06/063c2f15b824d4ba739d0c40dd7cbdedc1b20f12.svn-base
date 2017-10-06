
// function definititions within Identity class
#include "stdafx.h"

#include <string.h>
#include "control.h"
#include "eventmessagequeue.h"
#include "identityanswer.h"

const char* Identity::StartIdBlock = "ID"; // Text for Start Of Id Block
const char* Identity::EndBlock = "ENDBLK"; // text for End of Id Block


const char* NameOperator = "NAM";
const char* CommentOperator = "COM";

const unsigned Identity::RestoreInputBufferSize = 1024;

char Identity::RestoreInputBuffer[Identity::RestoreInputBufferSize];

Identity::Identity (Patch* parent, const char* Name,
										 const char* Comment):IsModified(false), pParent (parent)
{
  char* NewName = new char[strlen(Name) + 1];
  if (NewName)
    {
      strcpy (NewName, Name);
      szName = NewName;
    }

  char* NewComment = new char[strlen(Comment) + 1];
  if (NewComment)
    {
      strcpy (NewComment, Comment);
      szComment = NewComment;
    }
  IdentityAnswer::AddIdentity (this);
}

Identity::~Identity()
{
  if (szName)
    delete []szName;
  if (szComment)
    delete [] szComment;

  IdentityAnswer::RemoveIdentity (this);
}

bool Identity::SetName (const char* Name)
{
	bool ret = false;
  //set modified flag
  SetModified(true);
  //clear existing memory for name
  // make get memory for new name
  char* NewName = new char[strlen(Name) + 1];
  if (NewName)
    {
    if (szName)  // delete the old one
      delete[]szName;

      strcpy (NewName, Name);
      szName = NewName;
			ret = true;
    }
	return ret;
}


bool Identity::SetComment (const char* Comment)
{
	bool ret = false;
  //set modified flag
  SetModified(true);

  // get more memory
  char* NewComment = new char[strlen(Comment) + 1];
  if (NewComment)
    {
    //clear existing memory
    if (szComment)
      delete []szComment;

      strcpy (NewComment, Comment);
      szComment = NewComment;
			ret = true;
    }
	return ret;
}

void Identity::SaveID(FILE* fp)
{
  if ((strlen(szName)) || (strlen (szComment)))
  {
   	// save Id Block
	  fprintf (fp, "%s\r\n", StartIdBlock);

    if (strlen(szName))
		{
      fprintf (fp, "%s %s\r\n", NameOperator, szName);
    }

    if (strlen(szComment))
		{
      fprintf (fp, "%s %s\r\n", CommentOperator, szComment);
    }

  fprintf (fp, "%s\r\n", EndBlock);
  }
  //clear modified flag
  IsModified = false;
}



bool Identity::RestoreID(FILE* infile)
{
	// restore name and comment
	bool complete = false;
	Readline (infile, RestoreInputBuffer, RestoreInputBufferSize);

  do
  {
  	char* cursor = RestoreInputBuffer;
    char* val;
    
		cursor = Tokenize (&cursor);

    if (!strcmp (cursor, NameOperator))
    {
     	val = cursor + strlen (cursor) + 1;
      SetName (val);
    }

    else if (!strcmp (cursor, CommentOperator))
    {
     	val = cursor + strlen (cursor) + 1;
      SetComment (val);
    }

    else if  (!strcmp (cursor, EndBlock))
    {
    	complete = true;
    }
    else
    {
    	// just read the line
		printf ("Unknown Indentity Command: %s\r\n", cursor);
    }

    if (!complete)
    {
      Readline (infile, RestoreInputBuffer, RestoreInputBufferSize);
    }
  } while (!complete);
  
 return true;
}


void  Identity::Error (error_message_type error_message, const Identity* sender)
{
	EventMessageQueue::VoidError (error_message, sender);
}

void  Identity::Error (error_message_type error_message, const Identity* sender, int param)
{
	EventMessageQueue::IntError (error_message, sender, param);
}

void  Identity::Error (error_message_type error_message, const Identity* sender, double param)
{
	EventMessageQueue::DoubleError (error_message, sender, param);
}

void  Identity::Error (error_message_type error_message, const Identity* sender, const char* param)
{
	EventMessageQueue::StringError (error_message, sender, param);
}

 

bool Identity::GetName (char* buf, unsigned buf_len)const
{
	bool ret = false;
	if (buf)
		{
    	if (strlen(szName))
      {
				strncpy (buf, szName, buf_len -1);
      }
      else
      {
				strncpy (buf, GetType(), buf_len -1);
      }

			buf[buf_len -1] = '\0';
			ret = true;
		}
	return ret;
}


bool Identity::GetComment (char* buf, unsigned buf_len)const
{
	bool ret = false;
	if (buf)
		{
			strncpy (buf, szComment, buf_len - 1);
			buf[buf_len -1] = '\0';
			ret = true;
		}
	return ret;

}


bool Identity::GetIdType (char* buf, unsigned buf_len)const
{
	bool ret = false;
	if (buf)
		{
			strncpy (buf, GetType(), buf_len - 1);
			buf[buf_len -1] = '\0';
			ret = true;
		}
	return ret;

}

bool Identity::GetDefaultAttribute (char* buf, unsigned buf_len)const
{
	bool ret = false;
	if (buf)
		{
			*buf = '\0';
			ret = true;
		}
  UNREFERENCED_PARAMETER(buf_len);
	return ret;
}

char* Identity::Tokenize (char** cursor)
{
  unsigned num_chars_found = 0;

	char* ret = *cursor;
  bool complete = false;

  do
  	{
	  char c = **cursor;
    switch (c)
    {
      case ' ':
      case '\t':

        if (num_chars_found)
          {
          **cursor = '\0';
          complete = true;
          }
        else
          {
          (*cursor)++;
          }

        break;

      case EOF:
      case '\0':
      case '\r':
      case '\n':
      	**cursor = '\0';
        complete = true;
        break;
      default:
      	(*cursor)++;
        num_chars_found++;
    	}

    } while (!complete);
	return ret;
}

bool Identity::Readline (FILE* infile, char* buf, unsigned buf_len)
{
	bool ret = true;
	unsigned i = 0;
  bool complete = false;

  do
  {
  	int c = fgetc(infile);

    switch (c)
    {
		case EOF:
			ret = i > 0;
			// no break so we can complete
		case '\n':
			
			buf [i] = '\0';
			complete = true;
			break;
		case '\r':
			buf [i] = '\0';
			i++;
			break;

		default:
			buf [i] = (char)c;
			i++;
		}
	} while (!complete && i < buf_len);


  // now fill the rest of buffer with Null
  memset (buf + i, 0, buf_len -i);
	return ret;
}

