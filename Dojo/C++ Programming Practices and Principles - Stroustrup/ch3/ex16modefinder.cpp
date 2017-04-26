//Exercise 4.16: Mode finder.


#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{
	cout << "Gimme a series of positive digits " << endl;
	int val0;
	vector<int> numbers;
	vector<int> counters;

	// Get inputs
	while (cin >> val0 && val0 != 0) numbers.push_back(val0);

	// Fill empty array
	for (int i = 0; i < numbers.size(); ++i) numbers[0] = 0;

	// Sort numbers array
	sort(numbers.begin(), numbers.end());

	// Count consecutive repetitions and input that into 'counters'
	for (int i = 0; i < numbers.size() - 1; ++i) {
		for (int j = i; j < numbers.size() - 1; j++) {

			if (numbers[i] == numbers[i + j])
				counters[j] += 1;
		}
	}

	// Spit results
	for (int i = 0; i < counters.size(); ++i) cout << "Number " << numbers[i] << " is found " << counters[i] << " times. " << endl;
	
