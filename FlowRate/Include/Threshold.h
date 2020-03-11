#pragma once


#define THRESHOLD_TIMEFRAME_MAX		86400	//Maximum time of 24 hour for testing
#define THRESHOLD_LIMIT_MAX			10000	//Maximum hitrate of 10000
#define THRESHOLD_BAN_LENGTH_MAX	86400	//Maximum Ban Time of 24 hours
#define THRESHOLD_BAN_LENGTH_MIN	1		//Minimum Ban Time of 1 second


class Threshold 
{

private:

	long Timeframe;
	long Maximum;
	//long BanLength;

public:


	Threshold();
	Threshold(long nTimeframe, long nLimit);
	~Threshold();

	bool setTimeframe(long newTimeframe);
	bool setLimit(long newLimit);
	//bool setBan_Length(long Value);

	long getTimeframe();
	long getLimit();
	//long getBan_Length();
	Threshold *Copy();



};

