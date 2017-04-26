#include "std_lib_facilities.h"

int main() {
	cout << "Gimme some penny, nickel, dime, quarters, halfs, dollar coins" << endl;
	int pennies, nickels, dimes, quarters, halfs, dollars, temp1;

	cout << "Gimme pennies" << endl;
	cin >> pennies;
	cout << "Gimme nickels" << endl;
	cin >> nickels;
	cout << "Gimme dimes" << endl;
	cin >> dimes;
	cout << "Gimme quarters" << endl;
	cin >> quarters;
	cout << "Gimme halfs" << endl;
	cin >> halfs;
	cout << "Gimme dollars" << endl;
	cin >> dollars;

	if (pennies == 1) cout << "You have 1 penny." << endl;
		cout << "You have " << pennies << " pennies." << endl;

    if (nickels == 1) cout << "You have 1 nickel." << endl;
	    cout << "You have " << nickels << " nickel." << endl;

	if (dimes == 1) cout << "You have 1 dime." << endl;
	    cout << "You have " << dimes << " dime." << endl;

	if (quarters == 1) cout << "You have 1 quarter." << endl;
	    cout << "You have " << quarters << " quarters." << endl;

	if (halfs == 1) cout << "You have 1 half-dollar." << endl;
	    cout << "You have " << halfs << " half-dollars." << endl;

	if (dollars == 1) cout << "You have 1 dollar." << endl;
    	cout << "You have " << dollars << " one-dollar coins." << endl;

		temp1 = pennies*1 + nickels*5 + dimes*10 + quarters*25 + halfs*50 + dollars*100;

		cout << "Total is " << temp1 << endl;
		cout << "You have $" << temp1 / 100  << "." << temp1 % 100  << endl;

}
