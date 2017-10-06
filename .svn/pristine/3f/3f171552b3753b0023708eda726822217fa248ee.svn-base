//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TypeElementUnit.h"
#include "TypeNames.h"
#include "ObjectBox.h"

//include headers for creating edit forms
#include "BaseShellsUnit.h"
#include "EditPatchUnit.h"
//Include headers for Object boxes
#include "VariableSizeBox.h"
#include "togglebox.h"
#include "NumberBox.h"

#include "help.h"
//---------------------------------------------------------------------------
TTypeElement::TTypeElement(String Type, int Help, pfnCreateForm CreateFunction, pfnCreateObject ObjectBoxFunction )
	 :TypeName(Type), pfnCreate(CreateFunction), pfnCreateObjectBox(ObjectBoxFunction),
    HelpContext (Help)
{
}

TTypeElement& TTypeElement::operator =(const TTypeElement& x)
{
    TypeName = x.TypeName;
    pfnCreate = x.pfnCreate;
    pfnCreateObjectBox = x.pfnCreateObjectBox;
    return *this;
}
//---------------------------------------------------------------------------

unsigned TTypeElementList::NumElements()
{
    return Elements.size();
}


TTypeElementListType TTypeElementList::Elements = LoadElementTypes();

CreateFormMapType TTypeElementList::EditFormMap = CreateFormMap();

CreateObjectMapType TTypeElementList::ObjectBoxMap = CreateObjectBoxMap();

CreateHelpMapType TTypeElementList::HelpMap = CreateHelpMap();


String TTypeElementList::GetType(unsigned Index)
{
    if(Index >= Elements.size())
        throw (String("Invalid Type Element"));
    return Elements[Index].TypeName;
}

pfnCreateObject TTypeElementList::GetCreateObjectBox(String Key)
{
   if(ObjectBoxMap.count(Key)) //is in map
      return ObjectBoxMap[Key];
   else
      return NULL;
}

pfnCreateForm TTypeElementList::GetCreateForm(String Key)
{
   if(EditFormMap.count(Key)) //is in map
      return EditFormMap[Key];
   else
      return NULL;
}

int TTypeElementList::HelpContext(String Key)
{
   if(HelpMap.count(Key)) //is in map
      return HelpMap[Key];
   else
      return 0;
}

//------------------------------------------------------------------------------

TTypeElementListType LoadElementTypes()
{
    TTypeElementListType TheList;
   //push all types onto the list;
   //add new types here

    TheList.push_back(TTypeElement(AnsiString(PATCH_TYPE), HID_PATCH, NULL, TVariableSizeBox::Create));

    TheList.push_back(TTypeElement(AnsiString(INLETPORT_TYPE), HID_PATCH_PORT));

    TheList.push_back(TTypeElement(AnsiString(OUTLETPORT_TYPE), HID_PATCH_PORT));

    TheList.push_back(TTypeElement(AnsiString(ANALOGUE_IN_TYPE), HID_PATCH));

    TheList.push_back(TTypeElement(AnsiString(ANALOGUE_OUT_TYPE), HID_PATCH));

    TheList.push_back(TTypeElement(AnsiString(CALCULATE_TYPE), HID_CALCULATE));

    TheList.push_back(TTypeElement(AnsiString(COUNTER_TYPE), HID_COUNTER));

    TheList.push_back(TTypeElement(AnsiString(DELAY_TYPE), HID_DELAY));

    TheList.push_back(TTypeElement(AnsiString(DIGITAL_IN_TYPE), HID_PATCH));

    TheList.push_back(TTypeElement(AnsiString(DIGITAL_OUT_TYPE), HID_PATCH));

    TheList.push_back(TTypeElement(AnsiString(DISPLAY_TYPE), HID_DISPLAY));

    TheList.push_back(TTypeElement(AnsiString(FLIPFLOP_TYPE), HID_FLIP_FLOP));

    TheList.push_back(TTypeElement(AnsiString(SWITCH_INLETS_TYPE), HID_INLETS_SWITCH,  NULL, TVariableSizeBox::Create));

    TheList.push_back(TTypeElement(AnsiString(MESSAGESTORE_TYPE), HID_MESSAGE_STORE));

    TheList.push_back(TTypeElement(AnsiString(METRO_TYPE), HID_METRO));

    TheList.push_back(TTypeElement(AnsiString(STDMIDIIN_TYPE), HID_MIDI_IN));

    TheList.push_back(TTypeElement(AnsiString(STDMIDIOUT_TYPE), HID_MIDI_OUT));

    TheList.push_back(TTypeElement(AnsiString(NUMBERSTORE_TYPE), HID_NUMBER_STORE, NULL, TNumberBox::Create));

    TheList.push_back(TTypeElement(AnsiString(SWITCH_OUTLETS_TYPE), HID_OUTLETS_SWITCH, NULL, TVariableSizeBox::Create));

    TheList.push_back(TTypeElement(AnsiString(RANDOMGEN_TYPE), HID_RANDOM_GENERATOR));

    TheList.push_back(TTypeElement(AnsiString(SELECTOR_TYPE), HID_SELECTOR));

    TheList.push_back(TTypeElement(AnsiString(SEQUENCER_TYPE), HID_SEQUENCER));

    TheList.push_back(TTypeElement(AnsiString(TABLE_TYPE), HID_TABLE));

    TheList.push_back(TTypeElement(AnsiString(TOGGLE_TYPE), HID_TOGGLE, NULL, TToggleBox::Create));

    TheList.push_back(TTypeElement(AnsiString(TRIGGER_TYPE), HID_TRIGGER));

 return TheList;
}


CreateFormMapType CreateFormMap()
{
    CreateFormMapType TheMap;//this will be returned

    for (unsigned i = 0; i < TTypeElementList::NumElements(); i++)
        {
        const TTypeElement Element = TTypeElementList::Elements[i];
        String Key = Element.TypeName;
        pfnCreateForm CreateFunction = Element.pfnCreate;
        //insert into the map
        TheMap.insert(CreateFormMapType::value_type(Key, CreateFunction));
        }
    return TheMap;
}

CreateObjectMapType CreateObjectBoxMap()
{
    CreateObjectMapType TheMap;//this will be returned

    for (unsigned i = 0; i < TTypeElementList::NumElements(); i++)
        {
        const TTypeElement Element = TTypeElementList::Elements[i];
        String Key = Element.TypeName;
        pfnCreateObject CreateFunction = Element.pfnCreateObjectBox;
        //insert into the map
        TheMap.insert(CreateObjectMapType::value_type(Key, CreateFunction));
        }
    return TheMap;
}

CreateHelpMapType CreateHelpMap()
{
    CreateHelpMapType TheMap;//this will be returned

    for (unsigned i = 0; i < TTypeElementList::NumElements(); i++)
        {
        const TTypeElement Element = TTypeElementList::Elements[i];
        String Key = Element.TypeName;
        int context = Element.HelpContext;
        //insert into the map
        TheMap.insert(CreateHelpMapType::value_type(Key, context));
        }
    return TheMap;
}


#pragma package(smart_init)
