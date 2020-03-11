#pragma once

#include <Packet.h>
#include <MatchCache.h>
#include <Threshold_List.h>
#include <Log.h>
#include <Action_List.h>
#include <Match.h>
#include <GUID.h>


using namespace std;


class Rule
{

private:

	bool Enabled;
	MatchCache Cache;
	GUID ID;

public:

	Match				Criteria;		//lists of matching criteria (hosts, ports, protocols etc)
	Threshold_List		Limit;			//limitations for each host
	Action_List			Actions;		//Actions to perform on a match
	TimeStamp			Time;
	IP_Address			Interface;
	
	Rule();
	Rule(GUID myID);
	~Rule();

	bool Init();

	void Enable();
	void Disable();
	bool isEnabled();


	//Initialiser for our static decleration
	static IPV4Range* IPV4_ANY();

	//Check if our packet meets our rule requirements
	bool TestPacket(Packet *P);

	//Check if our host has exceeded the limits implied on it
	bool CheckLimits();
	
	//Cleanup old packets
	bool Clean();

	bool SetMatchType(MATCH_STATUS newStatus);
	MATCH_STATUS GetMatchType();

	bool SetTimeStamp(EpocTime);
	EpocTime GetTimeStamp();
	GUID GetID();

	bool LoadCache();

};




