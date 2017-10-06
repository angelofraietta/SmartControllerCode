//## begin module%4069C85102EE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4069C85102EE.cm

//## begin module%4069C85102EE.cp preserve=no
//	Angelo Fraietta
//## end module%4069C85102EE.cp

//## Module: UDPPort%4069C85102EE; Pseudo Package body
//## Subsystem: link_driver%3D7412070347
//## Source file: D:\develop\Smartcontroller\controller\source\link_driver\udpport.cpp

//## begin module%4069C85102EE.additionalIncludes preserve=no
//## end module%4069C85102EE.additionalIncludes

//## begin module%4069C85102EE.includes preserve=yes

//#include "htmsocket.h"

#include <stdio.h>
//## end module%4069C85102EE.includes

// UDPPort
#include "udpport.h"
//## begin module%4069C85102EE.additionalDeclarations preserve=yes
#include <stdio.h>
//#include <io.h>

typedef struct
{
	float srate;

	struct sockaddr_in serv_addr; /* udp socket */
	#ifndef WIN32
		struct sockaddr_un userv_addr; /* UNIX socket */
	#endif
	int sockfd;		/* socket file descriptor */
	int index, len,uservlen;
	void *addr;
	int id;
} desc;

static void closeudp(int sockfd) {
	#ifdef WIN32
		closesocket(sockfd);
	#else
		close(sockfd);
	#endif
}

static int initudp(int chan)
{

#ifdef WIN32
	struct sockaddr_in serv_addr;
	unsigned int sockfd;
	if(   (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) != INVALID_SOCKET     ) {
		ZeroMemory((char *)&serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons((short)chan);
		if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
      perror("unable to  bind\n");
      closeudp (sockfd);
      sockfd = INVALID_SOCKET;
    }
		else
			{
				printf("Successful Bind to %u\r\n", chan);
			}
	}

	return (sockfd == INVALID_SOCKET ? -1 : (int)sockfd);
#else
	struct sockaddr_in serv_addr;
	int  sockfd;

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
			return sockfd;

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(chan);

	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("unable to  bind\n");
    closeudp (sockfd);
    sockfd = -1;
	}
	else
		{
			printf("Successful Bind to %u", chan);
		}

	return sockfd;
#endif
}
//## end module%4069C85102EE.additionalDeclarations


// Class UDPPort 


//## begin UDPPort::_init%406C962B003C.attr preserve=no  private: static bool {U} false
bool UDPPort::_init = false;
//## end UDPPort::_init%406C962B003C.attr





//## begin UDPPort::_flush_message%408865BA01A5.attr preserve=no  private: static const char* {U} "flush"
const char* UDPPort::_flush_message = "flush";
//## end UDPPort::_flush_message%408865BA01A5.attr

//## Operation: UDPPort%1080675297
UDPPort::UDPPort ()
  //## begin UDPPort::UDPPort%1080675297.hasinit preserve=no
      : _fd(-1), _isOpen(false), _disable_change_address(false)
  //## end UDPPort::UDPPort%1080675297.hasinit
  //## begin UDPPort::UDPPort%1080675297.initialization preserve=yes
  //## end UDPPort::UDPPort%1080675297.initialization
{
  //## begin UDPPort::UDPPort%1080675297.body preserve=yes
  //## end UDPPort::UDPPort%1080675297.body
}



//## Other Operations (implementation)
//## Operation: Open%1080675289; C++
//	Opens the Comm port
bool UDPPort::Open (const char* port_name, const char* port_settings)
{
  //## begin UDPPort::Open%1080675289.body preserve=yes
  return OpenPort(atoi(port_name));
  //## end UDPPort::Open%1080675289.body
}

//## Operation: Close%1080675290; C++
//	Closes the Comm Port
void UDPPort::Close ()
{
  //## begin UDPPort::Close%1080675290.body preserve=yes
  if (_isOpen)
  {
    closeudp(_fd);
    _fd = -1;
    _isOpen = false;
  }
  //## end UDPPort::Close%1080675290.body
}

//## Operation: WriteBuffer%1080675291; C++
//	Writes a buffer of Bytes to an open Port
bool UDPPort::WriteBuffer (const unsigned char* lpBuf, unsigned long dwToWrite)
{
  //## begin UDPPort::WriteBuffer%1080675291.body preserve=yes
  bool ret = false;

  if (_fd)
  {
    int bytes = sendto(_fd, (const char*) lpBuf, dwToWrite, 0 , (const sockaddr*)&_to, sizeof(_to));
    ret = bytes == dwToWrite;
  }
  return ret;
  //## end UDPPort::WriteBuffer%1080675291.body
}

//## Operation: ReadBuffer%1080675292; C++
//	Reads a buffer of Bytes from a port with a timeout
unsigned long UDPPort::ReadBuffer (unsigned  char* lpBuf, unsigned long dwToRead)
{
  //## begin UDPPort::ReadBuffer%1080675292.body preserve=yes

    int size_from = sizeof(_from);
    int n;
	  if ((n = recvfrom(_fd, (char*)lpBuf, dwToRead, 0, (sockaddr*)&_from, &size_from)) >0)
	  {
  		  if (!_disable_change_address)
        {
          // set our to address to the from
          _to.sin_addr =  _from.sin_addr;
        }
        else if (_to.sin_addr.s_addr != _from.sin_addr.s_addr)             
        {
          printf ("UDP Port To and From Do not Match\r\n");
          n = 0;
        }
	  }
    return n;
  //## end UDPPort::ReadBuffer%1080675292.body
}

//## Operation: reset%1081798837
void UDPPort::reset ()
{
  //## begin UDPPort::reset%1081798837.body preserve=yes
  //## end UDPPort::reset%1081798837.body
}

//## Operation: SetTo%1082089062
//	Sets the To address
bool UDPPort::SetTo (const char* to_address)
{
  //## begin UDPPort::SetTo%1082089062.body preserve=yes
  bool ret = false;

  if (to_address)
  {
    _to.sin_addr.s_addr = inet_addr (to_address);
    ret = true;
  }

  _disable_change_address = ret;
  return ret;

  //## end UDPPort::SetTo%1082089062.body
}

//## Operation: GetFrom%1082089063
//	Returns the From Address
bool UDPPort::GetFrom (char* ret_buf, unsigned buf_size)
{
  //## begin UDPPort::GetFrom%1082089063.body preserve=yes
  bool ret = false;

  char* host_add = inet_ntoa (_from.sin_addr);
  if (host_add)
  {
    strncpy(ret_buf, host_add, buf_size-1);
    ret_buf [buf_size -1] = 0;
    ret = true;
  }

  return ret;
  //## end UDPPort::GetFrom%1082089063.body
}

//## Operation: OpenPort%1082317733
bool UDPPort::OpenPort (int port_number)
{
  //## begin UDPPort::OpenPort%1082317733.body preserve=yes
#ifdef WIN32  
	if (! _init)
		{
			
			WORD wVersionRequested;
			WSADATA wsaData;
			
			wVersionRequested = MAKEWORD( 2, 2 );
			
			WSAStartup( wVersionRequested, &wsaData );
		}
#endif
	
  Close();
  _fd = initudp(port_number);

  memset (&_from, 0, sizeof _from);
	#ifndef WIN32
  _to.sin_len         = sizeof (_to);
  #endif
  _to.sin_family      = AF_INET;
  _to.sin_port        = htons ((short)port_number);
  _to.sin_addr.s_addr = inet_addr ("192.168.0.255");

  _isOpen = (_fd > 0);

  return _isOpen;

  //## end UDPPort::OpenPort%1082317733.body
}

//## Operation: flush%1082670126
//	Flushes the input buffer. Accompplied by sending a
//	message to the local port and waiting Until it is
//	received
void UDPPort::flush ()
{
  //## begin UDPPort::flush%1082670126.body preserve=yes
  bool flush_complete = false;
  static int flush_num = 0;
  sockaddr_in flush_to;
  sockaddr_in flush_from;
  int size_from = sizeof(flush_from);

  char flush_end_buf [64];
  char ret_buf [1024];

  memset (&flush_to, 0, sizeof flush_to);
	#ifndef WIN32
  flush_to.sin_len         = sizeof (flush_to);
  #endif
  flush_to.sin_family      = AF_INET;
  flush_to.sin_port        = _to.sin_port;
  flush_to.sin_addr.s_addr = inet_addr ("127.0.0.1");


  printf ("UDP Flush Start\r\n");

  // send two messages - one for us, and one for blocked thread
  sendto(_fd, _flush_message, strlen(_flush_message), 0 , (const sockaddr*)&flush_to, sizeof(flush_to));
  sendto(_fd, _flush_message, strlen(_flush_message), 0 , (const sockaddr*)&flush_to, sizeof(flush_to));


  sprintf(flush_end_buf, "%s%u", _flush_message, flush_num);

  sendto(_fd, flush_end_buf, strlen(flush_end_buf) +1, 0 , (const sockaddr*)&flush_to, sizeof(flush_to));
  do
  {
    if ((recvfrom(_fd, ret_buf, sizeof(ret_buf), 0, (sockaddr*)&flush_from, &size_from)) >0)
    {
      if (flush_to.sin_addr.s_addr == flush_from.sin_addr.s_addr)
      {
        flush_complete = !strcmp(flush_end_buf, ret_buf);
      }
    }
    else
    {
      flush_complete = true;
    }
  } while (!flush_complete);


  printf ("UDP Flush End\r\n");
  flush_num++;
  //## end UDPPort::flush%1082670126.body
}

// Additional Declarations
  //## begin UDPPort%4069C85102EE.declarations preserve=yes
  //## end UDPPort%4069C85102EE.declarations

//## begin module%4069C85102EE.epilog preserve=yes
//## end module%4069C85102EE.epilog
