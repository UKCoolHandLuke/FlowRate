#include <PacketRecord.h>
#include <time.h>


//Record only the Timestamp
PacketRecord::PacketRecord()
{
	this->Time_Stamp = time(0);
	time(&this->Time_Stamp);
	this->Packet_Stamp = NULL;
}

//Record the Timestamp and the Packet
PacketRecord::PacketRecord(Packet *P)
{
	this->Time_Stamp = time(0);
	time(&this->Time_Stamp);
	this->Packet_Stamp = P;
}


PacketRecord::~PacketRecord()
{
	//Remove all record details
	this->Time_Stamp = NULL;
	this->Packet_Stamp = NULL;
}

