#pragma once

#include <Firewall_Manager.h>
#include <Windows_Firewall.h>
#include <Utility.h>


Firewall_Manager::Firewall_Manager() : Manager(1000)
{
}

Firewall_Manager::~Firewall_Manager()
{
}


/*
This task will have two main purposes
	Add any Item to the firewall
	Remove any expired Items from the firewall
*/
bool Firewall_Manager::Execute()
{

	Action_Block *HostBlock = (Action_Block *)GetTask();
	
	//Tweak the rulename to make it unique for the Windows Firewall Engine

	if (HostBlock != NO_TASK)
		{
		//Firewall_Block *Blocked_Host = new Firewall_Block();
		//The firewall needs to be change to simply accept a Firewall_Block structure which should contain all data needed
		//Looking for Who, What, When, How long for
		
		//Check if the rule already exists for this host
		for (Int32 i = 0; i < Firewall_List.size(); i++)
			{
			Action_Block *B = Firewall_List.at(i);
			//if(B->GetID() == Host->GetID())
			if (*B == *HostBlock)
				{
				System::Logging.Writeln("Host: " + HostBlock->Host + " already filtered", LogLevel::LOG_DEBUG);
				delete HostBlock;
				return(false);
				}
			}
				
		System::Logging.Writeln("Adding filter rule: " + HostBlock->Get_RuleID() + " for host " + HostBlock->Host + " which will be removed at " + TimeStamp::EpochToString(HostBlock->RemovalTime), LogLevel::LOG_INFO);
		Windows_Firewall::AddRule(HostBlock);
		Firewall_List.push_back(HostBlock);
		}

	
	//Lets scrub our expired rules
	
	//Get Current time
	EpocTime Current_EpocTime = TimeStamp::CurrentEpoc();
	Action_Block *F;


	std::vector<Action_Block *>::iterator it = Firewall_List.begin();
	while (it != Firewall_List.end())
	{
		F = *it;
		if (F->RemovalTime < Current_EpocTime)
		{
			//Remove the Firewall rule as it has expired
			it = Firewall_List.erase(it);
			System::Logging.Writeln("Removing expired rule: " + F->Get_RuleID() + " for host " + F->Host, LogLevel::LOG_INFO);
			Windows_Firewall::RemoveRule(F);
			delete F;
		}
		else
		{
			++it;
		}

	}


	return(true);
}
