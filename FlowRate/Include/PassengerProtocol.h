#pragma once

#include <GlobalTypes.h>
#include <KeyValuePair.h>
#include <Protocol.h>

//#define PROTOCOL_ANY			9999
//#define PROTOCOL_NOT_SET		-1

class PassengerProtocol
{

private:


public:

	PassengerProtocol();
	~PassengerProtocol();

	Int32 ProtocolNumber;		//Holds the protocol number of the current Packet

	KeyValuePair_List <Int32>	Properties;
	PassengerProtocol *Copy();


	PassengerProtocol& operator=(const PassengerProtocol& A)
	{
		Properties.clear();
		
		for (Int32 i = 0; i < A.Properties.size(); i++)
		{
			Properties.Add(A.Properties.at(i)->Key, A.Properties.at(i)->Value);
		}

		ProtocolNumber = A.ProtocolNumber;
	return(*this);
	}


};
