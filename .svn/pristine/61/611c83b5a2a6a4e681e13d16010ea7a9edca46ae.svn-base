//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("WindowsCommDriver.res");
USEFORM("CommDriver.cpp", Driver);
USEUNIT("..\windowscommport.cpp");
USEUNIT("..\windowscommstream.cpp");
USEUNIT("..\windowsmidiport.cpp");
USEUNIT("..\..\linklayer.cpp");
USEUNIT("..\..\linkprotocol.cpp");
USEUNIT("..\..\crc32.cpp");
USEUNIT("..\..\udpport.cpp");
USEUNIT("..\..\networklayer.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->CreateForm(__classid(TDriver), &Driver);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
