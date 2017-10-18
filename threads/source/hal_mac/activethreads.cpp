
#include "activeobject.h"
#include "event.h"
#include "mutex.h"

#include <stdio.h>

#include <unistd.h>
#include <iostream>


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
  std::cout<<"test Thread run"<<std::endl;
	
    while (!Terminated() && !_purge)
		{
			if (pEvent->Wait(3000))
				{
					if (!_purge)
						{
						  std::cout<<"TestThread:run"<<std::endl;
							//SysBeep (200);
						}
				}
			else
				{
				  std::cout<<"TestThread:event not received (this is OK)"<<std::endl;
				}
		}

}


void TestThread::Purge()
{
	_purge = true;
	std::cout<<"TestThread->Purge"<<std::endl;
  Go();
}




int main ()
{
  Mutex* mutex = Mutex::create();
  
  std::cout<<"TestThread App2"<<std::endl;


  int int_size = sizeof(int);
  int long_size = sizeof(long);
  int* ptr = &int_size;
  int ptr_size = sizeof(ptr);
  
    std::cout<<"Int Size"<<int_size<<std::endl;
    std::cout<<"Long Size"<<long_size<<std::endl;

    std::cout<<"Pointer Size"<<ptr_size<<std::endl;

  
  TestThread* t = new TestThread;
  t->start();

	// last two should fail
	for (unsigned i = 0; i < 6; i++)
		{
                std::cout<<"TestThread Main"<<i<<std::endl;
                mutex->Obtain();
                Sleep (i);
                t->Go();
                mutex->Release();
		}


	Sleep (1);
	delete t;

	return 0;

}
