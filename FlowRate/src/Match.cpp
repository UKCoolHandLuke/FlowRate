#include <Match.h>

Match::Match()
{
	DestinationIP_List = new IP_Address_Range_List;
	SourceIP_List = new IP_Address_Range_List();
	DestinationPort_List = new PortRange_List();
	SourcePort_List = new PortRange_List();
	_Protocol_List = new Protocol_List();
	Properties = new KeyValuePair_List<Int32>();
	Src_Exception_List = new IP_Address_Range_List();
	Dst_Exception_List = new IP_Address_Range_List();

	Cache = NULL;		//MatchCache Pointer

}

Match::~Match()
{

	delete DestinationIP_List;
	delete SourceIP_List;

	delete DestinationPort_List;
	delete SourcePort_List;

	delete _Protocol_List;

	delete Properties;

	delete Src_Exception_List;
	delete Dst_Exception_List;

}