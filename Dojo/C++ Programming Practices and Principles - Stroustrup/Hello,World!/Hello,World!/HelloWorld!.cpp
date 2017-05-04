// Trythis6
#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

class bad_ints {};
class bad_input {};
class bad_size {};
class bad_overflow {};

int main()

try {



	}
} catch (exception& e) {
		cout << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (bad_overflow) {
		cout << "error: There was an overflow issue." << endl;
		keep_window_open();
		return 3;
	}
	catch (bad_input) {
		cout << "error: Check your input " << endl;
		keep_window_open();
		return 4;
	}
	catch (bad_ints) {
		cout << "error: Entries were not non-negative " << endl;
		keep_window_open();
		return 5;
	}
	catch (...) {
		cout << "Oops: unknown exception!\n";
		keep_window_open();
		return 2;
	}

