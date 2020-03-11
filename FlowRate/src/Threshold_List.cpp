#include <Threshold_List.h>



Threshold_List::Threshold_List()
{

}


Threshold_List::~Threshold_List()
{
	while (Thresholds.size() > 0)
	{
		Threshold *T = Thresholds.front();
		Thresholds.erase(Thresholds.begin());
		delete T;
	}
}

//Add a threshold
bool Threshold_List::Add(Threshold *T)
{

	//We need to add in order of time
	/************************************
	Needs testing and fixing
	*************************************/
	List_Lock.Lock();
		for (Int32 i = 0; i < Thresholds.size(); i++)
		{
			if (T->getTimeframe() < Thresholds[i]->getTimeframe())
			{
				Thresholds.insert(Thresholds.begin() + i, T);
				List_Lock.Unlock();
				return(true);
			}
		}

	Thresholds.push_back(T);
	
	List_Lock.Unlock();

	return(true);
}

//Remove a threshold
bool Threshold_List::Remove(Threshold *T)
{	
	//Dont forget the locks
	//Thresholds.empty(T);
	List_Lock.Lock();

	for (Int32 i = 0; i < Thresholds.size(); i++)
	{
		if (Thresholds.at(i) == T)
		{
			//remove the threshold
			Thresholds.erase(Thresholds.begin() + i);
		}
	}

	List_Lock.Unlock();

	return(true);
}

//Check if a threshold has been reached for a given src IP
/*bool Threshold_List::Check(MatchCache *M)
{
	return(true);
}
*/



Threshold_Trigger *Threshold_List::CheckLimits(Host *M)
{

	List_Lock.Lock();
	for (Int32 i = 0; i < Thresholds.size(); i++)
	{
		long Hits = M->countHits(Thresholds[i]->getTimeframe());

		//stringstream ss;
		//ss << "Checking if Rule exceeds our limit: " << Hits << "/" << Thresholds[i]->getLimit() << " within " << Thresholds[i]->getTimeframe();
		//System::Logging.Writeln(ss.str(), LogLevel::LOG_INFO);

		if (Hits > Thresholds[i]->getLimit())
		{
			//ss << "Exceeded";
			//System::Logging.Writeln(ss.str(), LogLevel::LOG_INFO);
			//We have exceeded the limits of the rule
			//stringstream ss;
			//ss << "Host: " << M->HostAddress.to_string() << " Exceeded the rule limit of " << Thresholds[i]->getLimit() << "/" << Thresholds[i]->getTimeframe() << "s" ;
			//Log::Writeln(ss.str(),LogLevel::INFO);
			//cout << "Limit Exceeded" << endl;
			Threshold_Trigger *T = new Threshold_Trigger();
			T->Host = M;
			T->Threshold_Rule = Thresholds[i];
			List_Lock.Unlock();
			return(T);
		}
	}

	List_Lock.Unlock();
return(NULL);
}



unsigned int Threshold_List::CleanList(Host *M)
{
	unsigned int Counter = 0;

	List_Lock.Lock();

	//Clean only based on the longest requirement
	if (Thresholds.size() > 0)	
	{	
		//Get our current Time then reduce the time frame from it
		TimeStamp TimeNow;
		M->Clean(TimeNow.GetEpoc() - Thresholds.back()->getTimeframe());
	}


List_Lock.Unlock();
return(Counter);
}



long Threshold_List::GetLongestThreshold()
{
	int Value=THRESHOLD_NONE;
	List_Lock.Lock();
		if(Thresholds.size()>0)
			Value = Thresholds.back()->getTimeframe();

	List_Lock.Unlock();
	return(Value);
}