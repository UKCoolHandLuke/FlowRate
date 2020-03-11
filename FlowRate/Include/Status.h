#pragma once

#include <GlobalTypes.h>
#include <System.h>

enum Status_Result
{
	SUCCESS,
	FAILURE
};



class Status
{

private:

	Int32 ErrorCode = 0;
	string Message;


public:

	Status();
	~Status();

	void Start();
	Status_Result End();
	Status_Result Result;


	void SetResult(Status_Result R);
	Status_Result GetResult();

	void SetMessage(string M);
	string GetMessage();
};
