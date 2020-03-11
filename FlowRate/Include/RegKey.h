#pragma once

#include <vector>
#include <RegValue.h>

#define MAX_KEY_LENGTH			255
#define MAX_VALUE_NAME			16383
#define MAX_VALUE_DATA_SIZE		255

class RegKey
{

private:
	string Name;

public:

	vector <RegKey *> Keys;
	vector <RegValue *> Values;

	RegKey();
	~RegKey();

	static bool Load(string KeyLocation, RegKey *R);

	RegKey		*GetSubKey(string Name);			//Get a subkey by name
	RegValue	*GetValuebyName(string ValueName);
};