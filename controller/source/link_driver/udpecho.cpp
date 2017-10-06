#include <stdio.h>
#include "activeobject.h"
#include "UDPPort.h"
#include "event.h"

#define RESPOND_PORT_NUMBER 7700
class UDPRespond:public ActiveObject
{
  public:
  UDPRespond (unsigned port_number) :_port(new UDPPort)
  {
    if (_port->OpenPort(port_number))
    {
      printf ("Opened Port\r\n");
    }
  }
  ~UDPRespond (){kill();}

  private:
  UDPPort* _port;
  void run ();
};


void UDPRespond::run()
{
  while (!Terminated())
		{
    //printf("Receive\r\n");
    char buff [1024];
    char from [32];
    long bytes_read =  _port->ReadBuffer((unsigned char*)buff, sizeof(buff));

      if (_port->GetFrom(from, sizeof(from)))
      {
        _port->SetTo(from);
        printf ("Received %s from %s \r\n", buff, from);
        // receive and echo
      }
		}
}





int main ()
{
	//cout<<"TestThread App"<<endl;
	printf("Mainline\r\n");

  Event* pEvent;

  pEvent =  Event::create();
  UDPRespond* t = new UDPRespond(RESPOND_PORT_NUMBER);
  t->start();

  while (pEvent->Wait())
  {

  }

}