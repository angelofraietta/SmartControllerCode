//## begin module%3D6C5A160219.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D6C5A160219.cm

//## begin module%3D6C5A160219.cp preserve=no
//	Angelo Fraietta
//## end module%3D6C5A160219.cp

//## Module: MacCommPort%3D6C5A160219; Package specification
//## Subsystem: link_driver::hal_mac%3AEF6A5C035B
//	The Mac implementation of the CommStream
//## Source file: c:\develop\Winsmartcontroller\controller\source\link_driver\hal_mac\maccommport.h

#ifndef maccommport_h
#define maccommport_h 1

//## begin module%3D6C5A160219.additionalIncludes preserve=no
//## end module%3D6C5A160219.additionalIncludes

//## begin module%3D6C5A160219.includes preserve=yes
//## end module%3D6C5A160219.includes

// CommStream
#include "commstream.h"
//## begin module%3D6C5A160219.declarations preserve=no
//## end module%3D6C5A160219.declarations

//## begin module%3D6C5A160219.additionalDeclarations preserve=yes
//## end module%3D6C5A160219.additionalDeclarations


//## begin MacCommPort%3D6C589B0138.preface preserve=yes
//## end MacCommPort%3D6C589B0138.preface

//## Class: MacCommPort%3D6C589B0138
//## Category: link_driver::physical::hal_mac%3D6C58700353
//## Subsystem: link_driver::hal_mac%3AEF6A5C035B
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class MacCommPort : public CommPort  //## Inherits: <unnamed>%3D6C58A502C3
{
  //## begin MacCommPort%3D6C589B0138.initialDeclarations preserve=yes
  //## end MacCommPort%3D6C589B0138.initialDeclarations

  public:
    // Additional Public Declarations
      //## begin MacCommPort%3D6C589B0138.public preserve=yes
      //## end MacCommPort%3D6C589B0138.public

  protected:
    // Additional Protected Declarations
      //## begin MacCommPort%3D6C589B0138.protected preserve=yes
      //## end MacCommPort%3D6C589B0138.protected

  private:
    // Additional Private Declarations
      //## begin MacCommPort%3D6C589B0138.private preserve=yes
      //## end MacCommPort%3D6C589B0138.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin MacCommPort%3D6C589B0138.implementation preserve=yes
      //## end MacCommPort%3D6C589B0138.implementation

};

//## begin MacCommPort%3D6C589B0138.postscript preserve=yes
//## end MacCommPort%3D6C589B0138.postscript

// Class MacCommPort 

//## begin module%3D6C5A160219.epilog preserve=yes
//## end module%3D6C5A160219.epilog


#endif
