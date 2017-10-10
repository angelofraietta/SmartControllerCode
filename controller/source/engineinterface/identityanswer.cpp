//## begin module%3ACAAFDE026B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ACAAFDE026B.cm

//## begin module%3ACAAFDE026B.cp preserve=no
//	Angelo Fraietta
//## end module%3ACAAFDE026B.cp

//## Module: IdentityAnswer%3ACAAFDE026B; Package body
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\identityanswer.cpp

//## begin module%3ACAAFDE026B.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3ACAAFDE026B.additionalIncludes

//## begin module%3ACAAFDE026B.includes preserve=yes
#include "smutility.h"
#include "control.h"
#include <string.h>
#include "typedefs.h"
#include "interfacetypes.h"

//## end module%3ACAAFDE026B.includes

// identity
#include "identity.h"
// IdentityAnswer
#include "identityanswer.h"
// PatchAnswer
#include "patchanswer.h"

#include "emap.h"
//## begin module%3ACAAFDE026B.declarations preserve=no
using sm_str::map;

map <DWORD, DWORD> valid_identities;
typedef map<DWORD, DWORD>::value_type map_value_type;
//## end module%3ACAAFDE026B.declarations

//## begin module%3ACAAFDE026B.additionalDeclarations preserve=yes
//## end module%3ACAAFDE026B.additionalDeclarations


// Class Utility IdentityAnswer 

//## begin IdentityAnswer::pFunc%3AC15EF100E6.attr preserve=no  private: static IdentityAnswer::pfunctype [eMaxFuncIndex] {V} {GetName, GetComment, GetType, GetModified, SetName, SetComment, GetDefaultAttribute, SetDefaultAttribute, CanSave, GetParent, SetParent}
IdentityAnswer::pfunctype  IdentityAnswer::pFunc[eMaxFuncIndex] = {GetName, GetComment, GetType, GetModified, SetName, SetComment, GetDefaultAttribute, SetDefaultAttribute, CanSave, GetParent, SetParent};
//## end IdentityAnswer::pFunc%3AC15EF100E6.attr


//## Other Operations (implementation)
//## Operation: GetIdentity%983336508
//	Determines whether an Identity key is valid by testing
//	the BYTE** buf If the Identity is Valid, a pointer to
//	the Identity associated with the cursor key is returned.
//	buf  is incremented to one after the last byte.
//## Postconditions:
//	cursor points to next parameter
Identity* IdentityAnswer::GetIdentity (const BYTE** buf)
{
  //## begin IdentityAnswer::GetIdentity%983336508.body preserve=yes
	const BYTE* cursor = *buf;
	P_IDENTITY pId (&cursor);
	*buf = cursor;
	return GetIdentity(pId);

  //## end IdentityAnswer::GetIdentity%983336508.body
}

//## Operation: GetDefaultAttribute%984007434
//	Gets the Attribute defininded by the P_IDENTITY and
//	index  parameters.  The P_IDENTITY, Attribute type, and
//	Attribute value are returned as parameters. Returns the
//	number of bytes in ret buffer
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned IdentityAnswer::GetDefaultAttribute (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin IdentityAnswer::GetDefaultAttribute%984007434.body preserve=yes
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Identity* pIdentity = GetIdentity (&cursor);
	if (pIdentity)
		{
			if (pIdentity->GetDefaultAttribute ((char*)answer, answer_size))
				{
					ret_bytes = strlen ((const char*)answer) + 1;
				}
		}
	return ret_bytes;

  //## end IdentityAnswer::GetDefaultAttribute%984007434.body
}

//## Operation: PerformOperation%985746356
//	Public function by which all answers are derived.  The
//	member function index is the first byte in the question
//	parameter. After the index is obtained, the appropriate
//	member function is called.  Returns the number of bytes
//	in ret buffer
unsigned IdentityAnswer::PerformOperation (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin IdentityAnswer::PerformOperation%985746356.body preserve=yes
	unsigned ret_bytes = 0;

	// deal with the question
	const BYTE* q_cursor = question;
	unsigned func_index = (unsigned)SMUtility::BufToTargetFunc (&q_cursor);


	if (func_index < eMaxFuncIndex)
		{
			ret_bytes += (pFunc[func_index]) (q_cursor, answer, answer_size);
		}
	return ret_bytes;
  //## end IdentityAnswer::PerformOperation%985746356.body
}

//## Operation: GetName%986510811
//	Gets the name of the identity defininded by the P_
//	IDENTITY   parameters  name is returned in the answer.
//	Returns the number of bytes in ret buffer
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned IdentityAnswer::GetName (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin IdentityAnswer::GetName%986510811.body preserve=yes
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Identity* pIdentity = GetIdentity (&cursor);
	if (pIdentity)
		{
			if (pIdentity->GetName ((char*)answer, answer_size))
				{
					ret_bytes = strlen ((const char*)answer) + 1;
				}
		}
	return ret_bytes;
  //## end IdentityAnswer::GetName%986510811.body
}

//## Operation: GetComment%986510812
//	Gets the comment of the identity defininded by the P_
//	IDENTITY   parameters  name is returned in the answer.
//	Returns the number of bytes in ret buffer
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned IdentityAnswer::GetComment (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin IdentityAnswer::GetComment%986510812.body preserve=yes
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Identity* pIdentity = GetIdentity (&cursor);
	if (pIdentity)
		{
			if (pIdentity->GetComment ((char*)answer, answer_size))
				{
					ret_bytes = strlen ((const char*)answer) + 1;
				}
		}
	return ret_bytes;
  //## end IdentityAnswer::GetComment%986510812.body
}

//## Operation: GetType%986510813
//	Gets the type of the identity defininded by the P_
//	IDENTITY   parameters  name is returned in the answer.
//	Returns the number of bytes in ret buffer
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned IdentityAnswer::GetType (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin IdentityAnswer::GetType%986510813.body preserve=yes
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Identity* pIdentity = GetIdentity (&cursor);
	if (pIdentity)
		{
			if (pIdentity->GetIdType ((char*)answer, answer_size))
				{
					ret_bytes = strlen ((const char*)answer) + 1;
				}
		}
	return ret_bytes;
  //## end IdentityAnswer::GetType%986510813.body
}

//## Operation: GetModified%986510814
//	Gets the modified attribute of the identity defininded
//	by the P_IDENTITY   parameters  name is returned in the
//	answer. Returns the number of bytes in ret buffer
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned IdentityAnswer::GetModified (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin IdentityAnswer::GetModified%986510814.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Identity* pIdentity = GetIdentity (&cursor);
	if (pIdentity)
		{
			unsigned modified = pIdentity->GetModified();
			SMUtility::IntToBuf ((short) modified, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;
  //## end IdentityAnswer::GetModified%986510814.body
}

//## Operation: SetName%986510815
//	Sets the name of the Identity
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
//	new_value
unsigned IdentityAnswer::SetName (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin IdentityAnswer::SetName%986510815.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Identity* pIdentity = GetIdentity (&cursor);
	if (pIdentity)
		{
			bool success = pIdentity->SetName ((const char*)cursor);

			SMUtility::IntToBuf ((short) (success?1:0), answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;
  //## end IdentityAnswer::SetName%986510815.body
}

//## Operation: SetComment%986510816
//	Sets the comment of the Identity
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
//	new_value
unsigned IdentityAnswer::SetComment (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin IdentityAnswer::SetComment%986510816.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Identity* pIdentity = GetIdentity (&cursor);
	if (pIdentity)
		{
			bool success = pIdentity->SetComment ((const char*)cursor);

			SMUtility::IntToBuf ((short) (success?1:0), answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;
  //## end IdentityAnswer::SetComment%986510816.body
}

//## Operation: SetDefaultAttribute%986947728
//	Sets the Attribute defininded by the P_IDENTITY and
//	index  parameters.  The P_IDENTITY, Attribute type, and
//	Attribute value are returned as parameters. Returns the
//	number of bytes in ret buffer
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned IdentityAnswer::SetDefaultAttribute (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin IdentityAnswer::SetDefaultAttribute%986947728.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Identity* pIdentity = GetIdentity (&cursor);
	if (pIdentity)
		{
			bool success = pIdentity->SetDefaultAttribute ((const char*)cursor);

			SMUtility::IntToBuf ((short) (success?1:0), answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end IdentityAnswer::SetDefaultAttribute%986947728.body
}

//## Operation: CanSave%986947730; C++
//	Returns whether a BaseShell Object associated with Input
//	dwpShell key can be saved
//	return_value in Post conditions is a null terminated
//	char*
//## Preconditions:
//	question buf has the parameters as follows
//	P_BASESHELL
unsigned IdentityAnswer::CanSave (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin IdentityAnswer::CanSave%986947730.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	Identity* pIdentity = GetIdentity (&cursor);
	if (pIdentity)
		{
			unsigned can_save = pIdentity->CanSave();
			SMUtility::IntToBuf ((short) can_save, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end IdentityAnswer::CanSave%986947730.body
}

//## Operation: GetParent%986947732; C++
//	Returns the Key to the Parent of the Input dwpShell key.
//	return_value in Post conditions is of type P_PATCH
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
unsigned IdentityAnswer::GetParent (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin IdentityAnswer::GetParent%986947732.body preserve=yes

	if (answer_size < sizeof (P_PATCH))
		{
			return 0;
		}

	const BYTE* cursor = question;
 	Identity* pId = GetIdentity (&cursor);
	if (pId)
		{
			P_PATCH pPatch (pId->GetParent());
			pPatch.toBuf(answer);
		}
	else
		{
			P_PATCH pPatch;
			pPatch.toBuf(answer);
		}

	return sizeof (P_PATCH);


  //## end IdentityAnswer::GetParent%986947732.body
}

//## Operation: SetParent%986947733; C++
//	Sets the Parent parameter of the BaseShell.
//## Preconditions:
//	question buf has the parameters as follows
//	P_IDENTITY
//	P_PATCH
unsigned IdentityAnswer::SetParent (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin IdentityAnswer::SetParent%986947733.body preserve=yes
	const BYTE* cursor = question;
	Identity* pIdentity = GetIdentity (&cursor);
	Patch* pParent =  PatchAnswer::GetPatch (&cursor);

	if (pIdentity)
		{
			pIdentity->SetParent(pParent);
		}

  UNREFERENCED_PARAMETER (answer);
  UNREFERENCED_PARAMETER (answer_size);
	return 0;

  //## end IdentityAnswer::SetParent%986947733.body
}

//## Operation: AddIdentity%1020302311
//	Adds Identity to List of Valid Identies
bool IdentityAnswer::AddIdentity (Identity* id)
{
  //## begin IdentityAnswer::AddIdentity%1020302311.body preserve=yes
  P_IDENTITY pid = P_IDENTITY (id);
	
	DWORD key = pid.Key();

  valid_identities.insert (map_value_type(key, key));
  return true;
  //## end IdentityAnswer::AddIdentity%1020302311.body
}

//## Operation: RemoveIdentity%1020302312
//	RemovesIdentity to List of Valid Identies
bool IdentityAnswer::RemoveIdentity (Identity* id)
{
  //## begin IdentityAnswer::RemoveIdentity%1020302312.body preserve=yes
  P_IDENTITY pid = P_IDENTITY (id);
  bool ret = false;

  if (valid_identities.count(pid.Key()))
  	{
    valid_identities.erase (pid.Key());
    ret = true;
  	}

  return ret;
  //## end IdentityAnswer::RemoveIdentity%1020302312.body
}

//## Operation: GetIdentity%1020302313
//	Returns Identity Given a P_IDENTITY
Identity* IdentityAnswer::GetIdentity (P_IDENTITY pid)
{
  //## begin IdentityAnswer::GetIdentity%1020302313.body preserve=yes
  Identity* ret = NULL;

	if (valid_identities.count (pid.Key()))
  {
  	ret = *pid;
  }
  return ret;

  //## end IdentityAnswer::GetIdentity%1020302313.body
}

// Additional Declarations
  //## begin IdentityAnswer%3A99D27700DE.declarations preserve=yes
  //## end IdentityAnswer%3A99D27700DE.declarations

//## begin module%3ACAAFDE026B.epilog preserve=yes
//## end module%3ACAAFDE026B.epilog
