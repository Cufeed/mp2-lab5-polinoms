#pragma once
#include "TNode.h"
#include <iostream>
using namespace std;

template<class T>
class TList
{
protected:
	TNode<T>* pFirst; // первое звено
	TNode<T>* pCurrent; // текущее звено
	TNode<T>* pPrevious; // звено перед текущим
	TNode<T>* pLast; // последнее звено
	TNode<T>* pStop; // значение указателя, означающего конец списка
	int length; // количество звеньев в списке

public:

	TList();
	~TList();
	int GetLength() { return length; }
	bool IsEmpty(); // список пуст ?
	// вставка звеньев
	void InsertFirst(T item); // перед первым
	void InsertCurrent(T item); // перед текущим 
	void InsertLast(T item);  // вставить последним 

	// удаление звеньев
	void DeleteFirst(); // удалить первое звено 
	void DeleteCurrent(); // удалить текущее звено

	void GoNext(); // сдвиг вправо текущего звена
	// (=1 после применения GoNext для последнего звена списка)

	void Reset(); // установить на начало списка
	bool IsEnd();  // список завершен ?

	T GetCurrentItem();
	void SetCurrentItem(T item) { pCurrent->value = item; }


};
template <class T>
TList<T>::TList()
{
	pFirst = nullptr;
	pCurrent = nullptr;
	pPrevious = nullptr;
	pLast = nullptr;
	pStop = nullptr;
	length = 0;
}

template <class T>
TList<T>::~TList()
{
	Reset();
}

template <class T>
bool TList<T>::IsEmpty()
{
	return length == 0;
}

template <class T>
void TList<T>::InsertFirst(T item)
{
	TNode<T>* newNode = new TNode<T>;
	newNode->value = item;
	newNode->pNext = pFirst;
	pFirst = newNode;
	if (length == 0) {
		pLast = newNode;
		pStop = newNode->pNext;
	}
	length++;
}

template <class T>
void TList<T>::InsertLast(T item)
{
	if (length == 0) {
		InsertFirst(item);
	}
	else {
		TNode<T>* newNode = new TNode<T>;
		newNode->value = item;
		newNode->pNext = pStop; //=================обозначить пстоп?
		pLast->pNext = newNode;
		pLast = newNode;
		length++;
		pStop = newNode->pNext;
	}
}



template <class T>
void TList<T>::InsertCurrent(T item)
{
	if (pCurrent == pFirst) {
		InsertFirst(item);
	}
	else {
		TNode<T>* newNode = new TNode<T>;
		newNode->value = item;
		newNode->pNext = pCurrent;
		pPrevious->pNext = newNode;
		pPrevious = newNode;
		length++;
	}
}

template <class T>
void TList<T>::DeleteFirst()
{
	if (length == 0) {
		throw "List is empty";
	}
	TNode<T>* temp = pFirst;
	pFirst = pFirst->pNext;
	if (pFirst != nullptr) {
		pStop = pFirst->pNext;
	}
	delete temp;
	length--;
	if (length == 0) {
		pCurrent = nullptr;
		pPrevious = nullptr;
		pLast = nullptr;
		pStop = nullptr;
	}
}

template <class T>
void TList<T>::DeleteCurrent()
{
	if (length == 0) {
		throw "List is empty";
	}
	if (pCurrent == pFirst) {
		DeleteFirst();
	}
	else {
		TNode<T>* temp = pCurrent;
		pPrevious->pNext = pCurrent->pNext;
		if (pCurrent == pLast) {
			pLast = pPrevious;
			pStop = pLast->pNext;
		}
		pCurrent = pCurrent->pNext;
		delete temp;
		length--;
	}
}

template <class T>
T TList<T>::GetCurrentItem()
{
	if (IsEmpty())
		throw std::out_of_range("Empty");
	if (pCurrent == pStop) {
		throw "No current item";
	}
	return pCurrent->value;
}

template <class T>
void TList<T>::Reset()
{
	while (pFirst != nullptr) {
		TNode<T>* temp = pFirst;
		pFirst = pFirst->pNext;
		delete temp; //111111111111111111111111111111111111111111111	
	}
	pCurrent = nullptr;
	pPrevious = nullptr;
	pLast = nullptr;
	pStop = nullptr;
	length = 0;
}

template <class T>
void TList<T>::GoNext()
{
	if (pCurrent != pStop) {
		pPrevious = pCurrent;
		pCurrent = pCurrent->pNext;
	}
}

template <class T>
bool TList<T>::IsEnd()
{
	return pCurrent == pStop;
}