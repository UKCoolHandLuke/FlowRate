#include <RuleEngine.h>
#include <Action_Manager.h>

vector <Rule*> RuleEngine::Rules;		//init
vector <Rule*> RuleEngine::Whitelist;	//init
Semaphore RuleEngine::List_Lock;		//init



RuleEngine::RuleEngine()
{
}

RuleEngine::~RuleEngine()
{
}

//Static
Rule *RuleEngine::CreateRule()
{
	Rule *R = new Rule();
	//Add(R);
	return(R);
}

//Static
Rule *RuleEngine::CreateRule(GUID myID)
{
	Rule *R = new Rule(myID);
	//Add(R);
	return(R);
}


int RuleEngine::Count()
{
	return(Rules.size());
}

Rule *RuleEngine::GetRule(int index)
{
	Rule *R=NULL;
	if (index > Rules.size())	//this is likely wrong +1
	{
		R = Rules.at(index);
		return(R);
	}

return(NULL);
}

bool RuleEngine::AddRule(Rule *R)
{
	stringstream ss;
	ss << "Adding Rule: " << R->GetID() << " to interface " << R->Interface.Get();
	vector <Rule*> *Rulelist_to_change = &RuleEngine::Rules;

	for (unsigned i = 0; i < R->Actions.size();i++)
	{
		ss << endl;
		ss << " - Action: " << R->Actions[i]->getDescription();


		if (R->Actions[i]->Properties.getvalue("TYPE") == to_string(ACTION_ALLOW))
		{
			//Add to the whitelist not the standard list
			Rulelist_to_change = &RuleEngine::Rules;
		}
	}

	System::Logging.Writeln(ss.str(), LogLevel::LOG_INFO);

	List_Lock.Lock();
		Rulelist_to_change->push_back(R);
	List_Lock.Unlock();
	
	return(false);
}


bool RuleEngine::RemoveRule(Rule *R)
{

	stringstream ss;
	ss << "Removing Rule: " << R->GetID();
	System::Logging.Writeln(ss.str(),LogLevel::LOG_INFO);

	List_Lock.Lock();

	for (std::vector<Rule*>::iterator it = Rules.begin(); it != Rules.end(); ++it)
	{
		Rule *CurrentRule = *it;
		if (CurrentRule == R)
		{
			Rules.erase(it);
			List_Lock.Unlock();
			return(true);
		}
	}

	List_Lock.Unlock();

	return(false);
}


bool RuleEngine::ProcessPacket(Packet *P)
{
	int returnValue = false;			//Did at least one rule match
	stringstream ss;

	List_Lock.Lock();

	for (std::vector<Rule*>::iterator it = Rules.begin(); it != Rules.end(); ++it)
	{
		Rule *R = *it;
		if (R->isEnabled())
		{
			if (R->TestPacket(P))
			{
				returnValue = true;
				ss.str("");
				ss << "Packet Matches Rule: " << R->GetID() << "-";
				ss << Packet::to_string(P);
				System::Logging.Writeln(ss.str(),LogLevel::LOG_DEBUG);
			}
		}
	}

	List_Lock.Unlock();

	if (System::Logging.getLogLevel() == LogLevel::LOG_DEBUG)
	{
		if (!returnValue)
		{
			ss << "No match for packet: " << Packet::to_string(P);
			System::Logging.Writeln(ss.str(), LogLevel::LOG_DEBUG);
		}
	}


return(returnValue);
}


bool RuleEngine::Clean()
{
	List_Lock.Lock();

	for (std::vector<Rule*>::iterator it = Rules.begin(); it != Rules.end(); ++it)
	{
		Rule *R = *it;
		R->Clean();
	}

	List_Lock.Unlock();

return(true);
}


//static
Rule *RuleEngine::GetRuleByID(GUID ID)
{

	List_Lock.Lock();

	for (std::vector<Rule*>::iterator it = Rules.begin(); it != Rules.end(); ++it)
	{
		Rule *R = *it;
		if (R->GetID() == ID)
		{
			List_Lock.Unlock();
			return(R);
		}
	}

List_Lock.Unlock();
return(NULL);
}


/*
Static
Return a list of interface IP addresses
*/

set<string> RuleEngine::GetInterfaces()
{

	List_Lock.Lock();

	set<string> I_List;

	for (std::vector<Rule*>::iterator it = Rules.begin(); it != Rules.end(); ++it)
	{
		Rule *R = *it;
		if (R->Interface.Get() != "")
		{
			if (!I_List.count(R->Interface.Get()))
			{
				I_List.insert(R->Interface.Get());
			}
		}
	}
	
	List_Lock.Unlock();

	return(I_List);
}


string RuleEngine::getStats()
{
	stringstream ss;

	List_Lock.Lock();

	ss << "Total Rules: " << Rules.size() << endl;

	for (std::vector<Rule*>::iterator it = Rules.begin(); it != Rules.end(); ++it)
	{
		Rule *R = *it;
		ss << "Rule: " << R->GetID() << " - ";
		ss << "Cache size: " << R->Criteria.Cache->getSize() << " spread over " << R->Criteria.Cache->getHostCount() << " hosts" << endl;
	}

	List_Lock.Unlock();



	return(ss.str());
}