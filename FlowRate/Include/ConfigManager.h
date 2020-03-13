#pragma once

#include <StringList.h>
#include <RegKey.h>
#include <Rule.h>
#include <RuleEngine.h>
#include <exception>
#include <Action_Manager.h>
#include <iterator>
#include <Utility.h>

#define INVALID_NUMBER	-1

#define REGISTRY_LOCATION "SOFTWARE\\FlowRate"

class ConfigManager
{

private:

	static StringList *LoadStrings(RegKey *KeyHandle, string ValueName);
	static int LoadInt(RegKey *KeyHandle, string ValueName);
	static string LoadString(RegKey *KeyHandle, string ValueName);
	static StringList *SplitString(string input, char delimeter);

public:

	ConfigManager();
	~ConfigManager();

	static bool LoadSettings();
	static bool LoadRule(RegKey *R, Rule *&M);

};


