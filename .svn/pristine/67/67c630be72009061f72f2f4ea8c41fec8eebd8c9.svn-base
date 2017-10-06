#include "stdafx.h"
#include "control.h"
#include "identity.h"
#include "tablepoints.h"
#include <stdio.h>
#include <float>

#include "funcdec.h"

#include "fileanswer.h"


#define MAX_LINES_PER_TABLE 10

TablePoints::TablePoints(const char* FileName)
  :Name(FileName),
  NumTables(0),
  Modified(false)
{
  Reload();
}


void TablePoints::Reload()
{
#ifdef _DO_STREAM

	if (strlen(Name.c_str()))
		{
			FILE* InFile;

			//clear the existing table
			ValueTable.erase(ValueTable.begin(), ValueTable.end());

			const DWORD FileBuffLen = 255;
			char FullFileName [FileBuffLen];

			const char* default_dir = FileAnswer::GetDefaultDirName();

      if (default_dir)
      {
        strcpy (FullFileName, default_dir);
      }
      else
      {
        FullFileName [0] = '\0';
      }
			strcat (FullFileName, Name.c_str());

			printf ("Attempt to open %s\r\n", FullFileName);

			InFile = fopen (FullFileName, "r");

			if (InFile)
				{
					printf ("Successful open %s\r\n", FullFileName);
					MessageCell value;
					const unsigned BUF_SIZE = 80;
					char in_buf [BUF_SIZE];

					while(Identity::Readline (InFile, in_buf, BUF_SIZE))
						{
							char* cursor = in_buf;

							cursor = Identity::Tokenize (&cursor);

							while (strlen (cursor))
              {
								value.Store (cursor);
              	ValueTable.push_back(value);

              	cursor = cursor + strlen (cursor) + 1;
								cursor = Identity::Tokenize (&cursor);
              }


						}

					fclose(InFile);
				}
			else
				{
					printf ("Did not open %s\r\n", FullFileName);
				}
		}
#endif
}

bool TablePoints::Save()
{
  return Save(Name.c_str());
}

bool TablePoints::Save(const char* FileName)
{
  bool ret = false;

	if (strlen(Name.c_str()))
		{
			FILE* outfile;

			const DWORD FileBuffLen = 255;
			char FullFileName [FileBuffLen];

			const char* default_dir = FileAnswer::GetDefaultDirName();

      if (default_dir)
      {
        strcpy (FullFileName, default_dir);
      }
      else
      {
        FullFileName [0] = '\0';
      }

			strcat (FullFileName, Name.c_str());

			outfile = fopen (FullFileName, "w");

			if (outfile)
      {
        for (unsigned i = 0; i < ValueTable.size(); i++)
        {
        	MessageCell next =  ValueTable[i];

          char buff[FileBuffLen];
          if (next.GetMessage(buff, FileBuffLen))
          {
        	  fprintf (outfile, "%s \n", buff);
					}
        }

        fclose(outfile);
        ret = true;
      }

    Modified = false;
    }


    return ret;
}

double TablePoints::GetHighestValue()const
{
  if(!ValueTable.size())
    return -DBL_MAX;


  double Value = -DBL_MAX;

  for(unsigned i = 0; i < ValueTable.size(); i++)
  {
    MessageCell next = ValueTable[i];
    if (next.MsgType == MessageCell::IntType)
    {
    	if(next.ival > Value)
      {// make it the largest
        Value = next.ival;
      }
    }
    else if (next.MsgType == MessageCell::DoubleType)
    {
    	if(next.dval > Value)
      {// make it the largest
        Value = next.dval;
      }
    }
  }
  return Value;
}

double TablePoints::GetLowestValue()const
{
  if(!ValueTable.size())
    return DBL_MAX;

  double Value = DBL_MAX;

  for(unsigned i = 0; i < ValueTable.size(); i++)
  {
    MessageCell next = ValueTable[i];
    if (next.MsgType == MessageCell::IntType)
    {
    	if(next.ival < Value) // make it the largest
      {
        Value = next.ival;
      }
    }
    else if (next.MsgType == MessageCell::DoubleType)
    {
    	if(next.dval < Value)
      {// make it the largest
        Value = next.dval;
      }
    }
    
  }

  return Value;
}



