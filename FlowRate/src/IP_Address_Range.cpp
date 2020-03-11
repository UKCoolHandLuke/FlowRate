#include <IP_Address_Range.h>

IP_Address_Range::IP_Address_Range()
{
	BottomRange = NULL;
	TopRange = NULL;
}


IP_Address_Range::IP_Address_Range(string IP)
{
	BottomRange = NULL;
	TopRange = NULL;
	Set(IP, IP);
}

IP_Address_Range::IP_Address_Range(string Address_Bottom, string Address_Top)
{
	BottomRange = NULL;
	TopRange = NULL;
	Set(Address_Bottom, Address_Top);
}



IP_Address_Range::~IP_Address_Range()
{
	if (BottomRange == TopRange)
		delete BottomRange;
	else
		{
		delete BottomRange;
		delete TopRange;
		}	

}

// this will fail as the assignments need to be specific to each address type (IPv4 vs IPv6)
bool IP_Address_Range::Set(IP_Address *Bottom, IP_Address *Top)
{
	if (Top != NULL && Bottom != NULL)
	{
		if (*Top > *Bottom)
		{
			return(Set(Bottom->Get(), Top->Get()));
		}
	}

	return(false);
}

bool IP_Address_Range::Set(string Address_Bottom, string Address_Top)
{
	bool result = false;

	if (BottomRange != NULL)
		delete BottomRange;
	if (TopRange != NULL)
		delete TopRange;

	BottomRange = IP_Address::Create(Address_Bottom);
	TopRange = IP_Address::Create(Address_Top);
	if ((BottomRange != NULL) && (TopRange != NULL))
		result = true;

return(result);
}


bool IP_Address_Range::IsInRange(string IP)
{
	bool result = false;

	if (BottomRange == NULL || TopRange == NULL)
		return(false);

	IP_Address *A = IP_Address::Create(IP);

	if ((*A >= *BottomRange) && (*A <= *TopRange))
		result = true;

	delete A;
	return(result);
}
