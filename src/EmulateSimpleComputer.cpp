//============================================================================
// Name        : EmulateSimpleComputer.cpp
// Author      : nrs1g15
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

#if DEBUGMODE
	openLogFile("debug.txt");
#endif
	PC.flashMemory(compiledCode, numLines);
	PC.startCPU();
#if DEBUGMODE
	closeLogFile();
#endif
	return 0;
}
