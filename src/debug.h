/*
 * debug.h
 *
 *  Created on: Mar 18, 2018
 *      Author: NRS1G15
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <ctime>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
using namespace std;

string getTime(void) {
	auto now = chrono::system_clock::now();
	time_t now_time = chrono::system_clock::to_time_t(now);
	string time = ctime(&now_time);
	return time.substr(11, 8);
}
void memoryLog(string function, unsigned int targetAddress, signed int sourceValue) {
	ofstream logFile;
	logFile.open ("debug.txt", ios::app);
	switch (function) {
	case "Save":
		logFile << getTime() << ": Memory: " << function << " : " << sourceValue << " -> ["<< targetAddress << "]." <<  endl;
		break;
	case "Load":
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

#endif /* DEBUG_H_ */
