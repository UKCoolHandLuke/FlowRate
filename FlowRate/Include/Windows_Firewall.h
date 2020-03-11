#pragma once
#include <windows.h>
#include <crtdbg.h>
#include <netfw.h>
#include <objbase.h>
#include <oleauto.h>
#include <stdio.h>
#include <comutil.h>		//BSTR
#include <atlcomcli.h>		

#include <Action_Block.h>
#include <Match.h>

#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "oleaut32.lib" )

/*
NET_FW_IP_PROTOCOL_TCP,
NET_FW_IP_PROTOCOL_UDP,
NET_FW_IP_PROTOCOL_ANY
*/

class Windows_Firewall
{

private:
	static HRESULT WFCOMInitialize(INetFwPolicy2** ppNetFwPolicy2);
	static Log Log_File;


	static bool Rule_Add(string Name, string Group, MATCH_STATUS Direction, string Host, Int32 Protocol, Int32 Port);		//Adds an individual rule to our firewall
	static bool Rule_Remove(string BlockRule);																//Remove individual rule from our firewall

public:

	Windows_Firewall();
	~Windows_Firewall();


	static bool AddRule(Action_Block *BlockRule);
	static bool RemoveRule(Action_Block *BlockRule);

	//static bool RemoveRule(Action_Block *BlockRule);
	static Int32 Clear();
	

};