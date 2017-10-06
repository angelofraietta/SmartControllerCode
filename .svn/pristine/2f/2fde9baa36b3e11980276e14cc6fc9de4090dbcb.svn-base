
#ifndef SOCKET_CPP
#define SOCKET_CPP

#include "stdafx.h"
#include "control.h"
#include <algorithm>



bool SocketContainer::RemoveConnector (const Connector* pCon)
{
	
  bool Success;
  // test for equality
	if (!pCon) return false;
  
  Success = false;
  unsigned Size = (unsigned) apConnector.size();
  for(unsigned i = 0; i < Size &&!Success; i++) //has been found
    {
      if(*pCon == *(apConnector[i]))
				{
					apConnector.erase(&apConnector[i]);
					Success = true;
				}
    }
	
  return  Success;
}


bool SocketContainer::HasConnector(const Connector* pTestCon)const
{
  //std::vector <Connector *>::const_iterator iter;
	
	/* for(iter = apConnector.begin();
		 iter!= apConnector.end(); ++iter)
  */
  if (!pTestCon) return false;
	for (unsigned i = 0; i < apConnector.size(); i++)
		{
			//Connector const*pCon = *iter;
			Connector const*pCon = apConnector [i];
			if (*pTestCon == *pCon)
				return 1;
		};
	return 0;
}

bool SocketContainer::AddConnector (Connector* pCon)
{
  // see if already exists
  if(!HasConnector(pCon))
    {
      apConnector.push_back(pCon);
      return 1;
    }
  else
    return 0;
}

Connector* SocketContainer::GetConnector(unsigned Index)
{
  unsigned Size;
	
  Size = (unsigned) apConnector.size();
  if (Index >= Size)
    return NULL;
  else
    return apConnector[Index];
}

unsigned SocketContainer::GetNumConnectors()const
{
  return (unsigned) apConnector.size();
	
}

unsigned SocketContainer::FindIndex(const Connector* pCon)const
{
  // assumes that the connector exists
  unsigned Index;
  unsigned Size;
	if (!pCon) return 0;
  
  Size = (unsigned) apConnector.size();
  for(Index = 0; Index < Size; Index++ )
    {
      Connector* pTest = apConnector[Index];
      if (pTest == pCon)
				break;
    }
  return Index;
	
}

void SocketContainer::SwapConnector(unsigned Index1, unsigned Index2)
{
  unsigned Size;
	
  Size = (unsigned) apConnector.size();
	
  if(Index1 < Size && Index2 < Size)
    {
      Connector* pTemp = apConnector[Index1];
      apConnector[Index1] = apConnector[Index2];
      apConnector[Index2] = pTemp;
    }
}
//***********************************************************************

bool InletContainer::DeleteConnectors()
{
  bool Success = true;
  Connector* pCon;
  int Size;
	
  Size = apConnector.size();
	
  for(int i = Size - 1; i >= 0; i--)
    {
      pCon = apConnector[i];;
      Success = Success && pCon->Disconnect(Connector::ByInlet);
    };
  return Success;
}



#endif
