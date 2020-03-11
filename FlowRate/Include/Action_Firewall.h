#pragma once

#include <Action.h>
#include <System.h>
#include <string>
#include <Log.h>

#include <windows.h>
#include <crtdbg.h>
#include <netfw.h>
#include <objbase.h>
#include <oleauto.h>
#include <stdio.h>
#include <System_Firewall.h>

#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "oleaut32.lib" )


#define ACTION_FIREWALL_DURATION_DEFAULT		0


class Action_Firewall : public Action
{

private:


public:

	Action_Firewall();
	~Action_Firewall();


	Action_Result Execute(Action_Block *Block);
	string getDescription();
};