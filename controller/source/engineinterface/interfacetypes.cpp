
#include "stdafx.h"
#include "interfacetypes.h"
#include "identityanswer.h"
#include "control.h"
#include "patch.h"

class Patch;
class BaseShell;
class Identity;
class Connector;
class EventAnswer;

//## Operation: P_IDENTITY%983922934
P_IDENTITY::P_IDENTITY (Identity* val)
{
  //## begin P_IDENTITY::P_IDENTITY%983922934.body preserve=yes
    key = IdentityAnswer::GetIdentityKey(val);
  //## end P_IDENTITY::P_IDENTITY%983922934.body
}

//## Indirection Operation (generated)
Identity* P_IDENTITY::operator->() const
{
  //## begin P_IDENTITY::operator->.body preserve=yes
  return IdentityAnswer::GetIdentity (*this);
  //## end P_IDENTITY::operator->.body
}

//## Dereference Operation (generated)
Identity* P_IDENTITY::operator*() const
{
  //## begin P_IDENTITY::operator*.body preserve=yes
  return IdentityAnswer::GetIdentity (*this);
  //## end P_IDENTITY::operator*.body
}

      


//## Operation: P_BASESHELL%983397798
P_BASESHELL::P_BASESHELL (BaseShell* val)
  //## begin P_BASESHELL::P_BASESHELL%983397798.hasinit preserve=no
  //## end P_BASESHELL::P_BASESHELL%983397798.hasinit
  //## begin P_BASESHELL::P_BASESHELL%983397798.initialization preserve=yes
                          :P_IDENTITY (val)
  //## end P_BASESHELL::P_BASESHELL%983397798.initialization
{
  //## begin P_BASESHELL::P_BASESHELL%983397798.body preserve=yes
  //## end P_BASESHELL::P_BASESHELL%983397798.body
}

//## Dereference Operation (generated)
BaseShell* P_BASESHELL::operator*() const
{
  //## begin P_BASESHELL::operator*.body preserve=yes
  return (BaseShell*) IdentityAnswer::GetIdentity (*this);
  //## end P_BASESHELL::operator*.body
}


//## Operation: P_PATCH%983397799
P_PATCH::P_PATCH (Patch* val)
  //## begin P_PATCH::P_PATCH%983397799.hasinit preserve=no
  //## end P_PATCH::P_PATCH%983397799.hasinit
  //## begin P_PATCH::P_PATCH%983397799.initialization preserve=yes
                          :P_BASESHELL (val)
  //## end P_PATCH::P_PATCH%983397799.initialization
{
  //## begin P_PATCH::P_PATCH%983397799.body preserve=yes
  //## end P_PATCH::P_PATCH%983397799.body
}


//## Dereference Operation (generated)
Patch* P_PATCH::operator*() const
{
  //## begin P_PATCH::operator*.body preserve=yes
  return (Patch*)IdentityAnswer::GetIdentity (*this);
  //## end P_PATCH::operator*.body
}

//## Operation: P_CONNECTOR%983397800
P_CONNECTOR::P_CONNECTOR (Connector* val)
  //## begin P_CONNECTOR::P_CONNECTOR%983397800.hasinit preserve=no
  //## end P_CONNECTOR::P_CONNECTOR%983397800.hasinit
  //## begin P_CONNECTOR::P_CONNECTOR%983397800.initialization preserve=yes
                          :P_IDENTITY (val)
  //## end P_CONNECTOR::P_CONNECTOR%983397800.initialization
{
  //## begin P_CONNECTOR::P_CONNECTOR%983397800.body preserve=yes
  //## end P_CONNECTOR::P_CONNECTOR%983397800.body
}

//## Dereference Operation (generated)
Connector* P_CONNECTOR::operator*() const
{
  //## begin P_CONNECTOR::operator*.body preserve=yes
                          return (Connector*)IdentityAnswer::GetIdentity (*this);
  //## end P_CONNECTOR::operator*.body
}

 
