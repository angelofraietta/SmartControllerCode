
#ifndef mutex_h
#define mutex_h 1



class Mutex 
{
  public:
    //## Destructor (generated)
      virtual ~Mutex();


    //## Other Operations (specified)
      //## Operation: Wait%1012451970
      virtual bool Obtain () = 0;

      //## Operation: Release%1012451971
      virtual void Release () = 0;

      //## Operation: create%1012532984
      static Mutex* create ();


};


inline Mutex::~Mutex()
{
}



#endif
