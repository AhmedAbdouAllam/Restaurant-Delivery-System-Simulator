#pragma once
#include "Generic_DS/Node.h"
template < typename T>
class LinkedList
{
	Node<T>* Head;
	int count;
	Node<T>* GetNodeAt(int Pos)const;
public:
	LinkedList();
	bool remove(int Pos);
	bool insert(T it, int pos);
	bool isEmpty()const ;
	void clear();
	int getLength()const;
	T GetEntery(int Pos)const;
	T replace(int Pos, T newE);
	bool InsertEnd(T item);
};
template < typename T>
Node<T>* LinkedList<T>::GetNodeAt(int Pos)const
{
	Pos = Pos - 1;
	if (Pos >= count)
		return nullptr;

	Node<T>* scPtr = Head;

	for (int i = 1; i <= Pos; i++)
		scPtr = scPtr->getNext();
	return scPtr;

}

template < typename T>
bool LinkedList<T>::insert(T it, int Pos)
{
	Node<T>*Added = new Node<T>(it);
	if (!Added || Pos > count + 1|| Pos <= 0) return false;
	if (!Head && Pos == 1)
	{
		Head = Added;
		count++;
		return true;
	}
	if (Pos != count + 1)
		Added->SetNext(GetNodeAt(Pos - 1)->getNext());
	GetNodeAt(Pos - 1)->setNext(Added);
	count++;
	return true;
}
template < typename T>
LinkedList<T>::LinkedList()
{
	count = 0;
	Head = nullptr;
}
template < typename T>
bool LinkedList<T>::remove(int Pos)
{
	if (Pos > count)return false;
	if (Pos <= 0)return false;
	
	Node<T>*Temp;

	if (Pos == 1)
	{
		Temp = Head;
		Head = Head->getNext();
		delete Temp;
		count--;
		return true;
	}
	Temp = GetNodeAt(Pos);
	if (!Temp) return false;
	GetNodeAt(Pos - 1)->setNext(Temp->getNext());
	delete Temp;
	count--;
	return true;
}
template < typename T>
bool LinkedList<T>::isEmpty()const
{
	if (count == 0)return true;
	return false;
}


template < typename T>
void LinkedList<T>::clear()
{
	Node<T>* ScPtr;
	while (Head)
	{
		ScPtr = Head;
		Head = Head->getNext();
		delete Scptr;
	}
}
template < typename T>
int LinkedList<T> ::getLength()const
{
	return count;
}

template < typename T>
T  LinkedList<T> ::GetEntery(int Pos)const
{
		return GetNodeAt(Pos)->getItem();
}
template < typename T>
T LinkedList<T> ::replace(int Pos, T newE)
{
	if (Pos == 1)
	{
		T = Head->getItem
			remove(1);
		insert(newE, 1);
	}
	else
	{
		Node<T>* rem;
		rem = GetNodeAt(Pos);
		Node<T>* Added = new Node<T>(newE);
		Added->setNext(GetNodeAt(Pos+1));
		GetNodeAt(Pos - 1)->setNext(Added);
		
		delete rem;
	}
}

template < typename T>
bool LinkedList<T> ::InsertEnd(T item)
{
	Node<T>*Added = new Node<T>(item);
	if (!Added)return false;
	if (!Head)
	{
		Head = Added;
		count++;
		return true;
	}
	Node<T>*ScPtr = Head;
	while (ScPtr->getNext())
		ScPtr = ScPtr->getNext();
	ScPtr->setNext(Added);
	count++;
	return true;
}

