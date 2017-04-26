// Ex. 17 - Quadratic root solver
#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{
	// Inputs and setups
	vector<int> scores;
	vector<string> names;
	string nam = ""; int sco = 0;

	// Get names from user.
	while (nam != "no" || sco != 0) {
		cout << " Gimme a name and a score " << endl;
		cin >> nam >> sco;
		names.push_back(nam); 
		scores.push_back(sco);
	}

	// Sanity test.
	for (int i = 0; i < names.size(); ++i) cout << names[i] << " had " << scores[i] << " points " << endl;

	// Check if repeated.
	for (int i = 0; i < names.size()-1; ++i) {
		for (int j =  i; j < names.size() - 1 ; ++i) {
			if (names[i] == names[j+2]) {
				cout << "names index is at " << i << " " << names[i] << " names[i]" << endl;
				cout << "names index is at " << j << " " << names[j + 1] << " names[j+1]" << endl;
				return 0;
			}
		}

		cout << names[i] << " had " << scores[i] << " points " << endl;
	}

	//Exercise 20
	//Output corresponding score to name or name not found.
	cout << "Now gimme a name to check for " << endl;
	string searchname; int searchscore;
	cin >> searchname;
	for (int x : names) {
		if (searchname == names[x]) {
			cout << names[x] << " had a score of " << scores[x] << endl;
			break;
		}
	}
		cout << " Name not found. " << endl;


	//Exercise 21
	//Output corresponding names given scores or score not found
	int	check = 0;
		cout << "Now gimme a score to check for " << endl;
		for (int x : scores) {
			if (searchschore == score[x]) {
				cout << names[x] << " had a score of " << scores[x] << endl;
				check += 1;
				continue;
			}
		}
		if (check == 0) cout << "Sorry, no one had that score." << endl;
}
