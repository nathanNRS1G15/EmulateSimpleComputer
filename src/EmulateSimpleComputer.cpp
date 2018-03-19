//============================================================================
// Name        : EmulateSimpleComputer.cpp
// Author      : NRS1G15
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;


#include "debug.h"
#include "simpleComputer.h"

int main() {
	//cout << "Hello World" << endl; // prints Hello World

	/*unsigned int a = 12;
	signed char b = -128;
	unsigned int c = ((a << 8) | 255) & b; //‭111 0100 1100‬
	cout << (signed int)(signed char)c << endl;
	cout << (c >> 8) << endl;*/

	simpleComputer PC;
	//signed int instruction = 0x01;
	//instruction <<= OPERANDONE;
	//instruction |= 100;
	//instruction <<= OPERANDTWO;

	//cout << instruction << endl;
	int instructions[1];
	instructions[0] = 2;
	instructions[1] = 4;

	PC.flashMemory(&instructions[0], 2);

	int array[3000] = {0};
	array[300] = 0xffff;
	//cout << array[300] << endl;
	return 0;
}
