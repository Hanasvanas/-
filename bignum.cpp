#include "bignum.h"
//Преобразование строки в число
bool bignum::str_to_bignum(const string s)
{
	int k;
	if (s.length() == 0)
		return false;	//если строка пустая - ошибка
	digits.resize(s.length());
//		digits[i] = (char)0;	//заполнение всех цифр нулями
	if (s[0] == '-')			//если первый знак -
	{
		signbit = MINUS;	//установить признак -
		k = 1;				//индекс начала числа=1
	}
	else if (s[0] == '+')	//если первый знак +
	{
		signbit = PLUS;	// знак +
		k = 1;				//индекс начала числа=1
	}
	else
	{
		signbit = PLUS;	//иначе знак +
		k = 0;				//индекс начала числа=0
	}
	if (s.length() == k)
		return false;	//если только знак - ошибка

	lastdigit = -1;	//индекс старшей цифры=-1
	for (int i = s.length() - 1; i >= k; i--)
	{
		if (s[i]<'0' || s[i]>'9')
			return false;	//если не цифра, вернуть ошибку
		lastdigit++;						//увеличить индекс старшей цифры
		digits[lastdigit] = s[i] - '0';	//перенести цифру в число
	}
	return true;
}
//выровнять незначащие ноли
void bignum::zero_justify()
{
	while ((lastdigit > 0) && (digits[lastdigit] == 0))	//пока старшая значащая цифра =0
		lastdigit--;											//уменьшаем ее индекс

	if ((lastdigit == 0) && (digits[0] == 0))
		signbit = PLUS; // костыль, чтобы убрать -0 
}
// умножить n на 10^d 
void bignum::digit_shift(int d)
{
	if ((lastdigit == 0) && (digits[0] == 0)) return;	//если n=0, выйти
	digits.resize(digits.size() + d);	//увеличить длину числа

	for (int i = lastdigit; i >= 0; i--)		//цикл свига чисел влево
		digits[i + d] = digits[i];

	for (int i = 0; i < d; i++) digits[i] = 0;	//обнуляем выдвинутые разрады

	lastdigit = lastdigit + d;		//Корректируем индекс старшей цифры
}
//двоичное возведение в степень
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
// Перегрузка оператора стандартного вывода
ostream& operator<<(ostream& output, const bignum& b)
{
	if (b.signbit == MINUS)
		output << "-";//Если число отицательное, вывести -

	for (int i = b.lastdigit; i >= 0; i--)		//посимвольно вывести все цифры
	{
		char c = '0' + b.digits[i];
		cout << c;
	}
	return output;
}
// Перегрузка оператора стандартного ввода
istream& operator >> (istream & input, bignum &b)
{
	string s;
	input >> s;	//ввод строки
	if (!b.str_to_bignum(s))	//и преобразование в число
	{
		throw "Bad number\n";
	}
	return input;
}
//сложение
bignum operator+(const bignum& left, const bignum& right)
{
	bignum c = 0;
	if (left.signbit == right.signbit)
		c.signbit = left.signbit;	//если знаки суммируемых чисел одинаковые, результат будет иметь этот знак
	else
	{	//если разный
		if (left.signbit == MINUS)	//если left<0
		{
			return right - (-left);
		}
		else //если right<0
		{
			return left - (-right);
		}
	}
	//сложение для двух одинаковых знаков
	c.lastdigit = (left.lastdigit > right.lastdigit ? left.lastdigit : right.lastdigit) + 1;//определить индекс макс из двух значащих цифр
	c.digits.resize(c.lastdigit + 1);	//задать длину числа
	int carry = 0;		//перенос=0
						//сложение столбиком от младших цифр к старшим
	for (int i = 0; i <= (c.lastdigit); i++)
	{
		char l = i < left.digits.size() ? left.digits[i] : 0;	//очередные цифры чисел
		char r = i < right.digits.size() ? right.digits[i] : 0;
		c.digits[i] = (char)(carry + l + r) % 10;	//сложение соотв цифр по модулю 10 и переноса
		carry = (carry + l + r) / 10;		//запоминание переноса
	}
	//убрать незначащие ноли
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

//вычитание
bignum operator-(const bignum& left, const bignum& right)
{
	bignum c = 0;
	if ((left.signbit == MINUS) || (right.signbit == MINUS))	//если одно из чисел отрицательное
	{
		return left + (-right);
	}
	if (left < right) //если left<right
	{
		return -(right - left);	//выход
	}
	c.lastdigit = (left.lastdigit > right.lastdigit ? left.lastdigit : right.lastdigit);	//определить индекс макс из двух значащих цифр
	c.digits.resize(c.lastdigit + 1);	//задать длину числа
	int borrow = 0;		//заем=0
						//вычитание столбиком от младших цифр к старшим
	for (int i = 0; i <= (c.lastdigit); i++) 
	{
		char l = i < left.digits.size() ? left.digits[i] : 0;	//очередные цифры чисел
		char r = i < right.digits.size() ? right.digits[i] : 0;
		int v = (l -borrow - r);	//вычитание из соотв цифр числа a цифр числа right и заема
		if (l > 0)	//если цифра а положительно
			borrow = 0;			//сбрасываем заем
		if (v < 0) 
		{		//если в результате вычитания цифр полулся отриц результат, 
			v = v + 10;		//делаем его положительным
			borrow = 1;		//но получили заем из старшего разряда
		}
		c.digits[i] = (char)v % 10;	//сохранить результирующую цифру
	}
	//убрать незначащие ноли
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

//сравнение
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
//умножение
bignum operator*(const bignum& left, const bignum& right)
{
	bignum c = 0;
	c.digits.resize(left.digits.size() + right.digits.size());	//задать длину числа (макс длина будет не больше суммы длин исходных множителей)
	bignum row = left;			// сдвигаемый ряд=а
								//умножение стобликом
	for (int i = 0; i <= right.lastdigit; i++)
	{
		for (int j = 1; j <= right.digits[i]; j++)
		{
			c = c + row;
		}
		row.digit_shift(1);
	}
	c.setsign(left.signbit * right.signbit);	//получить результирующий знак
	c.zero_justify();	//убрать незначащие ноли
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
//деление
bignum operator/(const bignum& left, const bignum& right)
{
	if (right == 0)		//проверка делителя на 0
		throw "Division by zero\n";
	bignum c = 0;
	bignum row = 0;                     /* сдвигаемый ряд =0*/
	c.digits.resize(left.digits.size());	//задать длину числа (макс длина будет не больше делимого)
	c.lastdigit = left.lastdigit;	//задать размер результата
	bignum leftcopy = left;
	bignum rightcopy = right;
	leftcopy.setsign(PLUS);//делаем беззнаковое деление
	rightcopy.setsign(PLUS);
	//деление столбиком
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
	//убрать незначащие ноли
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
//остаток от деления
bignum operator%(const bignum& left, const bignum& right)
{
	if (right == 0)		//проверка делителя на 0
		throw "Division by zero\n";
	bignum c = 0;
	c.digits.resize(left.digits.size());	//задать длину числа (макс длина будет не больше делимого)
	c.lastdigit = left.lastdigit;	//задать размер результата
	bignum row = 0;                     /* сдвигаемый ряд =0*/
	bignum leftcopy = left;	//копии чисел
	bignum rightcopy = right;
	leftcopy.setsign(PLUS);//делаем беззнаковое деление
	rightcopy.setsign(PLUS);
	//деление столбиком
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
	//в row остается остаток
	row.setsign(left.signbit);		//знак остатка определяем по знак делимого
									//убрать незначащие ноли
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

