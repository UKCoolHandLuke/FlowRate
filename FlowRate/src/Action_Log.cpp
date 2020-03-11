#include <Action_Log.h>

Action_Log::Action_Log()
{
	LogObj=NULL;
	//LogObj = new Log("FirewallLog.txt");
	//Properties.Add("NAME", "ACTION_LOG");
}

Action_Log::~Action_Log()
{
	delete LogObj;
}


Action_Result Action_Log::Execute(Action_Block *Block)
{

	Action_Result Result;
	stringstream ss;

	if (LogObj == NULL)
	{
		if (Properties.ContainsKey("FILENAME")!=KEY_NOT_FOUND)
		{
			string Filename = Properties.getvalue("FILENAME");
			LogObj = new Log(Filename);
		}
		else
		{
			Result.Result = false;
			Result.Message = "Failed to get log filename";

			delete Block;	//clean up the block
			return(Result);
		}
	}
	
	ss << "Host: " + Block->Host + " Exceeded rule of ";
	ss << Block->Threshold->getLimit();
	ss << " packets(s) within ";
	ss << Block->Threshold->getTimeframe();
	ss << " seconds.";

	ss << " host stack is: ";
	ss << Block->HostStackSize;

	if (LogObj->Writeln(ss.str(),LogLevel::LOG_INFO))
		Result.Result = true;

	
	delete Block;	//clean up the block

	return(Result);
}

string Action_Log::getDescription()
{
	stringstream ss;
	ss << "Log all hosts exceeding the rule to file " << Properties.getvalue("FILENAME");
	return(ss.str());
}