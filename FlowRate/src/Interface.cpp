#include <Interface.h>
#include <IP.h>

InterfaceManager::InterfaceManager()
{

}

InterfaceManager::~InterfaceManager()
{

}


int InterfaceManager::AddInterface(pcap_t *adhandle)
{
	Interface *I = new Interface(adhandle);
	pcap_t *h = adhandle;

	HANDLE  InterfaceThread;	//may need to be destroyed after use (this may need to be a structure)
	DWORD   dwThreadId = 0;
	
	InterfaceThread = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		ProcessInterface,       // thread function name
		I,						// argument to thread function 
		0,                      // use default creation flags 
		&dwThreadId);			// returns the thread identifier 

	return(ERROR_SUCCESS);
}


DWORD WINAPI ProcessInterface(LPVOID lpParam)
{
	Interface *I = (Interface*)lpParam;
	I->DoWork();
	return(ERROR_SUCCESS);
}



int InterfaceManager::RemoveInterface(pcap_t *adhandle)
{
	return(ERROR_SUCCESS);
}

int InterfaceManager::StartInterface()
{
	return(ERROR_SUCCESS);
}

int InterfaceManager::StopInterface()
{
	return(ERROR_SUCCESS);
}



Interface::Interface(pcap_t *adhandle)
{
	handle = adhandle;
}


Interface::~Interface()
{

	//if handle 
	//free handle

}


pcap_t *Interface::GetHandle()
{
	return(handle);
}


int Interface::DoWork()
{

	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	stringstream ss;

	int res = 0;

	//pcap_t *adhandle = (pcap_t *)lpParam;

	while ((res = pcap_next_ex(handle, &header, &pkt_data)) >= 0)
	{
		if (res == 1)
		{
			ProcessPacket(header, pkt_data);
		}
		else if(res == 0)   //0 means we timed out waiting for a packet
		{
			//cout << "Timeout waiting for data" << endl;
		}
		else if(res == PCAP_ERROR)
		{
			ss.str("");
			ss << "An error occured getting data: " << res;
			System::Logging.Writeln(ss.str());
		}
		else
		{
			ss.str("");
			ss << "An error occured: " << res;
			System::Logging.Writeln(ss.str());
		}

	}

	pcap_close(handle);

	ss.str("");
	ss << "This should not happen, it will likely kill our thread" << res;
	System::Logging.Writeln(ss.str(),LogLevel::LOG_INFO);

	return(ERROR_SUCCESS);
}





int Interface::ProcessPacket(pcap_pkthdr *header, const u_char *pkt_data)
{

	/*
	
	This function should:
	Get the details of the packet (ipv4,ipv6 etc)
	Get the source address etc
	Fill the Packet structure for processing

	*/

	ip_v4_header *ih;
	udp_header *uh;
	tcp_header *tcp;
	icmp_header *icmp;
	u_int ip_len=0;
	u_short sport=0, dport=0;

	time_t local_tv_sec;
	struct tm ltime;
	char timestr[16];

	local_tv_sec = header->ts.tv_sec;
	localtime_s(&ltime, &local_tv_sec);
	strftime(timestr, sizeof timestr, "%H:%M:%S", &ltime);
	
	Packet *P = IP::CreatePacket(pkt_data);

	if (P == NULL)
		return(NULL);

	RuleEngine::ProcessPacket(P);
	delete P;

	return(1);
}