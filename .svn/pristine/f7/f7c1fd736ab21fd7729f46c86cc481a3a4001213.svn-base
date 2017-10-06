//## begin module%3AEF6C1903D3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AEF6C1903D3.cm

//## begin module%3AEF6C1903D3.cp preserve=no
//	Angelo Fraietta
//## end module%3AEF6C1903D3.cp

//## Module: WindowsCommPort%3AEF6C1903D3; Package specification
//	Windows specification of CommPort
//## Subsystem: hal_windows%3AEF69F502F9
//	The windows implementation of the CommStream
//## Source file: c:\develop\linkdriver\hal_windows\windowscommport.h

#ifndef windowscommport_h
#define windowscommport_h 1

//## begin module%3AEF6C1903D3.additionalIncludes preserve=no
//## end module%3AEF6C1903D3.additionalIncludes

//## begin module%3AEF6C1903D3.includes preserve=yes
//## end module%3AEF6C1903D3.includes

// CommStream
#include "commstream.h"
//## begin module%3AEF6C1903D3.declarations preserve=no
//## end module%3AEF6C1903D3.declarations

//## begin module%3AEF6C1903D3.additionalDeclarations preserve=yes
//## end module%3AEF6C1903D3.additionalDeclarations


//## begin WindowsCommPort%3AE75EB7024E.preface preserve=yes
//## end WindowsCommPort%3AE75EB7024E.preface

//## Class: WindowsCommPort%3AE75EB7024E
//	This is a Communications port for Windows platform
//## Category: physical::hal_windows%3AEF70AB03E0
//## Subsystem: hal_windows%3AEF69F502F9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class WindowsCommPort : public CommPort  //## Inherits: <unnamed>%3AE76CA1000B
{
  //## begin WindowsCommPort%3AE75EB7024E.initialDeclarations preserve=yes
  //## end WindowsCommPort%3AE75EB7024E.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: WindowsCommPort%988756721
      WindowsCommPort (const char* name = NULL	// name of the port to open
      );

    //## Destructor (generated)
      ~WindowsCommPort();


    //## Other Operations (specified)
      //## Operation: GetTimeouts%-1144797312; C++
      bool GetTimeouts (COMMTIMEOUTS& cto);

      //## Operation: SetTimeouts%-1924942881; C++
      bool SetTimeouts (COMMTIMEOUTS& cto);

      //## Operation: SetDcb%1436041025; C++
      bool SetDcb (DCB& dcb);

      //## Operation: GetDcb%-1736609045; C++
      bool GetDcb (DCB* dcb);

      //## Operation: Open%988245413; C++
      bool Open (const char* port_name, const char* port_settings = NULL);

      //## Operation: Close%988245414; C++
      void Close ();

      //## Operation: WriteBuffer%988245416; C++
      bool WriteBuffer (const BYTE* lpBuf, DWORD dwToWrite);

      //## Operation: GetDcdStatus%988245417; C++
      bool GetDcdStatus ();

      //## Operation: GetCtsStatus%988245418; C++
      bool GetCtsStatus ();

      //## Operation: GetDsrStatus%988245419; C++
      bool GetDsrStatus ();

      //## Operation: GetRingStatus%988245420; C++
      bool GetRingStatus ();

      //## Operation: SetDtrStatus%988245421
      void SetDtrStatus (bool status);

      //## Operation: SetRtsStatus%988245422
      void SetRtsStatus (bool status);

      //## Operation: ReadBuffer%988245423; C++
      DWORD ReadBuffer (BYTE* lpBuf, DWORD dwToRead, DWORD total_timeout = 100, 	// total transaction timeout in ms
      DWORD inter_char_timeout = 5	// inter character timeout in MS
      );

      //## Operation: FlushBuffer%988245424; C++
      DWORD FlushBuffer ();

      //## Operation: CharsInBuffer%988245425; C++
      DWORD CharsInBuffer ();

      //## Operation: read%988245426; C++
      DWORD read (BYTE* lpBuf, DWORD dwToRead);

    // Additional Public Declarations
      //## begin WindowsCommPort%3AE75EB7024E.public preserve=yes
      //## end WindowsCommPort%3AE75EB7024E.public

  protected:
    // Additional Protected Declarations
      //## begin WindowsCommPort%3AE75EB7024E.protected preserve=yes
      //## end WindowsCommPort%3AE75EB7024E.protected

  private:
    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: _handle%3AE7716303C4
      //	The windows handle of the Com Port
      const HANDLE get__handle () const;
      void set__handle (HANDLE value);

    // Additional Private Declarations
      //## begin WindowsCommPort%3AE75EB7024E.private preserve=yes
      //## end WindowsCommPort%3AE75EB7024E.private

  private: //## implementation
    // Data Members for Class Attributes

      //## begin WindowsCommPort::_handle%3AE7716303C4.attr preserve=no  private: HANDLE {U} NULL
      HANDLE _handle;
      //## end WindowsCommPort::_handle%3AE7716303C4.attr

    // Additional Implementation Declarations
      //## begin WindowsCommPort%3AE75EB7024E.implementation preserve=yes
      //## end WindowsCommPort%3AE75EB7024E.implementation

};

//## begin WindowsCommPort%3AE75EB7024E.postscript preserve=yes
//## end WindowsCommPort%3AE75EB7024E.postscript

// Class WindowsCommPort 

//## Get and Set Operations for Class Attributes (inline)

inline const HANDLE WindowsCommPort::get__handle () const
{
  //## begin WindowsCommPort::get__handle%3AE7716303C4.get preserve=no
  return _handle;
  //## end WindowsCommPort::get__handle%3AE7716303C4.get
}

inline void WindowsCommPort::set__handle (HANDLE value)
{
  //## begin WindowsCommPort::set__handle%3AE7716303C4.set preserve=no
  _handle = value;
  //## end WindowsCommPort::set__handle%3AE7716303C4.set
}

//## begin module%3AEF6C1903D3.epilog preserve=yes
//## end module%3AEF6C1903D3.epilog


#endif
