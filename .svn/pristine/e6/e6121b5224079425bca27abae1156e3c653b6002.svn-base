#include <conio.h>
#include <iostream.h>

#include "stdafx.h"
#include "scheduler.h"
extern "C"
{
	void OpenCommPorts ();
  bool OpenMidiInputDevice (unsigned device_num, unsigned device_index);
  bool OpenMidiOutputDevice (unsigned device_num, unsigned device_index);
  void CloseMidiInputDevices ();
  void CloseMidiOutputDevices ();
  void SaveNVRAM(const char* path);
  bool NVRAMIdle();
  void RestoreNVRAM();
}

int main ()
{

  //OpenCommPorts ();
  OpenMidiInputDevice (0, 0);
  //SaveNVRAM("C:\\temp\\tempname\\");
  // RestoreNVRAM();
  while (!NVRAMIdle())
  {
    Sleep (5000);
  }

  cout<<"press any key to finish ..."<<endl;

  getch ();

  return 0;
}

