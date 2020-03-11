#include <Winsock_Interface.h>
#include <IP.h>
#include <Packet_Manager.h>


Winsock_Interface::Winsock_Interface(string IP)
{
	_IP.Set(IP);
	Init();
}

Winsock_Interface::~Winsock_Interface()
{

	System::Logging.Writeln("Closing socket for interface " + _IP.Get());
	string sResult = "";

	if (Initialised)
	{
		int Result = closesocket(s0k);
		switch (Result)
		{
		case SUCCESS:
			sResult = "Success";
			break;
		case WSANOTINITIALISED:
			sResult = "Error - but it was not previously initialised.  Oh well";
			break;
		case WSAENOTSOCK:
			sResult = "Error - not a socket";
			break;
		case WSAEINPROGRESS:
			sResult = "Error - socket is busy";
			break;
		case WSAEINTR:
			sResult = "Error - was canceled";
			break;
		case WSAEWOULDBLOCK:
			sResult = "Error - would cause the socket to block";
			break;

		default:
			sResult = "Unknown";
			break;
		}
	}
	
	try
	{
		WSACleanup();
	}
	catch (exception e)
	{

	}

	System::Logging.Writeln(sResult);
}


string Winsock_Interface::GetAddress()
{
	return (_IP.Get());
}


bool Winsock_Interface::Initialise_Interface()
{

	WSADATA w;
	SOCKADDR_IN sa;
	DWORD bytes;
	//char hostname[HOSTNAME_LEN];
	//struct hostent *h;
	unsigned int opt = 1;
	if (WSAStartup(MAKEWORD(2, 2), &w) != 0)
		{
		System::Logging.Writeln("WSAStartup failed");
		return(false);
		}

	if ((s0k = socket(AF_INET, SOCK_RAW, IPPROTO_IP)) == INVALID_SOCKET)
		{
		System::Logging.Writeln("Unable to open raw socket for interface: " + GetAddress());
		return(false);
		}

	// use default interface
	/*
	if ((gethostname(hostname, HOSTNAME_LEN)) == SOCKET_ERROR)
		{
		System::Logging.Writeln("unable to gethostname");
		return(false);
		}
	if ((h = gethostbyname(hostname)) == NULL)
		{
		System::Logging.Writeln("unable to gethostbyname");
		return(false);
		}
	*/
	sa.sin_family = AF_INET;
	sa.sin_port = htons(6000);
	sa.sin_addr.S_un.S_addr = inet_addr((char *)_IP.Get().c_str());
	//sa.sin_addr = inet_addr((char *)_IP.Get().c_str());

	//memcpy(&sa.sin_addr.S_un.S_addr, h->h_addr_list[0], h->h_length);
	if ((bind(s0k, (SOCKADDR *)&sa, sizeof(sa))) == SOCKET_ERROR)
		System::Logging.Writeln("Unable to bind socket to interface " + GetAddress());
	if (promiscuous)	/* -d on the command line to disable promiscuous mode */
		if ((WSAIoctl(s0k, SIO_RCVALL, &opt, sizeof(opt), NULL, 0, &bytes, NULL, NULL)) == SOCKET_ERROR)
			System::Logging.Writeln("Failed to set promiscuous mode to interface " + GetAddress());

	return(true);
}


Status Winsock_Interface::Init()
{

	DWORD   dwThreadId = 0;

	Status S;

	S.Start();
		Initialise_Interface();
	S.End();

	if (S.Result == Status_Result::FAILURE)
	{
		Initialised = false;
		S.SetResult(Status_Result::FAILURE);
		S.SetMessage("Failed to initialise interface");
		return(S);
	}

	Initialised = true;

	InterfaceThread = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		Process,				// thread function name
		(LPVOID)this,			// argument to thread function 
		0,                      // use default creation flags 
		&dwThreadId);			// returns the thread identifier 

	return(S);
}


bool Winsock_Interface::Start()
{
	bool Result = false;
	System::Logging.Writeln("Changing interface (" + GetAddress() + ") to state to: Started");

	Lock.Lock();
	if (Initialised)
		{
		State = SOCKET_RUNNING;
		Result = true;
		}
	else
		{
		State = SOCKET_RUNNING;
		Result = false;
		}
		
	Lock.Unlock();
	
	return(Result);
}



SOCKET Winsock_Interface::GetSocket()
{
	SOCKET *s = NULL;
	Lock.Lock();
		s = &s0k;
	Lock.Unlock();

return(*s);
}

int Winsock_Interface::GetState()
{
	int S;

	Lock.Lock();
		S = State;
	Lock.Unlock();

	return(S);
}




bool Winsock_Interface::Stop()
{
	System::Logging.Writeln("Changing interface (" + GetAddress() + ") to state to: Stopped");
	Lock.Lock();
		State = SOCKET_PAUSED;
	Lock.Unlock();

	return(true);
}

bool Winsock_Interface::Terminate()
{
	System::Logging.Writeln("Changing interface (" + GetAddress() + ") to state to: Terminate");
	Lock.Lock();
		State = SOCKET_TERMINATE;
	Lock.Unlock();

	return(true);
}




DWORD WINAPI Process(LPVOID lpParam)
{

	Winsock_Interface *I = (Winsock_Interface *)lpParam;

	stringstream ss;
	char pak[PAKSIZE];
	DWORD bytes;
	//char Buff[256];

	//bool Processing = true;
	SOCKET S = I->GetSocket();

		while (I->GetState() != Winsock_Interface::SOCKET_TERMINATE)
		{

			if (I->GetState() == Winsock_Interface::SOCKET_RUNNING)
			{
				memset(pak, 0, sizeof(pak));
				if ((bytes = recv(S, pak, sizeof(pak), 0)) == SOCKET_ERROR)
				{
					System::Logging.Writeln("Error getting data on socket for interface " + I->GetAddress());
				}
				else
				{
					Packet *P = IP::CreatePacket((const u_char *)pak);

					//ss.str("");
					//cout << Packet::to_string(P) << endl;

					RuleEngine::ProcessPacket(P);

					delete P;
				}
			}
			else
			{
				Sleep(1);
			}

		}

		System::Logging.Writeln("Killing thread for interface " + I->GetAddress());
		delete(I);
		ExitThread(SUCCESS);

return(true);
}


