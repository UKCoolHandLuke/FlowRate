#pragma once
#include <IP_Address.h>

constexpr auto ERROR = -1;

class IPv4_Address : public IP_Address
{
private:

	const Int32 Segment_Count = 4;
	
	static Int32 ToInt(string input)
	{
		Int32 Value = 0;
		Value = atoi(input.c_str());
		return(Value);
	}



public:

	IPv4_Address() : IP_Address()
	{
	}

	IPv4_Address(string IP)
	{
		Set(IP);
	}

	//Static
	static bool IsValid(string IP)
	{
		const int IPV4_SEGMENT_COUNT = 4;
		vector<string> Output;
		int Value = 0;
		//Split the string by dotted decimals
		//Then do call Set
		if (Split(IP, '.', 4, &Output))
		{
			if (Output.size() == IPV4_SEGMENT_COUNT)
			{
				for (int i = 0; i < IPV4_SEGMENT_COUNT; i++)
				{
					Value = ToInt(Output[i]);
					if ((Value < 0) || (Value > 255))
					{
						return(false);
					}
				}
				return(true);
			}
		}

		return(false);
	}


	//Set the ip address
	bool Set(string IP)
	{
		vector<string> Output;
		//Split the string by dotted decimals
		//Then do call Set
		if (Split(IP, '.', 4, &Output))
			{
				string FullString = "";

				if (IsValid(IP))
				{
					for (Int32 i = 0; i < Segment_Count - 1; i++)
					{
						Segment[i] = Output[i];
						FullString += Segment[i];
						FullString += ".";
					}
					Segment[Segment_Count - 1] = Output[Segment_Count - 1];
					FullString += Segment[Segment_Count - 1];
					sIP = FullString;
					return(true);

				}
			}
	return(false);
	}


	//Get the ip address
	string Get()
	{
		return(sIP);
	}



	static Int32 IPv4ToDecimal(string IP)
	{
		Int32 FullValue = 0;

		vector<string> Me;
		if (Split(IP, '.', 4, &Me))
		{
			
			FullValue = 16777216 * ToInt(Me[0]);
			FullValue += 65536 * ToInt(Me[1]);
			FullValue += 256 * ToInt(Me[2]);
			FullValue += ToInt(Me[3]);
			return(FullValue);
		}

	return(ERROR);
	}


	virtual bool operator> (IP_Address& A)
	{
		Int32 MyIP = IPv4ToDecimal(sIP);
		Int32 AIP = IPv4ToDecimal(A.Get());

		if (MyIP > AIP)
			return(true);

		return(false);
	}

	virtual bool operator>= (IP_Address& A)
	{
		Int32 MyIP = IPv4ToDecimal(sIP);
		Int32 AIP = IPv4ToDecimal(A.Get());

		if (MyIP >= AIP)
			return(true);

		return(false);
	}


	virtual bool operator< (IP_Address& A)
	{
	Int32 MyIP = IPv4ToDecimal(sIP);
	Int32 AIP = IPv4ToDecimal(A.Get());

	if (MyIP < AIP)
		return(true);

	return(false);
	}

	virtual bool operator<=(IP_Address& A)
	{
		Int32 MyIP = IPv4ToDecimal(sIP);
		Int32 AIP = IPv4ToDecimal(A.Get());

		if (MyIP <= AIP)
			return(true);

		return(false);
	}

	   
	
};
