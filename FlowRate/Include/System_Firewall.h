#pragma once

#include <Log.h>
#include <Firewall_Manager.h>


static class System_Firewall
{

private:

public:

	System_Firewall();
	~System_Firewall();

	static Firewall_Manager FW_Manager;
};
