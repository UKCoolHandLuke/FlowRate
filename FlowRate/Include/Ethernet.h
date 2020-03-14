#pragma once



#define ETHERNET_IPV4	2048
#define ETHERNET_IPV6	34525

#define ETHERNET_ARP	2054


#define ETHERNET_FRAME_LENGTH_BOUNDARY	1535	//Values below this are defined as frame size, anything above will define a passenger protocol



struct Ethernet_Header
{
	unsigned char	dmac[6];
	unsigned char	smac[6];
	unsigned short	type;
	unsigned char	payload[];
};


//Convert a single decimal value into a hex one
string DecimalToHex(Int32 Value)
{
	
	stringstream ss;
	ss << std::hex << Value;
	return(ss.str());
}


string DecimalToMacAddress(unsigned char Values[6])
{
	stringstream ss;

	for (int i = 0; i < 5; i++)
	{
		string val = DecimalToHex(Values[i]);
		if (val.length() == 1)
			val = "0" + val;

		ss << val;
		ss << ":";
	}

	ss << DecimalToHex(Values[5]);

	return(ss.str());
}


unsigned int ToLittleEndian(unsigned int Input)
{
	//unsigned int x = Input;
	int valueShifted = (Input << 8) | (Input >> 8);
	return(valueShifted);
}