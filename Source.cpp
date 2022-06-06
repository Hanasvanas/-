#include <iostream>
#include <string>
#include "bignum.h"
using namespace std;
int main()
{
	bignum a, b, r;
	char ch[16] = { 0 };
	while (ch[0] != '0')
	{
		try
		{
			cout << "Select action:" << endl;
			cout << "1 - Add" << endl;
			cout << "2 - Sub" << endl;
			cout << "3 - Mul" << endl;
			cout << "4 - Div" << endl;
			cout << "5 - Mod" << endl;
			cout << "6 - Power" << endl;
			cout << "0 - Exit" << endl;
			cin >> ch;	//ввод знака операции
			if (ch[0]<'0' || ch[0]>'6')		//если введенр недопустимое значение
			{
				cout << "Wrong choice!" << endl;	//вывести сообщение
				continue;
			}
			if (ch[0] == '0')
				break;
			string op, sk1, sk2;
			cout << "Enter a: ";
			cin >> a;		//ввод первого числа
			cout << "Enter b: ";
			cin >> b;		//ввести второе число
			if (b < 0)	//если второе число отрицательное
			{
				sk1 = "(";	//взять его в скобки
				sk2 = ")";
			}
			switch (ch[0])		//в зависимости от выбранной операции
			{
			case '1':
				op = "+";				//вывести ее знак
				r = a + b;		//и выполнить операцию
				break;
			case '2':
				op = "-";				//вывести ее знак
				r = a - b;//и выполнить операцию
				break;
			case '3':
				op = "*";				//вывести ее знак
				r = a*b;//и выполнить операцию
				break;
			case '4':
				op = "/";				//вывести ее знак
				r = a / b;	//и выполнить операцию
				break;
			case '5':
				op = "%";				//вывести ее знак
				r = a%b;	//и выполнить операцию
				break;
			case '6':
				op = "^";			//вывести ее знак
				r = a.pow(b);		//и выполнить операцию
				break;
			}
			cout << a << op << sk1 << b << sk2 << "=" << r << endl;			//вывести второе число и вывести результат

		}
		catch (char *msg)		//отлавливаем пользовательское исключение
		{
			cout << msg << endl;
		}
	}
	return 0;
}