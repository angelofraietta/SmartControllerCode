//conversion function from Number to Midi
#include "stdafx.h"
#include "estring.h"

#include <stdio.h>
#include <map>                           
#include "funcdec.h"
#include "typedefs.h"

using std::map;
#define NUM_NOTE_NAMES 12
//these need only be created once
static const char *const szaNoteNames [NUM_NOTE_NAMES] =
{
  "C",  "C#",  "D",  "D#",
  "E",  "F",   "F#", "G",
  "G#", "A",   "A#", "B"
};


extern "C"  void   NumberToMidi(unsigned NumVal, LPSTR Buf)
{
  if(NumVal > 127)
    {
      strcpy(Buf, "");
      return;
    }
  
  //60 = C3. 3 = 60/12 -2
  char IntBuf [4]; //capable of holding three chars + NULL
  
  //get the note name
  unsigned NoteIndex = NumVal % NUM_NOTE_NAMES;
  const char *const szNoteChar = szaNoteNames[NoteIndex];
  
  //calculate the Octave
  int OctaveSet = NumVal/NUM_NOTE_NAMES -2;
  sprintf(IntBuf, "%d", OctaveSet);
  
  //transfer into buffer
  strcpy(Buf, szNoteChar);
  strcat(Buf, IntBuf);
  
  
}


typedef map<char, int, std::less<char> > TranslationMapType;

TranslationMapType CreateNoteTranlationMap();//forward dec

//define and populate a translation map for the note names
static TranslationMapType NoteNumberMap = CreateNoteTranlationMap();

TranslationMapType CreateNoteTranlationMap()
{
  TranslationMapType  NoteNumber;
  //define the elements and populate
  
  NoteNumber.insert(TranslationMapType::value_type('C',0));
  NoteNumber.insert(TranslationMapType::value_type('c', 0));
  NoteNumber.insert(TranslationMapType::value_type('D', 2));
  NoteNumber.insert(TranslationMapType::value_type('d', 2));
  NoteNumber.insert(TranslationMapType::value_type('E', 4));
  NoteNumber.insert(TranslationMapType::value_type('e', 4));
  NoteNumber.insert(TranslationMapType::value_type('F', 5));
  NoteNumber.insert(TranslationMapType::value_type('f', 5));
  NoteNumber.insert(TranslationMapType::value_type('G', 7));
  NoteNumber.insert(TranslationMapType::value_type('g', 7));
  NoteNumber.insert(TranslationMapType::value_type('A', 9));
  NoteNumber.insert(TranslationMapType::value_type('a', 9));
  NoteNumber.insert(TranslationMapType::value_type('B', 11));
  NoteNumber.insert(TranslationMapType::value_type('b', 11));
  return NoteNumber;
}

TranslationMapType CreateAccidentalTranlationMap();//forward dec

//define and populate a translation map for the note names
static TranslationMapType AccidentalValueMap = CreateAccidentalTranlationMap();

TranslationMapType CreateAccidentalTranlationMap()
{
  TranslationMapType  AccidentalValue;
  //define the elements and populate
  
  AccidentalValue.insert(TranslationMapType::value_type('#',1));
  AccidentalValue.insert(TranslationMapType::value_type('b',-1));
  AccidentalValue.insert(TranslationMapType::value_type('X',2));
  AccidentalValue.insert(TranslationMapType::value_type('x',2));
  return AccidentalValue;
}


extern "C"  bool   MidiToNumber(LPSTR szNoteName, int* Result)
{
  //convert a note Name to a Midi Number
  //the result can be outside the allowable range
  //60 = C3. 3 = 60/12 - 2
  
  int iNoteValue, iAccidentalValue = 0, iOctaveMultiplier;
  
  bool Valid;
  //test the first char
  char* cCursor = szNoteName;
  Valid = NoteNumberMap.count(*cCursor);
  if(!Valid)
    return false;
  iNoteValue = NoteNumberMap[*cCursor];
  
  //test for accidental
  cCursor++;
  while(AccidentalValueMap.count(*cCursor))
    {
      iAccidentalValue = iAccidentalValue + AccidentalValueMap[*cCursor];
      cCursor++;
    }
  
  //test the octave multiplier
  bool ValidInt = Atoi(&iOctaveMultiplier, cCursor);
  if(!ValidInt)
    return false;
  
  iOctaveMultiplier = (iOctaveMultiplier + 2) * NUM_NOTE_NAMES;
  
  *Result = iNoteValue + iAccidentalValue + iOctaveMultiplier;
  
  return true;
}




