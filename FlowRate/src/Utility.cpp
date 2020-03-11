#include <Utility.h>

int StringToInt(string Input)
{
	if (Input.size() > 0)
	{
		try
		{
			int Val = stoi(Input);
			return(Val);
		}
		catch (exception e)
		{
			//System::Logging.Writeln("Failed to convert int from: " + Input);
		}
	}
	return(INVALID_NUMBER);
}



string IntToString(Int32 Input)
{
	stringstream ss;
	ss << Input;
	return(ss.str());
}
