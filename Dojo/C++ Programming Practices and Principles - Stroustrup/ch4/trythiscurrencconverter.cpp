#include "std_lib_facilities.h"

int main() {
	constexpr double dollar_per_euro = 1.07;
	constexpr double dollar_per_peso = .0531632;
	constexpr double dollar_per_pound = 1.282;
	double coin1 = 1;
	char unit = 0;

	cout << "Please enter a currency followed by anoter (e, p, s)" << endl;
	cin >> coin1 >> unit;

switch(unit)
{
	case: 'e'
	 cout << coin1 << " EU == " << dollar_per_euro*coin1 << " US " << endl;
	 break;
	case: 'p'
	 cout << coin1 << " MXN == " << dollar_per_peso*coin1 << " US " << endl;
	 break;
	case: 's'
	 cout << coin1 << " UK == " << dollar_per_pound*coin1 << " US " << endl;
	 break;
	default:
	 cout << "Sorry, I don't know a unit called " << unit << endl;
}

}
