// Change the program to write out the smaller value is: followed by the
// smaller of the numbers and the larger value is: followed by the larger value.
#include "std_lib_facilities.h"

int main()
{
	cout << "Gimme 2 ints" << endl;
	int val1 = 0, val2 = 0;
	while (cin >> val1 >> val2)
	{
		if (val2 < val1)
		{
			int temp = 0;
			temp = val2;
			val2 = val1;
			val1 = temp;
		}
		cout << "The smaller value is: " << val1 << endl;
		cout << "The larger value is: " << val2 << endl;
	}
}
