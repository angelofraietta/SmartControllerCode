//## begin module%3CF1B0700221.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CF1B0700221.cm

//## begin module%3CF1B0700221.cp preserve=no
//	Angelo Fraietta
//## end module%3CF1B0700221.cp

//## Module: SysexDriver%3CF1B0700221; Pseudo Package specification
//## Subsystem: engine%39F51CB901B8
//## Source file: c:\develop\Winsmartcontroller\controller\source\engine\sysexdriver.h

#ifndef sysexdriver_h
#define sysexdriver_h 1

//## begin module%3CF1B0700221.additionalIncludes preserve=no
//## end module%3CF1B0700221.additionalIncludes

//## begin module%3CF1B0700221.includes preserve=yes
//## end module%3CF1B0700221.includes

// PresentationAnswer
#include "presentationanswer.h"

class LinkProtocol;

//## begin module%3CF1B0700221.additionalDeclarations preserve=yes
//## end module%3CF1B0700221.additionalDeclarations


//## begin SysexDriver%3CF1B0700221.preface preserve=yes
//## end SysexDriver%3CF1B0700221.preface

//## Class: SysexDriver%3CF1B0700221
//## Category: engine%39F4C4E2005F
//## Subsystem: engine%39F51CB901B8
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class SysexDriver 
{
  //## begin SysexDriver%3CF1B0700221.initialDeclarations preserve=yes
  //## end SysexDriver%3CF1B0700221.initialDeclarations

  public:
    //## Constructors (generated)
      SysexDriver();


    //## Other Operations (specified)
      //## Operation: Reset%1022473326
      void Reset ();

      //## Operation: ProcessByte%1022473327
      void ProcessByte (char data);

    // Additional Public Declarations
      //## begin SysexDriver%3CF1B0700221.public preserve=yes
      //## end SysexDriver%3CF1B0700221.public

  protected:
    // Additional Protected Declarations
      //## begin SysexDriver%3CF1B0700221.protected preserve=yes
      //## end SysexDriver%3CF1B0700221.protected

  private:

    //## Other Operations (specified)
      //## Operation: ProcessOurSysex%1022473328
      void ProcessOurSysex (char data);

      //## Operation: ProcessOtherSysex%1022473329
      void ProcessOtherSysex (char data);

    // Additional Private Declarations
      //## begin SysexDriver%3CF1B0700221.private preserve=yes
      //## end SysexDriver%3CF1B0700221.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _dle%3CF1B0F40131
      //## begin SysexDriver::_dle%3CF1B0F40131.attr preserve=no  private: BYTE {U} 0
      BYTE _dle;
      //## end SysexDriver::_dle%3CF1B0F40131.attr

      //## Attribute: _byte_num%3CF1B151026B
      //## begin SysexDriver::_byte_num%3CF1B151026B.attr preserve=no  private: unsigned {U} 0
      unsigned _byte_num;
      //## end SysexDriver::_byte_num%3CF1B151026B.attr

      //## Attribute: _sysex_header%3CF1B8AA019D
      //## begin SysexDriver::_sysex_header%3CF1B8AA019D.attr preserve=no  private: static char[] {U} {0x7D, 0x01}
      static char _sysex_header[];
      //## end SysexDriver::_sysex_header%3CF1B8AA019D.attr

      //## Attribute: _our_sysex%3CF1B932022F
      //## begin SysexDriver::_our_sysex%3CF1B932022F.attr preserve=no  private: bool {U} true
      bool _our_sysex;
      //## end SysexDriver::_our_sysex%3CF1B932022F.attr

      //## Attribute: _rx_buf%3CF1CBB20352
      //## begin SysexDriver::_rx_buf%3CF1CBB20352.attr preserve=no  private: BYTE[1024] {U} 
      BYTE _rx_buf[1024];
      //## end SysexDriver::_rx_buf%3CF1CBB20352.attr

    // Data Members for Associations

      //## Association: engine::<unnamed>%3CF1BBCB01DB
      //## Role: SysexDriver::_link_layer%3CF1BBCB034E
      //## begin SysexDriver::_link_layer%3CF1BBCB034E.role preserve=no  public: LinkProtocol { -> 1RFHN}
      LinkProtocol *_link_layer;
      //## end SysexDriver::_link_layer%3CF1BBCB034E.role

      //## Association: engine::<unnamed>%3CF1C5A4033F
      //## Role: SysexDriver::_controller%3CF1C5A500F2
      //## begin SysexDriver::_controller%3CF1C5A500F2.role preserve=no  public: PresentationAnswer { -> 1VHN}
      PresentationAnswer _controller;
      //## end SysexDriver::_controller%3CF1C5A500F2.role

    // Additional Implementation Declarations
      //## begin SysexDriver%3CF1B0700221.implementation preserve=yes
      //## end SysexDriver%3CF1B0700221.implementation

};

//## begin SysexDriver%3CF1B0700221.postscript preserve=yes
//## end SysexDriver%3CF1B0700221.postscript

// Class SysexDriver 

//## begin module%3CF1B0700221.epilog preserve=yes
//## end module%3CF1B0700221.epilog


#endif
