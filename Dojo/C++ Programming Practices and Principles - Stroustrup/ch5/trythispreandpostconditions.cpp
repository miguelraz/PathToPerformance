// 5. Try this - post and pre conditions
#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;
int area(int length, int width)
// calculate area of a rectangle;
// pre-conditions: length and width are positive
// post-condition: returns a positive value that is the area
{
	if (length<=0 || width <=0) simple_error("area() pre-condition");
    int a =  length*width;
    if (a<=0) simple_error("area() post-condition");
    return a;
}

int main() {
	cout << "Gimme an x,y " << endl;
	int x, y;
	cin >> x >> y;
	cout << "x is " << x << " y is " << y << endl;
	cout << "Area return is " << area(x, y) << endl;
}
// break post and not pre conditions, give large numbers so that
// product overflows.
