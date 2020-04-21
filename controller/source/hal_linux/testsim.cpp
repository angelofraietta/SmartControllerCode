#include <stdio.h>
#include "stdafx.h"
#include "../engineinterface/presentationquestion.h"
#include "../engineinterface/patchquestion.h"
#include "answertask.h"
#include "udpport.h"

#define ECHO_PORT_NUM  1113

#define MAX_LEN 32


static const char* probe_question = "Who Are You";

extern "C"
{
    bool SimulatorInitialise();
	void  InitialiseEngine();
	void  DeinitialiseEngine();
}

void probeFunction()
{
        char buf[128];
        int port;
    
    
    UDPPort* udpport = new UDPPort();
    
    if (udpport->OpenPort(ECHO_PORT_NUM))
    {
        
        printf ("Opened probe port\r\n");
        
        unsigned long len = udpport->ReadBuffer((unsigned char *) buf, sizeof(buf));
        
        printf ("Read %d chars %s\r\n", len, buf);
        
        if (!strcmp(probe_question, buf))
        {
            printf("Valid Probe \r\n");
        }
        udpport->Close();
    }
        /*
        memset (&es, 0, sizeof es);
        es.sin_len         = sizeof (es);
        es.sin_family      = AF_INET;
        es.sin_port        = htons(ECHO_PORT_NUM);
        

        
        
        FILE* f_name = fopen(id_file, "r");
        if (f_name)
        {
            char buf [128];
            int num_fields = fscanf (f_name, "%s%u", buf, &port);
            
            if (num_fields < 1)
            {
                strcpy(buf, "Error In Name");
            }
            
            strcat(name_buf, buf);
            
            if (num_fields > 1)
            {
                printf("Port Found :%u\r\n", port);
                answer_port = port;
            }
            
            fclose(f_name);
        }
        else
        {
            strcat(name_buf, "Annon");
        }
        
        sprintf (buf, "%s %u", name_buf, answer_port);
        
        strcpy(name_buf, buf);
        
        printf ("Start Reader Task %s on Port %u\n", name_buf, ECHO_PORT_NUM);
        
        StartUPDTask (answer_port);
        */
    /*
        while (1)
        {
            struct sockaddr_in from;
            int flen = sizeof (from);
            int r;
            
            if (fd == -1)
            {
                rtems_task_wake_after(5000);
                continue;
            }
            
            memset (buf, 0, sizeof (buf));
            printf ("Wait Read Task\r\n");
            r = recvfrom (fd, buf, sizeof (buf), 0, (struct sockaddr*) &from, &flen);
            
            if (r < 0)
            {
                printf ("udp-echo: error reading from udp socket: (%d) %s\n",
                        errno, strerror (errno));
                continue;
            }
            
            printf ("udp-echo:%s: %d: %s\n", inet_ntoa (from.sin_addr), r, buf);
            
            // see if they have asked the correct question
            if (!strcmp(probe_question, buf))
            {
                es.sin_addr = from.sin_addr;
                
                if (sendto (fd, name_buf, strlen(name_buf), 0,
                            (const struct sockaddr*) &es, sizeof es) < 0)
                printf ("udp-echo: error writing to the udp socket: (%d) %s\n",
                        errno, strerror (errno));
                
                sprintf (buf, "Rtems Version %s %s", myuname.release, __DATE__);
                if (sendto (fd, buf, strlen(buf), 0,
                            (const struct sockaddr*) &es, sizeof es) < 0)
                printf ("udp-echo: error writing to the udp socket: (%d) %s\n",
                        errno, strerror (errno));
                
                // send how much free space
                DisplayFreeMemory();
                ListDirFiles(GetDefaultPatchPath());
                
                // list patches
                ListLoadedPatches();
                
            }
            else if (!strcmp(memory_question, buf))
            {
                es.sin_addr = from.sin_addr;
                DisplayFreeMemory();
                
            }
            else  if (!strcmp(file_list, buf))
            {
                es.sin_addr = from.sin_addr;
                ListDirFiles(GetDefaultPatchPath());
                
            }
            
            else  if (!strcmp(reboot_command, buf))
            {
                es.sin_addr = from.sin_addr;
                
                sprintf (buf, "Rebooting %s", name_buf);
                
                if (sendto (fd, buf, strlen(buf), 0,
                            (const struct sockaddr*) &es, sizeof es) < 0)
                printf ("udp-echo: error writing to the udp socket: (%d) %s\n",
                        errno, strerror (errno));
                
                SendIOReboot();
                rtems_task_wake_after (100);
                rtemsReboot();
            }
            else  if (!strcmp(list_patch_command, buf))
            {
                es.sin_addr = from.sin_addr;
                ListLoadedPatches();
                
            }
            
            
            
        }
        
    */
}


int main()
{
    char buff [256];
    
    printf ("Start Simulator\n");

	SimulatorInitialise();
        InitialisePresentation();


    //probeFunction();
    
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
