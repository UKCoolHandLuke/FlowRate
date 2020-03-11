#include <iostream>
#include <list>
#include <GlobalTypes.h>
#include <IPRange.h>
#include <string>

using namespace std;

IPV4Address::IPV4Address()
{
	Set(0, 0, 0, 0);
}

IPV4Address::IPV4Address(string IP)
	{
		Set(IP);
	}

IPV4Address::IPV4Address(Int32 Sections[4])
	{
		Set(Sections);
	}

IPV4Address::~IPV4Address()
	{
	}

bool IPV4Address::isValid(Int32 a, Int32 b, Int32 c, Int32 d)
{
	if ((a >= 0 && a < 256) && (b >= 0 && b < 256) && (c >= 0 && c < 256) && (d >= 0 && d < 256))
	{
		return(true);
	}

return(false);
}

bool IPV4Address::Set(Int32 a, Int32 b, Int32 c, Int32 d)
{
	if (isValid(a, b, c, d))
	{
		Section[0] = a;
		Section[1] = b;
		Section[2] = c;
		Section[3] = d;

		Convert_to_char(IPv4_char);

		//IPv4_string.assign(IPv4_char);
		//Set our string holder

		return(true);
	}

return(false);
}

bool IPV4Address::Set(Int32 Sections[4])
{
	return(Set(Sections[0], Sections[1], Sections[2], Sections[3]));
}

bool IPV4Address::Set(string IP)
{
	//Split the string by dotted decimals
	//Then do call Set
	
	Int32 Result[4] = {0,0,0,0};
	Int32 cnt = 0; 

	char *pch;
	pch = strtok((char *)IP.c_str(), ".");

	while (pch != NULL && cnt < 4)
	{
		Result[cnt] = atoi(pch);	
		pch = strtok(NULL, ".");
		cnt++;
	}

	//Only set if we have 4 sections
	if (cnt == 4)
		{
		return(Set(Result));
		}

	return(false);
}

bool IPV4Address::Set(IPV4Address *IP)
{
	return(Set(IP->Section));
}


IPV4Address IPV4Address::operator=(const IPV4Address& A)
{
	Set(A.Section[0], A.Section[1], A.Section[2], A.Section[3]);
	return IPV4Address(A);
}


string IPV4Address::to_string() const
{
	string IPv4_string = IPv4_char;
	return(IPv4_string);
}

char *IPV4Address::to_char()
{
	return(IPv4_char);
}

void IPV4Address::Convert_to_char(char *Buffer) 
{
	char *IP;
	char FullIP[16];

	memset(FullIP, NULL, sizeof(FullIP));	//clear out our buffer

	IP = new char[4];

	//string *S;
	//S = new string();

	int FullIPPos = 0;

	for (int i = 0; i < 4; i++)
	{
		memset(IP, NULL, sizeof(IP));
		itoa(Section[i], IP, 10);
		strncpy(&FullIP[FullIPPos], IP, strlen(IP));
		FullIPPos += strlen(IP);
		//S->append(IP);
		if (i < 3)
			{
			//S->append(".");
			FullIP[FullIPPos] = '.';
			FullIPPos++;
			}
	}


	//if (IPv4_char != NULL)
	//	delete IPv4_char;

	//char *New_IP = new char[strlen(FullIP)+1];
	memset(Buffer, NULL, sizeof(FullIP)+1);
	strncpy(Buffer,FullIP,strlen(FullIP));
	delete IP;
}




int IPV4Address::Length() const
{
	return(to_string().length());
}









IPV4Range::IPV4Range()
{
	BottomRange = new IPV4Address();
	TopRange = new IPV4Address();
}

IPV4Range::~IPV4Range()
{

	//Cleanup of all ip addresses in the list needs to be done

	if (BottomRange == TopRange)
		delete BottomRange;
	else
		{
		delete BottomRange;
		delete TopRange;
		}
	
}

bool IPV4Range::Set(IPV4Address *Bottom, IPV4Address *Top) 
{
	if (Top != NULL && Bottom != NULL)
	{
		if (*Top > *Bottom)
		{
			BottomRange->Set(Bottom);
			TopRange->Set(Top);
			return(true);
		}
	}

return(false);
}

bool IPV4Range::Set(string Address_Bottom, string Address_Top)
{
	return(Set(new IPV4Address(Address_Bottom), new IPV4Address(Address_Top)));
}



bool IPV4Range::IsInRange(IPV4Address *IP)
{
	if (IP != NULL)
	{

		if (*IP < *TopRange)
		{
			if (*IP > *BottomRange)
			{
				return(true);
			}
		}

	}

return(false);
}




IPV4Range_List::IPV4Range_List()
{
}

IPV4Range_List::~IPV4Range_List()
{
	while(this->size()>0)
	{
		IPV4Range *R = this->front();
		this->erase(this->begin());
		delete R;
	}
}


bool IPV4Range_List::Contains(IPV4Address *Address)
{
	IPV4Range *R;

	for (Int32 i = 0; i < this->size(); i++)
	{
		R = (IPV4Range *) this->at(i);

		if (R != NULL)
		{
			if (R->IsInRange(Address))
			{
				return(true);
			}
		}

	}

return(false);
}

bool IPV4Range_List::Contains(string Address)
{
	IPV4Address *A = new IPV4Address(Address);
	bool Result = Contains(A);
	delete A;
	return(Result);
}


//Shortcut to add single IP address
bool IPV4Range_List::Add(IPV4Address *Address)
{
	if (Address == NULL)
		return(false);

	IPV4Range *Range = new IPV4Range();
	Range->BottomRange = Address;		//shared address - be careful when deleting
	Range->TopRange = Address;			//shared address 
	push_back(Range);

	return(true);
}


//Add a range of IP addresses
bool IPV4Range_List::Add(IPV4Address *Address_Bottom, IPV4Address *Address_Top)
{
	if (Address_Bottom == NULL || Address_Top == NULL)
		return(false);

	IPV4Range *Range = new IPV4Range();
	Range->BottomRange = Address_Bottom;
	Range->TopRange = Address_Top;
	push_back(Range);

	return(true);
}




bool IPV4Range_List::Add(string Address)
{
	//return(Add(new IPV4Address(Address)));
	return(Add(new IPV4Address(Address)));
}


bool IPV4Range_List::Add(string Address_Bottom, string Address_Top)
{
	//this is not correct
	return(false);
	//return(Add(Address_Bottom,Address_Top));
}


bool IPV4Range_List::Add(IPV4Range *RangeList)
{
	push_back(RangeList);
	return(true);
}