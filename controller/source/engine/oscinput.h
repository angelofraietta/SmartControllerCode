//## begin module%40FEFD010122.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40FEFD010122.cm

//## begin module%40FEFD010122.cp preserve=no
//	Angelo Fraietta
//## end module%40FEFD010122.cp

//## Module: OSCInput%40FEFD010122; Pseudo Package specification
//## Subsystem: engine%39F51CB901B8
//## Source file: D:\develop\smartcontroller\controller\source\engine\oscinput.h

#ifndef oscinput_h
#define oscinput_h 1

//## begin module%40FEFD010122.additionalIncludes preserve=no
//## end module%40FEFD010122.additionalIncludes

//## begin module%40FEFD010122.includes preserve=yes
//## end module%40FEFD010122.includes

// ActiveObject
#include "activeobject.h"

class OSCArg;
class OSCIn;
namespace hal_include {
  class Scheduler;
} // namespace hal_include

class Event;
class UDPPort;

//## begin module%40FEFD010122.additionalDeclarations preserve=yes
//## end module%40FEFD010122.additionalDeclarations


//## begin OSCInput%40FEFD010122.preface preserve=yes
//## end OSCInput%40FEFD010122.preface

//## Class: OSCInput%40FEFD010122
//## Category: engine%39F4C4E2005F
//## Subsystem: engine%39F51CB901B8
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%40FF1D9002F6;OSCIn { -> F}
//## Uses: <unnamed>%40FF404603A2;OSCArg { -> F}
//## Uses: <unnamed>%4100430D0242;hal_include::Scheduler { -> F}

class OSCInput : public ActiveObject  //## Inherits: <unnamed>%40FEFD11017F
{
  //## begin OSCInput%40FEFD010122.initialDeclarations preserve=yes
  //## end OSCInput%40FEFD010122.initialDeclarations

  public:
    //## Constructors (generated)
      OSCInput();

    //## Destructor (generated)
      ~OSCInput();


    //## Other Operations (specified)
      //## Operation: run%1090452875
      void run ();

      //## Operation: open%1090452876
      bool open (int port_num);

      //## Operation: close%1090452877
      void close ();

      //## Operation: create%1090554363
      static bool create (int port);

      //## Operation: closeall%1090554364
      static void closeall ();

    // Additional Public Declarations
      //## begin OSCInput%40FEFD010122.public preserve=yes
      //## end OSCInput%40FEFD010122.public

  protected:
    // Additional Protected Declarations
      //## begin OSCInput%40FEFD010122.protected preserve=yes
      //## end OSCInput%40FEFD010122.protected

  private:

    //## Other Operations (specified)
      //## Operation: ParseOSCPacket%1090452878
      bool ParseOSCPacket (char*  buf, unsigned buf_len, const char* client_address);

      //## Operation: DataAfterAlignedString%1090452879
      char* DataAfterAlignedString (char* string, char* boundary);

      //## Operation: SendOSCMessage%1090452880
      bool SendOSCMessage (const char* osc_address, char* arg_data, int arg_data_length, const char* client_address);

      //## Operation: ObtainTypeTaggedArgs%1090452881
      unsigned ObtainTypeTaggedArgs (void* arg_data_buf, unsigned buf_len);

      //## Operation: ObtainHeuristicallyTypeGuessedArgs%1090452882
      unsigned ObtainHeuristicallyTypeGuessedArgs (void* arg_data_buf, unsigned buf_len, bool skipComma);

      //## Operation: IsNiceString%1090452883
      bool IsNiceString (char* string, char* boundary);

    // Additional Private Declarations
      //## begin OSCInput%40FEFD010122.private preserve=yes
      //## end OSCInput%40FEFD010122.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _is_open%40FF00C20383
      //## begin OSCInput::_is_open%40FF00C20383.attr preserve=no  private: bool {UT} false
      volatile bool  _is_open;
      //## end OSCInput::_is_open%40FF00C20383.attr

      //## Attribute: _port_num%40FF01DC025A
      //## begin OSCInput::_port_num%40FF01DC025A.attr preserve=no  private: int {U} 0
      int _port_num;
      //## end OSCInput::_port_num%40FF01DC025A.attr

      //## Attribute: _purging%40FF057800C4
      //	Flasg to indicate we are purging
      //## begin OSCInput::_purging%40FF057800C4.attr preserve=no  private: bool {UT} false
      volatile bool  _purging;
      //## end OSCInput::_purging%40FF057800C4.attr

      //## Attribute: _in_buf%40FF06710112
      //## begin OSCInput::_in_buf%40FF06710112.attr preserve=no  private: unsigned char [1024] {U} 
      unsigned char  _in_buf[1024];
      //## end OSCInput::_in_buf%40FF06710112.attr

      //## Attribute: _num_args%40FF42630141
      //## begin OSCInput::_num_args%40FF42630141.attr preserve=no  private: unsigned {U} 0
      unsigned _num_args;
      //## end OSCInput::_num_args%40FF42630141.attr

      //## Attribute: _list_size%41008BD601C5
      //## begin OSCInput::_list_size%41008BD601C5.attr preserve=no  private: static unsigned {U} 0
      static unsigned _list_size;
      //## end OSCInput::_list_size%41008BD601C5.attr

    // Data Members for Associations

      //## Association: engine::<unnamed>%40FEFE82018F
      //## Role: OSCInput::_in_port%40FEFE830038
      //## begin OSCInput::_in_port%40FEFE830038.role preserve=no  public: UDPPort { -> 1RFHN}
      UDPPort *_in_port;
      //## end OSCInput::_in_port%40FEFE830038.role

      //## Association: engine::<unnamed>%40FF0318017F
      //## Role: OSCInput::pEvent%40FF03190085
      //## begin OSCInput::pEvent%40FF03190085.role preserve=no  public: Event { -> 1RFHN}
      Event *pEvent;
      //## end OSCInput::pEvent%40FF03190085.role

      //## Association: engine::<unnamed>%40FF40F101AE
      //## Role: OSCInput::_args%40FF40F103D2
      //## begin OSCInput::_args%40FF40F103D2.role preserve=no  public: OSCArg { -> RFHN}
      OSCArg *_args;
      //## end OSCInput::_args%40FF40F103D2.role

    // Additional Implementation Declarations
      //## begin OSCInput%40FEFD010122.implementation preserve=yes
      //## end OSCInput%40FEFD010122.implementation

};

//## begin OSCInput%40FEFD010122.postscript preserve=yes
//## end OSCInput%40FEFD010122.postscript

// Class OSCInput 

//## begin module%40FEFD010122.epilog preserve=yes
//## end module%40FEFD010122.epilog


#endif
