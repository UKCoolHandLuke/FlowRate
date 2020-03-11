#pragma once
#include <Packet.h>

class PacketRecord
{

private:

	Packet *Packet_Stamp;
	time_t Time_Stamp;

public:

	PacketRecord();
	PacketRecord(Packet *P);
	~PacketRecord();

};