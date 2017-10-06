
// this module implements the interface between the eeprom driver and the pla
// requires 24lc256.h
 
typedef struct
{
	int reading: 1; // flag to indicate that we are doing an eeprom read
	int bytes_read:7; // counter that cycles back to zero
} str_ext_eeprom;


str_ext_eeprom extprom_read_state;
byte extprom_int_index = 0; // internal EEprom Index

/*
#inline
void InitialiseEEprom()
{
	ResetEEprom();
	extprom_read_state.reading = 0; // clear flag
	extprom_read_state.bytes_read = 0; // we let this cycle back to zero
	extprom_int_index = 0;
}
*/

// return true if more data, false if back at zero
#inline
short ReadIntEEprom(byte* ret_data)
{
	*ret_data = ReadConfigByte (extprom_int_index);
	extprom_int_index++;
	return (extprom_int_index);
}

#inline
void WriteIntEEprom(byte data)
{
	WriteConfigByte (extprom_int_index++, data);
}

/*
#inline 
short EEpromWriteReady()
{
	return CheckCurrentEEpromDevice();
}


short ReadExtEEpromByte (byte* ret_byte)
{
	short ret = false;

	if (extprom_read_state.reading)
		{
			if (extprom_read_state.bytes_read)
				{
					ret = ReadEEprom (ret_byte);
					if (ret)
						{
							extprom_read_state.bytes_read++;
						}
				}
			else //we have cycled back to zero Give them nothing and stop reading
				{
					extprom_read_state.reading = 0;
				}
		}
	else // we were not reading when we first got here but will be now
		{
			ret = ReadEEprom (ret_byte);
			if (ret)
				{
					extprom_read_state.bytes_read++;
					extprom_read_state.reading = 1; // we are reading now
				}
		}
			
	return ret;
} //ReadExtEEpromByte

*/



