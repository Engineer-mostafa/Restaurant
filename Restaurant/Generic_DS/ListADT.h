#pragma once
#include"Node.h"
#include<iostream>
using namespace std;
template<class T>
class ListADT
{
private:
	Node<T>* Head;
public:
	ListADT()
	{
		Head = nullptr;
	}
	///////////////////////////////////////////////////////////////////
	void InsertEnd(T newItem)
	{
		Node<T>* newNode = new Node<T>(newItem);
		newNode->setNext(nullptr);
		if (!Head)
			Head = newNode;
		else
		{
			Node<T>* ptr = Head;
			while (ptr->getNext() != nullptr)
				ptr = ptr->getNext();
			ptr->setNext(newNode);
		}
	}
	///////////////////////////////////////////////////////////////////
	bool DeleteNode(T Item)
	{
		if (!Head)
			return false;
		else if (Head->getItem() == Item && !Head->getNext())
		{
			Node<T>* ptr = Head;
			Head = nullptr;
			delete ptr;
			return true;
		}
		else if (Head->getItem() == Item)
		{
			Node<T>* ptr = Head;
			Head = Head->getNext();
			delete ptr;
			return true;
		}
		else {
			Node<T>* prev = Head;
			Node<T>* curr = Head->getNext();
			while (curr)
			{
				if (curr->getItem() == Item)
				{
					Node<T>* ptr = curr;
					prev->setNext(curr->getNext());
					delete ptr;
					curr = prev = nullptr;
					delete curr, prev;
					return true;
				}
				prev = curr;
				curr = curr->getNext();
			}
		}
		return false;

	}
	///////////////////////////////////////////////////////////////////////////
	void Print()
	{
		Node<T>* ptr = Head;
		while (ptr)
		{
			cout << ptr->getItem() << " ";
			ptr = ptr->getNext();
		}

	}
	bool DeleteFirst(T& IT)
	{
		if (Head)
		{
			IT = Head->getItem();
			Node<T>* temp = Head;
			Head = Head->getNext();
			delete temp;
			temp = nullptr;
			return true;
			
		}
	}

};

