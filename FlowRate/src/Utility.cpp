#include <Utility.h>

int StringToInt(string Input)
{
	if (Input.size() > 0)
	{
		try
		{
			int Val = stoi(Input);
			return(Val);
		}
		catch (exception e)
		{
			//System::Logging.Writeln("Failed to convert int from: " + Input);
		}
	}
	return(INVALID_NUMBER);
}



string IntToString(Int32 Input)
{
	stringstream ss;
	ss << Input;
	return(ss.str());
}




string ExpandString(const char *sText...)
{
	va_list args;
	va_start(args, sText);
	stringstream ss;

	string remainder = sText;
	string placeholder = "";

	int length = 0;
	char identifier;

	size_t pos = remainder.find("%");

	while (pos != std::string::npos)
	{
		placeholder = remainder.substr(0, pos);
		ss << placeholder;

		length = (remainder.size() - (pos + 2));
		identifier = remainder[pos + 1];
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


