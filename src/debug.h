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

#define DEBUGMODE true

string getTime(void);
void openLogFile(string file);
void closeLogFile();
void memoryLog(char function, unsigned int targetAddress, signed int sourceValue);
void CPULog(char function, signed int input, string regName);
void ALULog(string function, signed int sourceValue, signed int ACvalue, signed int result);
void instructionDecodeLog(string function, unsigned int instruction, int decoded);

#endif /* DEBUG_H_ */
