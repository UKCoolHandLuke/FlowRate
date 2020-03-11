#pragma once

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <Semaphore.h>

using namespace std;

#define NO_TASK	NULL

class Manager
{

private:

	
	bool Paused;
	HANDLE ThreadHandle;
	//DWORD ThreadID;
	
    static DWORD WINAPI ThreadProc(LPVOID lpParam);
	bool DoWork();
	vector <void *>Tasklist;
	Semaphore TaskLock;

protected:

	int Interval;

public:

	Manager(int iInterval);
	~Manager();

	virtual bool Execute();
	void Pause();
	void Resume();

	bool AddTask(void *T);
	void *GetTask();

};



