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
			cin >> ch;	//���� ����� ��������
			if (ch[0]<'0' || ch[0]>'6')		//���� ������� ������������ ��������
			{
				cout << "Wrong choice!" << endl;	//������� ���������
				continue;
			}
			if (ch[0] == '0')
				break;
			string op, sk1, sk2;
			cout << "Enter a: ";
			cin >> a;		//���� ������� �����
			cout << "Enter b: ";
			cin >> b;		//������ ������ �����
			if (b < 0)	//���� ������ ����� �������������
			{
				sk1 = "(";	//����� ��� � ������
				sk2 = ")";
			}
			switch (ch[0])		//� ����������� �� ��������� ��������
			{
			case '1':
				op = "+";				//������� �� ����
				r = a + b;		//� ��������� ��������
				break;
			case '2':
				op = "-";				//������� �� ����
				r = a - b;//� ��������� ��������
				break;
			case '3':
				op = "*";				//������� �� ����
				r = a*b;//� ��������� ��������
				break;
			case '4':
				op = "/";				//������� �� ����
				r = a / b;	//� ��������� ��������
				break;
			case '5':
				op = "%";				//������� �� ����
				r = a%b;	//� ��������� ��������
				break;
			case '6':
				op = "^";			//������� �� ����
				r = a.pow(b);		//� ��������� ��������
				break;
			}
			cout << a << op << sk1 << b << sk2 << "=" << r << endl;			//������� ������ ����� � ������� ���������

		}
		catch (char *msg)		//����������� ���������������� ����������
		{
			cout << msg << endl;
		}
	}
	return 0;
}