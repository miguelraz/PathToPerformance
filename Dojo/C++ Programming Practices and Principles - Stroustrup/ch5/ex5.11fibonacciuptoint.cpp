// Ex5.11 - Fibonnaci up to int.
// Version 1.0 - by @miguelraz 27.04.17
//

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

	// Take inputs with throws.
	int  sum = 0;
	int f1 = 1;
	int f2 = 1;
	int i = 0;

	while( sum >= 0){
		++i;
		    sum = f1 + f2;
			f1 = f2;
			f2 = sum;
			cout << "The " << i+2 << "th fibonacci number is " << f2 << endl;
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
	cout << "error: There was an overflow issue." << endl;
	keep_window_open();
	return 3;
} catch (bad_input) {
	cout << "error: Check your input " << endl;
	keep_window_open();
	return 4;
} catch (bad_ints) {
	cout << "error: Entries were not non-negative " << endl;
	keep_window_open();
	return 5;
} catch (...) {
	cout << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}
