#pragma once
#include <TimeStamp.h>
#include <Host.h>
#include <Threshold.h>
#include <Match.h>



class Action_Block
{
private:

public:
	string			Rule_ID;
	string			Unique_ID;
	EpocTime		TimeAdded = 0;
	EpocTime		RemovalTime = 0;

	string			 Host;
	MATCH_STATUS	 Direction;
	PortRange_List	*SRC_Port_List;
	PortRange_List	*DST_Port_List;
	Protocol_List	*ProtocolList;

	//Extended information
	Threshold			*Threshold;				//Which threshold was exceeded
	Int32				HostStackSize;			//What is the host stack size
	

	Action_Block();
	~Action_Block();

	string			 Get_RuleID() const;
	string			 Get_UniqueID() const;

	//Comparison Operators ==
	friend bool operator== (const Action_Block& A, const Action_Block& B)
	{

		string s1 = A.Get_RuleID();
		string s2 = B.Get_RuleID();
		//compare the rule ID
		if(s1 != s2)
		//if (A.GetID() != B.GetID())
			return(false);
		
		s1 = A.Get_UniqueID();
		s2 = B.Get_UniqueID();
		if (s1 != s2)
			return(false);
			
		//compare the source and dest hosts
		if (A.Host != B.Host)
			return(false);

		//no need to do any of this as the rule ID should prove they are identical
		//host is the only other variable

		//compare the direction
		//if (A.Direction != B.Direction)
		//	return(false);

		//compare protocols
		//if (*A.ProtocolList != *B.ProtocolList)
		//	return(false);

		//compare ports
		//if (*A.DST_Port_List != *B.DST_Port_List)
		//	return(false);

		//compare ports
		//if (*A.SRC_Port_List != *B.SRC_Port_List)
		//	return(false);
				
		return(true);
	}


	//overload the assignment
	void operator=(const Action_Block& A)
	{
		Host			= A.Host;
		Direction		= A.Direction;
		ProtocolList	= A.ProtocolList->Copy();
		DST_Port_List	= A.DST_Port_List->Copy();
		SRC_Port_List	= A.SRC_Port_List->Copy();
		Rule_ID			= A.Rule_ID;
		Unique_ID		= A.Unique_ID;
		RemovalTime		= A.RemovalTime;
		TimeAdded		= A.TimeAdded;

		//Extended
		Threshold		= A.Threshold->Copy();
		HostStackSize	= A.HostStackSize;
	}


};