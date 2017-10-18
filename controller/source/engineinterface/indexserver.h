/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   indexserver.h
 * Author: angelo
 *
 * Created on 19 October 2017, 6:19 AM
 */

#ifndef INDEXSERVER_H
#define INDEXSERVER_H

#include "evector.h"
#include "emap.h"
#include "mutex.h"

using sm_str::map;
using sm_str::vector;

template <class T>
class IndexServer {
public:
    IndexServer(unsigned array_size = 1024) :
    _array_size(array_size), _next_index (0)
    {
        //_mutex = Mutex::create();
    }
    
    unsigned addIndex(T* identity);
    T* getIdentityFromIndex(unsigned key);
    void eraseIndex (unsigned key);

    virtual ~IndexServer();
private:
    const unsigned _array_size;
    vector <T**> _key_indexes;
    volatile unsigned _next_index;
    //Mutex* _mutex;
};


template <class T>
    IndexServer<T>::~IndexServer()
    {
        for(unsigned i = 0; i < _key_indexes.size(); i++)
        {
            T ** next_buffer = _key_indexes[i];
            delete [] next_buffer;
        }
        
        _key_indexes.clear();
    }

    // Return a number that we will use as a key
    // we should put this in some sort of critical section
template <class T>
    unsigned IndexServer<T>::addIndex(T* identity)
    {
        unsigned buffer_num = _next_index / _array_size;
        
        T** next_buffer;

        if (_key_indexes.size() <= buffer_num)
        {
            // we need to add a buffer to fill arrays
            next_buffer = new T*[_array_size];
            _key_indexes.push_back(next_buffer);
        }
        else
        {        
            next_buffer = _key_indexes[buffer_num];
        }

        unsigned buf_index = _next_index % _array_size;
        next_buffer[buf_index] = identity;
        unsigned ret = _next_index;
        _next_index++;

        return ret;
    }
    
template <class T>
T* IndexServer<T>::getIdentityFromIndex(unsigned key)
{
    T* ret = NULL;
    
    unsigned buffer_num = key / _array_size;
    unsigned buf_index = key % _array_size;
    
    if (_key_indexes.size() > buffer_num)
    {
       T ** next_buffer = _key_indexes[buffer_num];
       ret = next_buffer [buf_index];
 
    }
    
    return ret;
    
}

template <class T>
void IndexServer<T>::eraseIndex (unsigned key)
{
    
    unsigned buffer_num = key / _array_size;
    unsigned buf_index = key % _array_size;
    
    if (_key_indexes.size() > buffer_num)
    {
       T ** next_buffer = _key_indexes[buffer_num];
       next_buffer [buf_index] = NULL;
 
    }   
}
#endif /* INDEXSERVER_H */

