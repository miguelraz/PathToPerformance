// Chapter6 - Try this - premade calculator
// Miguel Raz Guzman Macedo
// V1.0
// 04/05/2017
//
// This is example code from Chapter 6.6 "Trying the first version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//
#include "std_lib_facilities.h"
double expression();
double term();
double primary();
//------------------------------------------------------------------------------
class Token {
public:
	char kind;        // what kind of token
	double value;     // for numbers: a value
	Token(char ch) :kind(ch), value(0) { } // make a token from a char
	Token(char ch, double val) :kind(ch), value(val) { } // make a Token from a char and a double
};
//------------------------------------------------------------------------------
Token get_token()    // read a token from cin
{
	char ch;
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
		not yet   case ';':    // for "print"
		not yet   case 'q':    // for "quit"
	case '(': case ')': case '+': case '-': case '*': case '/':
		return Token(ch);        // let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;              // read a floating-point number
		return Token('8', val);   // let '8' represent "a number"
	}
	default:
		error("Bad token");
	}
}
//------------------------------------------------------------------------------
double expression()  // read and evaluate a Expression
{
	double left = term();      // read and evaluate a Term
	Token t = ts.get();     // get the next token
	while (true) {
		switch (t.kind) {
		case '+':
			left += term();    // evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left -= term();    // evaluate Term and subtract
			t = ts.get();
			break;
		default:
			ts.putback();
			return left;       // finally: no more + or -: return the answer
		}
	}
}
//------------------------------------------------------------------------------
double term()        // read and evaluate a Term
{
	double left = primary();
	Token t = ts.get();     // get the next token
	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		default:
			return left;
		}
	}
}
//------------------------------------------------------------------------------
double primary()     // read and evaluate a Primary
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':    // handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '8':            // we use '8' to represent a number
		return t.value;  // return the number's value
	default:
		error("primary expected");
	}
}
int main()
try {
	double val = 0;
	while (cin)
	Token t = ts.get();

	if (t.kind == 'q') break;
	if (t.kind == ';')
		cout << "=" << expression() << '\n';
	keep_window_open("~0");
}
catch (exception& e) {
	cerr << e.what() << endl;
	keep_window_open("~1");
	return 1;
}
catch (...) {
	cerr << "exception \n";
	keep_window_open("~2");
	return 2;
}
//------------------------------------------------------------------------------
