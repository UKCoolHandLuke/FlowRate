#include <Action_Allow.h>

Action_Allow::Action_Allow()
{
}

Action_Allow::~Action_Allow()
{
}


Action_Result Action_Allow::Execute(Action_Block *Block)
{

	Action_Result Result;

	System::Logging.Writeln(ExpandString("Host: %s  is whitelisted using the rule ", Block->Host), LogLevel::LOG_INFO);
	Result.Result = true;
		
	delete Block;	//clean up the block

	return(Result);
}


string Action_Allow::getDescription()
{
	stringstream ss;
	ss << "Whitelist hosts using this rule";
	return(ss.str());
}