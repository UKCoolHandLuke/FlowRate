#pragma once
#include <Manager.h>
#include <RuleEngine.h>


#define SCRUB_INTERVAL 500

class Packet_Manager : public Manager
{

private:

public:

	Packet_Manager();
	~Packet_Manager();

	virtual bool Execute();
};