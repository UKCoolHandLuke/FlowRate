#include <System.h>


//Static init
Log System::Logging("System.log");

System::System()
{
	
}

System::~System()
{
}

double System::getVersionDouble()
{
	return(VERSION_NUMBER);
}

string System::getVersionString()
{
	return(to_string(VERSION_NUMBER));
}

void System::Exit(string Message)
{
	stringstream ss;
	ss << "Application Exit with Message: " << Message;
	Logging.Writeln(ss.str());
	exit(0);
}




