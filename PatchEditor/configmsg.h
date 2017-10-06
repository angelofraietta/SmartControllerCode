#ifndef CONFIGMSG_H
#define CONFIGMSG_H

typedef unsigned char byte;

typedef struct
{
  byte index;
  byte status;
  byte data1;
  byte data2;
  byte data3;
} STR_CONFIG;

#define CONFIG_SPACE  4 // indexes between configurations
enum StatusIndex {eNoteOff, eNoteOn, ePolyphonicPressure, eControlChange,
                  eProgramChange, eChannelPressure, ePitchBend};



#endif
