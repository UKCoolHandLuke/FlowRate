#include <Host.h>
#include <algorithm>
#include <System.h>
#include <sstream>

Host::Host()
{
}

Host::~Host()
{
	//We have to remove all Packet Records from out list(s)
	Packet *P = NULL;

	while (Packets.size() > 0)
	{
		P = Packets.back();
		Packets.pop_back();

		if(P!=NULL)
			delete P;
		P = NULL;
	}	
}


Host::Host(string S)
{
	this->HostAddress.Set(S);
}


Host::Host(IP_Address S)
{
	this->HostAddress.Set(S.Get());
}


//Add a match record to our list
bool Host::Add(Packet *P)
{
Packets.push_back(P);

stringstream ss;

ss << HostAddress.to_string() << " Stack Size: " << Packets.size() << " ";
System::Logging.Writeln(ss.str(),LogLevel::LOG_DEBUG);

return(true);
}

size_t Host::Size()
{
	return(Packets.size());
}



long Host::countHits(long TimeFrame)
{
	TimeStamp T;
	EpocTime LimitTime = T.GetEpoc() - TimeFrame;
	unsigned PacketCounter = 0;

	for (unsigned int i = 0; i < Packets.size(); i++)
	{
		//Packet is within our range that we care about
		if (Packets[i]->DateTime.GetEpoc() > LimitTime)
		{
			PacketCounter++;
		}
	}
	
return(PacketCounter);
}



//Clean all packets older then the specified time

int Host::Clean(EpocTime TimeLimit)
{
	unsigned PacketCounter = 0;

	vector <Packet *> Removal;
	TimeStamp CurrentTime;
	long RemovalCutoff = CurrentTime.GetEpoc() - TimeLimit;
	vector<Packet *>::iterator it;

	for (it = Packets.begin(); it != Packets.end(); it++)
	{
		Packet *P = *(it);
		if (P->DateTime.GetEpoc() < RemovalCutoff)
		{
			//Add our packets to remove to our vector
			Removal.push_back(P);		
		}
	}


	//Remove the amount of elements from our primary vector to the size of our removal list
	Packets.erase(Packets.begin(), Packets.begin()+Removal.size());

	if(Removal.size()>0)
		System::Logging.Writeln("Scrubbed " + to_string(Removal.size()) + " packet(s) from host: " + HostAddress.to_string(), LogLevel::LOG_DEBUG);

	//delete packets
	while (Removal.size() > 0)
	{
		Packet *P = Removal.back();
		Removal.pop_back();
		delete P;
		P = NULL;
	}


	return(PacketCounter);
}