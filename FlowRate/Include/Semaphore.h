#pragma once
#include <Windows.h>


#define MAX_SEM_COUNT 1

class Semaphore
{

private:

	HANDLE ghSemaphore;

public:

	Semaphore();
	~Semaphore();

	bool Lock(DWORD MaxWait);
	bool Lock();			//With infinate wait
	bool Unlock();

};