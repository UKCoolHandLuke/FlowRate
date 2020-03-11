#include <MatchCache.h>
#include <algorithm>
#include <fstream>



MatchCache::MatchCache() : Manager(SAVE_INTERVAL)
{
	FirstLaunch = true;
}

MatchCache::MatchCache(string _ID) : Manager(SAVE_INTERVAL)
{
	//memset(ID, NULL, sizeof(ID));
	//Generate_ID(ID, sizeof(ID));
	//ID = _ID;		//Copy our Rule ID
	FirstLaunch = true;
}


MatchCache::~MatchCache()
{
	//if (PacketList != NULL)
		//delete PacketList;
}


bool MatchCache::Execute()
{
	if (FirstLaunch)
		{
		FirstLaunch = false;
		return(false);
		}
	else
		return(Save(this->ID));
}


//Add a matching packet to our structure
//The Cache will build a list of hosts - which will store packets
//This will build indefinately - its up to the cleaner to remove existing packets
Host *MatchCache::Add(Packet *P)
{
	if (P == NULL)
		return(NULL);

	string TargetAddress;

	if (MatchBasis == MATCH_SRC)
		TargetAddress = P->Source.Get();
	else
		TargetAddress = P->Destination.Get();

	//Host *H = FindHostEntry(TargetAddress.Get());
	Host *H = FindHostEntry(TargetAddress);

	

	//If we already have a host entry then just add our packet
	if (H != NULL)
		{
		Cache_Lock.Lock();
			H->Add(P);
		Cache_Lock.Unlock();
		return(H);
		}
	else
		{
		Host *H = new Host(TargetAddress);
		Cache_Lock.Lock();
			EntryList.push_back(H);
			H->Add(P);
		Cache_Lock.Unlock();
		return(H);
		}

return(NULL);
}



bool MatchCache::RemoveHost(IPV4Address IP)
{

	Host *H = FindHostEntry(IP);
	if (H != NULL)
	{
		//Cache_Lock.Lock();
			EntryList.erase(std::remove(EntryList.begin(), EntryList.end(), H), EntryList.end());
			delete H;
			H = NULL;
		//Cache_Lock.Unlock();
	}

return(false);
}



Host* MatchCache::FindHostEntry(IPV4Address IP)
{
	//Cache_Lock.Lock();
	for (Int32 i = 0; i < EntryList.size(); i++)
	{
		if (EntryList[i]->HostAddress == IP)	  //If we already have an entry then add our new record
		{
			Cache_Lock.Unlock();
			return(EntryList[i]);
		}
	}
	//Cache_Lock.Unlock();
return(NULL);
}


/*
Clear all entries in our cache
this will delete all host entries - which in turn will delete all packets
*/
int MatchCache::Flush()
{
	Host *Host=NULL;
	int Counter=0;
	
	Cache_Lock.Lock();

	while (EntryList.size()>0)
	{
		Host = EntryList.back();
		EntryList.pop_back();
		if(Host!=NULL)
			delete Host;
		Host = NULL;
		Counter++;
	}
	Cache_Lock.Unlock();
return(Counter);
}


bool MatchCache::SetMatchType(MATCH_STATUS newStatus)
{
	MatchBasis = newStatus;
	Flush();
	//Need to clear any existing entries
	return(true);
}

MATCH_STATUS MatchCache::GetMatchType()
{
	return(MatchBasis);
}



bool MatchCache::Clean(long OldestPacket_Time)
{

	
	Cache_Lock.Lock();
	for (Int32 i = 0; i < EntryList.size(); i++)
	{
		EntryList[i]->Clean(OldestPacket_Time);
		if (EntryList[i]->Size() == 0)
		{
			//Remove the host entry
			System::Logging.Writeln("Removing empty host cache for: " + EntryList[i]->HostAddress.to_string(),LogLevel::LOG_DEBUG);
			RemoveHost(EntryList[i]->HostAddress.to_string());
		}
			
	}
	Cache_Lock.Unlock();


return(true);
}


string MatchCache::GetID()
{
	return(ID);
}

bool MatchCache::SetID(string _ID)
{
	ID = _ID;
	return(true);
}



bool MatchCache::Save(string filename)
{
	string F = "Cache\\" + filename;

	std::ofstream out(F);

	Cache_Lock.Lock();

	for (Int32 i = 0; i < EntryList.size(); i++)
	{
		Host *H = EntryList.at(i);
		out << *H;
	}

	Cache_Lock.Unlock();

	out.close();

return(true);
}

//This might need a try catch for corrupt data

bool MatchCache::Load(string filename)
{
	bool result = false;
	Packet *P;
	Int32 Loadedcnt = 0;;
	stringstream ss;
	bool eof;

	string F = "Cache\\" + filename;
	System::Logging.Writeln("Loading Cache file " + F,LogLevel::LOG_INFO);

	std::ifstream in(F);

	if (in.is_open())
	{
		while (!in.eof())
		{

			P = new Packet();
			in >> *P;
			//this is a problem for failed loaded data
			//if loaded ()
			//Need to fix !!!!
			if (!in.eof())
			{
				Add(P);
				Loadedcnt++;
			}
		}
		in.close();
		result = true;
	}
	else
		System::Logging.Writeln("Failed to open cache file: " + F, LogLevel::LOG_INFO);

ss << "Loaded " << Loadedcnt << " cache entries";
System::Logging.Writeln(ss.str());
return(result);
}



int MatchCache::getSize()
{
	int Count = 0;


	Cache_Lock.Lock();
	for (Int32 i = 0; i < EntryList.size(); i++)
	{
		Host *H = EntryList.at(i);
		Count += H->Size();
	}
	Cache_Lock.Unlock();

	return(Count);
}

int MatchCache::getHostCount()
{
	int Count = 0;

	Cache_Lock.Lock();
		Count = EntryList.size();
	Cache_Lock.Unlock();
	return(Count);
}

