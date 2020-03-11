/*
19-11-2019
Allows the creation of a list of custom random of IP Addresses
Has a Maxmum allowed list size (currently set at 1024 entries)
*/


#include <IP_Address_List.h>

IP_Address_List::IP_Address_List()
{

}

IP_Address_List::~IP_Address_List()
{

}



bool IP_Address_List::Add(string A)
{
	if (this->size() < IP_ADDRESS_LIST_MAXIMUM)
	{
		this->push_back(new IP_Address(A));
		return(true);
	}

return(false);
}


bool IP_Address_List::Remove(string A)
{
	for (Int32 i = 0; i < this->size(); i++)
	{
		IP_Address *n = *(this->begin() + i);
		if (n->Get() == A)
		{
			this->erase(this->begin() + i);
			delete n;
			return(true);
		}
	}

return(false);
}


bool IP_Address_List::Contains(string A)
{
	for (Int32 i = 0; i < this->size(); i++)
	{
		IP_Address *n = *(this->begin() + i);
		if (n->Get() == A)
		{
			return(true);
		}
	}

	return(false);
}

bool IP_Address_List::Clear()
{
	while (this->size() > 0)
		{
		IP_Address *n = *(this->begin());
		this->erase(this->begin());
		delete n;
		}

return(true);
}


