#include <Rule_Manager.h>
#include <ConfigManager.h>


Rule_Manager::Rule_Manager() : Manager(1000)
{
}

Rule_Manager::~Rule_Manager()
{
}


bool Rule_Manager::Execute()
{

	//Rule_Manager::Clean();
	//this->AddTask(NULL);	//Add a blank Task for scrubbing old data
	//ConfigManager::LoadSettings();
	return(true);
}

