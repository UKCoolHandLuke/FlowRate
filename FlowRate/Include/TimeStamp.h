#pragma once

#include <iostream>
#include <ctime>
#include <string>

using namespace std;


typedef unsigned int EpocTime;


class TimeStamp
{

private:

	time_t Stamp;
	static TimeStamp *Instance;

public:

	TimeStamp();
	~TimeStamp();

	static TimeStamp *getInstance();

	void Now();						//take a snapshot of the time now
	string toString(int i);			//Pad and convert value to string

	//Allows to get current epoc
	static long CurrentEpoc();
	static string EpochToString(const time_t T);
	bool SetEpoc(EpocTime Newtime);
	EpocTime GetEpoc();				//return the epoc in seconds since Jan 1 1970
	string 	GetHumanTime();			//Return the time in human readable form
};


