#include "DictionaryHT.h"
#include "DictionaryRB.h"
#include <iostream>
#define NOMINMAX
#include <Windows.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "----------MAIN MENU----------" << endl;
	while (true)
	{
		cout << "Select a dictionary format:" << endl;
		cout << "(1) Hash-Table dictionary" << endl;
		cout << "(2) Red-Black Tree dictionary" << endl;

		string InputAction;
		cin >> InputAction;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (InputAction == "0")
		{
			break;
		}
		else if (InputAction == "1")
		{
			MenuHT();
		}
		else if (InputAction == "2")
		{
			MenuRB();
		}
		cout << endl;
	}
}