#pragma once
#include "THeadList.h"
#include "TMonom.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>

const int nonDisplayedZeros = 4; // Количество неотображаемых нулей при выводе коэффициента полинома
								 // Кол-во символов после запятой = 6 - nonDisplayedZeros


class TPolinom : public THeadList<TMonom>
{
public:
	TPolinom();
	TPolinom(TPolinom& other);
	TPolinom(string str);
	void re();
	TPolinom& operator=(TPolinom& other); // присваивание
	TPolinom& operator+(TPolinom& q); // сложение полиномов

	// дополнительно можно реализовать:
	void AddMonom(TMonom newMonom); // добавление монома
	TPolinom MultMonom(TMonom monom); // умножение мономов
	TPolinom AddPolinom(TPolinom& other); // добавление полинома
	TPolinom operator*(double coef); // умножение полинома на число
	TPolinom operator* (TPolinom& other); // умножение полиномов
	bool operator==(TPolinom& other); // сравнение полиномов на равенство
	string ToString(); // перевод в строку
	void ToCreed();
};

TPolinom::TPolinom() :THeadList<TMonom>::THeadList()
{
}

void TPolinom::re() {
	pCurrent = pFirst;
	pLast = pFirst;
}
TPolinom::TPolinom(TPolinom& other)
{
	if (this == &other) {}
	else {
		//TList<TMonom>::Reset();
		TMonom m;
		for (other.ToCreed(); !other.IsEnd(); other.GoNext()) {
			m = other.GetCurrentItem();
			TList<TMonom>::InsertLast(m);
			
		}
	}
	pCurrent = pFirst;

}

TPolinom::TPolinom(string str)
{	
	//TList<TMonom>::Reset();
	string monomStr;
	size_t startPos = 0;
	size_t endPos = str.find('+');
	while (endPos != string::npos) {
		monomStr = str.substr(startPos, endPos - startPos);
		TMonom m(monomStr);
		TList<TMonom>::InsertLast(m);
		startPos = endPos + 1;
		endPos = str.find('+', startPos);
	}
	monomStr = str.substr(startPos);
	TMonom m(monomStr);
	TList<TMonom>::InsertLast(m);
}

void TPolinom::ToCreed() {
	pCurrent = pFirst;
}

//bool TPolinom::operator==(TPolinom& other)
//{
//	if (GetLength() != other.GetLength()) {
//		return false;
//	}
//
//	ToCreed();
//	other.ToCreed();
//
//	for (int i = 0; !IsEnd(); GoNext()) {
//		if (other.IsEnd()) {
//			return false;
//		}
//
//		TMonom current = GetCurrentItem();
//		TMonom otherCurrent = other.GetCurrentItem();
//
//		if (current != otherCurrent) {
//			return false;
//		}
//
//		other.GoNext();
//	}
//
//	return true;
//}
TPolinom& TPolinom::operator=(TPolinom& other)
{
	//if (this == &other)
	//	return *this;
	//else {
		//TList<TMonom>::Reset();
		TMonom m;
		for (other.ToCreed(); !other.IsEnd(); other.GoNext())
		{
			m = other.GetCurrentItem();
			TList<TMonom>::InsertLast(m);
		}

		return *this;
	//}
}


TPolinom& TPolinom::operator+(TPolinom& other)
{
	TPolinom* result = new TPolinom(*this);
	*result = result->AddPolinom(other);
	TPolinom temp(*result);
	return *result;
}



void TPolinom::AddMonom(TMonom m)
{
	if (m.GetCoef() == 0)
		return;
	if (IsEmpty()) {
		THeadList<TMonom>::InsertLast(m);
		return;
	}

	for (ToCreed(); !IsEnd(); GoNext()) {
		TMonom current = GetCurrentItem();


		if (current.GetIndex() == m.GetIndex()) {
			current.SetCoef(current.GetCoef() + m.GetCoef());
			this->SetCurrentItem(current);
			//pCurrent->value = current;
			return;
		}
	}
	THeadList<TMonom>::InsertLast(m);
}

TPolinom TPolinom::MultMonom(TMonom monom)
{
	TPolinom result;
	for (ToCreed(); !IsEnd(); GoNext()) {
		TMonom m = GetCurrentItem();
		m.SetCoef(m.GetCoef() * monom.GetCoef());
		result.AddMonom(m);
	}
	return result;
}


TPolinom TPolinom::AddPolinom(TPolinom& other)
{
	TPolinom result;
	std::map<int, TMonom> monomMap;

	for (ToCreed(); !IsEnd(); GoNext()) {
		TMonom m = GetCurrentItem();
		monomMap[m.GetIndex()] = m;
	}

	for (other.ToCreed(); !other.IsEnd(); other.GoNext()) {
		TMonom m = other.GetCurrentItem();
		if (monomMap.count(m.GetIndex()) > 0) {
			monomMap[m.GetIndex()].SetCoef(monomMap[m.GetIndex()].GetCoef() + m.GetCoef());
		}
		else {
			monomMap[m.GetIndex()] = m;
		}
	}

	for (auto& pair : monomMap) {
		result.AddMonom(pair.second);
	}

	return result;
}



TPolinom TPolinom::operator*(double coef)
{
	TPolinom result;
	for (ToCreed(); !IsEnd(); GoNext()) {
		TMonom m = GetCurrentItem();
		m.SetCoef(m.GetCoef() * coef);
		result.AddMonom(m);
	}
	return result;
}

TPolinom TPolinom::operator*(TPolinom& other)
{
	TPolinom result;
	for (ToCreed(); !IsEnd(); GoNext()) {
		for (other.Reset(); !other.IsEnd(); other.GoNext()) {
			TMonom m = GetCurrentItem();
			m.SetCoef(m.GetCoef() * other.GetCurrentItem().GetCoef());
			result.AddMonom(m);
		}
	}
	return result;
}

bool TPolinom::operator==(TPolinom& other)
{
	if (GetLength() != other.GetLength()) {
		return false;
	}
	for (ToCreed(); !IsEnd(); GoNext()) {
		if (!other.IsEnd()) {
			other.GoNext();
		}
		if (!(GetCurrentItem() == other.GetCurrentItem())) {
			return false;
		}
	}
	return true;
}


string TPolinom::ToString()
{
	stringstream ss;
	this->pCurrent = this->pFirst;
	for (int i = 0; !IsEnd(); GoNext()) {
		TMonom m = GetCurrentItem();
		int index = m.GetIndex();
		int xExp = index / 100;
		int yExp = (index / 10) % 10;
		int zExp = index % 10;
		if (xExp != 0) {
			ss << m.GetCoef() << "x^" << xExp;
		}
		if (yExp != 0) {
			if (xExp != 0) {
				ss << " * ";
			}
			ss << m.GetCoef() << "y^" << yExp;
		}
		if (zExp != 0) {
			if (xExp != 0 || yExp != 0) {
				ss << " * ";
			}
			ss << m.GetCoef() << "z^" << zExp;
		}
		if (!IsEnd()) {
			ss << " + ";
		}
	}
	return ss.str();
}