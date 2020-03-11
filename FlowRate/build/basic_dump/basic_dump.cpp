//#include <winsvc.h>
#include <WinSock2.h>
#include <windows.h>
#include "pcap.h"

#include <list>
#include <string>
#include <sstream>

using namespace std;

#include <curl/curl.h>
#include <Semaphore.h>
#include <Interface.h>
#include <ConfigManager.h>

#pragma comment(lib, "comsuppw.lib") 



int Init();



int main()
{
	Init();
}


int Init()
{

	pcap_if_t *alldevs;
	pcap_if_t *d;
	int inum;
	int i=0;
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	
	InterfaceManager IntMgr;



	/* Retrieve the device list */
	if(pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}
	
	/* Print the list */
	for(d=alldevs; d; d=d->next)
	{
		//if (d->addresses != NULL)
		//{
			//if (d->addresses->addr != NULL)
			//{
				printf("%d. %s", ++i, d->name);
				//printf(" (%s)", iptos(((struct sockaddr_in *)d->addresses->addr)->sin_addr.s_addr));

				if (d->description)
				{
					printf(" (%s)\n", d->description);
				}
				else
					printf(" (No description available)\n");

				
			//}
		//}
	}
	
	if(i==0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return -1;
	}
	
	printf("Enter the interface number (1-%d):",i);
	scanf("%d", &inum);
	
	if(inum < 1 || inum > i)
	{
		printf("\nInterface number out of range.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}
	

	
	/* Open the device */
	/* Open the adapter */


	HANDLE  InterfaceThread;	//may need to be destroyed after use (this may need to be a structure)
	DWORD   dwThreadId = 0;
	int cnt = 1;

	for (d = alldevs; d; d = d->next)
	{
		
		if (cnt == inum)
		{
			if ((adhandle = pcap_open_live(d->name,	// name of the device
				65536,			// portion of the packet to capture. 
								// 65536 grants that the whole packet will be captured on all the MACs.
				1,				// promiscuous mode (nonzero means promiscuous)
				1000,			// read timeout
				errbuf			// error buffer
			)) == NULL)
			{
				fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
				/* Free the device list */
				pcap_freealldevs(alldevs);
				return -1;
			}

			IntMgr.AddInterface(adhandle);
		}
	cnt++;
	}


	ConfigManager::LoadSettings();
	
	System::Logging.setLogLevel(LogLevel::LOG_DEBUG);
	System::Logging.setEcho(true);

	while (1 == 1)
	{
		Sleep(1);
	}

	//printf("\nlistening on %s...\n", d->description);
	
	/* At this point, we don't need any more the device list. Free it */
	pcap_freealldevs(alldevs);
	
	/* start the capture */
	//pcap_loop(adhandle, 0, packet_handler, NULL);


	//WaitForSingleObject(InterfaceThread, INFINITE);

	return 0;
}

