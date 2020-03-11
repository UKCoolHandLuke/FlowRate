#include <Winsock_Manager.h>

#include <System.h>
#include <ConfigManager.h>


#pragma comment(lib, "ws2_32.lib")
#include <Status.h>
#include <Packet_Manager.h>

int main()
{

	System::Logging.setLogLevel(LogLevel::LOG_DEBUG);
	System::Logging.setEcho(true);

	ConfigManager::LoadSettings();
	
	Winsock_Manager M;
	Packet_Manager PktMgr;

	//We need to get a list of all interfaces from the rules
	//We need to create an interface for each unique interface (with multiple rules)

	set<string> Interface_List = RuleEngine::GetInterfaces();
	
	for each(string s in Interface_List)
	{
		M.Add_Interface(s);
		M.Start(s);
	}
	

	System::Logging.setLogLevel(LogLevel::LOG_INFO);


	string keypress;

	while (1 == 1)
	{
		Sleep(1);
		cin.get();
		cout << RuleEngine::getStats();
	}

	
}