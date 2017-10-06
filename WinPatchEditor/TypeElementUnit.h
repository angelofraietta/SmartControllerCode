//---------------------------------------------------------------------------
#ifndef TypeElementUnitH
#define TypeElementUnitH

#include "interfacebridge.h"
#include "Typenames.h"
#include <Forms.hpp>
#include <map>
#include <string>
#include <vector>

class TBaseShellHook;
class TObjectBox;
class TViewForm;
//---------------------------------------------------------------------------

//define type of function that creates forms
typedef TForm* (*pfnCreateForm)(TBaseShellHook*);
//define a map to create them
typedef std::map<AnsiString,
                pfnCreateForm,
                std::less<AnsiString> > CreateFormMapType;

//declare function for creating a map of functions to create EditForms
CreateFormMapType CreateFormMap(); //declare function


//declare function for creating type dependent of object box
typedef TObjectBox* (*pfnCreateObject)(TBaseShellHook*, TViewForm*);

//declare a map for creating ObjectBoxes
typedef std::map<AnsiString,
                pfnCreateObject,
                std::less<AnsiString> > CreateObjectMapType;

//declare function for creating a map of functions to create ObjectBoxes
CreateObjectMapType CreateObjectBoxMap();

typedef std::map<AnsiString,
                int,
                std::less<AnsiString> > CreateHelpMapType;

CreateHelpMapType CreateHelpMap();

class TTypeElement
{
public:
    TTypeElement(String, int Help = 0, pfnCreateForm = NULL, pfnCreateObject = NULL);
    String TypeName;
    pfnCreateForm pfnCreate;
    pfnCreateObject pfnCreateObjectBox;
    TTypeElement& operator =(const TTypeElement&);
    const int HelpContext;
};

typedef std::vector<TTypeElement> TTypeElementListType;

TTypeElementListType LoadElementTypes();

class TTypeElementList:public TComponent
{
//allow access by these functions
friend TTypeElementListType LoadElementTypes();
friend CreateFormMapType CreateFormMap();
friend CreateObjectMapType CreateObjectBoxMap();
friend CreateHelpMapType CreateHelpMap();
public:
    static unsigned NumElements();
    static String GetType(unsigned Index);
    static pfnCreateForm GetCreateForm(String);
    static pfnCreateObject GetCreateObjectBox(String);
    static int HelpContext (String object_type);
private:
    static TTypeElementListType Elements;
    static CreateFormMapType EditFormMap;
    static CreateObjectMapType ObjectBoxMap;
    static CreateHelpMapType HelpMap;
};


#endif
