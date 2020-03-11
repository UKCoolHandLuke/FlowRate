#pragma once
#include <Action_Email.h>
#include <Action_Log.h>
#include <Action_Firewall.h>
#include <Action_Allow.h>
//#include <Action_Stats.h>

#define ACTION_LOG			0
#define ACTION_EMAIL		1
#define ACTION_FIREWALL		2
#define ACTION_ALLOW		3
#define ACTION_STATS		4

class Action_Manager
{

private:

public:

	Action_Manager();
	~Action_Manager();

	static Action *CreateAction(int ActionType);

};
