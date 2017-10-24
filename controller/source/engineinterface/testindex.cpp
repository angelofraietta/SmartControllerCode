#include <stdio.h>

#include <unistd.h>
#include <iostream>

#include "indexserver.h"

class TestClass{
public:
    TestClass (unsigned i) : _ival(i){}
    
    unsigned getIval()const {return _ival;}
private:
    const unsigned _ival;
};

int main ()
{
  const int num_elements = 2000;
    
  IndexServer <TestClass> server;
    
  std::cout<<"Hello World"<<std::endl;


  int int_size = sizeof(int);
  int long_size = sizeof(long);
  int* ptr = &int_size;
  int ptr_size = sizeof(ptr);
  
  
  
    std::cout<<"Int Size"<<int_size<<std::endl;
    std::cout<<"Long Size"<<long_size<<std::endl;

    std::cout<<"Pointer Size"<<ptr_size<<std::endl;

    for (unsigned i = 1; i <= num_elements; i++)
    {
        unsigned i_val = i * i;
        TestClass* new_class = new TestClass (i_val);
        server.addIndex(new_class);
    }
  
    for (unsigned i = 1; i <= num_elements; i++)
    {
        unsigned i_val = i * i;
        TestClass* new_class = server.getIdentityFromIndex(i);
        
        if (i_val != new_class->getIval())
        {
            std::cout<<"Fail on"<<i_val<<std::endl;
        }
        else
        {
            std::cout<<"Success "<<i<< " " << new_class->getIval()<<std::endl;
        }
        delete new_class;
    }
  
    
    return 0;

}
