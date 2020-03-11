#include <Manager.h>



Manager::Manager(int iInterval)
{
	Paused = false;
	Interval = iInterval;
	ThreadHandle = CreateThread(NULL, 0, ThreadProc, this,	0,0);
}

Manager::~Manager()
{
}

//virtual method
bool Manager::Execute()
{
	return(true);
}


bool Manager::DoWork()
{
	while (true)
	{
		if (!Paused)
			{
			Execute();
			}
		Sleep(Interval);
	}
}


void *Manager::GetTask()
{
	TaskLock.Lock();
	if (Tasklist.size() > 0)
	{
		void *Task = Tasklist.front();
		Tasklist.erase(Tasklist.begin());
		TaskLock.Unlock();
		return(Task);
	}
	TaskLock.Unlock();
return(NO_TASK);
}


DWORD WINAPI Manager::ThreadProc(LPVOID lpParam)
{
	((Manager *)lpParam)->DoWork();
	return(0);
}


void Manager::Pause()
{
	Paused = true;
}

void Manager::Resume()
{
	Paused = false;
}

bool Manager::AddTask(void *T)
{
	TaskLock.Lock();
		Tasklist.push_back(T);
	TaskLock.Unlock();

return(true);
}




