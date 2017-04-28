#include "std_lib_facilities.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
try {
	cout << "Success!\n";
	keep_window_open();
	return 0;
} catch (exception& e) {
	cout << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
} catch (...) {
	cout << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}

//1. Cout << "Success!\n";
// Undeclared identifier Cout

//2. cout << "Success!\n;
// Newline in constant - didn't finish ''

//3. cout << "Success" << !\n"
// Illegal escape sequence - missing ;, unfinished ''

//4. cout << success << '\n';
// 'success' is not declared. Needs to be a string or var for cout.

//5. string res = 7; vector<int> v(10); v[5] = res; cout << "Success!\n";
// Inserting string into a vector. Derp. --cannot convert from 'int' to 'string'

//6. vector<int> v(10); v(5) = 7; if (v(5) != 7) cout << "Success!\n";
// Need square brackets :D

//7. if (cond) cout << "Success!\n"; else cout << "Fail!\n";
// cond is not defined

//8. bool c = false; if (c) cout << "Success!\n"; else cout << "Fail!\n";
// c is false

//9. string s = "ape"; boo c = "fool"<s; if (c) cout << "Success!\n";
// Doesn't say bool.

//10. string s = "ape"; if (s == "fool") cout << "Success!\n";
// Need to change conditional to 'ape'.

//11. string s = "ape"; if (s == "fool") cout < "Success!\n";
// Missing a '<<' after the cout.

//12. string s = "ape"; if (s + "fool") cout < "Success!\n";
// Conditional is not a test.

//13. vector<char> v(5); for (int i = 0; 0<v.size(); ++i); cout << "Success!\n";
// 0 is the index - infinte loop!

//14. vector<char> v(5); for (int i = 0; i <= v.size(); ++i); cout << "Success!\n";
// The '<=' is not trustworthy.

//15. string s = "Success!\n"; for (int i = 0; i<6; ++i) cout << s[i];
// Accesses characters within string, only prints out to third 's'.

//16. if (true) then cout << "Success!\n"; else cout << "Fail!\n";
// 'then' does not exist in C++.

//17. int x = 2000; char c = x; if (c == 2000) cout << "Success!\n";
// Converting char to int narrows and destroys.

//18. string s = "Success!\n"; for (int i = 0; i<10; ++i) cout << s[i];
// Not many errors, but dirty.

//19. vector v(5); for (int i = 0; i <= v.size(); ++i); cout << "Success!\n";
// Didn't cast vector with a type.

//20. int i = 0; int j = 9; while (i<10) ++j; if (j<i) cout << "Success!\n";
// Infinite loop! update the ++i instead.

//21. int x = 2; double d = 5 / (x–2); if (d == 2 * x + 0.5) cout << "Success!\n";
// DAAAAMN used a whitespace character that wasn't allowed!

//22. string<char> s = "Success!\n"; for (int i = 0; i <= 10; ++i) cout << s[i];
// Delete the <char> part.

//23. int i = 0; while (i<10) ++j; if (j<i) cout << "Success!\n";
// j was not declared/initialized.

//24. int x = 4; double d = 5 / (x–2); if (d = 2 * x + 0.5) cout << "Success!\n";
// Missing an equals, using 'x-2' is not kosher.

//25. cin << "Success!\n"
