#include <Windows_Firewall.h>


//Static init for log file
Log Windows_Firewall::Log_File("Firewall.log");

Windows_Firewall::Windows_Firewall()
{
}

Windows_Firewall::~Windows_Firewall()
{
}




//Static
bool Windows_Firewall::Rule_Add(string Name, string Group, MATCH_STATUS Direction, string Host, Int32 Protocol, Int32 Port)
{
	HRESULT hrComInit = S_OK;
	HRESULT hr = S_OK;

	INetFwPolicy2 *pNetFwPolicy2 = NULL;
	INetFwRules *pFwRules = NULL;
	INetFwRule *pFwRule = NULL;

	long CurrentProfilesBitMask = 0;

	stringstream ss;

	ss << "Adding filter rule: " + Name + " for host " + Host;
	ss << " Protocol: " + to_string(Protocol);
	ss << " Port: " + to_string(Port);
	//Log_File.Writeln("Adding Firewall Rule for host: " + Host);

	Log_File.Writeln(ss.str(), LogLevel::LOG_INFO);

	//Lets determine the direction (Incoming/outgoing)

	// The rule name, description, and group are provided as indirect strings for 
	// localization purposes. These resource strings can be found in the rc file
	/*
	BSTR bstrRuleName = SysAllocString(L"FWRule:");
	BSTR bstrRuleDescription = SysAllocString(L"Filter host: ");
	BSTR bstrRuleGroup = SysAllocString(L"FWRule");
	
	BSTR bstrRuleLPorts = SysAllocString(L"4000");
	BSTR bstrRuleRHost = SysAllocString(L"8.8.8.8");
	*/

	BSTR bstrRuleName = _com_util::ConvertStringToBSTR((char *)Name.c_str());
	BSTR bstrRuleDescription = _com_util::ConvertStringToBSTR((char *)Name.c_str());
	BSTR bstrRuleGroup = _com_util::ConvertStringToBSTR((char *)Group.c_str());

	BSTR bstrHost = _com_util::ConvertStringToBSTR((char *)Host.c_str());
	BSTR bstrPort = _com_util::ConvertStringToBSTR((char *)to_string(Port).c_str());


	// Error checking for BSTR allocations
	if (NULL == bstrRuleName) { printf("Failed to allocate bstrRuleName\n"); goto Cleanup; }
	if (NULL == bstrRuleDescription) { printf("Failed to allocate bstrRuleDescription\n"); goto Cleanup; }
	if (NULL == bstrRuleGroup) { printf("Failed to allocate bstrRuleGroup\n"); goto Cleanup; }
	if (NULL == bstrHost) { printf("Failed to allocate bstrRuleGroup\n"); goto Cleanup; }

	// Initialize COM.
	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED
	);

	// Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
	// initialized with a different mode. Since we don't care what the mode is,
	// we'll just use the existing mode.
	if (hrComInit != RPC_E_CHANGED_MODE)
	{
		if (FAILED(hrComInit))
		{
			printf("CoInitializeEx failed: 0x%08lx\n", hrComInit);
			goto Cleanup;
		}
	}

	// Retrieve INetFwPolicy2
	hr = WFCOMInitialize(&pNetFwPolicy2);
	if (FAILED(hr))
	{
		goto Cleanup;
	}

	// Retrieve INetFwRules
	hr = pNetFwPolicy2->get_Rules(&pFwRules);
	if (FAILED(hr))
	{
		printf("get_Rules failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Retrieve Current Profiles bitmask
	hr = pNetFwPolicy2->get_CurrentProfileTypes(&CurrentProfilesBitMask);
	if (FAILED(hr))
	{
		printf("get_CurrentProfileTypes failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// When possible we avoid adding firewall rules to the Public profile.
	// If Public is currently active and it is not the only active profile, we remove it from the bitmask
	if ((CurrentProfilesBitMask & NET_FW_PROFILE2_PUBLIC) &&
		(CurrentProfilesBitMask != NET_FW_PROFILE2_PUBLIC))
	{
		CurrentProfilesBitMask ^= NET_FW_PROFILE2_PUBLIC;
	}

	// Create a new Firewall Rule object.
	hr = CoCreateInstance(__uuidof(NetFwRule),NULL,	CLSCTX_INPROC_SERVER,__uuidof(INetFwRule),(void**)&pFwRule);
	if (FAILED(hr))
	{
		printf("CoCreateInstance for Firewall Rule failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Populate the Firewall Rule Name
	hr = pFwRule->put_Name(bstrRuleName);
	if (FAILED(hr))
	{
		printf("put_Name failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Populate the Firewall Rule Description
	hr = pFwRule->put_Description(bstrRuleDescription);
	if (FAILED(hr))
	{
		printf("put_Description failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Populate the Firewall Rule Protocol
	hr = pFwRule->put_Protocol(Protocol);
	if (FAILED(hr))
	{
		printf("put_Protocol failed: 0x%08lx\n", hr);
		goto Cleanup;
	}


	/*
	// Populate the Firewall Rule Protocol
	hr = pFwRule->put_Protocol(NET_FW_IP_PROTOCOL_TCP);
	if (FAILED(hr))
	{
		printf("put_Protocol failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Populate the Firewall Rule Local Ports
	hr = pFwRule->put_LocalPorts(bstrRuleLPorts);
	if (FAILED(hr))
	{
		printf("put_LocalPorts failed: 0x%08lx\n", hr);
		goto Cleanup;
	}
	*/


	//Local port or remote port block
	if (Protocol == IPPROTO_UDP || Protocol == IPPROTO_TCP)
	{
		if (Direction == MATCH_STATUS::MATCH_DST)	//remote port
		{
			hr = pFwRule->put_RemotePorts(bstrPort);
		}
		else										//local port
		{
			hr = pFwRule->put_LocalPorts(bstrPort);
		}
	}


	// Populate the Firewall Rule Local Ports

	//BSTR bstrName = SysAllocString(L(char *)H->HostAddress.to_char());

	//BSTR restr = SysAllocStringByteLen((char *)H->HostAddress.to_char(), H->HostAddress.Length());

	//BSTR RHostAddress = _com_util::ConvertStringToBSTR((char *)BlockRule->Block_Host.c_str());
	//BSTR RHostAddress = _com_util::ConvertStringToBSTR((char *)BlockRule->Block_Host.c_str());

	//BSTR RHostAddress = bs1.copy();

	hr = pFwRule->put_RemoteAddresses(bstrHost);
	//hr = pFwRule->put_RemoteAddresses(bstrRuleRHost);
	if (FAILED(hr))
	{
		printf("put_RemoteHost failed: 0x%08lx\n", hr);
		goto Cleanup;
	}
	



	// Populate the Firewall Rule Direction
	if(Direction == MATCH_STATUS::MATCH_DST)
		hr = pFwRule->put_Direction(NET_FW_RULE_DIR_OUT);
	else
		hr = pFwRule->put_Direction(NET_FW_RULE_DIR_IN);
	if (FAILED(hr))
	{
		printf("put_Direction failed: 0x%08lx\n", hr);
		goto Cleanup;
	}






	// Populate the Firewall Rule Group
	hr = pFwRule->put_Grouping(bstrRuleGroup);
	if (FAILED(hr))
	{
		printf("put_Grouping failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Populate the Firewall Rule Profiles
	hr = pFwRule->put_Profiles(CurrentProfilesBitMask);
	if (FAILED(hr))
	{
		printf("put_Profiles failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Populate the Firewall Rule Action
	hr = pFwRule->put_Action(NET_FW_ACTION_BLOCK);
	if (FAILED(hr))
	{
		printf("put_Action failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Populate the Firewall Rule Enabled
	hr = pFwRule->put_Enabled(VARIANT_TRUE);
	if (FAILED(hr))
	{
		printf("put_Enabled failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Add the Firewall Rule
	hr = pFwRules->Add(pFwRule);
	if (FAILED(hr))
	{
		printf("Firewall Rule Add failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

Cleanup:

	// Free BSTR's
	SysFreeString(bstrRuleName);
	SysFreeString(bstrRuleDescription);
	SysFreeString(bstrRuleGroup);
	SysFreeString(bstrPort);

	SysFreeString(bstrHost);

	// Release the INetFwRule object
	if (pFwRule != NULL)
	{
		pFwRule->Release();
	}

	// Release the INetFwRules object
	if (pFwRules != NULL)
	{
		pFwRules->Release();
	}

	// Release the INetFwPolicy2 object
	if (pNetFwPolicy2 != NULL)
	{
		pNetFwPolicy2->Release();
	}

	// Uninitialize COM.
	if (SUCCEEDED(hrComInit))
	{
		CoUninitialize();
	}

	return(true);
}


bool Windows_Firewall::AddRule(Action_Block *BlockRule)
{

	//Split up the rules in the Block Rule and add individually
	//This will include a rule for each port/protocol

	//If the direction is outgoing, we only care about remote ports
	//If the direction is inbound, we only care about local ports

	string RuleName = BlockRule->Get_RuleID() + ":" + BlockRule->Get_UniqueID();

	PortRange_List *Ports;

if (BlockRule->Direction == MATCH_STATUS::MATCH_DST)
		Ports = BlockRule->SRC_Port_List->Copy();
	else
		Ports = BlockRule->DST_Port_List->Copy();
		

	//Lets check which protocols we need to filter
	if (BlockRule->ProtocolList->size() > 0)	
	{
		for (Int32 p = 0; p < BlockRule->ProtocolList->size(); p++)
		{
			if (Ports->size() > 0)	//protocols and ports together
			{
				for (Int32 i = 0; i < Ports->size(); i++)
				{
					Simple_Port_Range Range = Ports->at(i)->GetRange();
					for (Int32 Rng = Range.Min; Rng <= Range.Max; Rng++)
						{
						Rule_Add(RuleName, BlockRule->Get_RuleID(), BlockRule->Direction, BlockRule->Host, BlockRule->ProtocolList->at(p), Rng);
						}
				}
			}
			else                   //Protcol only
			{
				Rule_Add(RuleName, BlockRule->Get_RuleID(), BlockRule->Direction, BlockRule->Host, BlockRule->ProtocolList->at(p), 0);
			}
		}
	}
	else       //No protocols, only ports.  We should add both UDP and TCP as filters
	{
		if (Ports->size() > 0)
		{
			for (Int32 i = 0; i < Ports->size(); i++)
			{
				Simple_Port_Range Range = Ports->at(i)->GetRange();

				for (Int32 Rng = Range.Min; Rng < Range.Max; Rng++)
				{
					Rule_Add(RuleName, BlockRule->Get_RuleID(), BlockRule->Direction, BlockRule->Host, NET_FW_IP_PROTOCOL_TCP, Rng);
					Rule_Add(RuleName, BlockRule->Get_RuleID(), BlockRule->Direction, BlockRule->Host, NET_FW_IP_PROTOCOL_UDP, Rng);
				}
			}
		}
	}

	delete Ports;

return(true);
}



bool Windows_Firewall::RemoveRule(Action_Block *BlockRule)
{
	string RuleName = BlockRule->Get_RuleID() + ":" + BlockRule->Get_UniqueID();
	return (Rule_Remove(RuleName));
}



bool Windows_Firewall::Rule_Remove(string RuleName)
{
	//enum a list of rules

	HRESULT hrComInit = S_OK;
	HRESULT hr = S_OK;

	//ULONG cFetched = 0;
	CComVariant var;

	//IUnknown *pEnumerator;
	//IEnumVARIANT* pVariant = NULL;

	INetFwPolicy2 *pNetFwPolicy2 = NULL;
	INetFwRules *pFwRules = NULL;
	INetFwRule *pFwRule = NULL;

	//long fwRuleCount;

	//string RuleName = "FWRule: " + BlockRule->Get_RuleID();


	stringstream ss;
	//ss << "Removing filter rule: " + RuleName + " for host " + BlockRule->Host;
	//Log_File.Writeln(ss.str());

	BSTR bstrRuleName = _com_util::ConvertStringToBSTR((char *)RuleName.c_str());
	//BSTR bstrVal;			//used to store rule names when performing enum

	// Initialize COM.
	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED
	);

	// Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
	// initialized with a different mode. Since we don't care what the mode is,
	// we'll just use the existing mode.
	if (hrComInit != RPC_E_CHANGED_MODE)
	{
		if (FAILED(hrComInit))
		{
			wprintf(L"CoInitializeEx failed: 0x%08lx\n", hrComInit);
			goto Cleanup;
		}
	}

	// Retrieve INetFwPolicy2
	hr = WFCOMInitialize(&pNetFwPolicy2);
	if (FAILED(hr))
	{
		goto Cleanup;
	}

	hr = pNetFwPolicy2->get_Rules(&pFwRules);
	if (FAILED(hr))
	{
		wprintf(L"get_Rules failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	hr = pFwRules->Remove(bstrRuleName);
	if (FAILED(hr))
		{
		wprintf(L"RemoveRule failed: 0x%08lx\n", hr);
		goto Cleanup;
		}

Cleanup:

	SysFreeString(bstrRuleName);

	// Release pFwRule
	if (pFwRule != NULL)
	{
		pFwRule->Release();
	}

	// Release INetFwPolicy2
	if (pNetFwPolicy2 != NULL)
	{
		pNetFwPolicy2->Release();
	}

	// Uninitialize COM.
	if (SUCCEEDED(hrComInit))
	{
		CoUninitialize();
	}

	return(true);
}




/*
bool Windows_Firewall::RemoveRule(Action_Block *BlockRule)
{
	//enum a list of rules

	HRESULT hrComInit = S_OK;
	HRESULT hr = S_OK;

	ULONG cFetched = 0;
	CComVariant var;

	IUnknown *pEnumerator;
	IEnumVARIANT* pVariant = NULL;

	INetFwPolicy2 *pNetFwPolicy2 = NULL;
	INetFwRules *pFwRules = NULL;
	INetFwRule *pFwRule = NULL;

	long fwRuleCount;

	string RuleName = "FWRule: " + BlockRule->GetID();


	stringstream ss;
	ss << "Removing filter rule: " + RuleName + " for host " + BlockRule->Host;
	Log_File.Writeln(ss.str());

	BSTR bstrRuleName = _com_util::ConvertStringToBSTR((char *)RuleName.c_str());
	BSTR bstrVal;			//used to store rule names when performing enum

	// Initialize COM.
	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED
	);

	// Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
	// initialized with a different mode. Since we don't care what the mode is,
	// we'll just use the existing mode.
	if (hrComInit != RPC_E_CHANGED_MODE)
	{
		if (FAILED(hrComInit))
		{
			wprintf(L"CoInitializeEx failed: 0x%08lx\n", hrComInit);
			goto Cleanup;
		}
	}

	// Retrieve INetFwPolicy2
	hr = WFCOMInitialize(&pNetFwPolicy2);
	if (FAILED(hr))
	{
		goto Cleanup;
	}

	// Retrieve INetFwRules
	hr = pNetFwPolicy2->get_Rules(&pFwRules);
	if (FAILED(hr))
	{
		wprintf(L"get_Rules failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	// Obtain the number of Firewall rules
	hr = pFwRules->get_Count(&fwRuleCount);
	if (FAILED(hr))
	{
		wprintf(L"get_Count failed: 0x%08lx\n", hr);
		goto Cleanup;
	}


	//wprintf(L"The number of rules in the Windows Firewall are %d\n", fwRuleCount);

	// Iterate through all of the rules in pFwRules
	pFwRules->get__NewEnum(&pEnumerator);

	if (pEnumerator)
	{
		hr = pEnumerator->QueryInterface(__uuidof(IEnumVARIANT), (void **)&pVariant);
	}
	
	while (SUCCEEDED(hr) && hr != S_FALSE)
	{
		var.Clear();
		hr = pVariant->Next(1, &var, &cFetched);

		if (S_FALSE != hr)
		{
			if (SUCCEEDED(hr))
			{
				hr = var.ChangeType(VT_DISPATCH);
			}
			if (SUCCEEDED(hr))
			{
				hr = (V_DISPATCH(&var))->QueryInterface(__uuidof(INetFwRule), reinterpret_cast<void**>(&pFwRule));
			}

			if (SUCCEEDED(hr))
			{
				hr = pFwRule->get_Name(&bstrVal);
				
				if (wcscmp(bstrVal,bstrRuleName)==0)
				{
					hr = pFwRules->Remove(bstrRuleName);
				}

			}
		}
	}
	
Cleanup:

	SysFreeString(bstrRuleName);

	// Release pFwRule
	if (pFwRule != NULL)
	{
		pFwRule->Release();
	}

	// Release INetFwPolicy2
	if (pNetFwPolicy2 != NULL)
	{
		pNetFwPolicy2->Release();
	}

	// Uninitialize COM.
	if (SUCCEEDED(hrComInit))
	{
		CoUninitialize();
	}

	return(true);
}

*/



Int32 Windows_Firewall::Clear()
{

	//enum a list of rules

	HRESULT hrComInit = S_OK;
	HRESULT hr = S_OK;

	//ULONG cFetched = 0;
	CComVariant var;

	//IUnknown *pEnumerator;
	//IEnumVARIANT* pVariant = NULL;

	INetFwPolicy2 *pNetFwPolicy2 = NULL;
	INetFwRules *pFwRules = NULL;
	INetFwRule *pFwRule = NULL;

	//long fwRuleCount;

	string Group = "FWRule";


	stringstream ss;
	//ss << "Removing filter rule: " + RuleName + " for host " + BlockRule->Host;
	//Log_File.Writeln(ss.str());

	BSTR bstrRuleName = _com_util::ConvertStringToBSTR((char *)Group.c_str());
	//BSTR bstrVal;			//used to store rule names when performing enum

	// Initialize COM.
	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED
	);

	// Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
	// initialized with a different mode. Since we don't care what the mode is,
	// we'll just use the existing mode.
	if (hrComInit != RPC_E_CHANGED_MODE)
	{
		if (FAILED(hrComInit))
		{
			wprintf(L"CoInitializeEx failed: 0x%08lx\n", hrComInit);
			goto Cleanup;
		}
	}

	// Retrieve INetFwPolicy2
	hr = WFCOMInitialize(&pNetFwPolicy2);
	if (FAILED(hr))
	{
		goto Cleanup;
	}

	hr = pNetFwPolicy2->get_Rules(&pFwRules);
	if (FAILED(hr))
	{
		wprintf(L"get_Rules failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

	hr = pFwRules->Remove(bstrRuleName);
	if (FAILED(hr))
	{
		wprintf(L"RemoveRule failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

Cleanup:

	SysFreeString(bstrRuleName);

	// Release pFwRule
	if (pFwRule != NULL)
	{
		pFwRule->Release();
	}

	// Release INetFwPolicy2
	if (pNetFwPolicy2 != NULL)
	{
		pNetFwPolicy2->Release();
	}

	// Uninitialize COM.
	if (SUCCEEDED(hrComInit))
	{
		CoUninitialize();
	}

	return(true);

}



//Static 
HRESULT Windows_Firewall::WFCOMInitialize(INetFwPolicy2** ppNetFwPolicy2)
{
	HRESULT hr = S_OK;

	hr = CoCreateInstance(
		__uuidof(NetFwPolicy2),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(INetFwPolicy2),
		(void**)ppNetFwPolicy2);

	if (FAILED(hr))
	{
		printf("CoCreateInstance for INetFwPolicy2 failed: 0x%08lx\n", hr);
		goto Cleanup;
	}

Cleanup:
	return hr;
}


