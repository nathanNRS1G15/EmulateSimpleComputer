/*
 * assembler.h
 *
 *  Created on: Mar 19, 2018
 *      Author: NRS1G15
 */

#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

#include <iostream>
#include <string>
#include "instructions.h"
#include <fstream>

static signed int numLines = 0;					//Keeps track of the number of lines in assembler file
string* loadAssemblerFile(string file) {
	static string code[100];					//Buffer to hold the read lines
	ifstream myFile(file);						//Sets up input stream
	int i = 0;									//Initializes counter variable
	if(myFile.is_open()) {						//Checks to see if file has been closed, i.e file is read
		while(getline(myFile, code[i])) {		//Loops until end of file and writes line to buffer at location i
			i = i + 1;							//Increments i
		}
		myFile.close();							//Closes file
	}
	numLines = i;								//Sets number of lines to final value of increment
	return code;								//Returns array of all the lines of assembler read
}

int* convertAssembler(string *asmCode) {
	static int machineCode[100] = {0};			//Buffer for converted machine code
	int commaPos1 = 0;							//Initializes the first comma position
	int commaPos2 = 0;							//Initializes the second comma position
	string secondHalf;							//Initializes the second half of assembler code string
	string opcode;								//Initializes the opcode string
	for(int i = 0; i <= numLines; i++) {				//Loops for the amount of assembler read previously
		commaPos1 = asmCode[i].find_first_of(',');		//Finds and saves the first comma location
		opcode = asmCode[i].substr(0, commaPos1);		//Saves opcode as opcode is from start to first comma
		secondHalf = asmCode[i].substr(commaPos1 + 1, asmCode[i].length());		//Saves assembler code from first comma onwards to extract rest
		commaPos2 = secondHalf.find_first_of(',');		//Saves location of comma 2 in relation to second half
		if(!(opcode.compare("lm"))) {					//Checks the opcode
			machineCode[i] = LM << OPERANDONE;			//Inserts value for LM opcode and shifts it across by the size of operand one
			machineCode[i] |= stoi(secondHalf);			//Inserts value of operand one, which is the value of the first second half number in the assembler
			machineCode[i] <<= OPERANDTWO;				//Shifts across opcode and operand one by size of operand two
		}
		else if(!(opcode.compare("li"))) {
			machineCode[i] = LI << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("sm"))) {
			machineCode[i] = SM << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("si"))) {
			machineCode[i] = SI << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
			//Inserts operand two, which is number after the second comma position
			machineCode[i] |= stoi(secondHalf.substr(commaPos2 + 1, secondHalf.length()));
		}
		else if(!(opcode.compare("spdl"))) {
			machineCode[i] = SPDL << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("lpdl"))) {
			machineCode[i] = LPDL << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("add"))) {
			machineCode[i] = ADD << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("addi"))) {
			machineCode[i] = ADDI << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("sub"))) {
			machineCode[i] = SUB << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("subi"))) {
			machineCode[i] = SUBI << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("mul"))) {
			machineCode[i] = MUL << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("muli"))) {
			machineCode[i] = MULI << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("div"))) {
			machineCode[i] = DIV << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("divi"))) {
			machineCode[i] = DIVI << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("beq"))) {
			machineCode[i] = BEQ << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
			machineCode[i] |= stoi(secondHalf.substr(commaPos2 + 1, secondHalf.length()));
		}
		else if(!(opcode.compare("beqi"))) {
			machineCode[i] = BEQI << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
			//Due to potential signed number, the leading 1s must be removed by the 0x1fff
			//As otherwise they will cause corruption by overwriting the other bits
			machineCode[i] |= (stoi(secondHalf.substr(commaPos2 + 1, secondHalf.length())) & 0x1fff);
		}
		else if(!(opcode.compare("bne"))) {
			machineCode[i] = BNE << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
			machineCode[i] |= (stoi(secondHalf.substr(commaPos2 + 1, secondHalf.length())) & 0x1fff);
		}
		else if(!(opcode.compare("bnei"))) {
			machineCode[i] = BNEI << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
			machineCode[i] |= (stoi(secondHalf.substr(commaPos2 + 1, secondHalf.length())) & 0x1fff);
		}
		else if(!(opcode.compare("slt"))) {
			machineCode[i] = SLT << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("slti"))) {
			machineCode[i] = SLTI << OPERANDONE;
			machineCode[i] |= stoi(secondHalf);
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("j"))) {
			machineCode[i] = J << (OPERANDONE + OPERANDTWO);
			machineCode[i] |= (stoi(secondHalf.substr(commaPos2 + 1, secondHalf.length())) & 0x1fff);
		}
	}
	return machineCode;
}

int* compileAsm(string file) {
	return convertAssembler(loadAssemblerFile(file));	//returns converted machine code array
}

#endif /* ASSEMBLER_H_ */
