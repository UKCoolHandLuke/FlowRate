#include <Packet.h>
#include <PortRange.h>

Packet::Packet()
{
	//Set default values
	Source.Set("0.0.0.0");
	Destination.Set("0.0.0.0");
}

Packet::~Packet()
{

}


//Make a copy of a packet
//Date and time will be generated as new
//Other details will be copied

Packet *Packet::Copy()
{
	Packet *P = new Packet();
	P->Destination.Set(this->Destination.Get());
	P->Source.Set(this->Source.Get());

	P->Protocol = this->Protocol;

return(P);
}



//static method
string Packet::to_string(Packet *P)
{
	stringstream ss;
	ss << "(" << Protocol::Lookup(P->Protocol.ProtocolNumber) << ") ";

	ss << P->Source.Get();

	if (P->Protocol.ProtocolNumber == Protocol::UDP || P->Protocol.ProtocolNumber == Protocol::TCP)
	{
		ss << ":" << P->Protocol.Properties.getvalue("SOURCE.PORT") << "->";
		ss << P->Destination.Get();
		ss << ":" << P->Protocol.Properties.getvalue("DESTINATION.PORT");
	}
	else
	{
		ss << "->";
		ss << P->Destination.Get();
	}

	
	return(ss.str());
}




