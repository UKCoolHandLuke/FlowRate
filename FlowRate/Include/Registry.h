#include <iostream>
#include <string>
#include <exception>
#include <windows.h>

using namespace std;

#pragma once




//Example Usage:
/*
HKEY hKey;
LONG lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Perl", 0, KEY_READ, &hKey);
bool bExistsAndSuccess (lRes == ERROR_SUCCESS);
bool bDoesNotExistsSpecifically (lRes == ERROR_FILE_NOT_FOUND);
std::wstring strValueOfBinDir;
std::wstring strKeyDefaultValue;
GetStringRegKey(hKey, L"BinDir", strValueOfBinDir, L"bad");
GetStringRegKey(hKey, L"", strKeyDefaultValue, L"bad");
*/

class Registry
{

private:

	HKEY Key;

public:

	Registry();
	~Registry();
		

	
	bool Open(HKEY Hive, wstring Path);
	bool Close();


	LONG GetStringValue(const wstring &strValueName, wstring &strValue, const wstring &strDefaultValue);
	LONG GetBoolRegKey(const wstring &strValueName, bool &bValue, bool bDefaultValue);
	LONG GetDWORDRegKey(const wstring &strValueName, DWORD &nValue, DWORD nDefaultValue);
	
};


