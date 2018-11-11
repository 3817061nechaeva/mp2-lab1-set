// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower=mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower=s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower=BitField.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if((Elem < 0)||(Elem > MaxPower))
		throw -1;
	else 
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if((Elem<0) || (Elem>MaxPower))
		throw -1;
	else 
	return BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if((Elem < 0) || (Elem > MaxPower))
		throw -1;
	else 
	return BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower)
		return 0;
	else
		if (BitField != s.BitField)
			return 0;
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return !(*this == s);;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet temp(max(MaxPower, s.MaxPower));
	temp.BitField = BitField | s.BitField;
	return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < 0 || Elem >= MaxPower)
		throw -1;
	BitField.SetBit(Elem);
	return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem < 0 || Elem >= MaxPower)
		throw -1;
	BitField.ClrBit(Elem);
	return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet temp(max(MaxPower, s.MaxPower));
	temp.BitField = BitField & s.BitField;
	return temp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet temp(MaxPower);
	temp.BitField = ~BitField;
	return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i;
	while(istr>>i)
	{
		if(i>-1 && i<s.MaxPower)
			s.BitField.SetBit(i);
		else
			break;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr<<"{";
	for(int i=0; i<s.BitField.GetLength();i++)
	{
		if(s.BitField.GetBit(i)!=0)
			ostr<<i<<" ";
	}
	ostr<<"}";
	return ostr;
}
