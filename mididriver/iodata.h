//## begin module%3C689BFB02BC.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C689BFB02BC.cm

//## begin module%3C689BFB02BC.cp preserve=no
//	Angelo Fraietta
//## end module%3C689BFB02BC.cp

//## Module: IOData%3C689BFB02BC; Package specification
//## Subsystem: MidiDriver%3CB215CA01F1
//## Source file: c:\develop\mididriver\iodata.h

#ifndef iodata_h
#define iodata_h 1

//## begin module%3C689BFB02BC.additionalIncludes preserve=no
//## end module%3C689BFB02BC.additionalIncludes

//## begin module%3C689BFB02BC.includes preserve=yes
//## end module%3C689BFB02BC.includes

//## begin module%3C689BFB02BC.declarations preserve=no
//## end module%3C689BFB02BC.declarations

//## begin module%3C689BFB02BC.additionalDeclarations preserve=yes
//## end module%3C689BFB02BC.additionalDeclarations


//## begin IOData%3C58B1AD0035.preface preserve=yes
//## end IOData%3C58B1AD0035.preface

//## Class: IOData%3C58B1AD0035
//## Category: MidiDriver%3C588B4A020C
//## Subsystem: MidiDriver%3CB215CA01F1
//## Persistence: Transient
//## Cardinality/Multiplicity: n

typedef unsigned short IOData;

//## begin IOData%3C58B1AD0035.postscript preserve=yes
//## end IOData%3C58B1AD0035.postscript

//## begin MidiData%3C689C210090.preface preserve=yes
//## end MidiData%3C689C210090.preface

//## Class: MidiData%3C689C210090
//## Category: MidiDriver%3C588B4A020C
//## Subsystem: MidiDriver%3CB215CA01F1
//## Persistence: Transient
//## Cardinality/Multiplicity: n

typedef struct {unsigned char status, data1, data2;} MidiData;

//## begin MidiData%3C689C210090.postscript preserve=yes
//## end MidiData%3C689C210090.postscript

//## begin module%3C689BFB02BC.epilog preserve=yes
//## end module%3C689BFB02BC.epilog


#endif
