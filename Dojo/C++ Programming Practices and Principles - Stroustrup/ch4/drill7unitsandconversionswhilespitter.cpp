//Drill 7: Accept units and conversions
#include "std_lib_facilities.h"

int main()
{
	cout << "Gimme a double with units" << endl;

	double test, min, max; string unit;
	cin >> test >> unit;
	min = test;
	max = test;

	while (cin >> test >> unit)
	{
		if (unit == "cm") {
			test = test *.01;
			unit = "m";
		}
		if (unit == "in") {
			test = test * .0254;
			unit = "m";
		}
		if (unit == "ft") {
			test = test * .3048;
			unit = "m";
		}

		if (test <= min) {
			min = test;
			cout << "The smallest so far is " << min << unit << endl;
		}
		if (max <= test) {
			max = test;
			cout << "The largest so far is " << max << unit << endl;
		}
	}

}
