#include <Action_Manager.h>

Action_Manager::Action_Manager()
{
}

Action_Manager::~Action_Manager()
{
}

//Static
Action *Action_Manager::CreateAction(int ActionType)
{
	Action *A = NULL;

	switch (ActionType)
	{

	case ACTION_LOG:
		A = new Action_Log();
		break;
	case ACTION_EMAIL:
		A = new Action_Email();
		break;
	case ACTION_FIREWALL:
		A = new Action_Firewall();
		break;

	default:
		break;
	}

return(A);
}
