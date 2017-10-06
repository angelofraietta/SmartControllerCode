//## begin module%4069C85102EE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4069C85102EE.cm

//## begin module%4069C85102EE.cp preserve=no
//	Angelo Fraietta
//## end module%4069C85102EE.cp

//## Module: UDPPort%4069C85102EE; Pseudo Package specification
//## Subsystem: link_driver%3D7412070347
//## Source file: D:\develop\Smartcontroller\controller\source\link_driver\udpport.h

#ifndef udpport_h
#define udpport_h 1

//## begin module%4069C85102EE.additionalIncludes preserve=no
//## end module%4069C85102EE.additionalIncludes

//## begin module%4069C85102EE.includes preserve=yes
#ifdef WIN32
	#include <winsock2.h>	
	#include <string.h>
	#include <stdlib.h>
	#include <fcntl.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <ctype.h>
	#include <signal.h>
#else

	#include <string.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <fcntl.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <netinet/in.h>
	#include <rpc/rpc.h>
	#include <sys/socket.h>
	#include <sys/un.h>
	#include <sys/times.h>
	#include <sys/param.h>
	#include <sys/time.h>
	#include <sys/ioctl.h>
	#include <ctype.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <pwd.h>
	#include <signal.h>
	#include <grp.h>
	#include <sys/file.h>
//#include <sys/prctl.h>

	#ifdef NEED_SCHEDCTL_AND_LOCK
	#include <sys/schedctl.h>
	#include <sys/lock.h>
	#endif
#endif

//## end module%4069C85102EE.includes

// NetworkLayer
#include "networklayer.h"
//## begin module%4069C85102EE.additionalDeclarations preserve=yes
//## end module%4069C85102EE.additionalDeclarations


//## begin UDPPort%4069C85102EE.preface preserve=yes
//## end UDPPort%4069C85102EE.preface

//## Class: UDPPort%4069C85102EE
//## Category: link_driver%3D7411EB00A8
//## Subsystem: link_driver%3D7412070347
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class UDPPort : public NetworkLayer  //## Inherits: <unnamed>%4082F6FC03A9
{
  //## begin UDPPort%4069C85102EE.initialDeclarations preserve=yes
  //## end UDPPort%4069C85102EE.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: UDPPort%1080675297
      UDPPort ();


    //## Other Operations (specified)
      //## Operation: Open%1080675289; C++
      bool Open (const char* port_name, const char* port_settings = NULL);

      //## Operation: Close%1080675290; C++
      void Close ();

      //## Operation: WriteBuffer%1080675291; C++
      bool WriteBuffer (const unsigned char* lpBuf, unsigned long dwToWrite);

      //## Operation: ReadBuffer%1080675292; C++
      unsigned long ReadBuffer (unsigned  char* lpBuf, unsigned long dwToRead);

      //## Operation: reset%1081798837
      virtual void reset ();

      //## Operation: SetTo%1082089062
      virtual bool SetTo (const char* to_address);

      //## Operation: GetFrom%1082089063
      virtual bool GetFrom (char* ret_buf, unsigned buf_size);

      //## Operation: OpenPort%1082317733
      bool OpenPort (int port_number);

      //## Operation: flush%1082670126
      virtual void flush ();

    // Additional Public Declarations
      //## begin UDPPort%4069C85102EE.public preserve=yes
      //## end UDPPort%4069C85102EE.public

  protected:
    // Additional Protected Declarations
      //## begin UDPPort%4069C85102EE.protected preserve=yes
      //## end UDPPort%4069C85102EE.protected

  private:
    // Additional Private Declarations
      //## begin UDPPort%4069C85102EE.private preserve=yes
      //## end UDPPort%4069C85102EE.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: _fd%4069C9C900AB
      //	Handle of socket
      //## begin UDPPort::_fd%4069C9C900AB.attr preserve=no  private: int {U} -1
      int _fd;
      //## end UDPPort::_fd%4069C9C900AB.attr

      //## Attribute: _init%406C962B003C
      //## begin UDPPort::_init%406C962B003C.attr preserve=no  private: static bool {U} false
      static bool _init;
      //## end UDPPort::_init%406C962B003C.attr

      //## Attribute: _isOpen%407AF4F3035B
      //## begin UDPPort::_isOpen%407AF4F3035B.attr preserve=no  private: bool {U} false
      bool _isOpen;
      //## end UDPPort::_isOpen%407AF4F3035B.attr

      //## Attribute: _from%407F5E4E00DA
      //## begin UDPPort::_from%407F5E4E00DA.attr preserve=no  private: sockaddr_in {U} 
      sockaddr_in _from;
      //## end UDPPort::_from%407F5E4E00DA.attr

      //## Attribute: _to%407F5E59037A
      //## begin UDPPort::_to%407F5E59037A.attr preserve=no  private: sockaddr_in {U} 
      sockaddr_in _to;
      //## end UDPPort::_to%407F5E59037A.attr

      //## Attribute: _disable_change_address%40884C26035B
      //## begin UDPPort::_disable_change_address%40884C26035B.attr preserve=no  private: bool {U} false
      bool _disable_change_address;
      //## end UDPPort::_disable_change_address%40884C26035B.attr

      //## Attribute: _flushing%408865860109
      //## begin UDPPort::_flushing%408865860109.attr preserve=no  private: bool {U} false
      bool _flushing;
      //## end UDPPort::_flushing%408865860109.attr

      //## Attribute: _flush_message%408865BA01A5
      //## begin UDPPort::_flush_message%408865BA01A5.attr preserve=no  private: static const char* {U} "flush"
      static const char* _flush_message;
      //## end UDPPort::_flush_message%408865BA01A5.attr

    // Additional Implementation Declarations
      //## begin UDPPort%4069C85102EE.implementation preserve=yes
      //## end UDPPort%4069C85102EE.implementation

};

//## begin UDPPort%4069C85102EE.postscript preserve=yes
//## end UDPPort%4069C85102EE.postscript

// Class UDPPort 

//## begin module%4069C85102EE.epilog preserve=yes
//## end module%4069C85102EE.epilog


#endif
