#ifndef BIGNUM_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define PLUS		1		/* �������� ����� ����� */
#define MINUS		-1		/* �������� ������ ����� */
class bignum
{
private:
	vector<char> digits;         /* ����� ����� */
	int signbit;			/* 1 - ������������� -1 - ������������� */
	int lastdigit;			/* ������ ������� ����� ����� */
	//�������������� ������ � �����
	bool str_to_bignum(const string s);
	//��������� ���������� ����
	void zero_justify();
	// �������� n �� 10^d 
	void digit_shift(int d);
public:
	//��������� ����� �����
	void setsign(int s)
	{
		signbit = s;
	}
	// ���������� ��������� ������������ ������
	friend ostream& operator<<(ostream& output, const bignum& b);
	// ���������� ��������� ������������ �����
	friend istream& operator >> (istream & input, bignum &b);
	//��������
	friend bignum operator+(const bignum& left, const bignum& right);
	friend bignum operator+(int left, const bignum& right);
	friend bignum operator+(const bignum& left, int right);
	//���������
	friend bignum operator-(const bignum& left, const bignum& right);
	friend bignum operator-(int left, const bignum& right);
	friend bignum operator-(const bignum& left, int right);
	//���������
	friend bignum operator*(const bignum& left, const bignum& right);
	friend bignum operator*(int left, const bignum& right);
	friend bignum operator*(const bignum& left, int right);
	//�������
	friend bignum operator/(const bignum& left, const bignum& right);
	friend bignum operator/(int left, const bignum& right);
	friend bignum operator/(const bignum& left, int right);
	//������� �� �������
	friend bignum operator%(const bignum& left, const bignum& right);
	friend bignum operator%(int left, const bignum& right);
	friend bignum operator%(const bignum& left, int right);
	//���������
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

	//����������� �� ������ �����
	bignum(int n)
	{
		if (!str_to_bignum(to_string(n)))
			throw "Bad number\n";
	}
	//����������� �� ������
	bignum(const string s)
	{
		if (!str_to_bignum(s))
			throw "Bad number\n";
	}
	//����������� �� ���������
	bignum()
	{
		if (!str_to_bignum("0"))
			throw "Bad number\n";
	}
	//���������� �� ��������� ������
	bignum(const vector<char> _digits, int _signbit, int _lastdigit)
	{
		digits=_digits;
		signbit = _signbit;
		lastdigit = _lastdigit;
	}
	
	//������� �����
	bignum operator-() const
	{
		return bignum(digits, -signbit, lastdigit);
	}
	//���������� ���������
	bignum operator ++()
	{
		*this = *this + 1;
		return *this;
	}
	//����������� ���������
	bignum operator ++(int)
	{
		bignum t = *this;
		*this = *this + 1;
		return t;
	}
	//���������� ���������
	bignum operator --()
	{
		*this = *this - 1;
		return *this;
	}
	//����������� ���������
	bignum operator --(int)
	{
		bignum t = *this;
		*this = *this - 1;
		return t;
	}
	//������������ � ����������
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
	//�������� ���������� � �������
	bignum pow(const bignum &n);
};

#define BIGNUM_H
#endif // !BIGNUM_H

