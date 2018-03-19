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
	signed int instructions[1];

	signed int instruction = LI;
	instruction <<= OPERANDONE;
	instruction |= 100;
	instruction <<= OPERANDTWO;
	instructions[0] = instruction;

	instruction = ADDI;
	instruction <<= OPERANDONE;
	instruction |= 100;
	instruction <<= OPERANDTWO;
	instructions[1] = instruction;

	PC.flashMemory(&instructions[0], 2);
	return 0;
}
