#pragma once
template <class T>
class Node
{
private:
	T Data;
	Node *pNext, *pPrev;
public:
	Node();
	Node(const T &value);
	Node(const T &value, Node *pnext, Node *pprev);

	Node *getpNext() const;
	void setpNext(Node *pnext);
	Node *getpPrev() const;
	void setpPrev(Node *pprev);
	T getData() const;
	T *getData2();
	void setData(T value);

	~Node();

};

template<class T>
inline Node<T>::Node()
{
	Data = T();
	pNext = pPrev = nullptr;
}

template<class T>
inline Node<T>::Node(const T &value)
{
	Data = value;
	pNext = pPrev = nullptr;
}

template<class T>
inline Node<T>::Node(const T &value, Node * pnext, Node * pprev)
{
	Data = value;
	pNext = pnext;
	pPrev = pprev;
}

template<class T>
inline Node<T> * Node<T>::getpNext() const
{
	return pNext;
}

template<class T>
inline void Node<T>::setpNext(Node<T> * pnext)
{
	pNext = pnext;
}

template<class T>
inline Node<T> * Node<T>::getpPrev() const
{
	return pPrev;
}

template<class T>
inline void Node<T>::setpPrev(Node<T> * pprev)
{
	pPrev = pprev;
}

template<class T>
inline T Node<T>::getData() const
{
	return Data;
}

template<class T>
inline T * Node<T>::getData2()
{
	return &Data;
}

template<class T>
inline void Node<T>::setData(T value)
{
	Data = value;
}

template<class T>
inline Node<T>::~Node()
{
	if (pNext != nullptr)
		delete[] pNext;
	if (pPrev != nullptr)
		delete[] pPrev;
}
