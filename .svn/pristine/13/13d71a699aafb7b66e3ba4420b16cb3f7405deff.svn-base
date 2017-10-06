//---------------------------------------------------------------------------
#include "MidiInputUnit.h"

void MidiInDriver::processMidiInput()
{
	IOData iodata;

	bool data_valid = ReadData(&iodata);

  while (data_valid)
  {
    _display((unsigned char) (iodata & 0xff));
    data_valid = ReadData(&iodata);
  }


}


