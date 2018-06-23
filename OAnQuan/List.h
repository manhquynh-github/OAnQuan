#pragma once
#include <iostream>
#include "Node.h"
using namespace std;

template <class T>
class List
{
private:
	Node<T> *pHead;
	int Count;

	
	Node<T> *GetNodeByData(T value) const;
public:
	Node<T> *GetNodeByIndex(int index) const;

	List();

	int getCount() const;
	Node<T> *Front() const;

	Node<T> *Insert(const T &value, int index = -1);
	Node<T> *Add(const T &value);
	void AddRange(List<T> Collection);

	Node<T> *Remove(const T &value);
	Node<T> *RemoveAt(int index = -1);
	void RemoveRange(List<T> Collection);

	T Search(T value) const;
	int IndexOf(T value) const;

	T operator[](int index) const;

	void Clear();
	void Print();

	~List();
};

template<class T>
inline Node<T>* List<T>::GetNodeByIndex(int index) const
{
	if (index >= Count || index < 0)
		std::cout << "ERR: Index out of bounds.";
	else
	{
		if (index == 0)
			return pHead;
		else if (index == Count - 1)
			return pHead->getpPrev();

		Node<T> *node = pHead;

		for (int i = 0; (i < Count) && (i != index); i++)
			node = node->getpNext();

		return node;
	}

	return nullptr;
}

template<class T>
inline Node<T>* List<T>::GetNodeByData(T value) const
{
	Node<T> *node = nullptr;

	if (Count > 0)
	{
		node = pHead;

		do
		{
			node = node->getpNext();
		} while ((node != pHead) && (node->getData() != value));
	}

	return node;
}

template <class T>
List<T>::List()
{
	pHead = nullptr;
	Count = 0;
}

template<class T>
inline int List<T>::getCount() const
{
	return Count;
}

template<class T>
inline Node<T>* List<T>::Front() const
{
	return pHead;
}

template<class T>
inline Node<T>* List<T>::Insert(const T &value, int index)
{
	if (index == -1)
		index = Count;

	if (index > Count || index < 0)
	{
		std::cout << "ERR: (Insert) Index out of bounds.";
		return nullptr;
	}

	Node<T> *newnode = new Node<T>(value);

	if (!newnode) return nullptr;

	if (Count == 0)
	{
		pHead = newnode;
		pHead->setpNext(pHead);
		pHead->setpPrev(pHead);
	}
	else if (index == Count) // InsertTail
	{
		newnode->setpPrev(pHead->getpPrev());
		newnode->setpNext(pHead);
		pHead->getpPrev()->setpNext(newnode);	
		pHead->setpPrev(newnode);
	}
	else if (index == 0) // InsertHead
	{
		newnode->setpNext(pHead);
		newnode->setpPrev(pHead->getpPrev());
		pHead->getpPrev()->setpNext(newnode);
		pHead = newnode;
	}
	else
	{
		Node<T> *currentnode = GetNodeByIndex(index);
		newnode->setpNext(currentnode);
		newnode->setpPrev(currentnode->getpPrev());
		currentnode->getpPrev()->setpNext(newnode);
		currentnode->setpPrev(newnode);
	}

	Count++;
	return newnode;
}

template<class T>
inline Node<T>* List<T>::Add(const T &value)
{
	return Insert(value);
}

template<class T>
inline void List<T>::AddRange(List<T> Collection)
{
	if (Collection.Count > 0)
	{
		Node<T> *node = Collection.pHead;
		do
		{
			this->Add(node->getData());
			node = node->getpNext();
		} while (node != Collection.pHead)
	}
}

template<class T>
inline Node<T>* List<T>::Remove(const T &value)
{
	Node<T> *node = nullptr;

	if (Count > 0)
	{
		node = pHead;
		int i = 0;
		do
		{
			i++;
			node = node->getpNext();
		} while ((node != pHead) && (node->getData() != value));

		return RemoveAt(i);
	}

	return node;
}

template<class T>
inline Node<T>* List<T>::RemoveAt(int index)
{
	if (index == -1)
		index = Count - 1;

	if (index < 0 || index >= Count)
	{
		cout << "ERR: (RemoveAt) Index out of bounds.";
		return nullptr;
	}

	Node<T> *remove = nullptr;

	if (Count > 0)
	{
		if (Count == 1)
		{			
			pHead->setpNext(nullptr);
			pHead->setpPrev(nullptr);
			remove = pHead;
			pHead = nullptr;
		}
		else if (index == 0) // Remove Head
		{
			remove = pHead;
			pHead->getpNext()->setpPrev(pHead->getpPrev());
			pHead->getpPrev()->setpNext(pHead->getpNext());
			pHead = pHead->getpNext();
			remove->setpNext(nullptr);
			remove->setpPrev(nullptr);
		}
		else if (index == Count - 1) // Remove Tail
		{
			remove = pHead->getpPrev();
			pHead->setpPrev(remove->getpPrev());
			remove->getpPrev()->setpNext(pHead);
			remove->setpNext(nullptr);
			remove->setpPrev(nullptr);
		}
		else
		{
			remove = GetNodeByIndex(index);
			remove->getpPrev()->setpNext(remove->getpNext());
			remove->getpNext()->setpPrev(remove->getpPrev());
			remove->setpNext(nullptr);
			remove->setpPrev(nullptr);
		}

		Count--;
	}

	return remove;
}

template<class T>
inline void List<T>::RemoveRange(List<T> Collection)
{
	if (Collection.Count > 0)
	{
		Node<T> *node = Collection.pHead;

		do
		{
			delete Remove(node->getData());
			node = node->getpNext();
		} while (node != Collection.pHead);
	}
}

template<class T>
inline void List<T>::Clear()
{
	while (Count > 0)
	{
		delete RemoveAt();
	}
}

template<class T>
inline T List<T>::operator[](int index) const
{
	if (index >= Count || index < 0)
		cout << "ERR: Index out of bounds.";
	else
		return this->GetNodeByIndex(index)->getData();

	return T();
}

template<class T>
inline T List<T>::Search(T value) const
{
	Node<T> *node = this->GetNodeByData(value);
	if (node == nullptr) return NULL;
	return node->getData();
}

template<class T>
inline int List<T>::IndexOf(T value) const
{
	int index = -1;

	if (Count > 0)
	{
		Node<T> *node = pHead;

		for (int i = 0; i < Count && node->getData() != value; i++)
			node = node->getpNext();

		if (i != Count) return i;
	}
	return -1;
}

template<class T>
inline void List<T>::Print()
{
	if (Count > 0)
	{
		Node<T> *node = pHead;
		do
		{
			cout << node->getData() << endl;
			node = node->getpNext();
		} while (node != pHead);
	}
}

template <class T>
List<T>::~List()
{
	//Clear();
}
