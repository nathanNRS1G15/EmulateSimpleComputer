/*
 * debug.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: NRS1G15
 */

#include "debug.h"

static string opcodeLookUp[20] = {"lm", "li", "sm", "si", "add", "addi", "sub", "subi", "mul", "muli", "div", "divi", "beq", "beqi", "bne", "bnei", "slt", "slti", "j"};

string getTime(void) {
	auto now = chrono::system_clock::now();
	time_t now_time = chrono::system_clock::to_time_t(now);
	string time = ctime(&now_time);
	return time.substr(11, 8);
}
void memoryLog(char function, unsigned int targetAddress, signed int sourceValue) {
	ofstream logFile;
	logFile.open ("debug.txt", ios::app);
	switch (function) {
	case 'S':
		logFile << getTime() << ": Memory : " << function << " : " << sourceValue << " -> ["<< targetAddress << "]." <<  endl;
		break;
	case 'L':
		logFile << getTime() << ": Memory : " << function << " : ["<< targetAddress << "] -> " << sourceValue << "." <<  endl;
		break;
	}
	logFile.close();
}

void CPULog(char function, signed int input, string regName) {
	ofstream logFile;
	logFile.open ("debug.txt", ios::app);
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

	logFile.close();
}

void ALULog(string function, signed int sourceValue, signed int ACvalue, signed int result) {
	ofstream logFile;
	logFile.open ("debug.txt", ios::app);
	if(function == "PR")
		logFile << getTime() << ": ALU    : " << function << " : " << "PR -> " << ACvalue << ", source -> "<< sourceValue << " : " << result << " -> PR." <<  endl;
	else
		logFile << getTime() << ": ALU    : " << function << " : " << "AC -> " << ACvalue << ", source -> "<< sourceValue << " : " << result << " -> AC." <<  endl;

	logFile.close();
}

void instructionDecodeLog(string function, unsigned int instruction, int decoded) {
	ofstream logFile;
	logFile.open ("debug.txt", ios::app);
	logFile << getTime() << ": Decoder: " << function << " : " << instruction << " -> " << decoded << "." << endl;
	logFile.close();
}


