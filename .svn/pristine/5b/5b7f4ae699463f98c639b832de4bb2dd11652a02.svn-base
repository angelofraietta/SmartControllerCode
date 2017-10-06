//#include <iostream.h>
#include <sound.h>
#include "activeobject.h"
#include "event.h"

#include <stdio.h>

#include <unistd.h>

void Sleep (unsigned long sleep_time)
{
	sleep(sleep_time); 
}
 
 
class TestThread:public ActiveObject
{
  public:
  TestThread (): _purge(false), pEvent(Event::create()){}
  ~TestThread (){Purge(); Sleep (2); kill(); delete pEvent;}
  void Go(){pEvent->Release();}
  void Purge();
  private:
  void run ();
  Event* pEvent;
  volatile bool _purge;

};


void TestThread::run()
{
	//cout<<"test Thread run"<<endl;
	
    while (!Terminated() && !_purge)
		{
			if (pEvent->Wait(2000))
				{
					if (!_purge)
						{
							//cout<<"TestThread:run"<<endl;
							SysBeep (200);
						}
				}
			else
				{
					//cout<<"TestThread:event not received (this is OK)"<<endl;
				}
		}

}


void TestThread::Purge()
{
	_purge = true;
	//cout<<"TestThread->Purge"<<endl;
  Go();
}



#pragma export on
extern "C" int DoThread ()
{
	//cout<<"TestThread App2"<<endl;



  TestThread* t = new TestThread;
  t->start();

	// last two should fail
	for (unsigned i = 0; i < 6; i++)
		{
		//cout<<"TestThread Main"<<i<<endl;
			Sleep (i);
			t->Go();
		}


	Sleep (1);
	delete t;

	return 0;

}

#pragma export off
