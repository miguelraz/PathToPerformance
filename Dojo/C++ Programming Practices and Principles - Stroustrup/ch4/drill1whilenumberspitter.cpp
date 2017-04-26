// Drill 1: Write a program that consists of a while-loop that (each time around the loop) reads in two ints and then prints them.
//Exit the program when a terminating '|' is entered.
#include "std_lib_facilities.h"

int main()
{
	cout << "Gimme 2 ints" << endl;
	int val1 = 0, val2 = 0;
	while (cin >> val1 >> val2)
	{
	if (val1 == '|' || val2 == '|')
	{
		cout << "Game over" << endl;
		return 0;
	}
	cout << val1 << " " << val2 << endl;
}

}
