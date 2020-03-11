#pragma once
#include <vector>
#include <IP_Address.h>

#define IP_ADDRESS_LIST_MAXIMUM	1024

class IP_Address_List : vector<IP_Address *>
{

private:

public:

	IP_Address_List();
	~IP_Address_List();

	bool Add(string A);
	bool Remove(string A);
	bool Contains(string A);
	bool Clear();
};