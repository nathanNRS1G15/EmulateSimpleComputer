/*
 * debug.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: NRS1G15
 */

#include "debug.h"

static string opcodeLookUp[25] = {"lm", "li", "sm", "si", "spdl", "lpdl", "add", "addi", "sub", "subi", "mul", "muli", "div", "divi", "beq", "beqi", "bne", "bnei", "slt", "slti", "j"};
ofstream logFile;

void openLogFile(string file) {
	logFile.open(file, ios::app);
}

void closeLogFile(void) {
	logFile.close();
}


string getTime(void) {
	auto now = chrono::system_clock::now();
	time_t now_time = chrono::system_clock::to_time_t(now);
	string time = ctime(&now_time);
	return time.substr(11, 8);
}

void memoryLog(char function, unsigned int targetAddress, signed int sourceValue) {
	switch (function) {
	case 'S':
		logFile << getTime() << ": Memory : " << function << " : " << sourceValue << " -> ["<< targetAddress << "]." <<  endl;
		break;
	case 'L':
		logFile << getTime() << ": Memory : " << function << " : ["<< targetAddress << "] -> " << sourceValue << "." <<  endl;
		break;
	}
}

void CPULog(char function, signed int input, string regName) {
	switch(function) {
	case 'F':
		logFile << getTime() << ": CPU    : " << function << " : " << input << " -> IR." <<  endl;
		break;
	case 'E':
		logFile << getTime() << ": CPU    : " << function << " : " << opcodeLookUp[input - 1] << "." <<  endl;
		break;
	case 'R':
		logFile << getTime() << ": CPU    : " << regName << " : " << input << "." <<  endl;
	}
}

void ALULog(string function, signed int sourceValue, signed int ACvalue, signed int result) {
	if(function == "PR")
		logFile << getTime() << ": ALU    : " << function << " : " << "PR -> " << ACvalue << ", source -> "<< sourceValue << " : " << result << " -> PR." <<  endl;
	else
		logFile << getTime() << ": ALU    : " << function << " : " << "AC -> " << ACvalue << ", source -> "<< sourceValue << " : " << result << " -> AC." <<  endl;
}

void instructionDecodeLog(string function, unsigned int instruction, int decoded) {
	logFile << getTime() << ": Decoder: " << function << " : " << instruction << " -> " << decoded << "." << endl;
}


