#include "std_lib_facilities.h"

int main() {

	string first_name;
	cout << "Please give me your first name \n";
	cin >> first_name;

	string friend_name;
	cout << "Please give the name of who you want to write to \n";
	cin >> friend_name;

	string friend_name2;
	cout << "Please give the name of the second friend \n";
	cin >> friend_name2;

	char friend_gender;
	cout << "Please give the gender of your frind as 'm' or 'f' or 'x' \n";
	cin >> friend_gender;
	if (friend_gender != 'x' && friend_gender != 'm' && friend_gender != 'f')
		simple_error("Whoopsies \n");

	int age;
	cout << "Please give the age of the friend \n";
	cin >> age;
	if (age < 0 || age > 110)
		simple_error("You're kidding!");

	cout << "Dear " << friend_name << ", \n";
	cout << "Hope all is well. \n";
	cout << "Weather is lovely \n";

	if (friend_gender == 'm')
		cout << "If you see " << friend_name2 << " please ask him to call me \n";
	else if (friend_gender == 'f')
		cout << "If you see " << friend_name2 << " please ask her to call me \n";
	else if (friend_gender == 'x')
		cout << "If you see " << friend_name2 << " please ask them to call me \n";

	if (age < 12) cout << "Next year you will be " << age + 1 << "\n";
	if (age == 17) cout << "Next year you will be able to vote! \n";
	if (age > 70) cout << "I hope you are enjoying retirement.\n ";

	cout << "Yours sincerely, \n \n" << first_name << "\n";


}
