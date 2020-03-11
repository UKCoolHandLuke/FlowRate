#pragma once

#include <Action.h>
#include <System.h>
#include <string>
#include <Log.h>

class Action_Log : public Action
{

private:

	Log *LogObj;

public:

	Action_Log();
	~Action_Log();

	Action_Result Execute(Action_Block *Block);
	string getDescription();
};