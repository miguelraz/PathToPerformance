#include "std_lib_facilities.h"

int square(int n) {
	int sum = 0;

	for (int i = 0; i < n; ++i)
	{
		sum += n;
	}

	return sum;
}

int main()
{

	for (int i = 0; i < 100; ++i) cout << i << " " << square(i) << endl;
}
