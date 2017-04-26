// This program reads in words and spits out the same words but with Broccoli
// replaced by BLEEP.

#include "std_lib_facilities.h"

int main()
{
	vector<string> words;

	for (string temp; cin >> temp;) {
		if (temp == "Broccoli")	string temp = "BLEEP";
		words.push_back(temp);
	}
	for (int i = 0; i < words.size(); ++i)
		cout << words[i] << endl;

}
