//function definitions for Patch class
#include "stdafx.h"

#include "control.h"
#include "patch.h"
#include "typelist.h"
#include "typenames.h"
#include <algorithm>
#include <stack>
#include <list>
#include <stdlib.h>
#include "fileanswer.h"
#include "patchview.h"
#include "iodata.h"
#include "midioutputdriver.h"
#include "midiflags.h"

//#define SHOW_LOAD_DEBUG

static const char* PORT_IN = "PORTIN";
static const char* PORT_OUT = "PORTOUT";

static const char* szFileVersionPrefix = FILE_VERSION_PREFIX;
static const char* szEndViewId = END_VIEW_ID;
volatile bool Patch::_load_error = false;
volatile unsigned Patch::_patch_load_depth = 0;
unsigned Patch::_max_patch_load_depth = (unsigned)-1;

const unsigned Patch::NumAccess = Patch::eFilename + 1;

ArrayOfPatches Patch::pPatchList;

extern "C" void SetMaxPatchViewDepth (unsigned new_depth)
{
  Patch::_max_patch_load_depth = new_depth;
}

extern "C" unsigned GetMaxPatchViewDepth()
{
  return Patch::_max_patch_load_depth;
}
//**********************************************************************
// PatchInletPort function defs

//********************************************************************
const char*const Patch::szType = PATCH_TYPE;
#ifdef USE_SHORT_NAMES
//long filenames must be converted to short
DWORD GetShortPathName(
											 const char* lpszLongPath,	// points to a null-terminated path string
											 char* lpszShortPath,	// points to a buffer to receive the null-terminated short form of the path
											 DWORD cchBuffer 	// specifies the size of the buffer pointed to by lpszShortPath
											 );
#endif
Patch::Patch(Patch* Parent, unsigned NumInlets, unsigned NumOutlets,
						 const char* Name, const char* Comment, const char* FileName)
  :BaseShell(Parent, NumInlets, NumOutlets,
	     Name, Comment),  sFileName(FileName) {}
Patch::Patch( const char* Name)
  :BaseShell(NULL, 0, 0,
	     Name, ""),  sFileName("") {}


Patch::~Patch()
{

	RemovePatch (this);
  
  Reset();
  //delete all objects in both list
  unsigned Size = ObjectList.size();
  for(unsigned i = 0; i < Size; i++)
    delete ObjectList[i];
  
  Size = ConnectorList.size();
  for (unsigned i = 0; i < Size; i++)
    delete ConnectorList[i];
}


BaseShell* Patch::Create(Patch* Parent)
{
  Patch* ret = new Patch(Parent, 0,0, "", "", "");
  
  printf ("Patch::Create %lu\r\n", ret);
  if (!Parent)
  {
    AddPatch(ret);
  }
  
  return ret;
}



void Patch::Reset()
{
  int Size = ObjectList.size();
  for (int i = 0; i < Size; i++)
    ObjectList[i]->Reset();
}

BaseShell* Patch::AddInletPort(Patch* ParentPatch)
{
  return ParentPatch->AddInlet();
}


BaseShell* Patch::AddInlet()
{
  PatchInletPort* pNewInletPort = PatchInletPort::Create(this);
  if (!pNewInletPort)
    throw "Out of Memory";
  
  //Add To List of InletPorts
  ptInletPort.push_back(pNewInletPort);
  
  //add to Patch Form
  BaseShell::AddInlet();
  pNewInletPort->SetInletNumber(ptInletPort.size()-1);
  return pNewInletPort;
}

BaseShell* Patch::AddOutletPort(Patch* ParentPatch)
{
  return ParentPatch->AddOutlet();
}

BaseShell* Patch::AddOutlet()
{
  PatchOutletPort* pNewOutletPort = PatchOutletPort::Create(this);
  if(!pNewOutletPort)
    throw "Out of Memory";
  
  //Add To List of OutletPorts
  ptOutletPort.push_back(pNewOutletPort);
  // give  OutletPort the OutletNumber
  pNewOutletPort->SetOutletNumber(ptOutletPort.size()-1);
  
  
  BaseShell::AddOutlet();
  
  //set modified flag
  SetModified(true);
  
  return pNewOutletPort;
}

void Patch::RemoveInlet(PatchInletPort* pOldInlet)
{
  BaseShell::RemoveInlet();
  
  bool Found = false;
  for(unsigned i = 0; !Found && i < ptInletPort.size(); i++)
    {
      if (ptInletPort[i] == pOldInlet)
				{
					ptInletPort.erase(&(ptInletPort[i]));
					Found = true;
				}
    }
  
  //set modified flag
  SetModified(true);
  
  //  if(iter != ptInletPort.end()) //has been found
  //     ptInletPort.erase(iter);
}


void Patch::RemoveOutlet(PatchOutletPort* pOldOutlet)
{
  BaseShell::RemoveOutlet();
  //remove reference to InletPort
  //std::vector <PatchOutletPort*>::iterator iter;
  /*   iter = std::find(ptOutletPort.begin(), ptOutletPort.end(), pOldOutlet);
			 
       if(iter != ptOutletPort.end()) //has been found
       ptOutletPort.erase(iter);
  */
  bool Found = false;
  volatile unsigned size = ptOutletPort.size();

  for(unsigned i = 0; !Found && i < size; i++)
    {
      if (ptOutletPort[i] == pOldOutlet)
				{
					ptOutletPort.erase(&(ptOutletPort[i]));
					Found = true;
				}
    }
  //re-number remaining outlets
	size = ptOutletPort.size();
  for(unsigned i = 0; i < size; i++)
    {
			ptOutletPort[i]-> SetOutletNumber(i);
    }
	/*
		for(iter = ptOutletPort.begin();
		iter !=ptOutletPort.end(); ++iter);
		(*iter)->SetOutletNumber(i++);
		//set modified flag
  */
  SetModified(true);
  
}

const char* Patch::GetInletName(unsigned InletNumber)const
{
  if (InletNumber < GetNumInlets())
  {
    const PatchInletPort* port = ptInletPort[InletNumber]; 
    return port->GetName();
  }
  else
    return NULL;
}

const char* Patch::GetOutletName(unsigned OutletNumber)const
{
  if (OutletNumber < GetNumOutlets())
    return ptOutletPort[OutletNumber]->GetName();
  else
    return NULL;
}

void Patch::VoidInlet (unsigned InletNumber)
{
  if (InletNumber < GetNumInlets())
    ptInletPort[InletNumber]->Input();
}

void Patch::IntInlet (unsigned InletNumber, int i)
{
  if (InletNumber < GetNumInlets())
    ptInletPort[InletNumber]->Input(i);
}

void Patch::DoubleInlet (unsigned InletNumber, double d)
{
  if (InletNumber < GetNumInlets())
    ptInletPort[InletNumber]->Input(d);
}

void Patch::StringInlet (unsigned InletNumber, const char* s)
{
  if (InletNumber == 0)
    Reset();
  if (InletNumber < GetNumInlets())
    ptInletPort[InletNumber]->Input(s);
}

void Patch::ProduceOutput (unsigned OutletNumber)
{
  if (OutletNumber < GetNumOutlets())
    (tpOutlet[OutletNumber])->ProduceOutput();
}

void Patch::ProduceOutput (unsigned OutletNumber, int i)
{
  if (OutletNumber < GetNumOutlets())
    (tpOutlet[OutletNumber])->ProduceOutput(i);
}

void Patch::ProduceOutput (unsigned OutletNumber, double d)
{
  if (OutletNumber < GetNumOutlets())
    tpOutlet[OutletNumber]->ProduceOutput(d);
}

void Patch::ProduceOutput (unsigned OutletNumber, const char* s)
{
  if (OutletNumber < GetNumOutlets())
    tpOutlet[OutletNumber]->ProduceOutput(s);
}

BaseShell* Patch::FindObject(unsigned Index)
{
  if (Index < ObjectList.size())
    return ObjectList[Index];
  
  return NULL;
}

Connector* Patch::FindConnector(unsigned Index)
{
  if (Index < ConnectorList.size())
    return ConnectorList[Index];
  
  return NULL;
}

bool Patch::Detach(BaseShell* Item)
{
  bool Success = false;
  if (Item)
    {
      // test for equality
      bool Found = false;
      for(unsigned i = 0; !Found && i < ObjectList.size(); i++)
				{
					if (ObjectList[i] == Item)
						{
							BaseShell* pObject = ObjectList[i];
							delete pObject;
							ObjectList.erase(&(ObjectList[i]));
							Found = true;

              // now remove from all views
              for (unsigned j = 0; j < GetNumViews(); j++)
                {
                  ViewList[j]->RemoveObject(pObject);
                }

						}
				}


      //set modified flag
      SetModified(Success);
      
      return  Success;
    }
  else return false;
}

bool Patch::Detach(Connector* pCon, int Method)
{
  if (!pCon)
    return false;
  
  bool Success;
  
  //See if item exists in list
  // test for equality
  /*    std::vector <Connector*>::iterator iter;
				iter = std::find(ConnectorList.begin(), ConnectorList.end(), pCon);
				
				if(iter != ConnectorList.end()) //has been found
        {
        ConnectorList.erase(iter);
        DeadConnectorList.push_back(pCon);
        }
  */
  bool Found = false;
  for(unsigned i = 0; !Found && i < ConnectorList.size(); i++)
    {
      if (ConnectorList[i] == pCon)
				{
					
					ConnectorList.erase(&(ConnectorList[i]));
					DeadConnectorList.push_back(pCon);
					Found = true;
				}
    }
  
  if(!Found)
    return false;
  
  //set modified flag
  SetModified(true);
  
  
  
  if (Method == ByUserInterface)
    {
      Success = pCon->Disconnect(Connector::ByParent);
    }
  else // must be by connector
    return true;
  return Success;
  
}



bool Patch::Add(BaseShell* NewObject)
{
  ObjectList.push_back(NewObject);
  //set modified flag
	SetModified(true);


	return true;
}

bool Patch::Add(Connector* NewConnector)
{
  ConnectorList.push_back(NewConnector);
  //set modified flag
  SetModified(true);

  return true;
}



bool Patch::GetName (char* buf, unsigned buf_len)const
{
	bool ret = false;
	if (buf)
		{
			if (!(sFileName == string ("")) && pParent)
      {
				strncpy (buf, sFileName.c_str(), buf_len -1);
      }
      else
      {
				Identity::GetName (buf, buf_len);
      }

			buf[buf_len -1] = '\0';
			ret = true;
		}
	return ret;
}

void Patch::Save(FILE* OutFile)
{
  //save own details
  if (!(sFileName == string ("")) && pParent)
    {

      fprintf(OutFile, "%s %s \r\n", StartBlock, PATCH_FILE_ID);
      fprintf(OutFile, "%s %s\r\n", PATCH_FILE_ID, sFileName.c_str());
			fprintf(OutFile, "%s\r\n", EndBlock);
    }
	else
		{
			if (pParent)
				{
					fprintf (OutFile, "%s %s\r\n", StartBlock, GetType());
				}
			
			SaveID(OutFile);
			
			int Size = ObjectList.size();
			
			for (int i = 0; i < Size; i++)
				{
					BaseShell* pObject = ObjectList[i];
					pObject->Save(OutFile);
				}
			
			for (int i = 0; i < Size; i++)
				{
					ObjectList[i]->SaveConnectors (OutFile);
				}
			
			// Save Views
			for (unsigned i = 0; i < GetNumViews(); i++)
				{
					ViewList[i]->Save(OutFile);
				}
			
			//save port details
			if (GetNumInlets())
				{
					fprintf (OutFile, "%s ", PORT_IN);
					
					//save pointers to ports
					for (unsigned i = 0; i < GetNumInlets(); i++)
						fprintf (OutFile, "%u ",  ptInletPort[i]->PatchPosition());
					
					fprintf (OutFile, "\r\n");
				}
			
			if (GetNumOutlets())
				{
					fprintf (OutFile, "%s ", PORT_OUT);
					
					for (unsigned i = 0; i < GetNumOutlets(); i++)
						fprintf(OutFile, "%u ", ptOutletPort[i]->PatchPosition());
					
					fprintf(OutFile, "\r\n");
				}
			
			
			fprintf(OutFile, "%s\r\n", EndBlock);
			fflush(OutFile);
		}
}


//**********************************************************************
bool Patch::Restore(FILE* infile)
{

	bool complete = false;
  bool valid = false;
  bool eat_extra_endblock = false; // we set this true if we are skipping some sort of restore 

  _patch_load_depth++;
#ifdef SHOW_LOAD_DEBUG
	cout<<"Read Input Buffer"<<endl;
#endif

	Readline (infile, RestoreInputBuffer, RestoreInputBufferSize);
	// read all the different types of commands that it could be
  do
  {
  	char* cursor = RestoreInputBuffer;

		cursor = Tokenize (&cursor);
  	if (!strcmp (cursor, StartIdBlock))
    {
    	RestoreID(infile);
    }

    else if (!strcmp (cursor, PATCH_FILE_ID))
    {
      // we need to load patch from file
      cursor = cursor + strlen (cursor) +1;
      // cursor is now the new filename
      const char* FileName = Tokenize (&cursor);
      SetFileName(FileName);
      const char* default_dir = FileAnswer::GetDefaultDirName();

      char filepath [256];

      if (default_dir)
      {
        strcpy (filepath, default_dir);
      }
      else
      {
        filepath [0] = '\0';
      }

      strcat (filepath, FileName);

    	FILE* patchFile;

    	patchFile = fopen(filepath, "r");
      if (patchFile)
      	{
        Restore(patchFile);
      	fclose (patchFile);
        }


    }

    else if (!strcmp (cursor, BaseShell::StartBlock))
    {
#ifdef SHOW_LOAD_DEBUG
	cout<<"Restore BaseShell"<<endl;
#endif

    	// move past this to the object type;
      char* objtype =  cursor + strlen (cursor) + 1;
			objtype = Tokenize (&objtype);

      BaseShell* pShell = TypeList::Create (objtype, this);

      if (pShell)
      {
      	pShell->Restore (infile);
        Add (pShell);
      }
#ifdef SHOW_LOAD_DEBUG
			else
				{
					printf ("Unknown Object type %s\r\n", objtype);
				}
#endif
    }
    else if (!strcmp (cursor, Connector::StartBlock))
    {
#ifdef SHOW_LOAD_DEBUG
	cout<<"Restore Connector"<<endl;
#endif

      Connector* pCon = new Connector;
      if (pCon)
      {
      	if (pCon->Restore (infile, this))
					{
						Add (pCon);
#ifdef SHOW_LOAD_DEBUG
						cout<<"Connector added"<<endl;
#endif

					}
				else
					{
#ifdef SHOW_LOAD_DEBUG
						cout<<"Connector Killed"<<endl;
#endif

						delete pCon;
					}
      }
    }
    else if (!strcmp (cursor, PatchView::StartBlock))
    {
#ifdef SHOW_LOAD_DEBUG
			cout<<"Restore View"<<endl;
#endif

      if (_patch_load_depth <= _max_patch_load_depth)
      {
        PatchView* pView = new PatchView (this);

        if (pView)
        {
          pView->Restore (infile);
          ViewList.push_back(pView);
        }
      }
      else // we better eat up to the end block
      {
        eat_extra_endblock = true;
        printf ("Ignore this view\r\n");
      }

    }

    else if (!strcmp (cursor, PORT_IN))
    {
#ifdef SHOW_LOAD_DEBUG
	cout<<"Restore inlet ports"<<endl;
#endif

     	cursor = cursor + strlen (cursor) + 1;
      RestoreInletPorts (cursor);
    }

    else if (!strcmp (cursor, PORT_OUT))
    {
#ifdef SHOW_LOAD_DEBUG
	cout<<"Restore outlet ports"<<endl;
#endif

			cursor = cursor + strlen (cursor) + 1;
      RestoreOutletPorts (cursor);
    }
    else if  (!strcmp (cursor, EndBlock))
    {
      if (eat_extra_endblock)
      {
        eat_extra_endblock = false;
      }
      else{
    	  complete = true;
        valid = true;
      }

    }
    else
    {
    	// just read the line
			//cout<<"Unknown Patch Command: "<<cursor<<endl;
    }

    if (!complete)
    {
      complete = !Readline (infile, RestoreInputBuffer, RestoreInputBufferSize);
    }

  } while (!complete);

  Reset();
  _patch_load_depth--;
	return valid;
}

bool Patch::RestoreInletPorts(char* inbuf)
{
	bool ret = false;
  inbuf = Tokenize (&inbuf);
  unsigned i = 0; // this is the actual port number as it exists in the mapped ports

  while (*inbuf != '\0')
  {
   	unsigned index = atoi (inbuf);

    PatchInletPort* pShell = (PatchInletPort*) FindObject(index);
    unsigned inlet_number = pShell->GetInletNumber();

    if (inlet_number != i)
    {
    	SwapInlets(inlet_number, i);
    }

    i++;
    inbuf = inbuf + strlen (inbuf) +1;
   	inbuf = Tokenize (&inbuf);
  }

  return ret;
}

bool Patch::RestoreOutletPorts(char* inbuf)
{
	bool ret = false;
  inbuf = Tokenize (&inbuf);
  unsigned i = 0; // this is the actual port number as it exists in the mapped ports

  while (*inbuf != '\0')
  {
   	unsigned index = atoi (inbuf);

    PatchOutletPort* pShell = (PatchOutletPort*) FindObject(index);

    unsigned outlet_number = pShell->GetOutletNumber();

    if (outlet_number != i)
    {
    	SwapOutlets(outlet_number, i);
    }

    i++;
    inbuf = inbuf + strlen (inbuf) +1;
   	inbuf = Tokenize (&inbuf);
  }

  return ret;
}

typedef sm_ptr::vector <BaseShell*> RestoreObjectListType;

Connector* RestoreConnector(const char**, RestoreObjectListType&, unsigned long*, Patch*);


BaseShell* Patch::LoadPatchFile(const char* FileName, Patch* Parent)
{
    const char* default_dir = FileAnswer::GetDefaultDirName();

  	char filepath [256];
		if (default_dir)
			{
		    strcpy (filepath, default_dir);
			}
      else
      {
        filepath [0] = '\0';
      }

    strcat (filepath, FileName);



  FILE* infile;

  if(Parent && Parent->HasFileAncestor(FileName))
    {
      Error(ePatchAncestorError, Parent, FileName);
      return NULL;
    }

  infile = fopen(filepath, "r");

  if (!infile)
    {
      Error(eUnableToOpenPatch, Parent, filepath);
      printf ("Patch* Patch::LoadPatchFile Unable to load Patch %s", filepath);
      return NULL;
    }

  Patch* new_patch = (Patch*)Patch::Create (Parent);

  bool success = new_patch->Restore(infile);
  // read the patch line
  fclose(infile);

  if (success)
  {
    new_patch->SetFileName(FileName);
    new_patch->SetModified(false);

    if (!Parent)
    {
      printf ("file %s has no parent \r\n", filepath);
      
      // Now make a backup of this
      char backup_path [1024];
      sprintf(backup_path, "%s.back", filepath);
      FILE* outfile = fopen(backup_path, "w");
      new_patch->Save(outfile);
      fclose(outfile);
    }
  }
  else
  {
    delete new_patch;
    new_patch = NULL;
  }

  return new_patch;

}


BaseShell* Patch::CreatePatchFile(Patch* Parent)
{
  Patch* pPatch = new Patch(Parent, 0,0, "", "", "");
  return pPatch;
}




unsigned Patch::FindPosition(const BaseShell* pObject)const
{
  //return the order within the patch of the object
  //if object does not exist, returns NULL
  for (unsigned i = 0; i < ObjectList.size(); i ++)
    {
      if (ObjectList[i] == pObject)
				return i;
    }
  return 0;
}

bool Patch::HasFileAncestor(const char* TestName)const
{
  //returns true if the filename is an ancestor
  //The same as this filename?
  if (!strcmp(sFileName.c_str(), TestName))
    return true;
  
  if (IsOrphan())
    return false;
  else  //see parent
    return pParent->HasFileAncestor(TestName);
}

Connector* Patch::GetDeadConnector()
{
  if (DeadConnectorList.empty())
    return NULL;
  
  Connector* pCon = DeadConnectorList.front();
  DeadConnectorList.pop_front();
  return pCon;
}

bool Patch::CanSave()const
{
  return ( !(pParent) || (sFileName == "" && pParent->CanSave()));
}

void Patch::SwapInlets(unsigned InletNumber1, unsigned InletNumber2)
{
  if(InletNumber1 < GetNumInlets() && InletNumber2 < GetNumInlets())
    {
      PatchInletPort* Temp = ptInletPort[InletNumber1];
      ptInletPort[InletNumber1] = ptInletPort[InletNumber2];
      ptInletPort[InletNumber2] = Temp;
      ptInletPort[InletNumber1]->SetInletNumber(InletNumber1);
      ptInletPort[InletNumber2]->SetInletNumber(InletNumber2);      
    }
}

void Patch::SwapOutlets(unsigned OutletNumber1, unsigned OutletNumber2)
{
  if(OutletNumber1 < GetNumOutlets() && OutletNumber2 < GetNumOutlets())
    {
      PatchOutletPort* Temp = ptOutletPort[OutletNumber1];
      ptOutletPort[OutletNumber1] = ptOutletPort[OutletNumber2];
      ptOutletPort[OutletNumber2] = Temp;
      ptOutletPort[OutletNumber1]->SetOutletNumber(OutletNumber1);
      ptOutletPort[OutletNumber2]->SetOutletNumber(OutletNumber2);      
    }
}

PatchInletPort* Patch::GetInlet(unsigned InletNum)
{
  if(InletNum < GetNumInlets())
    return ptInletPort[InletNum];
  else
    return NULL;
}


PatchOutletPort* Patch::GetOutlet(unsigned OutletNum)
{
  if(OutletNum < GetNumOutlets())
    return ptOutletPort[OutletNum];
  else
    return NULL;
}

int Patch::NumObjects()const {return ObjectList.size();}
int Patch::NumConnectors()const{return ConnectorList.size();}


bool Patch::GetFileName(char* buf, unsigned buf_len)const 
{
    printf ("Patch::GetFileName\r\n");
	bool ret = false;
	if (strlen (sFileName.c_str()) < buf_len)
		{
			strcpy (buf, sFileName.c_str());
			ret = true;
		}
	return ret;
}

bool Patch::SetFileName(const char* FileName)
{
  sFileName = FileName;
  return true;
}


const Patch::str_access Patch::aAccess[NumAccess] =
{
  {"NumberOfObjects", &Patch::NumObjects, NULL},
  {"NumberOfConnectors", &Patch::NumConnectors, NULL},
  {"IsOrphan", &Patch::IsOrphan, NULL},
	 {"Filename", &Patch::GetFileName, &Patch::SetFileName}
};


const char* Patch::GetAccessName (unsigned index)const
{
  const char* ret = NULL;

  if (index < NumAccess)
    {
      ret = aAccess[index].access_name;
    }
  return ret;
}

bool Patch::SetAttribute (unsigned index, const char* value)
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].set_func)
    {
      //(this->*tpIntSetAccessFunc[index])(value);
      ret = (this->*aAccess [index].set_func) (value);
    }

  return ret;
}

bool Patch::GetAttribute (unsigned index, char* ret_value, unsigned ret_size) const
{
  bool ret = false;

  if (index < NumAccess && aAccess [index].get_func)
    {
      ret = (this->*aAccess [index].get_func) (ret_value, ret_size);
    }

  return ret;
}


bool Patch:: NumObjects (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (NumObjects (), ret, ret_size);
}

bool Patch:: NumConnectors (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (NumConnectors (), ret, ret_size);
}

bool Patch:: IsOrphan (char* ret, unsigned ret_size) const
{
	return SMUtility::IntToStr (IsOrphan (), ret, ret_size);
}

void Patch::AddPatch (Patch* pPatch)
{
	pPatchList.push_back(pPatch);
	if (!_load_error)
		{
			IOData out_data = (IOData) ((IO_FLAGS * 0x100) | (IO_PATCH_LOADED));
			MidiOutputDriver::TransmitIoData (out_data);
		}
}

void Patch::RemovePatch (Patch* pPatch)
{
    bool found = false;
    printf ("Patch::RemovePatch \r\n");
    
    for (unsigned i = 0; i < pPatchList.size() && !found; i++)
    {
        // Get reference to data element in array
        Patch*& data = pPatchList[i];

        if (data == pPatch)
    	{
            pPatchList.erase(&data);
            found = true;

            if (!_load_error)
            {
                IOData out_data = (IOData) (IO_FLAGS * 0x100 | (IO_NO_PATCH));
                MidiOutputDriver::TransmitIoData (out_data);
           }
        }
    }
    if (!found)
    {
        printf ("Patch::RemovePatch - Patch not found\r\n");
    }
}

unsigned Patch::NumPatches()
{
	return pPatchList.size();
}

extern "C" unsigned GetNumberLoadedPatches()
{
  return Patch::NumPatches();
}

extern "C" unsigned GetLoadedPatchFilename(unsigned index, char* buf, unsigned buf_len)
{
  unsigned ret = 0;

  if (index <  GetNumberLoadedPatches())
  {
    Patch* p_patch =  Patch::GetPatch(index);

    if (p_patch)
    {
      if (p_patch->GetFileName(buf, buf_len))
      {
        ret = strlen(buf);
      }
    }
  }

  return ret;
}

Patch* Patch::GetPatch(unsigned index)
{

	Patch* ret = NULL;

	if (index < pPatchList.size())
	{
  	ret = pPatchList [index];
  }
  return ret;
}

PatchView* Patch::GetView(unsigned index)
{
	PatchView* ret = NULL;
	if (index < GetNumViews())
		{
			ret = ViewList[index];
		}
	return ret;
}

unsigned Patch::AddView()
{
	unsigned index = ViewList.size();
	PatchView* pView = new PatchView (this);
	ViewList.push_back(pView);

	return index;
}
