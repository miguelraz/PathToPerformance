// Ex5.2 - correct Celsius to Kelvin.
// Version 1.0 - by @miguelraz 27.04.17
// This program converts from Celsius to Kelvin with some simple try/blocks.

#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

class bad_temp {}; // Create empy class to be thrown.

double celsiustokelvin(double celsius) {			// converts Celsius to Kelvin
	double kelvin = celsius + 273.15;

	if (kelvin <= 0) throw bad_temp();
	return kelvin;
}

// Calculates Celsius to Kelvin.
// Throws bad_temp if below absolute zero.

int main()
try {

	double celsius = 0; // Decalre input variable.
	cout << "Gimme the temperature to be transformed from Celsius to Kelvin " << endl;
	cin >> celsius; // Retrieve input variable.

	double kelvin = celsiustokelvin(celsius); // Convert temperature.
	cout << kelvin << " is the temp in Kelvin " << endl;

	cout << "Success!\n";
	keep_window_open();
	return 0;
} catch (exception& e) {
	cout << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
} catch (...) {
	cout << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}
