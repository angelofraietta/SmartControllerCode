#include <windows.h>

#include <conio.h>
#include <stdio.h>
#include <stddef.h>
#include "ringqueue.h"
#include "controlfilter.h"

#define Q_SIZE 127

const BYTE DLE_CHARS [] = {0x01};

void main ()
{
  RingQueue q (Q_SIZE);
  ControlFilter cf (DLE_CHARS, sizeof(DLE_CHARS));
  bool running_dle = false;

  if(!cf.Valid())
  {
    cout<<"Invalid control filter. Press any key to exit..."<<endl;
    getch();
    return;
  }

  cout<<"push "<<Q_SIZE<<" elements onto q. Add one more should fail"<<endl;
  BYTE i;

  for (i = 0; i <= Q_SIZE; i++)
  {
    BYTE encoded_val = i;
    BYTE dle_char = cf.Encode(&encoded_val);
    if (dle_char)
    {
      q.push(dle_char);
      cout<<"push dle"<<(int)dle_char<<endl;
    }

    if (!q.push(encoded_val))
    {
      cout<<"push failed on element number "<<(int)(i + 1)<<endl;
    }
    else
    {
      cout<<"push "<<(int)encoded_val<<endl;
    }
  }

  cout<<"q size = "<<q.size()<<endl;
  cout<<"press any key to read half..."<<endl;
  getch();


  for(unsigned j = 0; j < Q_SIZE / 2; j++)
  {
    BYTE x = q.front();
    if (cf.Decode(&x, &running_dle))
    {
      cout<<(int)x<<endl;
    }
    q.pop();
  }

  cout<<"q size = "<<q.size()<<endl;
  cout<<"press any key to re-fill queue..."<<endl;
  getch();

  for (i = 0; i <= Q_SIZE; i++)
  {
    if (!q.push(i))
    {
      cout<<"push failed on element number "<<(int)(i + 1)<<endl;
    }
    else
    {
      cout<<"push "<<(int)i<<endl;
    }

  }

  cout<<"q size = "<<q.size()<<endl;
  cout<<"press any key to read all..."<<endl;
  getch();

  while(!q.empty())
  {
    int x = q.front();
    cout<<x<<endl;
    q.pop();
  }

  cout<<"q size = "<<q.size()<<endl;
  cout<<"press any key to finish..."<<endl;
  getch();
}