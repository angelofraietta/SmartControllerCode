//## begin module%3C5F56DE030D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C5F56DE030D.cm

//## begin module%3C5F56DE030D.cp preserve=no
//	Angelo Fraietta
//## end module%3C5F56DE030D.cp

//## Module: MidiDriver%3C5F56DE030D; Pseudo Package specification
//## Subsystem: MidiDriver%3CB215CA01F1
//## Source file: c:\develop\MidicontrollerPatchEditor\mididriver\mididriver.h

#ifndef mididriver_h
#define mididriver_h 1

//## begin module%3C5F56DE030D.additionalIncludes preserve=no
//## end module%3C5F56DE030D.additionalIncludes

//## begin module%3C5F56DE030D.includes preserve=yes
//## end module%3C5F56DE030D.includes

#include "iodata.h"
//## begin module%3C5F56DE030D.additionalDeclarations preserve=yes
#include "equeue.h"
//## end module%3C5F56DE030D.additionalDeclarations


//## begin MidiDriver%3C5F56DE030D.preface preserve=yes
//## end MidiDriver%3C5F56DE030D.preface

//## Class: MidiDriver%3C5F56DE030D; Abstract
//## Category: MidiDriver%3C588B4A020C
//## Subsystem: MidiDriver%3CB215CA01F1
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class MidiDriver 
{
  //## begin MidiDriver%3C5F56DE030D.initialDeclarations preserve=yes
  //## end MidiDriver%3C5F56DE030D.initialDeclarations

  public:
    //## Destructor (generated)
      virtual ~MidiDriver();


    //## Other Operations (specified)
      //## Operation: close%1012864645
      //	closes device
      virtual bool close () = 0;

      //## Operation: open%1012864644
      //	opens device.
      virtual bool open (int device_num, 	// The device number required by hardware. This value is
      	// the the device number in the hardware
      int device_id = -1	// Index that the device will be identified as the driver.
      	// -1 signifies that the device_num is used
      ) = 0;

      //## Operation: isEmpty%1014585200
      bool isEmpty () const;

      //## Operation: GetDeviceNum%1018564232
      //	Rteurns the Device Number
      int GetDeviceNum () const;

    // Additional Public Declarations
      //## begin MidiDriver%3C5F56DE030D.public preserve=yes
      //## end MidiDriver%3C5F56DE030D.public

  protected:
    //## Constructors (specified)
      //## Operation: MidiDriver%1012864652
      //	Constructor which defines queue size
      MidiDriver (int queue_size);


    //## Other Operations (specified)
      //## Operation: DequeData%1012859308
      //	Removes and retrieves item from Queue
      bool DequeData (IOData* item);

      //## Operation: EnqueData%1012859307
      //	Adds data item to queue
      bool EnqueData (IOData item);

    // Data Members for Class Attributes

      //## Attribute: _device_num%3C6345DB0061
      //	Handle obtained during Open Function
      //## begin MidiDriver::_device_num%3C6345DB0061.attr preserve=no  protected: int {UA} -1
      int _device_num;
      //## end MidiDriver::_device_num%3C6345DB0061.attr

    // Additional Protected Declarations
      //## begin MidiDriver%3C5F56DE030D.protected preserve=yes
      //## end MidiDriver%3C5F56DE030D.protected

  private:
    // Additional Private Declarations
      //## begin MidiDriver%3C5F56DE030D.private preserve=yes
      //## end MidiDriver%3C5F56DE030D.private

  private: //## implementation
    // Data Members for Associations

      //## Association: MidiDriver::DataQueue%3C5F592B0242
      //## Role: MidiDriver::pData%3C5F592B0244
      //## begin MidiDriver::pData%3C5F592B0244.role preserve=no  public: IOData { -> 0..nVHN}
      sm_str::e_static_queue<IOData> pData;
      //## end MidiDriver::pData%3C5F592B0244.role

    // Additional Implementation Declarations
      //## begin MidiDriver%3C5F56DE030D.implementation preserve=yes
      //## end MidiDriver%3C5F56DE030D.implementation

};

//## begin MidiDriver%3C5F56DE030D.postscript preserve=yes
//## end MidiDriver%3C5F56DE030D.postscript

// Class MidiDriver 

inline MidiDriver::MidiDriver (int queue_size)
  //## begin MidiDriver::MidiDriver%1012864652.hasinit preserve=no
      : _device_num(-1), pData(queue_size)
  //## end MidiDriver::MidiDriver%1012864652.hasinit
  //## begin MidiDriver::MidiDriver%1012864652.initialization preserve=yes
  //## end MidiDriver::MidiDriver%1012864652.initialization
{
  //## begin MidiDriver::MidiDriver%1012864652.body preserve=yes
  //## end MidiDriver::MidiDriver%1012864652.body
}


inline MidiDriver::~MidiDriver()
{
  //## begin MidiDriver::~MidiDriver%.body preserve=yes
  //## end MidiDriver::~MidiDriver%.body
}



//## Other Operations (inline)
inline bool MidiDriver::DequeData (IOData* item)
{
  //## begin MidiDriver::DequeData%1012859308.body preserve=yes
  bool ret = false;

  if (!pData.empty())
  {
	  *item =  pData.top();
  	pData.pop();
    ret = true;
  }
  return ret;
  //## end MidiDriver::DequeData%1012859308.body
}

inline bool MidiDriver::EnqueData (IOData item)
{
  //## begin MidiDriver::EnqueData%1012859307.body preserve=yes
   return pData.push(item);
  //## end MidiDriver::EnqueData%1012859307.body
}

inline bool MidiDriver::isEmpty () const
{
  return pData.empty();

  //## begin MidiDriver::isEmpty%1014585200.body preserve=yes
  //## end MidiDriver::isEmpty%1014585200.body
}

inline int MidiDriver::GetDeviceNum () const
{
  return _device_num;

  //## begin MidiDriver::GetDeviceNum%1018564232.body preserve=yes
  //## end MidiDriver::GetDeviceNum%1018564232.body
}

//## begin module%3C5F56DE030D.epilog preserve=yes
//## end module%3C5F56DE030D.epilog


#endif
