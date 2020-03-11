#pragma once

#include <Manager.h>
#include <IPRange.h>
#include <TimeStamp.h>

#include <Action_Block.h>

//void Firewall_Block::Generate_ID(char *s, const int len);	//static init




class Firewall_Manager : public Manager
{

private:

	vector <Action_Block *> Firewall_List;

public:

	Firewall_Manager();
	~Firewall_Manager();


	//virtual method
	bool Execute();
};


