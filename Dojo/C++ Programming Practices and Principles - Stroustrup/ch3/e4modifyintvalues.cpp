#include "std_lib_facilities.h"

int main() {

	cout << "Gimme 2 ints\n";
	float val1 = 0;
	float val2 = 0;
	cin >> val1;
	cin >> val2;
	cout << "El resultado es: " << val1 + val2 << endl;

	cout << "The larger one is " << max(val1, val2) << " \n";
	cout << "The smaller one is " << min(val1, val2) << " \n";
	cout << "Their difference is " << max(val1,val2) - min(val1,val2) << " \n";
	cout << "Their product is " << val1*val2 << " \n";
	cout << "Their ratio is " << val1 / val2 << " \n";

	// Yes, outputs are different if they are ints or floats. The division will be different for ints.
	//
}
