#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iostream>

#include <Semaphore.h>

using namespace std;

enum LogLevel
{
	LOG_INFO		= 0,
	LOG_WARNING		= 10,
	LOG_CRITICAL	= 20,
	LOG_DEBUG		= 30
};


class Log
{

private:
	string filename;
	//static Log Create();

	bool Write(char *Text, bool endline);

	LogLevel Verbosity;
	bool Echo;
	
	Semaphore File_Lock;
	Semaphore Verbosity_Lock;
	
public:

	

	Log(string Filename);
	~Log();

	bool Write(string Text);
	bool Write(char *Text);
	
	bool Writeln(char *Text);
	bool Writeln(string Text);

	bool Writeln(const char * Text, LogLevel L);
	bool Writeln(string Text, LogLevel L);

	LogLevel getLogLevel();
	void setLogLevel(LogLevel L);

	bool getEcho();
	bool setEcho(bool tf);

};

