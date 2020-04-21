  //## begin module%3D473347019E.additionalIncludes preserve=no
  //## end module%3D473347019E.additionalIncludes

  //## begin module%3D473347019E.includes preserve=yes
  #include <stdio.h>
  #include <pthread.h>
  #include <sys/time.h>
  //#include <mach/mach.h>
  //#include <mach/clock.h>
  //#include <mach/mach_error.h>
  //## end module%3D473347019E.includes

  // Mutex
  #include "mutex.h"

  class LinuxMutex : public Mutex  //## Inherits: <unnamed>%3D4732DA0089
  {
    //## begin LinuxMutex%3D4732CC026A.initialDeclarations preserve=yes
    //## end LinuxMutex%3D4732CC026A.initialDeclarations

    public:
        LinuxMutex();

        ~LinuxMutex();


        bool Obtain ();

        void Release ();

        pthread_mutex_t count_mutex;
  };



  Mutex* Mutex::create ()
  {
          return new LinuxMutex;
  }


  LinuxMutex::LinuxMutex()
  {
    pthread_mutex_init(&count_mutex, NULL);
  }


  LinuxMutex::~LinuxMutex()
  {
    Release();
    pthread_mutex_destroy(&count_mutex);
  }



  bool LinuxMutex::Obtain ()
  {
    bool ret = true;
    pthread_mutex_lock(&count_mutex);
    return ret;
  }

  //## Operation: Release%1028069954
  void LinuxMutex::Release ()
  {
    pthread_mutex_unlock(&count_mutex);
  }
