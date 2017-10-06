//## begin module%3A9D9F8503C9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A9D9F8503C9.cm

//## begin module%3A9D9F8503C9.cp preserve=no
//	Angelo Fraietta
//## end module%3A9D9F8503C9.cp

//## Module: InterfaceTypes%3A9D9F8503C9; Package specification
//	Contains specifications for the Interface types used
//	betwen the PatchEditor and the Engine.
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\smartcontroller\controller\source\engineinterface\interfacetypes.h

#ifndef interfacetypes_h
#define interfacetypes_h 1

//## begin module%3A9D9F8503C9.additionalIncludes preserve=no
#include <stdio.h>
//## end module%3A9D9F8503C9.additionalIncludes

//## begin module%3A9D9F8503C9.includes preserve=yes
//## end module%3A9D9F8503C9.includes


class Patch;
class BaseShell;
class Identity;
class Connector;
class EventAnswer;

//## begin module%3A9D9F8503C9.declarations preserve=no
//## end module%3A9D9F8503C9.declarations

//## begin module%3A9D9F8503C9.additionalDeclarations preserve=yes
//## end module%3A9D9F8503C9.additionalDeclarations


//## begin KeyBaseType%3A9DABFA005D.preface preserve=yes
//## end KeyBaseType%3A9DABFA005D.preface

//## Class: KeyBaseType%3A9DABFA005D
//	Allows the Key types to inherit from this
//## Category: EngineInterface%3A998EE60122
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class KeyBaseType 
{
  //## begin KeyBaseType%3A9DABFA005D.initialDeclarations preserve=yes
  //## end KeyBaseType%3A9DABFA005D.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: KeyBaseType%983397785
      KeyBaseType (const BYTE** val	// address of four bytes of big endian data
      )
        //## begin KeyBaseType::KeyBaseType%983397785.hasinit preserve=no
        //## end KeyBaseType::KeyBaseType%983397785.hasinit
        //## begin KeyBaseType::KeyBaseType%983397785.initialization preserve=yes
        :key (0)
        //## end KeyBaseType::KeyBaseType%983397785.initialization
      {
        //## begin KeyBaseType::KeyBaseType%983397785.body preserve=yes
        const BYTE* cursor = *val;
        memcpy (&key, cursor, sizeof (key));
        cursor += sizeof (key);
        *val = cursor;
        //## end KeyBaseType::KeyBaseType%983397785.body
      }

      //## Operation: KeyBaseType%983397788
      KeyBaseType (unsigned long val = 0)
        //## begin KeyBaseType::KeyBaseType%983397788.hasinit preserve=no
        //## end KeyBaseType::KeyBaseType%983397788.hasinit
        //## begin KeyBaseType::KeyBaseType%983397788.initialization preserve=yes
        :key(val)
        //## end KeyBaseType::KeyBaseType%983397788.initialization
      {
        //## begin KeyBaseType::KeyBaseType%983397788.body preserve=yes
        //## end KeyBaseType::KeyBaseType%983397788.body
      }

    //## Equality Operations (generated)
      int operator==(const KeyBaseType &right) const
      {
        //## begin KeyBaseType::operator==.body preserve=yes
        return key == right.key;
        //## end KeyBaseType::operator==.body
      }

      int operator!=(const KeyBaseType &right) const
      {
        //## begin KeyBaseType::operator!=.body preserve=yes
        return key != right.key;
        //## end KeyBaseType::operator!=.body
      }


    //## Other Operations (specified)
      //## Operation: operator =%983397786
      KeyBaseType& operator = (unsigned long right)
      {
        key = right;
        return *this;

        //## begin KeyBaseType::operator =%983397786.body preserve=yes
        //## end KeyBaseType::operator =%983397786.body
      }

      //## Operation: toString%983397787
      void toString (char* ret_buf	// return buffer where the string will be written
      ) const
      {
        sprintf (ret_buf, "%lu", key);

        //## begin KeyBaseType::toString%983397787.body preserve=yes
        //## end KeyBaseType::toString%983397787.body
      }

      //## Operation: operator!%983397797
      bool operator ! () const
      {
        return !key;

        //## begin KeyBaseType::operator!%983397797.body preserve=yes
        //## end KeyBaseType::operator!%983397797.body
      }

      //## Operation: toBuf%985819684
      BYTE* toBuf (BYTE* buf	// the target buffer
      ) const
      {
        //## begin KeyBaseType::toBuf%985819684.body preserve=yes
				memcpy (buf, &key, sizeof (key));
				return buf + sizeof (key);
        //## end KeyBaseType::toBuf%985819684.body
      }

      //## Operation: operator =%985819703
      KeyBaseType& operator = (const BYTE** in_val	// address of four bytes of big endian data
      )
      {
        //## begin KeyBaseType::operator =%985819703.body preserve=yes
				key = 0;
				
				const BYTE* cursor = *in_val;
				for (unsigned i = 0; i < sizeof(DWORD); i++)
					{
						DWORD byte_val = *cursor;
						for (unsigned weight = 0; weight < i; weight ++)
							{
								byte_val =  (byte_val * 0x100);
							}
						
						key += byte_val;
						cursor++;
					}
				*in_val = cursor;
				return *this;
        //## end KeyBaseType::operator =%985819703.body
      }

      //## Operation: Key%986437489
      DWORD Key () const
      {
        return key;

        //## begin KeyBaseType::Key%986437489.body preserve=yes
        //## end KeyBaseType::Key%986437489.body
      }

      //## Operation: operator ()%986437490
      bool operator () () const
      {
        return (key);

        //## begin KeyBaseType::operator ()%986437490.body preserve=yes
        //## end KeyBaseType::operator ()%986437490.body
      }

      //## Operation: operator <%986437491
      bool operator < (const KeyBaseType& right) const
      {
        return key < right.key;

        //## begin KeyBaseType::operator <%986437491.body preserve=yes
        //## end KeyBaseType::operator <%986437491.body
      }

    // Additional Public Declarations
      //## begin KeyBaseType%3A9DABFA005D.public preserve=yes
    inline bool operator() () {return (key);}
      //## end KeyBaseType%3A9DABFA005D.public
  protected:
    // Data Members for Class Attributes

      //## Attribute: key%3A9DAF04003E
      //## begin KeyBaseType::key%3A9DAF04003E.attr preserve=no  protected: unsigned long {U} 
      unsigned long key;
      //## end KeyBaseType::key%3A9DAF04003E.attr

    // Additional Protected Declarations
      //## begin KeyBaseType%3A9DABFA005D.protected preserve=yes
      //## end KeyBaseType%3A9DABFA005D.protected

  private:
    // Additional Private Declarations
      //## begin KeyBaseType%3A9DABFA005D.private preserve=yes
      //## end KeyBaseType%3A9DABFA005D.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin KeyBaseType%3A9DABFA005D.implementation preserve=yes
      //## end KeyBaseType%3A9DABFA005D.implementation

};

//## begin KeyBaseType%3A9DABFA005D.postscript preserve=yes
//## end KeyBaseType%3A9DABFA005D.postscript

//## begin P_IDENTITY%3A99CCB200C7.preface preserve=yes
//## end P_IDENTITY%3A99CCB200C7.preface

//## Class: P_IDENTITY%3A99CCB200C7
//	This is a Key that is used between the PatchEditor and
//	the Engine. It is used to associate an Identity with a
//	DWORD key.  The DWORD is used by the Patch Editor and is
//	converted to an Identity* in the engineinterface.
//## Category: EngineInterface%3A998EE60122
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AC9121D02AA;Identity { -> F}

class P_IDENTITY : public KeyBaseType  //## Inherits: <unnamed>%3A9DACB70240
{
  //## begin P_IDENTITY%3A99CCB200C7.initialDeclarations preserve=yes
  //## end P_IDENTITY%3A99CCB200C7.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: P_IDENTITY%983397789
      P_IDENTITY (const BYTE** val	// address of four bytes of big endian data
      )
        //## begin P_IDENTITY::P_IDENTITY%983397789.hasinit preserve=no
        //## end P_IDENTITY::P_IDENTITY%983397789.hasinit
        //## begin P_IDENTITY::P_IDENTITY%983397789.initialization preserve=yes
        :KeyBaseType (val)
        //## end P_IDENTITY::P_IDENTITY%983397789.initialization
      {
        //## begin P_IDENTITY::P_IDENTITY%983397789.body preserve=yes
        //## end P_IDENTITY::P_IDENTITY%983397789.body
      }

      //## Operation: P_IDENTITY%983397790
      P_IDENTITY (unsigned long val = 0)
        //## begin P_IDENTITY::P_IDENTITY%983397790.hasinit preserve=no
        //## end P_IDENTITY::P_IDENTITY%983397790.hasinit
        //## begin P_IDENTITY::P_IDENTITY%983397790.initialization preserve=yes
        :KeyBaseType (val)
        //## end P_IDENTITY::P_IDENTITY%983397790.initialization
      {
        //## begin P_IDENTITY::P_IDENTITY%983397790.body preserve=yes
        //## end P_IDENTITY::P_IDENTITY%983397790.body
      }

      //## Operation: P_IDENTITY%983922934
      P_IDENTITY (Identity* val)
        //## begin P_IDENTITY::P_IDENTITY%983922934.hasinit preserve=no
        //## end P_IDENTITY::P_IDENTITY%983922934.hasinit
        //## begin P_IDENTITY::P_IDENTITY%983922934.initialization preserve=yes
				:KeyBaseType ((unsigned long) val)
        //## end P_IDENTITY::P_IDENTITY%983922934.initialization
      {
        //## begin P_IDENTITY::P_IDENTITY%983922934.body preserve=yes
        //## end P_IDENTITY::P_IDENTITY%983922934.body
      }

    //## Indirection Operation (generated)
      Identity* operator->() const
      {
        //## begin P_IDENTITY::operator->.body preserve=yes
				return (Identity*)key;
        //## end P_IDENTITY::operator->.body
      }

    //## Dereference Operation (generated)
      Identity* operator*() const
      {
        //## begin P_IDENTITY::operator*.body preserve=yes
				return (Identity*)key;
        //## end P_IDENTITY::operator*.body
      }

    // Additional Public Declarations
      //## begin P_IDENTITY%3A99CCB200C7.public preserve=yes
      //## end P_IDENTITY%3A99CCB200C7.public

  protected:
    // Additional Protected Declarations
      //## begin P_IDENTITY%3A99CCB200C7.protected preserve=yes
      //## end P_IDENTITY%3A99CCB200C7.protected

  private:
    // Additional Private Declarations
      //## begin P_IDENTITY%3A99CCB200C7.private preserve=yes
      //## end P_IDENTITY%3A99CCB200C7.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin P_IDENTITY%3A99CCB200C7.implementation preserve=yes
      //## end P_IDENTITY%3A99CCB200C7.implementation

};

//## begin P_IDENTITY%3A99CCB200C7.postscript preserve=yes
//## end P_IDENTITY%3A99CCB200C7.postscript

//## begin P_BASESHELL%3A99CCB201A3.preface preserve=yes
//## end P_BASESHELL%3A99CCB201A3.preface

//## Class: P_BASESHELL%3A99CCB201A3
//## Category: EngineInterface%3A998EE60122
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AC9124401B6;BaseShell { -> F}

class P_BASESHELL : public P_IDENTITY  //## Inherits: <unnamed>%3AA6C34103DA
{
  //## begin P_BASESHELL%3A99CCB201A3.initialDeclarations preserve=yes
  //## end P_BASESHELL%3A99CCB201A3.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: P_BASESHELL%983397791
      P_BASESHELL (const BYTE** val	// address of four bytes of big endian data
      )
        //## begin P_BASESHELL::P_BASESHELL%983397791.hasinit preserve=no
        //## end P_BASESHELL::P_BASESHELL%983397791.hasinit
        //## begin P_BASESHELL::P_BASESHELL%983397791.initialization preserve=yes
        :P_IDENTITY (val)        
        //## end P_BASESHELL::P_BASESHELL%983397791.initialization
      {
        //## begin P_BASESHELL::P_BASESHELL%983397791.body preserve=yes
        //## end P_BASESHELL::P_BASESHELL%983397791.body
      }

      //## Operation: P_BASESHELL%983397792
      P_BASESHELL (unsigned long val = 0)
        //## begin P_BASESHELL::P_BASESHELL%983397792.hasinit preserve=no
        //## end P_BASESHELL::P_BASESHELL%983397792.hasinit
        //## begin P_BASESHELL::P_BASESHELL%983397792.initialization preserve=yes
        :P_IDENTITY (val)
        //## end P_BASESHELL::P_BASESHELL%983397792.initialization
      {
        //## begin P_BASESHELL::P_BASESHELL%983397792.body preserve=yes
        //## end P_BASESHELL::P_BASESHELL%983397792.body
      }

      //## Operation: P_BASESHELL%983397798
      P_BASESHELL (BaseShell* val)
        //## begin P_BASESHELL::P_BASESHELL%983397798.hasinit preserve=no
        //## end P_BASESHELL::P_BASESHELL%983397798.hasinit
        //## begin P_BASESHELL::P_BASESHELL%983397798.initialization preserve=yes
				:P_IDENTITY ((unsigned long) val)
        //## end P_BASESHELL::P_BASESHELL%983397798.initialization
      {
        //## begin P_BASESHELL::P_BASESHELL%983397798.body preserve=yes
        //## end P_BASESHELL::P_BASESHELL%983397798.body
      }

    //## Dereference Operation (generated)
      BaseShell* operator*() const
      {
        //## begin P_BASESHELL::operator*.body preserve=yes
	return (BaseShell*)key;
        //## end P_BASESHELL::operator*.body
      }

    // Additional Public Declarations
      //## begin P_BASESHELL%3A99CCB201A3.public preserve=yes
      //## end P_BASESHELL%3A99CCB201A3.public

  protected:
    // Additional Protected Declarations
      //## begin P_BASESHELL%3A99CCB201A3.protected preserve=yes
      //## end P_BASESHELL%3A99CCB201A3.protected

  private:
    // Additional Private Declarations
      //## begin P_BASESHELL%3A99CCB201A3.private preserve=yes
      //## end P_BASESHELL%3A99CCB201A3.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin P_BASESHELL%3A99CCB201A3.implementation preserve=yes
      //## end P_BASESHELL%3A99CCB201A3.implementation

};

//## begin P_BASESHELL%3A99CCB201A3.postscript preserve=yes
//## end P_BASESHELL%3A99CCB201A3.postscript

//## begin P_PATCH%3A99CCB201C1.preface preserve=yes
//## end P_PATCH%3A99CCB201C1.preface

//## Class: P_PATCH%3A99CCB201C1
//## Category: EngineInterface%3A998EE60122
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AC912530207;Patch { -> F}

class P_PATCH : public P_BASESHELL  //## Inherits: <unnamed>%3AA6C34E00FE
{
  //## begin P_PATCH%3A99CCB201C1.initialDeclarations preserve=yes
  //## end P_PATCH%3A99CCB201C1.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: P_PATCH%983397793
      P_PATCH (const BYTE** val	// address of four bytes of big endian data
      )
        //## begin P_PATCH::P_PATCH%983397793.hasinit preserve=no
        //## end P_PATCH::P_PATCH%983397793.hasinit
        //## begin P_PATCH::P_PATCH%983397793.initialization preserve=yes
        :P_BASESHELL (val)
        //## end P_PATCH::P_PATCH%983397793.initialization
      {
        //## begin P_PATCH::P_PATCH%983397793.body preserve=yes
        //## end P_PATCH::P_PATCH%983397793.body
      }

      //## Operation: P_PATCH%983397794
      P_PATCH (unsigned long val = 0)
        //## begin P_PATCH::P_PATCH%983397794.hasinit preserve=no
        //## end P_PATCH::P_PATCH%983397794.hasinit
        //## begin P_PATCH::P_PATCH%983397794.initialization preserve=yes
        :P_BASESHELL (val)
        //## end P_PATCH::P_PATCH%983397794.initialization
      {
        //## begin P_PATCH::P_PATCH%983397794.body preserve=yes
        //## end P_PATCH::P_PATCH%983397794.body
      }

      //## Operation: P_PATCH%983397799
      P_PATCH (Patch* val)
        //## begin P_PATCH::P_PATCH%983397799.hasinit preserve=no
        //## end P_PATCH::P_PATCH%983397799.hasinit
        //## begin P_PATCH::P_PATCH%983397799.initialization preserve=yes
				:P_BASESHELL ((unsigned long) val)
        //## end P_PATCH::P_PATCH%983397799.initialization
      {
        //## begin P_PATCH::P_PATCH%983397799.body preserve=yes
        //## end P_PATCH::P_PATCH%983397799.body
      }

      //## Operation: P_PATCH%986437488
      P_PATCH (P_BASESHELL val)
        //## begin P_PATCH::P_PATCH%986437488.hasinit preserve=no
        //## end P_PATCH::P_PATCH%986437488.hasinit
        //## begin P_PATCH::P_PATCH%986437488.initialization preserve=yes
        :P_BASESHELL (val.Key())
        //## end P_PATCH::P_PATCH%986437488.initialization
      {
        //## begin P_PATCH::P_PATCH%986437488.body preserve=yes
        //## end P_PATCH::P_PATCH%986437488.body
      }

    //## Dereference Operation (generated)
      Patch* operator*() const
      {
        //## begin P_PATCH::operator*.body preserve=yes
	return (Patch*)key;
        //## end P_PATCH::operator*.body
      }

    // Additional Public Declarations
      //## begin P_PATCH%3A99CCB201C1.public preserve=yes
      //## end P_PATCH%3A99CCB201C1.public

  protected:
    // Additional Protected Declarations
      //## begin P_PATCH%3A99CCB201C1.protected preserve=yes
      //## end P_PATCH%3A99CCB201C1.protected

  private:
    // Additional Private Declarations
      //## begin P_PATCH%3A99CCB201C1.private preserve=yes
      //## end P_PATCH%3A99CCB201C1.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin P_PATCH%3A99CCB201C1.implementation preserve=yes
      //## end P_PATCH%3A99CCB201C1.implementation

};

//## begin P_PATCH%3A99CCB201C1.postscript preserve=yes
//## end P_PATCH%3A99CCB201C1.postscript

//## begin P_CONNECTOR%3A99CCB201FD.preface preserve=yes
//## end P_CONNECTOR%3A99CCB201FD.preface

//## Class: P_CONNECTOR%3A99CCB201FD
//## Category: EngineInterface%3A998EE60122
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AC912670198;Connector { -> F}

class P_CONNECTOR : public P_IDENTITY  //## Inherits: <unnamed>%3AA6C3600230
{
  //## begin P_CONNECTOR%3A99CCB201FD.initialDeclarations preserve=yes
  //## end P_CONNECTOR%3A99CCB201FD.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: P_CONNECTOR%983397795
      P_CONNECTOR (const BYTE** val	// address of four bytes of big endian data
      )
        //## begin P_CONNECTOR::P_CONNECTOR%983397795.hasinit preserve=no
        //## end P_CONNECTOR::P_CONNECTOR%983397795.hasinit
        //## begin P_CONNECTOR::P_CONNECTOR%983397795.initialization preserve=yes
        :P_IDENTITY (val)
        //## end P_CONNECTOR::P_CONNECTOR%983397795.initialization
      {
        //## begin P_CONNECTOR::P_CONNECTOR%983397795.body preserve=yes
        //## end P_CONNECTOR::P_CONNECTOR%983397795.body
      }

      //## Operation: P_CONNECTOR%983397796
      P_CONNECTOR (unsigned long val = 0)
        //## begin P_CONNECTOR::P_CONNECTOR%983397796.hasinit preserve=no
        //## end P_CONNECTOR::P_CONNECTOR%983397796.hasinit
        //## begin P_CONNECTOR::P_CONNECTOR%983397796.initialization preserve=yes
        :P_IDENTITY (val)
        //## end P_CONNECTOR::P_CONNECTOR%983397796.initialization
      {
        //## begin P_CONNECTOR::P_CONNECTOR%983397796.body preserve=yes
        //## end P_CONNECTOR::P_CONNECTOR%983397796.body
      }

      //## Operation: P_CONNECTOR%983397800
      P_CONNECTOR (Connector* val)
        //## begin P_CONNECTOR::P_CONNECTOR%983397800.hasinit preserve=no
        //## end P_CONNECTOR::P_CONNECTOR%983397800.hasinit
        //## begin P_CONNECTOR::P_CONNECTOR%983397800.initialization preserve=yes
				:P_IDENTITY ((unsigned long) val)
        //## end P_CONNECTOR::P_CONNECTOR%983397800.initialization
      {
        //## begin P_CONNECTOR::P_CONNECTOR%983397800.body preserve=yes
        //## end P_CONNECTOR::P_CONNECTOR%983397800.body
      }

    //## Dereference Operation (generated)
      Connector* operator*() const
      {
        //## begin P_CONNECTOR::operator*.body preserve=yes
				return (Connector*)key;
        //## end P_CONNECTOR::operator*.body
      }

    // Additional Public Declarations
      //## begin P_CONNECTOR%3A99CCB201FD.public preserve=yes
      //## end P_CONNECTOR%3A99CCB201FD.public

  protected:
    // Additional Protected Declarations
      //## begin P_CONNECTOR%3A99CCB201FD.protected preserve=yes
      //## end P_CONNECTOR%3A99CCB201FD.protected

  private:
    // Additional Private Declarations
      //## begin P_CONNECTOR%3A99CCB201FD.private preserve=yes
      //## end P_CONNECTOR%3A99CCB201FD.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin P_CONNECTOR%3A99CCB201FD.implementation preserve=yes
      //## end P_CONNECTOR%3A99CCB201FD.implementation

};

//## begin P_CONNECTOR%3A99CCB201FD.postscript preserve=yes
//## end P_CONNECTOR%3A99CCB201FD.postscript

//## begin P_EVENTQ%3AC90FA503A6.preface preserve=yes
//## end P_EVENTQ%3AC90FA503A6.preface

//## Class: P_EVENTQ%3AC90FA503A6
//	This holds the pointer to the Event message queue in the
//	engine.  This is held by the PresentationQuestion in
//	irder for it to probe its instance of the EventMessage
//## Category: EngineInterface%3A998EE60122
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AC911BC026F;EventAnswer { -> F}

class P_EVENTQ : public KeyBaseType  //## Inherits: <unnamed>%3AC90FB90318
{
  //## begin P_EVENTQ%3AC90FA503A6.initialDeclarations preserve=yes
  //## end P_EVENTQ%3AC90FA503A6.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: P_EVENTQ%986253844
      P_EVENTQ (const BYTE** val	// address of four bytes of big endian data
      )
        //## begin P_EVENTQ::P_EVENTQ%986253844.hasinit preserve=no
        //## end P_EVENTQ::P_EVENTQ%986253844.hasinit
        //## begin P_EVENTQ::P_EVENTQ%986253844.initialization preserve=yes
				:KeyBaseType (val)
        //## end P_EVENTQ::P_EVENTQ%986253844.initialization
      {
        //## begin P_EVENTQ::P_EVENTQ%986253844.body preserve=yes
        //## end P_EVENTQ::P_EVENTQ%986253844.body
      }

      //## Operation: P_EVENTQ%986253845
      P_EVENTQ (unsigned long val = 0)
        //## begin P_EVENTQ::P_EVENTQ%986253845.hasinit preserve=no
        //## end P_EVENTQ::P_EVENTQ%986253845.hasinit
        //## begin P_EVENTQ::P_EVENTQ%986253845.initialization preserve=yes
				:KeyBaseType (val)
        //## end P_EVENTQ::P_EVENTQ%986253845.initialization
      {
        //## begin P_EVENTQ::P_EVENTQ%986253845.body preserve=yes
        //## end P_EVENTQ::P_EVENTQ%986253845.body
      }

      //## Operation: P_EVENTQ%986253846
      P_EVENTQ (EventAnswer* val)
        //## begin P_EVENTQ::P_EVENTQ%986253846.hasinit preserve=no
        //## end P_EVENTQ::P_EVENTQ%986253846.hasinit
        //## begin P_EVENTQ::P_EVENTQ%986253846.initialization preserve=yes
				:KeyBaseType ((DWORD)val)
        //## end P_EVENTQ::P_EVENTQ%986253846.initialization
      {
        //## begin P_EVENTQ::P_EVENTQ%986253846.body preserve=yes
        //## end P_EVENTQ::P_EVENTQ%986253846.body
      }

    //## Dereference Operation (generated)
      EventAnswer* operator*() const
      {
        //## begin P_EVENTQ::operator*.body preserve=yes
				return (EventAnswer*)key;
        //## end P_EVENTQ::operator*.body
      }

    // Additional Public Declarations
      //## begin P_EVENTQ%3AC90FA503A6.public preserve=yes
      //## end P_EVENTQ%3AC90FA503A6.public

  protected:
    // Additional Protected Declarations
      //## begin P_EVENTQ%3AC90FA503A6.protected preserve=yes
      //## end P_EVENTQ%3AC90FA503A6.protected

  private:
    // Additional Private Declarations
      //## begin P_EVENTQ%3AC90FA503A6.private preserve=yes
      //## end P_EVENTQ%3AC90FA503A6.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin P_EVENTQ%3AC90FA503A6.implementation preserve=yes
      //## end P_EVENTQ%3AC90FA503A6.implementation

};

//## begin P_EVENTQ%3AC90FA503A6.postscript preserve=yes
//## end P_EVENTQ%3AC90FA503A6.postscript

//## begin module%3A9D9F8503C9.epilog preserve=yes
//## end module%3A9D9F8503C9.epilog


#endif
