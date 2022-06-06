#include "bignum.h"
//�������������� ������ � �����
bool bignum::str_to_bignum(const string s)
{
	int k;
	if (s.length() == 0)
		return false;	//���� ������ ������ - ������
	digits.resize(s.length());
//		digits[i] = (char)0;	//���������� ���� ���� ������
	if (s[0] == '-')			//���� ������ ���� -
	{
		signbit = MINUS;	//���������� ������� -
		k = 1;				//������ ������ �����=1
	}
	else if (s[0] == '+')	//���� ������ ���� +
	{
		signbit = PLUS;	// ���� +
		k = 1;				//������ ������ �����=1
	}
	else
	{
		signbit = PLUS;	//����� ���� +
		k = 0;				//������ ������ �����=0
	}
	if (s.length() == k)
		return false;	//���� ������ ���� - ������

	lastdigit = -1;	//������ ������� �����=-1
	for (int i = s.length() - 1; i >= k; i--)
	{
		if (s[i]<'0' || s[i]>'9')
			return false;	//���� �� �����, ������� ������
		lastdigit++;						//��������� ������ ������� �����
		digits[lastdigit] = s[i] - '0';	//��������� ����� � �����
	}
	return true;
}
//��������� ���������� ����
void bignum::zero_justify()
{
	while ((lastdigit > 0) && (digits[lastdigit] == 0))	//���� ������� �������� ����� =0
		lastdigit--;											//��������� �� ������

	if ((lastdigit == 0) && (digits[0] == 0))
		signbit = PLUS; // �������, ����� ������ -0 
}
// �������� n �� 10^d 
void bignum::digit_shift(int d)
{
	if ((lastdigit == 0) && (digits[0] == 0)) return;	//���� n=0, �����
	digits.resize(digits.size() + d);	//��������� ����� �����

	for (int i = lastdigit; i >= 0; i--)		//���� ����� ����� �����
		digits[i + d] = digits[i];

	for (int i = 0; i < d; i++) digits[i] = 0;	//�������� ���������� �������

	lastdigit = lastdigit + d;		//������������ ������ ������� �����
}
//�������� ���������� � �������
bignum bignum::pow(const bignum &n)
{
	if (n < 0)
		throw "Power should not be negative\n";
	bignum n1 = n;
	bignum res = 1;
	bignum a = *this;
	while (n1 != 0)
	{
		if (n1 % 2 == 1)
			res *= a;
		a *= a;
		n1 /= 2;
	}
	return res;
}
// ���������� ��������� ������������ ������
ostream& operator<<(ostream& output, const bignum& b)
{
	if (b.signbit == MINUS)
		output << "-";//���� ����� ������������, ������� -

	for (int i = b.lastdigit; i >= 0; i--)		//����������� ������� ��� �����
	{
		char c = '0' + b.digits[i];
		cout << c;
	}
	return output;
}
// ���������� ��������� ������������ �����
istream& operator >> (istream & input, bignum &b)
{
	string s;
	input >> s;	//���� ������
	if (!b.str_to_bignum(s))	//� �������������� � �����
	{
		throw "Bad number\n";
	}
	return input;
}
//��������
bignum operator+(const bignum& left, const bignum& right)
{
	bignum c = 0;
	if (left.signbit == right.signbit)
		c.signbit = left.signbit;	//���� ����� ����������� ����� ����������, ��������� ����� ����� ���� ����
	else
	{	//���� ������
		if (left.signbit == MINUS)	//���� left<0
		{
			return right - (-left);
		}
		else //���� right<0
		{
			return left - (-right);
		}
	}
	//�������� ��� ���� ���������� ������
	c.lastdigit = (left.lastdigit > right.lastdigit ? left.lastdigit : right.lastdigit) + 1;//���������� ������ ���� �� ���� �������� ����
	c.digits.resize(c.lastdigit + 1);	//������ ����� �����
	int carry = 0;		//�������=0
						//�������� ��������� �� ������� ���� � �������
	for (int i = 0; i <= (c.lastdigit); i++)
	{
		char l = i < left.digits.size() ? left.digits[i] : 0;	//��������� ����� �����
		char r = i < right.digits.size() ? right.digits[i] : 0;
		c.digits[i] = (char)(carry + l + r) % 10;	//�������� ����� ���� �� ������ 10 � ��������
		carry = (carry + l + r) / 10;		//����������� ��������
	}
	//������ ���������� ����
	c.zero_justify();
	return c;
}
bignum operator+(int left, const bignum& right)
{
	return bignum(to_string(left)) + right;
}
bignum operator+(const bignum& left, int right)
{
	return left + bignum(to_string(right));
}

//���������
bignum operator-(const bignum& left, const bignum& right)
{
	bignum c = 0;
	if ((left.signbit == MINUS) || (right.signbit == MINUS))	//���� ���� �� ����� �������������
	{
		return left + (-right);
	}
	if (left < right) //���� left<right
	{
		return -(right - left);	//�����
	}
	c.lastdigit = (left.lastdigit > right.lastdigit ? left.lastdigit : right.lastdigit);	//���������� ������ ���� �� ���� �������� ����
	c.digits.resize(c.lastdigit + 1);	//������ ����� �����
	int borrow = 0;		//����=0
						//��������� ��������� �� ������� ���� � �������
	for (int i = 0; i <= (c.lastdigit); i++) 
	{
		char l = i < left.digits.size() ? left.digits[i] : 0;	//��������� ����� �����
		char r = i < right.digits.size() ? right.digits[i] : 0;
		int v = (l -borrow - r);	//��������� �� ����� ���� ����� a ���� ����� right � �����
		if (l > 0)	//���� ����� � ������������
			borrow = 0;			//���������� ����
		if (v < 0) 
		{		//���� � ���������� ��������� ���� ������� ����� ���������, 
			v = v + 10;		//������ ��� �������������
			borrow = 1;		//�� �������� ���� �� �������� �������
		}
		c.digits[i] = (char)v % 10;	//��������� �������������� �����
	}
	//������ ���������� ����
	c.zero_justify();
	return c;
}
bignum operator-(int left, const bignum& right)
{
	return bignum(to_string(left)) - right;
}
bignum operator-(const bignum& left, int right)
{
	return left - bignum(to_string(right));
}

//���������
bool operator<(const bignum& left, const bignum& right)
{
	if ((left.signbit == MINUS) && (right.signbit == PLUS)) return true;
	if ((left.signbit == PLUS) && (right.signbit == MINUS)) return false;

	if (right.lastdigit > left.lastdigit) return (PLUS * left.signbit) == PLUS;
	if (left.lastdigit > right.lastdigit) return (MINUS * left.signbit) == PLUS;

	for (int i = left.lastdigit; i >= 0; i--) {
		if (left.digits[i] > right.digits[i]) return(MINUS * left.signbit) == PLUS;
		if (right.digits[i] > left.digits[i]) return(PLUS * left.signbit) == PLUS;
	}
	return false;
}
bool operator<(int left, const bignum& right)
{
	return bignum(to_string(left)) < right;
}
bool operator<(const bignum& left, int right)
{
	return left < bignum(to_string(right));
}
bool operator>(const bignum& left, const bignum& right)
{
	if ((left.signbit == MINUS) && (right.signbit == PLUS)) return false;
	if ((left.signbit == PLUS) && (right.signbit == MINUS)) return true;

	if (right.lastdigit > left.lastdigit) return (PLUS * left.signbit) == MINUS;
	if (left.lastdigit > right.lastdigit) return (MINUS * left.signbit) == MINUS;

	for (int i = left.lastdigit; i >= 0; i--) {
		if (left.digits[i] > right.digits[i]) return(MINUS * left.signbit) == MINUS;
		if (right.digits[i] > left.digits[i]) return(PLUS * left.signbit) == MINUS;
	}
	return false;
}
bool operator>(int left, const bignum& right)
{
	return bignum(to_string(left)) > right;
}
bool operator>(const bignum& left, int right)
{
	return left > bignum(to_string(right));
}
bool operator==(const bignum& left, const bignum& right)
{
	if ((left.signbit == MINUS) && (right.signbit == PLUS)) return false;
	if ((left.signbit == PLUS) && (right.signbit == MINUS)) return false;

	if (right.lastdigit > left.lastdigit) return false;
	if (left.lastdigit > right.lastdigit) return false;

	for (int i = left.lastdigit; i >= 0; i--) {
		if (left.digits[i] > right.digits[i]) return false;
		if (right.digits[i] > left.digits[i]) return false;
	}
	return true;
}
bool operator==(int left, const bignum& right)
{
	return bignum(to_string(left)) == right;
}
bool operator==(const bignum& left, int right)
{
	return left == bignum(to_string(right));
}
bool operator!=(const bignum& left, const bignum& right)
{
	return !(left == right);
}
bool operator!=(int left, const bignum& right)
{
	return bignum(to_string(left)) != right;
}
bool operator!=(const bignum& left, int right)
{
	return left != bignum(to_string(right));
}

bool operator>=(const bignum& left, const bignum& right)
{
	return (left > right) || (left == right);
}
bool operator>=(int left, const bignum& right)
{
	return bignum(to_string(left)) >= right;
}
bool operator>=(const bignum& left, int right)
{
	return left >= bignum(to_string(right));
}
bool operator<=(const bignum& left, const bignum& right)
{
	return (left < right) || (left == right);
}
bool operator<=(int left, const bignum& right)
{
	return bignum(to_string(left)) <= right;
}
bool operator<=(const bignum& left, int right)
{
	return left <= bignum(to_string(right));
}
//���������
bignum operator*(const bignum& left, const bignum& right)
{
	bignum c = 0;
	c.digits.resize(left.digits.size() + right.digits.size());	//������ ����� ����� (���� ����� ����� �� ������ ����� ���� �������� ����������)
	bignum row = left;			// ���������� ���=�
								//��������� ���������
	for (int i = 0; i <= right.lastdigit; i++)
	{
		for (int j = 1; j <= right.digits[i]; j++)
		{
			c = c + row;
		}
		row.digit_shift(1);
	}
	c.setsign(left.signbit * right.signbit);	//�������� �������������� ����
	c.zero_justify();	//������ ���������� ����
	return c;
}
bignum operator*(int left, const bignum& right)
{
	return bignum(to_string(left)) * right;
}
bignum operator*(const bignum& left, int right)
{
	return left * bignum(to_string(right));
}
//�������
bignum operator/(const bignum& left, const bignum& right)
{
	if (right == 0)		//�������� �������� �� 0
		throw "Division by zero\n";
	bignum c = 0;
	bignum row = 0;                     /* ���������� ��� =0*/
	c.digits.resize(left.digits.size());	//������ ����� ����� (���� ����� ����� �� ������ ��������)
	c.lastdigit = left.lastdigit;	//������ ������ ����������
	bignum leftcopy = left;
	bignum rightcopy = right;
	leftcopy.setsign(PLUS);//������ ����������� �������
	rightcopy.setsign(PLUS);
	//������� ���������
	for (int i = leftcopy.lastdigit; i >= 0; i--)
	{
		row.digit_shift(1);
		row.digits[0] = leftcopy.digits[i];
		c.digits[i] = 0;
		while (row >= rightcopy)
		{
			c.digits[i] ++;
			row = row - rightcopy;
		}
	}
	//������ ���������� ����
	c.zero_justify();
	return c;
}
bignum operator/(int left, const bignum& right)
{
	return bignum(to_string(left)) / right;
}
bignum operator/(const bignum& left, int right)
{
	return left / bignum(to_string(right));
}
//������� �� �������
bignum operator%(const bignum& left, const bignum& right)
{
	if (right == 0)		//�������� �������� �� 0
		throw "Division by zero\n";
	bignum c = 0;
	c.digits.resize(left.digits.size());	//������ ����� ����� (���� ����� ����� �� ������ ��������)
	c.lastdigit = left.lastdigit;	//������ ������ ����������
	bignum row = 0;                     /* ���������� ��� =0*/
	bignum leftcopy = left;	//����� �����
	bignum rightcopy = right;
	leftcopy.setsign(PLUS);//������ ����������� �������
	rightcopy.setsign(PLUS);
	//������� ���������
	for (int i = leftcopy.lastdigit; i >= 0; i--)
	{
		row.digit_shift(1);
		row.digits[0] = leftcopy.digits[i];
		c.digits[i] = 0;
		while (row >= rightcopy)
		{
			c.digits[i] ++;
			row = row - rightcopy;
		}
	}
	//� row �������� �������
	row.setsign(left.signbit);		//���� ������� ���������� �� ���� ��������
									//������ ���������� ����
	row.zero_justify();
	return row;
}
bignum operator%(int left, const bignum& right)
{
	return bignum(to_string(left)) % right;
}
bignum operator%(const bignum& left, int right)
{
	return left % bignum(to_string(right));
}

