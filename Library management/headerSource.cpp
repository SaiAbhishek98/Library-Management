#include<iostream>
#include<conio.h>
#include<string>
#include<algorithm>
#include<fstream>
//#include<ctime>
using namespace std;
fstream all1;
string take_password()
{
	string arg_pass;
	char ch;
	//cout << "Password :";
	ch = _getch();
	while (ch != 13) {
		arg_pass.push_back(ch);
		cout << "*";
		ch = _getch();
	}
	return arg_pass;
}

