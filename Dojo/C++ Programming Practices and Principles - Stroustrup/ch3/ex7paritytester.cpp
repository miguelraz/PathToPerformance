#include "std_lib_facilities.h"

int main() {
	cout << "Gimme an integer" << endl;
	int test;
	cin >> test;
	if (test % 2 == 0)
	{
		cout << "Your digit " << test << " is an even number." << endl;
	}
	else
	{
		cout << "Your digit " << test << " is an odd number. " << endl;
	}
}
