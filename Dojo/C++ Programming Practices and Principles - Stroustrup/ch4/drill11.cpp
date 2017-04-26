// Drill 9 through 11
#include "std_lib_facilities.h"

int main()
{
	cout << "Gimme a double with units" << endl;

	double test, min, max; string unit;
	cin >> test >> unit;
	vector<int> entries;
	min = test;
	max = test;

	while (cin >> test >> unit)
	{
		if (unit != "cm" && unit != "m" && unit != "in" && unit != "ft")
			simple_error("That is not an accepted unit type.");

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

		entries.push_back(test);

		if (test <= min) {
			min = test;
			cout << "The smallest so far is " << min << unit << endl;
		}
		if (max <= test) {
			max = test;
			cout << "The largest so far is " << max << unit << endl;
		}
	}

	for (int i = 0; i < entries.size(); i++)
		cout << entries[i] << endl;
	cout << "The largest was " << max << "m" << endl;
	cout << "The smallest was " << min << "m" << endl;

}
