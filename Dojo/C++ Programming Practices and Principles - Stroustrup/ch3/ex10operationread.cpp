#include "std_lib_facilities.h"

int main() {

	cout << "Yooo gimme an operator and two floats" << endl;
	float val1, val2;
	string operation;

	cin >> operation;
	cin >> val1;
	cin >> val2;

	if (operation == "+") cout << val1 + val2 << endl;
    if (operation == "-") cout << val1 - val2 << endl;
	if (operation == "*") cout << val1 * val2 << endl;
	if (operation == "/") cout << val1 / val2 << endl;

}
