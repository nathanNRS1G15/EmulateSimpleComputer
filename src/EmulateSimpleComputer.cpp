//============================================================================
// Name        : EmulateSimpleComputer.cpp
// Author      : NRS1G15
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;

#define DEBUGMODE false

int main() {
	//cout << "Hello World" << endl; // prints Hello World

	/*unsigned int a = 12;
	signed char b = -128;
	unsigned int c = ((a << 8) | 255) & b; //‭111 0100 1100‬
	cout << (signed int)(signed char)c << endl;
	cout << (c >> 8) << endl;*/

	int a = 0;
	unsigned int b = 0xffffffff;
	a = b;
	cout << a << endl;

	return 0;
}
