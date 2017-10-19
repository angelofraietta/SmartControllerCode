#include "stdafx.h"
#include <stdlib.h>
#include "control.h"
#include "patch.h"
#include "patchview.h"   


const char*const PatchView::szType = "PatchView";
const char*const PatchView::StartBlock = "VIEW"; // Start Of Object Block
const char*const PatchView::ViewObject::StartBlock = "OB"; // Start Of Object Bloc
const char*const PatchView::ViewConnector::StartBlock = "CON"; // Start Of Connector

PatchView::~PatchView()
{
}


void PatchView::AddObject(BaseShell* pShell,
													unsigned top,
													unsigned left,
													unsigned height,
													unsigned width,
													unsigned tag)
{
	ViewObject obj(pShell, top, left, height, width, tag);
	object_list.push_back(obj);
}


void PatchView::ClearView()
{
	object_list.erase(object_list.begin(), object_list.end());

  for (unsigned i = 0; i < connector_list.size(); i++)
  {
    delete connector_list[i];
  }
  
  connector_list.erase(connector_list.begin(), connector_list.end());
}

bool PatchView::GetObjectParams(unsigned index,
																BaseShell** pShell, 
																unsigned* top, 
																unsigned* left,
																unsigned* height, 
																unsigned* width,
																unsigned* tag)
{
	bool ret = false;
	if (index < object_list.size())
		{
			*pShell = object_list[index]._pShell;
			*top = object_list[index]._top;
			*left = object_list[index]._left;
			*height = object_list[index]._height;
			*width = object_list[index]._width;
			*tag = object_list[index]._tag;
			ret = true;

		}
	return ret;

}

bool PatchView::ModifyObject(BaseShell* pBaseshell,
														 unsigned top,
														 unsigned left,
														 unsigned height,
														 unsigned width,
														 unsigned tag)
{
	bool ret = false;
  unsigned index = GetObjectIndex (pBaseshell);

	if (index < object_list.size())
		{
     object_list[index]._top = top;
      object_list[index]._left = left;
      object_list[index]._height = height;
      object_list[index]._width = width;
      object_list[index]._tag = tag;
      ret = true;
		}

	return ret;
}
			
bool PatchView::RemoveObject(BaseShell* pShell)
{
  unsigned index = GetObjectIndex(pShell);
  bool ret = false;

  if (pShell == object_list[index]._pShell)
  {
    object_list.erase(&(object_list[index]));
    ret = true;
  }

  return ret;
}

// will return a value greater than the number of items if failed
unsigned PatchView::GetObjectIndex (BaseShell* pShell)
{
	unsigned i = 0;
	bool found = false;

	while (!found && i < object_list.size())
		{
			if (pShell == object_list[i]._pShell)
				{
					found = true;
				}
			else
				{
					i++;
				}
		}
	return i;
}

// will return a value greater than the number of items if failed
unsigned PatchView::GetConnectorIndex (Connector* pCon)
{
	unsigned i = 0;
	bool found = false;

	while (!found && i < connector_list.size())
		{
			if (pCon == connector_list[i]->_pCon)
				{
					found = true;
				}
			else
				{
					i++;
				}
		}
	return i;
}


int PatchView::AddConnector(Connector* pCon)
{
  int ret = connector_list.size();
  connector_list.push_back (new ViewConnector (pCon));
  return ret;
}

Connector* PatchView::GetConnector (unsigned index)
{
  Connector* ret = NULL;

  if (index < connector_list.size())
  {
    ret = connector_list[index]->_pCon;
  }
  return ret;
}

int PatchView::GetConnectorValue (unsigned index, unsigned value_num)
{
  int ret = 0;
  if (index < connector_list.size())
  {
    if (value_num < connector_list[index]->GetNumValues())
    {
      ret = connector_list[index]->GetValue (value_num);
    }
  }
  return ret;
}

bool PatchView::AddConnectorValue (unsigned index, int value)
{
  bool ret = false;
  if (index < connector_list.size())
  {
    connector_list[index]->AddValue (value);
    ret = true;
  }
  return ret;
}

unsigned PatchView::GetNumConnectorValues (unsigned index)
{
  int ret = 0;
  if (index < connector_list.size())
  {
    ret = connector_list[index]->GetNumValues();
  }
  return ret;
}

void PatchView::Save(FILE* outfile)
{
  //save Identity
  fprintf (outfile, "%s %s\r\n", StartBlock, GetType());

  SaveID(outfile);
	// now save object list

  for (unsigned i = 0; i < object_list.size(); i++)
  {
		object_list[i].Save(outfile);
  }

  // Now Save Connector List
  for (unsigned i = 0; i < connector_list.size(); i++)
  {
		connector_list[i]->Save(outfile);
  }


  // now store end block
  fprintf(outfile, "%s\r\n", EndBlock);
}
bool PatchView::Restore(FILE* infile)
{
	bool complete = false;
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
  	else if (!strcmp (cursor, ViewObject::StartBlock))
    {
    	ViewObject vObj;
			cursor =  cursor + strlen (cursor) + 1;
			vObj.Restore(GetParent(), cursor);
      object_list.push_back(vObj);
    }
  	else if (!strcmp (cursor, ViewConnector::StartBlock))
    {
    	ViewConnector *vCon = new ViewConnector;
			cursor =  cursor + strlen (cursor) + 1;
			vCon->Restore(GetParent(), cursor);
      connector_list.push_back(vCon);
    }

    else if  (!strcmp (cursor, EndBlock))
    {
    	complete = true;
    }
    else
    {
    	// just read the line
    }

    if (!complete)
    {
      complete = !Readline (infile, RestoreInputBuffer, RestoreInputBufferSize);
    }

  } while (!complete);

  // restore attributes
  return true;
}


void PatchView::ViewObject::Save(FILE* outfile)
{
	if (_pShell)
		{
			unsigned object_index = _pShell->PatchPosition();
			fprintf (outfile, "%s %u %u %u %u %u %u \r\n", 
							 StartBlock, object_index, _top, _left, _height, _width, _tag);
		}
}

void PatchView::ViewConnector::Save(FILE* outfile)
{
	if (_pCon)
		{
      BaseShell* outlet_base = _pCon->GetOutletBase ();

      if (outlet_base)
      {
			  unsigned object_index = outlet_base->PatchPosition();
        unsigned num_values = GetNumValues();
        unsigned outlet_number = _pCon->GetOutletNum();
        unsigned connector_index = outlet_base->FindOutletConnectorIndex (outlet_number, _pCon);

        // first write Header and Connection details
			  fprintf (outfile, "%s %u %u %u %u",
							 StartBlock, object_index, outlet_number, connector_index, num_values);

        // now write all the values
        for (unsigned i = 0; i < num_values; i++)
        {
          fprintf (outfile, " %d", GetValue (i));
        }

        // now write end of line
        fprintf (outfile, "\r\n");
      }
		}
}

bool PatchView::ViewObject::Restore(Patch* parent, char* input_buffer)
{
	char* cursor;
	cursor = input_buffer;
	unsigned object_index;
	object_index = atoi(cursor);
	Identity::Tokenize(&cursor);

	_pShell = parent->FindObject (object_index);
	// move to each value
	cursor =  cursor + strlen (cursor) + 1;
	_top = atoi(cursor);
	Identity::Tokenize(&cursor);

	cursor =  cursor + strlen (cursor) + 1;
	_left = atoi(cursor);
	Identity::Tokenize(&cursor);

	cursor =  cursor + strlen (cursor) + 1;
	_height = atoi(cursor);
	Identity::Tokenize(&cursor);

	cursor =  cursor + strlen (cursor) + 1;
	_width = atoi(cursor);
	Identity::Tokenize(&cursor);

	cursor =  cursor + strlen (cursor) + 1;
	_tag = atoi(cursor);

  return true;
}

bool PatchView::ViewConnector::Restore(Patch* parent, char* input_buffer)
{
	char* cursor;
	cursor = input_buffer;
	unsigned object_index;
  BaseShell* pShell;
  bool ret = false;

	object_index = atoi(cursor);
	Identity::Tokenize(&cursor);

	pShell = parent->FindObject (object_index);
  if (pShell)
  {
    unsigned outlet_number;
    unsigned connector_index;


    // now find outlet number
    // move to each value
    cursor =  cursor + strlen (cursor) + 1;
    outlet_number = atoi(cursor);
    Identity::Tokenize(&cursor);

    // get the Connector Index
    cursor =  cursor + strlen (cursor) + 1;
    connector_index = atoi(cursor);
    Identity::Tokenize(&cursor);

    // Get The Connector
    _pCon = pShell->GetOutletConnector (outlet_number, connector_index);

    if (_pCon)
    {
      // read how many parameters to expect
      unsigned num_values;

      cursor =  cursor + strlen (cursor) + 1;
      num_values = (unsigned) atoi(cursor);
      Identity::Tokenize(&cursor);

      // now read the values and store
      for (unsigned i = 0; i < num_values; i++)
      {
        cursor =  cursor + strlen (cursor) + 1;
        int value = atoi(cursor);
        Identity::Tokenize(&cursor);

        AddValue (value);
      }

      ret = true;
    }

  }

  return ret;;
}
