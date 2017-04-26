//Exercise11: Prime checker up to 100
#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{
	vector<int> numbers(100,0);
	vector<int> primes;
	primes[0] = 2;
	int result = 0;
	int check = 0;

	//Outer loop to traverse the number range
	for (int i = 1; i < 100; ++i) {
		//Start checker
		check = 0;

		//Inner loop to check modulus up to current number
		for (int j = 1; j < i; ++i) {
			if (i % j != 0) {
				++check;
				break;
			}
		}
			// Push newfound prime
			if (check == 0)	primes.push_back(i);
			cout << "The next prime is " << primes[i] << endl;
	}
}
