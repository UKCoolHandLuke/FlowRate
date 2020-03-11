#pragma once

#include <PacketRecord.h>
#include <Host.h>
#include <vector>
#include <Semaphore.h>
#include <Threshold_List.h>
#include <System.h>
#include <Manager.h>

using namespace std;

#define SAVE_INTERVAL		60000	//Default to save every 5 minutes

enum MATCH_STATUS					//which host should we be analysing for our cache
{
	MATCH_SRC = 0,
	MATCH_DST = 1
};


class MatchCache : Manager
{

private:

	vector<Host *>		EntryList;
	MATCH_STATUS		MatchBasis=MATCH_STATUS::MATCH_SRC;				//Default to matching based on SRC host
	Semaphore			Cache_Lock;										//To make the lists thread safe
	string ID;			//rule/match ID
	bool				FirstLaunch;

public:

	MatchCache(string _ID);
	MatchCache();
	~MatchCache();

	virtual bool Execute();												//Primary function to store our cache

	Host *Add(Packet *P);												//Add an entry
	bool Remove(Packet *P);												//Remove a specific entry
	bool RemoveHost(IPV4Address IP);									//Remove a specific entry
	Host* FindHostEntry(IPV4Address IP);								//Find a Host entry (based on IP)


	bool RemoveAfterTimestamp(long Timestamp);							//Remove all entries after a given time stamp
	int GetRecordCount(string src, long Timestamp);						//Get a count of all packets within our timeframe
	int getSize();														//Get a count of all packets
	int getHostCount();													//Get a count of all hosts
	int Flush();														//Flush all entries
	bool SetMatchType(MATCH_STATUS newStatus);
	MATCH_STATUS GetMatchType();

	bool Clean(long OldestPacket_Time);

	string GetID();
	bool SetID(string _ID);

	bool Save(string Filename);											//Flush the cache to a file
	bool Load(string Filename);											//Load the cache from a file

};
