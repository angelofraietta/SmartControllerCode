//## begin module%3C5F00A902F5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C5F00A902F5.cm

//## begin module%3C5F00A902F5.cp preserve=no
//	Angelo Fraietta
//## end module%3C5F00A902F5.cp

//## Module: MidiInputDriver%3C5F00A902F5; Package specification
//## Subsystem: MidiDriver%3CB215CA01F1
//## Source file: D:\develop\SmartController\mididriver\midiinputdriver.h

#ifndef midiinputdriver_h
#define midiinputdriver_h 1

//## begin module%3C5F00A902F5.additionalIncludes preserve=no
//## end module%3C5F00A902F5.additionalIncludes

//## begin module%3C5F00A902F5.includes preserve=yes
#include "stdafx.h"
//## end module%3C5F00A902F5.includes

#include "analogueinputvalue.h"
#include "mididriver.h"

class MidiInputSync;

//## begin module%3C5F00A902F5.declarations preserve=no
//## end module%3C5F00A902F5.declarations

//## begin module%3C5F00A902F5.additionalDeclarations preserve=yes
//## end module%3C5F00A902F5.additionalDeclarations


//## begin MidiInputDriver%3C588B9601D9.preface preserve=yes
//## end MidiInputDriver%3C588B9601D9.preface

//## Class: MidiInputDriver%3C588B9601D9; Abstract
//	Class that runs in two threads-- one in context of ISR
//	and the other in context of normal task
//## Category: MidiDriver%3C588B4A020C
//## Subsystem: MidiDriver%3CB215CA01F1
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%41C5D26801E4;AnalogueInputValue { -> }

class MidiInputDriver : public MidiDriver  //## Inherits: <unnamed>%3C5F573D016F
{
  //## begin MidiInputDriver%3C588B9601D9.initialDeclarations preserve=yes
  //## end MidiInputDriver%3C588B9601D9.initialDeclarations

  public:
    //## Destructor (generated)
      virtual ~MidiInputDriver();


    //## Other Operations (specified)
      //## Operation: DataReady%1012451964
      //	Function called by ISR when data is ready at input
      virtual bool DataReady (IOData data) = 0;

      //## Operation: ProcessInputData%1012451967
      //	Processes the enqued data until finished. This is done
      //	in the context of the InputSync task
      void ProcessInputData ();

      //## Operation: create%1012864642
      //	Constructor which defines queue size
      static MidiInputDriver* create (int queue_size, MidiInputSync* driver = NULL);

      //## Operation: ReadData%1012937116
      //	Removes and retrieves item from Queue. Rteuns true if
      //	successful. Is abstract so each subclass can protect its
      //	critical sections
      virtual bool ReadData (IOData* item) = 0;

      //## Operation: PreProcesData%1013549217
      //	Function for processing data within context of thread.
      //	Overloaded for specific hal implimenttaion
      virtual void PreProcesData ();

      //## Operation: PostProcesData%1013549218
      //	Function for processing data within context of thread.
      //	Overloaded for specific hal implimenttaion
      virtual void PostProcesData ();

      //## Operation: ExtDataInput%1031953702
      //	External function that can be used to receive IO Data
      static void ExtDataInput (IOData data);

      //## Operation: NumDevices%1049869257
      //	Returns the number of devices
      static unsigned NumDevices ();

      //## Operation: GetDeviceName%1049869258
      //	Returns the Name of a  device given a device index.
      //	Returns true if successful
      static bool GetDeviceName (unsigned index, char* ret_buf, unsigned buf_len);

      //## Operation: GetAnalogValue%1096433556
      //	Rtuens reference to Analogue Data
      AnalogueInputValue& GetAnalogValue (unsigned channel);

    // Additional Public Declarations
      //## begin MidiInputDriver%3C588B9601D9.public preserve=yes
      //## end MidiInputDriver%3C588B9601D9.public

  protected:
    //## Constructors (specified)
      //## Operation: MidiInputDriver%1012859309
      //	Constructor which defines queue size
      MidiInputDriver (int queue_size, MidiInputSync* driver);

    // Data Members for Class Attributes

      //## Attribute: _ana_values%415A412C031C
      //## begin MidiInputDriver::_ana_values%415A412C031C.attr preserve=no  protected: AnalogueInputValue [16] {UA} 
      AnalogueInputValue  _ana_values[16];
      //## end MidiInputDriver::_ana_values%415A412C031C.attr

    // Additional Protected Declarations
      //## begin MidiInputDriver%3C588B9601D9.protected preserve=yes
      //## end MidiInputDriver%3C588B9601D9.protected

  private:
    // Additional Private Declarations
      //## begin MidiInputDriver%3C588B9601D9.private preserve=yes
      //## end MidiInputDriver%3C588B9601D9.private

  private: //## implementation
    // Data Members for Associations

      //## Association: MidiDriver::<unnamed>%3C588FF6017F
      //## Role: MidiInputDriver::pThread%3C588FF70113
      //## begin MidiInputDriver::pThread%3C588FF70113.role preserve=no  public: MidiInputSync {1 -> 1RFHN}
      MidiInputSync *pThread;
      //## end MidiInputDriver::pThread%3C588FF70113.role

    // Additional Implementation Declarations
      //## begin MidiInputDriver%3C588B9601D9.implementation preserve=yes
      //## end MidiInputDriver%3C588B9601D9.implementation

};

//## begin MidiInputDriver%3C588B9601D9.postscript preserve=yes
//## end MidiInputDriver%3C588B9601D9.postscript

// Class MidiInputDriver 


//## Other Operations (inline)
inline void MidiInputDriver::PreProcesData ()
{
  //## begin MidiInputDriver::PreProcesData%1013549217.body preserve=yes
  //## end MidiInputDriver::PreProcesData%1013549217.body
}

inline void MidiInputDriver::PostProcesData ()
{
  //## begin MidiInputDriver::PostProcesData%1013549218.body preserve=yes
  //## end MidiInputDriver::PostProcesData%1013549218.body
}

//## begin module%3C5F00A902F5.epilog preserve=yes
//## end module%3C5F00A902F5.epilog


#endif
