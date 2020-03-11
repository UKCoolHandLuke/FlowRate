#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <GlobalTypes.h>
#include <sstream>

using namespace std;


#define IPV4_ANY_ADDRESS	"0.0.0.0"

/*
Defines a single IP Address
*/
class IPV4Address
{

private:
	Int32	Section[4];
	char	IPv4_char[20];	//Shoud be max 16
	//string	IPv4_string;
	bool isValid(Int32 a, Int32 b, Int32 c, Int32 d);
	
	//convert the IP to a char
	void Convert_to_char(char *Buffer);

public:

	IPV4Address();

	IPV4Address(string IP);

	IPV4Address(Int32 Sections[4]);

	~IPV4Address();

	bool Set(Int32 a, Int32 b, Int32 c, Int32 d);
	bool Set(Int32 Sections[4]);
	bool Set(string IP);
	bool Set(IPV4Address *IP);


	//Comparison Operators
	friend bool operator< (const IPV4Address& A, const IPV4Address& B)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!(A.Section[i] <= B.Section[i]))
				return(false);
		}

		return(true);
	}



	//Comparison Operators
	friend bool operator> (const IPV4Address& A, const IPV4Address& B)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!(A.Section[i] >= B.Section[i]))
				return(false);
		}

		return(true);
	}

	IPV4Address operator=(const IPV4Address& A);
	

	//Comparison Operators ==
	friend bool operator== (const IPV4Address& A, const IPV4Address& B)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!(A.Section[i] == B.Section[i]))
				return(false);
		}

		return(true);
	}



	//Convert from IP to string
	friend std::ostream& operator<<(std::ostream &out, const IPV4Address &A)
	{
		//stringstream ss;
		//ss << A.to_string();
		out << A.to_string();
		return(out);
	}

	string to_string() const;
	char *to_char();
	int Length() const;
};



/*
Defines a range or single IP Address
*/
class IPV4Range
{

private:


public:

	IPV4Address *BottomRange;
	IPV4Address *TopRange;

	IPV4Range();
	~IPV4Range();

	bool Set(IPV4Address *Top, IPV4Address *Bottom);
	bool Set(string Address_Bottom, string Address_Top);
	bool IsInRange(IPV4Address *IP);

};



/*
Defines a list of IP Ranges or single IP's
*/
class IPV4Range_List : public vector <IPV4Range *>
{

private:


public:

	IPV4Range_List();
	~IPV4Range_List();

	bool Add(IPV4Address *Address);
	bool Add(string Address);
	bool Add(IPV4Address *Address_Bottom,IPV4Address *Address_Top);
	bool Add(string Address_Bottom, string Address_Top);
	bool Add(IPV4Range *RangeList);

	bool Contains(IPV4Address *Address);
	bool Contains(string Address);

};


