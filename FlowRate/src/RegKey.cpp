#include <RegKey.h>
#include <Utility.h>

RegKey::RegKey()
{

}

RegKey::~RegKey()
{

	//loop all my keys and delete all subkeys/values
	while(Keys.size()>0)
	{
		RegKey *R = Keys.front();
		Keys.erase(Keys.begin());
		delete R;
	}

	
	//Clean our list of values
	while(Values.size()>0)
	{
		RegValue *R = Values.front();
		Values.erase(Values.begin());
		
		//delete  R->Value;				//delete the data
		delete R;
	}
	
}

//Static
bool RegKey::Load(string KeyLocation, RegKey *R)
{

	HKEY hKey;
	TCHAR    achClass[MAX_PATH] = TEXT("");
	DWORD    cchClassName = MAX_PATH;
	DWORD	 SubKeys;
	DWORD    cbMaxSubKey;
	DWORD    cchMaxClass;
	DWORD    cValues;
	DWORD    cchMaxValue;
	DWORD    cbMaxValueData;
	DWORD    cbSecurityDescriptor;
	FILETIME ftLastWriteTime;

	DWORD    cbName;
	TCHAR    achKey[MAX_KEY_LENGTH];
	DWORD	 cchValue = MAX_VALUE_NAME;
	TCHAR	 achValue[MAX_VALUE_NAME];

	int retCode;

	retCode = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT((char *)KeyLocation.c_str()), 0, KEY_READ | KEY_WOW64_64KEY, &hKey);
	if(retCode != ERROR_SUCCESS)
		{
		return(ERROR);
		}


	retCode = RegQueryInfoKey(hKey, achClass,&cchClassName,	NULL, &SubKeys, &cbMaxSubKey, &cchMaxClass,&cValues, &cchMaxValue, &cbMaxValueData, &cbSecurityDescriptor, &ftLastWriteTime);     

	//Load all subkeys
	if (SubKeys)
	{
		for (Int32 i = 0; i < SubKeys; i++)
		{
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime);
			if (retCode == ERROR_SUCCESS)
				{
				RegKey *RKey = new RegKey();
				RKey->Name = achKey;
				RegKey::Load(KeyLocation + "\\" + achKey,RKey);
				R->Keys.push_back(RKey);
				}

		}
	}


	//Load all values

	if (cValues)
	{
		DWORD	 Max_size;
		DWORD	 myDataType;
		CHAR	 *szBuffer;

		for (Int32 i = 0; i < cValues; i++)
		{
			Max_size = MAX_VALUE_DATA_SIZE;
			szBuffer = new CHAR[Max_size];
			memset(szBuffer, NULL, sizeof(Max_size));
			
			cchValue = MAX_VALUE_NAME;
			achValue[0] = '\0';
			retCode = RegEnumValue(hKey, i, achValue, &cchValue, NULL, &myDataType, (LPBYTE)szBuffer, &Max_size);
			if(retCode==ERROR_SUCCESS)
				{
				RegValue *RValue = new RegValue;
				RValue->DataType = myDataType;
				RValue->Value = szBuffer;
				RValue->Name = achValue;
				R->Values.push_back(RValue);
				}
		}
	}

	RegCloseKey(hKey);

return(ERROR_SUCCESS);
}


RegKey *RegKey::GetSubKey(string Name)
{

	for (Int32 i = 0; i < Keys.size(); i++)
	{
		if (Keys.at(i)->Name == Name)
		{
			return(Keys.at(i));
		}
	}

return(NULL);
}


RegValue *RegKey::GetValuebyName(string ValueName)
{
	for (Int32 i = 0; i < Values.size(); i++)
	{
		if (Values.at(i)->Name == ValueName)
		{
			return(Values.at(i));
		}
	}

return(NULL);
}

