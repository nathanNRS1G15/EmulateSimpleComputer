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
#include <vector>
using namespace std;
const string program = "PrimeNumbersProgram";		//Name of assembler file to run

int main() {
	int *compiledCode = compileAsm(program + string(".asm"));	//Converts asm file into array of machine codes
	simpleComputer PC;								//Creates instance of emulator

#if DEBUGMODE
	openLogFile(program + string("Debug.txt"));		//If debugmode is true within debug.h, debug file is opened
#endif
	PC.flashMemory(compiledCode, numLines);			//Writes program's machine code into emulator memory. numLines is global variable in assembler.h
	PC.startCPU();									//Starts the CPU execution cycles
#if DEBUGMODE
	closeLogFile();									//Closes debug file is program in debug mode
#endif
	return 0;
}
