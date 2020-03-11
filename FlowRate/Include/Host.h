#pragma once

#include <PacketRecord.h>
#include <vector>

using namespace std;

class Host
{

private:

	vector <Packet *> Packets;


public:

	IPV4Address HostAddress;

	Host();
	Host(string S);
	Host(IP_Address S);
	~Host();

	bool Add(Packet *P);
	size_t Size();				//return the size of the Host Cache
	
	//Return a count within a timelimit (epoch) Current - limit
	long countHits(long TimeFrame);
	int Clean(EpocTime TimeLimit);		//Clean all packets older then the specified time


	friend std::ostream &operator << (std::ostream &out, const Host& obj)
	{
		Host *New_Obj = const_cast <Host *>(&obj);

		for (Int32 i = 0; i < New_Obj->Packets.size(); i++)
		{
			out << *New_Obj->Packets.at(i);
		}

		return out;
	}

};
