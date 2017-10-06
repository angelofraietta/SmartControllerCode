//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"

//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent *Owner)
	: TForm(Owner)
{
  DWORD size, handle ;
  AnsiString app_name =   Application->ExeName;
  size = GetFileVersionInfoSize( app_name.c_str(), &handle);
  if (size)
  {
    int VersionMajor, VersionMinor, VersionRelease, VersionBuild;

    void *buf = malloc( size) ;
    GetFileVersionInfo( Application->ExeName.c_str(), 0, size, buf) ;
    VS_FIXEDFILEINFO *ffip ;
    unsigned ffisize ;
    VerQueryValue( buf, "\\", (void**)&ffip, &ffisize) ;
    VersionMajor = ffip->dwFileVersionMS >> 16 ;
    VersionMinor = ffip->dwFileVersionMS & 0xFFFF ;
    VersionRelease = ffip->dwFileVersionLS >> 16 ;
    VersionBuild = ffip->dwFileVersionLS & 0xFFFF ;
    VersionLabel->Caption = IntToStr(VersionMajor) + AnsiString (".") + IntToStr(VersionMinor)
    + AnsiString (".") + AnsiString(VersionRelease) + AnsiString (".") + AnsiString(VersionBuild);
    free( buf) ;
  }

}
//---------------------------------------------------------------------

