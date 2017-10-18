
//## begin module%3D473347019E.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3D473347019E.additionalIncludes

//## begin module%3D473347019E.includes preserve=yes
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <mach/mach.h>
#include <mach/clock.h>
#include <mach/mach_error.h>
//## end module%3D473347019E.includes

// Mutex
#include "mutex.h"

class MacMutex : public Mutex  //## Inherits: <unnamed>%3D4732DA0089
{
  //## begin MacMutex%3D4732CC026A.initialDeclarations preserve=yes
  //## end MacMutex%3D4732CC026A.initialDeclarations

  public:
      MacMutex();

      ~MacMutex();


      bool Obtain ();

      void Release ();

      pthread_mutex_t count_mutex;
};



Mutex* Mutex::create ()
{
	return new MacMutex;
}


MacMutex::MacMutex()
{
  pthread_mutex_init(&count_mutex, NULL);
}


MacMutex::~MacMutex()
{
  Release();
  pthread_mutex_destroy(&count_mutex);
}



bool MacMutex::Obtain ()
{
  bool ret = true;
  pthread_mutex_lock(&count_mutex);
  return ret;
}

//## Operation: Release%1028069954
void MacMutex::Release ()
{
  pthread_mutex_unlock(&count_mutex);
}

