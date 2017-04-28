// Ex5.8 through 5.11.
// Version 1.0 - by @miguelraz 27.04.17
// TBFixed: Differences vector.

#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

class bad_input {}; // Create empy class to be thrown.
class bad_top {};
class bad_size {};
class bad_ints {};
class bad_overflow {};
int main()
try {

	// Take inputs with throws.
	cout << "Gimme the size of N" << endl;
	int N;
	cin >> N;
	if (N <= 0) throw bad_size{};
	cout << N << " is N " << endl;
	vector<int> numbers;

	// Take in # of ints to be added.
	cout << "Gimme the amount of ints you want to add " << endl;
	double top = -1;
	cin >> top;
	cout << " top is " << top << endl;
	if (top < 1) throw bad_top{};

	// Take in ints to add
	cout << "Gime the positive ints. Press '|' to stop " << endl;
	double elements;
	while (cin >> elements) numbers.push_back(elements); // Read until not an integer.

	cout << "the size of numbers.size() is " << numbers.size() << endl;
	cout << "N is " << N << endl;
	if (numbers.size() > N) throw bad_input{};

	// Add, check, print.
	double sum = 0;
	for (int i = 0; i < top; ++i)
		sum += numbers[i];
	if (sum < 0) throw bad_overflow{};
	cout << sum << " is the sum for the first " << N << " numbers " << endl;

	// Make vector of double
	vector<double> diffs(N);
	cout << "diffs is of size " << N << endl;
		for (int i = 0; i < N - 1 ; ++i){
	diffs[i] = numbers[i + 1] - numbers[i];
	cout << " diffs[" << i << "] is " << diffs[i] << endl;
}
	// Finalize!
	cout << "Success!\n";
	keep_window_open();
	return 0;
} catch (exception& e) {
	cout << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
} catch (bad_overflow) {
	cout << "error: double overflow!" << endl;
	keep_window_open();
	return 3;
} catch (bad_input) {
	cout << "error: gave too many ints " << endl;
	keep_window_open();
	return 4;
} catch (bad_ints) {
	cout << "error: Your doubles where not positive " << endl;
	keep_window_open();
	return 5;
} catch (...) {
	cout << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}
