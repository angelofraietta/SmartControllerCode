#include <stdio.h>
#include <CoreFoundation/CFRunLoop.h>
#include "stdafx.h"
#include "../engineinterface/presentationquestion.h"
#include "../engineinterface/patchquestion.h"


extern "C"
{
    bool SimulatorInitialise();
	void  InitialiseEngine();
	void  DeinitialiseEngine();
}

int main()
{
    char buff [256];
    
    printf ("Start Simulator");

	SimulatorInitialise();
        InitialisePresentation();

	unsigned p_key = GetSelectedEngine();
        
        PresentationQuestion* p = getPresentation(p_key);
        
	P_PATCH p_val = PatchQuestion::MakeNew(p, "dummy.smp");

        printf ("P VAL %u\r\n", p_val.Key());
        
        PatchQuestion::SetFileName(p, p_val, "testsim.smp");
        PatchQuestion::GetFileName(p, p_val, buff, sizeof(buff));
        
        printf ("P VAL and name %u %s\r\n", p_val.Key(), buff);
	//cout<<"Press c to exit..."<<endl;

	char c;
	//cin>>c;
	while (c != 'c' && c != 'C')
		{
			//cin>>c;
		}

		return 0;
}
