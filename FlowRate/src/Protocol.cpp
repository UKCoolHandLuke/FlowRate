#include <GlobalTypes.h>
#include <Packet.h>

using namespace std;


string Protocol::Lookup(int P)
{
	string Answer = "";

	switch (P)
	{
	case Protocol::ICMP:
		Answer = "ICMP";
		break;

	case Protocol::TCP:
		Answer = "TCP";
		break;

	case Protocol::UDP:
		Answer = "UDP";
		break;

	case Protocol::VRRP:
		Answer = "VRRP";
		break;

	case Protocol::IGMP:
		Answer = "IGMP";
		break;

	case Protocol::GRE:
		Answer = "GRE";
		break;

	default:
		Answer = "unknown" + '(' + P + ')';
	}

	return(Answer);
}


//Not implemented lookup to protocol abreviation to code(number)
int Protocol::Lookup(string P)
{
	return(0);
}


Protocol_List::Protocol_List()
{
}

Protocol_List::~Protocol_List()
{
	clear();
}

bool Protocol_List::Add(Int32 P)
{
	push_back(P);
	return(true);
}


bool Protocol_List::Contains(Int32 P) const
{
	for (Int32 i = 0; i < size(); i++)
	{
		if (this->at(i) == Protocol::ANY)
			return(true);
		
		if (this->at(i) == P)
		{
			return(true);
		}
	}

return(false);
}


Protocol_List* Protocol_List::Copy()
{
	Protocol_List *P = new Protocol_List();

	for (Int32 i = 0; i < this->size(); i++)
	{
		Int32 Proto = this->at(i);
		P->push_back(Proto);
	}
	return(P);
}


