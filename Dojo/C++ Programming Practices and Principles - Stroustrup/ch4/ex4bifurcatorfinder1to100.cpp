//Exercise 4: Bifurcator 1 to 100 finder
#include "std_lib_facilities.h"

int main()
{

	double boundU = 100;
	double  boundL = 0;
	double guess = 50;
	int res = 0;

	while ( boundL != boundU)
	{

		cout << "Is your number between " << boundL << " and " << guess << " ? " << endl;
		cin >> res;

		// Check where to search next.
		if (res == 1) boundU = guess;
		if (res == 0) boundL = guess;

			guess = boundU - round((boundU - boundL)*.5);
			cout << "BoundU is now " << boundU << endl;
			cout << "BoundL is now " << boundL << endl;
			cout << "Guess is now " << guess << endl;

	}

	if (boundU == guess) guess = boundU;
	cout << "Your number is " << guess << " :D " << endl;

}
