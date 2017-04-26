//Exercise6: string to number and vice versaspitter
//#include "std_lib_facilities.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
int main()
{
	vector<string> written_number = {"zero", "one", "two", "three",
	"four", "five", "six", "seven", "eight", "nine"};
	string input;

	while (cin >> input)
	{
		cout << "Gimme a number or a string for a number" << endl;

		if (iss(input))
			for (int i = 0; i < 10; ++i)
				if (input == written_number[i]) cout << i << endl;

		if (isdigit(input)))
			for (int i = 0; i < 10; ++i)
				if (input == i) cout << written_number[i] << endl;
	}



}
