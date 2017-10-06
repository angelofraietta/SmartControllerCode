#ifndef MIDI_H
#define MIDI_H

/* this structure has been taken from Maximum MIDI */

#pragma pack(1)
typedef struct {
  DWORD	time;		// time in ticks since last event
  BYTE	status;		// status byte of this midi message
  BYTE	data1;		// first data byte of message
  BYTE	data2;		// second data byte of message
  BYTE	data3;		// third data byte, used for tempo changes
} MidiEvent;
#pragma pack()

typedef MidiEvent* LPMIDIEVENT;

#endif

