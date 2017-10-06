#include <rtems.h>
#include "activeobject.h"
#include "event.h"
#include <string>

#include <stdio.h>

void Sleep (unsigned long sleep_time)
{
	rtems_task_wake_after(sleep_time); 
}

class TestThread:public ActiveObject
{
  public:
  TestThread (): _purge(false), pEvent(Event::create()){}
  ~TestThread (){Purge(); Sleep (100); kill(); delete pEvent;}
  void Go(){pEvent->Release();}
  void Purge();
  private:
  void run ();
  Event* pEvent;
  volatile bool _purge;

};


void TestThread::run()
{
  while (!Terminated() && !_purge)
		{
			if (pEvent->Wait(5000))
				{
					if (!_purge)
						{
							//cout<<"TestThread:run"<<endl;
							printf("TestThread:run\r\n");
						}
				}
			else
				{
					//cout<<"TestThread:event not received (this is OK)"<<endl;
					printf("TestThread:event not received (this is OK)\r\n");
				}
		}
}


void TestThread::Purge()
{
	_purge = true;
	//cout<<"TestThread->Purge"<<endl;
	printf("TestThread->Purge\r\n");
  Go();
}



extern "C" void mainline ()
{
	//cout<<"TestThread App"<<endl;
	printf("Mainline\r\n");

  TestThread* t = new TestThread;
  t->start();

	// last two should fail
	for (unsigned i = 0; i < 6; i++)
		{
			Sleep (1000 * i);
			t->Go();
		}


	Sleep (10);
	delete t;


}
