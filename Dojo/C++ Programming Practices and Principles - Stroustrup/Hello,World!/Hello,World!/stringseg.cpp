#include "std_lib_facilities.h"

int hello() {
	cout << "Please enter your first name and age \n";
	string first_name;
	int age;
	cin >> first_name;
	cin >> age;
	cout << "Hello," << first_name << " (age " << age << ")\n";
}

hello();
