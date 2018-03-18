/*
 * debug.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: NRS1G15
 */

#include "debug.h"

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
		logFile << getTime() << ": Memory: " << function << " : " << sourceValue << " -> ["<< targetAddress << "]." <<  endl;
		break;
	case 'L':
		logFile << getTime() << ": Memory: " << function << " : ["<< targetAddress << "] -> " << sourceValue << "." <<  endl;
		break;
	}
	logFile.close();
}

void CPULog(string function, signed int input) {
	ofstream logFile;
	logFile.open ("debug.txt", ios::app);
	logFile << getTime() << ": CPU: " << function << " : " << input << " -> IR." <<  endl;
	logFile.close();
}

void ALULog(string function, signed int sourceValue, signed int ACvalue, signed int result) {
	ofstream logFile;
	logFile.open ("debug.txt", ios::app);
	logFile << getTime() << ": ALU: " << function << " : " << "AC -> " << ACvalue << ", source -> "<< sourceValue << " : " << result << " -> AC." <<  endl;
	logFile.close();
}

void instructionDecodeLog(string function, unsigned int instruction, int decoded) {
	ofstream logFile;
	logFile.open ("debug.txt", ios::app);
	logFile << getTime() << ": Decoder: " << function << " : " << instruction << " -> " << decoded << "." << endl;
	logFile.close();
}



