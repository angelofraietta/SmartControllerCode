#include <stdio.h>
#include <CoreFoundation/CFRunLoop.h>
#include "stdafx.h"
#include "../engineinterface/presentationquestion.h"
#include "../engineinterface/patchquestion.h"


extern "C"
{
	void  InitialiseEngine();
	void  DeinitialiseEngine();
}

int main()
{

	InitialiseEngine();

	PresentationQuestion* p = GetSelectedEngine();
	PatchQuestion::LoadPatchFile(p, "dummy.smp", (Patch*)0);

	//cout<<"Press c to exit..."<<endl;

	char c;
	//cin>>c;
	while (c != 'c' && c != 'C')
		{
			//cin>>c;
		}

		return 0;
}
