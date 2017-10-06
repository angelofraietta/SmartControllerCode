//## begin module%3CCE134402B9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CCE134402B9.cm

//## begin module%3CCE134402B9.cp preserve=no
//	Angelo Fraietta
//## end module%3CCE134402B9.cp

//## Module: memorycache%3CCE134402B9; Package specification
//## Subsystem: engine%39F51CB901B8
//	c:\develop\smartcontroller\controller\source\engine
//## Source file: c:\develop\smartcontroller\controller\source\engine\memorycache.h

#ifndef memorycache_h
#define memorycache_h 1

//## begin module%3CCE134402B9.additionalIncludes preserve=no
//## end module%3CCE134402B9.additionalIncludes

//## begin module%3CCE134402B9.includes preserve=yes
//## end module%3CCE134402B9.includes


class MemorySegment;

//## begin module%3CCE134402B9.declarations preserve=no
//## end module%3CCE134402B9.declarations

//## begin module%3CCE134402B9.additionalDeclarations preserve=yes
//## end module%3CCE134402B9.additionalDeclarations


//## begin MemoryCache%3CCE10F900D5.preface preserve=yes
//## end MemoryCache%3CCE10F900D5.preface

//## Class: MemoryCache%3CCE10F900D5
//	Class used for allocating and deallocating memory. Used
//	instead of freeing dynmaic memory back to heap
//## Category: engine%39F4C4E2005F
//## Subsystem: engine%39F51CB901B8
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class MemoryCache 
{
  //## begin MemoryCache%3CCE10F900D5.initialDeclarations preserve=yes
  //## end MemoryCache%3CCE10F900D5.initialDeclarations

  public:
    //## Constructors (generated)
      MemoryCache();

    //## Destructor (generated)
      ~MemoryCache();


    //## Other Operations (specified)
      //## Operation: allocate%1020137286
      void* allocate (size_t size);

      //## Operation: free%1020137287
      void free (void* mem	// The memort to return
      );

    // Additional Public Declarations
      //## begin MemoryCache%3CCE10F900D5.public preserve=yes
      //## end MemoryCache%3CCE10F900D5.public

  protected:
    // Additional Protected Declarations
      //## begin MemoryCache%3CCE10F900D5.protected preserve=yes
      //## end MemoryCache%3CCE10F900D5.protected

  private:
    // Additional Private Declarations
      //## begin MemoryCache%3CCE10F900D5.private preserve=yes
      //## end MemoryCache%3CCE10F900D5.private

  private: //## implementation
    // Data Members for Associations

      //## Association: engine::<unnamed>%3CCE13DB00FE
      //## Role: MemoryCache::_empty%3CCE13DB036B
      //## begin MemoryCache::_empty%3CCE13DB036B.role preserve=no  public: MemorySegment { -> 0..nRFHN}
      MemorySegment* _empty;
      //## end MemoryCache::_empty%3CCE13DB036B.role

      //## Association: hal_include::<unnamed>%3CCE11D30060
      //## Role: MemoryCache::_full%3CCE11D50244
      //## begin MemoryCache::_full%3CCE11D50244.role preserve=no  public: MemorySegment { -> 0..nRFHN}
      MemorySegment* _full;
      //## end MemoryCache::_full%3CCE11D50244.role

    // Additional Implementation Declarations
      //## begin MemoryCache%3CCE10F900D5.implementation preserve=yes
      //## end MemoryCache%3CCE10F900D5.implementation

};

//## begin MemoryCache%3CCE10F900D5.postscript preserve=yes
//## end MemoryCache%3CCE10F900D5.postscript

//## begin MemorySegment%3CCE11860240.preface preserve=yes
//## end MemorySegment%3CCE11860240.preface

//## Class: MemorySegment%3CCE11860240
//## Category: engine%39F4C4E2005F
//## Subsystem: engine%39F51CB901B8
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class MemorySegment 
{
  //## begin MemorySegment%3CCE11860240.initialDeclarations preserve=yes
  //## end MemorySegment%3CCE11860240.initialDeclarations

  public:
    //## Constructors (generated)
      MemorySegment();

    //## Destructor (generated)
      ~MemorySegment();

    // Additional Public Declarations
      //## begin MemorySegment%3CCE11860240.public preserve=yes
      //## end MemorySegment%3CCE11860240.public

  protected:
    // Additional Protected Declarations
      //## begin MemorySegment%3CCE11860240.protected preserve=yes
      //## end MemorySegment%3CCE11860240.protected

  private:
    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: _mem%3CCE12A100B6
      //	The memory contained by this object
      const void* get__mem () const;
      void set__mem (void* value);

    // Additional Private Declarations
      //## begin MemorySegment%3CCE11860240.private preserve=yes
      //## end MemorySegment%3CCE11860240.private

  private: //## implementation
    // Data Members for Class Attributes

      //## begin MemorySegment::_mem%3CCE12A100B6.attr preserve=no  private: void* {U} 
      void* _mem;
      //## end MemorySegment::_mem%3CCE12A100B6.attr

    // Data Members for Associations

      //## Association: hal_include::<unnamed>%3CCE12130026
      //## Role: MemorySegment::_next%3CCE121503B8
      //## begin MemorySegment::_next%3CCE121503B8.role preserve=no  public: MemorySegment { -> 0..1RFHN}
      MemorySegment *_next;
      //## end MemorySegment::_next%3CCE121503B8.role

    // Additional Implementation Declarations
      //## begin MemorySegment%3CCE11860240.implementation preserve=yes
      //## end MemorySegment%3CCE11860240.implementation

    friend class MemoryCache;
};

//## begin MemorySegment%3CCE11860240.postscript preserve=yes
//## end MemorySegment%3CCE11860240.postscript

// Class MemoryCache 

// Class MemorySegment 

//## Get and Set Operations for Class Attributes (inline)

inline const void* MemorySegment::get__mem () const
{
  //## begin MemorySegment::get__mem%3CCE12A100B6.get preserve=no
  return _mem;
  //## end MemorySegment::get__mem%3CCE12A100B6.get
}

inline void MemorySegment::set__mem (void* value)
{
  //## begin MemorySegment::set__mem%3CCE12A100B6.set preserve=no
  _mem = value;
  //## end MemorySegment::set__mem%3CCE12A100B6.set
}

//## begin module%3CCE134402B9.epilog preserve=yes
//## end module%3CCE134402B9.epilog


#endif
