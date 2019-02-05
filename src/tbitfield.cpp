// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"


TBitField::TBitField(int len)
{
  if (len <= 0)
    throw - 1;

  BitLen = len;
  MemLen = (len + 31) << 5;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
    pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
    pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
  delete[]pMem;
  pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n < 0 || n >= BitLen)
    throw - 1;
  return n << 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0 || n >= BitLen)
    throw - 1;
  return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n >= BitLen)
    throw - 1;
  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n >= BitLen)
    throw - 1;
  pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n < 0) || (n >= BitLen))
    throw - 1;
  return (pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this != &bf)
  {
    delete[]pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
      pMem[i] = bf.pMem[i];
  }
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  int sr = 1;
  if (BitLen != bf.BitLen)
    sr = 0;
  else
  {
    for (int i = 0; i < MemLen; i++)
    {
      if (pMem[i] != bf.pMem[i])
      {
        sr = 0;
        break;
      }
    }
  }
  return sr;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  TBitField temp(max(BitLen, bf.BitLen));
  for (int i = 0; i < MemLen; i++)
    temp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    temp.pMem[i] |= bf.pMem[i];
  return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  TBitField temp(max(BitLen, bf.BitLen));
  for (int i = 0; i < MemLen; i++)
    temp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    temp.pMem[i] &= bf.pMem[i];
  return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField temp(BitLen);
  for (int i = 0; i < BitLen; i++)
  {
    if (this->GetBit(i) == 0)
      temp.SetBit(i);
  }
  return temp;
}


istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  string str;
  istr >> str;
  if (str.size() != bf.GetLength())
    throw - 1;
  for (int i = 0; i < bf.BitLen; i++)
  {
    if (str[i] == '0')
      bf.ClrBit(i);
    else if (str[i] == '1')
      bf.SetBit(i);
    else
      throw - 1;
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.BitLen; i++)
  {
    if (bf.GetBit(i))
      ostr << 1;
    else
      ostr << 0;
  }
  return ostr;
}
