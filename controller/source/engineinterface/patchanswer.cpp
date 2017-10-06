//## begin module%3A9C920B0193.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A9C920B0193.cm

//## begin module%3A9C920B0193.cp preserve=no
//	Angelo Fraietta
//## end module%3A9C920B0193.cp

//## Module: PatchAnswer%3A9C920B0193; Package body
//	Contains the header information for obtaining Answers to
//	Patchs.  Module has been added as this Module body
//	contains class definitions
//## Subsystem: engineinterface%3A9C858C00CB
//	c:\develop\smartcontroller\controller\source\engineinterf
//	ace
//## Source file: c:\develop\winsmartcontroller\controller\source\engineinterface\patchanswer.cpp

//## begin module%3A9C920B0193.additionalIncludes preserve=no
#include "stdafx.h"
#include "control.h"
#include "patch.h"
#include "identityanswer.h"
#include "scheduler.h"
//## end module%3A9C920B0193.additionalIncludes

//## begin module%3A9C920B0193.includes preserve=yes
#include "fileanswer.h"
//## end module%3A9C920B0193.includes

// timer
#include "timer.h"
// ConnectorAnswer
#include "connectoranswer.h"
// PatchAnswer
#include "patchanswer.h"

class BaseShell;
class Patch;
class DetachBaseShell;
class PatchDeleter;

//## begin module%3A9C920B0193.declarations preserve=no
//## end module%3A9C920B0193.declarations

//## begin module%3A9C920B0193.additionalDeclarations preserve=yes
//## end module%3A9C920B0193.additionalDeclarations


//## begin DetachBaseShell%3A99EED80225.preface preserve=yes
//## end DetachBaseShell%3A99EED80225.preface

//## Class: DetachBaseShell%3A99EED80225
//## Category: EngineInterface%3A998EE60122
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3A9C8B54035E;BaseShell { -> F}

class DetachBaseShell : public DelayLine  //## Inherits: <unnamed>%3A99F0520020
{
  //## begin DetachBaseShell%3A99EED80225.initialDeclarations preserve=yes
  //## end DetachBaseShell%3A99EED80225.initialDeclarations

  public:
    //## Constructors (generated)
      DetachBaseShell();

    //## Destructor (generated)
      ~DetachBaseShell();


    //## Other Operations (specified)
      //## Operation: Send%983336552
      bool Send (BaseShell* receiver);

    // Additional Public Declarations
      //## begin DetachBaseShell%3A99EED80225.public preserve=yes
      //## end DetachBaseShell%3A99EED80225.public

  protected:

    //## Other Operations (specified)
      //## Operation: PurgeItem%983336557; C++
      void PurgeItem (unsigned long );

    // Additional Protected Declarations
      //## begin DetachBaseShell%3A99EED80225.protected preserve=yes
      //## end DetachBaseShell%3A99EED80225.protected

  private:

    //## Other Operations (specified)
      //## Operation: OutputFunction%983336553; C++
      void OutputFunction (DWORD receiver);

    // Additional Private Declarations
      //## begin DetachBaseShell%3A99EED80225.private preserve=yes
      //## end DetachBaseShell%3A99EED80225.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin DetachBaseShell%3A99EED80225.implementation preserve=yes
      //## end DetachBaseShell%3A99EED80225.implementation

};

//## begin DetachBaseShell%3A99EED80225.postscript preserve=yes
//## end DetachBaseShell%3A99EED80225.postscript

//## begin PatchDeleter%3A99EB1401F7.preface preserve=yes
//## end PatchDeleter%3A99EB1401F7.preface

//## Class: PatchDeleter%3A99EB1401F7
//	Class instance for deleting Patches.  The request is
//	passed through the Send function to the Scheduler.  When
//	the Scheduler task actions the request, the Output
//	Function is called, which in turn deletes the Patch.
//## Category: EngineInterface::Answer%3AA7F4FF028C
//## Subsystem: engineinterface%3A9C858C00CB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3A9C8ABF033B;BaseShell { -> F}

class PatchDeleter : public DelayLine  //## Inherits: <unnamed>%3A99EB3D01EC
{
  //## begin PatchDeleter%3A99EB1401F7.initialDeclarations preserve=yes
  //## end PatchDeleter%3A99EB1401F7.initialDeclarations

  public:
    //## Constructors (generated)
      PatchDeleter();

    //## Destructor (generated)
      ~PatchDeleter();


    //## Other Operations (specified)
      //## Operation: Send%983336474
      bool Send (Patch* receiver);

    // Additional Public Declarations
      //## begin PatchDeleter%3A99EB1401F7.public preserve=yes
      //## end PatchDeleter%3A99EB1401F7.public

  protected:

    //## Other Operations (specified)
      //## Operation: PurgeItem%983336555; C++
      void PurgeItem (unsigned long );

    // Additional Protected Declarations
      //## begin PatchDeleter%3A99EB1401F7.protected preserve=yes
      //## end PatchDeleter%3A99EB1401F7.protected

  private:

    //## Other Operations (specified)
      //## Operation: OutputFunction%983336475; C++
      void OutputFunction (DWORD receiver);

    // Additional Private Declarations
      //## begin PatchDeleter%3A99EB1401F7.private preserve=yes
      //## end PatchDeleter%3A99EB1401F7.private

  private: //## implementation
    // Data Members for Associations

      //## Association: EngineInterface::<unnamed>%3A99EBF4005F
      //## Role: PatchDeleter::receiver%3A99EBF50006
      //## begin PatchDeleter::receiver%3A99EBF50006.role preserve=no  public: Patch { -> nRFHN}
      //## end PatchDeleter::receiver%3A99EBF50006.role

    // Additional Implementation Declarations
      //## begin PatchDeleter%3A99EB1401F7.implementation preserve=yes
      //## end PatchDeleter%3A99EB1401F7.implementation

};

//## begin PatchDeleter%3A99EB1401F7.postscript preserve=yes
//## end PatchDeleter%3A99EB1401F7.postscript

// Class DetachBaseShell 


//## Other Operations (inline)
//## Operation: PurgeItem%983336557; C++
//	Empty function required by DelayLine anccestor class
inline void DetachBaseShell::PurgeItem (unsigned long )
{
  //## begin DetachBaseShell::PurgeItem%983336557.body preserve=yes
  //## end DetachBaseShell::PurgeItem%983336557.body
}

// Class PatchDeleter 


//## Other Operations (inline)
//## Operation: PurgeItem%983336555; C++
//	Empty function required by DelayLine anccestor class
inline void PatchDeleter::PurgeItem (unsigned long )
{
  //## begin PatchDeleter::PurgeItem%983336555.body preserve=yes
  //## end PatchDeleter::PurgeItem%983336555.body
}

// Class DetachBaseShell 


DetachBaseShell::DetachBaseShell()
  //## begin DetachBaseShell::DetachBaseShell%.hasinit preserve=no
  //## end DetachBaseShell::DetachBaseShell%.hasinit
  //## begin DetachBaseShell::DetachBaseShell%.initialization preserve=yes
  //## end DetachBaseShell::DetachBaseShell%.initialization
{
  //## begin DetachBaseShell::DetachBaseShell%.body preserve=yes
  //## end DetachBaseShell::DetachBaseShell%.body
}


DetachBaseShell::~DetachBaseShell()
{
  //## begin DetachBaseShell::~DetachBaseShell%.body preserve=yes
  //## end DetachBaseShell::~DetachBaseShell%.body
}



//## Other Operations (implementation)
//## Operation: Send%983336552
//	Sends a request message to the Scheduler. Returns true
//	if request was successful
bool DetachBaseShell::Send (BaseShell* receiver)
{
  return GoOneShot ((DWORD)receiver);

  //## begin DetachBaseShell::Send%983336552.body preserve=yes
  //## end DetachBaseShell::Send%983336552.body
}

//## Operation: OutputFunction%983336553; C++
void DetachBaseShell::OutputFunction (DWORD receiver)
{
  BaseShell* pShell = (BaseShell*)receiver;
  Patch* pPatch = pShell->GetParent ();
  pPatch->Detach (pShell);

  //## begin DetachBaseShell::OutputFunction%983336553.body preserve=yes
  //## end DetachBaseShell::OutputFunction%983336553.body
}

// Additional Declarations
  //## begin DetachBaseShell%3A99EED80225.declarations preserve=yes
  //## end DetachBaseShell%3A99EED80225.declarations

// Class Utility PatchAnswer 

//## begin PatchAnswer::pFunc%3ADFC3F40369.attr preserve=no  private: static PatchAnswer::pfunctype [eMaxFuncIndex] {U} {DetachBaseShellObject, FindBaseShellPosition, AddBaseShell, NumberBaseShells, FindBaseShell, DetachConnector, AddConnector, NumberConnectors, FindConnector, GetDeadConnector, AddInlet, AddOutlet, MakeNew, SetFileName, LoadPatchFile, GetFileName, Save, Destroy, SwapOutlets, SwapInlets, GetInlet, GetOutlet, GetOutletPortNumber, GetInletPortNumber, NumberPatches, GetPatch}
PatchAnswer::pfunctype  PatchAnswer::pFunc[eMaxFuncIndex] = {DetachBaseShellObject, FindBaseShellPosition, AddBaseShell, NumberBaseShells, FindBaseShell, DetachConnector, AddConnector, NumberConnectors, FindConnector, GetDeadConnector, AddInlet, AddOutlet, MakeNew, SetFileName, LoadPatchFile, GetFileName, Save, Destroy, SwapOutlets, SwapInlets, GetInlet, GetOutlet, GetOutletPortNumber, GetInletPortNumber, NumberPatches, GetPatch};
//## end PatchAnswer::pFunc%3ADFC3F40369.attr

//## begin PatchAnswer::_PatchDelete%3A99EC60000A.role preserve=no  public: static PatchDeleter { -> 1VFHN}
PatchDeleter PatchAnswer::_PatchDelete;
//## end PatchAnswer::_PatchDelete%3A99EC60000A.role

//## begin PatchAnswer::_DetachBaseShell%3A99EFF80144.role preserve=no  public: static DetachBaseShell { -> 1VFHN}
DetachBaseShell PatchAnswer::_DetachBaseShell;
//## end PatchAnswer::_DetachBaseShell%3A99EFF80144.role


//## Other Operations (implementation)
//## Operation: DetachBaseShellObject%983336476; C++
//	Deletes a BaseShell object from the Patch.
unsigned PatchAnswer::DetachBaseShellObject (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::DetachBaseShellObject%983336476.body preserve=yes
	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	if (pPatch)
		{
			BaseShell* pShell = BaseShellAnswer::GetBaseShell (&cursor);
			if (pShell)
				{
					pPatch->Detach (pShell);
				}
		}
	UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);
	return 0;

  //## end PatchAnswer::DetachBaseShellObject%983336476.body
}

//## Operation: FindBaseShellPosition%983336477; C++
//	Returns the index that a  BaseShell has within the Patch.
unsigned PatchAnswer::FindBaseShellPosition (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::FindBaseShellPosition%983336477.body preserve=yes
	if (answer_size < sizeof(short))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	if (pPatch)
		{
			BaseShell* pShell = BaseShellAnswer::GetBaseShell (&cursor);
			if (pShell)
				{
					unsigned pos = pPatch->FindPosition (pShell);
					SMUtility::IntToBuf ((short) pos, answer);
					ret = sizeof (short);
				}
		}

	return ret;

  //## end PatchAnswer::FindBaseShellPosition%983336477.body
}

//## Operation: AddBaseShell%983336478; C++
//	Inserts a BaseShell Object into th Patch
unsigned PatchAnswer::AddBaseShell (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::AddBaseShell%983336478.body preserve=yes
	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	if (pPatch)
		{
			BaseShell* pShell = BaseShellAnswer::GetBaseShell (&cursor);
			if (pShell)
				{
					pPatch->Add (pShell);
				}
		}
	UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);
	return 0;
  //## end PatchAnswer::AddBaseShell%983336478.body
}

//## Operation: NumberBaseShells%983336479; C++
//	Returns the Number of BaseShells the Patch has
unsigned PatchAnswer::NumberBaseShells (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::NumberBaseShells%983336479.body preserve=yes
	if (answer_size < sizeof(short))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	if (pPatch)
		{
			unsigned num = pPatch->NumObjects ();
			SMUtility::IntToBuf ((short) num, answer);
			ret = sizeof (short);
			
		}

	return ret;

  //## end PatchAnswer::NumberBaseShells%983336479.body
}

//## Operation: FindBaseShell%983336480; C++
//	Returns the BaseShell at the Patch index.
unsigned PatchAnswer::FindBaseShell (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::FindBaseShell%983336480.body preserve=yes
	if (answer_size < sizeof(P_BASESHELL))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	unsigned pos = SMUtility::BufToInt(&cursor);
	if (pPatch)
		{
			P_BASESHELL pShell (pPatch->FindObject (pos));
			pShell.toBuf (answer);
			ret = sizeof (P_BASESHELL);
			
		}

	return ret;

  //## end PatchAnswer::FindBaseShell%983336480.body
}

//## Operation: DetachConnector%983336481; C++
//	Deletes a Connector from the Patch
unsigned PatchAnswer::DetachConnector (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::DetachConnector%983336481.body preserve=yes
 	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	if (pPatch)
		{
			Connector* pCon = ConnectorAnswer::GetConnector (&cursor);
			if (pCon)
				{
					pPatch->Detach (pCon, Patch::ByUserInterface);
				}
		}
	UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);
	return 0;

  //## end PatchAnswer::DetachConnector%983336481.body
}

//## Operation: AddConnector%983336482; C++
//	Inserts a Connector into the Patch
unsigned PatchAnswer::AddConnector (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::AddConnector%983336482.body preserve=yes
	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	if (pPatch)
		{
			Connector* pCon = ConnectorAnswer::GetConnector (&cursor);
			if (pCon)
				{
					pPatch->Add (pCon);
				}
		}
	UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);
	return 0;

  //## end PatchAnswer::AddConnector%983336482.body
}

//## Operation: NumberConnectors%983336483; C++
//	Returns the number of Connectors a Patch has.
unsigned PatchAnswer::NumberConnectors (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::NumberConnectors%983336483.body preserve=yes
	if (answer_size < sizeof(short))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	if (pPatch)
		{
			unsigned num = pPatch->NumConnectors ();
			SMUtility::IntToBuf ((short) num, answer);
			ret = sizeof (short);
			
		}

	return ret;

  //## end PatchAnswer::NumberConnectors%983336483.body
}

//## Operation: FindConnector%983336484; C++
//	Returns the Connector at the Patch index.
unsigned PatchAnswer::FindConnector (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::FindConnector%983336484.body preserve=yes
	if (answer_size < sizeof(P_CONNECTOR))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	unsigned pos = SMUtility::BufToInt(&cursor);
	if (pPatch)
		{
			P_CONNECTOR pCon (pPatch->FindConnector (pos));
			pCon.toBuf (answer);
			ret = sizeof (P_CONNECTOR);
			
		}

	return ret;

  //## end PatchAnswer::FindConnector%983336484.body
}

//## Operation: GetDeadConnector%983336485; C++
//	Returns the old P_CONNECTOR key of a Connectors that
//	were deleted by deleting BaseShell objects to which they
//	were connected, thus allowing the PatchEditor to stay in
//	sync with the Engine.  This call is normally done
//	through itteration until there are no more returned.
unsigned PatchAnswer::GetDeadConnector (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::GetDeadConnector%983336485.body preserve=yes
	if (answer_size < sizeof(P_CONNECTOR))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	if (pPatch)
		{
			P_CONNECTOR pCon (pPatch->GetDeadConnector ());
			pCon.toBuf (answer);
			ret = sizeof (P_CONNECTOR);
			
		}

	return ret;
	
  //## end PatchAnswer::GetDeadConnector%983336485.body
}

//## Operation: AddInlet%983336486; C++
//	Adds a New Inlet to the Patch and returns the P_
//	BASESHELL key for it
unsigned PatchAnswer::AddInlet (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::AddInlet%983336486.body preserve=yes
	if (answer_size < sizeof(P_BASESHELL))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);

	if (pPatch)
		{
			P_BASESHELL pShell (pPatch->AddInlet ());
			pShell.toBuf (answer);
			ret = sizeof (P_BASESHELL);
			
		}

	return ret;

  //## end PatchAnswer::AddInlet%983336486.body
}

//## Operation: AddOutlet%983336487; C++
//	Adds a New Outlet to the Patch and returns the P_
//	BASESHELL key for it
unsigned PatchAnswer::AddOutlet (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::AddOutlet%983336487.body preserve=yes
	if (answer_size < sizeof(P_BASESHELL))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);

	if (pPatch)
		{
			P_BASESHELL pShell (pPatch->AddOutlet ());
			pShell.toBuf (answer);
			ret = sizeof (P_BASESHELL);
			
		}

	return ret;
  //## end PatchAnswer::AddOutlet%983336487.body
}

//## Operation: MakeNew%983336488; C++
//	Creates a new Patch based upon the input name. The P_
//	PATCH key is returned
unsigned PatchAnswer::MakeNew (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::MakeNew%983336488.body preserve=yes
	if (answer_size < sizeof (P_PATCH))
		{
			return 0;
		}
	const char* name = (const char*) question;
	Patch* pPatch = new Patch (name);
	P_PATCH dwpPatch (pPatch);

  Patch::AddPatch(pPatch);
	dwpPatch.toBuf(answer);
	return sizeof (P_PATCH);
  //## end PatchAnswer::MakeNew%983336488.body
}

//## Operation: SetFileName%983336489; C++
//	Sets the Filename attribute of a Patch
unsigned PatchAnswer::SetFileName (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::SetFileName%983336489.body preserve=yes
  printf ("PatchAnswer::SetFileName\r\n");
	const BYTE* cursor = question;
	Patch* pPatch = GetPatch (&cursor);
	const char* filename = (const char*)cursor;
	if (pPatch)
		{
			pPatch->SetFileName(filename);

		}
	UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);
	return 0;
  //## end PatchAnswer::SetFileName%983336489.body
}

//## Operation: LoadPatchFile%983336490; C++
//	Loads a Patch from file given the filename of the Patch
//	and the Parent of the Patch. Rteurns the P_PATCH of the
//	loaded Patch
unsigned PatchAnswer::LoadPatchFile (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::LoadPatchFile%983336490.body preserve=yes
  unsigned ret = 0;

	const BYTE* cursor = question;
	Patch* pParent = GetPatch(&cursor);
	const char* name = (const char*) cursor;

	// see if the patch is already loaded
	bool found = false;
	unsigned num_patches = Patch::NumPatches ();
	unsigned i = 0;

	while (!found && i < num_patches)
		{
			Patch* pPatch = Patch::GetPatch (i);
			if(!strcmp (name, pPatch->GetFileName()))
				{
					found = true;
					P_PATCH dwpPatch ((Patch*)NULL);

          if ((answer) && answer_size >= sizeof (P_PATCH))
          {
            dwpPatch.toBuf(answer);
          }


				}
			i++;
		}

	if (!found || (pParent))
	{
		printf("LoadPatchFile  %s\r\n", name); 
		
		P_PATCH dwpPatch  = ((Patch*)(Patch::LoadPatchFile(name, pParent)));
    if ((answer) && answer_size >= sizeof (P_PATCH))
    {
      dwpPatch.toBuf(answer);
    }

	}

  if (answer_size >= sizeof (P_PATCH))
  {
  	ret = sizeof (P_PATCH);
  }
  return ret;
  //## end PatchAnswer::LoadPatchFile%983336490.body
}

//## Operation: GetFileName%983336491; C++
//	Returns the filename of the Patch
unsigned PatchAnswer::GetFileName (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::GetFileName%983336491.body preserve=yes
	const BYTE* cursor = question;
	unsigned ret_bytes = 0;
	Patch* pPatch = GetPatch (&cursor);
	if (pPatch)
		{
			char* filename = (char*)answer;
			pPatch->GetFileName (filename, answer_size-1 );
			ret_bytes = strlen (filename) + 1;
		}
	return ret_bytes;

  //## end PatchAnswer::GetFileName%983336491.body
}

//## Operation: Save%983336492; C++
//	Saves the Patch to the filesystem using the  filename
//	parameter
unsigned PatchAnswer::Save (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::Save%983336492.body preserve=yes
	const BYTE* cursor = question;
	unsigned ret_bytes = 0;
	Patch* pPatch = GetPatch (&cursor);
  const char* filename = (const char*)cursor;

  if (pPatch)
  {
    const char* default_dir = FileAnswer::GetDefaultDirName();

    char filepath  [256];                           

    if (default_dir)
    {
      strcpy (filepath, default_dir);
    }
    else
    {
      filepath[0] = '\0';
    }

    strcat (filepath, filename);

    FILE* fp = fopen (filepath, "w+");

    if (fp)
    {
      pPatch->Save(fp);
      fclose (fp);
    }
  }

	return 0;

  //## end PatchAnswer::Save%983336492.body
}

//## Operation: Destroy%983336493; C++
//	Deletes the Patch.
unsigned PatchAnswer::Destroy (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::Destroy%983336493.body preserve=yes
	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	if (pPatch)
		{
			_PatchDelete.Send (pPatch);
		}
	else
		{
			// delete default patch
			_PatchDelete.Send (0);

		}

	UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);
	return 0;

  //## end PatchAnswer::Destroy%983336493.body
}

//## Operation: SwapOutlets%983336494; C++
//	Swaps the position of the two outlets, whose indexes are
//	passed as parameters
unsigned PatchAnswer::SwapOutlets (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::SwapOutlets%983336494.body preserve=yes
 	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	if (pPatch)
		{
			unsigned index1 = SMUtility::BufToInt(&cursor);
			unsigned index2 = SMUtility::BufToInt(&cursor);
			pPatch ->SwapOutlets (index1, index2);
		}

	UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);
	return 0;
  //## end PatchAnswer::SwapOutlets%983336494.body
}

//## Operation: SwapInlets%983336495; C++
//	Swaps the position of the two intlets, whose indexes are
//	passed as parameters
unsigned PatchAnswer::SwapInlets (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::SwapInlets%983336495.body preserve=yes
 	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	if (pPatch)
		{
			unsigned index1 = SMUtility::BufToInt(&cursor);
			unsigned index2 = SMUtility::BufToInt(&cursor);
			pPatch ->SwapInlets (index1, index2);
		}

	UNREFERENCED_PARAMETER (answer);
	UNREFERENCED_PARAMETER (answer_size);
	return 0;
  //## end PatchAnswer::SwapInlets%983336495.body
}

//## Operation: GetInlet%983336496; C++
//	Returns the P_BASESHELL of the Object that is the Inlet
//	of the Patch, the Inlet specified as the inlet_num
//	parameter
unsigned PatchAnswer::GetInlet (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::GetInlet%983336496.body preserve=yes
	if (answer_size < sizeof(P_BASESHELL))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	unsigned index = SMUtility::BufToInt(&cursor);
	if (pPatch)
		{
			P_BASESHELL pShell (pPatch->GetInlet (index));
			pShell.toBuf (answer);
			ret = sizeof (P_BASESHELL);
			
		}

	return ret;
  //## end PatchAnswer::GetInlet%983336496.body
}

//## Operation: GetOutlet%983336497; C++
//	Returns the P_BASESHELL of the Object that is the Outlet
//	of the Patch, the Outlet specified as the outlet_num
//	parameter
unsigned PatchAnswer::GetOutlet (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::GetOutlet%983336497.body preserve=yes
	if (answer_size < sizeof(P_BASESHELL))
		{
			return 0;
		}

	unsigned ret = 0;

	const BYTE* cursor = question;	
	Patch* pPatch = GetPatch (&cursor);
	unsigned index = SMUtility::BufToInt(&cursor);
	if (pPatch)
		{
			P_BASESHELL pShell (pPatch->GetOutlet (index));
			pShell.toBuf (answer);
			ret = sizeof (P_BASESHELL);
			
		}

	return ret;
  //## end PatchAnswer::GetOutlet%983336497.body
}

//## Operation: GetPatch%983336498
//	Determines whether a Patch key is valid by testing the
//	dwpPatch. If the Patch is Valid, a pointer to the Patch
//	associated with the dwpPatch key is returned.
Patch* PatchAnswer::GetPatch (const BYTE** buf)
{
  //## begin PatchAnswer::GetPatch%983336498.body preserve=yes
 	const BYTE* cursor = *buf;
	P_PATCH pId (&cursor);
	*buf = cursor;
	return (Patch*) IdentityAnswer::GetIdentity (pId);

  //## end PatchAnswer::GetPatch%983336498.body
}

//## Operation: PerformOperation%985819705
//	Public function by which all answers are derived.  The
//	member function index is the first byte in the question
//	parameter. After the index is obtained, the appropriate
//	member function is called.
unsigned PatchAnswer::PerformOperation (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::PerformOperation%985819705.body preserve=yes
	unsigned ret_bytes = 0;

	// deal with the question
	const BYTE* q_cursor = question;
  
	unsigned func_index = (unsigned)SMUtility::BufToTargetFunc (&q_cursor);

  
	if (func_index < eMaxFuncIndex)
		{
			ret_bytes += (pFunc[func_index]) (q_cursor, answer, answer_size);
		}
	return ret_bytes;

  //## end PatchAnswer::PerformOperation%985819705.body
}

//## Operation: GetOutletPortNumber%988078471; C++
//	Gets the Port number of the Outlet port
unsigned PatchAnswer::GetOutletPortNumber (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::GetOutletPortNumber%988078471.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	PatchOutletPort* pPort = (PatchOutletPort*)(BaseShellAnswer::GetBaseShell (&cursor));
	if (pPort)
		{
			unsigned num = pPort->GetOutletNumber ();
			SMUtility::IntToBuf ((short) num, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;

  //## end PatchAnswer::GetOutletPortNumber%988078471.body
}

//## Operation: GetInletPortNumber%988078472; C++
//	Gets the Port number of the Inlet port
unsigned PatchAnswer::GetInletPortNumber (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::GetInletPortNumber%988078472.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
	unsigned ret_bytes = 0;
	const BYTE* cursor = question;
	PatchInletPort* pPort = (PatchInletPort*)(BaseShellAnswer::GetBaseShell (&cursor));
	if (pPort)
		{
			unsigned num = pPort->GetInletNumber ();
			SMUtility::IntToBuf ((short) num, answer);
			ret_bytes = sizeof(short);
		}
	return ret_bytes;
  //## end PatchAnswer::GetInletPortNumber%988078472.body
}

//## Operation: NumberPatches%1020226579; C++
//	Returns the P_BASESHELL of the Object that is the Inlet
//	of the Patch, the Inlet specified as the inlet_num
//	parameter
unsigned PatchAnswer::NumberPatches (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::NumberPatches%1020226579.body preserve=yes
	if (answer_size < sizeof (short))
		{
			return 0;
		}
  unsigned num = Patch::NumPatches ();
	SMUtility::IntToBuf ((short) num, answer);

  return sizeof(short);
  
  //## end PatchAnswer::NumberPatches%1020226579.body
}

//## Operation: GetPatch%1020226580; C++
//	Returns the P_BASESHELL of the Object that is the Outlet
//	of the Patch, the Outlet specified as the outlet_num
//	parameter
unsigned PatchAnswer::GetPatch (const BYTE* question, BYTE* answer, unsigned answer_size)
{
  //## begin PatchAnswer::GetPatch%1020226580.body preserve=yes
	if (answer_size < sizeof (P_PATCH))
		{
			return 0;
		}

	const BYTE* cursor = question;
  unsigned index = SMUtility::BufToInt(&cursor);

  Patch* pPatch = Patch::GetPatch (index);
  P_PATCH dwpPatch (pPatch);
	dwpPatch.toBuf(answer);
  
	return sizeof (P_PATCH);
  //## end PatchAnswer::GetPatch%1020226580.body
}

// Additional Declarations
  //## begin PatchAnswer%3A99D2AC01DF.declarations preserve=yes
  //## end PatchAnswer%3A99D2AC01DF.declarations

// Class PatchDeleter 



PatchDeleter::PatchDeleter()
  //## begin PatchDeleter::PatchDeleter%.hasinit preserve=no
  //## end PatchDeleter::PatchDeleter%.hasinit
  //## begin PatchDeleter::PatchDeleter%.initialization preserve=yes
  //## end PatchDeleter::PatchDeleter%.initialization
{
  //## begin PatchDeleter::PatchDeleter%.body preserve=yes
  //## end PatchDeleter::PatchDeleter%.body
}


PatchDeleter::~PatchDeleter()
{
  //## begin PatchDeleter::~PatchDeleter%.body preserve=yes
  //## end PatchDeleter::~PatchDeleter%.body
}



//## Other Operations (implementation)
//## Operation: Send%983336474
//	Sends a request message to the Scheduler. Returns true
//	if request was successful
bool PatchDeleter::Send (Patch* receiver)
{
  //## begin PatchDeleter::Send%983336474.body preserve=yes
  bool ret = false;

  if (hal_include::Scheduler::LockEngine ())
  {
    ret = GoOneShot ((DWORD)receiver);
    hal_include::Scheduler::UnlockEngine ();
  }
  return ret;

  //## end PatchDeleter::Send%983336474.body
}

//## Operation: OutputFunction%983336475; C++
void PatchDeleter::OutputFunction (DWORD receiver)
{
  Patch* pPatch = (Patch*)receiver;
	if (pPatch)
		{
			delete pPatch;
		}
	else
		{
			pPatch = Patch::GetPatch (0);
			if (pPatch)
				{
					delete pPatch;
				}
		}
  //## begin PatchDeleter::OutputFunction%983336475.body preserve=yes
  //## end PatchDeleter::OutputFunction%983336475.body
}

// Additional Declarations
  //## begin PatchDeleter%3A99EB1401F7.declarations preserve=yes
  //## end PatchDeleter%3A99EB1401F7.declarations

//## begin module%3A9C920B0193.epilog preserve=yes
//## end module%3A9C920B0193.epilog
