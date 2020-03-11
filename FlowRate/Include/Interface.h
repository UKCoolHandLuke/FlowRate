#pragma once

#include <string>
#include "pcap.h"
#include <RuleEngine.h>
#include <IPRange.h>
#include <PortRange.h>
#include <windows.h>
#include <Packet.h>


#pragma comment(lib, "comsuppw.lib") 

using namespace std;


DWORD WINAPI ProcessInterface(LPVOID lpParam);		//thread entry point

class InterfaceManager
{

private:
	
	int StartInterface();
	int StopInterface();
	
public:
	InterfaceManager();
	~InterfaceManager();

	int AddInterface(pcap_t *adhandle);
	int RemoveInterface(pcap_t *adhandle);

};


class Interface
{

private:

	pcap_t *handle;
	int ProcessPacket(pcap_pkthdr *header, const u_char *pkt_data);

public:
	Interface(pcap_t *handle);
	~Interface();

	pcap_t *GetHandle();
	int DoWork();
};

