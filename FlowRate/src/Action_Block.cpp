#include <Action_Block.h>


Action_Block::Action_Block()
{
	//Generate_ID(Rule_ID, 10);
	Unique_ID = "";
	TimeStamp T;
	TimeAdded = T.GetEpoc();
	RemovalTime = 0;

	SRC_Port_List	= NULL;
	DST_Port_List	= NULL;
	ProtocolList	= NULL;
	Threshold		= NULL;
	HostStackSize	= 0;
}

Action_Block::~Action_Block()
{
	if(SRC_Port_List!=NULL)
		delete SRC_Port_List;
	if (DST_Port_List != NULL)
		delete DST_Port_List;
	if (ProtocolList != NULL)
		delete ProtocolList;
	if (Threshold != NULL)
		delete Threshold;
}


string Action_Block::Get_RuleID() const
{
	return(Rule_ID);
}

string Action_Block::Get_UniqueID() const
{
	return(Unique_ID);
}

//Each action needs its own copy of the action_block that then gets destroyed once finished with