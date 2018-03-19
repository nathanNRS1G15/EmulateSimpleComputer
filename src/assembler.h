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

string* loadAssemblerFile(string file) {
	static string code[50];
	ifstream myFile(file);
	int i = 0;
	if(myFile.is_open()) {
		while(getline(myFile, code[i])) {
			i = i + 1;
		}
		myFile.close();
	}
	return code;
}

int* convertAssembler(string *asmCode) {
	static int machineCode[50] = {0};
	int commaPos = 0;
	string opcode = "";
	for(int i = 0; i < 3; i++) {
		commaPos = asmCode[i].find_first_of(',');
		opcode = asmCode[i].substr(0, commaPos);
		if(!(opcode.compare("lw"))) {
			machineCode[i] = LW << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("li"))) {
			machineCode[i] = LI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("sw"))) {
			machineCode[i] = SW << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("add"))) {
			machineCode[i] = ADD << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("addi"))) {
			machineCode[i] = ADDI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("sub"))) {
			machineCode[i] = SUB << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("subi"))) {
			machineCode[i] = SUBI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("mul"))) {
			machineCode[i] = MUL << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("muli"))) {
			machineCode[i] = MULI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("div"))) {
			machineCode[i] = DIV << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("divi"))) {
			machineCode[i] = DIVI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
	}
	return machineCode;
}

int* compileAsm(string file) {
	return convertAssembler(loadAssemblerFile(file));
}

#endif /* ASSEMBLER_H_ */
