#include <iostream>
#include <list>
#include <GlobalTypes.h>
#include <PortRange.h>
#include <string>

using namespace std;

const Int32 PORT_MIN = 1;
const Int32 PORT_MAX = 65535;


Port::Port()
{
	_Port = PORT_NOT_SET;
}

Port::Port(Int32 P)
{
	set(P);
}

Int32 Port::get() const
{
	return(_Port);
}

bool Port::set(Int32 P)
{
	if (P == PORT_ANY)
	{
		_Port = P;
		return(true);
	}

	if(isInRange(P))
	{
		_Port = P;
		return(true);
	}

return(false);
}

bool Port::isInRange(Int32 P)
{

	if (P >= PORT_MIN && P <= PORT_MAX)
		return(true);

return(false);
}

bool Port::isSet()
{
	if (_Port != PORT_NOT_SET)
		return(true);

return(false);
}





/*
Port Range Class
*/

PortRange::PortRange()
{
	
}

PortRange::PortRange(Int32 Min, Int32 Max)
{
	SetRange(Min, Max);
}


PortRange::~PortRange()
{

}



bool PortRange::SetRange(Int32 Min, Int32 Max)
{
	bool Result = false;

	Port *A = new Port();
	Port *B = new Port();

	if (A->set(Min) && B->set(Max))
	{
		Result = SetRange(A, B);
	}

	delete A;
	delete B;

return(Result);
}


bool PortRange::SetRange(Port *Min, Port *Max)
{

	if ((Min != NULL) && (Max != NULL))
	{
		_Bottom.set(Min->get());
		_Top.set(Max->get());
		return(true);
	}

return(false);
}



bool PortRange::IsInRange(Int32 P) 
{
	if (_Bottom.get() == PORT_ANY || _Top.get() == PORT_ANY)
		return(true);

	if ((P >= _Bottom.get()) && (P <= _Top.get()))
	{
		return(true);
	}

return(false);
}


Simple_Port_Range PortRange::GetRange() const
{
	Simple_Port_Range S;
	S.Min = _Bottom.get();
	S.Max = _Top.get();
	return(S);
}










PortRange_List::PortRange_List()
{
}

PortRange_List::~PortRange_List()
{
	//need to remove all entries in our list

	while (this->size() > 0)
	{
		PortRange *R = this->front();
		this->erase(this->begin());
		delete R;
	}

	//clear();
}








bool PortRange_List::Contains(Port P) const
{
	PortRange *R;

	for (Int32 i = 0; i < this->size(); i++)
	{
		R = (PortRange *)this->at(i);

		if (R != NULL)
		{
			if (R->IsInRange(P.get()))
			{
				return(true);
			}
		}

	}

return(false);
}


//Shortcut to add single Port
bool  PortRange_List::Add(Port P)
{
	PortRange *Range = new PortRange();
	Range->SetRange(&P, &P);

	push_back(Range);

	return(true);
}



PortRange_List* PortRange_List::Copy()
{
	PortRange_List *NewList = new PortRange_List();

	for (int i = 0; i < this->size(); i++)
	{
		Simple_Port_Range P = this->at(i)->GetRange();
		PortRange *NewRange = new PortRange(P.Min,P.Max);
		NewList->push_back(NewRange);
	}
	return(NewList);
}
