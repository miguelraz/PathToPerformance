#include "std_lib_facilities.h"

int main() {
	cout << "Gimme some spelled out numbers" << endl;
	string numbah;
	cin >> numbah;
	if (numbah != "zero"
		&& numbah != "one"
		&& numbah != "two"
		&& numbah != "three"
		&& numbah != "four") simple_error("Not a number I know");

	if (numbah == "zero") cout << 0 << endl;
	if (numbah == "one") cout << 1 << endl;
	if (numbah == "two") cout << 2 << endl;
	if (numbah == "three") cout << 3 << endl;
	if (numbah == "four") cout << 4 << endl;


}
