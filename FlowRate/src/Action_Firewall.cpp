#pragma once

#include <Action_Firewall.h>
#include <windows.h>
#include <stdio.h>
#include <comutil.h>
#include <atlcomcli.h>
#include <netfw.h>
#include <Windows_Firewall.h>
#include <Firewall_Manager.h>
#include <Log.h>


Action_Firewall::Action_Firewall()
{
	//LogObj = NULL;
	//LogObj = new Log("FirewallLog.txt");
	//Properties.Add("NAME", "ACTION_FIREWALL");
}

Action_Firewall::~Action_Firewall()
{
	
}


Action_Result Action_Firewall::Execute(Action_Block *Block)
{
	
	Action_Result Result;
	stringstream ss;
	Int32 Duration = ACTION_FIREWALL_DURATION_DEFAULT;		//default firewall blocked duration

	//We need a copy of the host details and rules details for the firewall rule
	//Pointers would kill this

	if (Properties.ContainsKey("Duration") != KEY_NOT_FOUND)
	{
		string BanTime = Properties.getvalue("Duration");
		Duration = StringToInt(BanTime);
		if (Duration == INVALID_NUMBER)
			Duration = ACTION_FIREWALL_DURATION_DEFAULT;
	}


	Block->RemovalTime = Block->TimeAdded + Duration;


	System_Firewall::FW_Manager.AddTask(Block);

	Result.Result = true;
	return(Result);
}


string Action_Firewall::getDescription()
{
	stringstream ss;
	ss << "Apply a firewall rule that will only be relinquished after " << Properties.getvalue("Duration") << " second(s)";
	return(ss.str());
}



