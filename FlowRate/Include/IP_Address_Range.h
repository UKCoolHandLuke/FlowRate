#pragma once
#include <IP_Address.h>

class IP_Address_Range
{

private:

	IP_Address *BottomRange;
	IP_Address *TopRange;

public:

	IP_Address_Range();
	IP_Address_Range(string IP);
	IP_Address_Range(string Address_Bottom, string Address_Top);
	~IP_Address_Range();


	bool Set(IP_Address *Top, IP_Address *Bottom);
	bool Set(string Address_Bottom, string Address_Top);
	bool IsInRange(string IP);

};