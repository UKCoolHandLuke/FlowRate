#include <Semaphore.h>

Semaphore::Semaphore()
{
	ghSemaphore = CreateSemaphore(NULL, 1, MAX_SEM_COUNT, NULL);

}

Semaphore::~Semaphore()
{
	CloseHandle(ghSemaphore);
}


bool Semaphore::Lock()
{
	return(Lock(INFINITE));
}


bool Semaphore::Lock(DWORD MaxWait)
{
	DWORD dwWaitResult;

	dwWaitResult = WaitForSingleObject(ghSemaphore, MaxWait);

	if (dwWaitResult == WAIT_OBJECT_0)
		return(true);

	return(false);
}


bool Semaphore::Unlock()
{

	if (ReleaseSemaphore(ghSemaphore, 1, NULL))
		return(true);


	return(false);
}
