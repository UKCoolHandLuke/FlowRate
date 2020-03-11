#include <Registry.h>


Registry::Registry()
{
	Key = NULL;
}

Registry::~Registry()
{
	if (Key != NULL)
	{
		//Close the key first
		Close();
	}
}



bool Registry::Open(HKEY Hive, wstring Path)
{
	
	LONG lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, TEXT(Path.c_str()), 0, KEY_READ | KEY_WOW64_64KEY, &Key);
	if (lRes != ERROR_SUCCESS)
	{
		Key = NULL;
		return(false);
	}

	return(true);
}


bool Registry::Close()
{
	if (Key != NULL)
	{
		RegCloseKey(Key);
		Key = NULL;
		return(true);
	}

	return(false);
}

LONG Registry::GetStringValue(const wstring &strValueName, std::wstring &strValue, const wstring &strDefaultValue)
{
	strValue = strDefaultValue;
	WCHAR szBuffer[512];
	DWORD dwBufferSize = sizeof(szBuffer);
	ULONG nError;

	if (Key == NULL)
		return(false);

	nError = RegQueryValueExW(Key, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);

	if (ERROR_SUCCESS == nError)
		strValue = szBuffer;

	return nError;
}


LONG Registry::GetBoolRegKey(const wstring &strValueName, bool &bValue, bool bDefaultValue)
{
	DWORD nDefValue((bDefaultValue) ? 1 : 0);
	DWORD nResult(nDefValue);

	if (Key == NULL)
		return(false);

	LONG nError = GetDWORDRegKey(strValueName.c_str(), nResult, nDefValue);
	if (ERROR_SUCCESS == nError)
		bValue = (nResult != 0) ? true : false;

	return nError;
}


LONG Registry::GetDWORDRegKey(const std::wstring &strValueName, DWORD &nValue, DWORD nDefaultValue)
{
	if (Key == NULL)
		return(false);

	nValue = nDefaultValue;
	DWORD dwBufferSize(sizeof(DWORD));
	DWORD nResult(0);
	LONG nError = ::RegQueryValueExW(Key, strValueName.c_str(), 0, NULL, reinterpret_cast<LPBYTE>(&nResult), &dwBufferSize);

	if (ERROR_SUCCESS == nError)
		nValue = nResult;

	return nError;
}