//---------------------------------------------------------------------------
#ifndef SysexWriterH
#define SysexWriterH

typedef unsigned char byte;

class MidiOutputDriver;
class SysexWriter
{
  private:
    byte _sysexbuf [1024];
  public:
    SysexWriter();
    ~SysexWriter();

   bool WriteSysexData (unsigned device, const byte* buf, unsigned buflen);
};
//---------------------------------------------------------------------------
#endif
 