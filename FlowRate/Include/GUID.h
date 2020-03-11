#include <algorithm>
#include <string>

using namespace std;

#pragma once

//#define GUID char*

#define GUID string


class UniqueID
{

private:

public:

	UniqueID();
	~UniqueID();

	static GUID GenerateGUID();
};
