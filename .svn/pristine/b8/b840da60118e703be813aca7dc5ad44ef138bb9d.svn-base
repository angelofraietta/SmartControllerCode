//## begin module%41C5D1F60167.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41C5D1F60167.cm

//## begin module%41C5D1F60167.cp preserve=no
//	Angelo Fraietta
//## end module%41C5D1F60167.cp

//## Module: AnalogueInputValue%41C5D1F60167; Pseudo Package specification
//## Subsystem: MidiDriver%3CB215CA01F1
//## Source file: D:\develop\SmartController\mididriver\analogueinputvalue.h

#ifndef analogueinputvalue_h
#define analogueinputvalue_h 1

//## begin module%41C5D1F60167.additionalIncludes preserve=no
//## end module%41C5D1F60167.additionalIncludes

//## begin module%41C5D1F60167.includes preserve=yes
//## end module%41C5D1F60167.includes

//## begin module%41C5D1F60167.additionalDeclarations preserve=yes
#include <stdio.h>
//## end module%41C5D1F60167.additionalDeclarations


//## begin AnalogueInputValue%41C5D1F60167.preface preserve=yes
//## end AnalogueInputValue%41C5D1F60167.preface

//## Class: AnalogueInputValue%41C5D1F60167
//	Contains Cached Analogue Input Values
//## Category: MidiDriver%3C588B4A020C
//## Subsystem: MidiDriver%3CB215CA01F1
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AnalogueInputValue 
{
  //## begin AnalogueInputValue%41C5D1F60167.initialDeclarations preserve=yes
  //## end AnalogueInputValue%41C5D1F60167.initialDeclarations

  public:
    //## Constructors (generated)
      AnalogueInputValue();


    //## Other Operations (specified)
      //## Operation: getAnaVal%1103483502
      //	Returns the addiion of the Upper And Lower Bits
      unsigned getAnaVal () const;

    // Data Members for Class Attributes

      //## Attribute: in_queue%41C5D2090167
      //	state indicating whether the analogue value is in the
      //	queue
      //## begin AnalogueInputValue::in_queue%41C5D2090167.attr preserve=no  public: bool {UT} false
      volatile bool  in_queue;
      //## end AnalogueInputValue::in_queue%41C5D2090167.attr

      //## Attribute: lower_bits%41C5D2090168
      //## begin AnalogueInputValue::lower_bits%41C5D2090168.attr preserve=no  public: unsigned {UT} 0
      volatile unsigned  lower_bits;
      //## end AnalogueInputValue::lower_bits%41C5D2090168.attr

      //## Attribute: upper_bits%41C5D2090177
      //## begin AnalogueInputValue::upper_bits%41C5D2090177.attr preserve=no  public: unsigned {UT} 0
      volatile unsigned  upper_bits;
      //## end AnalogueInputValue::upper_bits%41C5D2090177.attr

    // Additional Public Declarations
      //## begin AnalogueInputValue%41C5D1F60167.public preserve=yes
      //## end AnalogueInputValue%41C5D1F60167.public

  protected:
    // Additional Protected Declarations
      //## begin AnalogueInputValue%41C5D1F60167.protected preserve=yes
      //## end AnalogueInputValue%41C5D1F60167.protected

  private:
    // Additional Private Declarations
      //## begin AnalogueInputValue%41C5D1F60167.private preserve=yes
      //## end AnalogueInputValue%41C5D1F60167.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin AnalogueInputValue%41C5D1F60167.implementation preserve=yes
      //## end AnalogueInputValue%41C5D1F60167.implementation

};

//## begin AnalogueInputValue%41C5D1F60167.postscript preserve=yes
//## end AnalogueInputValue%41C5D1F60167.postscript

// Class AnalogueInputValue 

inline AnalogueInputValue::AnalogueInputValue()
  //## begin AnalogueInputValue::AnalogueInputValue%.hasinit preserve=no
      : in_queue(false), lower_bits(0), upper_bits(0)
  //## end AnalogueInputValue::AnalogueInputValue%.hasinit
  //## begin AnalogueInputValue::AnalogueInputValue%.initialization preserve=yes
  //## end AnalogueInputValue::AnalogueInputValue%.initialization
{
  //## begin AnalogueInputValue::AnalogueInputValue%.body preserve=yes
  //## end AnalogueInputValue::AnalogueInputValue%.body
}



//## Other Operations (inline)
inline unsigned AnalogueInputValue::getAnaVal () const
{
  //## begin AnalogueInputValue::getAnaVal%1103483502.body preserve=yes
  //## end AnalogueInputValue::getAnaVal%1103483502.body

  unsigned short ret = upper_bits & 0x0ff;
  ret = ret << 2;
  unsigned short lower = lower_bits & 0x0ff;
  ret += lower; return ret;
}

//## begin module%41C5D1F60167.epilog preserve=yes
//## end module%41C5D1F60167.epilog


#endif
