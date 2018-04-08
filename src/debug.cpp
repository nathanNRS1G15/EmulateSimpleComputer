/*
 * debug.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: NRS1G15
 */

#include "debug.h"

//Array of all opcodes, so when, for example, 0x01 opcode is called debug can look up 0x01 and see its "li"
static string opcodeLookUp[25] = {"lm", "li", "sm", "si", "spdl", "lpdl", "add", "addi", "sub", "subi", "mul", "muli", "div", "divi", "beq", "beqi", "bne", "bnei", "slt", "slti", "j"};
ofstream logFile;

void openLogFile(string file) {
	logFile.open(file, ios::app); //Opens argument file in append mode which is now in the global variable
}

void closeLogFile(void) {
	logFile.close(); //Closes log file
}


string getTime(void) {
	/*
	 * reference for this section www.cplusplus.com/reference/chrono/system_clock/now/
	 */
	auto now = chrono::system_clock::now(); 					//Gets the current time
	time_t now_time = chrono::system_clock::to_time_t(now); 	//Converts time to time_t format
	string time = ctime(&now_time);								//Converts time_t format time to string
	return time.substr(11, 8);									//Removes unwanted part of time format, the date and year so only current time is left
}

void memoryLog(char function, unsigned int targetAddress, signed int sourceValue) {
	switch (function) { 		//Switch based on the current memory mode; save or load
	case 'S':					//Save mode
		logFile << getTime() << ": Memory : " << function << " : " << sourceValue << " -> ["<< targetAddress << "]." <<  endl;	//Writes current time, memory mode, source and target address to log file
		break;
	case 'L':					//Load mode
		logFile << getTime() << ": Memory : " << function << " : ["<< targetAddress << "] -> " << sourceValue << "." <<  endl;	//Writes current time, memory mode, source and target address to log file
		break;
	}
}

void CPULog(char function, signed int input, string regName) {
	switch(function) {			//Switch based on the current CPU mode; Fetch, Execute, Register manipulation
	case 'F':					//Fetch mode
		logFile << getTime() << ": CPU    : " << function << " : " << input << " -> IR." <<  endl;	//Writes time, CPU function and variable value being loaded into IR to log file
		break;
	case 'E':					//Execute mode
		logFile << getTime() << ": CPU    : " << function << " : " << opcodeLookUp[input - 1] << "." <<  endl;	//Writes time, CPU function and decoded opcode to log file
		break;
	case 'R':					//Register mode
		logFile << getTime() << ": CPU    : " << regName << " : " << input << "." <<  endl;		//Writes time, CPU function, register and its current value to log file
	}
}

void ALULog(string function, signed int sourceValue, signed int ACvalue, signed int result) {
	if(function == "PR")		//Data written to log file based on if the ALU is altering PR or standard operation
		logFile << getTime() << ": ALU    : " << function << " : " << "PR -> " << ACvalue << ", source -> "<< sourceValue << " : " << result << " -> PR." <<  endl;	//Writes time, ALU function, current PR value and number being written to PR register to log file
	else
		logFile << getTime() << ": ALU    : " << function << " : " << "AC -> " << ACvalue << ", source -> "<< sourceValue << " : " << result << " -> AC." <<  endl;	//Writes time, ALU function, current AC value, source value and the result of the operation to log file
}

void instructionDecodeLog(string function, unsigned int instruction, int decoded) {
	logFile << getTime() << ": Decoder    : " << function << " : " << instruction << " -> " << decoded << "." << endl;	//Writes time, decoder function, original instruction value and decoded value to log file
}

void busLogWrite(signed int address, signed int data) {
	logFile << getTime() << ": BUS        : " << "Write: Address: " << address << ", Data: "<< data << endl;
}

void busLogRead(signed int address) {
	logFile << getTime() << ": BUS        : " << "Read: Address: " << address << endl;
}

void IOlog(signed int address, signed int data) {
	logFile << getTime() << ": IO     :     " << "Write: Address: " << address << ", Data: "<< data << endl;
}

