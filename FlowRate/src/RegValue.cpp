#include <RegValue.h>

RegValue::RegValue()
{
	Value = NULL;
	Name = "";
}

RegValue::~RegValue()
{
	if (Value != NULL)
	{
		delete Value;
	}
}
