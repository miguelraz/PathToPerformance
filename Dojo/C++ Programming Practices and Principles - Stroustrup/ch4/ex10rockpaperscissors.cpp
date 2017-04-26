//Exercise 10: Make a rock paper scissors with computer using a semirandom choice.

//#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

int winner(string str1, string str2)
{
	cout << "You chose " << str1 << endl;
	cout << "CPU chose " << str2 << endl;


	if (str1 == str2){
		cout << "Whoops! Tie! Try again. " << endl;
		return 0;
	}
	if (str1 == "Paper" && str2 == "Rock"){
		cout << "You won!" << endl;
		return 0;
	}

	if (str1 == "Rock" && str2 == "Scissors"){
		cout << "You won!" << endl;
		return 0;
	}

	if (str1 == "Scissors" && str2 == "Paper"){
		cout << "You won!" << endl;
		return 0;
	}

	// Else is a losing scenario or
	cout << "You lost! :( " << endl;
	return 0;
}

int main()
{
	// Setup inputs
	vector<string> choices = { "Rock", "Paper", "Scissors" };
	string input; double  counter = 1;
	string choice;
	cout << "Gimme Rock, Paper, or Scissors " << endl;
	cin >> input;

	// Start game
	while (cin >> input) {
		// CPU chooses
		choice = choices[pow(2, counter) % 3];
		++counter;

		switch (input.substr(0)) {
		case 'R':
			winner(input, choice);
			break;
		case 'S':
			winner(input, choice);
			break;
		case 'P':
			winner(input, choice);
			break;
		default:
			cout << "That is not a valid input. Choose Rock, Paper or Scissors. " << endl;
		}
	}
}
