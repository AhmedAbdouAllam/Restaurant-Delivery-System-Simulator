#pragma once
#include "Generic_DS/Node.h"
template < typename T>
class Stack
{
	Node<T>*Top;
public:
	Stack();
	bool isEmpty()const;
	bool pop(T&it);
	T peek()const;
	bool push(T it);
};
template < typename T>
Stack<T> ::Stack()
{
	Top = NULL;
}
template < typename T>
bool Stack<T> ::isEmpty()const
{
	if (Top)
		return false;
	return true;
}
template < typename T>
T Stack<T> ::peek()const
{
	return Top->getItem();
}
template < typename T>
bool Stack<T> ::pop(T&it)
{
	if (isEmpty())return false;
	Node<T>*Temp = Top;
	Top = Top->getNext();
	it = Temp->getItem();
	delete Temp;
	return true;
}
template < typename T>
bool Stack<T> ::push(T it)
{
	Node<T>*Added = new Node<T>(it);
	if (!Added)return false;
	Added->setNext(Top);
	Top = Added;
	return true;
}