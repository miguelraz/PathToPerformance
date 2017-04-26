// Ex. 17 - Quadratic root solver
#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{
	// Get inputs.
	double a, b, c, res1, res2;
	cout << "Gimme a " << endl;
	cin >> a;
	cout << "Gimme b " << endl;
	cin >> b;
	cout << "Gimme c " << endl;
	cin >> c;

	// Sanity check.
	if (b*b - 4 * a*c < 0) simple_error("Derp. No complex case please.");

	// In German, this is called the midnight formula...
	res1 = (-1 * b + sqrt(b*b - 4 * a*c) / (2 * a));
	res2 = (-1 * b - sqrt(b*b - 4 * a*c) / (2 * a));

	// Print
	cout << "Your results are x1 = " << res1 << " and x2 = " << res2 << endl;
}
