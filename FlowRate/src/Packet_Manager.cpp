#include <Packet_Manager.h>


Packet_Manager::Packet_Manager() : Manager(SCRUB_INTERVAL)
{
	System::Logging.Writeln("Packet Manager Started");
}

Packet_Manager::~Packet_Manager()
{
}


bool Packet_Manager::Execute()
{

	RuleEngine::Clean();
	//this->AddTask(NULL);	//Add a blank Task for scrubbing old data
	return(true);
}