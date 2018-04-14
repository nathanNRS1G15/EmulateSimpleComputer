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

	int *compiledCode = compileAsm("PrimeNumbersProgram.asm");	//Converts asm file into array of machine codes
	simpleComputer PC;								//Creates instance of emulator

#if DEBUGMODE
	openLogFile("debug.txt");						//If debugmode is true within debug.h, debug file is opened
#endif
	PC.flashMemory(compiledCode, numLines);			//Writes program's machine code into emulator memory
	PC.startCPU();									//Starts the CPU execution cycles
#if DEBUGMODE
	closeLogFile();									//Closes debug file is program in debug mode
#endif
	return 0;
}
