#include "std_lib_facilities.h"

int main() {
	cout << "Gimme 3 ints" << endl;
	int val1 = 0;
	int val2 = 0;
	int val3 = 0;

	cin >> val1;
	cin >> val2;
	cin >> val3;

	if (val1 <= val2 && val2 <= val3) cout << "Your ordered numbers are " << val1 << " " << val2 << " " << val3 << endl;
	if (val1 <= val3 && val3 <= val2) cout << "Your ordered numbers are " << val1 << " " << val3 << " " << val2 << endl;
	if (val2 <= val3 && val3 <= val1) cout << "Your ordered numbers are " << val2 << " " << val3 << " " << val1 << endl;
	if (val2 <= val1 && val1 <= val3) cout << "Your ordered numbers are " << val2 << " " << val1 << " " << val3 << endl;
	if (val3 <= val2 && val2 <= val1) cout << "Your ordered numbers are " << val3 << " " << val2 << " " << val1 << endl;
	if (val3 <= val1 && val1 <= val2) cout << "Your ordered numbers are " << val3 << " " << val1 << " " << val2 << endl;

}
