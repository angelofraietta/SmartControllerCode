   //## begin module%3D4719D5004D.cm preserve=no
   //        %X% %Q% %Z% %W%
   //## end module%3D4719D5004D.cm

   //## begin module%3D4719D5004D.cp preserve=no
   //      Angelo Fraietta
   //## end module%3D4719D5004D.cp

   //## Module: LinuxThread%3D4719D5004D; Package body
   //## Subsystem: hal_mac%3B255F3402D7
   //## Source file: c:\develop\multithreads\source\hal_mac\linuxThread.cpp

   //## begin module%3D4719D5004D.additionalIncludes preserve=no
   //## end module%3D4719D5004D.additionalIncludes

   //## begin module%3D4719D5004D.includes preserve=yes
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
   #include "activeobject.h"

   #include <iostream>
   //## end module%3D4719D5004D.includes

   // MultiThread
   #include "multithread.h"

   class LinuxThread;


   //## begin module%3D4719D5004D.declarations preserve=no
   //## end module%3D4719D5004D.declarations

   //## begin module%3D4719D5004D.additionalDeclarations preserve=yes

   #define kDefaultThreadStackSize 0
   extern "C" void* ThreadEntry (void* param);

   //## end module%3D4719D5004D.additionalDeclarations


   //## begin LinuxThread%3D47197A0363.preface preserve=yes
   //## end LinuxThread%3D47197A0363.preface

   //## Class: LinuxThread%3D47197A0363
   //## Category: MultiThread::hal_mac%3D4719390298
   //## Subsystem: hal_mac%3B255F3402D7
   //## Persistence: Transient
   //## Cardinality/Multiplicity: n

   class LinuxThread : public MultiThread  //## Inherits: <unnamed>%3D4719900076
   {
     //## begin LinuxThread%3D47197A0363.initialDeclarations preserve=yes
     //## end LinuxThread%3D47197A0363.initialDeclarations

     public:
       //## Constructors (specified)
         //## Operation: LinuxThread%1028069949
         LinuxThread (ActiveObject* pActive);


       //## Other Operations (specified)
         //## Operation: resume%1028069950
         void resume ();

         //## Operation: wait%1028069951
         void wait (unsigned long period // The period we are going to wait
         );

       // Additional Public Declarations
         //## begin LinuxThread%3D47197A0363.public preserve=yes
         //## end LinuxThread%3D47197A0363.public

     protected:
       // Additional Protected Declarations
         //## begin LinuxThread%3D47197A0363.protected preserve=yes
         //## end LinuxThread%3D47197A0363.protected

     private:
       // Additional Private Declarations
         //## begin LinuxThread%3D47197A0363.private preserve=yes
         //## end LinuxThread%3D47197A0363.private

     private: //## implementation
       // Additional Implementation Declarations
         //## begin LinuxThread%3D47197A0363.implementation preserve=yes
     pthread_t _threadId;

         //## end LinuxThread%3D47197A0363.implementation
   };

   //## begin LinuxThread%3D47197A0363.postscript preserve=yes
   //## end LinuxThread%3D47197A0363.postscript

   // Class LinuxThread

   // Class MultiThread



   //## Other Operations (implementation)
   //## Operation: create%994716922
   //      Static create function that returns the sub class,
   //      depending upon the component
   MultiThread* MultiThread::create (ActiveObject* pActive)
   {
     //## begin MultiThread::create%994716922.body preserve=yes
     return new LinuxThread(pActive);
     //## end MultiThread::create%994716922.body
   }

   // Additional Declarations
     //## begin MultiThread%3B255966033E.declarations preserve=yes
     //## end MultiThread%3B255966033E.declarations

   // Class LinuxThread

   //## Operation: LinuxThread%1028069949
   //      Constructor with parameter that points to ActiveObject
   LinuxThread::LinuxThread (ActiveObject* pActive)
     //## begin LinuxThread::LinuxThread%1028069949.hasinit preserve=no
     //## end LinuxThread::LinuxThread%1028069949.hasinit
     //## begin LinuxThread::LinuxThread%1028069949.initialization preserve=yes
           :MultiThread (pActive)
     //## end LinuxThread::LinuxThread%1028069949.initialization
   {
     //## begin LinuxThread::LinuxThread%1028069949.body preserve=yes
     //## end LinuxThread::LinuxThread%1028069949.body
   }



   //## Other Operations (implementation)
   //## Operation: resume%1028069950
   void LinuxThread::resume ()
   {
     //## begin LinuxThread::resume%1028069950.body preserve=yes

     if (pthread_create(&_threadId, NULL, ThreadEntry, (void*)_pActive))
     {
       printf("Unable to create task");
     }

     //## end LinuxThread::resume%1028069950.body
   }


   //## Operation: wait%1028069951
   //      Waits for the thread to finish
   void LinuxThread::wait (unsigned long period)
   {
     //## begin LinuxThread::wait%1028069951.body preserve=yes
    pthread_kill(_threadId, 0);
    #pragma unused(period)

     //## end LinuxThread::wait%1028069951.body
   }

   // Additional Declarations
     //## begin LinuxThread%3D47197A0363.declarations preserve=yes
     //## end LinuxThread%3D47197A0363.declarations

   //## begin module%3D4719D5004D.epilog preserve=yes
   extern "C" void* ThreadEntry (void* param)
   {
       ActiveObject * pActive = (ActiveObject *) param;

           //sleep(1);
       pActive->initialise ();
       pActive->run ();



           printf("End Thread Entry");
           pthread_exit (NULL);

   }

   //## end module%3D4719D5004D.epilog