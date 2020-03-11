#include <Action.h>



Action::Action()
{
}

Action::~Action()
{

}

/*
This is broken - it suppresses all actions 
needs to have a host list to suppress only one host
maybe a struct for Host/ActionTime
*/
Action_Result Action::Check_Then_Execute(Action_Block *Block)
{
Action_Result R;
R.Result = false;
R.Message = "Action suppressed";

	TimeStamp CurrentTime;
	//long HostLastExecute = Cache.GetLastExecute(H->HostAddress);
	
	if ((Cache.GetLastExecute(Block->Host) + Suppression_Time) <= CurrentTime.GetEpoc())
		{
		Cache.Update(Block->Host);
		return(Execute(Block));
		}
	else
		{
		//Clean up our action_block
		delete Block;
		}

return(R);
}


//Blank Action - Should be overridden by inherited action
Action_Result Action::Execute(Action_Block *Block)
{
	Action_Result Result;
	return(Result);
}


bool Action::SetSuppressionTime(EpocTime iTime)
{
	if ((iTime >= SUPPRESION_MIN) && (iTime <= SUPPRESION_MAX))
	{
		Suppression_Time = iTime;
		return(true);
	}

return(false);
}

EpocTime Action::GetSuppressionTime()
{
	return(Suppression_Time);
}


string Action::getDescription()
{
	stringstream ss;
	ss << "This action will ....";
	return(ss.str());
}

