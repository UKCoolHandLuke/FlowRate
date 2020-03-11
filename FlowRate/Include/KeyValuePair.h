#pragma once

#include <string>
#include <vector>
#include <GlobalTypes.h>


#define KEY_NOT_FOUND -1
#define VALUE_NOT_SET -1

using namespace std;

template <class T>
class KeyValuePair
{
private:
public:

	string Key="";
	T Value;

	KeyValuePair()
	{
	}

	~KeyValuePair()
	{
	}

	static KeyValuePair<T>* Create(string Key, T Value);
};


template <class T>
KeyValuePair<T> *KeyValuePair<T>::Create(string Key, T Value)
{
	KeyValuePair *KV = new KeyValuePair<T>();
	KV->Key = Key;
	KV->Value = Value;
	return(KV);
}





template <class T>
class KeyValuePair_List : public vector <KeyValuePair <T> *>
{

public:


	KeyValuePair_List();
	~KeyValuePair_List();


	//Return -1 on not found
	//Returns index if found
	Int32 ContainsKey(string Key);

	/*
	Return a Value given a key
	*/
	T getvalue(string Key);


	/*
	Set a value given a key
	Will also create a key if it doesnt exist
	*/
	bool setValue(string Key, T Value);




	/*
	Add a key to our current List (if the key doesnt already exist)
	*/
	bool Add(string Key, T Value);


	/*
	Add a key to our current List (if the key doesnt already exist)
	*/
	bool Remove(string Key);
};


template <class T>
KeyValuePair_List<T>::KeyValuePair_List()
{
}

template <class T>
KeyValuePair_List<T>::~KeyValuePair_List()
{
	//Cleanup any elements contained
	KeyValuePair<T> *KV;

	while (this->size() > 0)
	{
		KV = (KeyValuePair<T> *) this->at(0);
		Remove(KV->Key);
	}

}



//Return -1 on not found
//Returns index if found
template <class T>
Int32 KeyValuePair_List<T>::ContainsKey(string Key)
{

	KeyValuePair <T>*KV = NULL;

	for (Int32 i = 0; i < this->size(); i++)
	{
		KV = (KeyValuePair <T>*)this->at(i);
		if (KV->Key == Key)
		{
			return(i);
		}
	}

	return(KEY_NOT_FOUND);
}

template <class T>
T KeyValuePair_List<T>::getvalue(string Key)
{
	Int32 Index = ContainsKey(Key);
	KeyValuePair <T>*KV = NULL;

	if (Index != KEY_NOT_FOUND)
	{
		KV = (KeyValuePair <T>*)this->at(Index);
		return KV->Value;
	}

return(NULL);
}

template <class T>
bool KeyValuePair_List<T>::setValue(string Key, T Value)
{
	Int32 Index = ContainsKey(Key);
	KeyValuePair <T>*KV = NULL;

	if (Index == KEY_NOT_FOUND)
	{
		return Add(Key, Value);
	}
	else
	{
		KV = (KeyValuePair *)this->at(Index);
		KV->Value = Value;
		return(true);
	}

	return(false);
}

template <class T>
bool KeyValuePair_List<T>::Add(string Key, T Value)
{
	if (ContainsKey(Key) != KEY_NOT_FOUND)
		return(false);

	KeyValuePair<T> *KV = KeyValuePair<T>::Create(Key, Value);
	if (KV != NULL)
	{
		this->push_back(KV);
		return(true);
	}
	return (false);
}

template <class T>
bool KeyValuePair_List<T>::Remove(string Key)
{

	Int32 Index = ContainsKey(Key);
	KeyValuePair <T>*KV;

	if (Index != KEY_NOT_FOUND)
	{
		KV = at(Index);
		this->erase(this->begin() + Index);

		delete KV;
		return(true);
	}

	return(false);
}



