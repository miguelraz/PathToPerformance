// Ex5.13 - days of the week and value skipping if in list
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

	vector<int> numbers;
	vector<string> days;

	int num; string day;

	while (cin >> day >> num) {
		days.push_back(day);
		numbers.push_back(num);
	}

	vector<string> syns =
	{"Mon", "monday", "mon", "Tue", "tuesday", "tue", "Wednesday", "Wed", "wed", "Thur", "thursday", "thur",
	"Fri", "friday", "fri", "Saturday", "Sat", "saturday", "sunday", "sun", "sunday" };
	int sum = 0;
	for (int i = 0; i < numbers.size(); ++i) {
		sum += numbers[i];

	}
	cout << "The sum of all values is " << sum << endl;

	string alldays;
	for (int i = 0; i < days.size(); ++i) {
		for (int j = 0; j < syns.size(); ++j) {
			if (days[i] == syns[j]) {
				++i;
				break;
			}
			alldays += days[i];
		}
		cout << "All the days are " << alldays << endl;

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
