#include <IP_Address.h>
#include <IPv4_Address.h>
#include <IPv6_Address.h>

IP_Address::IP_Address()
{
	sIP = "";
	Base_Object = NULL;
}

IP_Address::IP_Address(string IP)
{
	//Set the IP
	Base_Object = NULL;
	Set(IP);
}


IP_Address::~IP_Address()
{
	if (Base_Object != NULL)
		delete Base_Object;
}

//Static
IP_Address *IP_Address::Create(string IP)
{
	if (IPv4_Address::IsValid(IP))
		{
		IPv4_Address *A = new IPv4_Address(IP);
		return(A);
		}
	if (IPv6_Address::IsValid(IP))
		{
		IPv6_Address *A = new IPv6_Address(IP);
		return(A);
		}

return(NULL);
}

//Static
bool IP_Address::IsValid(string IP)
{
	return(false);
}



string IP_Address::Get()
{
	if (Base_Object != NULL)
		return(Base_Object->Get());
	
	return("");
}

bool IP_Address::Set(string IP)
{
	if (Base_Object != NULL)
		delete Base_Object;
	
	Base_Object = IP_Address::Create(IP);
	return(false);
}

bool IP_Address::Split(string IP, char delim, Int32 max_split_count, vector<string> *Output)
{
	stringstream ss(IP);
	string token;
	vector<string> IP_Segments;

	while (std::getline(ss, token, delim))
	{
		IP_Segments.push_back(token);
	}

	if (IP_Segments.size() >= max_split_count)
	{
		if (Output != NULL)
		{
			Output->clear();
			for (Int32 i = 0; i < max_split_count; i++)
			{
				Output->push_back(IP_Segments[i]);
			}
			return(true);
		}
	}

	return(false);
}


char *IP_Address::to_char()
{
	return((char *)sIP.c_str());
}


int IP_Address::length()
{
	return(sIP.size());
}




//Assignment operator
IP_Address IP_Address::operator=(IP_Address& A)
{
	Set(A.Get());
	return(*this);
}

//Comparison Operator
bool IP_Address::operator==(IP_Address& A)
{
	if (A.Get() == Get())
		return(true);

return(false);
}

//Not Comparison Operator
bool IP_Address::operator!=(IP_Address& A)
{
if (this->Get() != A.Get())
	return(true);

return(false);
}


//Greater than comparison (virtual)
bool IP_Address::operator>(IP_Address& A)
{
	if(this->Get() > A.Get())
		return(true);

	return(false);
}

//Greater than or equal comparison (virtual)
bool IP_Address::operator>=(IP_Address& A)
{
	if (this->Get() >= A.Get())
		return(true);

	return(false);
}

//less than Comparison Operator
bool IP_Address::operator<(IP_Address& A)
{
	if (A.Get() < this->Get())
		return(false);

	return(true);
}

//less than or equal Comparison Operator
bool IP_Address::operator<=(IP_Address& A)
{
	if (this->Get() <= A.Get())
		return(true);

	return(false);
}



//Comparison with char array (IP address)
bool IP_Address::operator== (const char A[])
{
	string sA = A;
	if (this->Get() == sA)
		return(true);

return(false);
}


//Comparison with char array (IP address)
bool IP_Address::operator!= (const char A[])
{
	string sA = A;
	if (this->Get() == sA)
		return(false);

	return(true);
}




