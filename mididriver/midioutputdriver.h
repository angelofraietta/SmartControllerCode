//## begin module%3C5F01180038.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C5F01180038.cm

//## begin module%3C5F01180038.cp preserve=no
//	Angelo Fraietta
//## end module%3C5F01180038.cp

//## Module: MidiOutputDriver%3C5F01180038; Package specification
//## Subsystem: MidiDriver%3CB215CA01F1
//## Source file: C:\develop\WinSmartController\mididriver\midioutputdriver.h

#ifndef midioutputdriver_h
#define midioutputdriver_h 1

//## begin module%3C5F01180038.additionalIncludes preserve=no
//## end module%3C5F01180038.additionalIncludes

//## begin module%3C5F01180038.includes preserve=yes
//#include "evector.h"
//## end module%3C5F01180038.includes

#include "midiinputdriver.h"
#include "filedriver.h"
#include "mididriver.h"
#include "midiutilities.h"
//## begin module%3C5F01180038.declarations preserve=no
//## end module%3C5F01180038.declarations

//## begin module%3C5F01180038.additionalDeclarations preserve=yes
//## end module%3C5F01180038.additionalDeclarations


//## begin MidiOutputDriver%3C5E05CA01BF.preface preserve=yes
//## end MidiOutputDriver%3C5E05CA01BF.preface

//## Class: MidiOutputDriver%3C5E05CA01BF; Abstract
//## Category: MidiDriver%3C588B4A020C
//## Subsystem: MidiDriver%3CB215CA01F1
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3C5F3FAD02B6;MidiUtilities { -> }
//## Uses: <unnamed>%3D8241990287;FileDriver { -> }
//## Uses: <unnamed>%3D825D2201C4;MidiInputDriver { -> }

class MidiOutputDriver : public MidiDriver  //## Inherits: <unnamed>%3C5F57A0003B
{
  //## begin MidiOutputDriver%3C5E05CA01BF.initialDeclarations preserve=yes
  //## end MidiOutputDriver%3C5E05CA01BF.initialDeclarations

  public:
    //## Destructor (generated)
      virtual ~MidiOutputDriver();


    //## Other Operations (specified)
      //## Operation: TxDataReady%1012859306
      //	Function called by IO device to inform driver that it is
      //	ready to receive data. If data is ready, the driver
      //	returns true and places the data that is to be
      //	transmitted into the IOData parameter
      //## Postconditions:
      //	rxData contains the value of the received data
      bool TxDataReady (IOData* io_data = NULL);

      //## Operation: create%1012864640
      //	Constructor which defines queue size
      static MidiOutputDriver* create (int queue_size);

      //## Operation: TransmitMidiData%1013488868
      virtual void TransmitMidiData (const MidiData& midi_data, int output_num = 0	// The Midi Output to go to
      );

      //## Operation: SetTxReady%1017707552
      //	Sets the _tx_ready flag to the value stated
      void SetTxReady (bool ready);

      //## Operation: TransmitMidiMessageByte%1018308378
      //	Transmits Midi Byte to an output
      static void TransmitMidiMessageByte (unsigned char data, 	// The Midi byte to transmit
      int output_num = 0, 	// The Midi Output to go to
      unsigned device = 0);

      //## Operation: TransmitControlVoltage%1018308379
      //	Transmits a variable cv to output
      static void TransmitControlVoltage (unsigned char data_val, int output_num, unsigned device = 0);

      //## Operation: TransmitDigitalVoltage%1018308380
      //	transmits digital CV outputs
      static void TransmitDigitalVoltage (unsigned char data_val, int output_num, unsigned device = 0);

      //## Operation: TransmitMidiDataMessage%1018308381
      static void TransmitMidiDataMessage (const MidiData& midi_data, int output_num = 0, 	// The Midi Output to go to
      unsigned device = 0);

      //## Operation: TransmitIoData%1031946742
      //	Transmits DataIO to an output
      static void TransmitIoData (IOData io_data, 	// The Midi byte to transmit
      int output_num = 0, 	// The Midi Output to go to
      unsigned device = 0);

      //## Operation: NumDevices%1018316747
      //	Returns the Number of Output Devices
      static unsigned NumDevices ();

      //## Operation: GetDeviceName%1049869260
      //	Returns the Name of a  device given a device index.
      //	Returns true if successful
      static bool GetDeviceName (unsigned index, char* ret_buf, unsigned buf_len);

    // Additional Public Declarations
      //## begin MidiOutputDriver%3C5E05CA01BF.public preserve=yes
			bool GetTxReady()const {return _tx_ready;}
      //## end MidiOutputDriver%3C5E05CA01BF.public

  protected:
    //## Constructors (specified)
      //## Operation: MidiOutputDriver%1012859302
      //	Constructor which defines queue size
      MidiOutputDriver (int queue_size);


    //## Other Operations (specified)
      //## Operation: TransmitMidiByte%1012859303
      //	Transmits Midi Byte to an output
      virtual void TransmitMidiByte (unsigned char data, 	// The Midi byte to transmit
      int output_num = 0	// The Midi Output to go to
      ) = 0;

      //## Operation: TransmitCV%1012859304
      //	Transmits a variable cv to output
      virtual void TransmitCV (unsigned char data_val, int output_num) = 0;

      //## Operation: TransmitDigital%1012859305
      //	transmits digital CV outputs
      virtual void TransmitDigital (unsigned char data_val, int output_num) = 0;

    // Data Members for Class Attributes

      //## Attribute: _tx_ready%3C5E08E80126
      //	Flag indicating that the IO device driver is ready to
      //	accept Data immediately. Is set upon return interrupt or
      //	initial open
      //## begin MidiOutputDriver::_tx_ready%3C5E08E80126.attr preserve=no  protected: bool {UAT} false
      volatile bool  _tx_ready;
      //## end MidiOutputDriver::_tx_ready%3C5E08E80126.attr

      //## Attribute: _max_devices%3CB2310200A6
      //## begin MidiOutputDriver::_max_devices%3CB2310200A6.attr preserve=no  protected: static int {VA} 6
      static int _max_devices;
      //## end MidiOutputDriver::_max_devices%3CB2310200A6.attr

    // Data Members for Associations

      //## Association: MidiDriver::<unnamed>%3CB22B7B011A
      //## Role: MidiOutputDriver::_devices%3CB22B7F01B6
      //## begin MidiOutputDriver::_devices%3CB22B7F01B6.role preserve=no  protected: static MidiOutputDriver { -> 0..nUHAN}
      static MidiOutputDriver*  _devices[];
      //## end MidiOutputDriver::_devices%3CB22B7F01B6.role

    // Additional Protected Declarations
      //## begin MidiOutputDriver%3C5E05CA01BF.protected preserve=yes
      //## end MidiOutputDriver%3C5E05CA01BF.protected

  private:
    // Additional Private Declarations
      //## begin MidiOutputDriver%3C5E05CA01BF.private preserve=yes
      //## end MidiOutputDriver%3C5E05CA01BF.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin MidiOutputDriver%3C5E05CA01BF.implementation preserve=yes
      //## end MidiOutputDriver%3C5E05CA01BF.implementation

};

//## begin MidiOutputDriver%3C5E05CA01BF.postscript preserve=yes
//## end MidiOutputDriver%3C5E05CA01BF.postscript

// Class MidiOutputDriver 


//## Other Operations (inline)
inline void MidiOutputDriver::SetTxReady (bool ready)
{
  _tx_ready = ready;

  //## begin MidiOutputDriver::SetTxReady%1017707552.body preserve=yes
  //## end MidiOutputDriver::SetTxReady%1017707552.body
}

//## begin module%3C5F01180038.epilog preserve=yes
//## end module%3C5F01180038.epilog


#endif
