//5 try this error handling
#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

void error(string s1, string s2) {
	throw runtime_error(s1 + s2);
}

int main()
{
	// Take user inputs.
	cout << "Gimme x" << endl;
	int x;
	cin >> x;

	error(" this is 1", "this is 2");
	//try {
	//	cout << sqrt(x) << " sqrt(x) " << endl;
	//	return 0; //0 indicates success.
	//}
	//catch (exception& e) {
	//	cerr << "error: " << e.what() << endl;
	//	keep_window_open();
	//	return 1; // 1 indicates failures.
	//}
	//catch (...) {
	//	cerr << "Oops: unknown exception! " << endl;
	//	keep_window_open();
	//	return 2; // 2 indicates failure.
	//}

}
