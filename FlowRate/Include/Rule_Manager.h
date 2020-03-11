#pragma once
#include <Manager.h>
#include <RuleEngine.h>


#define SCRUB_INTERVAL 500

class Rule_Manager : public Manager
{

private:

public:

	Rule_Manager();
	~Rule_Manager();

	virtual bool Execute();
	bool getStats();
};