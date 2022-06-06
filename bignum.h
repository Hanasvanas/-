#ifndef BIGNUM_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define PLUS		1		/* «начение плюса числа */
#define MINUS		-1		/* «начение минуса числа */
class bignum
{
private:
	vector<char> digits;         /* цифры числа */
	int signbit;			/* 1 - положительное -1 - отрицательное */
	int lastdigit;			/* индекс старшей цифры числа */
	//ѕреобразование строки в число
	bool str_to_bignum(const string s);
	//выровн€ть незначащие ноли
	void zero_justify();
	// умножить n на 10^d 
	void digit_shift(int d);
public:
	//установка знака числа
	void setsign(int s)
	{
		signbit = s;
	}
	// ѕерегрузка оператора стандартного вывода
	friend ostream& operator<<(ostream& output, const bignum& b);
	// ѕерегрузка оператора стандартного ввода
	friend istream& operator >> (istream & input, bignum &b);
	//сложение
	friend bignum operator+(const bignum& left, const bignum& right);
	friend bignum operator+(int left, const bignum& right);
	friend bignum operator+(const bignum& left, int right);
	//вычитание
	friend bignum operator-(const bignum& left, const bignum& right);
	friend bignum operator-(int left, const bignum& right);
	friend bignum operator-(const bignum& left, int right);
	//умножение
	friend bignum operator*(const bignum& left, const bignum& right);
	friend bignum operator*(int left, const bignum& right);
	friend bignum operator*(const bignum& left, int right);
	//деление
	friend bignum operator/(const bignum& left, const bignum& right);
	friend bignum operator/(int left, const bignum& right);
	friend bignum operator/(const bignum& left, int right);
	//остаток от делени€
	friend bignum operator%(const bignum& left, const bignum& right);
	friend bignum operator%(int left, const bignum& right);
	friend bignum operator%(const bignum& left, int right);
	//сравнени€
	friend bool operator<(const bignum& left, const bignum& right);
	friend bool operator<(int left, const bignum& right);
	friend bool operator<(const bignum& left, int right);
	friend bool operator>(const bignum& left, const bignum& right);
	friend bool operator>(int left, const bignum& right);
	friend bool operator>(const bignum& left, int right);
	friend bool operator==(const bignum& left, const bignum& right);
	friend bool operator==(int left, const bignum& right);
	friend bool operator==(const bignum& left, int right);
	friend bool operator!=(const bignum& left, const bignum& right);
	friend bool operator!=(int left, const bignum& right);
	friend bool operator!=(const bignum& left, int right);
	friend bool operator>=(const bignum& left, const bignum& right);
	friend bool operator>=(int left, const bignum& right);
	friend bool operator>=(const bignum& left, int right);
	friend bool operator<=(const bignum& left, const bignum& right);
	friend bool operator<=(int left, const bignum& right);
	friend bool operator<=(const bignum& left, int right);

	//конструктор из целого числа
	bignum(int n)
	{
		if (!str_to_bignum(to_string(n)))
			throw "Bad number\n";
	}
	//конструктор из строки
	bignum(const string s)
	{
		if (!str_to_bignum(s))
			throw "Bad number\n";
	}
	//конструктор по умолчанию
	bignum()
	{
		if (!str_to_bignum("0"))
			throw "Bad number\n";
	}
	//конструтор из составных частей
	bignum(const vector<char> _digits, int _signbit, int _lastdigit)
	{
		digits=_digits;
		signbit = _signbit;
		lastdigit = _lastdigit;
	}
	
	//унарный минус
	bignum operator-() const
	{
		return bignum(digits, -signbit, lastdigit);
	}
	//префиксный инкремент
	bignum operator ++()
	{
		*this = *this + 1;
		return *this;
	}
	//постфиксный инкремент
	bignum operator ++(int)
	{
		bignum t = *this;
		*this = *this + 1;
		return t;
	}
	//префиксный декремент
	bignum operator --()
	{
		*this = *this - 1;
		return *this;
	}
	//постфиксный декремент
	bignum operator --(int)
	{
		bignum t = *this;
		*this = *this - 1;
		return t;
	}
	//ѕрисваивани€ с операци€ми
	bignum& operator+=(bignum& b)
	{
		*this = *this + b;
		return *this;
	}
	bignum& operator+=(int b)
	{
		*this = *this + b;
		return *this;
	}

	bignum& operator-=(bignum& b)
	{
		*this = *this - b;
		return *this;
	}
	bignum& operator-=(int b)
	{
		*this = *this - b;
		return *this;
	}

	bignum& operator*=(bignum& b)
	{
		*this = *this * b;
		return *this;
	}
	bignum& operator*=(int b)
	{
		*this = *this * b;
		return *this;
	}

	bignum& operator/=(bignum& b)
	{
		*this = *this / b;
		return *this;
	}
	bignum& operator/=(int b)
	{
		*this = *this / b;
		return *this;
	}

	bignum& operator%=(bignum& b)
	{
		*this = *this % b;
		return *this;
	}
	bignum& operator%=(int b)
	{
		*this = *this % b;
		return *this;
	}
	//двоичное возведение в степень
	bignum pow(const bignum &n);
};

#define BIGNUM_H
#endif // !BIGNUM_H

