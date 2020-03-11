#include <GUID.h>

GUID UniqueID::GenerateGUID()
{
	string result;
	char s[21];
	int len = sizeof(s)-1;


	memset(s, NULL, len);

	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < (len - 1); ++i)
	{
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	s[len] = 0;

	result = s;

return(result);
}


