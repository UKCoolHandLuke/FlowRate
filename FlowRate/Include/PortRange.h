#pragma once
#include <iostream>
#include <vector>

#include <GlobalTypes.h>

using namespace std;


//Define Global Port meanings
#define PORT_ANY		-1
#define PORT_NOT_SET	0


/*
Defines a range of ports
*/

class Port
{

private:

	Int32 _Port;

public:

	Port();
	Port(Int32 P);
	Int32 get() const;
	bool set(Int32 P);

	bool isInRange(Int32 P);		//Check if a port is within the port range without setting
	bool isSet();					//Determine if a port has a value assigned
};

struct Simple_Port_Range
{
	Int32 Min;
	Int32 Max;
};



class PortRange
{

private:
	Port _Bottom;
	Port _Top;

public:
	PortRange();
	PortRange(Int32 Min, Int32 Max);
	~PortRange();
	bool SetRange(Int32 Min, Int32 Max);
	bool SetRange(Port *Min, Port *Max);

	bool IsInRange(Int32 P);
	Simple_Port_Range GetRange() const;

	friend bool operator== (const PortRange& A, const PortRange& B)
	{

		Simple_Port_Range ARange = A.GetRange();
		Simple_Port_Range BRange = B.GetRange();

		if (ARange.Min == BRange.Min)
		{
			if (ARange.Max == BRange.Max)
			{
				return(true);
			}
		}

	return(false);
	}


};




/*
Defines a list of port ranges
*/
class PortRange_List : public vector <PortRange *>
{

private:

public:

	PortRange_List();
	~PortRange_List();

	bool Add(Port P);			//Add a single port
	bool Contains(Port P) const;

	// Overloading of Assignment Operator
	//void operator=(const PortRange_List &M);

	PortRange_List* Copy();

	friend bool operator== (const PortRange_List& A, const PortRange_List& B)
	{

		bool result;

		if (A.size() != B.size())
			return(false);

		for (unsigned int i = 0; i < A.size(); i++)
		{
			PortRange *A_PR = A.at(i);
			result = false;
			for (unsigned int j = 0; j < B.size(); j++)
			{
				PortRange *B_PR = B.at(j);
				if (*B_PR == *A_PR)
					result = true;
			}

			if (result == false)
				return(false);
		}

		return(true);
	}


	friend bool operator!= (const PortRange_List& A, const PortRange_List& B)
	{
		if (A == B)
			return(false);

		return(true);
	}

};

