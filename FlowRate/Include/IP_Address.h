#pragma once
#include <string>
#include <sstream>
#include <vector>

typedef unsigned int Int32;

using namespace std;

class IP_Address
{

protected:
	string Segment[8];
	string sIP;
	Int32 Version;

	static bool Split(string IP, char delim, Int32 max_split_count, vector<string> *Output);
	char *to_char();
	int length();
	   	 
	IP_Address *Base_Object;

public:

	IP_Address();
	IP_Address(string IP);
	~IP_Address();

	static IP_Address *Create(string IP);
	static bool IsValid(string IP);

	virtual string Get();
	virtual bool Set(string IP);
	
	//Overloaders
	IP_Address operator=(IP_Address& A);
	bool operator== (IP_Address& A);
	bool operator!= (IP_Address& A);
	virtual bool operator> (IP_Address& A);
	virtual bool operator>= (IP_Address& A);
	virtual bool operator< (IP_Address& A);
	virtual bool operator<= (IP_Address& A);

	bool operator== (const char A[]);
	bool operator!= (const char A[]);

};


