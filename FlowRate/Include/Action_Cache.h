#pragma once

#include <IPRange.h>
#include <TimeStamp.h>

class Action_Cache
{

private:

public:
	
	IPV4Address HostAddress;	//Address of the host
	long		LastActionTime;	//last action time epoch


	Action_Cache();
	~Action_Cache();
};


class Action_Cache_List : vector <Action_Cache *>
{

private:

	bool Add(IPV4Address Host);
	Action_Cache *GetElement(IPV4Address Host);

public:

	Action_Cache_List();
	~Action_Cache_List();

	bool Clear();
	bool Update(IPV4Address Host);
	bool Remove(IPV4Address Host);
	long GetLastExecute(IPV4Address Host);

};
