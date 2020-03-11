#include <TimeStamp.h>
#include <sstream>

TimeStamp *TimeStamp::Instance = NULL;

TimeStamp::TimeStamp()
{
	Now();
}

TimeStamp::~TimeStamp()
{
}

TimeStamp *TimeStamp::getInstance()
{
	if (Instance == NULL)
		Instance = new TimeStamp;

	Instance->Now();	//update our timestamp
	return(Instance);
}

void TimeStamp::Now()
{
	Stamp = time(0);
}

EpocTime TimeStamp::GetEpoc()
{
	return(Stamp);
}

string 	TimeStamp::GetHumanTime()
{
	tm *ltm = localtime(&Stamp);
	stringstream ss;

	//Convert everything to a string
	//The year since 1900 so we need to remove 100 years

	ss << toString(ltm->tm_mday) << "/" << toString((ltm->tm_mon)+1) << "/" << toString((ltm->tm_year)-100);
	ss << " ";
	ss << toString(ltm->tm_hour) << ":" << toString(ltm->tm_min) << ":" << toString(ltm->tm_sec);
	
	return(ss.str());
}

//Static
long TimeStamp::CurrentEpoc()
{
	TimeStamp T;
	return(T.GetEpoc());
}



string TimeStamp::toString(int i)
{

	stringstream ss;

	if (i < 10)
		ss << "0" << i;
	else
		ss << i;

return(ss.str());
}


bool TimeStamp::SetEpoc(EpocTime Newtime)
{
	if (Newtime > 0)
		Stamp = Newtime;
	else
		return(false);

return(true);
}

//Static
string TimeStamp::EpochToString(const time_t T)
{
	stringstream ss;
	tm *Time = std::localtime(&T);
	ss << Time->tm_hour << ":" << Time->tm_min << ":" << Time->tm_sec << " " << Time->tm_mday << "/" << (Time->tm_mon + 1) << "/" << (Time->tm_year + 1900);
	return(ss.str());
}
