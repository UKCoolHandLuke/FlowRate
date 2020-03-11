#pragma once
#include <IP_Address.h>


class IPv6_Address : public IP_Address
{
private:

	const Int32 Segment_Count = 3;

public:

	IPv6_Address() : IP_Address()
	{
	}

	IPv6_Address(string IP)
	{
	}


	//Set the ip address
	bool Set(string IP)
	{
		//Split the string by dotted decimals
		//Then do call Set

		/*

		if (Split(IP, ':', 8))
		{
			string FullString = "";

			for (Int32 i = 0; i < Segment_Count - 1; i++)
			{
				FullString += Segment[i];
				FullString += ".";
			}
			FullString += Segment[Segment_Count - 1];
			IP = FullString;
			return(true);
		}
		*/
		return(false);
	}


	//Set the ip address
	string Get()
	{
		return("");
	}


};