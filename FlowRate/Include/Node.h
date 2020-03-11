#pragma once

using namespace std;

#define NODE_LESS -1
#define NODE_GREATER 1
#define NODE_EQUAL 0

template <class T>
class Node
{
private:

public:

	Node *Left;
	Node *Right;
	Node *Parent;

	T *Data;

	Node();
	Node(T *N);
	~Node();

};



template <class T>
Node<T>::Node()
{
	//Data = *T;
	Data = NULL;
	Left = NULL;
	Right = NULL;
	Parent = NULL;
}

template <class T>
Node<T>::Node(T *N)
{
	Data = N;
	Left = NULL;
	Right = NULL;
	Parent = NULL;
}



template <class T>
Node<T>::~Node()
{

	if (Left != NULL)
		delete Left;

	if (Right != NULL)
		delete Right;

}