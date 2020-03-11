#include <Action_Cache.h>

Action_Cache::Action_Cache()
{
	HostAddress.Set("0.0.0.0");
}

Action_Cache::~Action_Cache()
{
}


/******************************************************************************************
Action Cache List Class
*******************************************************************************************/

Action_Cache_List::Action_Cache_List() 
{
}

Action_Cache_List::~Action_Cache_List()
{
	Clear();
}


Action_Cache *Action_Cache_List::GetElement(IPV4Address Host)
{

	for (std::vector<Action_Cache *>::iterator it = this->begin(); it != this->end(); ++it)
	{
		Action_Cache *ac = *it;
		if (ac->HostAddress == Host)
		{
			return(ac);
		}
	}

return(NULL);
}


bool Action_Cache_List::Clear()
{
	//Remove all elements from our list
	while (size() > 0)
	{
		Action_Cache *ac = back();
		this->pop_back();
		delete ac;
	}

return(true);
}

bool Action_Cache_List::Add(IPV4Address Host)
{
	TimeStamp T;
	Action_Cache *A = new Action_Cache();
	A->HostAddress = Host;
	A->LastActionTime = T.GetEpoc();
	this->push_back(A);
	return(true);
}

bool Action_Cache_List::Remove(IPV4Address Host)
{
	
	for (std::vector<Action_Cache *>::iterator it = this->begin(); it != this->end(); ++it)
	{
		Action_Cache *ac = *it;
		if (ac->HostAddress == Host)
			{
			this->erase(it);
			delete ac;
			return(true);
			}
	}

return(false);
}


bool Action_Cache_List::Update(IPV4Address Host)
{

	Action_Cache *ac = GetElement(Host);
	if (ac != NULL)
	{
		TimeStamp T;
		ac->LastActionTime = T.GetEpoc();
		return(true);
	}
	
	//We don't have the elemeent in our list - lets add it
	return (Add(Host));
}




long Action_Cache_List::GetLastExecute(IPV4Address Host)
{

	Action_Cache *ac = GetElement(Host);
	if (ac != NULL)
	{
		TimeStamp T;
		return(ac->LastActionTime);
	}

	//We don't have the elemeent in our list - return(0)
	return (0);
}

