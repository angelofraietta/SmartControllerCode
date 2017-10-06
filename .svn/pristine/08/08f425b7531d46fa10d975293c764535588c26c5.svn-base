
#include <iostream.h>
#include <conio.h>
#include <stdlib.h>


#include "memorycache.h"
#include "elist.h"
#include "evector.h"
#include "emap.h"
#include "equeue.h"

#define MAX_SIZE  20
int int_array [MAX_SIZE];
sm_str::vector <int*> int_vect (10);
sm_str::map <int, int> the_map;
sm_str::list <int> the_list;
sm_str::priority_queue <int> the_priority_queue;

sm_str::e_static_queue <int> the_static_queue (MAX_SIZE);

void test_priority_queue()
{
  cout<<"Pushing 10 random items onto Priority queue"<<endl;

  for (unsigned i = 0; i < 10; i++)
  {
    int num = rand ();
    the_priority_queue.push (num);
    cout <<num<<endl;
  }
  cout <<"display them all"<<endl;

  while (!the_priority_queue.empty())
  {
    int num = the_priority_queue.top();
    cout<<num<<endl;
    the_priority_queue.pop ();
  }
 
}

void test_static_queue ()
{
	unsigned i;

	for (i = 0; i < MAX_SIZE; i++)
  {
  	the_static_queue.push(i);
  }

	if (the_static_queue.push(0))
  {
  	cout<<"static queue pushed past full"<<endl;
  }

  while (!the_static_queue.empty())
  {
  	cout<<the_static_queue.top()<<endl;
    the_static_queue.pop();

    if (i < MAX_SIZE * 2)
    {
	    the_static_queue.push(i);
      i++;
    }

  }

}

void iterate_vector()
{
  cout<<"press any key to display the elements..."<<endl;
  getch();

  for (unsigned i = 0; i < int_vect.size(); i++)
  {
    cout<<"element "<<i<<" :"<<*(int_vect[i])<<endl;
  }
}

void iterate_map()
{

  sm_str::map <int, int>::iterator iter;

  for (iter = the_map.begin(); iter != the_map.end(); ++iter)
  {
    cout<<(*iter).second<<" "<<endl;
  }
  cout<<"press any key to continue...";
  getch();
}

void iterate_list()
{

  sm_str::list <int>::iterator iter;

  for (iter = the_list.begin(); iter != the_list.end(); ++iter)
  {
    cout<<(*iter)<<" "<<endl;
  }
  cout<<"press any key to continue...";
  getch();
}

void test_list()
{
  cout <<" Fill list"<<endl;

  for (int i = 0; i < MAX_SIZE; i++)
  {
    the_list.insert(i);
  }

  cout<<"Iterate List"<<endl;
  //iterate_map();
  iterate_list();

  cout<<" Keep first ten"<<endl;
  the_list.erase (the_list.begin() + 10, the_list.end());

  iterate_list();


  cout<<"Erase just the second and third"<<endl;
  the_list.erase (the_list.begin()+1, the_list.begin() + 3);

  iterate_list();

  cout<<"Erase first three"<<endl;
  // erase first three
  the_list.erase (the_list.begin(), the_list.begin() + 3);

  iterate_list();

  cout<<"add number 5 to the end"<<endl;

  the_list.insert (5);

  iterate_list();


  cout <<"add number 10 to front"<<endl;
  the_list.push_front (10);
  iterate_list();
  
  cout <<"Erase Entire List"<<endl;
  the_list.erase (the_list.begin(), the_list.end());
  iterate_list();
}

void test_vector ()
{
  cout<<"Initial Capacity :"<<int_vect.capacity()<<endl;
  cout<<"Initial Size :"<<int_vect.size()<<endl;

  cout <<"now fill vector up from back"<<endl;

  for (unsigned i = 0; i < MAX_SIZE; i++)
  {
    int_vect.push_back (&int_array[i]);
    cout<<"Capacity :"<<int_vect.capacity()<<endl;
    cout<<"Size :"<<int_vect.size()<<endl;
  }

  iterate_vector();

  cout<<"press any key to push them to the front.."<<endl;
  getch();

  for (unsigned i = 0; i < MAX_SIZE; i++)
  {
    int_vect.push_front (&int_array[i]);
    cout<<"Capacity :"<<int_vect.capacity()<<endl;
    cout<<"Size :"<<int_vect.size()<<endl;
  }

  iterate_vector();

  cout <<"Pop 3 off back"<<endl;
  for (unsigned i = 0; i < 3; i++)
  {
    int_vect.pop_back();
  }
  iterate_vector();

  cout <<"Pop 3 off front"<<endl;
  for (unsigned i = 0; i < 3; i++)
  {
    int_vect.erase(&int_vect [0]);
  }

  iterate_vector();

  cout <<"Remove 1 - 10 and iterate with iterator"<<endl;
  int_vect.erase (int_vect.begin () + 1, int_vect.begin () + 11);

  sm_str::vector <int*>::iterator iter;

  for (iter = int_vect.begin(); iter != int_vect.end (); ++iter)
  {
    cout<<endl<<*(*iter);
  }

  cout<<"press any key to continue...";
  getch();
  cout <<"Erase entire vector"<<endl;
  int_vect.erase (int_vect.begin (), int_vect.end ());
  iterate_vector ();

}

void test_map ()
{
  for (int i = 0; i < MAX_SIZE; i++)
  {
    the_map.insert(sm_str::map <int, int>::value_type (i, i));
  }

  // now remove them all
  for (int i = 0; i < MAX_SIZE; i++)
  {
    the_map.erase(i);
    cout <<"depth = "<<the_map.depth()<<endl;
    cout<<"Map size = "<<the_map.size()<<endl;
  }

  // lets iterate
  iterate_map ();
  getch();
  // now reverse
  for (int i = MAX_SIZE -1; i >= 0; i--)
  {
    the_map.insert(sm_str::map <int, int>::value_type (i, i));
  }

  // now remove them all
  for (int i = MAX_SIZE -1; i >= 0; i--)
  {
    the_map.erase(i);
    cout <<"depth = "<<the_map.depth()<<endl;
    cout<<"Map size = "<<the_map.size()<<endl;
  }
  char buff [20];
  cout<<"Press a Number to Display or c to continue >";
  cin>>buff;

  //unsigned i = 0;

  while (buff [0] != 'c' && buff [0] != 'C')
  {
    int index = atoi (buff);

    the_map.insert(sm_str::map <int, int>::value_type (index, index));
    cout <<"depth = "<<the_map.depth()<<endl;
    cout<<"Map size = "<<the_map.size()<<endl;


    if (the_map.count (index))
    {
      cout <<"Value = "<<the_map [index]<<endl;
    }
    else
    {
      cout <<"That number not present"<<endl;
    }

  cout<<"Press a Number to Display or c to continue >"<<endl;
  cin>>buff;
  }

  cout<<"erase entire map"<<endl;
  the_map.purge();
  iterate_map();
}

void main ()
{
  bool exit = false;
  char buff[80];

  for (unsigned i = 0; i < MAX_SIZE; i++)
  {
    int_array [i] = i;
  }

  do
    {
      cout <<"Select L for List, M for Map, V for vector, P for Priority Queue, S for Static Queue, or X for exit>";
      cin>>buff;

      switch (buff[0])
      {
      case 'x':
      case 'X':
        exit = true;
        break;

      case 'v':
      case 'V':
        test_vector();
        break;

      case 'M':
      case 'm':
        test_map();
        break;

      case 'l':
      case 'L':
        test_list();
        break;

      case 's':
      case 'S':
      	test_static_queue();
        break;

      case 'p':
      case 'P':
        test_priority_queue();
        break;

      default:
        cout<<"invalid selection"<<endl;
      }
    }   while (!exit);

}
