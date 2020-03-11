#include <Status.h>


Status::Status()
{
}

Status::~Status()
{
}


void Status::Start()
{
	Message = "";
	ErrorCode = 0;
	Result = Status_Result::SUCCESS;
}


Status_Result Status::End()
{
	DWORD EC = GetLastError();
	ErrorCode = EC;
	
	if (ErrorCode != Status_Result::SUCCESS)
	{
		Result = Status_Result::FAILURE;
		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
		Message = messageBuffer;
	}

return(Result);
}


void Status::SetResult(Status_Result R)
{
	Result = R;
}

Status_Result Status::GetResult()
{
	return(Result);
}

void Status::SetMessage(string M)
{
	Message = M;
}

string Status::GetMessage()
{
	return(Message);
}


