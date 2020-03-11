#pragma once

#include <Action.h>
#include <System.h>
#include <string>
#include <Log.h>
#include <curl/curl.h>


struct upload_status {
	int lines_read;
};


class Action_Email : public Action
{

private:

	struct upload_status upload_ctx;

public:

	Action_Email();
	~Action_Email();


	Action_Result Execute(Action_Block *Block);

};