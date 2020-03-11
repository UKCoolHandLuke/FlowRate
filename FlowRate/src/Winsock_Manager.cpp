#include <Winsock_Manager.h>

Winsock_Manager::Winsock_Manager()
{

}

Winsock_Manager::~Winsock_Manager()
{

}


Winsock_Interface *Winsock_Manager::GetSocket(IP_Address &I)
{
	for each (Winsock_Interface *var in Sockets)
	{
		if (var->GetAddress() == I.Get())
		{
			return(var);
		}	
	}

return(NULL);
}


bool Winsock_Manager::Start(string IP)
{
	Winsock_Interface *I = GetSocket(IP_Address(IP));
	if (I != NULL)
		{
		I->Start();
		return(true);
		}

return(false);
}


bool Winsock_Manager::Stop(string IP)
{
	Winsock_Interface *I = GetSocket(IP_Address(IP));
	if (I != NULL)
	{
		I->Stop();
		return(true);
	}

	return(false);
}



bool Winsock_Manager::Add_Interface(IP_Address I)
{
	Lock.Lock();

	Winsock_Interface *w = GetSocket(I);

	if (w != NULL)
	{
		Lock.Unlock();
		return(true);
	}
	else
	{
		Status S;
		S.Start();
			//string IP = I.Get();
			w = new Winsock_Interface(I.Get());
		S.End();

		if (S.Result == Status_Result::SUCCESS)
			{
			Sockets.push_back(w);
			Lock.Unlock();
			return(true);
			}
	}

Lock.Unlock();
return(false);
}



bool Winsock_Manager::Remove_Interface(IP_Address I)
{
	Lock.Lock();
	
	Winsock_Interface *w = GetSocket(I);
	if (w != NULL)
		{
		w->Stop();
		Sockets.erase(std::remove(Sockets.begin(), Sockets.end(), w), Sockets.end());
		w->Terminate();
		//delete (w);
		}
	Lock.Unlock();
	return(false);
}




