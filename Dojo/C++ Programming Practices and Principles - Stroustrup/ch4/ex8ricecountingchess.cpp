//Exercise 8 - count the rice on a chessboard
#include "std_lib_facilities.h"
int main()
{
// Rice adventure!
	int current_square = 0;
	int total_rice = 0;
	int riceinsquare = 0;
	int limit = 0;

	cout << "Gimme the amount of rice to limit " << endl;

	cin >> limit;

	while (total_rice < limit) {
		total_rice += pow(2,current_square);

		cout << "The current square was " << current_square << endl;
		cout << "The current rice was " << pow(2,current_square) << endl;
		cout << "The total rice was " << total_rice << endl;
		++current_square;
	}

	cout << "The amount of squares needed to give the inventor " << limit << " grains was "
		<< current_square-1 << " squares " << endl;

	int result;
	cout << "He actually wanted 2^64 grains which was " << pow(2, 64) << endl;

}
