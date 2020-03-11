#pragma once
#include <IP_Address_Range_List.h>
#include <IPRange.h>
#include <PortRange.h>
#include <Packet.h>
#include <MatchCache.h>

class Match
{

private:
	
public:

	MatchCache					*Cache;

	IP_Address_Range_List		*DestinationIP_List;
	PortRange_List				*DestinationPort_List;

	IP_Address_Range_List		*SourceIP_List;
	PortRange_List				*SourcePort_List;

	Protocol_List				*_Protocol_List;
	KeyValuePair_List	<Int32> *Properties;

	IP_Address_Range_List		*Src_Exception_List;
	IP_Address_Range_List		*Dst_Exception_List;

	Match();
	~Match();

};
