#include <Rule.h>
#include <ACTION_MANAGER.h>

Rule::Rule(GUID myID)
{
	//ID = id;
	Init();
	ID = myID;
	//ID = *myID;
	Cache.SetID(myID);
}

Rule::Rule()
{
	//We need to generate an ID
	//ID = 0;
	
	Init();
	//assign an ID
	ID = UniqueID::GenerateGUID();
}


Rule::~Rule()
{
	Criteria.Cache = NULL;
	//Clean our Actions;
}


bool Rule::Init()
{
	Criteria.Cache = &Cache;
	Disable();		//default to Disable the rule
	return(true);
}


void Rule::Enable()
{
	Enabled = true;
}

void Rule::Disable()
{
	Enabled = false;
}

bool Rule::isEnabled()
{
	return(Enabled);
}



//Static that defines the template for any IP address
IPV4Range* Rule::IPV4_ANY()
{
	IPV4Range* R = new IPV4Range();
	R->Set("0.0.0.0", "255.255.255.255");
	return(R);
}


bool Rule::TestPacket(Packet *P)
{
	if (P == NULL)
		return(false);

	if (Criteria.Src_Exception_List->Contains(P->Source.Get()))
		return(false);

	if (Criteria.Dst_Exception_List->Contains(P->Destination.Get()))
		return(false);

	if (Criteria._Protocol_List->size() > 0)
	{
		if (!Criteria._Protocol_List->Contains(P->Protocol.ProtocolNumber))
			return(false);
	}

	if (Criteria.DestinationIP_List->Length() > 0)
	{
		if (!Criteria.DestinationIP_List->Contains((P->Destination.Get())))
			return(false);
	}

	if (Criteria.SourceIP_List->Length() > 0)
	{
		if (!Criteria.SourceIP_List->Contains((P->Source.Get())))
			return(false);
	}


	if (Criteria.SourcePort_List->size() > 0)
	{
		Int32 sPort = P->Protocol.Properties.getvalue("SOURCE.PORT");
		if (sPort != KEY_NOT_FOUND)
		{
			if (!Criteria.SourcePort_List->Contains((sPort)))
				return(false);
		}
		else
		{
			return(false);
		}
	}


	if (Criteria.DestinationPort_List->size() > 0)
	{
		Int32 dPort = P->Protocol.Properties.getvalue("DESTINATION.PORT");
		if (dPort != KEY_NOT_FOUND)
		{
			if (!Criteria.DestinationPort_List->Contains((dPort)))
				return(false);
		}
		else
		{
			return(false);
		}
	}


	//This should mainly be used for flags
	bool PropertiesMatch = true;

	if (Criteria.Properties->size() > 0)
		PropertiesMatch = false;

	//Check our packet properties against our keyvalue pair list

	for (Int32 i = 0; i< Criteria.Properties->size(); i++)
	{
		Int32 Value = P->Protocol.Properties.getvalue(Criteria.Properties->at(i)->Key);
		if ((Value != KEY_NOT_FOUND) && (Value !=NULL))
		{
			//We found a key/value pair - test to check for a match
			if (Value != Criteria.Properties->getvalue(Criteria.Properties->at(i)->Key))
			{
				//They do not match so lets bomb out
				return(false);
			}
			else
			{
				PropertiesMatch = true;
			}
		}
	}

	if (!PropertiesMatch)
		return(false);





	//All matches complete

	if (System::Logging.getLogLevel() == LogLevel::LOG_DEBUG)
		{
		stringstream ss;
		ss << "Matched Packet (" + to_string(P->Protocol.ProtocolNumber) + ") ";
		ss << P->Source.Get() + " - " + P->Destination.Get();
		System::Logging.Writeln(ss.str(), LogLevel::LOG_DEBUG);
		}
	

	//Add the matching packet to our cache
	//Make a copy of the packet first


	Packet *newPacket = P->Copy();
	
	Host *H = Cache.Add(newPacket);

	//Check our limits
	Threshold_Trigger *Test = Limit.CheckLimits(H);
	if (Test != NULL)
		{
		Actions.Execute(Test->Host, Test->Threshold_Rule, &this->Criteria);
		delete Test;
		Test = NULL;
		}
	
	//Cache.Save(GetID()); - don't do this, will cause too many writes - it should be handled by a timed interval (manager)

	//Clean our lists
	//Limit.CleanList(H);
	//do not clean - we have a thread to do this

	//If we match all criteria return true
	return(true);
}




/*
Check to see if a host has exceeded its limits
*/
bool Rule::CheckLimits()
{
	return(false);
}

bool Rule::SetMatchType(MATCH_STATUS newStatus)
{
	return(Cache.SetMatchType(newStatus));
}

MATCH_STATUS Rule::GetMatchType()
{
	return(Cache.GetMatchType());
}

bool Rule::Clean()
{
	long OldestPacket_Time = Limit.GetLongestThreshold();
	if (OldestPacket_Time != THRESHOLD_NONE)
	{
		return(Cache.Clean(OldestPacket_Time));
	}

return(false);
}


bool Rule::SetTimeStamp(EpocTime E)
{
	//Blindly set the timestamp
	//Needs some sanity checks
	return(Time.SetEpoc(E));
}


EpocTime Rule::GetTimeStamp()
{
	return(Time.GetEpoc());
}

GUID Rule::GetID()
{
	return(ID);
}


/*
Load a Rule's cache from a file if it exists - this is usually done at startup
*/
bool Rule::LoadCache()
{
	return(Cache.Load(GetID()));
}



