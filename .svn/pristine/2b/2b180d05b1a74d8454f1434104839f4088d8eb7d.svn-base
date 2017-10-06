//## begin module%3A90440C00D7.cm preserve=no
//    %X% %Q% %Z% %W%
//## end module%3A90440C00D7.cm

//## begin module%3A90440C00D7.cp preserve=no
//  Angelo Fraietta
//## end module%3A90440C00D7.cp

//## Module: e_vector%3A90440C00D7; 
//## Subsystem: <Top Level>
//## Source file: c:\develop\estl\evector.h

//## begin module%3A90440C00D7.additionalIncludes preserve=no
//## end module%3A90440C00D7.additionalIncludes

//## begin module%3A90440C00D7.includes preserve=yes
#ifndef _ESTL_VECTOR_H
#define _ESTL_VECTOR_H

#ifdef HAL_MAC
#pragma supress_warnings on
#endif

#ifndef _NO_NAMESPACES
//## end module%3A90440C00D7.includes


//## Modelname: estr_stl%3A7757A1023B
namespace sm_str {
  template <class T> class vector;

} // namespace sm_str

//## begin module%3A90440C00D7.declarations preserve=no
//## end module%3A90440C00D7.declarations

//## begin module%3A90440C00D7.additionalDeclarations preserve=yes
//## end module%3A90440C00D7.additionalDeclarations


namespace sm_str {
  //## begin sm_str%3A7757A1023B.initialDeclarations preserve=yes
#endif // no namespaces
  //## end sm_str%3A7757A1023B.initialDeclarations

  //## begin sm_str::vector%3A763E800375.preface preserve=yes
  //## end sm_str::vector%3A763E800375.preface

  //## Class: vector%3A763E800375; Parameterized Class
  //  Vector of non-pointer types
  //## Category: estr_stl%3A7757A1023B
  //## Subsystem: <Top Level>
  //## Persistence: Transient
  //## Cardinality/Multiplicity: n

  template <class T // This is a non-pointer type object
  >
  class vector 
  {
    //## begin sm_str::vector%3A763E800375.initialDeclarations preserve=yes
    //## end sm_str::vector%3A763E800375.initialDeclarations

    public:
      //## begin sm_str::vector::iterator%3A905648024C.preface preserve=yes
      //## end sm_str::vector::iterator%3A905648024C.preface

      //## Class: iterator%3A905648024C
      //  An iterator for the vector
      //## Category: estr_stl%3A7757A1023B
      //## Persistence: Transient
      //## Cardinality/Multiplicity: n

      class iterator 
      {
        //## begin sm_str::vector::iterator%3A905648024C.initialDeclarations preserve=yes
        //## end sm_str::vector::iterator%3A905648024C.initialDeclarations

        public:
          //## Constructors (generated)
            iterator(const iterator &right)
              //## begin iterator::iterator.hasinit preserve=no
                  : _current(0), _vec(NULL)
              //## end iterator::iterator.hasinit
              //## begin iterator::iterator.initialization preserve=yes
              //## end iterator::iterator.initialization
            {
              //## begin sm_str::vector::iterator::iterator.body preserve=yes
              (*this) = right;
              //## end sm_str::vector::iterator::iterator.body
            }

          //## Constructors (specified)
            //## Operation: iterator%982533122
            iterator (vector<T>* vect = NULL, unsigned current = 0)
              //## begin sm_str::vector::iterator::iterator%982533122.hasinit preserve=no
              : _current(0), _vec(NULL)
              //## end sm_str::vector::iterator::iterator%982533122.hasinit
              //## begin sm_str::vector::iterator::iterator%982533122.initialization preserve=yes
              //## end sm_str::vector::iterator::iterator%982533122.initialization
              {
                //## begin sm_str::vector::iterator::iterator%982533122.body preserve=yes
                _vec = vect;
                _current = current;
                //## end sm_str::vector::iterator::iterator%982533122.body
            }

          //## Assignment Operation (generated)
            const iterator & operator=(const iterator &right)
            {
              //## begin sm_str::vector::iterator::operator=.body preserve=yes
              _vec = right._vec;
              _current = right._current;
              return *this;
              //## end sm_str::vector::iterator::operator=.body
            }
            
            //## Equality Operations (generated)
            bool operator==(const iterator &right) const
            {
              //## begin sm_str::vector::iterator::operator==.body preserve=yes
              return _vec == right._vec && _current == right._current;
              //## end sm_str::vector::iterator::operator==.body
            }
            
            bool operator!=(const iterator &right) const
            {
              //## begin sm_str::vector::iterator::operator!=.body preserve=yes
              return !(*this == right);
              //## end sm_str::vector::iterator::operator!=.body
            }
            
            //## Dereference Operation (generated)
            T& operator*() const
              {
                //## begin sm_str::vector::iterator::operator*.body preserve=yes
                //  There must be a valid vector associated with this
                //  iterator and current must be less than the vector size
                
                return (*_vec)[_current];
                //## end sm_str::vector::iterator::operator*.body
              }
            
            
            //## Other Operations (specified)
            //## Operation: operator++%982533120
            vector<T>::iterator& operator ++ ()
              {
                //## begin sm_str::vector::iterator::operator++%982533120.body preserve=yes
                _current++;
                return *this;
                //## end sm_str::vector::iterator::operator++%982533120.body
              }
            
            //## Operation: operator+%982533121
            vector<T>::iterator& operator + (unsigned size  // The amount to increae by
                                             )
              {
                //## begin sm_str::vector::iterator::operator+%982533121.body preserve=yes
                _current += size;
                return *this;
                //## end sm_str::vector::iterator::operator+%982533121.body
              }
            
            // Additional Public Declarations
            //## begin sm_str::vector::iterator%3A905648024C.public preserve=yes
            //## end sm_str::vector::iterator%3A905648024C.public
            
      protected:
            // Additional Protected Declarations
            //## begin sm_str::vector::iterator%3A905648024C.protected preserve=yes
            //## end sm_str::vector::iterator%3A905648024C.protected
            
      private:
            // Additional Private Declarations
            //## begin sm_str::vector::iterator%3A905648024C.private preserve=yes
            //## end sm_str::vector::iterator%3A905648024C.private
            
      private: //## implementation
            // Data Members for Class Attributes
            
            //## Attribute: _current%3A905B550179
            //## begin sm_str::vector::iterator::_current%3A905B550179.attr preserve=no  private: unsigned {U} 0
            unsigned _current;
            //## end sm_str::vector::iterator::_current%3A905B550179.attr
            
            // Data Members for Associations
            
            //## Association: estr_stl::<unnamed>%3A905F3A02A9
            //## Role: iterator::_vec%3A905F3B0296
            //## begin sm_str::vector::iterator::_vec%3A905F3B0296.role preserve=no  public: sm_str::vector { -> 0..1RFHN}
            vector *_vec;
            //## end sm_str::vector::iterator::_vec%3A905F3B0296.role
            
            // Additional Implementation Declarations
            //## begin sm_str::vector::iterator%3A905648024C.implementation preserve=yes
            friend class vector<T>;
            //## end sm_str::vector::iterator%3A905648024C.implementation
      };
      
      //## begin sm_str::vector::iterator%3A905648024C.postscript preserve=yes
      //## end sm_str::vector::iterator%3A905648024C.postscript
      
      //## Constructors (specified)
      //## Operation: vector%980824871
      vector (unsigned initial_size = 0)
        //## begin sm_str::vector::vector%980824871.hasinit preserve=no
        : _size(0), _data(NULL), _capacity(0), _growsize(256)
        //## end sm_str::vector::vector%980824871.hasinit
        //## begin sm_str::vector::vector%980824871.initialization preserve=yes
        //## end sm_str::vector::vector%980824871.initialization
        {
          //## begin sm_str::vector::vector%980824871.body preserve=yes
          reserve (initial_size);
          //## end sm_str::vector::vector%980824871.body
        }
      
      //## Destructor (generated)
      ~vector()
        {
          //## begin sm_str::vector::~vector.body preserve=yes
          delete [] _data;
          //## end sm_str::vector::~vector.body
        }
      
      
      //## Other Operations (specified)
      //## Operation: size%980824872
      unsigned size () const
        {
          //## begin sm_str::vector::size%980824872.body preserve=yes
          //## end sm_str::vector::size%980824872.body
          
          return _size;
        }
      
      //## Operation: capacity%980824873
      unsigned capacity () const
        {
          //## begin sm_str::vector::capacity%980824873.body preserve=yes
          //## end sm_str::vector::capacity%980824873.body
          
          return _capacity;
        }
      
      //## Operation: reserve%980824874
      void reserve (unsigned new_size)
        {
          //## begin sm_str::vector::reserve%980824874.body preserve=yes
          if (new_size && _capacity < new_size)
            {
              T* new_data = new T [new_size];
              
              if (new_data)
                {
                  // copy the elements over
                  for (unsigned i = 0; i < _capacity; i++)
                    {
                      new_data [i] = _data [i];
                    }
                  
                  // free the old array and assign to the new
                  delete [] _data;
                  _data = new_data;
                  _capacity = new_size;
                }
              
            }
          //## end sm_str::vector::reserve%980824874.body
        }
      
      //## Operation: push_back%980824875
      void push_back (T new_element)
        {
          //## begin sm_str::vector::push_back%980824875.body preserve=yes
          if (_size == _capacity)
            {
              reserve (_capacity + _growsize);
            }
          
          // lets check that size is now less in case the reserve failed
          if (_size < _capacity)
            {
              _data [_size] = new_element;
              _size++;
            }
          
          //## end sm_str::vector::push_back%980824875.body
        }
      
      //## Operation: push_front%980824876
      void push_front (T new_element)
        {
          //## begin sm_str::vector::push_front%980824876.body preserve=yes
          if (_size == _capacity)
            {
              reserve (_capacity + _growsize);
            }
          
          // lets check that size is now less in case the reserve failed
          if (_size < _capacity)
            {
              // move the elements up by one
              for (unsigned i = _size; i > 0; i--)
                {
                  _data [i] = _data [i-1];
                }
              
              _data [0] = new_element;
              _size++;
            }
          
          //## end sm_str::vector::push_front%980824876.body
        }
      
      //## Operation: operator []%980824877
      T& operator [] (unsigned index  // The index requested
                      )
        {
          //## begin sm_str::vector::operator []%980824877.body preserve=yes
          return _data [index];
          //## end sm_str::vector::operator []%980824877.body
        }
      
      //## Operation: erase%980824878
      void erase (const T* element  // The address of the elment to erase.
                  )
        {
          //## begin sm_str::vector::erase%980824878.body preserve=yes
          bool found = false;
          unsigned i = 0;
          
          while (!found && i < _size)
            {
              // compare the memory adresses
              if (element ==  _data + i)
                {
                  found = true;
                }
              else
                {
                  i++;
                }
            } // end while
          
          if (found)
            {
              // move all the elements back one space
              while (i < _size - 1)
                {
                  _data [i] = _data [i+1];
                  i++;
                }
              
              // now pop last one off the back
              pop_back();
            }
          //## end sm_str::vector::erase%980824878.body
        }
      
      //## Operation: pop_back%980824879
      void pop_back ()
        {
          //## begin sm_str::vector::pop_back%980824879.body preserve=yes
          if (_size)
            
            {
              // overwrite the last element with a default value T
              // because it may have resources attached to it
              T t; // a default T
              _data[_size - 1] = t;
              
              _size--;
            }
          //## end sm_str::vector::pop_back%980824879.body
        }
      
      //## Operation: operator []%980824880
      const T& operator [] (unsigned index  // The index requested
                            ) const
        {
          //## begin sm_str::vector::operator []%980824880.body preserve=yes
          return (const T) _data [index];
          //## end sm_str::vector::operator []%980824880.body
        }
      
      //## Operation: begin%980824887
      vector<T>::iterator begin ()
        {
          //## begin sm_str::vector::begin%980824887.body preserve=yes
          vector<T>::iterator iter (this);
          return iter;
          
          //## end sm_str::vector::begin%980824887.body
        }
      
      //## Operation: end%980824888
      vector<T>::iterator end ()
        {
          //## begin sm_str::vector::end%980824888.body preserve=yes
          vector<T>::iterator iter (this, _size);
          return iter;
          //## end sm_str::vector::end%980824888.body
        }
      
      //## Operation: erase%980824889
      void erase (vector<T>::iterator start,  // An iterator pointing to the element to erase
                  vector<T>::iterator finish  // An iterator pointing to one past the last elemnt to
                  // erase
                  )
        {
          //## begin sm_str::vector::erase%980824889.body preserve=yes
          if (start._vec && start._vec == finish._vec && start._current < finish._current)
            {
              unsigned num_to_move = start._vec->size() - finish._current;
              unsigned i;
              
              for (i = 0; i < num_to_move; i++)
                {
                  start._vec->_data[i + start._current] = finish._vec->_data[i + finish._current];
                }
              
              // now overwrite the ones erased with default value
              for (i = 0; i < finish._current - start._current; i++)
                {
                  pop_back();
                }
              
            }
          //## end sm_str::vector::erase%980824889.body
        }
      
      //## Operation: insert%980824890
      void insert (T* element_address,  // The address of the elment to erase.
                   T new_element)
        {
          //## begin sm_str::vector::insert%980824890.body preserve=yes
          bool found = false;
          unsigned insert_i = 0;
          
          while (!found && insert_i < _size)
            {
              // compare the memory adresses
              if (element_address == _data + insert_i)
                {
                  found = true;
                }
              else
                {
                  insert_i++;
                }
            } // end while
          
          if (found)
            {
              if (_size == _capacity)
                {
                  reserve (_capacity + _growsize);
                }
              
              // lets check that size is now less in case the reserve failed
              if (_size < _capacity)
                {
                  // move the elements up by one
                  // find the appropriate position
                  
                  for (unsigned i = _size; i > insert_i; i--)
                    {
                      _data [i] = _data [i-1];
                    }
                  
                  _data [insert_i] = new_element;
                  _size++;
                }
            } // end if found
          
          //## end sm_str::vector::insert%980824890.body
        }
      
  public:
      // Additional Public Declarations
      //## begin sm_str::vector%3A763E800375.public preserve=yes
      void clear(){_size = 0;}
      
      //## end sm_str::vector%3A763E800375.public
  protected:
      // Additional Protected Declarations
      //## begin sm_str::vector%3A763E800375.protected preserve=yes
      //## end sm_str::vector%3A763E800375.protected
      
  private:
      // Additional Private Declarations
      //## begin sm_str::vector%3A763E800375.private preserve=yes
      //## end sm_str::vector%3A763E800375.private
      
  private: //## implementation
      // Data Members for Class Attributes
      
      //## Attribute: _size%3A763FB20393
      //  this is the current number of elements.
      //## begin sm_str::vector::_size%3A763FB20393.attr preserve=no  private: unsigned {UT} 0
      volatile unsigned  _size;
      //## end sm_str::vector::_size%3A763FB20393.attr
      
      //## Attribute: _data%3A763FB30019
      //  This is the array of pointers
      //## begin sm_str::vector::_data%3A763FB30019.attr preserve=no  private: T* {U} NULL
      T* _data;
      //## end sm_str::vector::_data%3A763FB30019.attr
      
      //## Attribute: _capacity%3A763FB30087
      //  This the the maximum size that _size can become before
      //  memory re-allocation is required.
      //## begin sm_str::vector::_capacity%3A763FB30087.attr preserve=no  private: unsigned {U} 0
      unsigned _capacity;
      //## end sm_str::vector::_capacity%3A763FB30087.attr
      
      //## Attribute: _growsize%3A763FB300FF
      //  This is the size that the vector will grow by
      //## begin sm_str::vector::_growsize%3A763FB300FF.attr preserve=no  private: unsigned {U} 256
      unsigned _growsize;
      //## end sm_str::vector::_growsize%3A763FB300FF.attr
      
      // Data Members for Associations
      
      //## Association: estr_stl::<unnamed>%3A905F3A02A9
      //## Role: vector::<the_iterator>%3A905F3B0282
      //## begin sm_str::vector::<the_iterator>%3A905F3B0282.role preserve=no  public: sm_str::vector< T >::iterator {0..1 -> RFHGN}
      //## end sm_str::vector::<the_iterator>%3A905F3B0282.role
      
      // Additional Implementation Declarations
      //## begin sm_str::vector%3A763E800375.implementation preserve=yes
      //## end sm_str::vector%3A763E800375.implementation
      
  };
  
  //## begin sm_str::vector%3A763E800375.postscript preserve=yes
  //## end sm_str::vector%3A763E800375.postscript
  
  // Class sm_str::vector::iterator 
  
  

  // Additional Declarations
    //## begin sm_str::vector::iterator%3A905648024C.declarations preserve=yes
    //## end sm_str::vector::iterator%3A905648024C.declarations

  // Parameterized Class sm_str::vector 






  // Additional Declarations
    //## begin sm_str::vector%3A763E800375.declarations preserve=yes
#ifndef _NO_NAMESPACES
    //## end sm_str::vector%3A763E800375.declarations
} // namespace sm_str

//## begin module%3A90440C00D7.epilog preserve=yes
#endif // no namespaces

#ifdef HAL_MAC
#pragma supress_warnings off
#endif

#endif //_ESTL_VECTOR_H
//## end module%3A90440C00D7.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin sm_str::vector::iterator::iterator%copy.body preserve=no
    (*this) = right;
//## end sm_str::vector::iterator::iterator%copy.body

#endif
