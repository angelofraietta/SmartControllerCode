#include <windows.h>
#include <iostream.h>
#include "activeObject.h"
#include "event.h"
#include <stdio.h>
#include <conio.h>

class TestThread:public ActiveObject
{
  public:
  TestThread (): _purge(false), pEvent (Event::create()){}
  ~TestThread (){Purge(); kill(); delete pEvent;}
  void Go(){pEvent->Release();}
  private:
  void run ();
  Event* pEvent;
  volatile bool _purge;
  void Purge();
};


void TestThread::run()
{
  while (!Terminated() && !_purge)
  {
  	if (pEvent->Wait(5000))
    {
  		if (!_purge)
    	{
	    	cout<<"TestThread:run"<<endl;
    	}
    }
    else
    {
	    cout<<"TestThread:event fail"<<endl;
		}
  }
}

void TestThread::Purge()
{
	_purge = true;
  Go();
}

void main ()
{
  TestThread t;
  t.start();

  while (getch() != 'x')
 		t.Go();


}
