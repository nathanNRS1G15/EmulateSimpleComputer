//============================================================================
// Name        : EmulateSimpleComputer.cpp
// Author      : NRS1G15
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;


#include "debug.h"
#include "simpleComputer.h"
#include "assembler.h"

int main() {

	int *compiledCode = compileAsm("tests.asm");
	cout << compiledCode[0] << endl;
	cout << compiledCode[1] << endl;
	cout << compiledCode[2] << endl;
	simpleComputer PC;

	PC.flashMemory(compiledCode, 3);
	return 0;
}
