// Ex5.12 - Bulls and Cows
// Version 1.0 - by @miguelraz 28.04.17
// TBFixed - input a random number into guesses.
// TBFixed - check for cows not doing shenanigans, or accept only distinct digits.

#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

class bad_ints {};
class bad_input {};
class bad_size {};
class bad_overflow {};

// Wanna play?
// Asks player if they want to play Cows and Bulls, otherwise exits.
int asktoplay(){
	cout << "ASK: Do you want to play Cows and Bulls ? 1 for yes, 0 for no " << endl;
	int choice;
	cin >> choice;
	if (choice != 0 && choice != 1) throw bad_input{};
	if (choice == 1) {
		return 1;
	}
	if (choice == 0) {
		cout << " Have a good day ! " << endl;
		return 0;
	}
}

// Begin - start random seed with user input.
// Asks user for an randseed, returns code/solution for game.
// FIX:
// Need typeid func.
vector<int> begin(){

	cout << "BEGIN: Gimme an int to feed to randseed " << endl;
	int choice;
	cin >> choice;
	// if (choice < 0) throw bad_input{};
	srand(choice);
	vector<int> code(4);
	for (int k = 0; k < 4; ++k) {
			code.push_back(rand() % 10);
	}
	return code;
}

// Retrieve guess
// Takes user guess for what code is and returns it as vector<int> guess(3);
vector<int> retrieveguess() {

	cout << "RETRIEVE: Input a 4 digit number " << endl;
	vector<int> guess(4);
	cin >> guess[0] >> guess[1] >> guess[2] >> guess[3];
	// if (guess[i] == typeid(int)) throw bad_input{};
		return guess;


}
// Win condition
// Takes two vector<int>, outputs message if identical.
int wincondition(vector<int> guess, vector<int> code) {
	cout << "WINCONDITION?" << endl;
	if (guess[0] == code[0] &&	guess[1] == code[1] &&	guess[2] == code[2] &&	guess[3] == code[3]) {
		cout << " YOU WON! Would you like to play again? 1/Y 0/N" << endl;
		int choice;
		cin >> choice;
		if (choice != 0 && choice != 1) throw bad_input{};
		if (choice == 0) return 0;
	}
}

// Compare guess and code
// Takes two vector<int>, outputs message after comparing.
void compareguesscode(vector<int> guess, vector<int> code) {
	cout << "COMPARE: Comparing guess and code" << endl;
	int bulls = 0;
	int cows = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (guess[i] == code[j] && i != j) cows += 1;
		}
		if (guess[i] == code[i]) bulls += 1;

	}
	// We are counting cows twice as many times as needed
	cout << " Your guess had " << bulls << " bulls and " << cows/2 << " cows!" << endl;
}

int main()

try {

	int choice = asktoplay();
	vector<int> code = begin();

	// add a while to keep on playing
	while (true) {
		vector<int> guess = retrieveguess();
		wincondition(guess, code);
		compareguesscode(guess, code);
	}
		// choice = asktoplay();

		// Finalize!
		cout << "Success!\n";
		keep_window_open();
		return 0;

}
	catch (exception& e) {
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
