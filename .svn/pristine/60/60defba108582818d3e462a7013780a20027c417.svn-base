//## begin module%3B43FDC2039D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B43FDC2039D.cm

//## begin module%3B43FDC2039D.cp preserve=no
//	Angelo Fraietta
//## end module%3B43FDC2039D.cp

//## Module: RtemsCommPort%3B43FDC2039D; Pseudo Package specification
//## Subsystem: hal_rtems%3AEF6A0103BE
//## Source file: c:\develop\linkdriver\hal_rtems\rtemscommport.h

#ifndef rtemscommport_h
#define rtemscommport_h 1

//## begin module%3B43FDC2039D.additionalIncludes preserve=no
//## end module%3B43FDC2039D.additionalIncludes

//## begin module%3B43FDC2039D.includes preserve=yes
#include <stdio.h>
//## end module%3B43FDC2039D.includes

// CommStream
#include "commstream.h"
//## begin module%3B43FDC2039D.additionalDeclarations preserve=yes
//## end module%3B43FDC2039D.additionalDeclarations


//## begin RtemsCommPort%3B43FDC2039D.preface preserve=yes
//## end RtemsCommPort%3B43FDC2039D.preface

//## Class: RtemsCommPort%3B43FDC2039D
//## Category: physical::hal_rtems%3AEF70F40146
//## Subsystem: hal_rtems%3AEF6A0103BE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class RtemsCommPort : public CommPort  //## Inherits: <unnamed>%3B43FDE10059
{
  //## begin RtemsCommPort%3B43FDC2039D.initialDeclarations preserve=yes
  //## end RtemsCommPort%3B43FDC2039D.initialDeclarations

  public:
    //## Constructors (generated)
      RtemsCommPort();

    //## Destructor (generated)
      ~RtemsCommPort();


    //## Other Operations (specified)
      //## Operation: Open%994311832; C++
      bool Open (const char* port_name, const char* port_settings = NULL);

      //## Operation: Close%994311833; C++
      void Close ();

      //## Operation: WriteBuffer%994311834; C++
      bool WriteBuffer (const BYTE* lpBuf, DWORD dwToWrite);

      //## Operation: GetDcdStatus%994311835; C++
      bool GetDcdStatus ();

      //## Operation: GetCtsStatus%994311836; C++
      bool GetCtsStatus ();

      //## Operation: GetDsrStatus%994311837; C++
      bool GetDsrStatus ();

      //## Operation: GetRingStatus%994311838; C++
      bool GetRingStatus ();

      //## Operation: SetDtrStatus%994311839
      void SetDtrStatus (bool status);

      //## Operation: SetRtsStatus%994311840
      void SetRtsStatus (bool status);

      //## Operation: ReadBuffer%994311841; C++
      DWORD ReadBuffer (BYTE* lpBuf, DWORD dwToRead, DWORD total_timeout = 100, 	// total transaction timeout in ms
      DWORD inter_char_timeout = 5	// inter character timeout in MS
      );

      //## Operation: FlushBuffer%994311842; C++
      DWORD FlushBuffer ();

      //## Operation: CharsInBuffer%994311843; C++
      DWORD CharsInBuffer ();

      //## Operation: read%994311844; C++
      DWORD read (BYTE* lpBuf, DWORD dwToRead);

    // Additional Public Declarations
      //## begin RtemsCommPort%3B43FDC2039D.public preserve=yes
      //## end RtemsCommPort%3B43FDC2039D.public

  protected:
    // Additional Protected Declarations
      //## begin RtemsCommPort%3B43FDC2039D.protected preserve=yes
      //## end RtemsCommPort%3B43FDC2039D.protected

  private:
    // Additional Private Declarations
      //## begin RtemsCommPort%3B43FDC2039D.private preserve=yes
      //## end RtemsCommPort%3B43FDC2039D.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _file%3B43FDE50235
      //## begin RtemsCommPort::_file%3B43FDE50235.attr preserve=no  private: int {U} -1
      int _file;
      //## end RtemsCommPort::_file%3B43FDE50235.attr

    // Additional Implementation Declarations
      //## begin RtemsCommPort%3B43FDC2039D.implementation preserve=yes
      //## end RtemsCommPort%3B43FDC2039D.implementation

};

//## begin RtemsCommPort%3B43FDC2039D.postscript preserve=yes
//## end RtemsCommPort%3B43FDC2039D.postscript

// Class RtemsCommPort 

//## begin module%3B43FDC2039D.epilog preserve=yes
//## end module%3B43FDC2039D.epilog


#endif
