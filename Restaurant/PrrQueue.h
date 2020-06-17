#pragma once
#include "Generic_DS/Node.h"
template < typename T>
class PrrQueue
{
	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	PrrQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry,int Priority=0);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
};
template <typename T>
PrrQueue<T>::PrrQueue()
{
	backPtr=nullptr;
	frontPtr=nullptr;
}
template <typename T>
bool PrrQueue<T>::isEmpty() const
{
	if (frontPtr == nullptr || backPtr==nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PrrQueue<T>::enqueue(const T& newEntry,int Prr)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	if (!newNodePtr)
		return false;
	newNodePtr->setPrr(Prr);
	// Insert the new node
	if (isEmpty())
	{
		frontPtr = newNodePtr; // The queue is empty
		backPtr = newNodePtr;
		return true;
	}
	else if(backPtr->getPrr()>=Prr)
		{
		backPtr->setNext(newNodePtr);
		backPtr = newNodePtr;
		}
	else if (frontPtr->getPrr() < Prr)
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;;
	}
	else
	{
		Node<T>* ScPtr = frontPtr;

		while (ScPtr != backPtr && ScPtr)
		{
			if (ScPtr->getNext()->getPrr() < Prr)
				break;


			ScPtr = ScPtr->getNext();
		}
		if (ScPtr)
		{
			newNodePtr->setNext(ScPtr->getNext());
			ScPtr->setNext(ScPtr);
		}
	}
	return true;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PrrQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
	{
		backPtr = nullptr;
		frontPtr = nullptr;
	}
	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
template <typename T>
bool PrrQueue<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////
