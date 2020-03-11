#include <Threshold.h>
#include <System.h>

Threshold::Threshold()
{
	Maximum = 0;
	Timeframe = 0;
	//BanLength = THRESHOLD_BAN_LENGTH_MIN;
}

Threshold::Threshold(long nTimeframe, long nLimit)
{
	if (!setLimit(nLimit))
		Maximum = 0;

	if (!setTimeframe(nTimeframe))
		Timeframe = 0;

	//if (!setBan_Length(Ban_Length))
	//	BanLength = THRESHOLD_BAN_LENGTH_MIN;
}



Threshold::~Threshold()
{
}


bool Threshold::setTimeframe(long newTimeframe)
{
	if (newTimeframe < THRESHOLD_TIMEFRAME_MAX)
	{
		Timeframe = newTimeframe;
		return(true);
	}
	else
	{
		System::Logging.Writeln("Threshold timeframe exceeds maximum allowed",LogLevel::LOG_INFO);
	}

	return(false);
}


bool Threshold::setLimit(long newLimit)
{
	if (newLimit < THRESHOLD_LIMIT_MAX)
	{
		Maximum = newLimit;
		return(true);
	}
	else
	{
		System::Logging.Writeln("Threshold limit exceeds maximum allowed", LogLevel::LOG_INFO);
	}

return(false);
}

/*
bool Threshold::setBan_Length(long Value)
{
	if ((Value < THRESHOLD_BAN_LENGTH_MAX) && Value > THRESHOLD_BAN_LENGTH_MIN)		//minimum value of 1 minute
	{
		BanLength = Value;
		return(true);
	}

return(false);
}
*/

/*
long Threshold::getBan_Length()
{
	return(BanLength);
}
*/

long Threshold::getTimeframe()
{
	return(Timeframe);
}

long Threshold::getLimit()
{
	return(Maximum);
}


//Created a copy of a threshold base data
Threshold *Threshold::Copy()
{
	Threshold *T = new Threshold();
	T->setLimit(this->getLimit());
	T->setTimeframe(this->getTimeframe());
	//T->setBan_Length(this->getTimeframe());

return(T);
}