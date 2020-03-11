#pragma once
#include <iostream>
#include <Action_Result.h>
#include <Host.h>
#include <Threshold.h>
#include <sstream>
#include <KeyValuePair.h>
#include <TimeStamp.h>
#include <Match.h>
#include <Action_Cache.h>
#include <Action_Block.h>
#include <Utility.h>


#define SUPPRESION_MIN		0
#define SUPPRESION_DEFAULT	1
#define SUPPRESION_MAX		3600

class Action
{

private:

	Action_Cache_List Cache;

	EpocTime Suppression_Time = SUPPRESION_DEFAULT;


public:

	Action();
	~Action();

	KeyValuePair_List <string> Properties;
	virtual Action_Result Execute(Action_Block *Block);
	Action_Result Check_Then_Execute(Action_Block *Block);
	bool SetSuppressionTime(EpocTime iTime);
	EpocTime GetSuppressionTime();
	
	static Action *CreateAction();

	virtual string getDescription();	//Provide a dynamic text description of the action to be performed with details

};
