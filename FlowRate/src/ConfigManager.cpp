#include <ConfigManager.h>

bool ConfigManager::LoadSettings()
{
	//Load our reg key for our settings

	RegKey *MyKey = new RegKey();
	int Result = RegKey::Load(REGISTRY_LOCATION, MyKey);
	
	if (Result == ERROR_SUCCESS)
	{
		//List of rules
		RegKey *KeyName = MyKey->GetSubKey("Rules");

		System::Logging.Writeln(ExpandString("Processing %d Rule(s)", KeyName->Keys.size()));

		for (Int32 i = 0; i < KeyName->Keys.size(); i++)
		{
			RegKey *CurrentRule = KeyName->Keys.at(i);

			Rule *NewRule=NULL;
			if (LoadRule(CurrentRule, NewRule) == ERROR_SUCCESS)
			{
				Rule *Existingrule = RuleEngine::GetRuleByID(NewRule->GetID());
				if (Existingrule != NULL)
				{
					//We have a matching rule already loaded
					if (NewRule->GetTimeStamp() > Existingrule->GetTimeStamp())
					{
						//The new rule is newer than the existing one
						//Remove the existing rule - add our new one
						//We didn't copy the rules match cache so it will be reset.
						//Any existing Bans will remain as they are controlled by a different engine
						RuleEngine::RemoveRule(Existingrule);
						RuleEngine::AddRule(NewRule);
						delete Existingrule;
						//System::Logging.Writeln("Rule refreshed: " + NewRule->GetID());
					}
					else
					{
						//Rule hasn't changed since last load
						//Ignore it
						delete NewRule;
					}
				}
				else 
				{
					//No existing rule so just add the new rule
					if (NewRule->GetID().size() > 0)
					{
						if (NewRule->GetTimeStamp() > 0)
						{
							RuleEngine::AddRule(NewRule);
						}
						else
						{
							delete NewRule;
						}
					}
					else
					{
						delete NewRule;
					}
				}
				
			}
			else	//Rule failed to load
			{
				//cout << "failed to load rule" << endl;
			}
			
		}

	}
	
	delete MyKey;
	return(true);
}



/*
//Split a given string and return a list of its content
StringList *ConfigManager::SplitString(string input, char delimeter)
{
	StringList *v = new StringList();
	string::size_type i = 0;
	string::size_type j = input.find(delimeter);
	string subs = input;

	while (j != string::npos)
	{
		v->push_back(input.substr(i, j - i));
		i = ++j;
		j = input.find(delimeter, j);
		if (j == string::npos)
			if (input.substr(i, input.length()).size()>1)		//no blank strings
				v->push_back(input.substr(i, input.length()));
	}

	return(v);
}
*/

StringList *ConfigManager::SplitString(string input, char delimeter)
{
		StringList *v = new StringList();
		std::string::size_type b = 0;

		while ((b = input.find_first_not_of(delimeter, b)) != std::string::npos)
		{
			auto e = input.find_first_of(delimeter, b);
			v->push_back(input.substr(b, e - b));
			b = e;
		}

	return(v);
}


StringList *ConfigManager::LoadStrings(RegKey *KeyHandle, string ValueName)
{
	StringList *Output;

	RegValue *Reg_Source = KeyHandle->GetValuebyName(ValueName);
	if (Reg_Source != NULL)
	{
		Output = SplitString((char *)Reg_Source->Value, ';');
	}
	else
	{
		Output = new StringList;
	}

	return(Output);
}



int ConfigManager::LoadInt(RegKey *KeyHandle, string ValueName)
{

	int Value;

	RegValue *Reg_Source = KeyHandle->GetValuebyName(ValueName);
	if (Reg_Source != NULL)
	{
		Value = *(int *)Reg_Source->Value;
	}
	else
	{
		Value = INVALID_NUMBER;
	}

	return(Value);
}


string ConfigManager::LoadString(RegKey *KeyHandle, string ValueName)
{

	char *Value;
	string sValue;

	RegValue *Reg_Source = KeyHandle->GetValuebyName(ValueName);
	if (Reg_Source != NULL)
	{
		Value = (char *)Reg_Source->Value;
		sValue = Value;
	}
	else
	{
		sValue = "";
	}


	return(sValue);
}




//static
bool ConfigManager::LoadRule(RegKey *R, Rule *&NewRule)
{
	//first load ID and timestamp

	StringList *Source = LoadStrings(R, "Source");
	StringList *Destination = LoadStrings(R, "Destination");
	StringList *Protocol = LoadStrings(R, "Protocol");
	StringList *Source_Port = LoadStrings(R, "Source_Port");
	StringList *Destination_Port = LoadStrings(R, "Destination_Port");
	StringList *Properties = LoadStrings(R, "Properties");

	StringList *Limits = LoadStrings(R, "Limits");
	StringList *Src_Exception = LoadStrings(R, "Src_Exception");
	StringList *Dst_Exception = LoadStrings(R, "Dst_Exception");

	//Sanity Checks

	//End Sanity Checks
	

	//Check for a rule ID
	//Our Rule ID
	string ID = LoadString(R, "ID");
	string Interface = LoadString(R, "Interface");

	Rule *M;

	if (!ID.size()>0)	//If we don't have an ID
		{
		delete Source;
		delete Destination;
		delete Protocol;
		delete Source_Port;
		delete Destination_Port;
		delete Properties;
		delete Limits;
		delete Src_Exception;
		delete Dst_Exception;
		return(!ERROR_SUCCESS);
		}
	
	//We have an ID
	M = RuleEngine::CreateRule((char *)ID.c_str());
	M->Interface.Set(Interface);
	

	for (Int32 i = 0; i < Source->size(); i++)
		M->Criteria.SourceIP_List->Add(Source->at(i));

	for (Int32 i = 0; i < Destination->size(); i++)
		M->Criteria.DestinationIP_List->Add(Destination->at(i));

	for (Int32 i = 0; i < Source_Port->size(); i++)
		M->Criteria.SourcePort_List->Add(stoi(Source_Port->at(i)));

	for (Int32 i = 0; i < Destination_Port->size(); i++)
		M->Criteria.DestinationPort_List->Add(stoi(Destination_Port->at(i)));

	for (Int32 i = 0; i < Protocol->size(); i++)
		M->Criteria._Protocol_List->Add(StringToInt(Protocol->at(i)));
	
	for (Int32 i = 0; i < Src_Exception->size(); i++)
		M->Criteria.Src_Exception_List->Add(Src_Exception->at(i));

	for (Int32 i = 0; i < Dst_Exception->size(); i++)
		M->Criteria.Dst_Exception_List->Add(Dst_Exception->at(i));



	//Enabled
	int Enabled = LoadInt(R, "Enabled");
	if (Enabled != INVALID_NUMBER)
		M->Enable();

	//Direction
	int Direction = LoadInt(R, "Direction");
	if (Direction != INVALID_NUMBER)
		M->SetMatchType((MATCH_STATUS)Direction);



	//Load our timestamp
	//Failure to load will use current time for the rule
	long Ruletime = LoadInt(R, "Timestamp");
	if (Ruletime != INVALID_NUMBER)
		M->Time.SetEpoc(Ruletime);

	

	for (Int32 i = 0; i < Properties->size(); i++)
	{
		StringList *L = SplitString(Properties->at(i), '=');
		if (L->size() == 2)
		{
			M->Criteria.Properties->Add(L->at(0), StringToInt(L->at(1)));
		}
	}


	//Load Limits
	//Maybe split out the load limits section
	
	for (Int32 i = 0; i < Limits->size(); i++)
	{
		
		StringList *L = SplitString(Limits->at(i), '/');
		if (L->size() == 2)		//only for values that make sense
		{
			int LimitValue = StringToInt(L->at(0));
			int LimitTime = StringToInt(L->at(1));
			//int LimitBanTime = StringToInt(L->at(2));

			if ((LimitValue != INVALID_NUMBER) && (LimitTime != INVALID_NUMBER))
			{
				Threshold *T = new Threshold();
				T->setLimit(LimitValue);
				T->setTimeframe(LimitTime);
				//T->setBan_Length(LimitBanTime);
				M->Limit.Add(T);
			}
		}
		delete L;
		
	
		//Actions

		
		RegKey *Actions = R->GetSubKey("Actions");
	
		if (Actions != NULL)
		{
			for (Int32 k = 0; k < Actions->Keys.size(); k++)
			{
				
				RegKey *CurrentAction = Actions->Keys.at(k);
				//Load all strings for the key and push them as properties
				
				int ActionType = LoadInt(CurrentAction, "TYPE");
				
				if (ActionType != INVALID_NUMBER)
				{

					//Get Name and value
					Action *A = Action_Manager::CreateAction(ActionType);
					if (A == NULL)
					{
						System::Logging.Writeln(ExpandString("Failed to load action with type %d for rule %s",ActionType,M->GetID()));
					}
					else
					{
						for (Int32 j = 0; j < CurrentAction->Values.size(); j++)
						{
							if (CurrentAction->Values.at(j)->DataType == REG_SZ)
								A->Properties.Add(CurrentAction->Values.at(j)->Name, (char *)CurrentAction->Values.at(j)->Value);
							if (CurrentAction->Values.at(j)->DataType == REG_DWORD)
								A->Properties.Add(CurrentAction->Values.at(j)->Name, IntToString(*(Int32 *)CurrentAction->Values.at(j)->Value));
						}
					M->Actions.push_back(A);
					}

					
				}
				
				
			}
		}
		
		
	}
	

	//Cleanup
	delete Source;
	delete Destination;
	delete Protocol;
	delete Source_Port;
	delete Destination_Port;
	delete Properties;
	delete Limits;
	delete Src_Exception;
	delete Dst_Exception;

	NewRule = M;
	
	//Load any Cache that may be involved
	NewRule->LoadCache();

return(ERROR_SUCCESS);
}