//Drill 6: Print smallest and largest so far.
#include "std_lib_facilities.h"

int main()
{
	cout << "Gimme a double" << endl;

	double min = 0, max = 0, test = 0;
	cin >> test;
	min = test;
	max = test;

	while (cin >> test)
	{
		if (test <= min) {
			min = test;
			cout << "The smallest so far is " << min << endl;
		}
		if (max <= test) {
			max = test;
			cout << "The largest so far is " << max << endl;
		}
	}

}
