// Testbed.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <stdarg.h>
#include <sstream>

using namespace std;

string ExpandString(const char *sText...);

int main()
{
	string H = "Hello";
	cout << ExpandString("Hello %s %d World",H, 5);
	
}


string ExpandString(const char *sText...)
{
	va_list args;
	va_start(args, sText);
	stringstream ss;

	string remainder = sText;
	string placeholder = "";

	int length=0;
	char identifier;

	size_t pos = remainder.find("%");
	
	while (pos != std::string::npos)
	{
		placeholder = remainder.substr(0, pos);
		ss << placeholder;

		length = (remainder.size() - (pos+2));
		identifier = remainder[pos+1];
		//lets fingure out what we should be expanding
		switch (identifier)
		{
		case 's':
			ss << va_arg(args, string);
			break;
		case 'd':
			ss << va_arg(args, int);
			break;
		case 'f':
			ss << va_arg(args, double);
			break;
		case 'c':
			ss << va_arg(args, char);
			break;

		default:
			ss << "%" << identifier;
			break;
		}
		remainder = remainder.substr(pos + 2, length);
		pos = remainder.find("%");
	}
	
	ss << remainder;

	va_end(args);
	return(ss.str());
}
