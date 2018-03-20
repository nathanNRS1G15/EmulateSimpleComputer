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

static signed int numLines = 0;
string* loadAssemblerFile(string file) {
	static string code[100];
	ifstream myFile(file);
	int i = 0;
	if(myFile.is_open()) {
		while(getline(myFile, code[i])) {
			i = i + 1;
		}
		myFile.close();
	}
	numLines = i;
	return code;
}

int* convertAssembler(string *asmCode) {
	static int machineCode[100] = {0};
	int commaPos1 = 0;
	int commaPos2 = 0;
	string secondHalf;
	string opcode;
	for(int i = 0; i <= numLines; i++) {
		commaPos1 = asmCode[i].find_first_of(',');
		opcode = asmCode[i].substr(0, commaPos1);
		secondHalf = asmCode[i].substr(commaPos1 + 1, asmCode[i].length());
		commaPos2 = secondHalf.find_first_of(',');
		if(!(opcode.compare("lm"))) {
			machineCode[i] = (LM << OPERANDONE) | stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("li"))) {
			machineCode[i] = LI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("sm"))) {
			machineCode[i] = SM << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("si"))) {
			machineCode[i] = SI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
			machineCode[i] |= stoi(secondHalf.substr(commaPos2 + 1, secondHalf.length()));
		}
		else if(!(opcode.compare("spdl"))) {
			machineCode[i] = SPDL << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("lpdl"))) {
			machineCode[i] = LPDL << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("add"))) {
			machineCode[i] = ADD << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("addi"))) {
			machineCode[i] = ADDI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("sub"))) {
			machineCode[i] = SUB << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("subi"))) {
			machineCode[i] = SUBI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("mul"))) {
			machineCode[i] = MUL << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("muli"))) {
			machineCode[i] = MULI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("div"))) {
			machineCode[i] = DIV << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("divi"))) {
			machineCode[i] = DIVI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("beq"))) {
			machineCode[i] = BEQ << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
			machineCode[i] |= stoi(secondHalf.substr(commaPos2 + 1, secondHalf.length()));
		}
		else if(!(opcode.compare("beqi"))) {
			machineCode[i] = BEQI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
			machineCode[i] |= (stoi(secondHalf.substr(commaPos2 + 1, secondHalf.length())) & 0x1fff);
		}
		else if(!(opcode.compare("bne"))) {
			machineCode[i] = BNE << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
			machineCode[i] |= (stoi(secondHalf.substr(commaPos2 + 1, secondHalf.length())) & 0x1fff);
		}
		else if(!(opcode.compare("bnei"))) {
			machineCode[i] = BNEI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
			machineCode[i] |= (stoi(secondHalf.substr(commaPos2 + 1, secondHalf.length())) & 0x1fff);
		}
		else if(!(opcode.compare("slt"))) {
			machineCode[i] = SLT << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
			machineCode[i] <<= OPERANDTWO;
		}
		else if(!(opcode.compare("slti"))) {
			machineCode[i] = SLTI << OPERANDONE;
			machineCode[i] |= stoi(asmCode[i].substr(commaPos1 + 1, asmCode[i].length()));
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
	return convertAssembler(loadAssemblerFile(file));
}

#endif /* ASSEMBLER_H_ */
