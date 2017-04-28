// Ex. 17 - Quadratic root solver
#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

int area(int length, int width) {

	//Check for area stuff
	if (length <= 0 || width <= 0) return -1;

	//Output.
	cout << "area(::int, ::int) returns " << length*width << endl;
	return length*width;
}
int frame_area(int x, int y) {

	//Check arguments and calculate frame
	constexpr int frame_width = 2;
	if (x - frame_width <= 0 || y - frame_width <= 0) error("non-positive area yo");

	// Output results.
	cout << "frame_area returns " << area(x - frame_width, y - frame_width) << endl;
	return area(x - frame_width, y - frame_width);

}

int f(int x, int y, int z) {

	// Calculate and print areas.
	int area1 = area(x, y);
	if (area1 <= 0) error("non positive area ");
	cout << "First pass. " << endl;

	int area2 = frame_area(3, z); // Mistake was here.
	cout << "Second pass. " << endl;

	int area3 = frame_area(y, z);
	cout << "Third pass. " << endl;
	double ratio = double(area1) / area3;

	// Output results.
	cout << "Area1 " << area1 << endl;
	cout << "Area2 " << area2 << endl;
	cout << "Area3 " << area3 << endl;
	cout << "Ratio " << ratio << endl;

	//Return.
	return ratio;
}

int main()
{
	// Take user inputs.
	cout << "Gimme x, y, and frame_width " << endl;
	int x, y, z;
	cin >> x >> y >> z;

	cout << "area(x,y) in main returns " << area(x, y) << endl;
	cout << endl;
	cout << "frame_area(x,y) in main returns " << frame_area(x, y) << endl;
	cout << endl;
	cout << "f(x,y,z) in main returns " << f(x, y, z) << endl;;


}
