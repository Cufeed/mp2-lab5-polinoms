#pragma once
#include "TList.h"
using namespace std;


template<class T>
class THeadList : public TList<T>
{
protected:
	TNode<T>* pHead;  // ���������, pFirst - ����� �� pHead
public:
	THeadList();
	~THeadList();
	void InsertFirst(T item); // ������� ������� ����� ���������
	void DeleteFirst(); // ������� ������ �����
};

template<class T>
THeadList<T>::THeadList()
{
	pHead = nullptr;
	pHead = new TNode<T>;
	pHead->pNext = pStop;
	TList<T>::pFirst = pHead;
	
}

template<class T>
THeadList<T>::~THeadList()
{
	Reset();
/*	TList<T>::Reset();*/ // ���� �� ������(� �� �������� ������!)
	while (!IsEnd()) {
		DeleteFirst();
	}
	//delete pHead;
}

template <class T>
void THeadList<T>::InsertFirst(T item)
{
	TNode<T>* newNode = new TNode<T>;
	newNode->value = item;
	newNode->pNext = pFirst;
	pFirst = newNode;
	pStop = newNode->pNext;
	length++;
}

template <class T>
void THeadList<T>::DeleteFirst()
{
	TList<T>::Reset();
	if (!TList<T>::IsEnd()) {
		TList<T>::DeleteCurrent(); // 1 ����� ��������� ��� � �����
	}
}