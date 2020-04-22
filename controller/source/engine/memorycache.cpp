//## begin module%3CCE1352007F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CCE1352007F.cm

//## begin module%3CCE1352007F.cp preserve=no
//	Angelo Fraietta
//## end module%3CCE1352007F.cp

//## Module: memorycache%3CCE1352007F; Package body
//## Subsystem: engine%39F51CB901B8
//	c:\develop\smartcontroller\controller\source\engine
//## Source file: c:\develop\smartcontroller\controller\source\engine\memorycache.cpp

//## begin module%3CCE1352007F.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3CCE1352007F.additionalIncludes

//## begin module%3CCE1352007F.includes preserve=yes
#include <stddef.h>
#include <stdlib.h>
//## end module%3CCE1352007F.includes

// memorycache
#include "memorycache.h"


//## begin module%3CCE1352007F.declarations preserve=no
//## end module%3CCE1352007F.declarations

//## begin module%3CCE1352007F.additionalDeclarations preserve=yes
//## end module%3CCE1352007F.additionalDeclarations


// Class MemoryCache 




MemoryCache::MemoryCache()
  //## begin MemoryCache::MemoryCache%.hasinit preserve=no
      : _empty(NULL), _full(NULL)
  //## end MemoryCache::MemoryCache%.hasinit
  //## begin MemoryCache::MemoryCache%.initialization preserve=yes
  //## end MemoryCache::MemoryCache%.initialization
{
  //## begin MemoryCache::MemoryCache%.body preserve=yes
  //## end MemoryCache::MemoryCache%.body
}


MemoryCache::~MemoryCache()
{
  //## begin MemoryCache::~MemoryCache%.body preserve=yes
  while (_empty)
  {
  	MemorySegment* _next = _empty->_next;
    delete _empty;
    _empty = _next;
  }

  while (_full)
  {
  	MemorySegment* _next = _full->_next;
    //delete [] (_full->_mem);
    free (_full->_mem);
    delete _full;
    _full = _next;
  }


  //## end MemoryCache::~MemoryCache%.body
}



//## Other Operations (implementation)
//## Operation: allocate%1020137286
//	Returns block of memory.
//## Postconditions:
//	If the block is available from the full list, it returns
//	the _mem from that memorysegment and places the
//	memorysegment in the empty list, otherwise it allocates
//	that memory from the heap.
void* MemoryCache::allocate (size_t size)
{
  //## begin MemoryCache::allocate%1020137286.body preserve=yes
  void* ret;

  if (_full)
  {
  	// get mem segment from full cache and remove segment from full list
  	MemorySegment* mem_store = _full;
    _full = mem_store->_next;
    ret = mem_store->_mem;

    mem_store->_mem = NULL;

    // now move segment to empty list
    mem_store->_next = _empty;
    _empty = mem_store;

  }
  else
  {
  	ret = malloc(size); // new char [size];
  }

  return ret;
  //## end MemoryCache::allocate%1020137286.body
}

//## Operation: free%1020137287
//	Returns the memory back to the store
//## Postconditions:
//	If a MemorySegment is available on the empty list
//	(otherwise it creates a new one),  stores the memory to
//	it and places the segment on the full list.
void MemoryCache::free (void* mem)
{
  //## begin MemoryCache::free%1020137287.body preserve=yes
  MemorySegment* mem_store;

  if (_empty)
  {
  	// get mem segment from empty list and remove from empty list
  	mem_store = _empty;
    _empty = mem_store->_next;
  }
  else
  {
  	mem_store = new MemorySegment;
  }

  if (mem_store)
  {
  	// stored memory into segment and place on full list
	  mem_store->_mem = mem;
    mem_store->_next = _full;
    _full = mem_store;
  }
  else
  {
    free (mem);
  	//delete [] mem;
  }

  //## end MemoryCache::free%1020137287.body
}

// Additional Declarations
  //## begin MemoryCache%3CCE10F900D5.declarations preserve=yes
  //## end MemoryCache%3CCE10F900D5.declarations

// Class MemorySegment 






MemorySegment::MemorySegment()
  //## begin MemorySegment::MemorySegment%.hasinit preserve=no
      : _next(NULL)
  //## end MemorySegment::MemorySegment%.hasinit
  //## begin MemorySegment::MemorySegment%.initialization preserve=yes
  //## end MemorySegment::MemorySegment%.initialization
{
  //## begin MemorySegment::MemorySegment%.body preserve=yes
  //## end MemorySegment::MemorySegment%.body
}


MemorySegment::~MemorySegment()
{
  //## begin MemorySegment::~MemorySegment%.body preserve=yes
  //## end MemorySegment::~MemorySegment%.body
}


// Additional Declarations
  //## begin MemorySegment%3CCE11860240.declarations preserve=yes
  //## end MemorySegment%3CCE11860240.declarations

//## begin module%3CCE1352007F.epilog preserve=yes
//## end module%3CCE1352007F.epilog
