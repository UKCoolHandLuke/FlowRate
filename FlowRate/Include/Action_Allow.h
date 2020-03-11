#pragma once

#include <Action.h>
#include <System.h>
#include <string>
#include <Log.h>

//This rule effectively whitelists the address/range/ports(s) that it is applied to

class Action_Allow : public Action
{

private:

public:

	Action_Allow();
	~Action_Allow();

	Action_Result Execute(Action_Block *Block);
	string getDescription();
};