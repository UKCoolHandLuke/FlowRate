#pragma once

#include <Threshold.h>
#include <Threshold_Trigger.h>
#include <MatchCache.h>
#include <vector>
#include <Log.h>
#include <Semaphore.h>

using namespace std;

#define THRESHOLD_NONE	-100

//List of thresholds
//Must be in order of length
//When checking we must do it cumulatively (shortest timeframe+next+longest)

class Threshold_List
{

private:

	vector <Threshold *> Thresholds;
	Semaphore List_Lock;

public:

	Threshold_List();
	~Threshold_List();

	bool Add(Threshold *T);
	bool Remove(Threshold *T);

	//Check if a threshold has been reached for a given src IP
	Threshold_Trigger *CheckLimits(Host *M);

	//Clean the related host cache based on threshold limits
	unsigned int CleanList(Host *M);

	long GetLongestThreshold();		//return the longest threshold, to help with scrubbing old packets (only the longest timeframe matters)

};