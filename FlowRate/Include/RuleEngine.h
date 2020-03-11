#pragma once
#include <iostream>
#include <Rule.h>
#include <Semaphore.h>
#include <set>

#include <Action_Allow.h>

using namespace std;

//Need to consider ordering of rules (ability to change the order)

class RuleEngine
{

private:

static vector <Rule *> Rules;
static vector <Rule *> Whitelist;
static Semaphore List_Lock;

public:

	RuleEngine();
	~RuleEngine();

	static int Count();
	static bool ProcessPacket(Packet *P);

	//Create a rule
	static Rule *CreateRule();
	static Rule *CreateRule(GUID myID);

	static Rule *GetRule(int index);
	static bool AddRule(Rule *R);
	static bool RemoveRule(Rule *R);

	static Rule *GetRuleByID(GUID ID);

	static set<string> GetInterfaces();

	//Need a method to remove rules etc - with lock


	static bool Clean();				//Remove stale packets (based on maximum threshold)

	static string getStats();

};
