#pragma once

#include <string>
#include <Registry.h>

#pragma comment(lib, "Advapi32.lib")

#define REG_NO_VALUE	-1

class RegValue
{

private:

protected:	  

public:

	RegValue();
	~RegValue();

	void	 *Value;
	DWORD	 DataType;
	string	 Name;

	/*
	DWORD	getType();
	bool	setValue(void *newValue);
	void	*getValue();
	void	setType(DWORD inType);
	void	setName(string Name);
	string 	getName();
	*/
};
