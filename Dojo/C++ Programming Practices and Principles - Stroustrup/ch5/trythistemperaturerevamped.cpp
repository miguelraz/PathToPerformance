//5.trythis temperature improved
#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

int main() {
	double sum = 0;
	double low_temp = 128 * -1; // initialize to impossibly low aka vostok
	double high_temp = 136 ; // initialize to “impossibly high” aka dubai march 30 2017
	int no_of_temps = 0;
	for (double temp; cin >> temp; ) {      // read temp
		++no_of_temps; // count temperatures
		sum += temp;  // compute sum
		if (temp > high_temp) high_temp = temp;	// find high
		if (temp < low_temp) low_temp = temp;   // find low
	}
		cout << "High temperature: " << high_temp << '\n';
		cout << "Low temperature: " << low_temp << '\n';
		cout << "Average temperature: " << sum / no_of_temps << '\n';
	}
