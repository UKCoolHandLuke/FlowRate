#pragma once


#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#ifndef _WINSOCK2API_
	#include <WinSock2.h>
	#include <Mstcpip.h>
#endif



#include <IP_Address.h>
#include <RuleEngine.h>
#include <Status.h>
#include <Semaphore.h>


#pragma comment(lib, "ws2_32.lib")

#define HOSTNAME_LEN 1024
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
#define PAKSIZE 65536

static short promiscuous = 1;


DWORD WINAPI Process(LPVOID lpParam);		//thread entry point



class Winsock_Interface
{

private:

IP_Address		_IP;
RuleEngine		_RuleEngine;
int				State = SOCKET_PAUSED;
bool			Initialised = false;
HANDLE			InterfaceThread;	//may need to be destroyed after use (this may need to be a structure)

SOCKET			s0k;			//Our listening Socket
RuleEngine		Rules;			//Our list of rules for this interface

Semaphore		Lock;

bool Initialise_Interface();
Status Init();

public:

	static const int SOCKET_PAUSED		= 0;
	static const int SOCKET_RUNNING		= 1;
	static const int SOCKET_TERMINATE	= 2;

	Winsock_Interface(string IP);
	~Winsock_Interface();

	string GetAddress();	//returns the string version of our IP
	SOCKET GetSocket();
	int GetState();

	bool Start();
	bool Stop();
	bool Terminate();
};
