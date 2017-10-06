/*********************************************************
Module for storing configuration in Pic EEProm
********************************************************/


//#inline
void WriteConfigByte (int index, byte config_byte)
{

#ifndef _SIMULATE
  restart_wdt();
	write_eeprom (index, config_byte);
  restart_wdt();
#else // let us decode from here
  int x;
  x = index;
#endif
} // end WriteConfigByte


#inline
byte ReadConfigByte (int index)
{
	return read_eeprom (index);
} // end ReadConfigByte
