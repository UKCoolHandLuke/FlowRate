#include <Log.h>



//Initialise static
/*string  Log::filename = "Log.txt";
LogLevel Log::Verbosity = LogLevel::INFO;
bool Log::Echo = false;
*/

Log SystemLog("System.log");

Log::Log(string Filename)
{
	filename = Filename;
	setLogLevel(LogLevel::LOG_INFO);
}


Log::~Log()
{

}



//Static
bool Log::Write(char *Text, bool endline)
{

	File_Lock.Lock();

	stringstream ss;
	ofstream outfile;
	outfile.open(filename, std::ios_base::app);

	//Log the date/time
	chrono::system_clock::time_point p = chrono::system_clock::now();
	time_t t = chrono::system_clock::to_time_t(p);


	char str[26] = { 0 };
	memset(str, 0, sizeof(str));

	struct tm * lt = localtime(&t);
	strftime(str, sizeof(str), "%F %T", lt);

	ss << str;
	ss << ":- ";

	ss << Text;


	if (endline)
		ss << endl;

	outfile << ss.str();
	outfile.close();

	//if echo is enabled - echo it
	if (getEcho())
		cout << ss.str();

	File_Lock.Unlock();

	return(true);
}




//Static
bool Log::Write(string Text)
{
	return(Write((char *)Text.c_str(),false));
}

bool Log::Writeln(string Text)
{
	return(Write((char *)Text.c_str(), true));
}


bool Log::Write(char *Text)
{
	return(Write(Text, false));
}

bool Log::Writeln(char *Text)
{
	return(Write(Text, true));
}




/*
Ony Write if log level are correct
*/

bool Log::Writeln(char * Text, LogLevel L)
{
	if (getLogLevel() >= L)
	{
		Writeln(Text);
		return(true);
	}

return(false);
}



bool Log::Writeln(string Text, LogLevel L)
{
	return(Writeln((char *)Text.c_str(), L));
}





/*
LOGGING LEVELS
*/
//Static
LogLevel Log::getLogLevel()
{
	
	Verbosity_Lock.Lock();
		LogLevel Level = Verbosity;
	Verbosity_Lock.Unlock();

	return(Level);
}

//Static
void Log::setLogLevel(LogLevel L)
{
	Verbosity_Lock.Lock();
		Verbosity = L;
	Verbosity_Lock.Unlock();
}




bool Log::getEcho()
{
	return(Echo);
}

bool Log::setEcho(bool tf)
{
	Echo = tf;
	return (true);
}




