//## begin module%3D335A94008F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D335A94008F.cm

//## begin module%3D335A94008F.cp preserve=no
//	Angelo Fraietta
//## end module%3D335A94008F.cp

//## Module: ViewAnswer%3D335A94008F; Package body
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\viewanswer.cpp

//## begin module%3D335A94008F.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3D335A94008F.additionalIncludes

//## begin module%3D335A94008F.includes preserve=yes
#include "control.h"
#include "patch.h"
#include "patchview.h"
#include "connectoranswer.h"
//## end module%3D335A94008F.includes

// PatchAnswer
#include "patchanswer.h"
// ViewAnswer
#include "viewanswer.h"
// SMUtility
#include "smutility.h"


//## begin module%3D335A94008F.declarations preserve=no
//## end module%3D335A94008F.declarations

//## begin module%3D335A94008F.additionalDeclarations preserve=yes
//## end module%3D335A94008F.additionalDeclarations


// Class Utility ViewAnswer 

//## begin ViewAnswer::pFunc%3D33613C01BB.attr preserve=no  private: static ViewAnswer::pfunctype [eMaxFuncIndex] {U} {GetNumViews, GetNumViewObjects, GetViewObject, GetViewObjectDisplayParams, AddViewObject, ClearView, GetViewName, SetViewName, ModifyViewObject, AddView, DeleteView, AddViewConnector, GetNumViewConnectors, GetViewConnector,  GetViewConnectorValue,  GetNumViewConnectorValues, AddViewConnectorValue}
ViewAnswer::pfunctype  ViewAnswer::pFunc[eMaxFuncIndex] = {GetNumViews, GetNumViewObjects, GetViewObject, GetViewObjectDisplayParams, AddViewObject, ClearView, GetViewName, SetViewName, ModifyViewObject, AddView, DeleteView, AddViewConnector, GetNumViewConnectors, GetViewConnector,  GetViewConnectorValue,  GetNumViewConnectorValues, AddViewConnectorValue};
//## end ViewAnswer::pFunc%3D33613C01BB.attr


//## Other Operations (implementation)
//## Operation: GetNumViews%1026777694; C++
//	Returns the number of views
unsigned ViewAnswer::GetNumViews (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::GetNumViews%1026777694.body preserve=yes
	if (answer_size < sizeof(short))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
			unsigned num = pPatch->GetNumViews ();
			SMUtility::IntToBuf ((short) num, answer);
			ret = sizeof (short);

		}

	return ret;

  //## end ViewAnswer::GetNumViews%1026777694.body
}

//## Operation: GetNumViewObjects%1026777695; C++
//	Returns the number of object in view
unsigned ViewAnswer::GetNumViewObjects (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::GetNumViewObjects%1026777695.body preserve=yes
	if (answer_size < sizeof(short))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
    	unsigned view_index = SMUtility::BufToInt(&cursor);

      PatchView* pView = pPatch->GetView(view_index);

			unsigned num = pView->GetNumObjects ();
			SMUtility::IntToBuf ((short) num, answer);
			ret = sizeof (short);

		}

	return ret;

  //## end ViewAnswer::GetNumViewObjects%1026777695.body
}

//## Operation: GetViewObject%1026777696; C++
//	Returns the basheshell parameter of object
unsigned ViewAnswer::GetViewObject (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::GetViewObject%1026777696.body preserve=yes
  UNREFERENCED_PARAMETER (question);
  UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);
  return 0;
  //## end ViewAnswer::GetViewObject%1026777696.body
}

//## Operation: GetViewObjectDisplayParams%1026777697; C++
//	Returns the display parameters of the object, being, P_
//	Basehell, top, left, height, width, and tag
unsigned ViewAnswer::GetViewObjectDisplayParams (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::GetViewObjectDisplayParams%1026777697.body preserve=yes

  const unsigned ret_size = sizeof (P_BASESHELL) + sizeof(short) * 5;
	if (answer_size < ret_size)
		{
			return 0;
		}
	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
    	unsigned view_index = SMUtility::BufToInt(&cursor);
      unsigned object_index = SMUtility::BufToInt(&cursor);

      PatchView* pView = pPatch->GetView(view_index);
			BaseShell* pShell;
      unsigned top, left, height, width, tag;

      if (pView->GetObjectParams (object_index, &pShell, &top, &left, &height, &width, &tag))
      {
        P_BASESHELL dwpShell(pShell);
        answer =  dwpShell.toBuf (answer);
        answer = SMUtility::IntToBuf ((short) top, answer);
        answer = SMUtility::IntToBuf ((short) left, answer);
        answer = SMUtility::IntToBuf ((short) height, answer);
        answer = SMUtility::IntToBuf ((short) width, answer);
        SMUtility::IntToBuf ((short) tag, answer);
	ret = ret_size;
      }


		}

	return ret;

  //## end ViewAnswer::GetViewObjectDisplayParams%1026777697.body
}

//## Operation: AddViewObject%1026777698; C++
//	Adds the display parameters of the object, being, p
//	Basehell, top, left, height, width, and tag
unsigned ViewAnswer::AddViewObject (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::AddViewObject%1026777698.body preserve=yes
	if (answer_size < sizeof(short))
		{
			return 0;
		}
	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
    	unsigned view_index = SMUtility::BufToInt(&cursor);

      PatchView* pView = pPatch->GetView(view_index);
			BaseShell* pShell = BaseShellAnswer::GetBaseShell(&cursor);

      if (pShell && pView)
      {
      	unsigned top, left, height, width, tag;
        top = SMUtility::BufToInt(&cursor);
        left = SMUtility::BufToInt(&cursor);
        height = SMUtility::BufToInt(&cursor);
        width = SMUtility::BufToInt(&cursor);
        tag = SMUtility::BufToInt(&cursor);
        pView->AddObject(pShell, top, left, height, width, tag);
        SMUtility::IntToBuf ((short) 1, answer);
        ret = sizeof(short);
    	}

    }
  return ret;
  //## end ViewAnswer::AddViewObject%1026777698.body
}

//## Operation: PerformOperation%1026777693
//	Public function by which all answers are derived.  The
//	member function index is the first byte in the question
//	parameter. After the index is obtained, the appropriate
//	member function is called.
unsigned ViewAnswer::PerformOperation (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::PerformOperation%1026777693.body preserve=yes
	unsigned ret_bytes = 0;

	// deal with the question
	const BYTE* q_cursor = question;
	unsigned func_index = (unsigned)SMUtility::BufToTargetFunc (&q_cursor);


	if (func_index < eMaxFuncIndex)
		{
			ret_bytes += (pFunc[func_index]) (q_cursor, answer, answer_size);
		}
	return ret_bytes;
  
  //## end ViewAnswer::PerformOperation%1026777693.body
}

//## Operation: ClearView%1026777699; C++
//	Clears View
unsigned ViewAnswer::ClearView (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::ClearView%1026777699.body preserve=yes
	const BYTE* cursor = question;
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
    	unsigned view_index = SMUtility::BufToInt(&cursor);

      PatchView* pView = pPatch->GetView(view_index);

			pView->ClearView ();

		}

  UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);

	return 0;
  //## end ViewAnswer::ClearView%1026777699.body
}

//## Operation: GetViewName%1026777706; C++
//	gets the Name of the View
unsigned ViewAnswer::GetViewName (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::GetViewName%1026777706.body preserve=yes
  unsigned ret_bytes = 0;

	const BYTE* cursor = question;
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
    	unsigned view_index = SMUtility::BufToInt(&cursor);

      PatchView* pView = pPatch->GetView(view_index);

      if (pView && pView->GetName ((char*)answer, answer_size))
				{
					ret_bytes = strlen ((const char*)answer) + 1;
				}
		}

  return ret_bytes;
  //## end ViewAnswer::GetViewName%1026777706.body
}

//## Operation: SetViewName%1026777707; C++
//	Sets the Name of the View
unsigned ViewAnswer::SetViewName (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::SetViewName%1026777707.body preserve=yes
	const BYTE* cursor = question;
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
    	unsigned view_index = SMUtility::BufToInt(&cursor);

      PatchView* pView = pPatch->GetView(view_index);
      if (pView)
      {
      	pView->SetName ((const char*)cursor);
      }
    }

  UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);

  return 0;
  //## end ViewAnswer::SetViewName%1026777707.body
}

//## Operation: AddView%1026777714; C++
//	Adds a view and returns the index
unsigned ViewAnswer::AddView (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::AddView%1026777714.body preserve=yes
	if (answer_size < sizeof(short))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
			unsigned num = pPatch->AddView ();
			SMUtility::IntToBuf ((short) num, answer);
			ret = sizeof (short);

		}

	return ret;

  //## end ViewAnswer::AddView%1026777714.body
}

//## Operation: DeleteView%1026777715; C++
//	Adds a view and returns the index
unsigned ViewAnswer::DeleteView (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::DeleteView%1026777715.body preserve=yes
  UNREFERENCED_PARAMETER (question);
  UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);

  return 0;
  //## end ViewAnswer::DeleteView%1026777715.body
}

//## Operation: AddViewConnector%1049496124
//	Adds the Connector To View Object
unsigned ViewAnswer::AddViewConnector (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::AddViewConnector%1049496124.body preserve=yes
	if (answer_size < sizeof(short))
		{
			return 0;
		}
	unsigned ret = 0;

	const BYTE* cursor = question;
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
    	unsigned view_index = SMUtility::BufToInt(&cursor);

      PatchView* pView = pPatch->GetView(view_index);
			Connector* pCon = ConnectorAnswer::GetConnector(&cursor);

      if (pCon && pView)
      {
        int index;
        index = pView->AddConnector(pCon);
        SMUtility::IntToBuf ((short) index, answer);
        ret = sizeof(short);
    	}

    }
  return ret;

  //## end ViewAnswer::AddViewConnector%1049496124.body
}

//## Operation: GetNumViewConnectors%1049496125
//	Returns the Number OF View Connectors within View
unsigned ViewAnswer::GetNumViewConnectors (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::GetNumViewConnectors%1049496125.body preserve=yes
	if (answer_size < sizeof(short))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
    	unsigned view_index = SMUtility::BufToInt(&cursor);

      PatchView* pView = pPatch->GetView(view_index);

			unsigned num = pView->GetNumConnectors ();
			SMUtility::IntToBuf ((short) num, answer);
			ret = sizeof (short);

		}

	return ret;


  //## end ViewAnswer::GetNumViewConnectors%1049496125.body
}

//## Operation: GetViewConnector%1049496126
//	Returns the Connector Pointed to at ViewIndex
unsigned ViewAnswer::GetViewConnector (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::GetViewConnector%1049496126.body preserve=yes

  const unsigned ret_size = sizeof (P_BASESHELL);
	if (answer_size < ret_size)
		{
			return 0;
		}
	unsigned ret = 0;

	const BYTE* cursor = question;
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
    	unsigned view_index = SMUtility::BufToInt(&cursor);
      unsigned object_index = SMUtility::BufToInt(&cursor);

      PatchView* pView = pPatch->GetView(view_index);
			Connector* pCon;

      pCon = pView->GetConnector (object_index);
      if (pCon)
				{
        P_CONNECTOR dwpCon(pCon);
        dwpCon.toBuf (answer);
				ret = ret_size;
        }
		}

	return ret;
  //## end ViewAnswer::GetViewConnector%1049496126.body
}

//## Operation: GetViewConnectorValue%1049496127
//	Returns the Value Stored at the point
unsigned ViewAnswer::GetViewConnectorValue (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::GetViewConnectorValue%1049496127.body preserve=yes
  const unsigned ret_size = sizeof (short);
	if (answer_size < ret_size)
		{
			return 0;
		}
	unsigned ret = 0;

	const BYTE* cursor = question;
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
    	unsigned view_index = SMUtility::BufToInt(&cursor);
      unsigned object_index = SMUtility::BufToInt(&cursor);
      unsigned value_index = SMUtility::BufToInt(&cursor);
      int value;
      PatchView* pView = pPatch->GetView(view_index);

      value = pView->GetConnectorValue (object_index, value_index);
      SMUtility::IntToBuf ((short) value, answer);
      ret = ret_size;
		}

	return ret;
  //## end ViewAnswer::GetViewConnectorValue%1049496127.body
}

//## Operation: GetNumViewConnectorValues%1049496128
//	Returns the Number of Values at a given Connector View
//	Point
unsigned ViewAnswer::GetNumViewConnectorValues (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::GetNumViewConnectorValues%1049496128.body preserve=yes
  const unsigned ret_size = sizeof (short);
	if (answer_size < ret_size)
		{
			return 0;
		}
	unsigned ret = 0;

	const BYTE* cursor = question;
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
    	unsigned view_index = SMUtility::BufToInt(&cursor);
      unsigned object_index = SMUtility::BufToInt(&cursor);
      unsigned num_values;
      PatchView* pView = pPatch->GetView(view_index);

      num_values = pView->GetNumConnectorValues (object_index);
      SMUtility::IntToBuf ((short) num_values, answer);
      ret = ret_size;
		}

	return ret;

  //## end ViewAnswer::GetNumViewConnectorValues%1049496128.body
}

//## Operation: ModifyViewObject%1026777711; C++
//	Modifiesthe display parameters of the object, being,
//	top, left, height, width, and tag given a Baseshell
unsigned ViewAnswer::ModifyViewObject (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::ModifyViewObject%1026777711.body preserve=yes
	const BYTE* cursor = question;
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
    	unsigned view_index = SMUtility::BufToInt(&cursor);

      PatchView* pView = pPatch->GetView(view_index);
      if (pView)
      {
      	BaseShell* pShell = BaseShellAnswer::GetBaseShell(&cursor);
      	unsigned top, left, height, width, tag;
        top = SMUtility::BufToInt(&cursor);
        left = SMUtility::BufToInt(&cursor);
        height = SMUtility::BufToInt(&cursor);
        width = SMUtility::BufToInt(&cursor);
        tag = SMUtility::BufToInt(&cursor);
        pView->ModifyObject(pShell, top, left, height, width, tag);
        SMUtility::IntToBuf ((short) 1, answer);
    	}

    }
  UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);
  return 0;
  //## end ViewAnswer::ModifyViewObject%1026777711.body
}

//## Operation: AddViewConnectorValue%1049496129; C++
//	Adds A New View Connector Value
unsigned ViewAnswer::AddViewConnectorValue (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin ViewAnswer::AddViewConnectorValue%1049496129.body preserve=yes
	const BYTE* cursor = question;
	Patch* pPatch = PatchAnswer::GetPatch (&cursor);
	if (pPatch)
		{
    	unsigned view_index = SMUtility::BufToInt(&cursor);

      PatchView* pView = pPatch->GetView(view_index);
      if (pView)
      {
      	unsigned object_num;                                             
        int new_value;
        bool ret;

        object_num = (unsigned)SMUtility::BufToInt(&cursor);
        new_value = SMUtility::BufToInt(&cursor);

        ret = pView->AddConnectorValue(object_num, new_value);
        SMUtility::IntToBuf ((short) ret, answer);
    	}

    }
  UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);
  return 0;

  //## end ViewAnswer::AddViewConnectorValue%1049496129.body
}

// Additional Declarations
  //## begin ViewAnswer%3D335A550193.declarations preserve=yes
  //## end ViewAnswer%3D335A550193.declarations

//## begin module%3D335A94008F.epilog preserve=yes
//## end module%3D335A94008F.epilog
