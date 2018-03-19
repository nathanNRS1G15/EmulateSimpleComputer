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
	simpleComputer PC;

	PC.flashMemory(compiledCode, numLines);
	PC.startCPU();
	for(int i = 0; i < 100; i++)
		cout << PC.readMem(i) << endl;
	return 0;
}
