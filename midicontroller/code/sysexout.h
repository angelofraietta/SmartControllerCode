#ifndef SYSEX_OUT_H
#define SYSEX_OUT_H

/* Sysex Out module used for Encoding Sysex Messages*/
#pragma inline
void WriteSysexOutData (byte out_byte)
{
	byte control_byte;

	control_byte = EncodeMidiByte (&out_byte);

	if (control_byte)
		{
			WriteOutData (control_byte);
		}
	WriteOutData (out_byte);
} // end WriteSysexOutData


void WriteSysexHeader()
{
  WriteOutData (SYSEX_BEGIN);
  restart_wdt();					
	WriteSysexOutData (SYSEX_ID);
  restart_wdt();					  
	WriteSysexOutData (EQUIPMENT_TYPE);
  restart_wdt();					
	WriteSysexOutData (ReadDeviceId());
  restart_wdt();					
}

#endif

