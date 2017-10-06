//## begin module%3A8C9E890143.cm preserve=no
//    %X% %Q% %Z% %W%
//## end module%3A8C9E890143.cm

//## begin module%3A8C9E890143.cp preserve=no
//  Angelo Fraietta
//## end module%3A8C9E890143.cp

//## Module: e_list%3A8C9E890143; 
//  This is a double linked list
//## Subsystem: <Top Level>
//## Source file: c:\develop\estl\elist.h

//## begin module%3A8C9E890143.additionalIncludes preserve=no
//## end module%3A8C9E890143.additionalIncludes

//## begin module%3A8C9E890143.includes preserve=yes
//## end module%3A8C9E890143.includes

//## begin module%3A8C9E890143.declarations preserve=no
//## end module%3A8C9E890143.declarations

//## begin module%3A8C9E890143.additionalDeclarations preserve=yes

#ifdef HAL_MAC
#pragma supress_warnings on
#endif

#include "memorycache.h"
#ifndef _NO_NAMESPACES

//## end module%3A8C9E890143.additionalDeclarations


//## Modelname: estr_stl%3A7757A1023B
namespace sm_str {
  //## begin sm_str%3A7757A1023B.initialDeclarations preserve=yes
#endif 
  //## end sm_str%3A7757A1023B.initialDeclarations

  //## begin sm_str::list%3A8C9EC80306.preface preserve=yes
  //## end sm_str::list%3A8C9EC80306.preface

  //## Class: list%3A8C9EC80306; Parameterized Class
  //  A template class linked List
  //## Category: estr_stl%3A7757A1023B
  //## Subsystem: <Top Level>
  //## Persistence: Transient
  //## Cardinality/Multiplicity: n

  template <class T // The Type of object contained within the List
  >
  class list 
  {
    //## begin sm_str::list%3A8C9EC80306.initialDeclarations preserve=yes
    public: // if is this is not here some compilers make the iterator private
    //## end sm_str::list%3A8C9EC80306.initialDeclarations

    class iterator;

    public:
      //## begin sm_str::list::e_node%3A8C9F21023C.preface preserve=yes
      class iterator;
      //## end sm_str::list::e_node%3A8C9F21023C.preface

      //## Class: e_node%3A8C9F21023C
      //  A node for an item in the list
      //## Category: estr_stl%3A7757A1023B
      //## Persistence: Transient
      //## Cardinality/Multiplicity: n

      class e_node 
      {
        //## begin sm_str::list::e_node%3A8C9F21023C.initialDeclarations preserve=yes
        //## end sm_str::list::e_node%3A8C9F21023C.initialDeclarations

        public:
          //## Constructors (specified)
            //## Operation: e_node%982293871
            e_node (T data)
              //## begin sm_str::list::e_node::e_node%982293871.hasinit preserve=no
                  : _data(data), _previous(NULL), _next(NULL)
              //## end sm_str::list::e_node::e_node%982293871.hasinit
              //## begin sm_str::list::e_node::e_node%982293871.initialization preserve=yes
              //## end sm_str::list::e_node::e_node%982293871.initialization
            {
              //## begin sm_str::list::e_node::e_node%982293871.body preserve=yes
              //## end sm_str::list::e_node::e_node%982293871.body
            }

          //## Storage Management Operations (specified)
            //## Operation: operator new%1030411613
            static void* operator new (size_t size);

            //## Operation: operator delete%1030411614
            static void operator delete (void* mem);


          //## Other Operations (specified)
            //## Operation: detach%982293867
            list<T>::e_node* detach ()
            {
              //## begin sm_str::list::e_node::detach%982293867.body preserve=yes
              if (_next)
                {
                  _next->_next = _previous;
                }
              if (_previous)
                {
                  _previous->_previous = _next;
                }
              return _next;
              //## end sm_str::list::e_node::detach%982293867.body
            }

            //## Operation: data%982622338
            T& data ()
            {
              return _data;

              //## begin sm_str::list::e_node::data%982622338.body preserve=yes
              //## end sm_str::list::e_node::data%982622338.body
            }

          // Additional Public Declarations
            //## begin sm_str::list::e_node%3A8C9F21023C.public preserve=yes
            //## end sm_str::list::e_node%3A8C9F21023C.public

        protected:
          // Additional Protected Declarations
            //## begin sm_str::list::e_node%3A8C9F21023C.protected preserve=yes
            //## end sm_str::list::e_node%3A8C9F21023C.protected

        private:
          // Additional Private Declarations
            //## begin sm_str::list::e_node%3A8C9F21023C.private preserve=yes
            //## end sm_str::list::e_node%3A8C9F21023C.private

        private: //## implementation
          // Data Members for Class Attributes

            //## Attribute: _data%3A8CA69E0379
            //  The Data contained by the list
            //## begin sm_str::list::e_node::_data%3A8CA69E0379.attr preserve=no  private: T {U} data
            T _data;
            //## end sm_str::list::e_node::_data%3A8CA69E0379.attr

            //## Attribute: _mem_manager%3D6AD7D4034D
            //## begin sm_str::list::e_node::_mem_manager%3D6AD7D4034D.attr preserve=no  private: static MemoryCache {U} 
            static MemoryCache _mem_manager;
            //## end sm_str::list::e_node::_mem_manager%3D6AD7D4034D.attr

          // Data Members for Associations

            //## Association: estr_stl::<unnamed>%3A8C9F6302CD
            //## Role: e_node::_previous%3A8C9F6801A8
            //## begin sm_str::list::e_node::_previous%3A8C9F6801A8.role preserve=no  public: sm_str::list< T >::e_node {0..1 -> RFHN}
            e_node *_previous;
            //## end sm_str::list::e_node::_previous%3A8C9F6801A8.role

            //## Association: estr_stl::<unnamed>%3A8C9F6302CD
            //## Role: e_node::_next%3A8C9F68019E
            //## begin sm_str::list::e_node::_next%3A8C9F68019E.role preserve=no  public: sm_str::list< T >::e_node { -> 0..1RFHN}
            e_node *_next;
            //## end sm_str::list::e_node::_next%3A8C9F68019E.role

            //## Association: estr_stl::<unnamed>%3A8CA32003E2
            //## Role: e_node::<the_iterator>%3A8CA322036C
            //## begin sm_str::list::e_node::<the_iterator>%3A8CA322036C.role preserve=no  public: sm_str::list< T >::iterator {0..1 -> RFHN}
            //## end sm_str::list::e_node::<the_iterator>%3A8CA322036C.role

          // Additional Implementation Declarations
            //## begin sm_str::list::e_node%3A8C9F21023C.implementation preserve=yes
            friend class list <T>;
            //## end sm_str::list::e_node%3A8C9F21023C.implementation
          friend class iterator;
      };

      //## begin sm_str::list::e_node%3A8C9F21023C.postscript preserve=yes
      //## end sm_str::list::e_node%3A8C9F21023C.postscript

      //## begin sm_str::list::iterator%3A8CA2C50341.preface preserve=yes
      //## end sm_str::list::iterator%3A8CA2C50341.preface

      //## Class: iterator%3A8CA2C50341
      //  An iterator for the list
      //## Category: estr_stl%3A7757A1023B
      //## Persistence: Transient
      //## Cardinality/Multiplicity: n

      class iterator 
      {
        //## begin sm_str::list::iterator%3A8CA2C50341.initialDeclarations preserve=yes
        //## end sm_str::list::iterator%3A8CA2C50341.initialDeclarations

        public:
          //## Constructors (generated)
            iterator()
              //## begin iterator::iterator.hasinit preserve=no
                  : _current_node(NULL)
              //## end iterator::iterator.hasinit
              //## begin iterator::iterator.initialization preserve=yes
              //## end iterator::iterator.initialization
            {
              //## begin sm_str::list::iterator::iterator.body preserve=yes
              //## end sm_str::list::iterator::iterator.body
            }

            iterator(const iterator &right)
              //## begin iterator::iterator.hasinit preserve=no
                  : _current_node(NULL)
              //## end iterator::iterator.hasinit
              //## begin iterator::iterator.initialization preserve=yes
              //## end iterator::iterator.initialization
            {
              //## begin sm_str::list::iterator::iterator.body preserve=yes
              _current_node = right._current_node;
              //## end sm_str::list::iterator::iterator.body
            }

          //## Assignment Operation (generated)
            const iterator & operator=(const iterator &right)
            {
              //## begin sm_str::list::iterator::operator=.body preserve=yes
              _current_node = right._current_node;
              return *this;
              //## end sm_str::list::iterator::operator=.body
            }

          //## Equality Operations (generated)
            bool operator==(const iterator &right) const
            {
              //## begin sm_str::list::iterator::operator==.body preserve=yes
              return _current_node == right._current_node;
              //## end sm_str::list::iterator::operator==.body
            }

            bool operator!=(const iterator &right) const
            {
              //## begin sm_str::list::iterator::operator!=.body preserve=yes
              return !(*this == right);
              //## end sm_str::list::iterator::operator!=.body
            }

          //## Dereference Operation (generated)
            T& operator*() const
            {
              //## begin sm_str::list::iterator::operator*.body preserve=yes

              // note that this will barf if _current node is failed
              return _current_node->_data;
              //## end sm_str::list::iterator::operator*.body
            }


          //## Other Operations (specified)
            //## Operation: operator++%982293870
            list<T>::iterator& operator ++ ()
            {
              //## begin sm_str::list::iterator::operator++%982293870.body preserve=yes
              if (_current_node)
                {
                  _current_node = _current_node->_next;
                }
              return *this;
              //## end sm_str::list::iterator::operator++%982293870.body
            }

            //## Operation: operator+%982533119
            list<T>::iterator& operator + (unsigned size)
            {
              //## begin sm_str::list::iterator::operator+%982533119.body preserve=yes
              for (unsigned i = 0; i < size; i++)
                {
                  ++(*this);
                }
              return *this;
              //## end sm_str::list::iterator::operator+%982533119.body
            }

          // Additional Public Declarations
            //## begin sm_str::list::iterator%3A8CA2C50341.public preserve=yes
            //## end sm_str::list::iterator%3A8CA2C50341.public

        protected:
          // Additional Protected Declarations
            //## begin sm_str::list::iterator%3A8CA2C50341.protected preserve=yes
            //## end sm_str::list::iterator%3A8CA2C50341.protected

        private:
          // Additional Private Declarations
            //## begin sm_str::list::iterator%3A8CA2C50341.private preserve=yes
            //## end sm_str::list::iterator%3A8CA2C50341.private

        private: //## implementation
          // Data Members for Associations

            //## Association: estr_stl::<unnamed>%3A8CA32003E2
            //## Role: iterator::_current_node%3A8CA3220362
            //## begin sm_str::list::iterator::_current_node%3A8CA3220362.role preserve=no  public: sm_str::list< T >::e_node { -> 0..1RFHN}
            e_node *_current_node;
            //## end sm_str::list::iterator::_current_node%3A8CA3220362.role

          // Additional Implementation Declarations
            //## begin sm_str::list::iterator%3A8CA2C50341.implementation preserve=yes
            friend class list <T>;
            //## end sm_str::list::iterator%3A8CA2C50341.implementation
      };

      //## begin sm_str::list::iterator%3A8CA2C50341.postscript preserve=yes
      //## end sm_str::list::iterator%3A8CA2C50341.postscript

      //## Constructors (generated)
        list()
          //## begin list::list.hasinit preserve=no
              : _head(NULL), _tail(NULL)
          //## end list::list.hasinit
          //## begin list::list.initialization preserve=yes
          //## end list::list.initialization
        {
          //## begin sm_str::list::list.body preserve=yes
          //## end sm_str::list::list.body
        }

      //## Destructor (generated)
        ~list()
        {
          //## begin sm_str::list::~list.body preserve=yes
          while (_head)
            {
              e_node* next = _head->_next;
              delete _head;
              _head = next;
            }
          //## end sm_str::list::~list.body
        }


      //## Other Operations (specified)
        //## Operation: insert%982293868
        list<T>::e_node* insert (T element  // The element to be inserted
        )
        {
          //## begin sm_str::list::insert%982293868.body preserve=yes
          e_node* new_node = new e_node(element);
          if (new_node)
            {
              if (!_head)
                {
                  _head = new_node;
                  _tail = new_node;
                }
              else
                {
                  _tail->_next = new_node;
                  new_node->_previous = _tail;
                  _tail = new_node;
                }
            }
          return new_node;
          //## end sm_str::list::insert%982293868.body
        }

        //## Operation: erase%982293869
        void erase (list<T>::e_node* erased_node)
        {
          //## begin sm_str::list::erase%982293869.body preserve=yes
          if (erased_node)
            {
              if (erased_node->_next)
                {
                  erased_node->_next->_previous = erased_node->_previous;
                }
              if (erased_node->_previous)
                {
                  erased_node->_previous->_next = erased_node->_next;
                }
              
              if (erased_node == _head)
                {
                  _head = erased_node->_next;
                }
              if (erased_node == _tail)
                {
                  _tail = erased_node->_previous;
                }
              delete erased_node;
            }
          
          //## end sm_str::list::erase%982293869.body
        }

        //## Operation: begin%982293872
        list <T>::iterator begin ()
        {
          //## begin sm_str::list::begin%982293872.body preserve=yes
          iterator iter;
          iter._current_node = _head;
          return iter;
          //## end sm_str::list::begin%982293872.body
        }

        //## Operation: end%982293873
        list <T>::iterator end ()
        {
          //## begin sm_str::list::end%982293873.body preserve=yes
          iterator iter;
          return iter;
          
          //## end sm_str::list::end%982293873.body
        }

        //## Operation: erase%982533118
        void erase (list<T>::iterator start,  // The start iterator
        list<T>::iterator finish  // The element after the last one to erase
        )
        {
          //## begin sm_str::list::erase%982533118.body preserve=yes
          e_node* current = start._current_node;
          
          if (current)
            {
              // first make sure the head and tail are ging to be right
              if (current == _head)
                {
                  _head = finish._current_node;
                }
              
              if (!finish._current_node) // then it is the end
                {
                  _tail = current->_previous;
                }
              
              while (current && current != finish._current_node)
                {
                  if (current->_next)
                    {
                      current->_next->_previous = current->_previous;
                    }
                  if (current->_previous)
                    {
                      current->_previous->_next = current->_next;
                    }
                  
                  e_node* next = current->_next;
                  delete current;
                  current = next;
                }
            }
          //## end sm_str::list::erase%982533118.body
        }

        //## Operation: push_front%982533123
        list<T>::e_node* push_front (T element  // The element to be inserted
        )
        {
          //## begin sm_str::list::push_front%982533123.body preserve=yes
          e_node* new_node = new e_node(element);
          if (new_node)
            {
              if (!_head)
                {
                  _head = new_node;
                  _tail = new_node;
                }
              else
                {
                  _head->_previous = new_node;
                  new_node->_next = _head;
                  _head = new_node;
                }
            }
          return new_node;
          
          //## end sm_str::list::push_front%982533123.body
        }

    public:
      // Additional Public Declarations
        //## begin sm_str::list%3A8C9EC80306.public preserve=yes
        //## end sm_str::list%3A8C9EC80306.public

    protected:
      // Additional Protected Declarations
        //## begin sm_str::list%3A8C9EC80306.protected preserve=yes
        //## end sm_str::list%3A8C9EC80306.protected

    private:
      // Additional Private Declarations
        //## begin sm_str::list%3A8C9EC80306.private preserve=yes
        //## end sm_str::list%3A8C9EC80306.private

    private: //## implementation
      // Data Members for Associations

        //## Association: estr_stl::<unnamed>%3A8C9FEC023E
        //## Role: list::_head%3A8C9FED01EF
        //## begin sm_str::list::_head%3A8C9FED01EF.role preserve=no  public: sm_str::list< T >::e_node { -> 0..1RFHN}
        e_node *_head;
        //## end sm_str::list::_head%3A8C9FED01EF.role

        //## Association: estr_stl::<unnamed>%3A8CA8120392
        //## Role: list::_tail%3A8CA815006B
        //## begin sm_str::list::_tail%3A8CA815006B.role preserve=no  public: sm_str::list< T >::e_node { -> RFHN}
        e_node *_tail;
        //## end sm_str::list::_tail%3A8CA815006B.role

      // Additional Implementation Declarations
        //## begin sm_str::list%3A8C9EC80306.implementation preserve=yes
        //## end sm_str::list%3A8C9EC80306.implementation

  };

  //## begin sm_str::list%3A8C9EC80306.postscript preserve=yes
  //## end sm_str::list%3A8C9EC80306.postscript

  // Class sm_str::list::e_node 


  //## begin sm_str::list::e_node::_mem_manager%3D6AD7D4034D.attr preserve=no  private: static MemoryCache {U} 
  template <class T>
  MemoryCache list< T >::e_node::_mem_manager ;
  //## end sm_str::list::e_node::_mem_manager%3D6AD7D4034D.attr






  //## Operation: operator new%1030411613
  template <class T>
  void* list< T >::e_node::operator new (size_t size)
  {
    //## begin sm_str::list::e_node::operator new%1030411613.body preserve=yes
    return _mem_manager.allocate(size);
    //## end sm_str::list::e_node::operator new%1030411613.body
  }

  //## Operation: operator delete%1030411614
  template <class T>
  void list< T >::e_node::operator delete (void* mem)
  {
    //## begin sm_str::list::e_node::operator delete%1030411614.body preserve=yes
    _mem_manager.free(mem);    
    //## end sm_str::list::e_node::operator delete%1030411614.body
  }


  // Additional Declarations
    //## begin sm_str::list::e_node%3A8C9F21023C.declarations preserve=yes
    //## end sm_str::list::e_node%3A8C9F21023C.declarations

  // Class sm_str::list::iterator 


  // Additional Declarations
    //## begin sm_str::list::iterator%3A8CA2C50341.declarations preserve=yes
    //## end sm_str::list::iterator%3A8CA2C50341.declarations

  // Parameterized Class sm_str::list 



  // Additional Declarations
    //## begin sm_str::list%3A8C9EC80306.declarations preserve=yes
#ifndef _NO_NAMESPACES
    //## end sm_str::list%3A8C9EC80306.declarations
} // namespace sm_str

//## begin module%3A8C9E890143.epilog preserve=yes
#endif //No Namespace

#ifdef HAL_MAC
#pragma supress_warnings off
#endif

//## end module%3A8C9E890143.epilog
