//## begin module%3AEF6CFB0125.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AEF6CFB0125.cm

//## begin module%3AEF6CFB0125.cp preserve=no
//	Angelo Fraietta
//## end module%3AEF6CFB0125.cp

//## Module: CommStream%3AEF6CFB0125; Package specification
//	Common interface for CommStream and Comm Port
//## Subsystem: link_driver%3D7412070347
//## Source file: c:\develop\Winsmartcontroller\controller\source\link_driver\commstream.h

#ifndef commstream_h
#define commstream_h 1

//## begin module%3AEF6CFB0125.additionalIncludes preserve=no
//## end module%3AEF6CFB0125.additionalIncludes

//## begin module%3AEF6CFB0125.includes preserve=yes
//## end module%3AEF6CFB0125.includes

//## begin module%3AEF6CFB0125.declarations preserve=no
//## end module%3AEF6CFB0125.declarations

//## begin module%3AEF6CFB0125.additionalDeclarations preserve=yes
//## end module%3AEF6CFB0125.additionalDeclarations


//## begin CommStream%3AE79D6F0223.preface preserve=yes
//## end CommStream%3AE79D6F0223.preface

//## Class: CommStream%3AE79D6F0223
//	Superclass of all stream classes
//## Category: link_driver::physical%3AEF673A00FF
//## Subsystem: link_driver%3D7412070347
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class CommStream 
{
  //## begin CommStream%3AE79D6F0223.initialDeclarations preserve=yes
  //## end CommStream%3AE79D6F0223.initialDeclarations

  public:
    //## Constructors (generated)
      CommStream();

    //## Destructor (generated)
      virtual ~CommStream();


    //## Other Operations (specified)
      //## Operation: create%988756712
      static CommStream* create (const char* name);

      //## Operation: Open%-1077261126; C++
      virtual bool Open (const char* port_name, const char* port_settings = NULL) = 0;

      //## Operation: SetPortName%988245428
      void SetPortName (const char* new_name	// The new name of the port
      );

      //## Operation: Close%1444875127; C++
      virtual void Close () = 0;

      //## Operation: GetPortName%-256394663; C++
      const char* GetPortName () const;

      //## Operation: WriteBuffer%-1997851982; C++
      virtual bool WriteBuffer (const BYTE* lpBuf, unsigned long dwToWrite) = 0;

      //## Operation: ReadBuffer%746789771; C++
      virtual unsigned long ReadBuffer (BYTE* lpBuf, unsigned long dwToRead, unsigned long total_timeout = 100, 	// total transaction timeout in ms
      unsigned long inter_char_timeout = 5	// inter character timeout in MS
      ) = 0;

      //## Operation: FlushBuffer%277835887; C++
      virtual unsigned long FlushBuffer () = 0;

      //## Operation: CharsInBuffer%-1225006601; C++
      virtual unsigned long CharsInBuffer () = 0;

      //## Operation: read%1811433312; C++
      virtual unsigned long read (BYTE* lpBuf, unsigned long dwToRead) = 0;

      //## Operation: IsOpen%988245427
      bool IsOpen () const;

    // Additional Public Declarations
      //## begin CommStream%3AE79D6F0223.public preserve=yes
      //## end CommStream%3AE79D6F0223.public

  protected:
    // Data Members for Class Attributes

      //## Attribute: _isOpen%3AE764F00224
      //## begin CommStream::_isOpen%3AE764F00224.attr preserve=no  protected: bool {V} false
      bool _isOpen;
      //## end CommStream::_isOpen%3AE764F00224.attr

      //## Attribute: _portName%3AE76E5A024A
      //## begin CommStream::_portName%3AE76E5A024A.attr preserve=no  protected: string {U} ""
      string _portName;
      //## end CommStream::_portName%3AE76E5A024A.attr

    // Additional Protected Declarations
      //## begin CommStream%3AE79D6F0223.protected preserve=yes
      //## end CommStream%3AE79D6F0223.protected

  private:
    // Additional Private Declarations
      //## begin CommStream%3AE79D6F0223.private preserve=yes
      //## end CommStream%3AE79D6F0223.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin CommStream%3AE79D6F0223.implementation preserve=yes
      //## end CommStream%3AE79D6F0223.implementation

};

//## begin CommStream%3AE79D6F0223.postscript preserve=yes
//## end CommStream%3AE79D6F0223.postscript

//## begin CommPort%3AE7644C01F9.preface preserve=yes
//## end CommPort%3AE7644C01F9.preface

//## Class: CommPort%3AE7644C01F9; Abstract
//## Category: link_driver::physical%3AEF673A00FF
//## Subsystem: link_driver%3D7412070347
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AE764F001E0; { -> F}
//## Uses: <unnamed>%3AE764F001F5; { -> F}
//## Uses: <unnamed>%3AE764F001FF; { -> F}
//## Uses: <unnamed>%3AE764F0020A; { -> F}
//## Uses: <unnamed>%3AE764F0020B; { -> F}

class CommPort : public CommStream  //## Inherits: <unnamed>%3AE79D9E002C
{
  //## begin CommPort%3AE7644C01F9.initialDeclarations preserve=yes
  //## end CommPort%3AE7644C01F9.initialDeclarations

  public:
    //## Constructors (generated)
      CommPort();

    //## Destructor (generated)
      virtual ~CommPort();


    //## Other Operations (specified)
      //## Operation: create%988756714
      static CommStream* create (const char* name);

      //## Operation: GetDcdStatus%797319074; C++
      virtual bool GetDcdStatus () = 0;

      //## Operation: GetCtsStatus%1192970356; C++
      virtual bool GetCtsStatus () = 0;

      //## Operation: GetDsrStatus%-233025017; C++
      virtual bool GetDsrStatus () = 0;

      //## Operation: GetRingStatus%988245410; C++
      virtual bool GetRingStatus () = 0;

      //## Operation: SetDtrStatus%988245411
      virtual void SetDtrStatus (bool status) = 0;

      //## Operation: SetRtsStatus%988245412
      virtual void SetRtsStatus (bool status) = 0;

    // Additional Public Declarations
      //## begin CommPort%3AE7644C01F9.public preserve=yes
      //## end CommPort%3AE7644C01F9.public

  protected:
    // Additional Protected Declarations
      //## begin CommPort%3AE7644C01F9.protected preserve=yes
      //## end CommPort%3AE7644C01F9.protected

  private:
    // Additional Private Declarations
      //## begin CommPort%3AE7644C01F9.private preserve=yes
      //## end CommPort%3AE7644C01F9.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin CommPort%3AE7644C01F9.implementation preserve=yes
      //## end CommPort%3AE7644C01F9.implementation

};

//## begin CommPort%3AE7644C01F9.postscript preserve=yes
//## end CommPort%3AE7644C01F9.postscript

//## begin MidiPort%3AEF666C02B1.preface preserve=yes
//## end MidiPort%3AEF666C02B1.preface

//## Class: MidiPort%3AEF666C02B1
//	Uses the Midi input and output
//## Category: link_driver::physical%3AEF673A00FF
//## Subsystem: link_driver%3D7412070347
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class MidiPort : public CommStream  //## Inherits: <unnamed>%3AEF669B02A5
{
  //## begin MidiPort%3AEF666C02B1.initialDeclarations preserve=yes
  //## end MidiPort%3AEF666C02B1.initialDeclarations

  public:
    //## Constructors (generated)
      MidiPort();

      MidiPort(const MidiPort &right);

    //## Destructor (generated)
      ~MidiPort();

    //## Assignment Operation (generated)
      const MidiPort & operator=(const MidiPort &right);

    //## Equality Operations (generated)
      int operator==(const MidiPort &right) const;

      int operator!=(const MidiPort &right) const;


    //## Other Operations (specified)
      //## Operation: create%988756715
      static CommStream* create (const char* name);

    // Additional Public Declarations
      //## begin MidiPort%3AEF666C02B1.public preserve=yes
      //## end MidiPort%3AEF666C02B1.public

  protected:
    // Additional Protected Declarations
      //## begin MidiPort%3AEF666C02B1.protected preserve=yes
      //## end MidiPort%3AEF666C02B1.protected

  private:
    // Additional Private Declarations
      //## begin MidiPort%3AEF666C02B1.private preserve=yes
      //## end MidiPort%3AEF666C02B1.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin MidiPort%3AEF666C02B1.implementation preserve=yes
      //## end MidiPort%3AEF666C02B1.implementation

};

//## begin MidiPort%3AEF666C02B1.postscript preserve=yes
//## end MidiPort%3AEF666C02B1.postscript

// Class CommStream 

inline CommStream::CommStream()
  //## begin CommStream::CommStream%.hasinit preserve=no
      : _isOpen(false), _portName("")
  //## end CommStream::CommStream%.hasinit
  //## begin CommStream::CommStream%.initialization preserve=yes
  //## end CommStream::CommStream%.initialization
{
  //## begin CommStream::CommStream%.body preserve=yes
  //## end CommStream::CommStream%.body
}


inline CommStream::~CommStream()
{
  //## begin CommStream::~CommStream%.body preserve=yes
  //## end CommStream::~CommStream%.body
}



//## Other Operations (inline)
//## Operation: SetPortName%988245428
//	Sets the port name
inline void CommStream::SetPortName (const char* new_name)
{
  _portName = new_name;

  //## begin CommStream::SetPortName%988245428.body preserve=yes
  //## end CommStream::SetPortName%988245428.body
}

//## Operation: GetPortName%-256394663; C++
//	Gets the name of the Com Port
inline const char* CommStream::GetPortName () const
{
  return _portName.c_str();

  //## begin CommStream::GetPortName%-256394663.body preserve=yes
  //## end CommStream::GetPortName%-256394663.body
}

//## Operation: IsOpen%988245427
//	returns true if open
inline bool CommStream::IsOpen () const
{
  return _isOpen;

  //## begin CommStream::IsOpen%988245427.body preserve=yes
  //## end CommStream::IsOpen%988245427.body
}

// Class CommPort 

inline CommPort::CommPort()
  //## begin CommPort::CommPort%.hasinit preserve=no
  //## end CommPort::CommPort%.hasinit
  //## begin CommPort::CommPort%.initialization preserve=yes
  //## end CommPort::CommPort%.initialization
{
  //## begin CommPort::CommPort%.body preserve=yes
  //## end CommPort::CommPort%.body
}


inline CommPort::~CommPort()
{
  //## begin CommPort::~CommPort%.body preserve=yes
  //## end CommPort::~CommPort%.body
}


// Class MidiPort 

//## begin module%3AEF6CFB0125.epilog preserve=yes
//## end module%3AEF6CFB0125.epilog


#endif
