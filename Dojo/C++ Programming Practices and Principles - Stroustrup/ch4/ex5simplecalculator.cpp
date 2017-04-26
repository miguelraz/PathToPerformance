// Exercise 5: Simple calculator.
#include "std_lib_facilities.h"

int main()
{

	double val1; double val2;
	char operation;

	cout << "Gimme the 2 floats you want to operate on " << endl;
	cin >> val1 >> val2;
	cout << "Gimme the operation you want to do - +,-,*,/" << endl;
	cin >> operation;

	switch (operation) {
	case '+':
		cout << val1 + val2 << endl;
		break;
	case '-':
		cout << val1 - val2 << endl;
		break;
	case '*':
		cout << val1 * val2 << endl;
		break;
	case '/':
		cout << val1 / val2 << endl;
		break;
	}
}
