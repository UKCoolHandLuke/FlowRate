#pragma once

#include <iostream>
#include <GlobalTypes.h>

#include <IP_Address.h>
#include <IPRange.h>
#include <Protocol.h>
#include <PortRange.h>
#include <PassengerProtocol.h>
#include <TimeStamp.h>

using namespace std;

/*
#define TCP_FLAG_FIN			1
#define TCP_FLAG_SYN			2
#define TCP_FLAG_RST			4
#define TCP_FLAG_PUSH			8
#define TCP_FLAG_ACK			10
#define TCP_FLAG_URG			20
#define TCP_FLAG_ECE			40
#define TCP_FLAG_CWR			80
*/

class Packet
{

private:

public:

	
	IP_Address					Source;
	IP_Address					Destination;

	Packet();
	~Packet();

	PassengerProtocol			Protocol;
	TimeStamp					DateTime;

	Packet *Copy();

	static string to_string(Packet *P);		//Convert a packet to a usable string



	friend std::ostream &operator << (std::ostream &out, const Packet& obj)
	{
		Packet *New_Obj = const_cast <Packet *>(&obj);
		out << New_Obj->DateTime.GetEpoc() << "\n";
		out << New_Obj->Destination.Get() << "\n";
		out << New_Obj->Source.Get() << "\n";
		out << New_Obj->Protocol.ProtocolNumber << std::endl;
		out << New_Obj->Protocol.Properties.size() << std::endl;
		for (Int32 i = 0; i < New_Obj->Protocol.Properties.size();i++)
		{
			out << New_Obj->Protocol.Properties.at(i)->Key << std::endl;
			out << New_Obj->Protocol.Properties.at(i)->Value << std::endl;
		}
		
		return out;
	}


	friend std::istream &operator >> (std::istream &in, Packet &obj)
	{
		EpocTime epoctime;
		string Src, Dst;
		Int32 Protocol;
		Int32 ProtocolPropertiesSize;
		string Key;
		Int32 Value;

		in >> epoctime;
		in >> Dst;
		in >> Src;
		in >> Protocol;
		in >> ProtocolPropertiesSize;
		if (in.eof())
			return(in);

		for (Int32 i = 0; i < ProtocolPropertiesSize; i++)
		{
			in >> Key;
			in >> Value;
			obj.Protocol.Properties.Add(Key, Value);
		}


		obj.DateTime.SetEpoc(epoctime);
		obj.Source.Set(Src);
		obj.Destination.Set(Dst);
		obj.Protocol.ProtocolNumber = Protocol;


		return in;
	}

};


