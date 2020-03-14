#pragma once

#include <Log.h>
#include <Utility.h>

#define VERSION_NUMBER	0.21

class System
{

private:
	

public:

	System();
	~System();

	static double getVersionDouble();
	static string getVersionString();

	static Log Logging;
	static void Exit(string Message);	//exit the system with a message

};

