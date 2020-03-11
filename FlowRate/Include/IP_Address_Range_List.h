#pragma once
#include <IP_Address_Range.h>


class IP_Address_Range_List : public vector<IP_Address_Range *>
{

private:

public:

	IP_Address_Range_List();
	~IP_Address_Range_List();
	
	bool Add(string IP_Address);
	bool Add(string Bottom, string Top);

	bool Contains(string IP);
	int Length();

};