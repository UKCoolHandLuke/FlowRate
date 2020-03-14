#pragma once

#include <iostream>
#include <sstream>
#include <stdarg.h>
#include <sstream>
#include <GlobalTypes.h>

using namespace std;

#define INVALID_NUMBER	-1


int StringToInt(string Input);
string IntToString(Int32 Input);
string ExpandString(const char *sText...);
