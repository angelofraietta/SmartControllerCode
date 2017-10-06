#ifndef DELTATIME_H
#define DELTATIME_H

unsigned WriteVarLen(register unsigned long value, BYTE* Buff);

DWORD ReadVarLen(BYTE* StartBuff, unsigned* pNumBytesRead);
#endif
