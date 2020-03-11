#pragma once

#include <Action.h>
#include <vector>
#include <Threshold.h>
#include <Host.h>

using namespace std;

class Action_List : public vector <Action *>
{

private:
	

public:

	Action_List();
	~Action_List();

	bool Execute(Host *H, Threshold *T, Match *M);
};