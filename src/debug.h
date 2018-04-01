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

#define DEBUGMODE true					//defines whether the program should be complied in debug mode or not

string getTime(void);					//Gets the current time as a string in form HH:MM:SS
void openLogFile(string file);			//Opens the wanted file as a log file
void closeLogFile();					//Closes log file
void memoryLog(char function, unsigned int targetAddress, signed int sourceValue);				//Used to log memory activity
void CPULog(char function, signed int input, string regName);									//Used to log CPU activity
void ALULog(string function, signed int sourceValue, signed int ACvalue, signed int result);	//Used to log ALU activity
void instructionDecodeLog(string function, unsigned int instruction, int decoded);				//Used to log decoder activity

#endif /* DEBUG_H_ */
