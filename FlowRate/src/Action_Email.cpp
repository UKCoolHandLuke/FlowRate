#include <Action_Email.h>



Action_Email::Action_Email()
{
	//LogObj = new Log("FirewallLog.txt");
	Properties.Add("NAME", "ACTION_EMAIL");
}

Action_Email::~Action_Email()
{
}


static const char *payload_text[] = {
""
};




static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
	struct upload_status *upload_ctx = (struct upload_status *)userp;
	const char *data;

	if ((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
		return 0;
	}

	data = payload_text[upload_ctx->lines_read];

	if (data) {
		size_t len = strlen(data);
		memcpy(ptr, data, len);
		upload_ctx->lines_read++;

		return len;
	}

	return 0;
}





Action_Result Action_Email::Execute(Action_Block *Block)
{

	Action_Result Result;
	stringstream ss;

	//Get our base properties
	//NEED TO REMOVE THE BLOCK WHEN FINISHED !

	if (Properties.ContainsKey("EMAIL_SERVER") == KEY_NOT_FOUND)
	{
		Result.Result = false;
		Result.Message = "No Email server provided";
		return(Result);
	}

	if (Properties.ContainsKey("EMAIL_FROM") == KEY_NOT_FOUND)
	{
		Result.Result = false;
		Result.Message = "No Email From provided";
		return(Result);
	}

	if (Properties.ContainsKey("EMAIL_TO") == KEY_NOT_FOUND)
	{
		Result.Result = false;
		Result.Message = "No Email To provided";
		return(Result);
	}


	string Email_From = Properties.getvalue("EMAIL_FROM");
	string Email_To = Properties.getvalue("EMAIL_TO");
	string Email_Server = Properties.getvalue("EMAIL_SERVER");


	/*
	Send the email
	*/

	CURL *curl;
	CURLcode res = CURLE_OK;
	curl = curl_easy_init();
	struct curl_slist *recipients = NULL;

	upload_ctx.lines_read = 0;

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "");
		curl_easy_setopt(curl, CURLOPT_MAIL_FROM, (char *)Email_From.c_str());
		recipients = curl_slist_append(recipients, (char *)Email_To.c_str());
		curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

		curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
		curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
		//curl_easy_setopt(curl, CURLOPT_READDATA, &payload_text);
		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			{
			Result.Result = false;
			Result.Message = curl_easy_strerror(res);
			//fprintf(stderr, "Action_Email failed: %s\n", curl_easy_strerror(res));
			}
		else
			{
			System::Logging.Writeln("Notification email sent to: " + Email_To);
			Result.Result = true;
			Result.Message = "Success";
			}


	curl_slist_free_all(recipients);
	curl_easy_cleanup(curl);

	return(Result);
	}
	

	return(Result);
}