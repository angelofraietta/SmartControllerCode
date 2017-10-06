/*******************************************************************
 * Module for encoding and decoding a data stream from transmission
 * through a Midi sysex block
 * The main issue is preventing any bytes with a MSB of 1 from being 
 * transmitted inside a Midi stream.
 *******************************************************************/
#ifndef MIDIDRV_H
#define MIDIDRV_H

// define control characters
#define MIDIDRV_MODMSB 0x01 // the following char must have MSB set
#define MIDIDRV_NOMOD 0x02 // the following char is not a control char

/*****************************************************************************
 * Author: A. Fraietta
 * Function: EncodeMidiByte
 * Purpose:  Determine whether a control character is required for a charcter
 *           And if so, modify the input character and return the control 
 *           char value
 * Input:    char_to_tx - address of char that needs to be transmitted (also Op)
 * Output:   char_to_tx - the new value of character that will be transmitted
 * Returns:  a control char if required, otherwise zero
 ******************************************************************************/
inline BYTE EncodeMidiByte (BYTE *char_to_tx)
{
	BYTE ret;

	if (*char_to_tx & 0x80) // Msb is 1
		{
			*char_to_tx &= 0x7F; // clear MSB
			ret = MIDIDRV_MODMSB;
		}
	else // test if it is a control char
		{
			if (*char_to_tx == MIDIDRV_MODMSB || *char_to_tx == MIDIDRV_NOMOD)
				{
					// set control char to notify that *char_to_tx is not to
					// behave as a control char
					ret = MIDIDRV_NOMOD;
				}
			else
				{
					ret = 0x00;

				}
		}
	return ret;
} // end EncodeMidiByte

/*****************************************************************************
 * Author: A. Fraietta
 * Function: DecodeMidiByte
 * Purpose:  Decodes and modify two input charaters

 * Input:    control_char - control char used to determine mod reqd for current_char
 *           current_char - char that is being tested

 * Output:   control_char - new value for control char used for next current_char
 *           current_char - decoded value of current_char

 * Returns:  true if current_char is an valid (not control) character
 *
 * Notes: using 0x00 in case as it is most common and makes function more efficient
 ******************************************************************************/
inline bool DecodeMidiByte (BYTE *control_char, BYTE *current_char)
{
	bool ret;

	switch (*control_char)
		{
		case 0x00: // place first for efficiency
			if (*current_char == MIDIDRV_MODMSB || *current_char == MIDIDRV_NOMOD)
				{
					ret = false;
					*control_char = *current_char;
				}
			else
				{
					ret = true;
				}
			break;

		case MIDIDRV_MODMSB:
			ret = true;
			*control_char = 0x00; // clear next control char
			*current_char |= 0x80; // set MSB
			break;

		default:
			ret = true;
			*control_char = 0x00; // clear next control char
		} // end select

	return ret;
} // end DecodeMidiByte


#endif

/*****************************************************************************
 * Author: A. Fraietta
 * Function: CalculateMidiTxBufferSize
 * Purpose:  Calculates the size of a buffer to encode

 * Input:    Tx_Buffer- buffer of chars to be transmitted
 *           Buff_size - size of buffer

 * Output:   Nill

 * Returns:  Size of buffer required does not include start and end sysex chars
 *
 * Notes:
 ******************************************************************************/
inline unsigned CalculateMidiTxBufferSize (BYTE *buf, unsigned buf_size)
{
	unsigned ret;
	unsigned i;
	BYTE current_char; // local so we do not modify buff

	ret = 0;

	for (i = 0; i < buf_size; i++)
		{
			current_char = buf[i];

			if (EncodeMidiByte (&current_char))
				{
					ret += 2;
				}
			else
				{
					ret++;
				}
		}
	return ret;

} // end CalculateMidiTxBufferSize
