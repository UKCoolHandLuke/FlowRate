#pragma once

#include <Winsock_Interface.h>
#include <vector>
#include <set>

class Winsock_Manager
{

private:

	Semaphore Lock;

	vector<Winsock_Interface *> Sockets;

	Winsock_Interface *GetSocket(IP_Address &I);

public:

	Winsock_Manager();
	~Winsock_Manager();

	bool Add_Interface(IP_Address I);		//Add an interface by IP
	bool Remove_Interface(IP_Address I);	//Remove an interface by IP
	//GetState();							//Return the status of an interface. RUNNING, STOPPED, ERROR.

	bool Start(string IP);	//Start an interface
	bool Stop(string IP);	//Stop an interface


};
