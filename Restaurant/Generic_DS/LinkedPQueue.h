#ifndef LINKED_PQUEUE_
#define LINKED_PQUEUE_

#include "Node.h"
#include "PQueueADT.h"
using namespace std;


template <typename T>
class LinkedPQueue :public PQueueADT<T>
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	LinkedPQueue()
	{
		backPtr = nullptr;
		frontPtr = nullptr;
	}

	bool isEmpty() const
	{
		return frontPtr ? 0 : 1;
	}


	void PrintList() const
	{
		Node<T> * temp = frontPtr;
		while (temp)
		{
			cout << temp->getItem() << " ";
			temp = temp->getNext();
		}
	}

	bool enqueue(const T& newEntry)
	{
		Node<T>* newN = new Node<T>(newEntry);
		Node<T>*prev = frontPtr;
		if (isEmpty())
		{
			frontPtr = newN;
			backPtr = frontPtr;
		}
		else if (!prev->getNext() && prev->getItem() < newEntry)
		{
			newN->setNext(frontPtr);
			backPtr = frontPtr;
			frontPtr = newN;
			return 1;
		}
		else
		{
			if (prev->getItem() < newEntry)
			{
				newN->setNext(frontPtr);
				frontPtr = newN;
				return 1;
			}
			while (prev->getNext())
			{
				if (prev->getNext()->getItem() < newEntry)
				{
					newN->setNext(prev->getNext());
					prev->setNext(newN);
					break;
				}
				prev = prev->getNext();
			}

			if (prev == backPtr)
			{
				backPtr->setNext(newN);
				backPtr = newN;
				return 1;
			}
		}

		return 1;
	}

	bool dequeue(T& frntEntry)
	{
		if (isEmpty())
			return 0;
		Node<T>* nodeToDeletePtr = frontPtr;
		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();

		if (nodeToDeletePtr == backPtr)
			backPtr = nullptr;

		delete nodeToDeletePtr;
		return 1;
	}

	bool peek(T& frntEntry)  const
	{
		return frontPtr ? 1, frntEntry = frontPtr->getItem() : 0;
	}

	~LinkedPQueue()
	{

		T temp;
		while (dequeue(temp));
	}

	LinkedPQueue(const LinkedPQueue<T> & LQ)
	{
		Node<T>* temp = LQ.frontPtr;
		if (!temp)
		{
			LinkedPQueue();
			return;
		}
		Node<T>* newN = new Node<T>(temp->getItem());
		frontPtr = backPtr = newN;
		temp = temp->getNext*();

		while (temp)
		{
			Node<T>* newN = new Node<T>(temp->getItem());
			backPtr->setNext(newN);
			backPtr = newN;
			temp = temp->getNext();
		}

	}


};

#endif