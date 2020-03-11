#include <PassengerProtocol.h>

PassengerProtocol::PassengerProtocol()
{
	ProtocolNumber = Protocol::NOT_SET;
}

PassengerProtocol::~PassengerProtocol()
{

}


/*
Create a copy of our passenger protocol
*/
PassengerProtocol *PassengerProtocol::Copy()
{
	PassengerProtocol *P = new PassengerProtocol();
	
	for (Int32 i = 0; i < this->Properties.size();i++)
	{
		P->Properties.Add(this->Properties.at(i)->Key, this->Properties.at(i)->Value);
	}

	P->ProtocolNumber = this->ProtocolNumber;

return(P);
}
