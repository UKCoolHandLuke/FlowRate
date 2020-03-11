#include <IP_Address_Range_List.h>


IP_Address_Range_List::IP_Address_Range_List()
{
}

IP_Address_Range_List::~IP_Address_Range_List()
{
	//clean up the list
	for (Int32 i = 0; i < this->size(); i++)
	{
		IP_Address_Range *R = *this->begin();
		erase(this->begin());
		delete R;
	}
}

bool IP_Address_Range_List::Add(string IP)
{
	IP_Address_Range *R = new IP_Address_Range(IP);
	this->push_back(R);
	return(true);
}

bool IP_Address_Range_List::Add(string Bottom, string Top)
{
	IP_Address_Range *R = new IP_Address_Range(Bottom,Top);
	this->push_back(R);
	return(true);
}


bool IP_Address_Range_List::Contains(string IP)
{

	for (std::vector<IP_Address_Range*>::iterator it = begin(); it != end(); ++it)
	{
		IP_Address_Range *IPRangeList = *it;
		if (IPRangeList->IsInRange(IP))
		{
			return(true);
		}
	}

return(false);
}


int IP_Address_Range_List::Length()
{
	return(this->size());
}
