#pragma once
#include <vector>

using namespace std;


class Protocol
{

private:

public:

	enum Code
	{
		ICMP = 1,
		IGMP = 2,
		IPINIP = 4,
		TCP = 6,
		EGP = 8,
		IGP = 9,
		UDP = 17,
		RDP = 27,
		GRE = 47,
		ESP = 50,
		AH = 51,
		IPV6_ICMP = 58,
		VRRP = 112,
		ISIS = 124,
		ANY = 9999,
		NOT_SET = -1
	};

/*
#define TCP_FLAG_FIN			1
#define TCP_FLAG_SYN			2
#define TCP_FLAG_RST			4
#define TCP_FLAG_PUSH			8
#define TCP_FLAG_ACK			10
#define TCP_FLAG_URG			20
#define TCP_FLAG_ECE			40
#define TCP_FLAG_CWR			80
*/

	enum TCP_FLAGS
	{
		FLAG_FIN  = 1,
		FLAG_SYN = 2,
		FLAG_RST = 3,
		FLAG_PUSH = 8,
		FLAG_ACK = 10,
		FLAG_URG = 20,
		FLAG_ECE = 40,
		FLAG_CWR = 80
	};
	


	Protocol()
	{
	}

	static string Lookup(int P);	//Lookup a protocol and return its string
	static int Lookup(string P);	//Lookup a protocol and return its string

};






class Protocol_List : public vector <Int32>
{

private:

public:

	Protocol_List();
	~Protocol_List();

	bool Add(Int32 P);
	bool Remove(Int32 P);
	bool Contains(Int32 P) const;

	Protocol_List* Copy();


	friend bool operator== (const Protocol_List& A, const Protocol_List& B)
	{
		if (A.size() != B.size())
			return(false);

		for (unsigned int i = 0; i < A.size(); i++)
			{
			int Proto = A.at(i);
			if (!B.Contains(Proto))
				{
				return(false);
				}
			}

	return(true);
	}


	friend bool operator!= (const Protocol_List& A, const Protocol_List& B)
	{
		if (A == B)
			return(false);

	return(true);
	}


	void operator=(const Protocol_List& A)
	{
		//Clear the list first
		clear();

		for (unsigned int i = 0; i < A.size(); i++)
		{
			push_back(A.at(i));
		}
	}



};
