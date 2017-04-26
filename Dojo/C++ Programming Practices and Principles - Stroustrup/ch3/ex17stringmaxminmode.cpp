
#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{
	cout << "Gimme a series of strings " << endl;
	string val0;
	vector<string> strings;
	vector<int> counters;

	// Get inputs
	while (cin >> val0) strings.push_back(val0);

	// Fill empty counters array
	for (int i = 0; i < strings.size(); ++i) counters[0] = 0;

	// Sort numbers array
	sort(strings.begin(), strings.end());

	// Count consecutive repetitions and input that into 'counters'
	for (int i = 0; i < strings.size() - 1; ++i) {
		for (int j = i; j < strings.size() - 1; j++) {

			if (strings[i] == strings[i + j])
				counters[j] += 1;
		}
	}

	// Spit results
	for (int i = 0; i < counters.size(); ++i) cout << " Strings " << strings[i] << " is the most found at " << counters[i] << " times. " << endl;

	// Setup min and max
	string min, max;
	min = strings[0]; max = strings[0];

	//Cheat codes - since strings is already sorted, take the first and last items of vector.
	//min = strings[0]; max = strings.end();

	// Basic sort and store
	for (int i = 0; i < strings.size(); ++i){
		if (min <= strings[i]) min = strings[i];
		if (max >= strings[i]) max = strings[i];
	}

	//Print staaaahff
	cout << "The max lexicographical string given was " << max << endl;
	cout << "The min lexicographical string given was " << min << endl;




}
