//## begin module%3D823D930073.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D823D930073.cm

//## begin module%3D823D930073.cp preserve=no
//## end module%3D823D930073.cp

//## Module: FileDriver%3D823D930073; Pseudo Package body
//## Subsystem: MidiDriver%3CB215CA01F1
//## Source file: c:\develop\MidicontrollerPatchEditor\mididriver\filedriver.cpp

//## begin module%3D823D930073.additionalIncludes preserve=no
//## end module%3D823D930073.additionalIncludes

//## begin module%3D823D930073.includes preserve=yes
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

//## end module%3D823D930073.includes

#include "filedriver.h"
//## begin module%3D823D930073.additionalDeclarations preserve=yes
static const int MAX_FILES = 2;
static const char* filenames [MAX_FILES] = {"/mnt/hda/NVRAM.DAT", "/mnt/hda/NVRAM2.DAT"};

static const char* hard_drive = "/mnt/hda";

static void ListHardDrive()
{
  DIR *dir;
  struct dirent *ent;
  char dir_buffer [100];

  strcpy (dir_buffer, hard_drive);

	
	if ((dir = opendir(dir_buffer)) == NULL)
		{
			printf ("\r\nUnable to open directory");
		}
	else
		{
			printf ("\r\Refresh Directory %s\r\n", dir_buffer);
			while ((ent = readdir(dir)) != NULL)
				{
					;
				}
			if (closedir(dir) != 0)
				{
					printf("\r\nUnable to close directory");
				}
		}

}
//## end module%3D823D930073.additionalDeclarations


// Class Utility FileDriver 

//## begin FileDriver::_fp%3D823E340377.attr preserve=no  private: static FILE* {UA} 0
FILE* FileDriver::_fp = 0;
//## end FileDriver::_fp%3D823E340377.attr


//## Other Operations (implementation)
bool FileDriver::WriteByte (char data, int file_index)
{
  //## begin FileDriver::WriteByte%1031946743.body preserve=yes
	bool ret = false;

	if (OpenForWrite(file_index))
		{
			ret = (fwrite (&data, 1, 1, _fp));
		}
	return ret;

  //## end FileDriver::WriteByte%1031946743.body
}

bool FileDriver::ReadByte (char* ret_byte, int file_index)
{
  //## begin FileDriver::ReadByte%1031946744.body preserve=yes
	bool ret = false;
  if (OpenForRead(file_index))
		{
			ret = fread(ret_byte, 1, 1, _fp);
		}
	return ret;

  //## end FileDriver::ReadByte%1031946744.body
}

void FileDriver::InitPosition ()
{
  //## begin FileDriver::InitPosition%1031946745.body preserve=yes
	if (_fp)
		{
			fclose (_fp);
			_fp = 0;
			ListHardDrive();
		}


  //## end FileDriver::InitPosition%1031946745.body
}

bool FileDriver::OpenForWrite (int index)
{
  //## begin FileDriver::OpenForWrite%1031946747.body preserve=yes
	if (!_fp)
		{
			if (index < MAX_FILES)
				_fp = fopen (filenames[index], "w+b");
		}
	return (_fp);

  //## end FileDriver::OpenForWrite%1031946747.body
}

bool FileDriver::OpenForRead (int index)
{
  //## begin FileDriver::OpenForRead%1031946748.body preserve=yes
	if (!_fp)
		{
			if (index < MAX_FILES)
				_fp = fopen (filenames[index], "r+b");
		}
	return (_fp);

  //## end FileDriver::OpenForRead%1031946748.body
}

void FileDriver::Flush ()
{
  //## begin FileDriver::Flush%1031953703.body preserve=yes
  if (_fp)
  {
    fflush(_fp);
  }

  //## end FileDriver::Flush%1031953703.body
}

// Additional Declarations
  //## begin FileDriver%3D823D930073.declarations preserve=yes
  //## end FileDriver%3D823D930073.declarations

//## begin module%3D823D930073.epilog preserve=yes
//## end module%3D823D930073.epilog
